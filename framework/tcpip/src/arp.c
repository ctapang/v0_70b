/*******************************************************************************
  Address Resolution Protocol (ARP) Client and Server

  Summary:
    ARP implementation file
    
  Description:
    This source file contains the functions and storage of the 
    ARP routines
    
    Provides IP address to Ethernet MAC address translation
    Reference: RFC 826
*******************************************************************************/

/*******************************************************************************
FileName:   arp.c
Copyright � 2011 released Microchip Technology Inc.  All rights
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


#include "tcpip/src/tcpip_private.h"
#include "tcpip/src/arp_private.h"
#include "tcpip/src/hash_fnv.h"
#include "tcpip/tcpip_helpers.h"


#define TCPIP_THIS_MODULE_ID    TCPIP_MODULE_ARP
#include "tcpip/src/tcpip_notify.h"


/****************************************************************************
  Section:
    Constants and Variables
  ***************************************************************************/

// global ARP module descriptor
typedef struct
{
    int                 nIfs;                // number of interfaces ARP running on
    ARP_CACHE_DCPT*     arpCacheDcpt;        // ARP caches per interface
    const void*         memH;                // memory allocation handle
    int                 initCount;           // ARP module initialization count
    bool                deleteOld;           // if 0 and old cache still in place don't re-initialize it

    uint32_t            timeSeconds;         // coarse ARP time keeping, seconds
    tcpipAsyncHandle      timerHandle;

    SINGLE_LIST         registeredUsers;     // notification users
    // timing
    uint32_t            entrySolvedTmo;      // solved entry removed after this tmo
                                             // if not referenced - seconds
    uint32_t            entryPendingTmo;     // timeout for a pending to be solved entry in the cache, in seconds
    uint32_t            entryRetryTmo;       // timeout for resending an ARP request for a pending entry - seconds
                                             // 1 sec < tmo < entryPendingTmo
    int                 permQuota;           // max percentage of permanent entries allowed in the cache - %                            
    TCPIP_MAC_PACKET*   pMacPkt;             // packet that we use to send requests ARP requests
                                             // only ONE packet is used for now even if there are multiple interfaces!!!
}ARP_MODULE_DCPT;


// the module descriptor
static ARP_MODULE_DCPT arpMod = { 0 };


static TCPIP_MAC_ADDR             arpBcastAdd = { {0xff, 0xff, 0xff, 0xff, 0xff, 0xff} };

#ifdef TCPIP_STACK_USE_ZEROCONF_LINK_LOCAL
#define MAX_REG_APPS            2           // MAX num allowed registrations of Modules/Apps
static struct arp_app_callbacks reg_apps[MAX_REG_APPS]; // Call-Backs storage for MAX of two Modules/Apps

#endif

// the default initialization data
static const ARP_MODULE_CONFIG arpConfigDefault = 
{
	ARP_CACHE_ENTRIES_DEFAULT,
	true,
    ARP_CACHE_SOLVED_ENTRY_TMO,
    ARP_CACHE_PENDING_ENTRY_TMO,
    ARP_CACHE_PENDING_RETRY_TMO,
    ARP_CACHE_PERMANENT_QUOTA,
    ARP_CACHE_PURGE_THRESHOLD,
    ARP_CACHE_PURGE_QUANTA,
};


/****************************************************************************
  Section:
    Helper Function Prototypes
  ***************************************************************************/

static bool         _ARPSendIfPkt(TCPIP_NET_IF* pIf, TCPIP_ARP_OPERATION_TYPE oper, uint32_t srcIP, uint32_t dstIP, TCPIP_MAC_ADDR* dstMAC);

#ifdef TCPIP_STACK_USE_ZEROCONF_LINK_LOCAL
static void         _ARPProcessRxPkt(TCPIP_NET_IF* pIf, ARP_PACKET* packet);
#endif

static void         _SwapARPPacket(ARP_PACKET* p);

static void         _ARPUpdateEntry(TCPIP_NET_IF* pIf, ARP_HASH_ENTRY* arpHE, TCPIP_MAC_ADDR* hwAdd);
static TCPIP_ARP_RESULT   _ARPAddCompleteEntry(TCPIP_NET_IF* pIf, IPV4_ADDR* pIPAddr, TCPIP_MAC_ADDR* hwAdd);
    
static void         _ARPDeleteCache(ARP_CACHE_DCPT* pArpDcpt);
static void         _ARPDeleteClients(void);
static void         _ARPDeleteResources(void);

static void         _ARPNotifyClients(TCPIP_NET_IF* pNetIf, const IPV4_ADDR* ipAdd, const TCPIP_MAC_ADDR* MACAddr, TCPIP_ARP_EVENT_TYPE evType);

static TCPIP_ARP_RESULT   _ARPProbeAddress(TCPIP_NET_IF* pIf, IPV4_ADDR* IPAddr, IPV4_ADDR* srcAddr, TCPIP_ARP_OPERATION_TYPE opType, TCPIP_MAC_ADDR* pHwAdd);

static TCPIP_MAC_PACKET* _ARPAllocateTxPacket(void);

static void         _ARPTxAckFnc (TCPIP_MAC_PACKET * pPkt, const void * param);


#if defined( OA_HASH_DYNAMIC_KEY_MANIPULATION )
size_t TCPIP_ARP_HashKeyHash(OA_HASH_DCPT* pOH, void* key);
#if defined(OA_DOUBLE_HASH_PROBING)
size_t TCPIP_ARP_HashProbeHash(OA_HASH_DCPT* pOH, void* key);
#endif  // defined(OA_DOUBLE_HASH_PROBING)
OA_HASH_ENTRY* TCPIP_ARP_HashEntryDelete(OA_HASH_DCPT* pOH);
int TCPIP_ARP_HashKeyCompare(OA_HASH_DCPT* pOH, OA_HASH_ENTRY* hEntry, void* key);
void TCPIP_ARP_HashKeyCopy(OA_HASH_DCPT* pOH, OA_HASH_ENTRY* dstEntry, void* key);
#endif  // defined ( OA_HASH_DYNAMIC_KEY_MANIPULATION )

/*static __inline__*/static  void /*__attribute__((always_inline))*/ _ARPSetEntry(ARP_HASH_ENTRY* arpHE, ARP_ENTRY_FLAGS newFlags,
                                                                      TCPIP_MAC_ADDR* hwAdd, SINGLE_LIST* addList)
{
    arpHE->hEntry.flags.value &= ~ARP_FLAG_ENTRY_VALID_MASK;
    arpHE->hEntry.flags.value |= newFlags;
    
    if(hwAdd)
    {
        arpHE->hwAdd = *hwAdd;
    }
    
    arpHE->tInsert = arpMod.timeSeconds;
    arpHE->nRetries = 1;
    if(addList)
    {
        TCPIP_Helper_SingleListTailAdd(addList, (SGL_LIST_NODE*)&arpHE->next);
    }
}


// re-inserts at the tail, makes the entry fresh
/*static __inline__*/static  void /*__attribute__((always_inline))*/ _ARPRefreshEntry(ARP_HASH_ENTRY* arpHE, SINGLE_LIST* pL)
{
    TCPIP_Helper_SingleListNodeRemove(pL, (SGL_LIST_NODE*)&arpHE->next);
    arpHE->tInsert = arpMod.timeSeconds;
    TCPIP_Helper_SingleListTailAdd(pL, (SGL_LIST_NODE*)&arpHE->next);
}

/*static __inline__*/static  void /*__attribute__((always_inline))*/ _ARPRemoveCacheEntries(ARP_CACHE_DCPT* pArpDcpt)
{

    if(pArpDcpt->hashDcpt)
    {
        TCPIP_OAHASH_EntriesRemoveAll(pArpDcpt->hashDcpt);
        SingleListDelete(&pArpDcpt->incompleteList);
        SingleListDelete(&pArpDcpt->completeList);
        SingleListDelete(&pArpDcpt->permList);
    }
}

static  void _ARPRemoveEntry(ARP_CACHE_DCPT* pArpDcpt, OA_HASH_ENTRY* hE)
{
    SINGLE_LIST     *remList;

    if((hE->flags.value & ARP_FLAG_ENTRY_PERM) != 0 )
    {
        remList =  &pArpDcpt->permList;
    }
    else if((hE->flags.value & ARP_FLAG_ENTRY_COMPLETE) != 0 )
    {
        remList =  &pArpDcpt->completeList;
    }
    else
    {
        remList =  &pArpDcpt->incompleteList;
    }

    TCPIP_Helper_SingleListNodeRemove(remList, (SGL_LIST_NODE*)&((ARP_HASH_ENTRY*)hE)->next);     

    TCPIP_OAHASH_EntryRemove(pArpDcpt->hashDcpt, hE);

}

/****************************************************************************
  Section:
    Function Implementations
  ***************************************************************************/
#ifdef TCPIP_STACK_USE_ZEROCONF_LINK_LOCAL
/************ User Application APIs ****************************************/

/*****************************************************************************
  Function:
    int8_t TCPIP_ARP_CallbacksRegister(struct arp_app_callbacks *app)

  Summary:
    Registering callback with ARP module to get notified about certian events.
    
  Description:
    This function allows end user application to register with callbacks, which
    will be called by ARP module to give notification to user-application about 
    events occurred at ARP layer. For ex: when a ARP-packet is received, which is
    conflicting with our own pair of addresses (MAC-Address and IP-address).
    This is an extension for zeroconf protocol implementation (ZeroconfLL.c)

  Precondition:
    None

  Parameters:
    app - ARP-Application callbacks structure supplied by user-application 
    
  Returns:
    id > 0 - Returns non-negative value that represents the id of registration
             The same id needs to be used in de-registration
    -1     - When registered applications exceed MAX_REG_APPS and there is no
             free slot for registration
 
  ***************************************************************************/
int8_t TCPIP_ARP_CallbacksRegister(struct arp_app_callbacks *app)
{
    uint8_t i;
    for(i=0; i<MAX_REG_APPS; i++)
    {
        if(!reg_apps[i].used)
        {
            reg_apps[i].TCPIP_ARP_PacketNotify = app->TCPIP_ARP_PacketNotify;
            reg_apps[i].used = 1;
            return (i+1); // Return Code. Should be used in deregister.
        }
    }
    return -1; // No space for registration
}

/*****************************************************************************
  Function:
    bool TCPIP_ARP_CallbacksDeregister(int8_t reg_id)

  Summary:
    De-Registering callbacks with ARP module that are registered previously.
    
  Description:
    This function allows end user-application to de-register with callbacks, 
    which were registered previously.
    This is called by user-application, when its no longer interested in 
    notifications from ARP-Module. This allows the other application to get 
    registered with ARP-module.   

  Precondition:
    None

  Parameters:
    reg_id - Registration-id returned in TCPIP_ARP_CallbacksRegister call
    
  Returns:
    true  - On success
    false - Failure to indicate invalid reg_id  
  ***************************************************************************/ 
bool TCPIP_ARP_CallbacksDeregister(int8_t reg_id)
{
    if(reg_id <= 0 || reg_id > MAX_REG_APPS)
        return false;

    reg_apps[reg_id-1].used = 0; // To indicate free slot for registration
    return true;
}


/*****************************************************************************
  Function:
    void _ARPProcessRxPkt(TCPIP_NET_IF* pIf, ARP_PACKET* packet)

  Summary:
    Processes Received-ARP packet (ARP request/Reply).
    
  Description:
    This function is to pass-on the ARP-packet to registered application,
    with the notification of Rx-ARP packet. 

  Precondition:
    ARP packet is received completely from MAC

  Parameters:
    pIf   - interface to use 
    packet - Rx packet to be processed     

  Returns:
    None   
  ***************************************************************************/
static void _ARPProcessRxPkt(TCPIP_NET_IF* pIf, ARP_PACKET* packet)
{
    uint8_t pass_on = 0; // Flag to indicate whether need to be forwarded
    uint8_t i;

    // Probing Stage
    if(pIf->netIPAddr.Val == 0x00)
    {
        pass_on = 1; // Pass to Registered-Application for further processing        
    }
    else if(pIf->netIPAddr.Val)
    {
        /* Late-conflict */
        if(packet->SenderIPAddr.Val == pIf->netIPAddr.Val)
        {
            pass_on = 1;
        }
    }
    if(pass_on)
    {
    
        for(i =0; i< MAX_REG_APPS; i++)
        {
            if(reg_apps[i].used)
            {
                reg_apps[i].TCPIP_ARP_PacketNotify(pIf,
				packet->SenderIPAddr.Val,
                                packet->TargetIPAddr.Val,
                                &packet->SenderMACAddr,
                                &packet->TargetMACAddr,
                                packet->Operation);                
            }
        }
    }
}

#endif  // TCPIP_STACK_USE_ZEROCONF_LINK_LOCAL


/*****************************************************************************
  Function:
    static bool _ARPSendIfPkt(TCPIP_NET_IF* pIf, TCPIP_ARP_OPERATION_TYPE oper, uint32_t srcIP, uint32_t dstIP, TCPIP_MAC_ADDR* dstMAC)

  Description:
    Writes an ARP packet to the MAC using the interface pointer for src IP and MAC address.

  Precondition:
    None

  Parameters:

  Return Values:
    true - The ARP packet was generated properly
    false - otherwise

  ***************************************************************************/
static bool _ARPSendIfPkt(TCPIP_NET_IF* pIf, TCPIP_ARP_OPERATION_TYPE oper, uint32_t srcIP, uint32_t dstIP, TCPIP_MAC_ADDR* dstMAC)
{
    TCPIP_MAC_PACKET* pMacPkt;
    ARP_PACKET*       pArp;
    TCPIP_MAC_HANDLE hMac;

    if(arpMod.pMacPkt != 0 && (arpMod.pMacPkt->pktFlags & TCPIP_MAC_PKT_FLAG_QUEUED) == 0)
    {
        pMacPkt = arpMod.pMacPkt;
    }
    else
    {   // packet not available, have to allocate another one
        if((pMacPkt = _ARPAllocateTxPacket()) == 0)
        {
            return false;
        }
        arpMod.pMacPkt = pMacPkt;   // show we're using this one now
    }


    pArp = (ARP_PACKET*)pMacPkt->pNetLayer;

    pArp->HardwareType  = HW_ETHERNET;
    pArp->Protocol      = ARP_IP;
    pArp->MACAddrLen    = sizeof(TCPIP_MAC_ADDR);
    pArp->ProtocolLen   = sizeof(IPV4_ADDR);
    pArp->Operation = oper;

    pArp->SenderMACAddr = pIf->netMACAddr;
    pArp->SenderIPAddr.Val  = srcIP;
    pArp->TargetMACAddr = *dstMAC;
    pArp->TargetIPAddr.Val  = dstIP;

    _SwapARPPacket(pArp);

    // format the MAC packet
    pMacPkt->pDSeg->segLen = sizeof(ARP_PACKET);
    if(TCPIP_PKT_PacketMACFormat(pMacPkt, dstMAC, (const TCPIP_MAC_ADDR*)TCPIP_STACK_NetMACAddressGet(pIf), ETHERTYPE_ARP))
    {
        pMacPkt->next = 0;  // send single packet
        hMac = TCPIP_STACK_NetToMAC(pIf);
        if(TCPIP_MAC_PacketTx(hMac, pMacPkt) >= 0)
        {   // MAC sets itself the TCPIP_MAC_PKT_FLAG_QUEUED
            return true;
        }
    }

    // something failed
    return false;
}

/*****************************************************************************
  Function:
    static void _ARPUpdateEntry(TCPIP_NET_IF* pIf, ARP_HASH_ENTRY* arpHE, TCPIP_MAC_ADDR* hwAdd)

  Description:
    Updates the info for an existing ARP cache entry

  Precondition:
    None

  Parameters:
    pIf             - interface
    arpHE           - particular cache entry to be updated
    hwAdd           - the (new) hardware address

  Return Values:
    None
  ***************************************************************************/
static void _ARPUpdateEntry(TCPIP_NET_IF* pIf, ARP_HASH_ENTRY* arpHE, TCPIP_MAC_ADDR* hwAdd)
{
    TCPIP_ARP_EVENT_TYPE evType; 
    ARP_CACHE_DCPT  *pArpDcpt;
    
    pArpDcpt = arpMod.arpCacheDcpt + TCPIP_STACK_NetIxGet(pIf);
    if((arpHE->hEntry.flags.value & ARP_FLAG_ENTRY_PERM) == 0)
    {   

        if((arpHE->hEntry.flags.value & ARP_FLAG_ENTRY_COMPLETE) == 0)
        {   // was waiting for this one, it was queued
            evType = ARP_EVENT_SOLVED;
            TCPIP_Helper_SingleListNodeRemove(&pArpDcpt->incompleteList, (SGL_LIST_NODE*)&arpHE->next);
        }
        else
        {   // completed entry, but now updated
            evType = ARP_EVENT_UPDATED;
            TCPIP_Helper_SingleListNodeRemove(&pArpDcpt->completeList, (SGL_LIST_NODE*)&arpHE->next);
        }
        
        // move to tail, updated
        _ARPSetEntry(arpHE, ARP_FLAG_ENTRY_COMPLETE, hwAdd, &pArpDcpt->completeList);
    }
    else
    {   // permanent entries are not updated
        evType = ARP_EVENT_PERM_UPDATE;
    }

    _ARPNotifyClients(pIf, &arpHE->ipAddress, &arpHE->hwAdd, evType);

}


/*****************************************************************************
  Function:
    static TCPIP_ARP_RESULT _ARPAddCompleteEntry(TCPIP_NET_IF* pIf, IPV4_ADDR* pIPAddr, TCPIP_MAC_ADDR* hwAdd)

  Description:
    Updates the info for an existing ARP cache entry

  Precondition:
    None

  Parameters:
    pIf             - network interface 
    arpHE           - particular cache entry to be updated
    hwAdd           - the (new) hardware address

  Return Values:
    ARP_RES_CACHE_FULL  - cache full error
    ARP_RES_OK          - success
  ***************************************************************************/
static TCPIP_ARP_RESULT _ARPAddCompleteEntry(TCPIP_NET_IF* pIf, IPV4_ADDR* pIPAddr, TCPIP_MAC_ADDR* hwAdd)
{
    ARP_CACHE_DCPT  *pArpDcpt;
    ARP_HASH_ENTRY  *arpHE;
    OA_HASH_ENTRY   *hE;

    pArpDcpt = arpMod.arpCacheDcpt + TCPIP_STACK_NetIxGet(pIf);
    
    hE = TCPIP_OAHASH_EntryLookupOrInsert(pArpDcpt->hashDcpt, pIPAddr);
    if(hE == 0)
    {   // oops, hash full?
        return ARP_RES_CACHE_FULL;
    }

    // now in cache
    arpHE = (ARP_HASH_ENTRY*)hE;
    if(arpHE->hEntry.flags.newEntry != 0)
    {   // populate the new entry
        _ARPSetEntry(arpHE, ARP_FLAG_ENTRY_COMPLETE, hwAdd, &pArpDcpt->completeList);
    }
    else
    {   // existent entry
        _ARPUpdateEntry(pIf, arpHE, hwAdd);
    }

    return ARP_RES_OK;
}



/*****************************************************************************
  Function:
    void TCPIP_ARP_Initialize(const TCPIP_STACK_MODULE_CTRL* const stackCtrl, const ARP_MODULE_CONFIG* arpData)

  Summary:
    Initializes the ARP module.
    
  Description:
    Initializes the ARP module.
    Calls can be done with the request of not tearing down the ARP cache
    This helps for ifup/ifdown sequences.
    Of course, if this is the case the memory allocated for the ARP cache
    has to be from a persistent heap.
    
  Precondition:
    None

  Parameters:
    stackCtrl  - stack initialization parameters
    arpData    - ARP specific initialization parameters

  Returns:
    true if initialization succeded,
    false otherwise
  
  Remarks:
    The request to maintain old ARP cache info (deleteOld field from the ARP_MODULE_CONFIG initialization data)
    is not implemented for stack init/deinit sequences.
    To maintain the data after the stack is completely de-initialized would need a persistent heap
    that's not yet implemented.
    The selection cannot be changed by ifup since this operation does not carry ARP configuration 
    parameters (arpDate == 0).
  ***************************************************************************/
bool TCPIP_ARP_Initialize(const TCPIP_STACK_MODULE_CTRL* const stackCtrl, const ARP_MODULE_CONFIG* arpData)
{
    OA_HASH_DCPT*   hashDcpt;
    ARP_CACHE_DCPT* pArpDcpt;
    size_t          hashMemSize;
    int             ix;

    if(stackCtrl->stackAction == TCPIP_STACK_ACTION_IF_UP)
    {   // interface going up
        // store the delete option for de-initialization
        if(arpMod.deleteOld)
        {   // remove the old entries, if there
            pArpDcpt = arpMod.arpCacheDcpt + stackCtrl->netIx;
            _ARPRemoveCacheEntries(pArpDcpt);
        }
        // else do not re-initialize
        return true;
    }

    // stack going up

    // use default if no initialization data is provided
    if(arpData == 0)
    {
        arpData = &arpConfigDefault;
    }

    // store the delete option for de-initialization
    arpMod.deleteOld = arpData->deleteOld;

    if(arpMod.initCount == 0)
    {   // first time we're run
        // check if there's any persistent data
        if(arpMod.arpCacheDcpt !=0 && (arpData->deleteOld || arpMod.nIfs != stackCtrl->nIfs))
        {   // delete the old copy
            _ARPDeleteResources();
        }

        // store the memory allocation handle
        arpMod.memH = stackCtrl->memH;
        arpMod.nIfs =  stackCtrl->nIfs;

        // parameters initialization
        arpMod.entrySolvedTmo = arpData->entrySolvedTmo;
        arpMod.entryPendingTmo = arpData->entryPendingTmo;
        arpMod.entryRetryTmo = arpData->entryRetryTmo;
        arpMod.permQuota = arpData->permQuota;


        if(arpMod.arpCacheDcpt == 0)
        {
            arpMod.arpCacheDcpt = (ARP_CACHE_DCPT*)TCPIP_HEAP_Calloc(arpMod.memH, arpMod.nIfs, sizeof(*arpMod.arpCacheDcpt)); 
            if(arpMod.arpCacheDcpt == 0)
            {   // failed
                return false;
            }

            hashMemSize = sizeof(OA_HASH_DCPT) + arpData->cacheEntries * sizeof(ARP_HASH_ENTRY);
            for(ix = 0, pArpDcpt = arpMod.arpCacheDcpt; ix < arpMod.nIfs; ix++, pArpDcpt++)
            {
                hashDcpt = (OA_HASH_DCPT*)TCPIP_HEAP_Malloc(arpMod.memH, hashMemSize);

                if(hashDcpt == 0)
                {   // failed
                    _ARPDeleteResources();
                    return false;
                }

                // populate the entries
                hashDcpt->memBlk = hashDcpt + 1;
                hashDcpt->hParam = pArpDcpt;    // store the descriptor it belongs to
                hashDcpt->hEntrySize = sizeof(ARP_HASH_ENTRY);
                hashDcpt->hEntries = arpData->cacheEntries;
                hashDcpt->probeStep = ARP_HASH_PROBE_STEP;

#if defined ( OA_HASH_DYNAMIC_KEY_MANIPULATION )
                hashDcpt->hashF = TCPIP_ARP_HashKeyHash;
#if defined(OA_DOUBLE_HASH_PROBING)
                hashDcpt->probeHash = TCPIP_ARP_HashProbeHash;
#endif  // defined(OA_DOUBLE_HASH_PROBING)
                hashDcpt->delF = TCPIP_ARP_HashEntryDelete;
                hashDcpt->cmpF = TCPIP_ARP_HashKeyCompare;
                hashDcpt->cpyF = TCPIP_ARP_HashKeyCopy; 
#endif  // defined ( OA_HASH_DYNAMIC_KEY_MANIPULATION )
                TCPIP_OAHASH_Initialize(hashDcpt);

                pArpDcpt->hashDcpt = hashDcpt;
                TCPIP_Helper_SingleListInitialize(&pArpDcpt->permList);
                TCPIP_Helper_SingleListInitialize(&pArpDcpt->completeList);
                TCPIP_Helper_SingleListInitialize(&pArpDcpt->incompleteList);

                pArpDcpt->purgeThres = (arpData->purgeThres * pArpDcpt->hashDcpt->hEntries + 99)/100;
                pArpDcpt->purgeQuanta = arpData->purgeQuanta;

            }

            arpMod.pMacPkt = _ARPAllocateTxPacket();
            arpMod.timerHandle = _TCPIPStackAsyncHandlerRegister(TCPIP_ARP_Task, 0, ARP_TASK_PROCESS_RATE * 1000);

            if(arpMod.pMacPkt == 0 || arpMod.timerHandle == 0)
            {
                _ARPDeleteResources();
                return false;
            }

            arpMod.timeSeconds = 0;
            TCPIP_Helper_SingleListInitialize(&arpMod.registeredUsers);
        }
    }

    // per interface initialization
    pArpDcpt = arpMod.arpCacheDcpt + stackCtrl->netIx;

    if(arpMod.deleteOld)
    {   // remove the old entries, if there
        _ARPRemoveCacheEntries(pArpDcpt);
    }
    // else do not re-initialize
    
    arpMod.initCount++;

    return true;
}




void TCPIP_ARP_Deinitialize(const TCPIP_STACK_MODULE_CTRL* const stackCtrl)
{
    
    if(stackCtrl->stackAction == TCPIP_STACK_ACTION_IF_DOWN)
    {   // interface going down
        if(arpMod.deleteOld)
        {
            _ARPRemoveCacheEntries(arpMod.arpCacheDcpt + stackCtrl->netIx);
        }
    }
    else
    {   // if(stackCtrl->stackAction == TCPIP_STACK_ACTION_DEINIT)
        // stack shut down
        if(arpMod.initCount > 0)
        {   // we're up and running
            if(--arpMod.initCount == 0)
            {   // all closed
                // release resources
                // if(arpMod.deleteOld)
                // Note: ignored, always clean up at stack shut down
                {
                    _ARPDeleteResources();
                }
            }
        }
    }
       
       

}

static void _ARPDeleteResources(void)
{

    if(arpMod.arpCacheDcpt)
    {
        int ix;
        ARP_CACHE_DCPT* pArpDcpt;

        for(ix = 0, pArpDcpt = arpMod.arpCacheDcpt; ix < arpMod.nIfs; ix++, pArpDcpt++)
        {
            _ARPDeleteCache(pArpDcpt);
        }

        TCPIP_HEAP_Free(arpMod.memH, arpMod.arpCacheDcpt);
        arpMod.arpCacheDcpt = 0;
    }

    _ARPDeleteClients();
    arpMod.memH = 0;

    if(arpMod.timerHandle)
    {
        _TCPIPStackAsyncHandlerDeRegister(arpMod.timerHandle);
        arpMod.timerHandle = 0;
    }

    if(arpMod.pMacPkt)
    {
        if((arpMod.pMacPkt->pktFlags & TCPIP_MAC_PKT_FLAG_QUEUED) == 0 )
        {
            TCPIP_PKT_PacketFree(arpMod.pMacPkt);
        }
        arpMod.pMacPkt = 0;
    }

}



static void _ARPDeleteCache(ARP_CACHE_DCPT* pArpDcpt)
{

    if(pArpDcpt->hashDcpt)
    {
        _ARPRemoveCacheEntries(pArpDcpt);
        TCPIP_HEAP_Free(arpMod.memH, pArpDcpt->hashDcpt);
        pArpDcpt->hashDcpt = 0;
    }

}

static void _ARPDeleteClients(void)
{
    TCPIP_Notification_RemoveAll(&arpMod.registeredUsers, arpMod.memH);
}

static TCPIP_MAC_PACKET* _ARPAllocateTxPacket(void)
{
    TCPIP_MAC_PACKET*   pPkt;

    // allocate TCPIP_MAC_PACKET packet
    pPkt = TCPIP_PKT_PacketAlloc(sizeof(TCPIP_MAC_PACKET), sizeof(ARP_PACKET), TCPIP_MAC_PKT_FLAG_ARP | TCPIP_MAC_PKT_FLAG_TX);

    if(pPkt)
    {
        TCPIP_PKT_PacketAcknowledgeSet(pPkt, _ARPTxAckFnc, 0);
    }


    return pPkt;
}


static void _ARPTxAckFnc (TCPIP_MAC_PACKET * pPkt, const void * param)
{
    if(arpMod.pMacPkt != pPkt)
    {   // another one allocated
        TCPIP_PKT_PacketFree(pPkt);
    }
    // else we should be OK
}



TCPIP_ARP_HANDLE TCPIP_ARP_HandlerRegister(TCPIP_NET_HANDLE hNet, TCPIP_ARP_EVENT_HANDLER handler, const void* hParam)
{
    if(arpMod.memH)
    {
        ARP_LIST_NODE* newNode = (ARP_LIST_NODE*)TCPIP_Notification_Add(&arpMod.registeredUsers, arpMod.memH, sizeof(*newNode));
        if(newNode)
        {
            newNode->handler = handler;
            newNode->hParam = hParam;
            newNode->hNet = hNet;
            return newNode;
        }
    }

    return 0;

}

// deregister the event handler
bool TCPIP_ARP_HandlerDeRegister(TCPIP_ARP_HANDLE hArp)
{
    if(hArp && arpMod.memH)
    {
        if(TCPIP_Notification_Remove((SGL_LIST_NODE*)hArp, &arpMod.registeredUsers, arpMod.memH))
        {
            return true;
        }
    }

    return false;
}

static void _ARPNotifyClients(TCPIP_NET_IF* pNetIf, const IPV4_ADDR* ipAdd, const TCPIP_MAC_ADDR* MACAddr, TCPIP_ARP_EVENT_TYPE evType)
{
    ARP_LIST_NODE* aNode;

    for(aNode = (ARP_LIST_NODE*)arpMod.registeredUsers.head; aNode != 0; aNode = aNode->next)
    {
        if(aNode->hNet == 0 || aNode->hNet == pNetIf)
        {   // trigger event
            (*aNode->handler)(pNetIf, ipAdd, MACAddr, evType, aNode->hParam);
        }
    }
    
}


// called after service needed reported
// maintain the queues
void TCPIP_ARP_Task(void)
{
    int netIx, purgeIx;
    ARP_HASH_ENTRY  *pE;
    ARP_CACHE_DCPT  *pArpDcpt;
    SGL_LIST_NODE   *pN;
    TCPIP_NET_IF *pIf;
    int         nArpIfs;
    bool        isConfig;


    arpMod.timeSeconds += ARP_TASK_PROCESS_RATE;

    nArpIfs = TCPIP_STACK_NumberOfNetworksGet();

    for(netIx = 0, pArpDcpt = arpMod.arpCacheDcpt; netIx < nArpIfs; netIx++, pArpDcpt++)
    {
        pIf = (TCPIP_NET_IF*)TCPIP_STACK_IndexToNet(netIx);

        // process the incomplete queue
        // see if there's something to remove
        while( (pN = pArpDcpt->incompleteList.head) != 0)
        {
            pE = (ARP_HASH_ENTRY*) ((uint8_t*)pN - offsetof(ARP_HASH_ENTRY, next));
            if( (arpMod.timeSeconds - pE->tInsert) >= arpMod.entryPendingTmo)
            {   // expired, remove it
                TCPIP_OAHASH_EntryRemove(pArpDcpt->hashDcpt, &pE->hEntry);
                TCPIP_Helper_SingleListHeadRemove(&pArpDcpt->incompleteList);
                _ARPNotifyClients(pIf, &pE->ipAddress, 0, ARP_EVENT_TMO);
            }
            else
            {   // this list is ordered, we can safely break out
                break;
            }
        }

        // see if we have to query again
        isConfig = _TCPIPStackIsConfig(pIf);

        for(pN = pArpDcpt->incompleteList.head; pN != 0; pN = pN->next)
        {
            pE = (ARP_HASH_ENTRY*) ((uint8_t*)pN - offsetof(ARP_HASH_ENTRY, next));
            if( (arpMod.timeSeconds - pE->tInsert) >= pE->nRetries * arpMod.entryRetryTmo)
            {   // expired, retry it
                if(isConfig == false || (pE->hEntry.flags.value & ARP_FLAG_ENTRY_CONFIGURE) != 0 )
                {
                    _ARPSendIfPkt(pIf, ARP_OPERATION_REQ, (uint32_t)pIf->netIPAddr.Val, pE->ipAddress.Val, &arpBcastAdd);
                    pE->nRetries++;
                }
            }
        }

        // see the completed entries queue
        while( (pN = pArpDcpt->completeList.head) != 0)
        {
            pE = (ARP_HASH_ENTRY*) ((uint8_t*)pN - offsetof(ARP_HASH_ENTRY, next));
            if( (arpMod.timeSeconds - pE->tInsert) >= arpMod.entrySolvedTmo)
            {   // expired, remove it
                TCPIP_OAHASH_EntryRemove(pArpDcpt->hashDcpt, &pE->hEntry);
                TCPIP_Helper_SingleListHeadRemove(&pArpDcpt->completeList);
            }
            else
            {   // this list is ordered, we can safely break out
                break;
            }
        }

        // finally purge, if needed
        if(pArpDcpt->hashDcpt->fullSlots >= pArpDcpt->purgeThres)
        {
            for(purgeIx = 0; purgeIx < pArpDcpt->purgeQuanta; purgeIx++)
            {
                pN = TCPIP_Helper_SingleListHeadRemove(&pArpDcpt->completeList);
                if(pN)
                {
                    pE = (ARP_HASH_ENTRY*) ((uint8_t*)pN - offsetof(ARP_HASH_ENTRY, next));
                    TCPIP_OAHASH_EntryRemove(pArpDcpt->hashDcpt, &pE->hEntry);
                }
                else
                {   // no more entries
                    break;
                }
            }
        } 

        
    } 

}



/*****************************************************************************
  Function:
    TCPIP_ARP_RESULT TCPIP_ARP_Process(TCPIP_NET_IF* pIf, TCPIP_MAC_PACKET* pPkt)

  Summary:
    Processes an incoming ARP packet.
    
  Description:
    Retrieves an ARP packet from the MAC buffer and determines if it is a
    response to our request (in which case the ARP is resolved) or if it
    is a request requiring our response (in which case we transmit one.)

  Precondition:
    ARP packet is ready in the MAC buffer.

  Parameters:
    None

  Return Values:
    ARP_RES_OK      - processing OK.
    ARP_RES_error   - some error occurred
  ***************************************************************************/
TCPIP_ARP_RESULT TCPIP_ARP_Process(TCPIP_NET_IF* pIf, TCPIP_MAC_PACKET* pPkt)
{
    ARP_PACKET      *pArpPkt;
    TCPIP_MAC_ADDR        *dstMAC; 
    OA_HASH_ENTRY   *hE;
    ARP_CACHE_DCPT  *pArpDcpt;
    int              netIx;
    TCPIP_ARP_RESULT       arpReqRes;
    TCPIP_MAC_PKT_ACK_RES ackRes;

    netIx = TCPIP_STACK_NetIxGet(pIf);
    pArpDcpt = arpMod.arpCacheDcpt + netIx;

    // Obtain the incoming ARP packet and process
    pArpPkt = (ARP_PACKET*)pPkt->pNetLayer;
    _SwapARPPacket(pArpPkt);
    arpReqRes = ARP_RES_OK;

    // Validate the ARP packet
    if ( pArpPkt->HardwareType != HW_ETHERNET     ||
            pArpPkt->MACAddrLen != sizeof(TCPIP_MAC_ADDR)  ||
            pArpPkt->ProtocolLen != sizeof(IPV4_ADDR) )
    {
        ackRes = TCPIP_MAC_PKT_ACK_STRUCT_ERR;
    }
    else
    {
#ifdef TCPIP_STACK_USE_ZEROCONF_LINK_LOCAL
        _ARPProcessRxPkt(pIf, pArpPkt);
#endif

        // Handle incoming ARP packet
        hE = TCPIP_OAHASH_EntryLookup(pArpDcpt->hashDcpt, &pArpPkt->SenderIPAddr.Val);
        if(hE != 0)
        {   // we already have this sender and we should update it
            _ARPUpdateEntry(pIf, (ARP_HASH_ENTRY*)hE, &pArpPkt->SenderMACAddr);
        }

        while(!_TCPIPStackIsConfig(pIf) && (pArpPkt->TargetIPAddr.Val == pIf->netIPAddr.Val))
        {   // we are the target and we should add to cache anyway
            if(hE == 0)
            {   // not there yet
                arpReqRes = _ARPAddCompleteEntry(pIf, &pArpPkt->SenderIPAddr, &pArpPkt->SenderMACAddr);
            }

            // Handle incoming ARP operation
            if(pArpPkt->Operation == ARP_OPERATION_REQ)
            {   
                // ARP packet asking for this host IP address 
#ifdef TCPIP_STACK_USE_ZEROCONF_LINK_LOCAL
                /* Fix for Loop-Back suppression:
                 * For ZCLL-Claim packets, host should not respond.
                 * Check Sender's MAC-address with own MAC-address and 
                 * if it is matched, response will not be sent back. This
                 * was leading to flooding of ARP-answeres */
                if(!memcmp (&pArpPkt->SenderMACAddr, &pIf->netMACAddr, 6))
                {
                    SYS_CONSOLE_MESSAGE("Loopback answer suppressed \r\n");
                    break;
                }
#endif

                // Need to send a reply to the requestor 
                dstMAC = &pArpPkt->SenderMACAddr;
                // Send an ARP response to the received request
                if(!_ARPSendIfPkt(pIf, ARP_OPERATION_RESP, (uint32_t)pIf->netIPAddr.Val, (uint32_t)pArpPkt->SenderIPAddr.Val, dstMAC))
                {
                    arpReqRes =  ARP_RES_TX_FAILED;
                }
            }
            break;
        }

        ackRes = TCPIP_MAC_PKT_ACK_RX_OK;
    }


    TCPIP_PKT_PacketAcknowledge(pPkt, ackRes); 
    return arpReqRes;
}

    
// the IP layer should request for the proper IP address!
// no checking is done at this level
TCPIP_ARP_RESULT TCPIP_ARP_Resolve(TCPIP_NET_HANDLE hNet, IPV4_ADDR* IPAddr)
{
    TCPIP_NET_IF *pIf;
   
    if(IPAddr->Val == 0)
    {   // do not store 0's in cache
        return ARP_RES_BAD_ADDRESS;
    }
    
    pIf = _TCPIPStackHandleToNetUp(hNet);
    if(pIf == 0)
    {
        return ARP_RES_NO_INTERFACE;
    }

    if(_TCPIPStackIsConfig(pIf))
    {   // no ARP probes during configuration
        return ARP_RES_CONFIGURE_ERR;
    }

    return _ARPProbeAddress(pIf, IPAddr, &pIf->netIPAddr, ARP_OPERATION_REQ, 0);
}

TCPIP_ARP_RESULT TCPIP_ARP_Probe(TCPIP_NET_HANDLE hNet, IPV4_ADDR* IPAddr, IPV4_ADDR* srcAddr, TCPIP_ARP_OPERATION_TYPE opType)
{
    TCPIP_NET_IF *pIf =_TCPIPStackHandleToNetUp(hNet);

    if(pIf == 0)
    {
        return ARP_RES_NO_INTERFACE;
    }


    if(_TCPIPStackIsConfig(pIf) && (opType & ARP_OPERATION_CONFIGURE) == 0)
    {   // no ARP probes during configuration
        return ARP_RES_CONFIGURE_ERR;
    }

    return _ARPProbeAddress(pIf, IPAddr, srcAddr, opType, 0);
}


static TCPIP_ARP_RESULT _ARPProbeAddress(TCPIP_NET_IF* pIf, IPV4_ADDR* IPAddr, IPV4_ADDR* srcAddr, TCPIP_ARP_OPERATION_TYPE opType, TCPIP_MAC_ADDR* pHwAdd)
{
    ARP_CACHE_DCPT  *pArpDcpt;
    OA_HASH_ENTRY   *hE;
   
    if(IPAddr->Val == 0)
    {   // do not store 0's in cache
        return ARP_RES_BAD_ADDRESS;
    }
     
    pArpDcpt = arpMod.arpCacheDcpt + TCPIP_STACK_NetIxGet(pIf);

    hE = TCPIP_OAHASH_EntryLookupOrInsert(pArpDcpt->hashDcpt, &IPAddr->Val);
    if(hE == 0)
    {   // oops!
        return ARP_RES_CACHE_FULL;
    }
        
    if(hE->flags.newEntry != 0)
    {   // new entry; add it to the not done list 
        _ARPSetEntry((ARP_HASH_ENTRY*)hE, (opType & ARP_OPERATION_CONFIGURE) != 0 ? ARP_FLAG_ENTRY_CONFIGURE : 0 , 0, &pArpDcpt->incompleteList);

        // initiate an ARP request operation
        _ARPSendIfPkt(pIf, (opType & ARP_OPERATION_MASK), (uint32_t)srcAddr->Val, ((ARP_HASH_ENTRY*)hE)->ipAddress.Val, &arpBcastAdd);
        return ARP_RES_ENTRY_NEW;
    }
    // else, even if it is not complete, TCPIP_ARP_Task will initiate retransmission
    // Normally if the entry is existent, it should be refreshed, since it's obviously needed.
    // However, the TCPIP_ARP_IsResolved() will do it, because that's the call that actually uses the entry!
    if((hE->flags.value & ARP_FLAG_ENTRY_VALID_MASK) != 0)
    {   // found address in cache
        ARP_HASH_ENTRY  *arpHE = (ARP_HASH_ENTRY*)hE;
        if(pHwAdd)
        {
            *pHwAdd = arpHE->hwAdd;
        }
        if((hE->flags.value & ARP_FLAG_ENTRY_COMPLETE) != 0 )
        {   // an existent entry, re-used, gets refreshed
            _ARPRefreshEntry(arpHE, &pArpDcpt->completeList);
        }
        return ARP_RES_ENTRY_SOLVED;
    }
    
    // incomplete
    return ARP_RES_ENTRY_QUEUED;


}

bool TCPIP_ARP_IsResolved(TCPIP_NET_HANDLE hNet, IPV4_ADDR* IPAddr, TCPIP_MAC_ADDR* MACAddr)
{
    OA_HASH_ENTRY   *hE;
    ARP_CACHE_DCPT  *pArpDcpt;
    TCPIP_NET_IF  *pIf;

    pIf = _TCPIPStackHandleToNetUp(hNet);
    if(!pIf)
    {
        return ARP_RES_NO_INTERFACE;
    }
    

    pArpDcpt = arpMod.arpCacheDcpt + TCPIP_STACK_NetIxGet(pIf);
    
    hE = TCPIP_OAHASH_EntryLookup(pArpDcpt->hashDcpt, &IPAddr->Val);
    if(hE != 0 && (hE->flags.value & ARP_FLAG_ENTRY_VALID_MASK) != 0 )
    {   // found address in cache
        ARP_HASH_ENTRY  *arpHE = (ARP_HASH_ENTRY*)hE;
        if(MACAddr)
        {
            *MACAddr = arpHE->hwAdd;
        }
        if((hE->flags.value & ARP_FLAG_ENTRY_COMPLETE) != 0 )
        {   // an existent entry, re-used, gets refreshed
            _ARPRefreshEntry(arpHE, &pArpDcpt->completeList);
        }
        return true;
    }
    
    return false;
    
}



/*****************************************************************************
  Function:
    void _SwapARPPacket(ARP_PACKET* p)

  Description:
    Swaps endian-ness of header information in an ARP packet.

  Precondition:
    None

  Parameters:
    p - The ARP packet to be swapped

  Returns:
    None
  ***************************************************************************/
static void _SwapARPPacket(ARP_PACKET* p)
{
    p->HardwareType     = TCPIP_Helper_htons(p->HardwareType);
    p->Protocol         = TCPIP_Helper_htons(p->Protocol);
    p->Operation        = TCPIP_Helper_htons(p->Operation);
}

TCPIP_ARP_RESULT TCPIP_ARP_EntrySet(TCPIP_NET_HANDLE hNet, IPV4_ADDR* ipAdd, TCPIP_MAC_ADDR* hwAdd, bool perm)
{
    ARP_CACHE_DCPT  *pArpDcpt;
    ARP_HASH_ENTRY  *arpHE;
    OA_HASH_ENTRY   *hE;
    SINGLE_LIST     *oldList, *newList;
    ARP_ENTRY_FLAGS newFlags;
    TCPIP_ARP_RESULT      res;
    TCPIP_NET_IF    *pIf;

    if(ipAdd->Val == 0)
    {   // do not store 0's in cache
        return ARP_RES_BAD_ADDRESS;
    }
    
    pIf = _TCPIPStackHandleToNetUp(hNet);
    if(!pIf)
    {
        return ARP_RES_NO_INTERFACE;
    }
    
    pArpDcpt = arpMod.arpCacheDcpt + TCPIP_STACK_NetIxGet(pIf);

    hE = TCPIP_OAHASH_EntryLookupOrInsert(pArpDcpt->hashDcpt, &ipAdd->Val);
    if(hE == 0)
    {   // oops!
        return ARP_RES_CACHE_FULL;
    }

    // where to put it
    if(perm)
    {
        newList = &pArpDcpt->permList;
        newFlags = ARP_FLAG_ENTRY_PERM;
    }
    else
    {
        newList = &pArpDcpt->completeList;
        newFlags = ARP_FLAG_ENTRY_COMPLETE;       // complete
    }
    
    arpHE = (ARP_HASH_ENTRY*)hE;
   
    if(hE->flags.newEntry == 0)
    {   // existent entry
        if( (hE->flags.value & ARP_FLAG_ENTRY_PERM) != 0 )
        {
            oldList =  &pArpDcpt->permList;
        }
        else if( (hE->flags.value & ARP_FLAG_ENTRY_COMPLETE) != 0 )
        {
            oldList =  &pArpDcpt->completeList;
        }
        else
        {
            oldList =  &pArpDcpt->incompleteList;
        }

        if(newList != oldList)
        {   // remove from the old list
            TCPIP_Helper_SingleListNodeRemove(oldList, (SGL_LIST_NODE*)&arpHE->next);
        }
        res = ARP_RES_ENTRY_EXIST;
    }
    else
    {
        res = ARP_RES_OK;
    }
    
    // add it to where it belongs
    _ARPSetEntry(arpHE, newFlags, hwAdd, newList);

    if(SingleListCount(&pArpDcpt->permList) >= (arpMod.permQuota * pArpDcpt->hashDcpt->fullSlots)/100)
    {   // quota exceeded
        res = ARP_RES_PERM_QUOTA_EXCEED;
    }

    return res;
}

TCPIP_ARP_RESULT TCPIP_ARP_EntryGet(TCPIP_NET_HANDLE hNet, IPV4_ADDR* ipAdd, TCPIP_MAC_ADDR* pHwAdd, bool probe)
{   
    TCPIP_NET_IF  *pIf = _TCPIPStackHandleToNetUp(hNet);

    if(pIf == 0)
    {
        return ARP_RES_NO_INTERFACE;
    }

    if(probe)
    {
        if(_TCPIPStackIsConfig(pIf))
        {   // no ARP probes during configuration
            return ARP_RES_CONFIGURE_ERR;
        }
        return _ARPProbeAddress(pIf, ipAdd, &pIf->netIPAddr, ARP_OPERATION_REQ, pHwAdd);
    }
    else
    {
        return (TCPIP_ARP_IsResolved(pIf, ipAdd, pHwAdd))? ARP_RES_OK : ARP_RES_NO_ENTRY;
    }

}

TCPIP_ARP_RESULT TCPIP_ARP_EntryRemove(TCPIP_NET_HANDLE hNet,  IPV4_ADDR* ipAdd)
{
    OA_HASH_ENTRY   *hE;
    ARP_CACHE_DCPT  *pArpDcpt;
    TCPIP_NET_IF  *pIf;

    pIf = _TCPIPStackHandleToNetUp(hNet);
    if(!pIf)
    {
        return ARP_RES_NO_INTERFACE;
    }
    

    pArpDcpt = arpMod.arpCacheDcpt + TCPIP_STACK_NetIxGet(pIf);

    hE = TCPIP_OAHASH_EntryLookup(pArpDcpt->hashDcpt, &ipAdd->Val);

    if(hE == 0)
    {
        return ARP_RES_NO_ENTRY;
    }

    _ARPRemoveEntry(pArpDcpt, hE);
    
    return ARP_RES_OK;
}


TCPIP_ARP_RESULT TCPIP_ARP_EntryRemoveNet(TCPIP_NET_HANDLE hNet, IPV4_ADDR* ipAdd, IPV4_ADDR* mask , TCPIP_ARP_ENTRY_TYPE type)
{
    OA_HASH_ENTRY   *hE;
    ARP_HASH_ENTRY  *arpHE;
    ARP_CACHE_DCPT  *pArpDcpt;
    OA_HASH_DCPT    *pOH;
    TCPIP_NET_IF      *pIf;
    int             index;
    uint16_t        andFlags, resFlags;
    uint32_t        matchAdd;

    pIf = _TCPIPStackHandleToNetUp(hNet);
    if(!pIf)
    {
        return ARP_RES_NO_INTERFACE;
    }

    switch (type)
    {
        case ARP_ENTRY_TYPE_PERMANENT:
            andFlags = resFlags = ARP_FLAG_ENTRY_PERM;
            break;

        case ARP_ENTRY_TYPE_COMPLETE:
            andFlags = resFlags =  ARP_FLAG_ENTRY_COMPLETE;
            break;
            
        case ARP_ENTRY_TYPE_INCOMPLETE:
            andFlags = (ARP_FLAG_ENTRY_PERM | ARP_FLAG_ENTRY_COMPLETE);
            resFlags = 0;
            break;
            
        case ARP_ENTRY_TYPE_ANY:
            andFlags = resFlags = 0;
            break;

        default:
            return ARP_RES_BAD_TYPE;
    }


    pArpDcpt = arpMod.arpCacheDcpt + TCPIP_STACK_NetIxGet(pIf);
    pOH = pArpDcpt->hashDcpt;
    matchAdd = ipAdd->Val & mask->Val;

    
    // scan all entries
    for(index = 0; index < pOH->hEntries; index++)
    {
        hE = TCPIP_OAHASH_EntryGet(pArpDcpt->hashDcpt, index);
        if(hE->flags.busy != 0)
        {
            if((hE->flags.value & andFlags) == resFlags)
            {   // flags match
                arpHE = (ARP_HASH_ENTRY*)hE;
                if((arpHE->ipAddress.Val & mask->Val) == matchAdd)
                {   // address match;  delete entry
                    _ARPRemoveEntry(pArpDcpt, hE);
                }
            }
        }
    }

    return ARP_RES_OK;
}

TCPIP_ARP_RESULT TCPIP_ARP_EntryRemoveAll(TCPIP_NET_HANDLE hNet)
{
    TCPIP_NET_IF  *pIf;
    pIf = _TCPIPStackHandleToNetUp(hNet);
    if(!pIf)
    {
        return ARP_RES_NO_INTERFACE;
    }
    
    ARP_CACHE_DCPT  *pArpDcpt = arpMod.arpCacheDcpt + TCPIP_STACK_NetIxGet(pIf);

    _ARPRemoveCacheEntries(pArpDcpt);

    return ARP_RES_OK;
}

TCPIP_ARP_RESULT TCPIP_ARP_EntryQuery(TCPIP_NET_HANDLE hNet, size_t index, TCPIP_ARP_ENTRY_QUERY* pArpQuery)
{
    OA_HASH_ENTRY   *hE;
    ARP_HASH_ENTRY  *arpHE;
    ARP_CACHE_DCPT  *pArpDcpt;
    TCPIP_MAC_ADDR        noHwAdd = {{0}};
    TCPIP_NET_IF  *pIf;

    pIf = _TCPIPStackHandleToNetUp(hNet);
    if(!pIf)
    {
        return ARP_RES_NO_INTERFACE;
    }

    pArpDcpt = arpMod.arpCacheDcpt + TCPIP_STACK_NetIxGet(pIf);
    hE = TCPIP_OAHASH_EntryGet(pArpDcpt->hashDcpt, index);
    

    if(hE == 0)
    {
        return ARP_RES_BAD_INDEX;
    }
    
    arpHE = (ARP_HASH_ENTRY*)hE;

    if(pArpQuery)
    {
        pArpQuery->entryIpAdd.Val = 0;
        pArpQuery->entryHwAdd = noHwAdd;
        
        if(hE->flags.busy == 0)
        {
            pArpQuery->entryType = ARP_ENTRY_TYPE_INVALID;
        }
        else if((hE->flags.value & ARP_FLAG_ENTRY_VALID_MASK) != 0)
        {
            pArpQuery->entryType = ((hE->flags.value & ARP_FLAG_ENTRY_PERM) != 0)?
                                ARP_ENTRY_TYPE_PERMANENT:ARP_ENTRY_TYPE_COMPLETE;
            pArpQuery->entryIpAdd.Val = arpHE->ipAddress.Val;
            pArpQuery->entryHwAdd = arpHE->hwAdd;
        }
        else
        {
            pArpQuery->entryType = ARP_ENTRY_TYPE_INCOMPLETE;
            pArpQuery->entryIpAdd.Val = arpHE->ipAddress.Val;
        }
    }

    return ARP_RES_OK;
}

size_t TCPIP_ARP_CacheEntriesNoGet(TCPIP_NET_HANDLE hNet, TCPIP_ARP_ENTRY_TYPE type)
{
    TCPIP_NET_IF  *pIf;
    
    pIf = _TCPIPStackHandleToNetUp(hNet);
    if(!pIf)
    {
        return ARP_RES_NO_INTERFACE;
    }
    
    ARP_CACHE_DCPT  *pArpDcpt = arpMod.arpCacheDcpt + TCPIP_STACK_NetIxGet(pIf);
    OA_HASH_DCPT    *pOH = pArpDcpt->hashDcpt;

    switch(type)
    {
        case ARP_ENTRY_TYPE_INVALID:
           return pOH->hEntries - pOH->fullSlots;

        case ARP_ENTRY_TYPE_PERMANENT:
           return SingleListCount(&pArpDcpt->permList);

        case ARP_ENTRY_TYPE_COMPLETE:
           return SingleListCount(&pArpDcpt->completeList);

        case ARP_ENTRY_TYPE_INCOMPLETE:
           return SingleListCount(&pArpDcpt->incompleteList);

        case ARP_ENTRY_TYPE_ANY:
           return pOH->fullSlots;

        default:    // case ARP_ENTRY_TYPE_TOTAL:
           return pOH->hEntries;
    }

}

TCPIP_ARP_RESULT TCPIP_ARP_CacheThresholdSet(TCPIP_NET_HANDLE hNet, int purgeThres, int purgeEntries)
{
    TCPIP_NET_IF  *pIf;

    pIf = _TCPIPStackHandleToNetUp(hNet);
    if(!pIf)
    {
        return ARP_RES_NO_INTERFACE;
    }
    
    ARP_CACHE_DCPT  *pArpDcpt = arpMod.arpCacheDcpt + TCPIP_STACK_NetIxGet(pIf);

    pArpDcpt->purgeThres = (purgeThres * pArpDcpt->hashDcpt->hEntries + 99)/100;
    pArpDcpt->purgeQuanta = purgeEntries;

    return ARP_RES_OK;
}

#if !defined ( OA_HASH_DYNAMIC_KEY_MANIPULATION )

// static versions
// 
size_t TCPIP_OAHASH_KeyHash(OA_HASH_DCPT* pOH, void* key)
{
    return fnv_32_hash(key, sizeof(((ARP_HASH_ENTRY*)0)->ipAddress)) % (pOH->hEntries);
}

#if defined(OA_DOUBLE_HASH_PROBING)
size_t TCPIP_OAHASH_HashProbe(OA_HASH_DCPT* pOH, void* key)
{
    return fnv_32a_hash(key, sizeof(((ARP_HASH_ENTRY*)0)->ipAddress)) % (pOH->hEntries);
}

#endif  // defined(OA_DOUBLE_HASH_PROBING)

// Deletes an entry to make room in the hash table.
// This shouldn't normally occur if TCPIP_ARP_Task()
// does its job of periodically performing the cache clean-up.
// However, since the threshold can be dynamically adjusted,
// the situation could still occur
OA_HASH_ENTRY* TCPIP_OAHASH_EntryDelete(OA_HASH_DCPT* pOH)
{
    ARP_CACHE_DCPT  *pArpDcpt;
    ARP_HASH_ENTRY  *pE;
    SGL_LIST_NODE   *pN;
    SINGLE_LIST     *pRemList = 0;    
    
    pArpDcpt = (ARP_CACHE_DCPT*)pOH->hParam;

    if( (pN = pArpDcpt->incompleteList.head) != 0)
    {
        pE = (ARP_HASH_ENTRY*) ((uint8_t*)pN - offsetof(ARP_HASH_ENTRY, next));
        if( (arpMod.timeSeconds - pE->tInsert) >= arpMod.entryPendingTmo)
        {   // we remove this one
            pRemList = &pArpDcpt->incompleteList;
        }
    }

    if(pRemList == 0)
    {   // no luck with the incomplete list; use the complete one
            pRemList = &pArpDcpt->completeList;
    }

    pN = TCPIP_Helper_SingleListHeadRemove(pRemList);

    if(pN)
    {
        pE = (ARP_HASH_ENTRY*) ((uint8_t*)pN - offsetof(ARP_HASH_ENTRY, next));
        return &pE->hEntry;    
    }

    // it's possible to be unable to make room in the cache
    // for example, too many permanent entries added...
                   
    return 0;
}


int TCPIP_OAHASH_KeyCompare(OA_HASH_DCPT* pOH, OA_HASH_ENTRY* hEntry, void* key)
{
    return ((ARP_HASH_ENTRY*)hEntry)->ipAddress.Val != ((ARP_UNALIGNED_KEY*)key)->v;
}

void TCPIP_OAHASH_KeyCopy(OA_HASH_DCPT* pOH, OA_HASH_ENTRY* dstEntry, void* key)
{

    ((ARP_HASH_ENTRY*)dstEntry)->ipAddress.Val = ((ARP_UNALIGNED_KEY*)key)->v;
}

#else   // defined ( OA_HASH_DYNAMIC_KEY_MANIPULATION )
// dynamic versions
// 
size_t TCPIP_ARP_HashKeyHash(OA_HASH_DCPT* pOH, void* key)
{
    return fnv_32_hash(key, sizeof(((ARP_HASH_ENTRY*)0)->ipAddress)) % (pOH->hEntries);
}

#if defined(OA_DOUBLE_HASH_PROBING)
size_t TCPIP_ARP_HashProbeHash(OA_HASH_DCPT* pOH, void* key)
{
    return fnv_32a_hash(key, sizeof(((ARP_HASH_ENTRY*)0)->ipAddress)) % (pOH->hEntries);
}

#endif  // defined(OA_DOUBLE_HASH_PROBING)

// Deletes an entry to make room in the hash table.
// This shouldn't normally occur if TCPIP_ARP_Task()
// does its job of periodically performing the cache clean-up.
// However, since the threshold can be dynamically adjusted,
// the situation could still occur
OA_HASH_ENTRY* TCPIP_ARP_HashEntryDelete(OA_HASH_DCPT* pOH)
{
    ARP_CACHE_DCPT  *pArpDcpt;
    ARP_HASH_ENTRY  *pE;
    SGL_LIST_NODE   *pN;
    SINGLE_LIST     *pRemList = 0;    
    
    pArpDcpt = (ARP_CACHE_DCPT*)pOH->hParam;

    if( (pN = pArpDcpt->incompleteList.head) != 0)
    {
        pE = (ARP_HASH_ENTRY*) ((uint8_t*)pN - offsetof(ARP_HASH_ENTRY, next));
        if( (arpMod.timeSeconds - pE->tInsert) >= arpMod.entryPendingTmo)
        {   // we remove this one
            pRemList = &pArpDcpt->incompleteList;
        }
    }

    if(pRemList == 0)
    {   // no luck with the incomplete list; use the complete one
            pRemList = &pArpDcpt->completeList;
    }

    pN = TCPIP_Helper_SingleListHeadRemove(pRemList);

    if(pN)
    {
        pE = (ARP_HASH_ENTRY*) ((uint8_t*)pN - offsetof(ARP_HASH_ENTRY, next));
        return &pE->hEntry;    
    }

    // it's possible to be unable to make room in the cache
    // for example, too many permanent entries added...
                   
    return 0;
}


int TCPIP_ARP_HashKeyCompare(OA_HASH_DCPT* pOH, OA_HASH_ENTRY* hEntry, void* key)
{
    return ((ARP_HASH_ENTRY*)hEntry)->ipAddress.Val != ((ARP_UNALIGNED_KEY*)key)->v;
}

void TCPIP_ARP_HashKeyCopy(OA_HASH_DCPT* pOH, OA_HASH_ENTRY* dstEntry, void* key)
{

    ((ARP_HASH_ENTRY*)dstEntry)->ipAddress.Val = ((ARP_UNALIGNED_KEY*)key)->v;
}


#endif  // !defined ( OA_HASH_DYNAMIC_KEY_MANIPULATION )



