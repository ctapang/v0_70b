/*******************************************************************************
  TCP/IP commands implementation

  Summary:
    Module for Microchip TCP/IP Stack
    
  Description:
    TCPIP stack commands entities. 
    Note, this module is based on system command parser
*******************************************************************************/

/*******************************************************************************
FileName:   tcpip_commands.c
Copyright �2012 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED �AS IS?WITHOUT WARRANTY OF ANY KIND,
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
#include "tcpip_modules_config.h"
#include "tcpip/tcpip_manager.h"
#if defined(TCPIP_IF_MRF24W)
#include "driver/wifi/mrf24w/drv_wifi.h"
#endif  // defined(TCPIP_IF_MRF24W)

#if defined(TCPIP_STACK_COMMAND_ENABLE)

#define TCPIP_THIS_MODULE_ID    TCPIP_MODULE_TCPIP_COMMAND
static int  initialNetIfs = 0;    // Backup interfaces number for stack restart
static TCPIP_HEAP_HANDLE       initialHeapH = 0;

#if defined(TCPIP_STACK_COMMANDS_STORAGE_ENABLE)

typedef struct
{
    size_t                  stgSize;        // size  + valid flag
    TCPIP_STACK_NET_IF_DCPT netDcptStg;     // configuration save
    uint8_t                 restoreBuff[sizeof(TCPIP_NETWORK_CONFIG) + 120]; // buffer to restore the configuration
}TCPIP_COMMAND_STG_DCPT;

static TCPIP_COMMAND_STG_DCPT*   pCmdStgDcpt = 0;   // store current interface configuration
static TCPIP_NETWORK_CONFIG*     pCmdNetConf = 0;   // create the array of configurations needed for stack initialization

static bool                     tcpipCmdPreserveSavedInfo = false; // do not discard the saved data

#endif  // defined(TCPIP_STACK_COMMANDS_STORAGE_ENABLE)

static int _Command_AddressService(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv, TCPIP_STACK_ADDRESS_SERVICE_TYPE svcType);


static int _Command_NetInfo(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv);
static int _Command_DefaultInterfaceSet (_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv);
static int CommandDhcpOptions(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv);
static int _Command_DHCPSOnOff(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv);
static int _Command_ZcllOnOff(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv);
static int _Command_IPAddressSet(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv);
static int _Command_GatewayAddressSet(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv);
static int _Command_PrimaryDNSAddressSet(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv);
static int _Command_BIOSNameSet(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv);
static int _Command_MACAddressSet(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv);
static int _Command_NetworkOnOff(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv);
static int _Command_StackOnOff(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv);
static int _Command_HeapInfo(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv);
static int CommandArp(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv);

#if defined(TCPIP_STACK_USE_DHCP_SERVER)
static int _Command_DHCPLeaseInfo(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv);
#endif  //  defined(TCPIP_STACK_USE_DHCP_SERVER)

#if defined(TCPIP_STACK_USE_ICMP_CLIENT)

#define TCPIP_COMMAND_ICMP_ECHO_REQUEST_MIN_DELAY 5  // minimum delay between successive echo requests

// ping command task status
typedef enum
{
    TCPIP_PING_CMD_IDLE = 0,    // ping task is idle
    TCPIP_PING_CMD_DNS_GET,     // get DNS
    TCPIP_PING_CMD_DNS_WAIT,    // wait for DNS
    TCPIP_PING_CMD_DO_PING,     // send pings
}TCPIP_PING_CMD_STAT;

static int                  CommandPing(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv);
static void                 CommandPingHandler(TCPIP_NET_HANDLE hNetIf, IPV4_ADDR * remoteIP, void * data);
static void                 _PingStop(_CMDIO_DEV_NODE* pCmdIO, const void* cmdIoParam);

static tcpipAsyncHandle       icmptickH = 0;      // tick handle

static char                 icmpTargetHost[31];     // current target host name
static char                 icmpTargetAddrStr[17];  // current target address string
static IPV4_ADDR            icmpTargetAddr;         // current target address
static uint16_t             icmpSequenceNo;         // current sequence number
static uint16_t             icmpIdentifier;         // current ID number

static int                  icmpReqNo;              // number of requests to send
static int                  icmpReqCount;           // current request counter
static int                  icmpAckRecv;            // number of acks
static int                  icmpReqDelay;

static ICMP_HANDLE          hIcmp = 0;
static _CMDIO_DEV_NODE*     pIcmpCmd = 0;
static const void*          icmpCmdIoParam = 0;
SYS_TICK                    icmpStartTick;

static TCPIP_PING_CMD_STAT  icmpCmdStat = TCPIP_PING_CMD_IDLE;


#endif  // defined(TCPIP_STACK_USE_ICMP_CLIENT)

// TCPIP stack command table
static const _SYS_CMD_DCPT    tcpipCmdTbl[]=
{
    {"netinfo",     _Command_NetInfo,              ": Get network information"},
    {"defnet",      _Command_DefaultInterfaceSet,  ": Set default network interface"},
    {"dhcp",        CommandDhcpOptions,          ": DHCP client commands"},
    {"dhcps",       _Command_DHCPSOnOff,           ": Turn DHCP server on/off"},
    {"zcll",        _Command_ZcllOnOff,            ": Turn ZCLL on/off"},
    {"setip",       _Command_IPAddressSet,         ": Set IP address and mask"},
    {"setgw",       _Command_GatewayAddressSet,    ": Set Gateway address"},
    {"setdns",      _Command_PrimaryDNSAddressSet,     ": Set DNS address"},
    {"setbios",     _Command_BIOSNameSet,          ": Set host's NetBIOS name"},
    {"setmac",      _Command_MACAddressSet,        ": Set MAC address"},
    {"if",          _Command_NetworkOnOff,         ": Bring an interface up/down"},
    {"stack",       _Command_StackOnOff,           ": Stack turn on/off"},
    {"heapinfo",    _Command_HeapInfo,             ": Check heap status"},
#if defined(TCPIP_STACK_USE_DHCP_SERVER)
    {"dhcpsinfo",	_Command_DHCPLeaseInfo, 	     ": Display DHCP Server Lease Details" },
#endif  //  defined(TCPIP_STACK_USE_DHCP_SERVER)
#if defined(TCPIP_STACK_USE_ICMP_CLIENT)
    {"ping",        CommandPing,                 ": Ping an IP address"},
#endif  // defined(TCPIP_STACK_USE_ICMP_CLIENT)
    {"arp",         CommandArp,                   ": arp commands"},
};

bool TCPIP_Commands_Initialize(const TCPIP_STACK_MODULE_CTRL* const stackCtrl, const TCPIPCMD_MODULE_CONFIG* const pCmdInit)
{
    if(stackCtrl->stackAction == TCPIP_STACK_ACTION_IF_UP)
    {   // interface restart
        return true;
    }


    // stack init
    initialNetIfs = stackCtrl->nIfs;
    initialHeapH = stackCtrl->memH;

    // create command group
    if (!_SYS_COMMAND_ADDGRP(tcpipCmdTbl, sizeof(tcpipCmdTbl)/sizeof(*tcpipCmdTbl), "tcpip", ": stack commands"))
    {
        SYS_ERROR(SYS_ERROR_ERROR, "Failed to create TCPIP Commands\r\n");
        return false;
    }

#if defined(TCPIP_STACK_COMMANDS_STORAGE_ENABLE)
    // get storage for interfaces configuration
    // cannot be taken from the TCPIP-HEAP because we need it persistent after
    // TCPIP_STACK_Deinit() is called!
    if(pCmdStgDcpt == 0 && pCmdNetConf == 0)
    {
        pCmdStgDcpt = (TCPIP_COMMAND_STG_DCPT*)SystemCalloc(initialNetIfs, sizeof(*pCmdStgDcpt));
        pCmdNetConf = (TCPIP_NETWORK_CONFIG*)SystemCalloc(initialNetIfs, sizeof(*pCmdNetConf));
        if(pCmdStgDcpt == 0 || pCmdNetConf == 0)
        {   // failure is not considered to be catastrophic
            SYS_ERROR(SYS_ERROR_WARN, "Failed to create TCPIP Commands Storage/Config\r\n");
        }
    }
#endif  // defined(TCPIP_STACK_COMMANDS_STORAGE_ENABLE)

#if defined(TCPIP_IF_MRF24W) && defined(TCPIP_STACK_COMMANDS_WIFI_ENABLE)
    WIFICommandsInit();
#endif

#if defined(TCPIP_STACK_USE_ICMP_CLIENT)
    hIcmp = 0;

    icmptickH = _TCPIPStackAsyncHandlerRegister(TCPIPCommandsTask, 0, 0);
    if(icmptickH == 0)
    {   // timer is not active now
        SYS_ERROR(SYS_ERROR_ERROR, "ICMP tick registration failed\r\n");
        return false;
    }
    // else the timer will start when we send a query
    icmpCmdStat = TCPIP_PING_CMD_IDLE;
    icmpAckRecv = 0;

#endif  // defined(TCPIP_STACK_USE_ICMP_CLIENT)

    return true;
}

void TCPIP_Commands_Deinitialize(const TCPIP_STACK_MODULE_CTRL* const stackCtrl)
{
    // if(stackCtrl->stackAction == TCPIP_STACK_ACTION_DEINIT) // stack shut down
    // if(stackCtrl->stackAction == TCPIP_STACK_ACTION_IF_DOWN) // interface down

    if(stackCtrl->stackAction == TCPIP_STACK_ACTION_DEINIT)
    {   // whole stack is going down
#if defined(TCPIP_STACK_COMMANDS_STORAGE_ENABLE)
        if(tcpipCmdPreserveSavedInfo == false)
        {
            SystemFree(pCmdStgDcpt);
            SystemFree(pCmdNetConf);
            pCmdStgDcpt = 0;
            pCmdNetConf = 0;
        }
#endif  // defined(TCPIP_STACK_COMMANDS_STORAGE_ENABLE)

#if defined(TCPIP_STACK_USE_ICMP_CLIENT)
        if(icmptickH != 0)
        {
            _TCPIPStackAsyncHandlerDeRegister(icmptickH);
            icmptickH = 0;
        }
#endif  // defined(TCPIP_STACK_USE_ICMP_CLIENT)

    }
}

static int _Command_NetInfo(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv)
{
    int i;
    TCPIP_NET_HANDLE netH;
    IPV4_ADDR ipAddr;
    const TCPIP_MAC_ADDR* pMac;
    TCPIP_NET_IF* pNetIf;
    TCPIP_STACK_MODULE macID;
    const char  *hostName, *msgAdd;
    const void* cmdIoParam = pCmdIO->cmdIoParam;
#if defined(TCPIP_STACK_USE_IPV6)
    IPV6_ADDR_STRUCT currIpv6Add;
    IPV6_ADDR_HANDLE prevHandle, nextHandle;
    char   addrBuff[44];
#else
    char   addrBuff[20];
#endif  // defined(TCPIP_STACK_USE_IPV6)

    if (argc > 2)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Usage: netinfo\r\n");
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ex: netinfo\r\n");
        return false;
    }

    for (i=0; i<initialNetIfs; i++)
    {
        netH = TCPIP_STACK_IndexToNet(i);
        pNetIf = _TCPIPStackHandleToNet(netH);
        macID = TCPIP_STACK_NetMACIdGet(pNetIf);
        (*pCmdIO->pCmdApi->print)(cmdIoParam, "---------- Interface <%s> ---------- \r\n", TCPIP_STACK_MACIdToString(macID));
        if(!TCPIP_STACK_NetIsUp(netH))
        {
            (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Interface is down\r\n");
            continue;
        }
        hostName = TCPIP_STACK_NetBIOSName(netH); 
#if defined(TCPIP_STACK_USE_NBNS)
        (*pCmdIO->pCmdApi->print)(cmdIoParam, "Host Name: %s - NBNS enabled\r\n", hostName);
#else
        (*pCmdIO->pCmdApi->print)(cmdIoParam, "Host Name: %s - NBNS disabled \r\n", hostName);
#endif  // defined(TCPIP_STACK_USE_NBNS)
        ipAddr.Val = TCPIP_STACK_NetAddress(netH);
        TCPIP_Helper_IPAddressToString(&ipAddr, addrBuff, sizeof(addrBuff));
        (*pCmdIO->pCmdApi->print)(cmdIoParam, "IPv4 Address: %s\r\n", addrBuff);

        ipAddr.Val = TCPIP_STACK_NetMask(netH);
        TCPIP_Helper_IPAddressToString(&ipAddr, addrBuff, sizeof(addrBuff));
        (*pCmdIO->pCmdApi->print)(cmdIoParam, "Mask: %s\r\n", addrBuff);

        ipAddr.Val = TCPIP_STACK_NetAddressGateway(netH);
        TCPIP_Helper_IPAddressToString(&ipAddr, addrBuff, sizeof(addrBuff));
        (*pCmdIO->pCmdApi->print)(cmdIoParam, "Gateway: %s\r\n", addrBuff);

        ipAddr.Val = TCPIP_STACK_NetAddressDnsPrimary(netH);
        TCPIP_Helper_IPAddressToString(&ipAddr, addrBuff, sizeof(addrBuff));
        (*pCmdIO->pCmdApi->print)(cmdIoParam, "DNS: %s\r\n", addrBuff);

        pMac = (const TCPIP_MAC_ADDR*)TCPIP_STACK_NetAddressMac(netH);
        TCPIP_Helper_MACAddressToString(pMac, addrBuff, sizeof(addrBuff));
        (*pCmdIO->pCmdApi->print)(cmdIoParam, "MAC Address: %s\r\n", addrBuff);

        // display IPv6 addresses
#if defined(TCPIP_STACK_USE_IPV6)
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "IPv6 Unicast addresses:\r\n");

        prevHandle = 0;
        do
        {
            nextHandle = TCPIP_STACK_NetIPv6AddressGet(netH, IPV6_ADDR_TYPE_UNICAST, &currIpv6Add, prevHandle);
            if(nextHandle)
            {   // have a valid address; display it
                TCPIP_Helper_IPv6AddressToString(&currIpv6Add.address, addrBuff, sizeof(addrBuff));
                (*pCmdIO->pCmdApi->print)(cmdIoParam, "    %s\r\n", addrBuff);
                prevHandle = nextHandle;
            }
        }while(nextHandle != 0);

        if(prevHandle == 0)
        {   // no valid address
            (*pCmdIO->pCmdApi->msg)(cmdIoParam, "    Unknown\r\n");
        }
        
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "IPv6 Multicast addresses:\r\n");
        prevHandle = 0;
        do
        {
            nextHandle = TCPIP_STACK_NetIPv6AddressGet(netH, IPV6_ADDR_TYPE_MULTICAST, &currIpv6Add, prevHandle);
            if(nextHandle)
            {   // have a valid address; display it
                TCPIP_Helper_IPv6AddressToString(&currIpv6Add.address, addrBuff, sizeof(addrBuff));
                (*pCmdIO->pCmdApi->print)(cmdIoParam, "    %s\r\n", addrBuff);
                prevHandle = nextHandle;
            }
        }while(nextHandle != 0);

        if(prevHandle == 0)
        {   // no valid address
            (*pCmdIO->pCmdApi->msg)(cmdIoParam, "    Unknown\r\n");
        }

#endif  // defined(TCPIP_STACK_USE_IPV6)

        if(TCPIP_DHCP_IsEnabled(netH))
        {
            msgAdd = "dhcp";
        }
        else if(TCPIP_ZCLL_IsEnabled(netH))
        {
            msgAdd = "zcll";
        }
        else if(TCPIP_DHCPS_IsEnabled(netH))
        {
            msgAdd = "dhcps";
        }
        else
        {
            msgAdd = "default IP address";
        }

        (*pCmdIO->pCmdApi->print)(cmdIoParam, "%s is ON\r\n", msgAdd);

        (*pCmdIO->pCmdApi->print)(cmdIoParam, "Link is %s\r\n", TCPIP_STACK_NetIsLinked(netH) ? "UP" : "DOWN");

    }
    return true;
}

#if defined(TCPIP_STACK_USE_DHCP_SERVER)
static int _Command_DHCPLeaseInfo(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv)
{
    TCPIP_NET_HANDLE netH;
    DHCPS_LEASE_HANDLE  prevLease, nextLease;
    DHCPS_LEASE_ENTRY leaseEntry;
    char   addrBuff[20];
const void* cmdIoParam = pCmdIO->cmdIoParam;	

	if (argc != 2)
    {
		(*pCmdIO->pCmdApi->msg)(cmdIoParam, "Usage: dhcpsinfo <interface> \r\n");
		(*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ex: dhcpsinfo PIC32INT \r\n");
		return false;
	}

    netH = TCPIP_STACK_NetHandleGet(argv[1]);
    if (netH == 0)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Unknown interface specified \r\n");
        return false;
    }

	(*pCmdIO->pCmdApi->print)(cmdIoParam,"MAC Address		IPAddress		RemainingLeaseTime \r\n",0);

    prevLease = 0;
    do
    {
        nextLease = TCPIP_DHCPS_LeaseEntryGet(netH, &leaseEntry, prevLease);
		if(!nextLease)
		{
            (*pCmdIO->pCmdApi->print)(cmdIoParam, " \n\r No more entry present \r\n", 0);
		}
        if(nextLease)
        {   // valid info
            // display info
            TCPIP_Helper_MACAddressToString(&leaseEntry.hwAdd, addrBuff, sizeof(addrBuff));
            (*pCmdIO->pCmdApi->msg)(cmdIoParam, addrBuff);
            TCPIP_Helper_IPAddressToString(&leaseEntry.ipAddress, addrBuff, sizeof(addrBuff));
            (*pCmdIO->pCmdApi->print)(cmdIoParam, "	%s ", addrBuff);
            (*pCmdIO->pCmdApi->print)(cmdIoParam, "	%d Secs\r\n", leaseEntry.leaseTime/SYS_TICK_TicksPerSecondGet());

            prevLease = nextLease;
        }
    }while(nextLease != 0);


	return true;

}
#endif  //  defined(TCPIP_STACK_USE_DHCP_SERVER)

static int _Command_DefaultInterfaceSet (_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv)
{
    TCPIP_NET_HANDLE netH;
    const void* cmdIoParam = pCmdIO->cmdIoParam;

    if (argc != 2)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Usage: defnet <interface>\r\n");
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ex: defnet PIC32INT\r\n");
        return false;
    }

    netH = TCPIP_STACK_NetHandleGet(argv[1]);
    if (netH == 0)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Unknown interface specified \r\n");
        return false;
    }

    if(TCPIP_STACK_NetDefaultSet(netH))
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Default interface set successful\r\n");
    }
    else
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Operation not accepted\r\n");
    }

    return true;
}

static int CommandDhcpOptions(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv)
{
    TCPIP_NET_HANDLE netH;
    IPV4_ADDR       reqIpAddr;
    bool            dhcpRes;
    int             opCode = 0;
    const void* cmdIoParam = pCmdIO->cmdIoParam;

    if (argc < 3)
    {
        (*pCmdIO->pCmdApi->print)(cmdIoParam, "Usage: %s <interface> <on/off/renew/request> \r\n", argv[0]);
        (*pCmdIO->pCmdApi->print)(cmdIoParam, "Ex: %s PIC32INT on \r\n", argv[0]);
        return false;
    }

    netH = TCPIP_STACK_NetHandleGet(argv[1]);
    if (netH == 0)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Unknown interface\r\n");
        return false;
    }

    if (strcmp(argv[2], "on") == 0)
    {   // turning on a service
        opCode = 1;
    }
    else if (strcmp(argv[2], "off") == 0)
    {   // turning off a service
        opCode = 2;
    }
    else if (strcmp(argv[2], "renew") == 0)
    {   // DHCP renew
        opCode = 3;
    }
    else if (strcmp(argv[2], "request") == 0)
    {   // DHCP request
        opCode = 4;
        if(argc < 4)
        {
            (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Request needs an IP address\r\n");
            return false;
        }

        if (!TCPIP_Helper_StringToIPAddress(argv[3], &reqIpAddr))
        {
            (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Invalid IP address string \r\n");
            return false;
        }
    }
    else
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Unknown option\r\n");
        return false;
    }


    switch(opCode)
    {
        case 1:
            dhcpRes = TCPIP_DHCP_Enable(netH);
            break;

        case 2:
            dhcpRes = TCPIP_DHCP_Disable(netH);
            break;

        case 3:
            dhcpRes = TCPIP_DHCP_Renew(netH);
            break;

        case 4:
            dhcpRes = TCPIP_DHCP_Request(netH, reqIpAddr);
            break;

        default:
            dhcpRes = false;
            break;
    }

    (*pCmdIO->pCmdApi->print)(cmdIoParam, "%s %s %s\r\n", argv[0], argv[2], dhcpRes ? "succes" : "fail");

    return true;
}

static int _Command_DHCPSOnOff(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv)
{
    return _Command_AddressService(pCmdIO, argc, argv, TCPIP_STACK_ADDRESS_SERVICE_DHCPS);
}

static int _Command_ZcllOnOff(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv)
{
    return _Command_AddressService(pCmdIO, argc, argv, TCPIP_STACK_ADDRESS_SERVICE_ZCLL);
}

static int _Command_AddressService(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv, TCPIP_STACK_ADDRESS_SERVICE_TYPE svcType)
{ 
    typedef bool(*addSvcFnc)(TCPIP_NET_HANDLE hNet);

    TCPIP_NET_HANDLE netH;
    addSvcFnc        addFnc;
    bool             addRes, svcEnable;
    const char       *msgOK, *msgFail;
    const void* cmdIoParam = pCmdIO->cmdIoParam;

    if (argc != 3)
    {
        (*pCmdIO->pCmdApi->print)(cmdIoParam, "Usage: %s <interface> <on/off> \r\n", argv[0]);
        (*pCmdIO->pCmdApi->print)(cmdIoParam, "Ex: %s PIC32INT on \r\n", argv[0]);
        return false;
    }

    netH = TCPIP_STACK_NetHandleGet(argv[1]);
    if (netH == 0)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Unknown interface\r\n");
        return false;
    }

    if (memcmp(argv[2], "on", 2) == 0)
    {   // turning on a service
        svcEnable = true;
    }
    else if (memcmp(argv[2], "off", 2) == 0)
    {   // turning off a service
        svcEnable = false;
    }
    else
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Unknown option\r\n");
        return false;
    }

    switch(svcType)
    {
        case TCPIP_STACK_ADDRESS_SERVICE_DHCPC:
            addFnc = svcEnable?TCPIP_DHCP_Enable:TCPIP_DHCP_Disable;
            break;

        case TCPIP_STACK_ADDRESS_SERVICE_DHCPS:
            addFnc = svcEnable?TCPIP_DHCPS_Enable:TCPIP_DHCPS_Disable;
            break;

        case TCPIP_STACK_ADDRESS_SERVICE_ZCLL:
            addFnc = svcEnable?TCPIP_ZCLL_Enable:TCPIP_ZCLL_Disable;
            break;

        default:
            addFnc = 0;     // unknown service; shouldn't happen
            break;
    }

    if(addFnc)
    {
        msgOK   = svcEnable?"enabled":"disabled";
        msgFail = svcEnable?"enable":"disable";

        addRes = (*addFnc)(netH);
        
        if(addRes)
        {
            (*pCmdIO->pCmdApi->print)(cmdIoParam, "%s %s\r\n", argv[0], msgOK);
        }
        else
        {
            (*pCmdIO->pCmdApi->print)(cmdIoParam, "Failed to %s %s\r\n", msgFail, argv[0]);
        }
    }

    return true;
}

static int _Command_IPAddressSet(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv)
{
    TCPIP_NET_HANDLE netH;
    TCPIP_NET_IF*   pNetIf;
    IPV4_ADDR ipAddr, ipMask;
    IPV4_ADDR*  pMask;
    const void* cmdIoParam = pCmdIO->cmdIoParam;

    if (argc < 3)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Usage: setip <interface> <x.x.x.x> <x.x.x.x>\r\n");
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ex: setip PIC32INT 192.168.0.8 255.255.255.0 \r\n");
        return false;
    }

    netH = TCPIP_STACK_NetHandleGet(argv[1]);
    if (netH == 0)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Unknown interface specified \r\n");
        return false;
    }

    pNetIf = _TCPIPStackHandleToNetUp(netH);
    if(pNetIf == 0)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "No such interface is up\r\n");
        return false;
    }

    if(_TCPIPStackAddressServiceIsRunning(pNetIf) != TCPIP_STACK_ADDRESS_SERVICE_NONE)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "An address service is already running. Stop DHCP, ZCLL, etc. first\r\n");
        return false;
    }

    if (!TCPIP_Helper_StringToIPAddress(argv[2], &ipAddr))
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Invalid IP address string \r\n");
        return false;
    }

    if(argc > 3)
    {   // we have net mask too
        if (!TCPIP_Helper_StringToIPAddress(argv[3], &ipMask))
        {
            (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Invalid IP mask string \r\n");
            return false;
        }
        pMask = &ipMask;
    }
    else
    {
        pMask = 0;
    }

    if(!TCPIP_STACK_NetAddressSet(netH, &ipAddr, pMask, true))
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Set ip address failed\r\n");
        return false;
    }

    return true;
}

static int _Command_GatewayAddressSet(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv)
{
    TCPIP_NET_HANDLE netH;
    IPV4_ADDR ipGateway;
    const void* cmdIoParam = pCmdIO->cmdIoParam;

    if (argc != 3) {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Usage: setgw <interface> <x.x.x.x> \r\n");
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ex: setgw PIC32INT 255.255.255.0 \r\n");
        return false;
    }

    netH = TCPIP_STACK_NetHandleGet(argv[1]);
    if (netH == 0) {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Unknown interface specified \r\n");
        return false;
    }

    if (!TCPIP_Helper_StringToIPAddress(argv[2], &ipGateway)) {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Invalid IP address string \r\n");
        return false;
    }

    if(!TCPIP_STACK_NetAddressGatewaySet(netH, &ipGateway)) {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Set gateway address failed\r\n");
        return false;
    }

    return true;
}

static int _Command_PrimaryDNSAddressSet(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv)
{
    TCPIP_NET_HANDLE netH;
    IPV4_ADDR ipDNS;
    const void* cmdIoParam = pCmdIO->cmdIoParam;

    if (argc != 3) {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Usage: setdns <interface> <x.x.x.x> \r\n");
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ex: setdns PIC32INT 255.255.255.0 \r\n");
        return false;
    }

    netH = TCPIP_STACK_NetHandleGet(argv[1]);
    if (netH == 0) {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Unknown interface specified \r\n");
        return false;
    }

    if (!TCPIP_Helper_StringToIPAddress(argv[2], &ipDNS)) {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Invalid IP address string \r\n");
        return false;
    }

    if(!TCPIP_STACK_NetAddressDnsPrimarySet(netH, &ipDNS)) {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Set DNS address failed\r\n");
        return false;
    }

    return true;
}

static int _Command_BIOSNameSet(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv)
{
    TCPIP_NET_HANDLE netH;
    const char* msg;
    const void* cmdIoParam = pCmdIO->cmdIoParam;

    if (argc != 3)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Usage: setbios <interface> <x.x.x.x> \r\n");
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ex: setbios PIC32INT MCHPBOARD_29 \r\n");
        return false;
    }

    netH = TCPIP_STACK_NetHandleGet(argv[1]);
    if (netH == 0)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Unknown interface specified \r\n");
        return false;
    }

    if(TCPIP_STACK_NetBiosNameSet(netH, argv[2]))
    {
        msg = "Set BIOS Name OK\r\n";
    }
    else
    {
        msg = "Set BIOS Name failed\r\n";
    }

    (*pCmdIO->pCmdApi->msg)(cmdIoParam, msg);
    return true;
}

static int _Command_MACAddressSet(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv)
{
    TCPIP_NET_HANDLE netH;
    TCPIP_MAC_ADDR macAddr;
    const void* cmdIoParam = pCmdIO->cmdIoParam;

    if (argc != 3) {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Usage: setmac <interface> <x:x:x:x:x:x> \r\n");
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ex: setmac PIC32INT aa:bb:cc:dd:ee:ff \r\n");
        return false;
    }

    netH = TCPIP_STACK_NetHandleGet(argv[1]);
    if (netH == 0) {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Unknown interface specified \r\n");
        return false;
    }

    (*pCmdIO->pCmdApi->print)(cmdIoParam, "argv[2]: %s\r\n", argv[2]);

    if (!TCPIP_Helper_StringToMACAddress(argv[2], macAddr.v)) {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Invalid MAC address string \r\n");
        return false;
    }

    if(!TCPIP_STACK_NetAddressMacSet(netH, &macAddr)) {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Set MAC address failed\r\n");
        return false;
    }

    return true;
}


static int _Command_NetworkOnOff(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv)
{
    bool res = false;
    TCPIP_NET_HANDLE netH;
#if defined(TCPIP_STACK_COMMANDS_STORAGE_ENABLE)
    TCPIP_COMMAND_STG_DCPT*   pDcpt;
    TCPIP_NETWORK_CONFIG*     pNetConf;
#endif  // defined(TCPIP_STACK_COMMANDS_STORAGE_ENABLE)
    uint16_t net_ix = 0;
    const void* cmdIoParam = pCmdIO->cmdIoParam;

    if (argc != 3)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Usage: if <interface> <down/up> \r\n");
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ex: if PIC32INT down \r\n");
        return false;
    }

    netH = TCPIP_STACK_NetHandleGet(argv[1]);

    if (netH == 0)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Unknown interface specified \r\n");
        return false;
    }

    net_ix = TCPIP_STACK_NetIndexGet(netH);

    if (memcmp(argv[2], "up", 2) == 0)
    {
        if(TCPIP_STACK_NetIsUp(netH))
        {
            (*pCmdIO->pCmdApi->msg)(cmdIoParam, "This interface already up\r\n");
            return true;
        }

#if defined(TCPIP_STACK_COMMANDS_STORAGE_ENABLE)
        pNetConf = 0;
        if(pCmdStgDcpt) 
        {
            // get the saved network configuration
            pDcpt = pCmdStgDcpt + net_ix;
            if(pDcpt->stgSize)
            {   // saved config is valid; restore
                pNetConf = TCPIP_STACK_NetConfigSet(&pDcpt->netDcptStg, pDcpt->restoreBuff, sizeof(pDcpt->restoreBuff), 0);
                (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Interface up: configuration restored\r\n");
            }
        }
        res = TCPIP_STACK_NetUp(netH, pNetConf);
#else
        res = TCPIP_STACK_NetUp(netH, 0);
#endif  // defined(TCPIP_STACK_COMMANDS_STORAGE_ENABLE)

    }
    else if (memcmp(argv[2], "down", 4) == 0)
    {
        if(TCPIP_STACK_NetIsUp(netH) == 0)
        {
            (*pCmdIO->pCmdApi->msg)(cmdIoParam, "This interface already down\r\n");
            return true;
        }

#if defined(TCPIP_STACK_COMMANDS_STORAGE_ENABLE)
        if(pCmdStgDcpt) 
        {
            // get the last network configuration so we use it when
            // restart the stack/interface 
            pDcpt = pCmdStgDcpt + net_ix;
            pDcpt->stgSize = TCPIP_STACK_NetConfigGet(netH, &pDcpt->netDcptStg, sizeof(pDcpt->netDcptStg), 0);

            (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Interface down: configuration saved\r\n");
        }
#endif  // defined(TCPIP_STACK_COMMANDS_STORAGE_ENABLE)

        res = TCPIP_STACK_NetDown(netH);
    } 
    else
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Wrong parameter specified \r\n");
        return false;
    }

    if (res == true)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Operation successful!\r\n");
    }
    else
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Operation failed!\r\n");
    }

    return true;
}

static int _Command_StackOnOff(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv)
{
#if defined(TCPIP_STACK_COMMANDS_STORAGE_ENABLE)
    TCPIP_NET_HANDLE netH;
    int              netIx;
    TCPIP_COMMAND_STG_DCPT  *pDcpt;
    TCPIP_NETWORK_CONFIG    *pCurrConf, *pDstConf;
#endif  // defined(TCPIP_STACK_COMMANDS_STORAGE_ENABLE)
    TCPIP_NETWORK_CONFIG    *pStackConf;
    const char              *msg;
    const void* cmdIoParam = pCmdIO->cmdIoParam;

    if (argc < 2)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Usage: stack <up/down> <preserve>\r\n");
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ex: stack down preserve\r\n");
        return false;
    }


    if (memcmp(argv[1], "up", 2) == 0)
    {
        pStackConf = 0;
#if defined(TCPIP_STACK_COMMANDS_STORAGE_ENABLE)
        if(pCmdStgDcpt != 0 && pCmdNetConf != 0) 
        {
            // get the saved network configuration
            pDcpt = pCmdStgDcpt + 0;
            pDstConf = pCmdNetConf + 0; 
            pCurrConf = 0;
            for (netIx = 0; netIx < initialNetIfs; netIx++)
            {
                if(pDcpt->stgSize)
                {   // saved config is valid; restore
                    pCurrConf = TCPIP_STACK_NetConfigSet(&pDcpt->netDcptStg, pDcpt->restoreBuff, sizeof(pDcpt->restoreBuff), 0);
                }
                else
                {   // don't have a config to restore
                    pCurrConf = 0;
                }

                if(pCurrConf == 0)
                {   // restore failed
                    break;
                }
                else
                {   // save into array for the stack initialization
                    memcpy(pDstConf, pCurrConf, sizeof(*pDstConf));
                }

                pDcpt++;
                pDstConf++;
            }

            if(pCurrConf)
            {   // success
                pStackConf = pCmdNetConf;
                msg = "Stack up: configuration restored\r\n";
            }
            else
            {
                msg = "Stack up: configuration restore failed\r\n";
            }

            (*pCmdIO->pCmdApi->msg)(cmdIoParam, msg);
        }
#endif  // defined(TCPIP_STACK_COMMANDS_STORAGE_ENABLE)

        (*pCmdIO->pCmdApi->print)(cmdIoParam, "Restarting the stack with %d interfaces\r\n", initialNetIfs);
        if (TCPIP_STACK_Initialize(pStackConf, initialNetIfs, 0, 0) == false)
        {
            msg = "Stack up failed\r\n";
        }
        else
        {
            msg = "Stack up succeeded\r\n";
        }
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, msg);
    }
    else if (memcmp(argv[1], "down", 4) == 0)
    {
#if defined(TCPIP_STACK_COMMANDS_STORAGE_ENABLE)
        tcpipCmdPreserveSavedInfo = false;
        if(argc == 3 && memcmp(argv[2], "preserve", strlen("preserve")) == 0)
        {
            if(pCmdStgDcpt) 
            {
                // get the last network configuration so we use it when
                // restart the stack/interface 
                pDcpt = pCmdStgDcpt + 0;
                for (netIx = 0; netIx < initialNetIfs; netIx++)
                {
                    netH = TCPIP_STACK_IndexToNet(netIx);
                    pDcpt->stgSize = TCPIP_STACK_NetConfigGet(netH, &pDcpt->netDcptStg, sizeof(pDcpt->netDcptStg), 0);
                    pDcpt++;
                }

                (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Stack down: configuration saved\r\n");
                tcpipCmdPreserveSavedInfo = true;
            }
        }
#endif  // defined(TCPIP_STACK_COMMANDS_STORAGE_ENABLE)

        TCPIP_STACK_Deinitialize();
#if defined(TCPIP_STACK_COMMANDS_STORAGE_ENABLE)
        tcpipCmdPreserveSavedInfo = false;          // make sure it doesn't work the next time
#endif  // defined(TCPIP_STACK_COMMANDS_STORAGE_ENABLE)
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Stack down succeeded\r\n");
    }

    return true;
}

static int _Command_HeapInfo(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv)
{
    int     ix, nTraces, nEntries;
    HEAP_TRACE_ENTRY    tEntry;
    const void* cmdIoParam = pCmdIO->cmdIoParam;

    if (argc != 1) {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Usage: heapinfo \r\n");
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ex: heapinfo \r\n");
        return false;
    }

    (*pCmdIO->pCmdApi->print)(cmdIoParam, "Initial created heap size: %d Bytes\r\n", TCPIP_HEAP_Size(initialHeapH));
    (*pCmdIO->pCmdApi->print)(cmdIoParam, "Allocable block heap size: %d Bytes\r\n", TCPIP_HEAP_MaxSize(initialHeapH));
    (*pCmdIO->pCmdApi->print)(cmdIoParam, "All available heap size: %d Bytes\r\n", TCPIP_HEAP_FreeSize(initialHeapH));
    (*pCmdIO->pCmdApi->print)(cmdIoParam, "Last heap error: 0x%x\r\n", TCPIP_HEAP_LastError(initialHeapH));

    nTraces = TCPIP_HEAP_TraceGetEntriesNo(initialHeapH, true);
    if(nTraces)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Trace info: \r\n");
        nEntries = TCPIP_HEAP_TraceGetEntriesNo(initialHeapH, false);
        for(ix = 0; ix < nEntries; ix++)
        {
            if(TCPIP_HEAP_TraceGetEntry(initialHeapH, ix, &tEntry))
            {
                (*pCmdIO->pCmdApi->print)(cmdIoParam, "Module: %4d, totAllocated: %5d, currAllocated: %5d, totFailed: %5d, maxFailed: %5d \r\n", tEntry.moduleId, tEntry.totAllocated, tEntry.currAllocated, tEntry.totFailed, tEntry.maxFailed);
            }
                    
        }
    }
    else
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "No Trace info exists.\r\n");
    }

    return true;
}


#if defined(TCPIP_STACK_USE_ICMP_CLIENT)
static int CommandPing(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv)
{
    const void* cmdIoParam = pCmdIO->cmdIoParam;

    if (argc < 2)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ping Usage: ping <stop> <name/address> <n> <msDelay>\r\n");
        return true;
    }

    if(strcmp(argv[1], "stop") == 0)
    {
        if(icmpCmdStat != TCPIP_PING_CMD_IDLE)
        {
            _PingStop(pCmdIO, cmdIoParam);
        }
        return true;
    }

    if(icmpCmdStat != TCPIP_PING_CMD_IDLE)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ping: command in progress. Retry later.\r\n");
        return true;
    }

    if(TCPIP_Helper_StringToIPAddress(argv[1], &icmpTargetAddr))
    {
        strncpy(icmpTargetAddrStr, argv[1], sizeof(icmpTargetAddrStr));
        icmpTargetHost[0] = '\0';
        icmpCmdStat = TCPIP_PING_CMD_DO_PING;
    }
    else
    {   // assume host address
        if(strlen(argv[1]) > sizeof(icmpTargetHost) - 1)
        {
            (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ping: Host name too long. Retry.\r\n");
            return true;
        }
        strcpy(icmpTargetHost, argv[1]);
        icmpCmdStat = TCPIP_PING_CMD_DNS_GET;
        (*pCmdIO->pCmdApi->print)(cmdIoParam, "Ping: resolving host: %s\r\n", icmpTargetHost);
    }


    if(hIcmp == 0)
    {
        if((hIcmp = TCPIP_ICMP_CallbackRegister(CommandPingHandler)) == 0)
        {
            (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ping: Failed to register ICMP handler\r\n");
            return true;
        }
    }

    icmpSequenceNo = SYS_Rand();
    icmpIdentifier = SYS_Rand();

    icmpReqNo = 0;
    icmpReqDelay = 0;
    if(argc >= 3)
    {
        icmpReqNo = atoi(argv[2]);
    }
    if(argc >= 4)
    {
        icmpReqDelay = atoi(argv[3]);
    }

    if(icmpReqNo == 0)
    {
        icmpReqNo = TCPIP_STACK_COMMANDS_ICMP_ECHO_REQUESTS;
    }
    if(icmpReqDelay == 0)
    {
        icmpReqDelay = TCPIP_STACK_COMMANDS_ICMP_ECHO_REQUEST_DELAY;
    }

    // convert to ticks
    if(icmpReqDelay < TCPIP_COMMAND_ICMP_ECHO_REQUEST_MIN_DELAY)
    {
        icmpReqDelay = TCPIP_COMMAND_ICMP_ECHO_REQUEST_MIN_DELAY;
    }

    pIcmpCmd = pCmdIO;
    icmpCmdIoParam = cmdIoParam; 
    icmpAckRecv = 0;
    icmpReqCount = 0;

    _TCPIPStackAsyncHandlerSetParams(icmptickH, 0, icmpReqDelay);

    return true;

}

static void CommandPingHandler(TCPIP_NET_HANDLE hNetIf, IPV4_ADDR * remoteIP, void * data)
{
    char addBuff[20];

    if(icmpCmdStat == TCPIP_PING_CMD_IDLE)
    {
        return; // not our reply?
    }

    uint16_t* pReply = (uint16_t*)data;
    uint16_t myRecvId = *pReply;
    uint16_t myRecvSequenceNumber = *(pReply + 1);


    if (myRecvSequenceNumber != icmpSequenceNo || myRecvId != icmpIdentifier)
    {
        (*pIcmpCmd->pCmdApi->msg)(icmpCmdIoParam, "Ping: wrong reply received\r\n");
    }
    else
    {
        uint32_t pingTicks = SYS_TICK_Get() - icmpStartTick;
        int pingMs = (pingTicks * 1000) / SYS_TICK_ResolutionGet();
        if(pingMs == 0)
        {
            pingMs = 1;
        }

        TCPIP_Helper_IPAddressToString(remoteIP, addBuff, sizeof(addBuff));

        (*pIcmpCmd->pCmdApi->print)(icmpCmdIoParam, "Ping: reply from %s: time = %dms\r\n", addBuff, pingMs);
        icmpAckRecv++;
    }

}

static void _PingStop(_CMDIO_DEV_NODE* pCmdIO, const void* cmdIoParam)
{
    _TCPIPStackAsyncHandlerSetParams(icmptickH, 0, 0);
    if(icmpCmdStat == TCPIP_PING_CMD_DNS_WAIT)
    {
        TCPIP_DNS_UsageEnd(0);
    }
    icmpCmdStat = TCPIP_PING_CMD_IDLE;
    if(pCmdIO)
    {
        (*pCmdIO->pCmdApi->print)(cmdIoParam, "Ping: done. Sent %d requests, received %d replies.\r\n", icmpReqCount, icmpAckRecv);
    }
    pIcmpCmd = 0;
}


void TCPIPCommandsTask(void)
{
    ICMP_ECHO_RESULT echoRes;
    DNS_RESULT  dnsRes;
    bool killIcmp = false;

    switch(icmpCmdStat)
    {
        case TCPIP_PING_CMD_DNS_GET:

            dnsRes = TCPIP_DNS_UsageBegin(0);
            if(dnsRes == DNS_RES_OK)
            {
                TCPIP_DNS_Resolve(icmpTargetHost, DNS_TYPE_A);
                icmpCmdStat = TCPIP_PING_CMD_DNS_WAIT;
            }
            else if(dnsRes != DNS_RES_BUSY)
            {   // some other error
                (*pIcmpCmd->pCmdApi->print)(icmpCmdIoParam, "Ping: DNS failure for %s\r\n", icmpTargetHost);
                killIcmp = true;
            }
            // else wait some more
            break;

        case TCPIP_PING_CMD_DNS_WAIT:
            dnsRes = TCPIP_DNS_IsResolved(icmpTargetHost, &icmpTargetAddr);
            if(dnsRes == DNS_RES_OK || dnsRes < 0)
            {
                TCPIP_DNS_UsageEnd(0);

                if(dnsRes == DNS_RES_OK)
                {

                    TCPIP_Helper_IPAddressToString(&icmpTargetAddr, icmpTargetAddrStr, sizeof(icmpTargetAddrStr));
                    icmpCmdStat = TCPIP_PING_CMD_DO_PING;
                }
                else
                {
                    (*pIcmpCmd->pCmdApi->print)(icmpCmdIoParam, "Ping: DNS failure for %s\r\n", icmpTargetHost);
                    killIcmp = true;
                }
            }
            // else (dnsRes > 0 ); wait some more
            break;


        case TCPIP_PING_CMD_DO_PING:
            if(icmpReqCount != 0 && icmpAckRecv == 0)
            {   // no reply received; 
                if(SYS_TICK_Get() - icmpStartTick > (SYS_TICK_ResolutionGet() * TCPIP_STACK_COMMANDS_ICMP_ECHO_TIMEOUT) / 1000)
                {   // timeout
                    (*pIcmpCmd->pCmdApi->print)(icmpCmdIoParam, "Ping: request timeout.\r\n");
                    killIcmp = true;
                    break;
                }
                // else wait some more
            }

            if(icmpReqCount == icmpReqNo)
            {   // no more requests to send
                killIcmp = true;
                break;
            }

            // send another request
            echoRes = TCPIP_ICMP_EchoRequestSend (&icmpTargetAddr, ++icmpSequenceNo, icmpIdentifier);

            if(echoRes >= 0 )
            {
                icmpStartTick = SYS_TICK_Get();
                if(icmpReqCount++ == 0)
                {
                    (*pIcmpCmd->pCmdApi->print)(icmpCmdIoParam, "Ping: request sent to: %s [%s]\r\n", icmpTargetHost, icmpTargetAddrStr);
                }
            }
            else
            {
                (*pIcmpCmd->pCmdApi->print)(icmpCmdIoParam, "Ping: failed to send request to: %s\r\n", icmpTargetAddrStr);
                killIcmp = true;
            }

            break;

        default:
            killIcmp = true;
            break;

    }

    if(killIcmp)
    {
        _PingStop(pIcmpCmd, icmpCmdIoParam);
    }

}





#endif  // defined(TCPIP_STACK_USE_ICMP_CLIENT)


static int CommandArp(_CMDIO_DEV_NODE* pCmdIO, int argc, char** argv)
{
    TCPIP_NET_HANDLE netH;
    IPV4_ADDR ipAddr;
    TCPIP_ARP_RESULT  arpRes;
    TCPIP_MAC_ADDR    macAddr;
    char*       message;
    char        addrBuff[20];
    size_t      arpEntries, ix;
    TCPIP_ARP_ENTRY_QUERY arpQuery;

    
    const void* cmdIoParam = pCmdIO->cmdIoParam;

    if (argc < 3)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Usage: arp <interface> <r/q/d/l> <ipAddr> \r\n");
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Ex: arp PIC32INT r 192.168.1.105 \r\n");
        return false;
    }

    netH = TCPIP_STACK_NetHandleGet(argv[1]);
    if (netH == 0)
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Unknown interface\r\n");
        return false;
    }


    if (strcmp(argv[2], "l") == 0)
    {   // list the cache contents
        arpEntries = TCPIP_ARP_CacheEntriesNoGet(netH, ARP_ENTRY_TYPE_TOTAL);
        (*pCmdIO->pCmdApi->print)(cmdIoParam, "arp: %d slots in the cache\r\n", arpEntries);
        for(ix = 0; ix < arpEntries; ix++)
        {
            TCPIP_ARP_EntryQuery(netH, ix, &arpQuery);
            if(arpQuery.entryType == ARP_ENTRY_TYPE_PERMANENT || arpQuery.entryType == ARP_ENTRY_TYPE_COMPLETE)
            {
                TCPIP_Helper_IPAddressToString(&arpQuery.entryIpAdd, addrBuff, sizeof(addrBuff));
                (*pCmdIO->pCmdApi->print)(cmdIoParam, "arp: IPv4 address: %s", addrBuff);
                TCPIP_Helper_MACAddressToString(&arpQuery.entryHwAdd, addrBuff, sizeof(addrBuff));
                (*pCmdIO->pCmdApi->print)(cmdIoParam, ", MAC Address: %s", addrBuff);
                if(arpQuery.entryType == ARP_ENTRY_TYPE_COMPLETE)
                {
                    (*pCmdIO->pCmdApi->msg)(cmdIoParam, ", complete\r\n");
                }
                else
                {
                    (*pCmdIO->pCmdApi->msg)(cmdIoParam, ", permanent\r\n");
                }
            }
            else if(arpQuery.entryType == ARP_ENTRY_TYPE_INCOMPLETE)
            {
                TCPIP_Helper_IPAddressToString(&arpQuery.entryIpAdd, addrBuff, sizeof(addrBuff));
                (*pCmdIO->pCmdApi->print)(cmdIoParam, "arp: IPv4 address: %s, queued\r\n", addrBuff);
            }
        }

        return false;
    }

    if (argc < 4 || !TCPIP_Helper_StringToIPAddress(argv[3], &ipAddr))
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "Invalid IP address string \r\n");
        return false;
    }

    if (strcmp(argv[2], "r") == 0)
    {   // request an address
        arpRes = TCPIP_ARP_EntryGet(netH, &ipAddr, &macAddr, true);
        switch(arpRes)
        {
            case ARP_RES_ENTRY_SOLVED:

                TCPIP_Helper_MACAddressToString(&macAddr, addrBuff, sizeof(addrBuff));
                (*pCmdIO->pCmdApi->print)(cmdIoParam, "arp: resolved - IPv4 address: %s, MAC Address: %s\r\n", argv[3], addrBuff);
                return false;

            case ARP_RES_ENTRY_QUEUED:
                message = "arp: address already queued\r\n";
                break;

            case ARP_RES_ENTRY_NEW:
                message = "arp: address newly queued\r\n";
                break;

            default:    // ARP_RES_CACHE_FULL  
                message = "arp: queue full/error\r\n";
                break;
        }
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, message);
    }
    else if (strcmp(argv[2], "q") == 0)
    {   // query for an address
        arpRes = TCPIP_ARP_EntryGet(netH, &ipAddr, &macAddr, false);
        if(arpRes == ARP_RES_OK)
        {
            TCPIP_Helper_MACAddressToString(&macAddr, addrBuff, sizeof(addrBuff));
            (*pCmdIO->pCmdApi->print)(cmdIoParam, "arp: IPv4 address: %s, MAC Address: %s\r\n", argv[3], addrBuff);
        }
        else
        {
            (*pCmdIO->pCmdApi->msg)(cmdIoParam, "arp: no such entry\r\n");
        }
    }
    else if (strcmp(argv[2], "d") == 0)
    {   // delete an address
        arpRes = TCPIP_ARP_EntryRemove(netH, &ipAddr);
        if(arpRes == ARP_RES_OK)
        {
            (*pCmdIO->pCmdApi->print)(cmdIoParam, "arp: removed %s\r\n", argv[3]);
        }
        else
        {
            (*pCmdIO->pCmdApi->msg)(cmdIoParam, "arp: no such entry\r\n");
        }
    }
    else
    {
        (*pCmdIO->pCmdApi->msg)(cmdIoParam, "arp: Unknown option\r\n");
    }


    return false;
}


#endif    // defined(TCPIP_STACK_COMMAND_ENABLE)


