/*******************************************************************************
  Generic TCP Server Example Application

  Summary:
    Module for Microchip TCP/IP Stack

  Description:
    -Implements an example "ToUpper" TCP server on port 9760 and
     should be used as a basis for creating new TCP server
     applications

  Description of how to run the demo:
     1) Connect the ethernet port of the programmed demo board to a
          computer either directly or through a router.
     2) Determine the IP address of the demo board.  This can be done several
          different ways.
        a) If you are using a demo setup with an LCD display (e.g. Explorer 16
             or PICDEM.net 2), the IP address should be displayed on the second
             line of the display.
        b) Open the Microchip Ethernet Device Discoverer from the start menu.
             Press the "Discover Devices" button to see the addresses and host
             names of all devices with the Announce Protocol enabled on your
             network.  You may have to configure your computer's firewall to
             prevent it from blocking UDP port 30303 for this solution.
        c) If your board is connected directly with your computer with a
             crossover cable:
                1) Open a command/DOS prompt and type 'ipconfig'.  Find the
                     network adaptor that is connected to the board.  The IP
                     address of the board is located in the 'Default Gateway'
                    field
                2) Open up the network status for the network adaptor that
                     connects the two devices.  This can be done by right clicking
                     on the network connection icon in the network settings folder
                     and select 'status' from the menu. Find the 'Default Gateway'
                     field.
     3) Open a command/DOS prompt.  Type "telnet ip_address 9760" where
          ip_address is the IP address that you got from step 2.
     4) As you type characters, they will be echoed back in your command prompt
          window in UPPER CASE.
     5) Press Escape to end the demo
*******************************************************************************/

/*******************************************************************************
FileName:  GenericTCPServer.c
Copyright � 2012 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED �AS IS� WITHOUT WARRANTY OF ANY KIND,
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


#include "tcpip_config.h"
#include "main_demo.h"

#if defined(TCPIP_STACK_USE_TCP) && defined(APP_USE_GENERIC_TCP_SERVER_DEMO)

#include "tcpip/tcpip.h"


// Defines which port the server will listen on
#define SERVER_PORT    9760 // Primary port that this server listen on
#define TEST_PORT 443       // Secondary service port (443 = HTTPS port)
#define MAX_DATA  1600
#define BUFFER_SIZE  512

/*****************************************************************************
  Function:
               void GenericTCPServer(void)

  Summary:
               Implements a simple ToUpper TCP Server.

  Description:
               This function implements a simple TCP server.  The function is invoked
               periodically by the stack to listen for incoming connections.  When a
               connection is made, the server reads all incoming data, transforms it
               to uppercase, and echos it back.

               This example can be used as a model for many TCP server applications.

  Precondition:
               TCP is initialized.

  Parameters:
               None

  Returns:
               None
  ***************************************************************************/
void GenericTCPServer(void)
{
        uint8_t AppBuffer[BUFFER_SIZE];
        uint32_t w,w2, wMaxGet, wMaxPut, wCurrentChunk;
        static TCP_SOCKET           MySocket;
        uint32_t i;
#if defined(TCPIP_STACK_USE_SSL_SERVER)
        static SYS_TICK serverTimer;
#endif
          static enum _TCPServerState
          {
           SM_HOME = 0,
                   SM_LISTENING,
#ifdef TCPIP_STACK_USE_SSL_SERVER
                   SM_START_SSL,
#endif
                   SSL_PROCESS_APP_DATA,
                   SM_CLOSING,
               } TCPServerState = SM_HOME;

               switch(TCPServerState)
               {
                    case SM_HOME:
                        // Allocate a socket for this server to listen and accept connections on
                         MySocket = TCPIP_TCP_ServerOpen(IP_ADDRESS_TYPE_IPV4, SERVER_PORT, 0);
                         if(MySocket == INVALID_SOCKET)
                               return;

                          TCPServerState = SM_LISTENING;
                    break;

                    case SM_LISTENING:
#if defined(TCPIP_STACK_USE_SSL_SERVER)
                            TCPIP_TCPSSL_ListenerAdd(MySocket, TEST_PORT);
#endif
                           // See if anyone is connected to us
                           if(!TCPIP_TCP_IsConnected(MySocket))
                                 return;
#if defined(TCPIP_STACK_USE_SSL_SERVER)

                            if(!TCPIP_TCPSSL_ServerStart(MySocket))
                                break;

                            serverTimer = SYS_TICK_Get();
                            TCPServerState = SM_START_SSL;
#else
                            TCPServerState = SSL_PROCESS_APP_DATA;
#endif
                        break;


#if defined(TCPIP_STACK_USE_SSL_SERVER)
                    case SM_START_SSL:

                        if (TCPIP_TCPSSL_StillHandshaking(MySocket))
                        {
                            // Handshaking may fail if the SSL_RSA_CLIENT_SIZE is not large enough
                            // for the server's certificate
                            if(SYS_TICK_Get()-serverTimer > 10*SYS_TICK_TicksPerSecondGet())
                            {
                                 // Close the socket so it can be used by other modules
                                 TCPIP_TCP_Close(MySocket);
                                 MySocket = INVALID_SOCKET;
                                 TCPServerState=SM_HOME;
                             }
                             break;
                         }
                         TCPServerState = SSL_PROCESS_APP_DATA;


                     break;
#endif
                     case SSL_PROCESS_APP_DATA:
			// Figure out how many bytes have been received and how many we can transmit.
			wMaxGet = TCPIP_TCP_GetIsReady(MySocket);	// Get TCP RX FIFO byte count
			wMaxPut = TCPIP_TCP_PutIsReady(MySocket);	// Get TCP TX FIFO free space

			// Make sure we don't take more bytes out of the RX FIFO than we can put into the TX FIFO
			if(wMaxPut < wMaxGet)
				wMaxGet = wMaxPut;

			// Process all bytes that we can
			// This is implemented as a loop, processing up to sizeof(AppBuffer) bytes at a time.
			// This limits memory usage while maximizing performance.  Single byte Gets and Puts are a lot slower than multibyte GetArrays and PutArrays.
			wCurrentChunk = sizeof(AppBuffer);
			for(w = 0; w < wMaxGet; w += sizeof(AppBuffer))
			{
				// Make sure the last chunk, which will likely be smaller than sizeof(AppBuffer), is treated correctly.
				if(w + sizeof(AppBuffer) > wMaxGet)
					wCurrentChunk = wMaxGet - w;

				// Transfer the data out of the TCP RX FIFO and into our local processing buffer.
				TCPIP_TCP_ArrayGet(MySocket, AppBuffer, wCurrentChunk);

				// Perform the "ToUpper" operation on each data byte
				for(w2 = 0; w2 < wCurrentChunk; w2++)
				{
					i = AppBuffer[w2];
					if(i >= 'a' && i <= 'z')
					{
						i -= ('a' - 'A');
						AppBuffer[w2] = i;
					}
                                        else if(i == '\e')   //escape
                                        {
                                            TCPServerState = SM_CLOSING;
                                        }
				}
                                SYS_CONSOLE_MESSAGE((char*)AppBuffer);

				// Transfer the data out of our local processing buffer and into the TCP TX FIFO.
				TCPIP_TCP_ArrayPut(MySocket, AppBuffer, wCurrentChunk);
			}

			// No need to perform any flush.  TCP data in TX FIFO will automatically transmit itself after it accumulates for a while.  If you want to decrease latency (at the expense of wasting network bandwidth on TCP overhead), perform and explicit flush via the TCPIP_TCP_Flush() API.

			break;

                      case SM_CLOSING:
                                             // Close the socket connection.
                        TCPIP_TCP_Close(MySocket);
                        TCPServerState = SM_HOME;
                      break;
               }
}

#endif  // defined(TCPIP_STACK_USE_TCP) && defined(APP_USE_GENERIC_TCP_SERVER_DEMO)

