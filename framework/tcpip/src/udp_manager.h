/*******************************************************************************
  UDP Module manager - private stack API

  Summary:
    
  Description:
*******************************************************************************/

/*******************************************************************************
FileName:  udp_manager.h 
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

#ifndef __UDP__MANAGER_H_
#define __UDP__MANAGER_H_


bool TCPIP_UDP_Initialize(const TCPIP_STACK_MODULE_CTRL* const stackInit, const UDP_MODULE_CONFIG* pUdpInit);
void TCPIP_UDP_Deinitialize(const TCPIP_STACK_MODULE_CTRL* const stackInit);

void TCPIP_UDP_ProcessIPv4(TCPIP_NET_IF* pNetIf, TCPIP_MAC_PACKET* pRxPkt);
void TCPIP_UDP_ProcessIPv6(TCPIP_MAC_PACKET* pRxPkt, IPV6_ADDR * localIP, IPV6_ADDR * remoteIP, uint16_t dataLen, uint16_t headerLen);


// BSD sockets support
typedef enum
{
    UDP_OPEN_SERVER         = 0x01,        // create a server socket
    UDP_OPEN_CLIENT         = 0x02,        // create a client socket
    // extra creation flags
    UDP_OPEN_TX_SPLIT       = 0x80,        // create a ZC BSD socket, the payload is external
                                           // No PUT operations available for this socket
    UDP_OPEN_CONFIG_SERVICE = 0x100,       // the owner of this socket is a stack confuguration service

}UDP_OPEN_TYPE;

// Stores the header of a UDP packet
typedef struct
{
    UDP_PORT    SourcePort;				// Source UDP port
    UDP_PORT    DestinationPort;		// Destination UDP port
    uint16_t    Length;					// Length of data
    uint16_t    Checksum;				// UDP checksum of the data
} UDP_HEADER;


UDP_SOCKET UDPOpenServerSkt(IP_ADDRESS_TYPE addType, UDP_PORT localPort,  IP_MULTI_ADDRESS* localAddress, UDP_OPEN_TYPE opType);


UDP_SOCKET UDPOpenClientSkt(IP_ADDRESS_TYPE addType, UDP_PORT remotePort, IP_MULTI_ADDRESS* remoteAddress, UDP_OPEN_TYPE opType);



// sets the payload for a TX_SPLIT/BSD created socket
bool UDPSetSplitPayload(UDP_SOCKET s, void* pLoad, uint16_t loadSize);


#endif // __UDP__MANAGER_H_


