/*******************************************************************************
  MRF24W Driver Connection Manager

  FileName:   
    drv_wifi_connection_manager.c  
  
  Summary:
    Module for Microchip TCP/IP Stack
    
  Description:
    -Provides access to MRF24W WiFi controller
    -Reference: MRF24W Data sheet, IEEE 802.11 Standard
*******************************************************************************/

//DOM-IGNORE-BEGIN
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


/*
*********************************************************************************************************
*                                           INCLUDES                               
*********************************************************************************************************
*/
#include "tcpip/src/tcpip_private.h"

#if defined(TCPIP_IF_MRF24W)


extern void IgnoreNextMgmtResult();

/*
*********************************************************************************************************
*                                           LOCAL GLOBAL VARIABLES                               
*********************************************************************************************************
*/

static bool g_LogicalConnection = false;

#if defined(DERIVE_KEY_FROM_PASSPHRASE_IN_HOST)
extern TCPIP_MAC_RES pbkdf2_sha1(const char *passphrase, const char *ssid, uint16_t ssid_len,
                 uint16_t iterations, uint8_t *buf, uint16_t buflen);
#endif

static bool isDisconnectAllowed(void);

/*******************************************************************************
  Function:    
    void DRV_WIFI_Connect(void)

  Summary:
    Commands the MRF24W to start a connection.

  Description:
    Directs the Connection Manager to scan for and connect to a WiFi network.
    This function does not wait until the connection attempt is successful, but 
    returns immediately.  

    Note that if the Connection Profile being used has WPA or WPA2 security
    enabled and is using a passphrase, the connection manager will first 
    calculate the PSK key, and then start the connection process.  The key 
    calculation can take up to 30 seconds.

  Precondition:
    MACInit must be called first.

  Parameters:
    None
  Returns:
    None.
      
  Remarks:
    None.
  *****************************************************************************/
void DRV_WIFI_Connect()
{
    uint8_t  hdrBuf[4];

    /* Write out header portion of msg (which is whole msg, there is no data) */
    hdrBuf[0] = WF_MGMT_REQUEST_TYPE;    /* indicate this is a mgmt msg     */
    hdrBuf[1] = WF_CM_CONNECT_SUBYTPE;   /* mgmt request subtype            */  
    hdrBuf[2] = CPID;
    hdrBuf[3] = 0;   

    SendMgmtMsg(hdrBuf,
                sizeof(hdrBuf),
                NULL,
                0);

    /* wait for mgmt response, free after it comes in, don't need data bytes */
    WaitForMgmtResponse(WF_CM_CONNECT_SUBYTPE, FREE_MGMT_BUFFER);
}

static bool isDisconnectAllowed(void)
{
    uint8_t   connectionState;
  
    DRV_WIFI_ConnectionStateGet(&connectionState);
    if (connectionState == DRV_WIFI_CSTATE_CONNECTED_INFRASTRUCTURE || connectionState == DRV_WIFI_CSTATE_CONNECTED_ADHOC)
    {
        return true;
    }

    return false;
}


// *****************************************************************************
/* Function:
    uint16_t DRV_WIFI_Disconnect(void);

  Summary:
    Directs the MRF24WG to disconnect from a WiFi network.

  Description:
    This function causes the MRF24WG to disconnect from a WiFi network.  No event
    is generated when a connection is terminated via the function call.

  Parameters:
    None

 Returns:
    DRV_WIFI_SUCCESS or DRV_WIFI_ERROR_DISCONNECT_FAILED

*/
uint16_t DRV_WIFI_Disconnect(void)
{
    uint8_t  hdrBuf[2];

/* WARNING !!! : 
    * Disconnect is allowed only in connected state. 
    * If module FW is in the midst of connection ( or reconenction) process, then
    * disconnect can hammer connection process, and furthermore it may cause
    * fatal failure in module FW operation. To be safte to use disconnect, we strongly
    * recommend you to disable module FW connection manager by uncommenting
    * #define DISABLE_MODULE_FW_CONNECT_MANAGER_IN_INFRASTRUCTURE    
    * in WF_Config.h
    */
    if (!isDisconnectAllowed())
        return DRV_WIFI_ERROR_DISCONNECT_FAILED;

    hdrBuf[0] = WF_MGMT_REQUEST_TYPE;
    hdrBuf[1] = WF_CM_DISCONNECT_SUBYTPE;

    SendMgmtMsg(hdrBuf,
                sizeof(hdrBuf),
                NULL,
                0);
 
    /* wait for mgmt response, free after it comes in, don't need data bytes */
    WaitForMgmtResponse(WF_CM_DISCONNECT_SUBYTPE, FREE_MGMT_BUFFER);

    return DRV_WIFI_SUCCESS;
}    
    
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
void DRV_WIFI_ConnectionStateGet(uint8_t *p_state)
{
    uint8_t  hdrBuf[2];
    uint8_t  msgData[2];
    
    hdrBuf[0] = WF_MGMT_REQUEST_TYPE;
    hdrBuf[1] = WF_CM_GET_CONNECTION_STATUS_SUBYTPE;

    SendMgmtMsg(hdrBuf,
                sizeof(hdrBuf),
                NULL,
                0);

    /* wait for mgmt response, read data, free after read */
    WaitForMgmtResponseAndReadData(WF_CM_GET_CONNECTION_STATUS_SUBYTPE, 
                                   sizeof(msgData),                  /* num data bytes to read          */
                                   MGMT_RESP_1ST_DATA_BYTE_INDEX,    /* only used if num data bytes > 0 */
                                   msgData);                         /* only used if num data bytes > 0 */
    
    *p_state = msgData[0];        /* connection state */
    if ((*p_state == DRV_WIFI_CSTATE_CONNECTED_INFRASTRUCTURE) || (*p_state == DRV_WIFI_CSTATE_CONNECTED_ADHOC))
    {
        SetLogicalConnectionState(true);
    }
    else
    {
        SetLogicalConnectionState(false);
    }        
}  

/*******************************************************************************
  Function:    
    bool WFisConnected()

  Summary:
    Query the connection status of the MRF24W.

  Description:
    Determine the fine granularity status of the connection state of the
    MRF24W.

  Precondition:
    MACInit must be called first.

  Parameters:
    None.

  Returns:
    true if the MRF24W is either connected or attempting to connect.
    false for all other conditions.
      
  Remarks:
    None.
  *****************************************************************************/
bool WFisConnected()
{
    return g_LogicalConnection;   
}      

/*******************************************************************************
  Function:    
    void SetLogicalConnectionState(bool state)

  Summary:
    Sets the logical connection state.

  Description:
    Logically, if the MRF24W is either connected or trying to connect, then
    it is "connected".  For all other scenarios, the MRF24W is "not
    connected".

  Precondition:
    MACInit must be called first.

  Parameters:
    state - Current logical connection state of the MRF24W.

  Returns:
    None.
      
  Remarks:
    None.
  *****************************************************************************/
void SetLogicalConnectionState(bool state)
{
    g_LogicalConnection = state;
}

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
void DRV_WIFI_ConnectContextGet(DRV_WIFI_CONNECTION_CONTEXT *p_ctx)
{
    SendGetParamMsg(PARAM_CONNECT_CONTEXT, (uint8_t *)p_ctx, sizeof(*p_ctx));
}

#if defined(DERIVE_KEY_FROM_PASSPHRASE_IN_HOST)
/*******************************************************************************
  Function:    
    TCPIP_MAC_RES DRV_WIFI_ConvPassphraseToKey(uint8_t key_len, uint8_t *key, uint8_t ssid_len, uint8_t *ssid)

  Summary:
    Convert passphrase to key

  Description:

  Precondition:
    MACInit must be called first.

  Parameters:
    key_len : key length
    key : passphrase as an input. key as an output
    ssid_len : ssid length
    ssid : ssid

  Returns:
    TCPIP_MAC_RES.
      
  Remarks:
    None.
 *****************************************************************************/
TCPIP_MAC_RES DRV_WIFI_ConvPassphraseToKey(uint8_t key_len, uint8_t *key, uint8_t ssid_len, uint8_t *ssid)
{
    static uint8_t psk[32];
    TCPIP_MAC_RES RetCode;
	
    key[key_len] = '\0';
    RetCode= pbkdf2_sha1((const char *)key, (const char *)ssid, ssid_len, 4096, (uint8_t *)psk, 32);
    if( RetCode == TCPIP_MAC_RES_OK)
	{
	    memcpy(key, psk, 32);
    }
	return RetCode;
}

#endif // defined(DERIVE_KEY_FROM_PASSPHRASE_IN_HOST)


extern tMgmtIndicatePassphraseReady passphraseReady;
void WifiAsyncWpaButtonConnectTask(void)
{

    if( TCPIP_MAC_RES_OK == DRV_WIFI_ConvPassphraseToKey(passphraseReady.keyLen,
                                                     passphraseReady.key,
                                                     passphraseReady.ssidLen,
                                                     passphraseReady.ssid))
    {
        DRV_WIFI_SetPSK(passphraseReady.key);
    }
    else
    {
        WifiAsyncSetEventPending(ASYNC_WPABUTTON_CONNECT);
    }
}
#endif /* TCPIP_IF_MRF24W */

//DOM-IGNORE-END