#ifndef ZERO_CONF_LL_PRIVATE_H
#define ZERO_CONF_LL_PRIVATE_H

#include <stdint.h>

// access to low level ARP definitions
#include "arp_private.h"

#include "zero_conf_helper.h"

void info_zcll_print(char * msg);
void debug_zcll_print(char * msg);
void info_mdns_print(char * msg);
void debug_mdns_print(char * msg);

// For verbose debugging
#ifdef DEBUG_MDNS
#define DEBUG_MDNS_PRINT(x) debug_mdns_print(x)
#define DEBUG_MDNS_MESG     sprintf
#else
#define DEBUG_MDNS_PRINT(x)
#define DEBUG_MDNS_MESG(x,y,...)      
#endif

// For less verbose debugging
#ifdef INFO_MDNS
#define INFO_MDNS_PRINT(x) info_mdns_print(x)
#define INFO_MDNS_MESG     sprintf
#else
#define INFO_MDNS_PRINT(x)
#define INFO_MDNS_MESG(x,y,...)      
#endif

// For warnings, errors, and other exceptions
#ifdef WARN_MDNS
#define WARN_MDNS_PRINT(x) SYS_CONSOLE_MESSAGE(x)
#define WARN_MDNS_MESG     sprintf
#else
#define WARN_MDNS_PRINT(x)
#define WARN_MDNS_MESG(x,y,...)      
#endif

// Always print
#define MDNS_PRINT(x) SYS_CONSOLE_MESSAGE(x)
#define MDNS_MESG     sprintf

#define DEBUG0_MDNS_PRINT  INFO_MDNS_PRINT
#define DEBUG0_MDNS_MESG   INFO_MDNS_MESG



// For verbose debugging
#ifdef DEBUG_ZCLL
#define DEBUG_ZCLL_PRINT(x) debug_zcll_print(x)
#define DEBUG_ZCLL_MESG     sprintf
#else
#define DEBUG_ZCLL_PRINT(x)
#define DEBUG_ZCLL_MESG(x,y,...) 
#endif

// For less verbose debugging
#ifdef INFO_ZCLL
#define INFO_ZCLL_PRINT(x) info_zcll_print(x)
#define INFO_ZCLL_MESG     sprintf
#else
#define INFO_ZCLL_PRINT(x)
#define INFO_ZCLL_MESG(x,y,...) 
#endif

// For warnings, errors, and other exceptions
#ifdef WARN_ZCLL
#define WARN_ZCLL_PRINT(x) SYS_CONSOLE_MESSAGE(x)
#define WARN_ZCLL_MESG     sprintf
#else
#define WARN_ZCLL_PRINT(x)
#define WARN_ZCLL_MESG(x,y,...) 
#endif

// Always print
#define ZCLL_PRINT(x) SYS_CONSOLE_MESSAGE(x)
#define ZCLL_MESG     sprintf

#define DEBUG0_ZCLL_PRINT  DEBUG_ZCLL_PRINT
#define DEBUG0_ZCLL_MESG   DEBUG_ZCLL_MESG

/* ARP  States Enum */
typedef enum
{
   ZCLL_ARP_PROBE = 0,// Par 2.1.1 RFC 5227.
   ZCLL_ARP_CLAIM,    //
   ZCLL_ARP_DEFEND    //Par 2.4 RFC 5227
} ZCLL_ARP_STATE;     // Zero Config Local Link




/* constants from RFC 2937, section 9. ALso found in RFC 5227 Par 1.1*/
#define PROBE_WAIT           1 /*second  (initial random delay)              */
#define PROBE_MIN            1 /*second  (minimum delay till repeated probe) */
#define PROBE_MAX            2 /*seconds (maximum delay till repeated probe) */
#define PROBE_NUM            3 /*         (number of probe packets)          */
#define ANNOUNCE_WAIT        2 /*seconds  (delay before announcing)          */
#define ANNOUNCE_NUM         2 /*        (number of announcement packets)    */
#define ANNOUNCE_INTERVAL    2 /*seconds (time between announcement packets) */
#define MAX_CONFLICTS       10 /*        (max conflicts before rate limiting)*/
#define RATE_LIMIT_INTERVAL 60 /*seconds (delay between successive attempts) */
#define DEFEND_INTERVAL     10 /*seconds (min. wait between defensive ARPs)  */

/* compilation constants */
#define IPV4_LLBASE         0xa9fe0100 /* 169.254.1.0 */
#define IPV4_LLBASE_MASK    0x0000FFFF /* corresponding network mask */



/* Link-Local States Enum */
typedef enum 
{
   SM_INIT = 0,
   SM_ADDR_INIT,
   SM_ADDR_PROBE,
   SM_ADDR_CLAIM,
   SM_ADDR_DEFEND,
   SM_ADDR_RELEASE,
} ZCLL_STATE;


/* ARP-Packet Types defined in RFC 2937 */
typedef enum
{
	ARP_REQUEST_TYPE = 0,
	ARP_PROBE_TYPE,
	ARP_CLAIM_TYPE,
	ARP_DEFEND_TYPE,
	ARP_RESPONSE_TYPE,
	UNKNOWN_TYPE,
}ARP_PKT_TYPE;


/* Flags for the ZCLL State Machine */
typedef union
{
    struct
    {
        uint8_t probe_conflict  : 1 ;     // Conflict When selecting IP-addr
        uint8_t late_conflict   : 1;      // Conflict When using IP-addr
        uint8_t defended        : 1;      // whether or not defended earlier
        //
        uint8_t reserved        : 5;        // not used
    };
    uint8_t Val;
}ZCLL_FLAGS;

typedef struct 
{
    SYS_TICK    event_time; // Internal Timer, to keep track of events
    SYS_TICK    random_delay;
    ZCLL_STATE  zcll_state;
    IPV4_ADDR   temp_IP_addr;   // Temporary IP address before checking uniquness
    uint8_t     time_recorded; // Flag to indicate event_time is loaded
    uint8_t     probe_count;
    uint8_t     conflict_count;
    uint8_t     announce_count;
    TCPIP_MAC_ADDR    temp_MAC_addr;   // Temporary MAC address
    ZCLL_FLAGS  zcll_flags;
    uint8_t     bDefaultIPTried;
    int8_t      arpRegId;
} ZCLL_NET_HANDLE;



void TCPIP_ZCLL_ARPAction(TCPIP_NET_HANDLE hNet
              ,IPV4_ADDR *SrcIPAddr
              ,IPV4_ADDR *DestIPAddr
              ,TCPIP_ARP_OPERATION_TYPE op_req
              ,ZCLL_ARP_STATE arp_action);

#endif
