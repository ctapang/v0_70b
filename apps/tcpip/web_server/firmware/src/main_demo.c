/*******************************************************************************
  Main Application Entry Point and TCP/IP Stack Demo

  Summary:
    Module for Microchip TCP/IP Stack

  Description:
    -Demonstrates how to call and use the Microchip TCP/IP stack
    -Reference: Microchip TCP/IP Stack Help (tcpip Help.chm)
 *******************************************************************************/

/*******************************************************************************
FileName:  MainDemo.c
Copyright © 2012 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED ?AS IS?WITHOUT WARRANTY OF ANY KIND,
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
// Include all headers for any enabled tcpip functions
#include "tcpip/tcpip.h"

// Include functions specific to this stack application
#include "tcpip/src/system/system_userio.h"



//
// Main application entry point.
//


int main(void)

{
#if defined (EX16_DEMO_BOARD)
    static SYS_TICK startTick = 0;
    SYS_USERIO_LED_STATE LEDstate = SYS_USERIO_LED_DEASSERTED;
#endif
    static IPV4_ADDR dwLastIP[2] = { {-1}, {-1} };

    IPV4_ADDR           ipAddr;
    int                 i, nNets;
    TCPIP_NET_HANDLE    netH;
    const char          *netName, *netBiosName;
    
#if defined (TCPIP_STACK_USE_ZEROCONF_MDNS_SD)
    char mDNSServiceName[] = "MyWebServiceNameX ";     // base name of the service Must not exceed 16 bytes long
                                                       // the last digit will be incremented by interface
#endif  // defined (TCPIP_STACK_USE_ZEROCONF_MDNS_SD)

    // perform system initialization
    SYS_Initialize(0);

    SYS_CONSOLE_MESSAGE("\r\n\n\n --- TCPIP Demo Starts! --- \r\n");

    // Display the names associated with each interface
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

    while (1)
    {
        SYS_Tasks();
#if defined (EX16_DEMO_BOARD)
        // Blink LED0 every second.
        if (SYS_TICK_Get() - startTick >= SYS_TICK_TicksPerSecondGet() / 2ul)
        {
            startTick = SYS_TICK_Get();
            LEDstate ^= SYS_USERIO_LED_ASSERTED;
            SYS_USERIO_SetLED(SYS_USERIO_LED_0, LEDstate);
        }
#endif

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
            }
        }

    }
}




