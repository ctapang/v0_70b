/*******************************************************************************
  TCPIP network packet manager implementation

  Summary:
    
  Description:
*******************************************************************************/

/*******************************************************************************
FileName:  tcpip_packet.c 
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
#include <sys/kmem.h>

#include "tcpip_private.h"
#include "tcpip_packet.h"

#define TCPIP_THIS_MODULE_ID    TCPIP_MODULE_PACKET_MANAGER

/*  TCPIP MAC Frame Offset

  Summary:
    An offset from a 4 byte aligned address where the MAC frame should start

  Description:
    Offset used on 32 bit machines that allows alignment of the network layer data.
    This allows improved efficiency for checksum calculations, etc.
  
  Remarks:
    Usual value is 2.

    See notes for the TCPIP_MAC_DATA_SEGMENT.segLoadOffset member.

*/

#if defined(TCPIP_IF_MRF24W)
    #define TCPIP_MAC_FRAME_OFFSET      6  // aligns ethernet packet and allows room for MRF 4-byte internal header
#else
    #define TCPIP_MAC_FRAME_OFFSET      2
#endif

static TCPIP_HEAP_HANDLE    pktMemH = 0;
static bool                 pktK0Heap = 0;

// API

bool TCPIP_PKT_Initialize(TCPIP_HEAP_HANDLE heapH)
{
    pktMemH = 0;

    while(heapH != 0)
    {
        TCPIP_MAC_PACKET* allocPtr;

        allocPtr = (TCPIP_MAC_PACKET*)TCPIP_HEAP_Malloc(heapH, sizeof(TCPIP_MAC_PACKET));

        if(allocPtr == 0)
        {
            break;
        }

        TCPIP_HEAP_Free(heapH, allocPtr);
        if(!IS_KVA(allocPtr))
        {   // only kernel space buffers accepted
            break;
        }
        // success
        pktK0Heap = IS_KVA0(allocPtr);
        pktMemH = heapH;

        break;
    }


    return pktMemH != 0;
    
}

void TCPIP_PKT_Deinitialize(void)
{
    pktMemH = 0;
}


// allocates a socket packet
TCPIP_MAC_PACKET*  TCPIP_PKT_SocketAlloc(uint16_t pktLen, uint16_t transpHdrLen, uint16_t payloadLen, TCPIP_MAC_PACKET_FLAGS flags)
{
    uint16_t          netHdrLen, totHdrLen;
    TCPIP_MAC_PACKET* pPkt;

    if((flags & TCPIP_MAC_PKT_FLAG_IPV6) != 0)
    {
        netHdrLen = sizeof(IPV6_HEADER);
    }
    else
    {
        netHdrLen = sizeof(IPV4_HEADER);
    }


    totHdrLen = netHdrLen + transpHdrLen;

    pPkt = TCPIP_PKT_PacketAlloc(pktLen, totHdrLen +  payloadLen, flags );

    if(pPkt)
    {   // set the layer pointers in place
        if(transpHdrLen)
        {
            pPkt->pTransportLayer = pPkt->pNetLayer + netHdrLen;
        }
    }

    return pPkt;
}


TCPIP_MAC_PACKET* TCPIP_PKT_PacketAlloc(uint16_t pktLen, uint16_t segLoadLen, TCPIP_MAC_PACKET_FLAGS flags)
{
    TCPIP_MAC_PACKET* pPkt;
    TCPIP_MAC_DATA_SEGMENT  *pSeg;
    uint16_t        pktUpLen, allocLen;

    if(pktLen < sizeof(TCPIP_MAC_PACKET))
    {
        pktLen = sizeof(TCPIP_MAC_PACKET);
    }

    pktUpLen = (((pktLen + 3) >> 2) << 2);     // 32 bits round up

    allocLen = pktUpLen + sizeof(*pSeg) + segLoadLen + sizeof(TCPIP_MAC_ETHERNET_HEADER) + TCPIP_MAC_FRAME_OFFSET;

    pPkt = (TCPIP_MAC_PACKET*)TCPIP_HEAP_Malloc(pktMemH, allocLen);

    if(pPkt)
    {   
        // clear the TCPIP_MAC_PACKET and 1st segment fields
        // populate the 1st segment
        memset(pPkt, 0, pktUpLen + sizeof(*pSeg));
        pSeg = (TCPIP_MAC_DATA_SEGMENT*)((uint8_t*)pPkt + pktUpLen);

        pSeg->segSize = segLoadLen + sizeof(TCPIP_MAC_ETHERNET_HEADER);
        pSeg->segLoadOffset = TCPIP_MAC_FRAME_OFFSET;
        pSeg->segLoad = (uint8_t*)(pSeg + 1) + TCPIP_MAC_FRAME_OFFSET;
        pSeg->segFlags = TCPIP_MAC_SEG_FLAG_STATIC; // embedded in TCPIP_MAC_PACKET itself
        pPkt->pDSeg = pSeg;

        pPkt->pMacLayer = pSeg->segLoad;
        pPkt->pktFlags = flags & (~TCPIP_MAC_PKT_FLAG_STATIC);  // this packet is dynamically allocated
        if(segLoadLen)
        {
            pPkt->pNetLayer = pPkt->pMacLayer + sizeof(TCPIP_MAC_ETHERNET_HEADER);
        }

        if(pktK0Heap)
        {
            pPkt = (TCPIP_MAC_PACKET*)KVA0_TO_KVA1(pPkt);
        }
    }

    return pPkt;


}

// acknowledges a packet
void TCPIP_PKT_PacketAcknowledge(TCPIP_MAC_PACKET* pPkt, TCPIP_MAC_PKT_ACK_RES ackRes)
{
    if(ackRes != TCPIP_MAC_PKT_ACK_NONE)
    {
        pPkt->ackRes = ackRes;
    }

    if(pPkt->ackFunc)
    {
       (*pPkt->ackFunc)(pPkt, pPkt->ackParam);
        pPkt->pktFlags &= ~TCPIP_MAC_PKT_FLAG_QUEUED;
    }
    else
    {
        SYS_ERROR(SYS_ERROR_WARN, "Packet Ack: orphan packet! \r\n");
    }
}

// frees a previously allocated packet
void TCPIP_PKT_PacketFree(TCPIP_MAC_PACKET* pPkt)
{

    if((pPkt->pktFlags & TCPIP_MAC_PKT_FLAG_STATIC) == 0)
    {   // we don't deallocate static packets
        TCPIP_MAC_DATA_SEGMENT  *pSeg, *pNSeg;

        for(pSeg = pPkt->pDSeg; pSeg != 0 ; )
        {
            pNSeg = pSeg->next;
            if((pSeg->segFlags & TCPIP_MAC_SEG_FLAG_STATIC) == 0)
            {
                if(pktK0Heap)
                {
                    pSeg = (TCPIP_MAC_DATA_SEGMENT*)KVA1_TO_KVA0(pSeg);
                }
                TCPIP_HEAP_Free(pktMemH, pSeg);
            }
            pSeg = pNSeg;
        }

        if(pktK0Heap)
        {
            pPkt = (TCPIP_MAC_PACKET*)KVA1_TO_KVA0(pPkt);
        }
        TCPIP_HEAP_Free(pktMemH, pPkt);
    }
}

TCPIP_MAC_DATA_SEGMENT* TCPIP_PKT_SegmentAlloc(uint16_t loadLen, uint16_t loadOffset, TCPIP_MAC_SEGMENT_FLAGS flags)
{
    TCPIP_MAC_DATA_SEGMENT* pSeg;
    uint16_t allocSize;

    if(loadLen != 0)
    {
        allocSize = sizeof(*pSeg) + loadLen + loadOffset;
    }
    else
    {
        allocSize = sizeof(*pSeg);
    }

    pSeg = (TCPIP_MAC_DATA_SEGMENT*)TCPIP_HEAP_Malloc(pktMemH, allocSize);

    if(pSeg)
    {
        memset(pSeg, 0, sizeof(*pSeg));

        pSeg->segFlags = flags & (~TCPIP_MAC_SEG_FLAG_STATIC);
        if(loadLen != 0)
        {
            pSeg->segSize = loadLen;
            pSeg->segLoadOffset = loadOffset;
            pSeg->segLoad = (uint8_t*)(pSeg + 1) + loadOffset;
        }

        if(pktK0Heap)
        {
            pSeg = (TCPIP_MAC_DATA_SEGMENT*)KVA0_TO_KVA1(pSeg);
        }
        
    }

    return pSeg;
}

void TCPIP_PKT_SegmentAppend(TCPIP_MAC_PACKET* pPkt, TCPIP_MAC_DATA_SEGMENT* pSeg)
{
    TCPIP_MAC_DATA_SEGMENT  *pN, *prev;

    if((pN = pPkt->pDSeg) == 0)
    {   // insert as root
        pPkt->pDSeg = pSeg;
    }
    else
    {   // traverse the list
        for(prev = 0; pN != 0; prev = pN, pN = pN->next);
        prev->next = pSeg;
    }

}


void TCPIP_PKT_SegmentFree(TCPIP_MAC_DATA_SEGMENT* pSeg)
{
    if( (pSeg->segFlags & TCPIP_MAC_SEG_FLAG_STATIC) == 0)
    {
        if(pktK0Heap)
        {
            pSeg = (TCPIP_MAC_DATA_SEGMENT*)KVA1_TO_KVA0(pSeg);
        }
        TCPIP_HEAP_Free(pktMemH, pSeg);
    }

}

// helpers

bool TCPIP_PKT_PacketMACFormat(TCPIP_MAC_PACKET* pPkt, const TCPIP_MAC_ADDR* dstAddr, const TCPIP_MAC_ADDR* srcAddr, uint16_t pktType)
{
    if(srcAddr)
    {
        TCPIP_MAC_ETHERNET_HEADER* macHdr;
        TCPIP_MAC_ADDR    *destHdrAdd, *srcHdrAdd;

        macHdr = (TCPIP_MAC_ETHERNET_HEADER*)pPkt->pMacLayer;
        srcHdrAdd = &macHdr->SourceMACAddr;

        if(dstAddr)
        {
            destHdrAdd = &macHdr->DestMACAddr;
            memcpy(destHdrAdd, dstAddr, sizeof(*destHdrAdd));
        }

        memcpy(srcHdrAdd, srcAddr, sizeof(*srcHdrAdd));
        // set the MAC frame type
        macHdr->Type = TCPIP_Helper_htons(pktType);

        // update the frame length
        pPkt->pDSeg->segLen += sizeof(TCPIP_MAC_ETHERNET_HEADER);
        return true;
    }

    return false;
}

// returns the segment to which dataAddress belongs
// 0 if not in this packet
TCPIP_MAC_DATA_SEGMENT* TCPIP_PKT_DataSegmentGet(TCPIP_MAC_PACKET* pPkt, uint8_t* dataAddress, bool srchTransport)
{
    TCPIP_MAC_DATA_SEGMENT  *pStartSeg, *pSeg;

    pStartSeg = 0;

    if(srchTransport)
    {   // search the segment containing the transport data
        for(pSeg = pPkt->pDSeg; pSeg != 0; pSeg = pSeg->next)
        {
            if(pSeg->segLoad <= pPkt->pTransportLayer && pPkt->pTransportLayer <= pSeg->segLoad + pSeg->segSize)
            {   // found segment containing the beg of the transport
                if(pPkt->pTransportLayer <= dataAddress && dataAddress <= pSeg->segLoad + pSeg->segSize)
                {
                    return pSeg;
                }

                pStartSeg = pSeg->next;
                break;
            }
        }
    }
    else
    {
        pStartSeg = pPkt->pDSeg;
    }


    for(pSeg = pStartSeg; pSeg != 0; pSeg = pSeg->next)
    {
        if(pSeg->segLoad <= dataAddress && dataAddress <= pSeg->segLoad + pSeg->segSize)
        {
            return pSeg;
        }
    }

    return 0;
}

