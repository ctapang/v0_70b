/*******************************************************************************
  WiFi MAC interface functions

  File Name:
    drv_wifi_mac.h

  Summary:
   WiFi-specific MAC function prototypes called by TCP/IP stack.

  Description:
    The functions in this header file are accessed by the TCP/IP stack via
    function pointers.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright © 2012 released Microchip Technology Inc. All rights reserved.

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

#ifndef _DRV_WIFI_H
#define _DRV_WIFI_H


#include <stdint.h>
#include <stdbool.h>

#if 0
// debug, remove later
#define PA6_IO                LATAbits.LATA6
#define PA6_TRISTATE          TRISAbits.TRISA6
#define SET_PA6_AS_OUTPUT()   TRISAbits.TRISA6 = 0
#endif


// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************


// WiFi Driver Version Number
#define DRV_WIFI_VERSION_NUMBER                 "3.0.0"

#define DRV_WIFI_MAX_SSID_LENGTH                (32)
#define DRV_WIFI_BSSID_LENGTH                   (6)
#define DRV_WIFI_RETRY_FOREVER                  (255)
#define DRV_WIFI_RETRY_ADHOC                    (3)

#define DRV_WIFI_MAX_CHANNEL_LIST_LENGTH        (14)
#define DRV_WIFI_MAX_SECURITY_KEY_LENGTH        (64)

#define DRV_WIFI_RTS_THRESHOLD_MAX              (2347) /* maximum RTS threshold size in bytes */
#define DRV_WIFI_MAX_NUM_RATES                  (8)

/* Key size defines */
#define DRV_WIFI_MIN_WPA_PASS_PHRASE_LENGTH     (8)
#define DRV_WIFI_MAX_WPA_PASS_PHRASE_LENGTH     (64)  // must include string terminator
#define DRV_WIFI_MAX_WPA2_PASS_PHRASE_LENGTH    (64)
#define DRV_WIFI_WPA_KEY_LENGTH                 (32)
#define DRV_WIFI_WPA2_KEY_LENGTH                (32)

// WEP key lengths
#define DRV_WIFI_WEP40_KEY_LENGTH               (20)        // 4 keys of 5 bytes each
#define DRV_WIFI_WEP104_KEY_LENGTH              (52)        // 4 keys of 13 bytes each
#define DRV_WIFI_MAX_WEP_KEY_LENGTH             (DRV_WIFI_WEP104_KEY_LENGTH)

// WPS PIN Length
#define WF_WPS_PIN_LENGTH                       8

// eventInfo define for DRV_WIFI_ProcessEvent() when no additional info is supplied
#define DRV_WIFI_NO_ADDITIONAL_INFO             ((uint16_t)0xffff)

// *****************************************************************************
/*  WEP Key Types

  Summary:
    Selections for WEP key type when using WEP security.

  Description
    This enumeration identifies the choices for the WEP key type when using
    WEP security.  The recommended key type (and default) is Open key.
*/

typedef enum
{
    /* use WEP shared key */
    DRV_WIFI_SECURITY_WEP_SHAREDKEY = 0,

    /* use WEP open key (default) */
    DRV_WIFI_SECURITY_WEP_OPENKEY   = 1        
} DRV_WIFI_WEP_KEY_TYPE;


// *****************************************************************************
/*  Mgmt Msg Error Codes

  Summary:
    Error codes returned when a mgmt message is sent to the MRF24W

  Description
    This enumeration identifies the errors that can occur when a DRV_WIFI API
    function call results in a mgmt message being sent, via SPI, to the MRF24W.
*/

typedef enum
{
    DRV_WIFI_SUCCESS                                              = 1,
    DRV_WIFI_ERROR_INVALID_SUBTYPE                                = 2,
    DRV_WIFI_ERROR_OPERATION_CANCELLED                            = 3,
    DRV_WIFI_ERROR_FRAME_END_OF_LINE_OCCURRED                     = 4,
    DRV_WIFI_ERROR_FRAME_RETRY_LIMIT_EXCEEDED                     = 5,
    DRV_WIFI_ERROR_EXPECTED_BSS_VALUE_NOT_IN_FRAME                = 6,
    DRV_WIFI_ERROR_FRAME_SIZE_EXCEEDS_BUFFER_SIZE                 = 7,
    DRV_WIFI_ERROR_FRAME_ENCRYPT_FAILED                           = 8,
    DRV_WIFI_ERROR_INVALID_PARAM                                  = 9,
    DRV_WIFI_ERROR_AUTH_REQ_ISSUED_WHILE_IN_AUTH_STATE            = 10,
    DRV_WIFI_ERROR_ASSOC_REQ_ISSUED_WHILE_IN_ASSOC_STATE          = 11,
    DRV_WIFI_ERROR_INSUFFICIENT_RESOURCES                         = 12,
    DRV_WIFI_ERROR_TIMEOUT_OCCURRED                               = 13,
    DRV_WIFI_ERROR_BAD_EXCHANGE_ENCOUNTERED_IN_FRAME_RECEPTION    = 14,
    DRV_WIFI_ERROR_AUTH_REQUEST_REFUSED                           = 15,
    DRV_WIFI_ERROR_ASSOCIATION_REQUEST_REFUSED                    = 16,
    DRV_WIFI_ERROR_PRIOR_MGMT_REQUEST_IN_PROGRESS                 = 17,
    DRV_WIFI_ERROR_NOT_IN_JOINED_STATE                            = 18,
    DRV_WIFI_ERROR_NOT_IN_ASSOCIATED_STATE                        = 19,
    DRV_WIFI_ERROR_NOT_IN_AUTHENTICATED_STATE                     = 20,
    DRV_WIFI_ERROR_SUPPLICANT_FAILED                              = 21,
    DRV_WIFI_ERROR_UNSUPPORTED_FEATURE                            = 22,
    DRV_WIFI_ERROR_REQUEST_OUT_OF_SYNC                            = 23,
    DRV_WIFI_ERROR_CP_INVALID_ELEMENT_TYPE                        = 24,
    DRV_WIFI_ERROR_CP_INVALID_PROFILE_ID                          = 25,
    DRV_WIFI_ERROR_CP_INVALID_DATA_LENGTH                         = 26,
    DRV_WIFI_ERROR_CP_INVALID_SSID_LENGTH                         = 27,
    DRV_WIFI_ERROR_CP_INVALID_SECURITY_TYPE                       = 28,
    DRV_WIFI_ERROR_CP_INVALID_SECURITY_KEY_LENGTH                 = 29,
    DRV_WIFI_ERROR_CP_INVALID_WEP_KEY_ID                          = 30,
    DRV_WIFI_ERROR_CP_INVALID_NETWORK_TYPE                        = 31,
    DRV_WIFI_ERROR_CP_INVALID_ADHOC_MODE                          = 32,
    DRV_WIFI_ERROR_CP_INVALID_SCAN_TYPE                           = 33,
    DRV_WIFI_ERROR_CP_INVALID_CP_LIST                             = 34,
    DRV_WIFI_ERROR_CP_INVALID_CHANNEL_LIST_LENGTH                 = 35,
    DRV_WIFI_ERROR_NOT_CONNECTED                                  = 36,
    DRV_WIFI_ERROR_ALREADY_CONNECTING                             = 37,
    
    /* Disconnect failed. Disconnect is allowed only when module is in connected state */
    DRV_WIFI_ERROR_DISCONNECT_FAILED                              = 38,

     /*  No stored scan results */
    DRV_WIFI_ERROR_NO_STORED_BSS_DESCRIPTOR                       = 39, 
    DRV_WIFI_ERROR_INVALID_MAX_POWER                              = 40,
    DRV_WIFI_ERROR_CONNECTION_TERMINATED                          = 41,
    DRV_WIFI_ERROR_HOST_SCAN_NOT_ALLOWED                          = 42, // Host Scan Failed. Host scan is allowed only in idle or connected state
    DRV_WIFI_ERROR_INVALID_WPS_PIN                                = 44  // WPS pin was invalid
} DRV_WIFI_MGMT_ERRORS;

typedef enum
{
    DRV_WIFI_ERROR_IN_HIBERNATE_MODE                              = 100  // invalid operation while MRF24WG is in hibernate mode
} DRV_WIFI_GENERAL_ERRORS;

// *****************************************************************************
/*  Tx Modes

  Summary:
    Selections for WiFi Tx mode

  Description
    This enumeration identifies the choices the MRF24W Tx mode.  It is recommended
    to use the DRV_WIFI_TXMODE_G_RATES for best performance.  See DRV_WIFI_TxModeSet().
*/

typedef enum
{
    /* Use 802.11 'g' rates */
    DRV_WIFI_TXMODE_G_RATES      = 0,

    /* Use only 802.11 'b' rates */
    DRV_WIFI_TXMODE_B_RATES      = 1,

    /* Use only 1 and 2 mbps rates */
    DRV_WIFI_TXMODE_LEGACY_RATES = 2
} DRV_WIFI_TX_MODES;


// *****************************************************************************
/*  Multicast Filter ID's

  Summary:
    Selections for software Multicast filter ID's

  Description
    This enumeration identifies the multicast filters that can be selected.  See
    DRV_WIFI_SWMulticastFilterSet().
*/

typedef enum
{
    DRV_WIFI_MULTICAST_FILTER_1       = 4,
    DRV_WIFI_MULTICAST_FILTER_2       = 5,
    DRV_WIFI_MULTICAST_FILTER_3       = 6,
    DRV_WIFI_MULTICAST_FILTER_4       = 7,
    DRV_WIFI_MULTICAST_FILTER_5       = 8,
    DRV_WIFI_MULTICAST_FILTER_6       = 9,
    DRV_WIFI_MULTICAST_FILTER_7       = 10,
    DRV_WIFI_MULTICAST_FILTER_8       = 11,
    DRV_WIFI_MULTICAST_FILTER_9       = 12,
    DRV_WIFI_MULTICAST_FILTER_10      = 13,
    DRV_WIFI_MULTICAST_FILTER_11      = 14,
    DRV_WIFI_MULTICAST_FILTER_12      = 15,
    DRV_WIFI_MULTICAST_FILTER_13      = 16,
    DRV_WIFI_MULTICAST_FILTER_14      = 17,
    DRV_WIFI_MULTICAST_FILTER_15      = 18,
    DRV_WIFI_MULTICAST_FILTER_16      = 19
} DRV_WIFI_MULTICAST_FILTER_IDS;


// *****************************************************************************
/*  Multicast Filter Modes

  Summary:
    Selections for Software Multicast Filters.

  Description
    This enumeration identifies the mode of multicast filters that can be selected.
    See DRV_WIFI_SWMulticastFilterSet().
*/

typedef enum
{
    /* Discard all received multicast messages */
    DRV_WIFI_MULTICAST_DISABLE_ALL  = 0,

    /* forward all multicast messages to host MCU */
    DRV_WIFI_MULTICAST_ENABLE_ALL   = 1,

    /* Use the MAC filtering capability for multicast messages*/
    DRV_WIFI_MULTICAST_USE_FILTERS  = 2
} DRV_WIFI_MULTICAST_FILTERS;

#define DRV_WIFI_DEAUTH_REASONCODE_MASK       ((uint8_t)0x80)
#define DRV_WIFI_DISASSOC_REASONCODE_MASK     ((uint8_t)0x40)


// *****************************************************************************
/*  WiFi Events

  Summary:
    Selections for events that can occur.

  Description
    This enumeration identifies the WiFi events that can occur and will be sent
    to DRV_WIFI_ProcessEvent().
*/

typedef enum
{
    /* No event has occurred */
    DRV_WIFI_EVENT_NONE                           = 0,
            
    /* Connection attempt to network successful */
    DRV_WIFI_EVENT_CONNECTION_SUCCESSFUL          = 1,

    /* Connection attempt failed */
    DRV_WIFI_EVENT_CONNECTION_FAILED              = 2,
    
    /* Connection lost; MRF24W attempting to reconnect  */
    DRV_WIFI_EVENT_CONNECTION_TEMPORARILY_LOST    = 3,

    /* Connection lost; MRF24W no longer trying to connect */
    DRV_WIFI_EVENT_CONNECTION_PERMANENTLY_LOST    = 4,
    
    /* Connection has been reestablished */
    DRV_WIFI_EVENT_CONNECTION_REESTABLISHED       = 5,

    /* Update to FLASH successful */
    DRV_WIFI_EVENT_FLASH_UPDATE_SUCCESSFUL        = 6,   

    /* Update to FLASH failed */
    DRV_WIFI_EVENT_FLASH_UPDATE_FAILED            = 7,   

    /* Key calculation is required */
    DRV_WIFI_EVENT_KEY_CALCULATION_REQUEST        = 8,   

    /* scan results are ready */
    DRV_WIFI_EVENT_SCAN_RESULTS_READY             = 9,   

    /* IE data ready */
    DRV_WIFI_EVENT_IE_RESULTS_READY               = 10,  

    /* Invalid WPS pin was entered */
    DRV_WIFI_EVENT_INVALID_WPS_PIN                = 12,  

    /* Client connection events */
    DRV_WIFI_EVENT_SOFT_AP                        = 13,  

    /* Disconnect done event */
    DRV_WIFI_EVENT_DISCONNECT_DONE                = 14,  

    /* WiFi error event occurred */
    DRV_WIFI_EVENT_ERROR                          = 15   
} DRV_WIFI_EVENTS;


// *****************************************************************************
/*  WiFi Scan Context default settings

  Summary:
    Default values for WiFi scan context

  Description
    This enumeration identifies the default WiFi scan context values that can be used
    in the DRV_WIFI_SCAN_CONTEXT structure.
*/

#define DRV_WIFI_DEFAULT_SCAN_COUNT                   (1)
#define DRV_WIFI_DEFAULT_SCAN_MIN_CHANNEL_TIME        (200)   // ms
#define DRV_WIFI_DEFAULT_SCAN_MAX_CHANNEL_TIME        (400)   // ms
#define DRV_WIFI_DEFAULT_SCAN_PROBE_DELAY             (20)    // us


// *****************************************************************************
/*  WiFi PS-Poll Listen Interval default settings

  Summary:
    Default values for WiFi PS PS-Poll Listen Interval settings

  Description
    These defines identify various default WiFi PS-Poll settings that can
    be used in the DRV_WIFI_PS_POLL_CONTEXT structure.
*/

#define DRV_WIFI_DEFAULT_PS_LISTEN_INTERVAL           ((uint16_t)1)       // 100ms multiplier, e.g. 1 * 100ms = 100ms
#define DRV_WIFI_DEFAULT_PS_DTIM_INTERVAL             ((uint16_t)2)       // number of beacon periods
#define DRV_WIFI_DEFAULT_PS_DTIM_ENABLED              true                // DTIM wake-up enabled (normally the case)



// *****************************************************************************
/*  WiFi AdHoc default settings

  Summary:
    Default values for WiFi AdHoc settings

  Description
    These defines identify various default WiFi AdHoc settings that can
    be used in the DRV_WIFI_ADHOC_NETWORK_CONTEXT structure.
*/

#define DRV_WIFI_DEFAULT_ADHOC_HIDDEN_SSID            false
#define DRV_WIFI_DEFAULT_ADHOC_BEACON_PERIOD          (100)   // ms
#define DRV_WIFI_DEFAULT_ADHOC_MODE                   DRV_WIFI_ADHOC_CONNECT_THEN_START

// see DRV_WIFI_SecurityWepSet() and DRV_WIFI_WEP_CONTEXT
#define DRV_WIFI_DEFAULT_WEP_KEY_TYPE                 DRV_WIFI_SECURITY_WEP_OPENKEY


// *****************************************************************************
/*  AdHoc Modes

  Summary:
    Selection of different AdHoc connection modes

  Description
    This enumeration identifies the AdHoc modes that can be selelcted when
    connecting in AdHoc mode.
*/
typedef enum adhocMode
{
    DRV_WIFI_ADHOC_CONNECT_THEN_START = 0,  // try to connect existing AdHoc network, if not found then start network
    DRV_WIFI_ADHOC_CONNECT_ONLY       = 1,  // only connect to existing AdHoc network
    DRV_WIFI_ADHOC_START_ONLY         = 2   // only start a new AdHoc network
} DRV_WIFI_ADHOC_MODES;

// *****************************************************************************
/*  WiFi Network Types

  Summary:
    Selection of different WiFi network types

  Description
    This enumeration identifies the WiFi network types that can be selected.
    Do NOT make these an enumerated type as they are used as a compile switch.
*/

#define DRV_WIFI_NETWORK_TYPE_INFRASTRUCTURE          (1)
#define DRV_WIFI_NETWORK_TYPE_ADHOC                   (2)
#define DRV_WIFI_NETWORK_TYPE_P2P                     (3)     /* not supported */
#define DRV_WIFI_NETWORK_TYPE_SOFT_AP                 (4)


// *****************************************************************************
/*  WiFi Security Types

  Summary:
    Selection of different WiFi security types

  Description
    This enumeration identifies the WiFi security types that can be selected.
    Do NOT make these an enumerated type as they are used as a compile switch.
*/

#define DRV_WIFI_SECURITY_OPEN                        (0)
#define DRV_WIFI_SECURITY_WEP_40                      (1)
#define DRV_WIFI_SECURITY_WEP_104                     (2)
#define DRV_WIFI_SECURITY_WPA_WITH_KEY                (3)
#define DRV_WIFI_SECURITY_WPA_WITH_PASS_PHRASE        (4)
#define DRV_WIFI_SECURITY_WPA2_WITH_KEY               (5)
#define DRV_WIFI_SECURITY_WPA2_WITH_PASS_PHRASE       (6)
#define DRV_WIFI_SECURITY_WPA_AUTO_WITH_KEY           (7)
#define DRV_WIFI_SECURITY_WPA_AUTO_WITH_PASS_PHRASE   (8)
#define DRV_WIFI_SECURITY_WPS_PUSH_BUTTON             (9)
#define DRV_WIFI_SECURITY_WPS_PIN                     (10)
#define DRV_WIFI_SECURITY_EAP                         (11)

#define DRV_WIFI_WPS_PIN_LENGTH                       (8)         // 7 digits + checksum byte

// *****************************************************************************
/*  WiFi Scan Types

  Summary:
    Selection of different WiFi scan types

  Description
    This enumeration identifies the WiFi scan types that can be selected.
*/

typedef enum
{
    DRV_WIFI_ACTIVE_SCAN  = 1,
    DRV_WIFI_PASSIVE_SCAN = 2
} DRV_WIFI_SCAN_TYPES;


// *****************************************************************************
/*  WiFi Reconnect Modes

  Summary:
    Selection of different Reconnection modes

  Description
    This enumeration identifies the reconnection modes that can be used in
    DRV_WIFI_ReconnectModeSet().
*/

typedef enum
{
    DRV_WIFI_DO_NOT_ATTEMPT_TO_RECONNECT = 0,
    DRV_WIFI_ATTEMPT_TO_RECONNECT        = 1
} DRV_WIFI_RECONNECT_MODES;


// Do not make this an enumerated type!
#define DRV_WIFI_DISABLED     (0)
#define DRV_WIFI_ENABLED      (1)

typedef enum
{
    DRV_WIFI_WPS_AUTH_OPEN       = 0x01,
    DRV_WIFI_WPS_AUTH_WPA_PSK    = 0x02,
    DRV_WIFI_WPS_AUTH_SHARED     = 0x04,
    DRV_WIFI_WPS_AUTH_WPA        = 0x08,
    DRV_WIFI_WPS_AUTH_WPA2       = 0x10,
    DRV_WIFI_WPS_AUTH_WPA2_PSK   = 0x20
} DRV_WIFI_WPS_AUTH_TYPES;

typedef enum
{
    DRV_WIFI_WPS_ENC_NONE        = 0x01,
    DRV_WIFI_WPS_ENC_WEP         = 0x02,
    DRV_WIFI_WPS_ENC_TKIP        = 0x04,
    DRV_WIFI_ENC_AES             = 0x08
} DRV_WIFI_WPS_ENCODE_TYPES;


// *****************************************************************************
/*  EventInfo types

  Summary:
    Selection of different EventInfo types

  Description
    This enumeration identifies the eventInfo types used in DRV_WIFI_ProcessEvent(),
    case DRV_WIFI_EVENT_CONNECTION_FAILED.
*/

typedef enum
{
    DRV_WIFI_JOIN_FAILURE                         = 2,
    DRV_WIFI_AUTHENTICATION_FAILURE               = 3,
    DRV_WIFI_ASSOCIATION_FAILURE                  = 4,
    DRV_WIFI_WEP_HANDSHAKE_FAILURE                = 5,
    DRV_WIFI_PSK_CALCULATION_FAILURE              = 6,
    DRV_WIFI_PSK_HANDSHAKE_FAILURE                = 7,
    DRV_WIFI_ADHOC_JOIN_FAILURE                   = 8,
    DRV_WIFI_SECURITY_MISMATCH_FAILURE            = 9,
    DRV_WIFI_NO_SUITABLE_AP_FOUND_FAILURE         = 10,
    DRV_WIFI_RETRY_FOREVER_NOT_SUPPORTED_FAILURE  = 11,
    DRV_WIFI_LINK_LOST                            = 12,
    DRV_WIFI_TKIP_MIC_FAILURE                     = 13,
    DRV_WIFI_RSN_MIXED_MODE_NOT_SUPPORTED         = 14,
    DRV_WIFI_RECV_DEAUTH                          = 15,
    DRV_WIFI_RECV_DISASSOC                        = 16,
    DRV_WIFI_WPS_FAILURE                          = 17,
    DRV_WIFI_P2P_FAILURE                          = 18      /* not supported */
} DRV_WIFI_EVENT_INFO;


// *****************************************************************************
/*  Deauth/Disassociate Reason Codes

  Summary:
    Selection of different codes when a deauth or disassociation event has occurred.

  Description
    This enumeration identifies the reason codes for a connection lost due to a
    deauthorization or disassociation from the AP.
*/

typedef enum
{
    DRV_WIFI_UNSPECIFIED                          = 1,
    DRV_WIFI_REASON_PREV_AUTH_NOT_VALID           = 2,
    DRV_WIFI_DEAUTH_LEAVING                       = 3,
    DRV_WIFI_DISASSOC_DUE_TO_INACTIVITY           = 4,
    DRV_WIFI_DISASSOC_AP_BUSY                     = 5,
    DRV_WIFI_CLASS2_FRAME_FROM_NONAUTH_STA        = 6,
    DRV_WIFI_CLASS3_FRAME_FROM_NONASSOC_STA       = 7,
    DRV_WIFI_DISASSOC_STA_HAS_LEFT                = 8,
    DRV_WIFI_STA_REQ_ASSOC_WITHOUT_AUTH           = 9,
    DRV_WIFI_INVALID_IE                           = 13,
    DRV_WIFI_MIC_FAILURE                          = 14,
    DRV_WIFI_4WAY_HANDSHAKE_TIMEOUT               = 15,
    DRV_WIFI_GROUP_KEY_HANDSHAKE_TIMEOUT          = 16,
    DRV_WIFI_IE_DIFFERENT                         = 17,
    DRV_WIFI_INVALID_GROUP_CIPHER                 = 18,
    DRV_WIFI_INVALID_PAIRWISE_CIPHER              = 19,
    DRV_WIFI_INVALID_AKMP                         = 20,
    DRV_WIFI_UNSUPP_RSN_VERSION                   = 21,
    DRV_WIFI_INVALID_RSN_IE_CAP                   = 22,
    DRV_WIFI_IEEE8021X_FAILED                     = 23,
    DRV_WIFI_CIPHER_SUITE_REJECTED                = 24
} DRV_WIFI_REASON_CODES;

// *****************************************************************************
/*  'Connection Temporarily Lost' event codes

  Summary:
    Selection of different codes when WiFi connection is temporarily lost.

  Description
    This enumeration identifies the codes for a connection temporarily lost.  These
    codes are used in DRV_WIFI_ProcessEvent(), case DRV_WIFI_EVENT_CONNECTION_TEMPORARILY_LOST.
*/
typedef enum
{
    /* connection temporarily lost due to beacon timeout */
    DRV_WIFI_BEACON_TIMEOUT                       = 1,

    /* connection temporarily lost due to deauth received from AP */
    DRV_WIFI_DEAUTH_RECEIVED                      = 2,

    /* connection temporarily lost due to disassociation received from AP */
    DRV_WIFI_DISASSOCIATE_RECEIVED                = 3
} DRV_WIFI_EVENT_CONN_TEMP_LOST_CODES;


// *****************************************************************************
/*  status codes for connection for association or authentication failure

  Summary:
    Selection of different codes when WiFi connection fails due to association or
    authentication failure.

  Description
    This enumeration identifies the codes for a connection failure due to
    association or authentication failure.  These codes are used in
    DRV_WIFI_ProcessEvent(), case DRV_WIFI_EVENT_CONNECTION_FAILED.
*/

typedef enum
{
    DRV_WIFI_UNSPECIFIED_FAILURE                  = 1,
    DRV_WIFI_CAPS_UNSUPPORTED                     = 10,
    DRV_WIFI_REASSOC_NO_ASSOC                     = 11,
    DRV_WIFI_ASSOC_DENIED_UNSPEC                  = 12,
    DRV_WIFI_NOT_SUPPORTED_AUTH_ALG               = 13,
    DRV_WIFI_UNKNOWN_AUTH_TRANSACTION             = 14,
    DRV_WIFI_CHALLENGE_FAIL                       = 15,
    DRV_WIFI_AUTH_TIMEOUT                         = 16,
    DRV_WIFI_AP_UNABLE_TO_HANDLE_NEW_STA          = 17,
    DRV_WIFI_ASSOC_DENIED_RATES                   = 18,
    DRV_WIFI_ASSOC_DENIED_NOSHORTPREAMBLE         = 19,
    DRV_WIFI_ASSOC_DENIED_NOPBCC                  = 20,
    DRV_WIFI_ASSOC_DENIED_NOAGILITY               = 21,
    DRV_WIFI_ASSOC_DENIED_NOSHORTTIME             = 25,
    DRV_WIFI_ASSOC_DENIED_NODSSSOFDM              = 26,
    DRV_WIFI_S_INVALID_IE                         = 40,
    DRV_WIFI_S_INVALID_GROUPCIPHER                = 41,
    DRV_WIFI_S_INVALID_PAIRWISE_CIPHER            = 42,
    DRV_WIFI_S_INVALID_AKMP                       = 43,
    DRV_WIFI_UNSUPPORTED_RSN_VERSION              = 44,
    DRV_WIFI_S_INVALID_RSN_IE_CAP                 = 45,
    DRV_WIFI_S_CIPHER_SUITE_REJECTED              = 46,
    DRV_WIFI_TIMEOUT                              = 47
} DRV_WIFI_STATUS_CODES;

// *****************************************************************************
/*  WiFi devices types

  Summary:
    Codes for WiFi device types

  Description
    This enumeration identifies WiFi device types.  The only device supported
    with this driver is DRV_WIFI_MRF24WG0M_DEVICE
*/

typedef enum
{
    DRV_WIFI_MRF24WB0M_DEVICE = 1,
    DRV_WIFI_MRF24WG0M_DEVICE = 2
} DRV_WIFI_DEVICE_TYPES;


// *****************************************************************************
/*  WiFi regional domain codes

  Summary:
    Regional domain codes.

  Description
    This enumeration identifies WiFi regional domain codes.  The regional domain
    can be determined by calling DRV_WIFI_RegionalDomainGet().
*/

typedef enum
{
    /* FCC, available channels: 1 - 11 */
    DRV_WIFI_DOMAIN_FCC   = 0,

    /* ESTI, available Channels: 1 - 13 */
    DRV_WIFI_DOMAIN_ETSI  = 2,

    /* Japan, available Channels: 1 - 14 */
    DRV_WIFI_DOMAIN_JAPAN = 7,

    /* Other, available Channels: 1 - 14 */
    DRV_WIFI_DOMAIN_OTHER = 7  
} DRV_WIFI_DOMAIN_CODES;


// *****************************************************************************
/*  WiFi Power Save states

  Summary:
    Wifi Power Save states

  Description
    This enumeration identifies WiFi Power save states.  See DRV_WIFI_PsPollEnable().
*/

typedef enum
{
    /* enable hibernate mode */
    DRV_WIFI_PS_HIBERNATE             = 1,

    /* enable power save mode with DTIM enabled */
    DRV_WIFI_PS_PS_POLL_DTIM_ENABLED  = 2,

    /* enable power save mode with DTIM disabled */
    DRV_WIFI_PS_PS_POLL_DTIM_DISABLED = 3,

    /* disable Power Save mode*/
    DRV_WIFI_PS_OFF                   = 4
} DRV_WIFI_POWER_SAVE_STATES;


// *****************************************************************************
/*  WiFi Hibernate states

  Summary:
    Wifi Hibernate states

  Description
    This enumeration identifies WiFi hibernate states.
*/
typedef enum
{
    DRV_WIFI_HB_NO_SLEEP      = 0,
    DRV_WIFI_HB_ENTER_SLEEP   = 1,
    DRV_WIFI_HB_WAIT_WAKEUP   = 2
} DRV_WIFI_HIBERNATE_STATES;



// *****************************************************************************
/*  WiFi Connection States

  Summary:
    Wifi Connection states

  Description
    This enumeration identifies WiFi Connection states states.  See
    DRV_WIFI_ConnectionStateGet().
*/

typedef enum
{
    /* No WiFi connection exists */
    DRV_WIFI_CSTATE_NOT_CONNECTED                = 1,

    /* WiFi connection in progress */
    DRV_WIFI_CSTATE_CONNECTION_IN_PROGRESS       = 2,

    /* WiFi connected in infrastructure mode */
    DRV_WIFI_CSTATE_CONNECTED_INFRASTRUCTURE     = 3,

    /* WiFi connected in adhoc mode */
    DRV_WIFI_CSTATE_CONNECTED_ADHOC              = 4,

    /* WiFi in process of reconnecting */
    DRV_WIFI_CSTATE_RECONNECTION_IN_PROGRESS     = 5,

    /* WiFi connection permanently lost */
    DRV_WIFI_CSTATE_CONNECTION_PERMANENTLY_LOST  = 6
} DRV_WIFI_CONNECTION_STATES;

#define ENABLE_WPS_PRINTS                       ((uint8_t)(1 << 0))
#define ENABLE_P2P_PRINTS                       ((uint8_t)(1 << 1))   /* not supported */


typedef enum
{
    DRV_WIFI_SOFTAP_EVENT_CONNECTED    = 0,
    DRV_WIFI_SOFTAP_EVENT_DISCONNECTED = 1
} DRV_WIFI_SOFT_AP_STATES;

typedef enum
{
    DRV_WIFI_SOFTAP_EVENT_LINK_LOST       = 0,
    DRV_WIFI_SOFTAP_EVENT_RECEIVED_DEAUTH = 1
} DRV_WIFI_SOFT_AP_EVENT_REASON_CODES ;

// *****************************************************************************
/*  WiFi MIB states

  Summary:
    Wifi MIB states

  Description
    This structure contains all the MIB data returned from the MRF24WG when
     DRV_WIFI_MacStatsGet() is called.
*/
typedef struct 
{
    /* Number of frames received with the Protected Frame subfield of the Frame */
    /*  Control field set to zero and the value of dot11ExcludeUnencrypted causes */
    /*  that frame to be discarded. */
    uint32_t MibWEPExcludeCtr;

    /* Total number of Tx bytes that have been transmitted */
    uint32_t MibTxBytesCtr;

    /* Number of frames successfully transmitted that had the multicast bit set */
    /*  in the destination MAC address */
    uint32_t MibTxMulticastCtr;

    /* Number of Tx frames that failed due to the number of transmits exceeding the retry count */
    uint32_t MibTxFailedCtr;

    /* Number of times a transmitted frame needed to be retried */
    uint32_t MibTxRtryCtr;

    /* Number of times a frame was successfully transmitted after more than one retransmission. */
    uint32_t MibTxMultRtryCtr;

    /* Number of Tx frames successfully transmitted. */
    uint32_t MibTxSuccessCtr;

    /* Number of frames received where the Sequence Control field indicates a duplicate. */
    uint32_t MibRxDupCtr;

    /* Number of CTS frames received in response to an RTS frame. */
    uint32_t MibRxCtsSuccCtr;

    /* Number of times an RTS frame was not received in response to a CTS frame. */
    uint32_t MibRxCtsFailCtr;

    /* Number of times an Ack was not received in response to a Tx frame. */
    uint32_t MibRxAckFailCtr;

    /* Total number of Rx bytes received. */
    uint32_t MibRxBytesCtr;

    /* Number of successful received frames (management or data) */
    uint32_t MibRxFragCtr;

    /* Number of frames received with the multicast bit set in the destination MAC address. */
    uint32_t MibRxMultCtr;

    /* Number of frames received with an invalid Frame Checksum (FCS). */
    uint32_t MibRxFCSErrCtr;

    /* Number of frames received where the Protected Frame subfield of the Frame Control Field is set to */
    /*  one and the WEPOn value for the key mapped to the transmitter?s MAC address indicates the frame */
    /*  should not have been encrypted. */
    uint32_t MibRxWEPUndecryptCtr;

    /* Number of times that fragments aged out, or were not received in the allowable time. */
    uint32_t MibRxFragAgedCtr;

    /* Number of MIC failures that have occurred. */
    uint32_t MibRxMICFailureCtr;    
} DRV_WIFI_MAC_STATS;

// *****************************************************************************
/*  WiFi Device Type/Version

  Summary:
    Contains data pertaining to MRF24WG device type and version number

  Description
    This structure contains MRF24WG device type and version number.  See
    DRV_WIFI_DeviceInfoGet().
*/
typedef struct 
{
    /* MRF24W_DEVICE_TYPE */
    uint8_t  deviceType;

    /* MRF24WG ROM version number */
    uint8_t  romVersion;

    /* MRF24WG patch version number */
    uint8_t  patchVersion; 
} DRV_WIFI_DEVICE_INFO;

    
// *****************************************************************************
/*  WiFi Connection Context

  Summary:
    Contains data pertaining to MRF24WG connection context

  Description
    This structure contains MRF24WG connection context data.  See
    DRV_WIFI_ConnectContextGet().
*/
typedef struct 
{
    /* channel number of current connection */
    uint8_t  channel;

    /* bssid of connected AP */
    uint8_t  bssid[6];   
} DRV_WIFI_CONNECTION_CONTEXT;


// *****************************************************************************
/*  WiFi Scan Context

  Summary:
    Contains data pertaining to WiFi scan context

  Description
    This structure contains MRF24WG scan context data.  See
    DRV_WIFI_ScanContextSet().
*/
typedef struct 
{
    /* 802.11 allows for active scanning, where the device sends out a broadcast
     probe request seeking an access point.  Also allowed is passive scanning
     where the device only listens to beacons being broadcast from access points.
     Set to DRV_WIFI_ACTIVE_SCAN (default) or DRV_WIFI_PASSIVE_SCAN */
    uint8_t  scanType; 

    /* The number of times to scan a channel while attempting to find a particular
     access point. Default is 1 */
    uint8_t  scanCount;

    /* The minimum time (in milliseconds) the MRF24WG will wait for a probe 
     response after sending a probe request.  If no probe responses are received 
     in minChannelTime then the MRF24WG will go on to the next channel, if any 
     are left to scan, or quit.  Default is 200ms. */
    uint16_t minChannelTime;

    /* If a probe response is received within minChannelTime then the MRF24WG will
     continue to collect any additional probe responses up to maxChannelTime
     before going to the next channel in the channelList.  Units are in
     milliseconds.  Default is 400ms. */
    uint16_t maxChannelTime;

    /* The number of microseconds to delay before transmitting a probe request
     following the channel change during scanning.  Default is 20uS. */
    uint16_t probeDelay;
    
} DRV_WIFI_SCAN_CONTEXT;


// *****************************************************************************
/*  WiFi PS-Poll Context

  Summary:
    Contains data pertaining to WiFi PS-Poll context

  Description
    This structure contains MRF24WG PS-Poll context data.  See
    DRV_WIFI_PsPollEnable().
*/

typedef struct 
{
    /* Number of 100ms intervals between instances when the MRF24WG wakes up to
     received buffered messages from the network.  Each count represents 100ms.
     For example, 1 = 100ms, 2 = 200ms, etc.  The default is 1 (100ms). */
    uint16_t listenInterval;

    /* Only used if useDtim is true.  The DTIM period indicates how often clients
     serviced by the access point should check for buffered multicast or broadcast
     messages awaiting pickup on the access point.    The DTIM interval is
     measured in number of beacon periods.  Default for DTIM period is 2. */
    uint16_t dtimInterval;

    /* True:  (default) check for buffered multicast or broadcast messages on
              the dtimInterval.
       False: check for buffered multicast or broadcast messages on the listenInterval */
    bool     useDtim;
    
} DRV_WIFI_PS_POLL_CONTEXT;


// *****************************************************************************
/*  WiFi AdHoc Context

  Summary:
    Contains data pertaining to WiFi AdHoc context

  Description
    This structure contains MRF24WG AdHoc context data.  See
    DRV_WIFI_AdhocContextSet().
*/

typedef struct 
{
    /* Defines how to start the AdHoc network. See DRV_WIFI_ADHOC_MODE. */
    /* Default is DRV_WIFI_ADHOC_CONNECT_THEN_START. */
    uint8_t  mode;

    /* When starting an AdHoc network, the SSID can be hidden in the beacons. */
    /* Set true to hide the SSID, else false.  Default is false. */
    bool     hiddenSsid;

    /* Sets the beacon period, in ms.  Default is 100ms */
    uint16_t beaconPeriod; 
} DRV_WIFI_ADHOC_NETWORK_CONTEXT;


// *****************************************************************************
/*  WiFi Wep Security Context

  Summary:
    Contains data pertaining to WiFi WEP context

  Description
    This structure contains MRF24WG WEP context. See DRV_WIFI_SecurityWepSet().
*/
typedef struct 
{
    /* DRV_WIFI_SECURITY_WEP_40 or DRV_WIFI_SECURITY_WEP_104 */
    uint8_t wepSecurityType;

    /* Array containing four WEP binary keys. This will be four, 5-byte keys for
     WEP-40 or four, thirteen-byte keys for WEP-104. */
    uint8_t wepKey[DRV_WIFI_MAX_WEP_KEY_LENGTH];

    /* number of bytes pointed to by p_wepKey */
    uint8_t wepKeyLength;

    /* DRV_WIFI_SECURITY_WEP_OPENKEY (default) or DRV_WIFI_SECURITY_WEP_SHAREDKEY */
    uint8_t wepKeyType;
    
} DRV_WIFI_WEP_CONTEXT;


// *****************************************************************************
/*  WiFi WPA Key context

  Summary:
    Contains data pertaining to WiFi WPA Key

  Description
    This structure contains MRF24WG WPA key info. This structure is used in the
    DRV_WIFI_WPA_CONTEXT and DRV_WIFI_WPS_CONTEXT structures.
*/
typedef struct
{
    /* binary key or passphrase */
    uint8_t key[DRV_WIFI_MAX_WPA2_PASS_PHRASE_LENGTH];

    /* number of bytes in binary key (always 32) or passphrase */
    uint8_t keyLength;
    
} DRV_WIFI_WPA_KEY_INFO;

// *****************************************************************************
/*  WiFi WPA context

  Summary:
    Contains data pertaining to WiFi WPA.

  Description
    This structure contains MRF24WG WPA context. See DRV_WIFI_SecurityWpaSet().

    <table>
    wpaSecurityType                              Description
    -----------------                            -----------
    DRV_WIFI_SECURITY_WPA_WITH_KEY               WPA binary key
    DRV_WIFI_SECURITY_WPA_WITH_PASS_PHRASE       WPA passphrase
    DRV_WIFI_SECURITY_WPA2_WITH_KEY              WPA2 binary key
    DRV_WIFI_SECURITY_WPA2_WITH_PASS_PHRASE      WPA2 passphrase
    DRV_WIFI_SECURITY_WPA_AUTO_WITH_KEY          Auto-select between WPA/WPA2 with binary key
    DRV_WIFI_SECURITY_WPA_AUTO_WITH_PASS_PHRASE  Auto-select between WPA/WPA2 with passphrase
    </table>

*/
typedef struct 
{
    /* desired security type (see description) */
    uint8_t wpaSecurityType;

    /* see DRV_WIFI_WPA_KEY_INFO */
    DRV_WIFI_WPA_KEY_INFO keyInfo;
    
} DRV_WIFI_WPA_CONTEXT;

// *****************************************************************************
/*  WiFi WPS security context

  Summary:
    Contains data pertaining to WiFi WPS security.

  Description
    This structure contains MRF24WG WPS security context. See DRV_WIFI_SecurityWpsSet().
*/
typedef struct 
{
    /* DRV_WIFI_SECURITY_WPS_PUSH_BUTTON or DRV_WIFI_SECURITY_WPS_PIN */
    uint8_t wpsSecurityType;                    

    /* if using DRV_WIFI_SECURITY_WPS_PIN then pointer to 8-digit pin */
    uint8_t wpsPin[DRV_WIFI_WPS_PIN_LENGTH];

    /* should always be 8 */
    uint8_t wpsPinLength;                       

    #if defined(DRV_WIFI_USE_HOST_WPA_KEY_CALCULATION)
        /* True if ASCII passphrase should be sent back to host
           so host can (more quickly) calculate binary key.  False
           if the MRF24WG should calculate the binary key  */
        bool    getPassPhrase;                  

        /* pointer to where the WiFi driver will store passphrase info
         (must be global memory) */
        DRV_WIFI_WPA_KEY_INFO *p_keyInfo;
    #endif // DRV_WIFI_USE_HOST_WPA_KEY_CALCULATION 
} DRV_WIFI_WPS_CONTEXT;

// *****************************************************************************
/*  WiFi security context

  Summary:
    Contains data pertaining to WiFi security.

  Description
    Structure/union can be used in functions DRV_WIFI_SecurityWepSet, DRV_WIFI_SecurityWpaSet,
    and DRV_WIFI_SecurityWpsSet
*/
typedef union
{
    /* set WEP security context */
    DRV_WIFI_WEP_CONTEXT wepContext;

    /* set WPA security context */
    DRV_WIFI_WPA_CONTEXT wpaContext;

    /* set WPS security context */
    DRV_WIFI_WPS_CONTEXT wpsContext;
} DRV_WIFI_SECURITY_CONTEXT;

// *****************************************************************************
/*  WiFi Scan Results

  Summary:
    Contains data pertaining to WiFi scan results

  Description
    This structure contains the result of WiFi scan operation.  See DRV_WIFI_ScanGetResult().

      apConfig Bit Mask
      <table>
        Bit 7       Bit 6       Bit 5       Bit 4       Bit 3       Bit 2       Bit 1       Bit 0
        -----       -----       -----       -----       -----       -----       -----       -----
        WPA2        WPA         Preamble    Privacy     Reserved    Reserved    Reserved    IE
      </table>

      <table>
      IE        1 if AP broadcasting one or more Information Elements, else 0
      Privacy   0 : AP is open (no security)
                 1: AP using security,  if neither WPA and WPA2 set then security is WEP.
      Preamble  0: AP transmitting with short preamble
                 1: AP transmitting with long preamble
      WPA       Only valid if Privacy is 1.
                 0: AP does not support WPA
                 1: AP supports WPA
      WPA2      Only valid if Privacy is 1.
                 0: AP does not support WPA2
                 1: AP supports WPA2
      </table>


*/
typedef struct
{
    /* Network BSSID value */
    uint8_t      bssid[DRV_WIFI_BSSID_LENGTH];

    /*  Network SSID value */
    uint8_t      ssid[DRV_WIFI_MAX_SSID_LENGTH]; 

    /* Access Point config (see description) */
    uint8_t      apConfig;

    /* not used */
    uint8_t      reserved;

    /* Network beacon interval */
    uint16_t     beaconPeriod;

    /* Only valid if bssType = DRV_WIFI_NETWORK_TYPE_INFRASTRUCTURE */
    uint16_t     atimWindow;   

    /*
      List of Network basic rates.  Each rate has the following format:
      
          Bit 7
      * 0: rate is not part of the basic rates set
      * 1: rate is part of the basic rates set

          Bits 6:0
      Multiple of 500kbps giving the supported rate.  For example, a value of 2 
      (2 * 500kbps) indicates that 1mbps is a supported rate.  A value of 4 in 
      this field indicates a 2mbps rate (4 * 500kbps).
      */
    uint8_t      basicRateSet[DRV_WIFI_MAX_NUM_RATES];

    /* Signal strength of received frame beacon or probe response.  Will range
       from a low of 43 to a high of 128. */
    uint8_t      rssi;          

    /* Number of valid rates in basicRates */
    uint8_t      numRates;

    /* Part of TIM element */
    uint8_t      DtimPeriod;

    /* DRV_WIFI_NETWORK_TYPE_INFRASTRUCTURE or DRV_WIFI_NETWORK_TYPE_ADHOC */
    uint8_t      bssType;

    /* Channel number */
    uint8_t      channel;

    /* Number of valid characters in ssid */
    uint8_t      ssidLen;       

} DRV_WIFI_SCAN_RESULT;

typedef struct 
{
    uint8_t state;
    uint8_t wakeup_notice;
} DRV_WIFI_HIBERNATE_STATE;

// *****************************************************************************
/*  WiFi SW Multicast Filter Config

  Summary:
    Contains data pertaining to WiFi software multicast filter configuration

  Description
    This structure contains data pertaining to the configuration of the software
    multicast config filter.

       <table>
        'action' Field                         Description
        --------------                         -----------
        DRV_WIFI_MULTICAST_DISABLE_ALL         Multicast filter discards all received multicast messages.

        DRV_WIFI_MULTICAST_ENABLE_ALL          Multicast filter forwards all received multicast messages to host.

        DRV_WIFI_MULTICAST_USE_FILTERS         The MAC filter will be used and the remaining fields define the filter.

      </table>

*/
typedef struct 
{
    /* DRV_WIFI_MULTICAST_FILTER_1 thru DRV_WIFI_MULTICAST_FILTER_16 */
    uint8_t filterId;

    /* configures the multicast filter (see description) */
    uint8_t action;

    /* Array containing the MAC address to filter on (using the destination
       address of each incoming 802.11 frame).  Specific bytes within the MAC
       address can be designated as ?don?t care? bytes.  See macBitMask.
       This field in only used if action = WF_MULTICAST_USE_FILTERS. */
    uint8_t macBytes[6];

    /* A byte where bits 5:0 correspond to macBytes[5:0].  If the bit is zero then
       the corresponding MAC byte must be an exact match for the frame to be
       forwarded to the Host PIC.  If the bit is one then the corresponding MAC
       byte is a ?don?t care? and not used in the Multicast filtering process.
       This field in only used if action = WF_MULTICAST_USE_FILTERS. */
    uint8_t macBitMask;

} DRV_WIFI_SWMULTICAST_CONFIG;

// *****************************************************************************
/*  WiFi WPS Credentials

  Summary:
    Contains data pertaining to WiFi WPS Credentials

  Description
    This structure contains data pertaining to the configuration of the WiFi
    WPS credentials.

         <table>
        'authType' Field            Description
        ----------------            -----------
        DRV_WIFI_WPS_AUTH_OPEN      open security
        DRV_WIFI_WPS_AUTH_WPA_PSK   WPA with PSK
        DRV_WIFI_WPS_AUTH_SHARED    Shared key
        DRV_WIFI_WPS_AUTH_WPA       WPA
        DRV_WIFI_WPS_AUTH_WPA2      WPA2
        DRV_WIFI_WPS_AUTH_WPA2_PSK  WPA2 with PSK
        </table>

          <table>
        'encType' Field             Description
        ----------------            -----------
        DRV_WIFI_WPS_ENC_NONE       No encoding
        DRV_WIFI_WPS_ENC_WEP        WEP encoding
        DRV_WIFI_WPS_ENC_TKIP       WPS/TKIP encodingShared key
        DRV_WIFI_ENC_AES            AES encoding
        </table>
*/
typedef struct 
{
        /* network SSID */
        uint8_t  ssid[32];

        /* binary security key (not used if security is open) */
        uint8_t  netKey[64];

        /* WPS authorization type (see description) */
        uint16_t authType;

        /* Encoding type (see description) */
        uint16_t encType;

        /* not used */
        uint8_t  netIdx;

        /* number of bytes in SSID */
        uint8_t  ssidLen;

        /* Only valid encType = WF_ENC_WEP.  This is the index of the WEP key being used. */
        uint8_t  keyIdx;

        /* number of bytes in netKey */
        uint8_t  keyLen;

        /* MAC address of AP */
        uint8_t  bssid[6];
} DRV_WIFI_WPS_CREDENTIAL;


// *****************************************************************************
/*  WiFi Soft AP Event Information

  Summary:
    Contains data pertaining to WiFi Soft AP event

  Description
    This structure contains data pertaining to Soft AP event.  See
    DRV_WIFI_SoftApEventInfoGet().
*/
typedef struct 
{
    /* event code */
    uint8_t event;

    /* reason code */
    uint8_t reason;

    /* MAC address */
    uint8_t address[6];
} DRV_WIFI_MGMT_INDICATE_SOFT_AP_EVENT;


// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines - System Level
// *****************************************************************************
// *****************************************************************************

//-------------------------
// Initialization Functions
//-------------------------
// *****************************************************************************
/* Function:
    bool DRV_WIFI_Initialize(void);

  Summary:
    Initializes the MRF24WG WiFi driver.

  Description:
    This function initializes the MRF24WG driver, making it ready for clients to
    use.

  Precondition:
    None.

  Parameters:
    pNetIf      - Pointer to network interface

  Returns:
    If successful returns true, else false.

  Remarks:
    This function must be called before any other WiFi routine is called.  Currently,
    this function performs no work, but that may change in the future.  The WiFi
    initialization takes place in a state machine called by MRF24W_MACInit().
*/
bool DRV_WIFI_Initialize(void* pNetIf);


// *****************************************************************************
/* Function:
    bool DRV_WIFI_Deinitialize(void);

  Summary:
    Initializes the MRF24WG WiFi driver.

  Description:
    This function deinitializes the MRF24WG driver.  It also saves the WiFi
    parameters in non-volatile storage.

  Precondition:
    None.

  Parameters:
    None

  Returns:
    If successful returns true, else false.

  Remarks:
    None
*/
bool DRV_WIFI_Deinitialize(void);

// *****************************************************************************
/* Function:
    void DRV_WIFI_NetworkTypeSet(uint8_t networkType);

  Summary:
    Sets the WiFi network type

  Description:
    This function selects the WiFi network type.

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    networkType     - One of the following:
                        DRV_WIFI_NETWORK_TYPE_INFRASTRUCTURE
                        DRV_WIFI_NETWORK_TYPE_ADHOC
                        DRV_WIFI_NETWORK_TYPE_P2P  - not supported
                        DRV_WIFI_NETWORK_TYPE_SOFT_AP

  Returns:
    None

  Example:
    <code>
        DRV_WIFI_NetworkTypeSet(DRV_WIFI_NETWORK_TYPE_INFRASTRUCTURE);
    </code>

  Remarks:
    None
*/
void DRV_WIFI_NetworkTypeSet(uint8_t networkType);


// *****************************************************************************
/* Function:
    void DRV_WIFI_NetworkTypeGet(uint8_t *p_networkType);

  Summary:
    Gets the WiFi network type

  Description:
    This function gets the WiFi network type.

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    p_networkType     - Pointer to where the network type will be written.
                        One of the following:
                          DRV_WIFI_NETWORK_TYPE_INFRASTRUCTURE
                          DRV_WIFI_NETWORK_TYPE_ADHOC
                          DRV_WIFI_NETWORK_TYPE_P2P - not supported
                          DRV_WIFI_NETWORK_TYPE_SOFT_AP

  Returns:
    None

  Example:
    <code>
        uint8_t networkType;

        DRV_WIFI_NetworkTypeGet(&networkType);
    </code>

  Remarks:
    None
*/
void DRV_WIFI_NetworkTypeGet(uint8_t *p_networkType);


// *****************************************************************************
/* Function:
    void  DRV_WIFI_SsidSet(uint8_t *p_ssid,  uint8_t ssidLength);

  Summary:
    Sets the SSID

  Description:
    Sets the SSID and SSID Length.  Note that an Access Point can have either a
    visible or hidden SSID.  If an Access Point uses a hidden SSID then an
    active scan must be used.

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    p_ssid      - Pointer to SSID buffer
    ssidLength  - number of bytes in SSID

  Returns:
    None

  Example:
    <code>
        uint8_t ssid[] = "MySSIDName";
        uint8_t ssidLength = strlen(ssid);
 
        DRV_WIFI_SsidSet(ssid, ssidLength);
     </code>

  Remarks:
    Do not include a string terminator in the SSID length.  SSID's are case-
    sensitive.  SSID length must be less than or equal to DRV_WIFI_MAX_SSID_LENGTH.
*/
void DRV_WIFI_SsidSet(uint8_t *p_ssid,  uint8_t ssidLength);


// *****************************************************************************
/* Function:
    void DRV_WIFI_SsidGet(uint8_t *p_ssid, uint8_t *p_ssidLength);

  Summary:
    Sets the SSID

  Description:
    Gets the SSID and SSID Length.

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    p_ssid      - Pointer to buffer where SSID will be written
    ssidLength  - number of bytes in SSID

  Returns:
    None

  Example:
    <code>
        uint8_t ssid[DRV_WIFI_MAX_SSID_LENGTH];
        uint8_t ssidLength;

        DRV_WIFI_SsidGet(ssid, &ssidLength);
     </code>

  Remarks:
    None
*/
void DRV_WIFI_SsidGet(uint8_t *p_ssid, uint8_t *p_ssidLength);


// *****************************************************************************
/* Function:
    void DRV_WIFI_AdhocContextSet(DRV_WIFI_ADHOC_NETWORK_CONTEXT *p_context);

  Summary:
    Sets the AdHoc context.

  Description:
    This function sets the AdHoc context.  It is only applicable when the
    DRV_WIFI_NETWORK_TYPE_ADHOC has been selected in DRV_WIFI_NetworkTypeSet().

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    p_context   - pointer to AdHoc context data; see definition for the
                  DRV_WIFI_ADHOC_NETWORK_CONTEXT structure.

  Returns:
    None

  Example:
    <code>
        DRV_WIFI_ADHOC_NETWORK_CONTEXT adHocContext;

        adHocContext.mode         = DRV_WIFI_ADHOC_CONNECT_THEN_START;
        adHocContext.hiddenSsid   = false;
        adHocContext.beaconPeriod = DRV_WIFI_DEFAULT_ADHOC_BEACON_PERIOD;

        DRV_WIFI_AdhocContextSet(&adHocContext);
 
     </code>

  Remarks:
    None
*/
void DRV_WIFI_AdhocContextSet(DRV_WIFI_ADHOC_NETWORK_CONTEXT *p_context);


// *****************************************************************************
/* Function:
    void DRV_WIFI_BssidSet(uint8_t *p_bssid);

  Summary:
    Sets the the Basic Service Set Identifier (BSSID).

  Description:
    This sets 6 byte (48-bit) MAC address of the Access Point that is being scanned for.
    It is optional to use this.  Where it is useful is if there are two AP's with the
    same ID; the BSSID is used to connect to the specified AP.  This setting can
    be used in lieu of the SSID.  Set each byte to 0xFF (default) if the BSSID is 
    not being used.  Not typically needed.

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    p_context   - pointer to BSSID

  Returns:
    None

  Example:
    <code>
        uint8_t bssid[6];

        bssid[0] = 0x00;
        bssid[1] = 0xe8;
        bssid[2] = 0xc0;
        bssid[3] = 0x11;
        bssid[4] = 0x22;
        bssid[5] = 0x33;

        DRV_WIFI_BssidSet(bssid);

    </code>

  Remarks:
    None
*/
void DRV_WIFI_BssidSet(uint8_t *p_bssid);


// *****************************************************************************
/* Function:
    void DRV_WIFI_BssidGet(uint8_t *p_bssid);

  Summary:
    Sets the the BSSID set in DRV_WIFI_BssidSet().

  Description:
    Retrieves the BSSID set in the previous call to DRV_WIFI_BssidSet().

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    p_context   - pointer to where BSSID will be written.

  Returns:
    None

  Example:
    <code>
        uint8_t bssid[6];

        DRV_WIFI_BssidGet(bssid);

    </code>

  Remarks:
    None
*/
void DRV_WIFI_BssidGet(uint8_t *p_bssid);


// *****************************************************************************
/* Function:
    void DRV_WIFI_ChannelListSet(uint8_t *p_channelList, uint8_t numChannels);

  Summary:
    Sets the the channel list.

  Description:
    This function sets the channel list that the MRF24WG will use when scanning
    or connecting.

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    p_channelList - list of channels
    numChannels   - number of channels in list; if set to 0, then MRF24WG will set
                    its channel list to all valid channels in its regional domain.

  Returns:
    None

  Example:
    <code>
        uint8_t channelList[1,6,11];

        DRV_WIFI_ChannelListSet(channelList, sizeof(channelList));

    </code>

  Remarks:
    None
*/
void DRV_WIFI_ChannelListSet(uint8_t *p_channelList, uint8_t numChannels);


// *****************************************************************************
/* Function:
    void RV_WIFI_ChannelListGet(uint8_t *p_channelList, uint8_t *p_numChannels);

  Summary:
    Gets the the channel list.

  Description:
    This function gets the current channel list.

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    p_channelList - pointer to where channel list will be written
    numChannels   - pointer to where number of channels in the list will be written.

  Returns:
    None

  Example:
    <code>
        uint8_t channelList[DRV_WIFI_MAX_CHANNEL_LIST_LENGTH];
        uint8_t numChannels;

        DRV_WIFI_ChannelListGet(channelList, &numChannels);

    </code>

  Remarks:
    None
*/
void DRV_WIFI_ChannelListGet(uint8_t *p_channelList, uint8_t *p_numChannels);

// *****************************************************************************
/* Function:
    void DRV_WIFI_ReconnectModeSet(uint8_t retryCount, uint8_t deauthAction,
                                   uint8_t beaconTimeout, uint8_t beaconTimeoutAction);

  Summary:
    Sets the WiFi reconnection mode.

  Description:
    This function controls how the MRF24WG behaves when an existing WiFi connection
    is lost.  The MRF24WG can lose an existing connection in one of two ways:
    1) Beacon timeout
    2) Deauth received from AP

    There are two options with respect to regaining a lost WiFi connection:
        1) MRF24WG informs the host that the connection was temporarily lost and
           then the MRF24WG retries N times (or forever) to regain the connection.
        2) MRF24WG simply informs the host application that the connection is lost,
           and it is up to the host to regain the connection via the API.

    Note: The retryCount parameter also applies when initially connecting.
          That is, the retryCount tells the MRF24WG how many time to try to
          connect to a WiFi network before giving up and generating the 
          DRV_WIFI_EVENT_CONNECTION_FAILED event.

        <table>
        'retryCount' field    Description
        ------------------    -----------
        0                     Do not try to regain a connection (simply report event to host)
        1:254                 Number of times MRF24WG should try to regain the connection
        255                   MRF24WG will retry forever (do not use for AdHoc connections)
        </table>

        <table>
        'deauthAction' field                   Description
        --------------------                   -----------
        DRV_WIFI_DO_NOT_ATTEMPT_TO_RECONNECT   Do not attempt to reconnect after a deauth
        DRV_WIFI_ATTEMPT_TO_RECONNECT          Attempt to reconnect after a deauth
        </table>

        <table>
        'beaconTimeout' field   Description
        ---------------------   -----------
        0                       MRF24WG will not monitor the beacon timeout condition
        1:255                   Number of missed beacons before designating the connection as lost.
        </table>

        <table>
        'beaconTimeoutAction' field             Description
        ---------------------------             -----------
        DRV_WIFI_DO_NOT_ATTEMPT_TO_RECONNECT    Do not attempt to reconnect after a beacon timeout
        DRV_WIFI_ATTEMPT_TO_RECONNECT           Attempt to reconnect after a beacon timeout
        </table>

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    retryCount        - Number of times the MRF24WG should try to regain the connection (see description)

    deauthAction      - In the event of a deauth from the AP, the action the MRF24WG
                        should take (see description)

    beaconTimeout     - Number of missed beacons before the MRF24WG designates the
                        connection as lost (see description)

    beaconTimeoutAction - In the event of a beacon timeout, the action the MRF24WG
                          should take (see description)

 Returns:
    None

  Example:
    <code>
        // Example 1: MRF24WG should retry forever if either a deauth or beacon
        // timeout occurs (beacon timeout is 3 beacon periods).
        DRV_WIFI_ReconnectModeSet(WF_RETRY_FOREVER,
                                  WF_ATTEMPT_TO_RECONNECT,
                                  3,
                                  WF_ATTEMPT_TO_RECONNECT);
 
        // Example 2: MRF24WG should not do any connection retries and only report
        // deauth events to the host.
        DRV_WIFI_ReconnectModeSet(0,
                                  WF_DO_NOT_ATTEMPT_TO_RECONNECT,
                                  0,
                                  WF_DO_NOT_ATTEMPT_TO_RECONNECT);

        // Example 3: MRF24WG should not do any connection retries, but report deauth
        // and beacon timeout events to host.  Beacon timeout should be 5 beacon periods.
        DRV_WIFI_ReconnectModeSet(0,
                                  WF_DO_NOT_ATTEMPT_TO_RECONNECT,
                                  5,
                                  WF_DO_NOT_ATTEMPT_TO_RECONNECT);

        // Example 4: MRF24WG should ignore beacon timeouts, but attempt to
        // reconnect 3 times if a deauth occurs.
        DRV_WIFI_ReconnectModeSet(3,
                                  WF_ATTEMPT_TO_RECONNECT,
                                  0,
                                  WF_DO_NOT_ATTEMPT_TO_RECONNECT);
    </code>

  Remarks:
    None
*/
void DRV_WIFI_ReconnectModeSet(uint8_t retryCount, uint8_t deauthAction, uint8_t beaconTimeout, uint8_t beaconTimeoutAction);

// *****************************************************************************
/* Function:
    void  DRV_WIFI_ReconnectModeGet(uint8_t *p_retryCount, uint8_t *p_deauthAction,
                                    uint8_t *p_beaconTimeout, uint8_t *p_beaconTimeoutAction);

  Summary:
    Gets the WiFi reconnection mode.

  Description:
    This function gets the reconnection mode parameters set in
    DRV_WIFI_ReconnectModeGet().

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    p_retryCount      - Pointer where retry count is written

    p_deauthAction    - Pointer where deauth action is written

    p_beaconTimeout   - Pointer where beacon timeout is written

    p_beaconTimeoutAction - Pointer where beacon timeout action is written.

 Returns:
    None

  Example:
    <code>
        uint8_t retryCount, deauthAction, beaconTimeout, beaconTimeoutAction;

        DRV_WIFI_ReconnectModeGet(&retryCount,
                                  &deauthAction,
                                  &beaconTimeout,
                                  &beaconTimeoutAction);
    </code>

  Remarks:
    None
*/
void DRV_WIFI_ReconnectModeGet(uint8_t *p_retryCount, uint8_t *p_deauthAction, uint8_t *p_beaconTimeout, uint8_t *p_beaconTimeoutAction);

// DOM-IGNORE-BEGIN
TCPIP_MAC_RES Demo_Wifi_Connect(void);
// DOM-IGNORE-END

// *****************************************************************************
/* Function:
    void DRV_WIFI_Connect(void);

  Summary:
    Directs the MRF24WG to connect to a WiFi network.

  Description:
    This function causes the MRF24WG to connect to a WiFi network.  Upon connection,
    or a failure to connect, an event will be generated.

  Precondition:
    WiFi initialization must be complete and relevant connection parameters must
    have been set.

  Parameters:
    None

 Returns:
    None

  Example:
    <code>
        DRV_WIFI_Connect();
    </code>

  Remarks:
    None
*/
void DRV_WIFI_Connect(void);

// *****************************************************************************
/* Function:
    uint16_t DRV_WIFI_Disconnect(void);

  Summary:
    Directs the MRF24WG to disconnect from a WiFi network.

  Description:
    This function causes the MRF24WG to disconnect from a WiFi network.  No event
    is generated when a connection is terminated via the function call.

  Precondition:
    WiFi initialization must be complete and a connection must be in progress.

  Parameters:
    None

 Returns:
    DRV_WIFI_SUCCESS or DRV_WIFI_ERROR_DISCONNECT_FAILED

  Example:
    <code>
        DRV_WIFI_Disconnect();
    </code>

  Remarks:
    None
*/
uint16_t DRV_WIFI_Disconnect(void);


// *****************************************************************************
/* Function:
    void DRV_WIFI_ConnectionStateGet(uint8_t *p_state);

  Summary:
    Gets the current WiFi connection state

  Description:
    This function gets the current WiFi connection state.

    <table>
    *p_state                                        Description
    --------                                        -----------
    DRV_WIFI_CSTATE_NOT_CONNECTED                   No WiFi connection exists
    DRV_WIFI_CSTATE_CONNECTION_IN_PROGRESS          WiFi connection in progress
    DRV_WIFI_CSTATE_CONNECTED_INFRASTRUCTURE        WiFi connected in infrastructure mode
    DRV_WIFI_CSTATE_CONNECTED_ADHOC                 WiFi connected in adhoc mode
    DRV_WIFI_CSTATE_RECONNECTION_IN_PROGRESS        WiFi in process of reconnecting
    DRV_WIFI_CSTATE_CONNECTION_PERMANENTLY_LOST     WiFi connection permanently lost
    </table>

  Precondition:
    WiFi initialization must be complete

  Parameters:
    p_state    - pointer to where state is written (see description)

 Returns:
    None

  Example:
    <code>
        uint8_t state;

        DRV_WIFI_ConnectionStateGet(&state);
    </code>

  Remarks:
    None
*/
void DRV_WIFI_ConnectionStateGet(uint8_t *p_state);


// *****************************************************************************
/* Function:
    void DRV_WIFI_ConnectContextGet(DRV_WIFI_CONNECTION_CONTEXT *p_ctx);

  Summary:
    Gets the current WiFi connection context

  Description:
    This function gets the current WiFi connection context.

  Precondition:
    WiFi initialization must be complete

  Parameters:
    p_ctx      - pointer to where connection context is written.  See
                 DRV_WIFI_CONNECTION_CONTEXT structure.

 Returns:
    None

  Example:
    <code>
        DRV_WIFI_CONNECTION_CONTEXT ctx;

        DRV_WIFI_ConnectContextGet(&ctx);
    </code>

  Remarks:
    None
*/
void DRV_WIFI_ConnectContextGet(DRV_WIFI_CONNECTION_CONTEXT *p_ctx);

/*******************************************************************************
   Function:
    void DRV_WIFI_SetLinkDownThreshold(uint8_t threshold)

  Summary:
    Sets number of consecutive WiFi Tx failures before link is considered down.

  Description:
    This function allows the application to set the number of MRF24W consecutive Tx failures
    before the connection failure event (DRV_WIFI_LINK_LOST) is reported to the host application.

  Precondition:
    WiFi initialization must be complete

  Parameters:
    threshold --  0:      disabled (default)
                  1-255:  number of consecutive Tx failures before connection failure event is reported

  Returns:
    None.

  Example:
    <code>
        DRV_WIFI_SetLinkDownThreshold(0); // disable link down threshold
    </code>

  Remarks:
    None.
 *****************************************************************************/
void DRV_WIFI_SetLinkDownThreshold(uint8_t threshold);


/*******************************************************************************
  Function:
    void DRV_WIFI_TxModeSet(uint8_t mode)

  Summary:
    Configures 802.11 Tx mode

  Description:
    This function sets the MRF24WG Tx mode.

        <table>
        mode                           Description
        ----                           -----------
        DRV_WIFI_TXMODE_G_RATES        Use all 802.11g rates (default)
        DRV_WIFI_TXMODE_B_RATES        Use only 802.11b rates
        DRV_WIFI_TXMODE_LEGACY_RATES   Use only 1 and 2 mbps rates
        </table>

  Precondition:
    WiFi initialization must be complete

  Parameters:
    mode - Tx mode value (see description)

  Returns:
    None.

  Example:
    <code>
        DRV_WIFI_TxModeSet(DRV_WIFI_TXMODE_G_RATES);
    </code>

  Remarks:
    None.
 *****************************************************************************/
void DRV_WIFI_TxModeSet(uint8_t mode);


/*******************************************************************************
  Function:
    void DRV_WIFI_TxModeGet(uint8_t *p_mode);

  Summary:
    Gets 802.11 Tx mode

  Description:
    This function gets the MRF24WG Tx mode.

  Precondition:
    WiFi initialization must be complete

  Parameters:
    p_mode -- Pointer to where mode will be written.  See DRV_WIFI_TX_MODES.

  Returns:
    None.

  Example:
    <code>
        uint8_t mode;

        DRV_WIFI_TxModeGet(&mode);
    </code>

  Remarks:
    None.
 *****************************************************************************/
void DRV_WIFI_TxModeGet(uint8_t *p_mode);


// *****************************************************************************
/* Function:
    void DRV_WIFI_RssiSet(uint8_t rssi);

  Summary:
    Sets RSSI restrictions when connecting

  Description:
    This setting is only used if:
      1) Neither an SSID or BSSID has been configured
                         or
      2) An SSID is defined and multiple AP's are discovered with the same SSID

    <table>
    rssi       Description
    ----       -----------
    0          Connect to first network found
    1-254      Only connect to network if the RSSI is greater or equal to this value
    255        Connect to the highest RSSI found (default)
    </table>

  Precondition:
    WiFi initialization must be complete

  Parameters:
    rssi - See description

 Returns:
    None

  Example:
    <code>
        DRV_WIFI_RssiSet(255);
    </code>

  Remarks:
    Rarely needed
*/
void DRV_WIFI_RssiSet(uint8_t rssi);


// *****************************************************************************
/* Function:
    void DRV_WIFI_RssiGet(uint8_t *p_rssi);

  Summary:
    Gets RSSI value set in DRV_WIFI_RssiSet()

  Description:
    This function retrieves the value set in Gets RSSI value set in DRV_WIFI_RssiSet().
    It does not retrieve the current connection RSSI value.  The scan result will
    yield the current RSSI.

  Precondition:
    WiFi initialization must be complete

  Parameters:
    p_rssi - pointer where rssi value is written

 Returns:
    None

  Example:
    <code>
        uint8_t rssi;

        DRV_WIFI_RssiGet(&rssi);
    </code>

  Remarks:
    None
*/
void DRV_WIFI_RssiGet(uint8_t *p_rssi);


// *****************************************************************************
/* Function:
    void DRV_WIFI_SecurityOpenSet(void);

  Summary:
    Sets WiFi security to open (no security)

  Description:
    This function sets the WiFi security to open.  One can only connect to an AP
    that is running in open mode.

  Precondition:
    WiFi initialization must be complete.  Must be in an unconnected state.

  Parameters:
    None

 Returns:
    None

  Example:
    <code>
        DRV_WIFI_SecurityOpenSet();
    </code>

  Remarks:
    None
*/
void DRV_WIFI_SecurityOpenSet(void);

// *****************************************************************************
/* Function:
    void DRV_WIFI_SecurityWepSet(DRV_WIFI_WEP_CONTEXT* p_context);

  Summary:
    Sets WiFi security to use WEP.

  Description:
    This function sets the WiFi security to WEP.  One can only connect to an AP
    that is running the same WEP mode.

  Precondition:
    WiFi initialization must be complete.  Must be in an unconnected state.

  Parameters:
    p_context - desired WEP context.  See DRV_WIFI_WEP_CONTEXT structure.

 Returns:
    None

  Example:
    <code>
        DRV_WIFI_WEP_CONTEXT context;

        context.wepSecurityType = DRV_WIFI_SECURITY_WEP_40;
        context.wepKey[] = {0x5a, 0xfb, 0x6c, 0x8e, 0x77,
                            0xc1, 0x04, 0x49, 0xfd, 0x4e,
                            0x43, 0x18, 0x2b, 0x33, 0x88,
                            0xb0, 0x73, 0x69, 0xf4, 0x78};

        context.wepKeyLength = 20;
        context.wepKeyType = DRV_WIFI_SECURITY_WEP_OPENKEY;
        DRV_WIFI_SecurityOpenSet(&context);
    </code>

  Remarks:
    None
*/
void DRV_WIFI_SecurityWepSet(DRV_WIFI_WEP_CONTEXT* p_context);

// *****************************************************************************
/* Function:
    DRV_WIFI_SecurityWpaSet(DRV_WIFI_WPA_CONTEXT* p_context);

  Summary:
    Sets WiFi security to use WPA or WPA2

  Description:
    This function sets the WiFi security to WPA or WPA2.  One can only connect to
    an AP that is running the same WPA mode.

  Precondition:
    WiFi initialization must be complete.  Must be in an unconnected state.

  Parameters:
    p_context - desired WPA context.  See DRV_WIFI_WPA_CONTEXT structure.

 Returns:
    None

  Example:
    <code>
        DRV_WIFI_WPA_CONTEXT context;

        context.wpaSecurityType  = DRV_WIFI_SECURITY_WPA2_WITH_PASS_PHRASE;
        context.keyInfo.key[]    = "MySecretWPA2PassPhrase";
        context.keyInfo.keyLenth = strlen(context.keyInfo.key);
        DRV_WIFI_SecurityWpaSet(&context);
    </code>

  Remarks:
    None
*/
void DRV_WIFI_SecurityWpaSet(DRV_WIFI_WPA_CONTEXT* p_context);


// *****************************************************************************
/* Function:
    void DRV_WIFI_SecurityWpsSet(DRV_WIFI_WPS_CONTEXT *p_context);

  Summary:
    Sets WiFi security to use WPS

  Description:
    This function sets the WiFi security to WPS.  One can only connect to
    an AP that supports WPS.

  Precondition:
    WiFi initialization must be complete.  Must be in an unconnected state.

  Parameters:
    p_context - desired WPA context.  See DRV_WIFI_WPS_CONTEXT structure.

 Returns:
    None

  Example:
    <code>
        DRV_WIFI_WPS_CONTEXT context;
        uint8_t wpsPin[8] = {1, 2, 3, 9, 0, 2, 1, 2};

        context.wpsSecurityType = DRV_WIFI_SECURITY_WPS_PUSH_BUTTON;
        memcpy(context.wpsPin, wpsPin, sizeof(wpsPin));
        context.wpsPinLength = 8;
        DRV_WIFI_SecurityWpsSet(&context);
    </code>

  Remarks:
    None
*/
void DRV_WIFI_SecurityWpsSet(DRV_WIFI_WPS_CONTEXT *p_context);


/*******************************************************************************
  Function:
    void DRV_WIFI_SecurityGet(uint8_t *p_securityType,
                              uint8_t *p_securityKey,
                              uint8_t *p_securityKeyLength)

  Summary:
    Gets the current WiFi security setting

  Description:
    This function gets the current WiFi security setting.

    <table>
    'securityType' Field                          Key         Length
    --------------------                          ---         ------
    DRV_WIFI_SECURITY_OPEN                        N/A         N/A
    DRV_WIFI_SECURITY_WEP_40                      binary      4 keys, 5 bytes each (total of 20 bytes)
    DRV_WIFI_SECURITY_WEP_104                     binary      4 keys, 13 bytes each (total of 52 bytes)
    DRV_WIFI_SECURITY_WPA_WITH_KEY                binary      32 bytes
    DRV_WIFI_SECURITY_WPA_WITH_PASS_PHRASE        ascii       8-63 ascii characters
    DRV_WIFI_SECURITY_WPA2_WITH_KEY               binary      32 bytes
    DRV_WIFI_SECURITY_WPA2_WITH_PASS_PHRASE       ascii       8-63 ascii characters
    DRV_WIFI_SECURITY_WPA_AUTO_WITH_KEY           binary      32 bytes
    DRV_WIFI_SECURITY_WPA_AUTO_WITH_PASS_PHRASE   ascii       8-63 ascii characters
    </table>

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    p_securityType      - Value corresponding to the security type desired (see description)
    p_securityKey       - Binary key or passphrase (not used if security is DRV_WIFI_SECURITY_OPEN)
    p_securityKeyLength - Number of bytes in p_securityKey (not used if security is DRV_WIFI_SECURITY_OPEN)

  Returns:
    None.

   Example:
    <code>
        uint8_t securityType;
        uint8_t securityKey[DRV_WIFI_MAX_SECURITY_KEY_LENGTH];
        uint8_t keyLength;

        DRV_WIFI_SecurityGet(&securityType, securityKey, &keyLength);
    </code>

  Remarks:
    If security was initially set with a passphrase that the MRF24WG used to generate
    a binary key, this function returns the binary key, not the passphrase.
*/
void DRV_WIFI_SecurityGet(uint8_t *p_securityType,
                          uint8_t *p_securityKey,
                          uint8_t *p_securityKeyLength);


/*******************************************************************************
  Function:
    void DRV_WIFI_WepKeyTypeGet(uint8_t *p_keyType)

  Summary:
    Gets the Wep Key type

  Description:
    This function gets the WEP key type:
      * DRV_WIFI_SECURITY_WEP_SHAREDKEY
      * DRV_WIFI_SECURITY_WEP_OPENKEY

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    p_keyType -- pointer to where key type will be written.

  Returns:
    None.

    Example:
    <code>
        uint8_t wepKeyType;

        DRV_WIFI_WepKeyTypeGet(&wepKeyType);
    </code>

  Remarks:
    None.
  *****************************************************************************/
void DRV_WIFI_WepKeyTypeGet(uint8_t *p_wepKeyType);


/*******************************************************************************
  Function:
    void DRV_WIFI_WPSCredentialsGet(DRV_WIFI_WPS_CREDENTIAL *p_cred);

  Summary:
    Gets the WPS credentials

  Description:
    This function gets the WPS credentials from the MRF24WG

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    p_cred -- pointer to where WPS credentials will be written.

  Returns:
    None.

    Example:
    <code>
        DRV_WIFI_WPS_CREDENTIAL cred;;

        DRV_WIFI_WPSCredentialsGet(&cred);
    </code>

  Remarks:
    None.
  *****************************************************************************/
void DRV_WIFI_WPSCredentialsGet(DRV_WIFI_WPS_CREDENTIAL *p_cred);


/*******************************************************************************
  Function:
    DRV_WIFI_MGMT_INDICATE_SOFT_AP_EVENT * DRV_WIFI_SoftApEventInfoGet(void);

  Summary:
    Gets the stored Soft AP event info

  Description:
    This function retrieves the additional event info after a Soft AP event has
    occurred.

  Precondition:
    Soft AP event must have occurred

  Parameters:
    p_event -- pointer to where event info is written.  See
               DRV_WIFI_MGMT_INDICATE_SOFT_AP_EVENT structure.

  Returns:
    None.

  Example:
    <code>
        DRV_WIFI_MGMT_INDICATE_SOFT_AP_EVENT info;;

        DRV_WIFI_WPSCredentialsGet(&info);
    </code>

  Remarks:
    None.
  *****************************************************************************/
 DRV_WIFI_MGMT_INDICATE_SOFT_AP_EVENT * DRV_WIFI_SoftApEventInfoGet(void);

/*******************************************************************************
  Function:
    void DRV_WIFI_YieldPassphraseToHost(void);

  Summary:
    Allows host to get WPS WPA-PSK passphrase and convert to binary key.

  Description:
     During WPS the MRF24WG will receive a passphrase.  That passphrase must be
     converted to a binary key.  The MRF24WG can do this, but it will take 20-30
     seconds.  The host MCU will be able to convert the passphrase to a
     binary key much faster.  If that is desired, then this function should be called
     to request the MRF24WG to signal the DRV_WIFI_EVENT_KEY_CALCULATION_REQUEST
     event when the passphrase is ready.  Then the host can retrieve the passphrase
     (see DRV_WIFI_WPSCredentialsGet()),  convert to a binary key (see
     DRV_WIFI_ConvPassphraseToKey()), and send it back to the MRF24WG via the
     DRV_WIFI_SetPSK() function.

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    None

  Returns:
    None.

  Example:
    <code>
        DRV_WIFI_YieldPassphraseToHost(&info);
    </code>

  Remarks:
    None.
 *****************************************************************************/
void DRV_WIFI_YieldPassphraseToHost(void);


/*******************************************************************************
  Function:
    void DRV_WIFI_SetPSK(uint8_t *p_psk);

  Summary:
    Sets the binary WPA PSK code in WPS.

  Description:
    This function is used in conjunction with DRV_WIFI_YieldPassphraseToHost().
    It sends the binary key to the MRF24WG after the host has converted an ASCII
    passphrase to a binary key.

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    p_psk - pointer to the binary key

  Returns:
    None.

  Example:
    <code>
        DRV_WIFI_YieldPassphraseToHost(&info);
    </code>

  Remarks:
    None.
 *****************************************************************************/
void DRV_WIFI_SetPSK(uint8_t *p_psk);


/*******************************************************************************
  Function:
    void DRV_WIFI_DeviceInfoGet(DRV_WIFI_DEVICE_INFO *p_deviceInfo)

  Summary:
    Retrieves MRF24WG device information

  Description:
    This function retrieves MRF24WG device information.  See DRV_WIFI_DEVICE_INFO
    structure.

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    p_deviceInfo - Pointer where device info will be written

  Returns:
    None.

  Example:
    <code>
        DRV_WIFI_DEVICE_INFO    info;

        DRV_WIFI_DeviceInfoGet(&info);
    </code>

  Remarks:
    None.
 *****************************************************************************/
void DRV_WIFI_DeviceInfoGet(DRV_WIFI_DEVICE_INFO *p_deviceInfo);


/*******************************************************************************
  Function:
    void DRV_WIFI_MacAddressSet(uint8_t *p_mac)

  Summary:
    Uses a different MAC address for the MRF24W

  Description:
    Directs the MRF24W to use the input MAC address instead of its
    factory-default MAC address.  This function does not overwrite the factory
    default, which is in FLASH memory.

  Precondition:
    WiFi initialization must be complete.  Cannot be called when the MRF24W is in a
    connected state.

  Parameters:
    p_mac  - Pointer to 6-byte MAC that will be sent to MRF24WG

  Returns:
    None.

   Example:
    <code>
        uint8_t mac[6] = {0x00, 0x1e, 0xc0, 0x11, 0x22, 0x33};

        DRV_WIFI_MacAddressSet(mac);
    </code>

  Remarks:
    None.
 *****************************************************************************/
void DRV_WIFI_MacAddressSet(uint8_t *p_mac);


/*******************************************************************************
  Function:
    void DRV_WIFI_MacAddressGet(uint8_t *p_mac)

  Summary:
    Retrieves the MRF24WG MAC address

  Description:
    This function retrieves the MRF24WG MAC address.

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    p_mac  - Pointer where mac address will be written (must point to a 6-byte buffer)

  Returns:
    None.

  Example:
    <code>
        uint8_t mac[6];

        DRV_WIFI_MacAddressGet(mac);
    </code>

  Remarks:
    None.
 *****************************************************************************/
void DRV_WIFI_MacAddressGet(uint8_t *p_mac);


/*******************************************************************************
  Function:
    void DRV_WIFI_TxPowerMaxSet(int8_t maxTxPower)

  Summary:
    Sets the Tx max power on the MRF24WG0M.

  Description:
    After initialization the MRF24WG0M max Tx power is determined by a
    factory-set value.  This function can set a different maximum
    Tx power levels.  However, this function can never set a maximum Tx power
    greater than the factory-set value, which can be read via
    DRV_WIFI_TxPowerFactoryMaxGet().

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    maxTxPower - valid range (0 to 17 dBm)

  Returns:
    None.

  Example:
    <code>
        DRV_WIFI_TxPowerMaxSet(8); // set max Tx power to 8dBm
    </code>

  Remarks:
      No conversion of units needed, input to MRF24WG0M is in dBm.
  *****************************************************************************/
void DRV_WIFI_TxPowerMaxSet(int8_t maxTxPower);


/*******************************************************************************
  Function:
    void DRV_WIFI_TxPowerMaxGet(int8_t *p_maxTxPower);

  Summary:
    Gets the Tx max power on the MRF24WG0M.

  Description:
    Gets the Tx max power setting from the MRF24WG.

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    p_maxTxPower - pointer to where max power setting is written (dBm).

  Returns:
    None.

  Example:
    <code>
        int8_t maxPower;

        DRV_WIFI_TxPowerMaxGet(&maxPower);
    </code>

  Remarks:
    None
  *****************************************************************************/
void DRV_WIFI_TxPowerMaxGet(int8_t *p_maxTxPower);


/*******************************************************************************
  Function:
    void DRV_WIFI_TxPowerFactoryMaxGet(int8_t *p_factoryMaxTxPower)

  Summary:
    Retrieves the factory-set max Tx power from the MRF24W.

  Description:
    This function retrieves the factory-set max tx power from the MRF24WG.

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    p_factoryMaxTxPower - pointer to where factory max power is written (dbM)

  Returns:
    None.

  Example:
    <code>
        int8_t maxPower;

        DRV_WIFI_TxPowerFactoryMaxGet(&maxPower);
    </code>

  Remarks:
    None.
  *****************************************************************************/
void DRV_WIFI_TxPowerFactoryMaxGet(int8_t *p_factoryMaxTxPower);


/*******************************************************************************
  Function:
    void DRV_WIFI_PsPollEnable(DRV_WIFI_PS_POLL_CONTEXT *p_context);

  Summary:
    Enables PS Poll mode.

  Description:
    Enables PS Poll mode.  PS-Poll (Power-Save Poll) is a mode allowing for
    longer battery life.  The MRF24W coordinates with the Access Point to go
    to sleep and wake up at periodic intervals to check for data messages, which
    the Access Point will buffer.  The listenInterval in the Connection
    Algorithm defines the sleep interval.  By default, PS-Poll mode is disabled.

    When PS Poll is enabled, the WF Host Driver will automatically force the
    MRF24W to wake up each time the Host sends Tx data or a control message
    to the MRF24W.  When the Host message transaction is complete the
    MRF24W driver will automatically re-enable PS Poll mode.

    When the application is likely to experience a high volume of data traffic
    then PS-Poll mode should be disabled for two reasons:
    1. No power savings will be realized in the presence of heavy data traffic.
    2. Performance will be impacted adversely as the WiFi Host Driver
        continually activates and deactivates PS-Poll mode via SPI messages.

  Precondition:
    WiFi initialization must be complete.

  Parameters:
     p_context -  Pointer to ps poll context.  See DRV_WIFI_PS_POLL_CONTEXT
                  structure.

  Returns:
    None.

  Example:
    <code>
        DRV_WIFI_PS_POLL_CONTEXT context;

        context.listenInterval = DRV_WIFI_DEFAULT_PS_LISTEN_INTERVAL;
        context.dtimInterval   = DRV_WIFI_DEFAULT_PS_DTIM_INTERVAL;
        context.useDtim        = DRV_WIFI_DEFAULT_PS_DTIM_ENABLED;

        DRV_WIFI_PsPollEnable(&context);
    </code>

  Remarks:
    None.
  *****************************************************************************/
void DRV_WIFI_PsPollEnable(DRV_WIFI_PS_POLL_CONTEXT *p_context);

/*******************************************************************************
  Function:
    void DRV_WIFI_PsPollDisable(void)

  Summary:
    Disables PS-Poll mode.

  Description:
    Disables PS Poll mode.  The MRF24W will stay active and not go sleep.

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
        DRV_WIFI_PsPollDisable(&context);
    </code>

  Remarks:
    None.
  *****************************************************************************/
void DRV_WIFI_PsPollDisable(void);


/*******************************************************************************
  Function:
    void DRV_WIFI_PowerSaveStateGet(uint8_t *p_powerSaveState)

  Summary:
    Gets the current power-save state.

  Description:
    This function gets the current MRF24WG power save state.

    <table>
    powerSaveState                      Definition
    --------------                      ----------
    DRV_WIFI_PS_HIBERNATE               MRF24W in hibernate state
    DRV_WIFI_PS_PS_POLL_DTIM_ENABLED    MRF24W in PS-Poll mode with DTIM enabled
    DRV_WIFI_PS_PS_POLL_DTIM_DISABLED   MRF24W in PS-Poll mode with DTIM disabled
    DRV_WIFI_PS_POLL_OFF                MRF24W is not in any power-save state
    </table>

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    p_powerSaveState - Pointer to where power state is written (see description)

  Returns:
    None.

  Example:
      <code>
        uint8_t state;

        DRV_WIFI_PowerSaveStateGet(&state);
      </code>

  Remarks:
    None.
  *****************************************************************************/
void DRV_WIFI_PowerSaveStateGet(uint8_t *p_powerSaveState);

/*******************************************************************************
  Function:
    void DRV_WIFI_HibernateEnable(void)

  Summary:
    Puts the MRF24WG into hibernate mode.

  Description:
    Enables Hibernate mode on the MRF24W, which effectively turns off the
    device for maximum power savings.

    MRF24W state is not maintained when it transitions to hibernate mode.

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    None.

  Returns:
    None.

  Example:
      <code>
        DRV_WIFI_HibernateEnable();
      </code>

  Remarks:
    None
  *****************************************************************************/
void DRV_WIFI_HibernateEnable(void);

/*******************************************************************************
  Function:
    bool DRV_WIFI_isHibernateEnable(void)

  Summary:
    Checks if MRF24W is in hibernate mode

  Description:
    Checks if MRF24W is in hibernate mode

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    None.

  Returns:
    true or false

  Example:
      <code>
        bool flag;

        flag = DRV_WIFI_isHibernateEnable();
      </code>

  Remarks:
    None
  *****************************************************************************/
bool DRV_WIFI_isHibernateEnable(void);


/*******************************************************************************
  Function:
    void DRV_WIFI_RtsThresholdSet(uint16_t rtsThreshold)

  Summary:
    Sets the RTS Threshold.

  Description:
    Sets the RTS/CTS packet size threshold for when RTS/CTS frame will be sent.
    The default is 2347 bytes – the maximum for 802.11.  It is recommended that
    the user leave the default at 2347 until they understand the performance and
    power ramifications of setting it smaller.  Valid values are from 0 to
    DRV_WIFI_RTS_THRESHOLD_MAX (2347).

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    rtsThreshold - Value of the packet size threshold

  Returns:
    None.

  Example:
      <code>
        DRV_WIFI_RtsThresholdSet(DRV_WIFI_RTS_THRESHOLD_MAX);
      </code>

  Remarks:
    None.
 *****************************************************************************/
void DRV_WIFI_RtsThresholdSet(uint16_t rtsThreshold);


/*******************************************************************************
  Function:
    void DRV_WIFI_RtsThresholdGet(uint16_t *p_rtsThreshold)

  Summary:
    Gets the RTS Threshold

  Description:
    Gets the RTS/CTS packet size threshold.

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    p_rtsThreshold - Pointer to where RTS threshold is written

  Returns:
    None.

  Example:
      <code>
        uint16_t threshold;

        DRV_WIFI_RtsThresholdGet(&threshold);
      </code>

  Remarks:
    None.
 *****************************************************************************/
void DRV_WIFI_RtsThresholdGet(uint16_t *p_rtsThreshold);

/*******************************************************************************
  Function:
    void DRV_WIFI_RegionalDomainGet(uint8_t *p_regionalDomain)

  Summary:
    Retrieves the MRF24WG Regional domain

  Description:
    Gets the regional domain on the MRF24W.  Values are:
    * DRV_WIFI_DOMAIN_FCC
    * DRV_WIFI_DOMAIN_ETSI
    * DRV_WIFI_DOMAIN_JAPAN
    * DRV_WIFI_DOMAIN_OTHER

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    p_regionalDomain - Pointer where the regional domain value will be written

  Returns:
    None.

  Example:
      <code>
        uint8_t domain;

        DRV_WIFI_RegionalDomainGet(&domain);
      </code>

  Remarks:
    None.
 *****************************************************************************/
void DRV_WIFI_RegionalDomainGet(uint8_t *p_regionalDomain);  


/*******************************************************************************
  Function:
    void DRV_WIFI_SWMulticastFilterSet(DRV_WIFI_SWMULTICAST_CONFIG *p_config);

  Summary:
    Sets a multicast address filter using one of the software multicast filters.

  Description:
    This function allows the application to configure up to two Multicast
    Address Filters on the MRF24W.  If two active multicast filters are set
    up they are OR’d together – the MRF24W will receive and pass to the Host
    CPU received packets from either multicast address.
    The allowable values in p_config are:

    filterId -- DRV_WIFI_MULTICAST_FILTER_1 thru DRV_WIFI_MULTICAST_FILTER_16

    action   -- DRV_WIFI_MULTICAST_DISABLE_ALL (default)
                   The Multicast Filter discards all received
                   multicast messages – they will not be forwarded
                   to the Host PIC.  The remaining fields in this
                   structure are ignored.

                DRV_WIFI_MULTICAST_ENABLE_ALL
                   The Multicast Filter forwards all received multicast messages
                   to the Host PIC. The remaining fields in this structure are
                   ignored.

                DRV_WIFI_MULTICAST_USE_FILTERS
                   The MAC filter will be used and the remaining fields in this
                   structure configure which Multicast messages are forwarded to
                   the Host PIC.

    macBytes -- Array containing the MAC address to filter on (using the destination
                address of each incoming 802.11 frame).  Specific bytes with the
                MAC address can be designated as ‘don’t care’ bytes.  See macBitMask.
                This field in only used if action = DRV_WIFI_MULTICAST_USE_FILTERS.

    macBitMask -- A byte where bits 5:0 correspond to macBytes[5:0].  If the bit is
                  zero then the corresponding MAC byte must be an exact match for the
                  frame to be forwarded to the Host PIC.  If the bit is one then the
                  corresponding MAC byte is a ‘don’t care’ and not used in the
                  Multicast filtering process.  This field in only used if
                  action = DRV_WIFI_MULTICAST_USE_FILTERS.

  Precondition:
    WiFi initialization must be complete.  DRV_WIFI_SWMultiCastFilterEnable() must
    have been called previously.

  Parameters:
    p_config -- pointer to the multicast config structure.  See
                DRV_WIFI_SWMULTICAST_CONFIG structure.

  Returns:
    None.

  Example:
      <code>
            DRV_WIFI_SWMULTICAST_CONFIG config;
            uint8_t macMask[] = {01, 00, 5e, ff, ff, ff};  // (0xff are the don't care bytes)

            // configure software multicast filter 1 to filter multicast addresses that
            // start with 01:00:5e
            config.action = DRV_WIFI_MULTICAST_USE_FILTERS;
            config->filterId = DRV_WIFI_MULTICAST_FILTER_1;
            memcpy(config->macBytes, macMask, 6);
            config->macBitMask = 0x38;            // bits 5:3 = 1 (don't care on bytes 3,4,5)
                                                  // bits 2:0 = 0 (exact match required on bytes 0,1,2)
      </code>

  Remarks:
    Cannot mix hardware and software multicast filters..
 *****************************************************************************/
void DRV_WIFI_SWMulticastFilterSet(DRV_WIFI_SWMULTICAST_CONFIG *p_config);

/*******************************************************************************
  Function:
    void DRV_WIFI_SWMultiCastFilterEnable(void)

  Summary:
    Forces the MRF24WG to use software multicast filters instead of hardware
    multicast filters.

  Description:
    This function allows the application to configure up to max 16 software 
    multicast address Filters on the MRF24WG0MA/B.

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    None.

  Returns:
    None.

  Example:
      <code>
        DRV_WIFI_SWMultiCastFilterEnable();
      </code>

  Remarks:
    Cannot mix hardware and software multicast filters..
  *****************************************************************************/
void DRV_WIFI_SWMultiCastFilterEnable(void);

/*******************************************************************************
  Function:
    void DRV_WIFI_HWMulticastFilterSet(uint8_t multicastFilterId,
                                       uint8_t multicastAddress[6])

  Summary:
    Sets a multicast address filter using one of the two hardware multicast filters.

  Description:
    This function allows the application to configure up to two hardware Multicast
    Address Filters on the MRF24W.  If two active multicast filters are set
    up they are OR’d together – the MRF24W will receive and pass to the Host
    CPU received packets from either multicast address.
    The allowable values for the multicast filter are:
    * DRV_WIFI_MULTICAST_FILTER_1
    * DRV_WIFI_MULTICAST_FILTER_2

    By default, both Multicast Filters are inactive.

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    multicastFilterId - DRV_WIFI_MULTICAST_FILTER_1 or DRV_WIFI_MULTICAST_FILTER_2
    multicastAddress  - 6-byte address (all 0xFF will inactivate the filter)

  Returns:
      None.

  Example:
      <code>
        uint8_t multicastFilterId = DRV_WIFI_MULTICAST_FILTER_1;
        uint8_t filterAddress[6] = {0x00 0x01, 0x5e, 0x11, 0x22, 0x33};

        DRV_WIFI_HWMulticastFilterSet(multicastFilterId, filterAddress);
      </code>

  Remarks:
      Cannot mix hardware and software multicast filters.
  *****************************************************************************/
void DRV_WIFI_HWMulticastFilterSet(uint8_t multicastFilterId, uint8_t multicastAddress[6]);


/*******************************************************************************
  Function:
    void DRV_WIFI_HWMulticastFilterGet(uint8_t multicastFilterId,
                                       uint8_t multicastAddress[6])

  Summary:
    Gets a multicast address filter from one of the two multicast filters.

  Description:
    Gets the current state of the specified Multicast Filter.

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    multicastFilterId - DRV_WIFI_MULTICAST_FILTER_1 or DRV_WIFI_MULTICAST_FILTER_2
    multicastAddress - pointer to where 6-byte multicast filter is written.

  Returns:
      None.

  Example:
      <code>

        uint8_t filterAddress[6];

        DRV_WIFI_HWMulticastFilterGet(DRV_WIFI_MULTICAST_FILTER_1, filterAddress);
      </code>

  Remarks:
      None.
  *****************************************************************************/
void DRV_WIFI_HWMulticastFilterGet(uint8_t multicastFilterId, uint8_t multicastAddress[6]);


/*******************************************************************************
  Function:
    void DRV_WIFI_MacStatsGet(DRV_WIFI_MAC_STATS *p_macStats);

  Summary:
    Gets MAC statistics.

  Description:
    This function gets the various MAC layer stats as maintained by the MRF24WG.
 
  Precondition:
    WiFi initialization must be complete.

  Parameters:
    p_macStats - Pointer to where MAC statistics are written.  See DRV_WIFI_MAC_STATS
                 structure.

  Returns:
    None.

  Example:
      <code>
        DRV_WIFI_MAC_STATS macStats;

        DRV_WIFI_MacStatsGet(&macStats);
      </code>

  Remarks:
    None.
  *****************************************************************************/
void DRV_WIFI_MacStatsGet(DRV_WIFI_MAC_STATS *p_macStats);


/*******************************************************************************
  Function:
    void DRV_WIFI_ScanContextSet(DRV_WIFI_SCAN_CONTEXT *p_context);

  Summary:
    Sets the WiFi scan context.

  Description:
    This function sets the WiFi scan context.  The MRF24WG defaults are fine for
    most applications, but they can be changed by this function.

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    p_context - Pointer to scan context.  See DRV_WIFI_SCAN_CONTEXT structure.

  Returns:
    None.

  Example:
      <code>
        DRV_WIFI_SCAN_CONTEXT context;

        context.scantype = DRV_WIFI_ACTIVE_SCAN;
        context.scanCount      = 1;
        context.minChannelTime = 200;   // ms
        context.maxChannelTime = 400;   // ms
        context.probeDelay     = 20;    // uS

        DRV_WIFI_ScanContextSet(&context);
      </code>

  Remarks:
    None.
  *****************************************************************************/
void DRV_WIFI_ScanContextSet(DRV_WIFI_SCAN_CONTEXT *p_context);


/*******************************************************************************
  Function:
    void DRV_WIFI_ScanContextGet(DRV_WIFI_SCAN_CONTEXT *p_context);

  Summary:
    Gets the WiFi scan context.

  Description:
    This function gets the WiFi scan context.

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    p_context - Pointer to where scan context will be written.  See
                DRV_WIFI_SCAN_CONTEXT structure.

  Returns:
    None.

  Example:
      <code>
        DRV_WIFI_SCAN_CONTEXT context;

        DRV_WIFI_ScanContextSet(&context);
      </code>

  Remarks:
    None.
  *****************************************************************************/
void DRV_WIFI_ScanContextGet(DRV_WIFI_SCAN_CONTEXT *p_context);


/*******************************************************************************
  Function:
    uint16_t DRV_WIFI_Scan(bool scanAll)

  Summary:
    Commands the MRF24W to start a scan operation.  This will generate the
    WF_EVENT_SCAN_RESULTS_READY event.

  Description:
    Directs the MRF24W to initiate a scan operation.  The Host Application will
    be notified that the scan results are ready when it receives the
    WF_EVENT_SCAN_RESULTS_READY event.  The eventInfo field for this event will
    contain the number of scan results.  Once the scan results are ready they
    can be retrieved with DRV_WIFI_ScanGetResult().

    Scan results are retained on the MRF24W until:
    1. Calling DRV_WIFI_Scan() again (after scan results returned from previous
         call).
    2. MRF24W reset.

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    scanAll -
            If false:
            * If SSID defined then only scan results with that SSID are retained.
            * If SSID not defined then all scanned SSID’s will be retained
            * Only scan results from Infrastructure or AdHoc networks are retained
            * The channel list that is scanned will be determined from the channels
              passed in via DRV_WIFI_ChannelListSet().

            If true:
            * All scan results are retained (both Infrastructure and Ad Hoc
               networks).
            * All channels within the MRF24W’s regional domain will be
               scanned.

  Returns:
    None.

  Example:
      <code>
        DRV_WIFI_Scan(true);
      </code>

  Remarks:
    None.
  *****************************************************************************/
uint16_t DRV_WIFI_Scan(bool scanAll);


/*******************************************************************************
  Function:
    void DRV_WIFI_ScanGetResult(uint8_t listIndex, t_wfScanResult  *p_scanResult)

  Summary:
    Read selected scan results back from MRF24W.

  Description:
    After a scan has completed this function is used to read one scan result at
    a time from the MRF24WG.

  Precondition:
    WiFi initialization must be complete.  WF_EVENT_SCAN_RESULTS_READY event must have
    already occurrerd.

  Parameters:
    listIndex    - Index (0-based list) of the scan entry to retrieve.
    p_scanResult - Pointer to where scan result is written.  See DRV_WIFI_SCAN_RESULT
                   structure.

  Returns:
    None.

  Example:
      <code>
        DRV_WIFI_SCAN_RESULT scanResult;

        DRV_WIFI_ScanGetResult(0, &scanResult); // get first scan result in list
      </code>

  Remarks:
    None.
  *****************************************************************************/
void DRV_WIFI_ScanGetResult(uint8_t listIndex,  DRV_WIFI_SCAN_RESULT *p_scanResult);


/*******************************************************************************
  Function:
    void DRV_WIFI_GratuitousArpStart(uint8_t period);

  Summary:
    Starts a periodic gratuitous ARP response

  Description:
    This function starts a gratuitous ARP response to be periodically transmitted.

  Precondition:
    WiFi initialization must be complete.  Connection process must be complete.

  Parameters:
    period - period between gratuitous ARP, in seconds

  Returns:
    None.

  Example:
      <code>
        DRV_WIFI_GratuitousArpStart(10); // begin sending gratuitous ARP's every
                                         // 10 seconds.
      </code>

  Remarks:
    None.
  *****************************************************************************/
void DRV_WIFI_GratuitousArpStart(uint8_t period);


/*******************************************************************************
  Function:
    void DRV_WIFI_GratuitousArpStop(void);

  Summary:
    Stops a periodic gratuitous ARP.

  Description:
    This function stops a gratuitous ARP.

  Precondition:
    WiFi initialization must be complete.

  Parameters:
    None

  Returns:
    None.

  Example:
      <code>
        DRV_WIFI_GratuitousArpStop();
      </code>

  Remarks:
    None.
  *****************************************************************************/
void DRV_WIFI_GratuitousArpStop(void);




/*******************************************************************************
  Function:
    void DRV_WIFI_ProcessEvent(uint16_t event, uint16_t eventInfo);

  Summary:
    Processes WiFi event

  Description:
    This function is called to process a WiFi event,

  Precondition:
    TCPIP stack should be initialized.

  Parameters:
    event       - event code
    eventInfo   - additional information about the event.  Not all events
                  have associated info, in which case this value will be
                  set to DRV_WIFI_NO_ADDITIONAL_INFO (0xff)

  Returns:
    None

  Remarks:
    None.
  *****************************************************************************/
void DRV_WIFI_ProcessEvent(uint16_t event, uint16_t eventInfo);


/*******************************************************************************
  Function:
    bool DRV_WIFI_ConfigDataLoad(void);

  Summary:
    Loads configuration data from the board EEPROM.

  Description:
    This function loads configuration data from the board EEPROM.  If not present
    or corrupted then default values will be used.

  Precondition:
    TCPIP stack should be initialized.

  Parameters:
    None
 
  Returns:
    None

  Remarks:
    None.
  *****************************************************************************/
bool DRV_WIFI_ConfigDataLoad(void);


/*******************************************************************************
  Function:
    bool DRV_WIFI_ConfigDataSave(void);

  Summary:
    Save configuration data to the board EEPROM.

  Description:
    This function saves configuration data to the board EEPROM.

  Precondition:
    TCPIP stack should be initialized.

  Parameters:
    None

  Returns:
    None

  Remarks:
    None.
  *****************************************************************************/
bool DRV_WIFI_ConfigDataSave(void);


/*******************************************************************************
  Function:
    bool DRV_WIFI_ConfigDataErase(void);

  Summary:
    Erases configuration data from the board EEPROM.

  Description:
    This function erases configuration data from the board EEPROM.

  Precondition:
    TCPIP stack should be initialized.

  Parameters:
    None

  Returns:
    None

  Remarks:
    None.
  *****************************************************************************/
bool DRV_WIFI_ConfigDataErase(void);


/*******************************************************************************
  Function:
    void DRV_WIFI_ConfigDataPrint(void);

  Summary:
    Outputs to console the configuration data from the board EEPROM.

  Description:
    This function outputs configuration data from the board EEPROM.

  Precondition:
    TCPIP stack should be initialized.

  Parameters:
    None

  Returns:
    None

  Remarks:
    None.
  *****************************************************************************/
void DRV_WIFI_ConfigDataPrint(void);


#endif /* _DRV_WIFI_H */



