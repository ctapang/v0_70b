/*******************************************************************************
  NetBIOS Name Service (NBNS) Server

  Summary:
    Module for Microchip TCP/IP Stack
    
  Description:
    -Responds to NBNS name requests to allow human name assignment 
     to the board.  i.e. allows nodes on the same IP subnet to use a 
     hostname to access the board instead of an IP address.
    -Reference: RFC 1002
*******************************************************************************/

/*******************************************************************************
FileName:   NBNS.c
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

#define __NBNS_C

#include "tcpip/src/tcpip_private.h"

#if defined(TCPIP_STACK_USE_NBNS)

#define TCPIP_THIS_MODULE_ID    TCPIP_MODULE_NBNS

// NBNS Header structure
typedef struct _NBNS_HEADER
{
	TCPIP_UINT16_VAL TransactionID;
	TCPIP_UINT16_VAL Flags;
	TCPIP_UINT16_VAL Questions;
	TCPIP_UINT16_VAL Answers;
	TCPIP_UINT16_VAL AuthoritativeRecords;
	TCPIP_UINT16_VAL AdditionalRecords;
} NBNS_HEADER;

static void TCPIP_NBNS_NamePut(UDP_SOCKET s, const char *String);
static void TCPIP_NBNS_NameGet(UDP_SOCKET s, uint8_t *String);

typedef enum
{
    NBNS_HOME = 0,
    NBNS_OPEN_SOCKET,
    NBNS_LISTEN
} TCPIP_NBNS_STAT;

typedef struct
{
    UDP_SOCKET          uSkt;
    TCPIP_NBNS_STAT     sm;
}TCPIP_NBNS_DCPT;


static TCPIP_NBNS_DCPT    nbnsDcpt;
static int                nbnsInitCount = 0;

/*********************************************************************
 * Function:        void TCPIP_NBNS_Initialize(const TCPIP_STACK_MODULE_CTRL* const stackCtrl, const NBNS_MODULE_CONFIG* pNbnsInit)
 *
 * PreCondition:    None
 *
 * Input:           stackCtrl - Interface and stack module data.
 *                  pNbnsInit - Module-specific information for NBNS.
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Initializes state machine
 *
 * Note:            None
 ********************************************************************/
bool TCPIP_NBNS_Initialize(const TCPIP_STACK_MODULE_CTRL* const stackCtrl, const NBNS_MODULE_CONFIG* pNbnsInit)
{

    if(stackCtrl->stackAction == TCPIP_STACK_ACTION_IF_UP)
    {  // interface restart
        return true;
    }
    
    // stack init
    if(nbnsInitCount == 0)
    {   // first time we run
        nbnsDcpt.sm = NBNS_HOME;
        nbnsDcpt.uSkt = INVALID_UDP_SOCKET;
    }
    
    // Reset per interface state machine and flags to default values
	
    nbnsInitCount++;
	return true;
}

/*********************************************************************
 * Function:        void TCPIP_NBNS_Deinitialize(const TCPIP_STACK_MODULE_CTRL* const stackCtrl)
 *
 * PreCondition:    None
 *
 * Input:           stackCtrl - Interface and stack module data.
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        DeInitializes state machine
 *
 * Note:            None
 ********************************************************************/
void TCPIP_NBNS_Deinitialize(const TCPIP_STACK_MODULE_CTRL* const stackCtrl)
{
    // if(stackCtrl->stackAction == TCPIP_STACK_ACTION_DEINIT) // stack shut down
    // if(stackCtrl->stackAction == TCPIP_STACK_ACTION_IF_DOWN) // interface down

    // one way or another this interface is going down

    if(stackCtrl->stackAction == TCPIP_STACK_ACTION_DEINIT)
    {   // whole stack is going down
        if(nbnsInitCount > 0)
        {   // we're up and running
            if(--nbnsInitCount == 0)
            {   // all closed
                // release resources
                if(nbnsDcpt.uSkt != INVALID_UDP_SOCKET)
                {
                   TCPIP_UDP_Close(nbnsDcpt.uSkt);
                   nbnsDcpt.uSkt = INVALID_UDP_SOCKET;
                }
                nbnsDcpt.sm = NBNS_HOME;
            }
        }
    }

}

/*********************************************************************
 * Function:        void TCPIP_NBNS_Task(TCPIP_NET_IF* pNetIf)
 *
 * PreCondition:    None
 *
 * Input:           pNetIf   - interface 
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Sends responses to NetBIOS name requests
 *
 * Note:            None
 ********************************************************************/

bool TCPIP_NBNS_Task(TCPIP_NET_IF* pNetIf)
{
	uint8_t 			i;
	TCPIP_UINT16_VAL    Type, Class;
	NBNS_HEADER			NBNSHeader;
	uint8_t				NameString[16];
    UDP_SOCKET          s;
    int                 nbnsRxSize;
    int                 nbnsTxSize;
    UDP_SOCKET_INFO     sktInfo;

    s = nbnsDcpt.uSkt;

	switch(nbnsDcpt.sm)
    {
        case NBNS_HOME:
            nbnsDcpt.sm++;
            break;

        case NBNS_OPEN_SOCKET:
            s = TCPIP_UDP_ServerOpen(IP_ADDRESS_TYPE_IPV4, NBNS_PORT, 0);
            if(s == INVALID_UDP_SOCKET)
                break;

            if(!TCPIP_UDP_RemoteBind(s, IP_ADDRESS_TYPE_IPV4, NBNS_PORT,  0))
            {
                TCPIP_UDP_Close(s);
                break;
            }

            nbnsDcpt.uSkt = s;
            nbnsDcpt.sm++;

        case NBNS_LISTEN:
            //if(!TCPIP_UDP_GetIsReady(s))
            nbnsRxSize = TCPIP_UDP_GetIsReady(s);
            if(!nbnsRxSize)
            {
                break;
            }


            // Respond only to name requests sent to us from nodes on the same subnet
            // This prevents us from sending out the wrong IP address information if 
            // we haven't gotten a DHCP lease yet.
            TCPIP_UDP_SocketInfoGet(s, &sktInfo);
            if(sktInfo.addressType != IP_ADDRESS_TYPE_IPV4 || 
                    _TCPIPStackIpAddFromAnyNet(pNetIf, &sktInfo.remoteIPaddress.v4Add) == 0)
            {
                TCPIP_UDP_Discard(s);
                break;
            }

            // Retrieve the NBNS header and de-big-endian it
            TCPIP_UDP_Get(s, &NBNSHeader.TransactionID.v[1]);
            TCPIP_UDP_Get(s, &NBNSHeader.TransactionID.v[0]);
            TCPIP_UDP_Get(s, &NBNSHeader.Flags.v[1]);
            TCPIP_UDP_Get(s, &NBNSHeader.Flags.v[0]);
            TCPIP_UDP_Get(s, &NBNSHeader.Questions.v[1]);
            TCPIP_UDP_Get(s, &NBNSHeader.Questions.v[0]);
            TCPIP_UDP_Get(s, &NBNSHeader.Answers.v[1]);
            TCPIP_UDP_Get(s, &NBNSHeader.Answers.v[0]);
            TCPIP_UDP_Get(s, &NBNSHeader.AuthoritativeRecords.v[1]);
            TCPIP_UDP_Get(s, &NBNSHeader.AuthoritativeRecords.v[0]);
            TCPIP_UDP_Get(s, &NBNSHeader.AdditionalRecords.v[1]);
            TCPIP_UDP_Get(s, &NBNSHeader.AdditionalRecords.v[0]);

            // Remove all questions
            while(NBNSHeader.Questions.Val--)
            {
                TCPIP_NBNS_NameGet(s, NameString);
                TCPIP_UDP_Get(s, &i);				// <??> Trailing character on string
                TCPIP_UDP_Get(s, &Type.v[1]);		// Question type
                TCPIP_UDP_Get(s, &Type.v[0]);
                TCPIP_UDP_Get(s, &Class.v[1]);	// Question class
                TCPIP_UDP_Get(s, &Class.v[0]);

                if(Type.Val == 0x0020u && Class.Val == 0x0001u)
                {
                    int nIfs, nIx;
                    TCPIP_NET_IF*   pIf;
                    const char*     netbName;

                    nIfs = TCPIP_STACK_NumberOfNetworksGet();
                    for(nIx = 0; nIx < nIfs; nIx++)
                    { 
                        pIf = (TCPIP_NET_IF*)TCPIP_STACK_IndexToNet(nIx); 
                        netbName = TCPIP_STACK_NetBIOSName(pIf);    // this checks the IF is up!
                        if(netbName != 0 && memcmp((void*)NameString, netbName, sizeof(pIf->NetBIOSName)) == 0)
                        {   // one of our interfaces has this name
                            nbnsTxSize = TCPIP_UDP_TxPutIsReady(s, 64);
                            if(nbnsTxSize)
                            {   

                                NBNSHeader.Flags.Val = 0x8400;

                                TCPIP_UDP_Put(s, NBNSHeader.TransactionID.v[1]);
                                TCPIP_UDP_Put(s, NBNSHeader.TransactionID.v[0]);
                                TCPIP_UDP_Put(s, NBNSHeader.Flags.v[1]);
                                TCPIP_UDP_Put(s, NBNSHeader.Flags.v[0]);
                                TCPIP_UDP_Put(s, 0x00);	// 0x0000 Questions
                                TCPIP_UDP_Put(s, 0x00);
                                TCPIP_UDP_Put(s, 0x00);	// 0x0001 Answers
                                TCPIP_UDP_Put(s, 0x01);
                                TCPIP_UDP_Put(s, 0x00);	// 0x0000 Athoritative records
                                TCPIP_UDP_Put(s, 0x00);
                                TCPIP_UDP_Put(s, 0x00);	// 0x0000 Additional records
                                TCPIP_UDP_Put(s, 0x00);

                                TCPIP_NBNS_NamePut(s, netbName);
                                TCPIP_UDP_Put(s, 0x00);	// 0x0020 Type: NetBIOS
                                TCPIP_UDP_Put(s, 0x20);
                                TCPIP_UDP_Put(s, 0x00);	// 0x0001 Class: Internet
                                TCPIP_UDP_Put(s, 0x01);
                                TCPIP_UDP_Put(s, 0x00);	// 0x00000000 Time To Live
                                TCPIP_UDP_Put(s, 0x00);
                                TCPIP_UDP_Put(s, 0x00);
                                TCPIP_UDP_Put(s, 0x00);

                                TCPIP_UDP_Put(s, 0x00);	// 0x0006 Data length
                                TCPIP_UDP_Put(s, 0x06);	
                                TCPIP_UDP_Put(s, 0x60);	// 0x6000 Flags: H-node, Unique
                                TCPIP_UDP_Put(s, 0x00);
                                TCPIP_UDP_Put(s, pIf->netIPAddr.v[0]);	// Put out IP address
                                TCPIP_UDP_Put(s, pIf->netIPAddr.v[1]);
                                TCPIP_UDP_Put(s, pIf->netIPAddr.v[2]);
                                TCPIP_UDP_Put(s, pIf->netIPAddr.v[3]);

                                // Change the destination address to the unicast address of the last received packet
                                TCPIP_UDP_SocketInfoGet(s, &sktInfo);
                                TCPIP_UDP_DestinationIPAddressSet(s, sktInfo.addressType, &sktInfo.remoteIPaddress);
                                TCPIP_UDP_Flush(s);				
                            }
                            break;
                        }
                    }
                }
            }

            TCPIP_UDP_Discard(s);

            break;
    }

    return true;
}

/*********************************************************************
 * Function:        static void TCPIP_NBNS_NamePut (UDP_SOCKET s, const char *String)
 *
 * PreCondition:    None
 *
 * Input:           String: The name to transmit
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Transmits the NetBIOS name across an open UDP
 *                  socket.
 *
 * Note:            None
 ********************************************************************/
static void TCPIP_NBNS_NamePut(UDP_SOCKET s, const char *String)
{
	uint8_t i, j;

	TCPIP_UDP_Put(s, 32);	// NetBIOS names are always 32 bytes long (16 decoded bytes)
	for(i = 0; i < 16u; i++)
	{
		j = *String++;
		TCPIP_UDP_Put(s, (j>>4) + 'A');
		TCPIP_UDP_Put(s, (j & 0x0F) + 'A');
	}
	
	TCPIP_UDP_Put(s, 0x00);
}

/*********************************************************************
 * Function:        static void TCPIP_NBNS_NameGet (UDP_SOCKET s, uint8_t *String)
 *
 * PreCondition:    None
 *
 * Input:           String: Pointer to an array into which
 *                  a received NetBIOS name should be copied.
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Reads the NetBIOS name from a UDP socket and
 *                  copies it into a user-specified buffer.
 *
 * Note:            None
 ********************************************************************/
static void TCPIP_NBNS_NameGet(UDP_SOCKET s, uint8_t *String)
{
	uint8_t i, j, k;

	if(String == NULL)
	{
		TCPIP_UDP_Get(s, &i);
		while(i--)
		{
			TCPIP_UDP_Get(s, &j);
		}
	}
	else
	{
		TCPIP_UDP_Get(s, &i);
		if(i != 32u)
		{
			*String = 0;
			return;
		}
		while(i--)
		{
			TCPIP_UDP_Get(s, &j);
			j -= 'A';
			k = j<<4;
			i--;
			TCPIP_UDP_Get(s, &j);
			j -= 'A';
			*String++ = k | j;
		}
	}
}


#endif //#if defined(TCPIP_STACK_USE_NBNS)
