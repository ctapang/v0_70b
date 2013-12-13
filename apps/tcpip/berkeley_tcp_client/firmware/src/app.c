/*******************************************************************************
  Sample Application

  File Name:
    app.c

  Summary:
    Sample "hello world" application

  Description:
    This file contains the sample "hello world" application's implementation.
 *******************************************************************************/


// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

//#include "system_config.h"
#include "app.h"
#include "system_config.h"

// Include all headers for any enabled tcpip functions
#include "tcpip/src/tcpip_private.h"
#include "tcpip_modules_config.h"
#include "tcpip/tcpip.h"

// Include functions specific to this stack application
#include "tcpip/src/system/system_userio.h"

#include "app_commands.h"
#include <sys/errno.h>


int32_t _APP_ParseUrl(char *uri, char **host, char **path);
int8_t _APP_PumpDNS(const char * hostname, IPV4_ADDR *ipv4Addr);

// *****************************************************************************
// *****************************************************************************
// Section: Global Variable Definitions
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
*/
APP_DATA appData;

// *****************************************************************************
/* Driver objects.

  Summary:
    Contains driver objects.

  Description:
    This structure contains driver objects returned by the driver init routines
    to the application. These objects are passed to the driver tasks routines.
*/

APP_DRV_OBJECTS appDrvObjects;

int nNets;
TCPIP_NET_HANDLE    netH;
SYS_USERIO_LED_STATE LEDstate = SYS_USERIO_LED_DEASSERTED;

// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Initialize( void )
{
    int i;
    const char          *netName, *netBiosName;


#if defined (TCPIP_STACK_USE_ZEROCONF_MDNS_SD)
    char mDNSServiceName[] = "MyWebServiceNameX ";     // base name of the service Must not exceed 16 bytes long
                                                       // the last digit will be incremented by interface
#endif  // defined (TCPIP_STACK_USE_ZEROCONF_MDNS_SD)

    appData.state = APP_TCPIP_WAIT_FOR_IP;

    nNets = TCPIP_STACK_NumberOfNetworksGet();

    for(i = 0; i < nNets; i++)
    {

        netH = TCPIP_STACK_IndexToNet(i);
        netName = TCPIP_STACK_NetNameGet(netH);
        netBiosName = TCPIP_STACK_NetBIOSName(netH);

#if defined(TCPIP_STACK_USE_NBNS)
        SYS_CONSOLE_PRINT("    Interface %s on host %s - NBNS enabled\r\n", netName, netBiosName);
#else
        SYS_CONSOLE_PRINT("    Interface %s on host %s - NBNS disabled\r\n", netName, netBiosName);
#endif  // defined(TCPIP_STACK_USE_NBNS)

#if defined (TCPIP_STACK_USE_ZEROCONF_MDNS_SD)
        mDNSServiceName[sizeof(mDNSServiceName) - 2] = '1' + i;
        TCPIP_MDNS_ServiceRegister( netH
                , mDNSServiceName                   // name of the service
                ,"_http._tcp.local"                 // type of the service
                ,80                                 // TCP or UDP port, at which this service is available
                ,((const uint8_t *)"path=/index.htm")  // TXT info
                ,1                                  // auto rename the service when if needed
                ,NULL                               // no callback function
                ,NULL);                             // no application context
#endif //TCPIP_STACK_USE_ZEROCONF_MDNS_SD

    }

    /* Intialize the app state to wait for
     * media attach. */

    APP_Commands_Init();

}


/*******************************************************************************
  Function:
    void APP_Tasks( void )

  Remarks:
    See prototype in app.h.
 */

void APP_Tasks( void )
{
    static IPV4_ADDR dwLastIP[2] = { {-1}, {-1} };
    IPV4_ADDR           ipAddr;
    int i;

    switch(appData.state)
    {
        case APP_TCPIP_WAIT_FOR_IP:
        {
            // if the IP address of an interface has changed
            // display the new value on the system console
            nNets = TCPIP_STACK_NumberOfNetworksGet();

            for (i = 0; i < nNets; i++)
            {
                netH = TCPIP_STACK_IndexToNet(i);
                ipAddr.Val = TCPIP_STACK_NetAddress(netH);
                if(dwLastIP[i].Val != ipAddr.Val)
                {
                    dwLastIP[i].Val = ipAddr.Val;

                    SYS_CONSOLE_MESSAGE(TCPIP_STACK_NetNameGet(netH));
                    SYS_CONSOLE_MESSAGE(" IP Address: ");
                    SYS_CONSOLE_PRINT("%d.%d.%d.%d \r\n", ipAddr.v[0], ipAddr.v[1], ipAddr.v[2], ipAddr.v[3]);
                    if (ipAddr.v[0] != 0 && ipAddr.v[0] != 169) // Wait for a Valid IP
                    {
                        appData.state = APP_TCPIP_WAITING_FOR_COMMAND;
                        SYS_CONSOLE_MESSAGE("Waiting for command type: openurl <url>\r\n");
                    }
                }
            }
        }
        break;
        case APP_TCPIP_WAITING_FOR_COMMAND:
        {
            if (APP_URL_Buffer[0] != '\0')
            {
                if (_APP_ParseUrl(APP_URL_Buffer, &appData.host, &appData.path))
                {
                    SYS_CONSOLE_PRINT("Could not parse URL '%s'\r\n", APP_URL_Buffer);
                    APP_URL_Buffer[0] = '\0';
                    break;
                }
                appData.state = APP_DNS_START_RESOLUTION;
            }
        }
        break;

        case APP_DNS_START_RESOLUTION:
        {
            DNS_RESULT result = TCPIP_DNS_UsageBegin(0);
            if (result != DNS_RES_OK)
            {
                SYS_CONSOLE_MESSAGE("Error in DNS aborting 1\r\n");
                APP_URL_Buffer[0] = '\0';
                break;
            }
            result = TCPIP_DNS_Resolve(appData.host, DNS_TYPE_A);
            if (result != DNS_RES_OK)
            {
                SYS_CONSOLE_MESSAGE("Error in DNS aborting 2\r\n");
                TCPIP_DNS_UsageEnd(0);
                APP_URL_Buffer[0] = '\0';
                break;
            }
            appData.state = APP_DNS_GET_RESULT;
            APP_URL_Buffer[0] = '\0';
        }
        break;

        case APP_DNS_GET_RESULT:
        {
            switch (_APP_PumpDNS(appData.host, (IPV4_ADDR*)&appData.addr.sin_addr.S_un.S_addr))
            {
                case -1:
                {
                    // Some sort of error, already reported
                    appData.state = APP_TCPIP_WAITING_FOR_COMMAND;
                }
                break;
                case 0:
                {
                    // Still waiting
                }
                break;
                case 1:
                {

                    appData.state = APP_BSD_START;
                }
                break;
            }
        }
        break;

        case APP_BSD_START:
        {
            int tcpSkt;
            // Create a socket for this client to connect with
            if((tcpSkt = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == SOCKET_ERROR )
            {
                return;
            }
            else
            {
                appData.socket = (SOCKET)tcpSkt;
            }

            SYS_CONSOLE_MESSAGE("BSD TCP client: Connecting...\r\n");

            appData.state = APP_BSD_CONNECT;
        }
        break;

        case APP_BSD_CONNECT:
        {
            int addrlen;
            // addr.sin_addr.S_un.S_addr destination IP address was set earlier in DNS step
            appData.addr.sin_port = HTTP_PORT;
            addrlen = sizeof(struct sockaddr);
            if(connect( appData.socket, (struct sockaddr*)&appData.addr, addrlen) < 0)
                return;

            appData.state = APP_BSD_SEND;
        }
        break;
        case APP_BSD_SEND:
        {
            //send TCP data
            char buffer[MAX_URL_SIZE];
            sprintf(buffer, "GET /%s HTTP/1.1\r\n"
                    "Host: %s\r\n"
                    "Connection: close\r\n\r\n", appData.path, appData.host);

            send(appData.socket, (const char*)buffer, strlen((char*)buffer), 0);
            appData.state = APP_BSD_OPERATION;
        }
        break;

        case APP_BSD_OPERATION:
            // Obtian and print the server reply
        {
            char recvBuffer[9];
            while(1)
            {
                i = recv(appData.socket, recvBuffer, sizeof(recvBuffer)-1, 0); //get the data from the recv queue

                if(i <= 0) // close or error condition
                {
                    if(i == 0 || errno != EWOULDBLOCK)
                    {
                        appData.state = APP_BSD_CLOSE; // true error/close condition
                    }
                    // else just wait for some more data

                    break;
                }

                recvBuffer[i] = '\0';    // Null terminate data
                SYS_CONSOLE_PRINT("BSD TCP client: server reply - %s \r\n", recvBuffer);

                if(appData.state == APP_BSD_OPERATION)
                    break;
            }
        }
        break;

        case APP_BSD_CLOSE:
            closesocket(appData.socket);
            appData.state = APP_TCPIP_WAITING_FOR_COMMAND;
            // No break needed

        default:
            return;
    }
}


int32_t _APP_ParseUrl(char *uri, char **host, char **path)
{
    char * pos;
    pos = strstr(uri, "//"); //Check to see if its a proper URL

    if ( !pos )
    {
        return -1;
    }
    *host = pos + 2; // This is where the host should start

    pos = strchr( * host, '/');

    if ( !pos )
    {
        *path = NULL;
    }
    else
    {
        * pos = '\0';
        *path = pos + 1;
    }
    return 0;
}

int8_t _APP_PumpDNS(const char * hostname, IPV4_ADDR *ipv4Addr)
{
    DNS_RESULT result = TCPIP_DNS_IsResolved(hostname, ipv4Addr);
    switch (result)
    {
        case DNS_RES_OK:
        {
            // We now have an IPv4 Address
            TCPIP_DNS_UsageEnd(0);
            // Open a socket
            return 1;
        }
        case DNS_RES_PENDING:
            return 0;
        case DNS_RES_SERVER_TMO:
        case DNS_RES_NO_ENTRY:
        default:
            SYS_CONSOLE_MESSAGE("TCPIP_DNS_IsResolved returned failure\r\n");
            TCPIP_DNS_UsageEnd(0);
            return -1;
    }
    // Should not be here!
    return -1;

}


/*******************************************************************************
 End of File
*/

