/*******************************************************************************
  Company:
    Microchip Technology Incorporated

  File Name:
    tcp.h

  Summary:
    Transmission Control Protocol (TCP) Communications Layer API

  Description:
    - Provides reliable, handshaked transport of application stream
      oriented data with flow control
    - Reference: RFC 793
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
FileName:  tcp.h
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
//DOM-IGNORE-END

#ifndef __TCP_H__
#define __TCP_H__


// *****************************************************************************
// *****************************************************************************
// Section: Data Types and Constants
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/*
  Type:
    TCP_PORT

  Summary:
    TCP Port

  Description:
    TCP Port Number identifier
*/
typedef uint16_t TCP_PORT;

// *****************************************************************************
/*
  Type:
    TCP_SOCKET

  Summary:
    TCP Socket

  Description:
    A TCP_SOCKET is stored as a single uint8_t
*/
typedef int16_t TCP_SOCKET;

// *****************************************************************************
/*
  Macro:
    INVALID_SOCKET

  Summary:
    Invalid Socket Indicator Macro

  Description:
    Indicates that the socket is invalid or could not be opened.
*/
#define INVALID_SOCKET      (-1)    // The socket is invalid or could not be opened

// *****************************************************************************
/*
  Structure:
    TCP_SOCKET_INFO

  Summary:
    TCP Socket Information

  Description:
    Information about a socket
*/
typedef struct
{
    IP_ADDRESS_TYPE     addressType;
    IP_MULTI_ADDRESS    remoteIPaddress;
    IP_MULTI_ADDRESS    localIPaddress;
    TCP_PORT            remotePort; // Port number associated with remote node
    TCP_PORT            localPort;  // local port number
} TCP_SOCKET_INFO;

// *****************************************************************************
/*
  Enumeration:
    TCP_ADJUST_FLAGS

  Summary:
    TCP Adjust Falgs

  Description:
    Adjust socket buffer sizes.
*/
typedef enum
{
    TCP_ADJUST_GIVE_REST_TO_RX  = 0x01,     // Resize flag: extra bytes go to RX
    TCP_ADJUST_GIVE_REST_TO_TX  = 0x02,     // Resize flag: extra bytes go to TX
    TCP_ADJUST_PRESERVE_RX      = 0x04,     // Resize flag: attempt to preserve RX buffer
    TCP_ADJUST_PRESERVE_TX      = 0x08,     // Resize flag: attempt to preserve TX buffer
    TCP_ADJUST_TX_ONLY          = 0x10,     // Resize flag: adjust the TX buffer only
    TCP_ADJUST_RX_ONLY          = 0x20,     // Resize flag: adjust the RX buffer only

}TCP_ADJUST_FLAGS;

// *****************************************************************************
/*
  Enumeration:
    TCP_SOCKET_OPTION

  Summary:
    TCP Socket Option

  Description:
    Socket options
*/
typedef enum
{
    TCP_OPTION_LINGER,              // The LINGER option controls the action taken when unsent data is queued on a socket and the socket is closed.
                                    // The linger option can be turned on/off and the timeout can be specified.
    TCP_OPTION_KEEPPALIVE,          // enable the use of keep-alive packets on TCP connections
                                    // The option can be turned on/off and the timeout can be specified
    TCP_OPTION_RX_BUFF,             // request different RX buffer size. Has to call TCPIP_TCP_OptionsGet to see the exact space
                                    // allocated
    TCP_OPTION_TX_BUFF,             // request different TX buffer size. Has to call TCPIP_TCP_OptionsGet to see the exact space
                                    // allocated
    TCP_OPTION_RX_TMO,              // specifies the RX timeout. If no data arrives in the specified timeout the socket is closed
    TCP_OPTION_TX_TMO,              // specifies the TX timeout. If no data can be sent in the specified timeout the socket is closed
    TCP_OPTION_NODELAY,             // enables the NO DELAY/Nagle algorithm functionality;
    TCP_OPTION_EXCLUSIVE_ADDRESS,   // enables a socket to be bound for exclusive access.
} TCP_SOCKET_OPTION;


// *****************************************************************************
/*
  Structure:
    TCP_OPTION_LINGER_DATA

  Summary:
    Linger options

  Description:
    Linger options
*/
typedef struct
{
    bool        lingerEnable;       // enable/disable linger; enabled by default for any socket
    bool        gracefulEnable;     // enable/disable graceful close; enabled by default for any socket
    uint16_t    lingerTmo;          // linger timeout in seconds (when enabled)
                                    // this option is not supported yet
}TCP_OPTION_LINGER_DATA;


// *****************************************************************************
/*
  Structure:
    TCP_MODULE_CONFIG

  Summary:
    TCP layer configuration/initialization

  Description:
    TCP layer configuration/initialization
*/
//
typedef struct
{
    int             nSockets;       // number of sockets to be created
    uint16_t        sktTxBuffSize;  // size of the socket tx buffer
    uint16_t        sktRxBuffSize;  // size of the socket rx buffer

} TCP_MODULE_CONFIG;


// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines - General
// *****************************************************************************
// *****************************************************************************


/*****************************************************************************
  Function:
     TCP_SOCKET TCPIP_TCP_ServerOpen(IP_ADDRESS_TYPE addType, TCP_PORT localPort,  IP_MULTI_ADDRESS* localAddress)

  Summary:
    Opens a TCP socket as a server.

  Description:
    Provides a unified method for opening TCP server sockets.

    Sockets are statically/dynamically allocated on boot, and can be claimed with this
    function and freed using TCPIP_TCP_Close.

  Precondition:
    TCP is initialized.

  Parameters:
    IP_ADDRESS_TYPE addType         -   The type of address being used. Example: IP_ADDRESS_TYPE_IPV4.
    TCP_PORT localPort              -   TCP port to listen on for connections.
    IP_MULTI_ADDRESS* localAddress  -   Local address to use.

  Returns:
    INVALID_SOCKET -  No sockets of the specified type were available to be
                      opened.
    Otherwise -       A TCP_SOCKET handle. Save this handle and use it when
                      calling all other TCP APIs.
 */
TCP_SOCKET  TCPIP_TCP_ServerOpen(IP_ADDRESS_TYPE addType, TCP_PORT localPort,  IP_MULTI_ADDRESS* localAddress);


/*****************************************************************************
  Function:
     TCP_SOCKET TCPIP_TCP_ClientOpen(IP_ADDRESS_TYPE addType, TCP_PORT remotePort, IP_MULTI_ADDRESS* remoteAddress)

  Summary:
    Opens a TCP socket as a client.

  Description:
    Provides a unified method for opening TCP client sockets.

    Sockets are dynamically allocated at stack initialization, and can be claimed with this
    function and freed using TCPIP_TCP_Abort or TCPIP_TCP_Close.

  Precondition:
    TCP is initialized.

  Parameters:
    IP_ADDRESS_TYPE addType         -   The type of address being used. Example: IP_ADDRESS_TYPE_IPV4.

    TCP_PORT remotePort             -   TCP port to connect to.
                                        The local port for client sockets will be automatically picked
                                        by the TCP module.

    IP_MULTI_ADDRESS* remoteAddress -   The remote address to be used.
                                        If 0 then the address is unspecified

  Returns:
    INVALID_SOCKET -  No sockets of the specified type were available to be
                      opened.
    Otherwise -       A TCP_SOCKET handle. Save this handle and use it when
                      calling all other TCP APIs.

 Remarks:
    IP_ADDRESS_TYPE_ANY is not supported (not a valid type for client open)!

    If the remoteAddress != 0 (and the address pointed by remoteAddress != 0)
    then the socket will immediately initiate a connection to the remote host

    If the remoteAddress is unspecified, then no connection is initiated.
    Client socket parameters can be se using TCPIP_TCP_Bind(), TCPIP_TCP_RemoteBind(), etc.
    calls and then connection initiated by calling TCPIP_TCP_Connect().

 */
TCP_SOCKET  TCPIP_TCP_ClientOpen(IP_ADDRESS_TYPE addType, TCP_PORT remotePort, IP_MULTI_ADDRESS* remoteAddress);


/******************************************************************************
  Function:
    bool  TCPIP_TCP_Bind(TCP_SOCKET hTCP, IP_ADDRESS_TYPE addType, TCP_PORT localPort,  IP_MULTI_ADDRESS* localAddress)

  Summary:
    Bind a socket to a local address
    This function is meant for unconnected server and client sockets.
    It is similar to TCPIP_TCP_SocketNetSet() that assigns a specific source interface for a socket.
    If localPort is 0 the stack will assign a unique local port

  Description:
    Sockets don't need specific binding, it is done automatically by the stack
    However, specific binding can be requested using these functions.
    Works for both client and server sockets.

  Precondition:
    TCP socket should have been opened with TCPIP_TCP_ServerOpen()/TCPIP_TCP_ClientOpen()().
    hTCP - valid socket

  Parameters:
    hTCP            -   Socket to bind
    addType         -   The type of address being used. Example: IP_ADDRESS_TYPE_IPV4.
    localPort       -   Local port to use
                        If 0,  the stack will assign a unique local port 
    localAddress    -   The local address to bind to.
                        Could be NULL if the local address does not need to be changed

  Returns:
    True of success
    false otherwise


  Remarks:
    The call should fail if the socket is already connected (both server and client sockets).
    However this is not currently implemented.
    It is the user's responsibility to call this function only for sockets that are not connected.
    Changing the socket parameters while the socket is connected will result
    in connection loss/unpredictable behavior.


 */
bool  TCPIP_TCP_Bind(TCP_SOCKET hTCP, IP_ADDRESS_TYPE addType, TCP_PORT localPort,  IP_MULTI_ADDRESS* localAddress);


/******************************************************************************
  Function:
    bool  TCPIP_TCP_RemoteBind(TCP_SOCKET hTCP, IP_ADDRESS_TYPE addType, TCP_PORT remotePort,  IP_MULTI_ADDRESS* remoteAddress)

  Summary:
    Bind a socket to a remote address
    This function is meant for unconnected server and client sockets.

  Description:
    Sockets don't need specific remote binding, they should accept connections on any incoming interface.
    Thus the binding is done automatically by the stack.
    However, specific remote binding can be requested using these functions.
    For a server socket it can be used to restrict accepting connections from  a specific remote host.
    For a client socket it will just change the default binding done when the socket was opened.

  Precondition:
    TCP socket should have been opened with TCPIP_TCP_ServerOpen()/TCPIP_TCP_ClientOpen()().
    hTCP - valid socket

  Parameters:
    hTCP            -   Socket to bind
    addType         -   The type of address being used. Example: IP_ADDRESS_TYPE_IPV4.
    remotePort      -   remote port to use
                        Could be 0 if the remote port does not need to be changed
    remoteAddress   -   The remote address to bind to.
                        Could be NULL if the remote address does not need to be changed

  Returns:
    True of success
    false otherwise


  Remarks:
    The socket remote port is changed only if a non-zero remotePort value is passed.
    The socket remote host address is changed only if a non-zero remoteAddress value is passed.

    The call should fail if the socket is already connected (both server and client sockets).
    However this is not currently implemented.
    It is the user's responsibility to call this function only for sockets that are not connected.
    Changing the socket parameters while the socket is connected will result
    in connection loss/unpredictable behavior.

  */
bool  TCPIP_TCP_RemoteBind(TCP_SOCKET hTCP, IP_ADDRESS_TYPE addType, TCP_PORT remotePort,  IP_MULTI_ADDRESS* remoteAddress);


/******************************************************************************
  Function:
    bool  TCPIP_TCP_OptionsSet(TCP_SOCKET hTCP, TCP_SOCKET_OPTION option, void* optParam)

  Summary:
    Allows setting options to a socket like adjust Rx/Tx buffer size, etc

  Description:
    Various options can be set at the socket level.
    This function provides compatibility with BSD implementations.

  Precondition:
    TCP socket should have been opened with TCPIP_TCP_ServerOpen()/TCPIP_TCP_ClientOpen()().
    hTCP - valid socket


  Parameters:
    hTCP            - socket to set options for
    option          - specific option to be set
    optParam        - the option value; this is option dependent
                        TCP_OPTION_LINGER               -- pointer to a TCP_OPTION_LINGER_DATA structure
                        TCP_OPTION_KEEPPALIVE           -- not supported yet
                        TCP_OPTION_RX_BUFF              -- size of the new RX buffer
                        TCP_OPTION_TX_BUFF              -- size of the new TX buffer
                        TCP_OPTION_RX_TMO               -- not supported yet
                        TCP_OPTION_TX_TMO               -- not supported yet
                        TCP_OPTION_NODELAY              -- boolean to enable/disable the NO DELAY functionality
                        TCP_OPTION_EXCLUSIVE_ADDRESS    -- not supported yet

  Returns:
    true if success
    false otherwise
  */
bool  TCPIP_TCP_OptionsSet(TCP_SOCKET hTCP, TCP_SOCKET_OPTION option, void* optParam);


/******************************************************************************
  Function:
    bool  TCPIP_TCP_OptionsGet(TCP_SOCKET hTCP, TCP_SOCKET_OPTION option, void* optParam)

  Summary:
    Allows getting the options for a socket like: current Rx/Tx buffer size, etc

  Description:
    Various options can be get at the socket level.
    This function provides compatibility with BSD implementations.

  Precondition:
    TCP socket should have been opened with TCPIP_TCP_ServerOpen()/TCPIP_TCP_ClientOpen()().
    hTCP - valid socket


  Parameters:
    hTCP            - socket to get options for
    option          - specific option to get
    optParam        - pointer to an area that will receive the option value; this is option dependent
                      the size of the area has to be large enough to accomodate the specific option
                        TCP_OPTION_LINGER               -- pointer to a TCP_OPTION_LINGER_DATA structure
                        TCP_OPTION_KEEPPALIVE           -- not supported yet
                        TCP_OPTION_RX_BUFF              -- size of the new RX buffer
                        TCP_OPTION_TX_BUFF              -- size of the new TX buffer
                        TCP_OPTION_RX_TMO               -- not supported yet
                        TCP_OPTION_TX_TMO               -- not supported yet
                        TCP_OPTION_NODELAY              -- pointer to boolean to return current NO DELAY status
                        TCP_OPTION_EXCLUSIVE_ADDRESS    -- not supported yet

  Returns:
    true if success
    false otherwise
  */
bool  TCPIP_TCP_OptionsGet(TCP_SOCKET hTCP, TCP_SOCKET_OPTION option, void* optParam);


/******************************************************************************
  Function:
    bool  TCPIP_TCP_IsConnected(TCP_SOCKET hTCP)

  Summary:
  Determines if a socket has an established connection.

  Description:
    This function determines if a socket has an established connection to
    a remote node.  Call this function after calling TCPIP_TCP_ServerOpen()/TCPIP_TCP_ClientOpen()
    to determine when the connection is set up and ready for use.  This function was
    historically used to check for disconnections, but TCPIP_TCP_WasReset is now a
    more appropriate solution.

  Precondition:
    TCP socket should have been opened with TCPIP_TCP_ServerOpen()/TCPIP_TCP_ClientOpen()().
    hTCP - valid socket

  Parameters:
  hTCP - The socket to check.

  Return Values:
    true - The socket has an established connection to a remote node.
    false - The socket is not currently connected.

  Remarks:
    A socket is said to be connected only if it is in the TCP_ESTABLISHED
    state.  Sockets in the process of opening or closing will return false.
  */
bool  TCPIP_TCP_IsConnected(TCP_SOCKET hTCP);


/*****************************************************************************
  Function:
    bool TCPIP_TCP_WasReset(TCP_SOCKET hTCP)

  Summary:
    Self-clearing semaphore inidicating socket reset.

  Description:
    This function is a self-clearing semaphore indicating whether or not
    a socket has been disconnected since the previous call.  This function
    works for all possible disconnections: a call to TCPIP_TCP_Disconnect, a FIN
    from the remote node, or an acknowledgement timeout caused by the loss
    of a network link.  It also returns true after the first call to TCPIP_TCP_Initialize.
    Applications should use this function to reset their state machines.

  Precondition:
    TCP is initialized.

  Parameters:
    hTCP - The socket to check.

  Return Values:
    true - The socket has been disconnected since the previous call.
    false - The socket has not been disconnected since the previous call.
 */
bool   TCPIP_TCP_WasReset(TCP_SOCKET hTCP);


/******************************************************************************
  Function:
    bool  TCPIP_TCP_Disconnect(TCP_SOCKET hTCP)

  Summary:
    Disconnects an open socket.

  Description:
	This function closes the TX side of a connection by sending a FIN (if 
	currently connected) to the remote node of the connection.
	
    If the socket has the linger option set (default), the queued TX data transmission will be attempted
    before sending the FIN.
    If the linger option is off, the queued TX data will be discarded.

    Please note that this call may fail in which case it can be re-issued.

  Precondition:
    TCP socket should have been opened with TCPIP_TCP_ServerOpen()/TCPIP_TCP_ClientOpen()().
    hTCP - valid socket

  Parameters:
    hTCP - Handle of the socket to disconnect.

  Returns:
	true if the call succeeded
    false otherwise; that means that the notification could not be sent to the remote host.
                     the call can be re-issued at a later time if desired

  Remarks:
	If the socket is using SSL, a CLOSE_NOTIFY record will be transmitted
	first to allow the SSL session to be resumed at a later time.
  */
bool  TCPIP_TCP_Disconnect(TCP_SOCKET hTCP);


/******************************************************************************
  Function:
    void  TCPIP_TCP_Abort(TCP_SOCKET hTCP, bool killSocket)

  Summary:
	Aborts a connection.

  Description:
	This function aborts a connection to a remote node by sending a RST (if 
	currently connected).
    Any pending TX/RX data is discarded.

    A client socket will always be closed and the associated resources released.
    The socket cannot be used again after this call.

    A server socket will abort the current connection:
    - if killSocket == false the socket will remain listening
    - if killSocket == true the socket will be closed and all associated resources released.
      The socket cannot be used again after this call.

  Precondition:
    TCP socket should have been opened with TCPIP_TCP_ServerOpen()/TCPIP_TCP_ClientOpen()().
    hTCP - valid socket

  Parameters:
    hTCP - Handle to the socket to disconnect.
    killSocket  - if true, it kills a server socket

  Returns:
    None
  */
void  TCPIP_TCP_Abort(TCP_SOCKET hTCP, bool killSocket);


/******************************************************************************
  Function:
    bool  TCPIP_TCP_Connect(TCP_SOCKET hTCP)

  Summary:
	Connects a client socket.

  Description:
	This function will try to initiate a connection on a client socket that's not connected yet.
    The client socket should have been created with  a call to TCPIP_TCP_ClientOpen 
    having the remoteAddress set to 0;


  Precondition:
    TCP socket should have been opened with TCPIP_TCP_ClientOpen() with an unspecified address.
    hTCP - valid socket

  Parameters:
    hTCP - Handle to the client socket to connect.

  Returns:
     true is the call succeeded
     false otherwise

  Remarks:
    the call will fail if the client socket has no remote host specified.
    Use TCPIP_TCP_RemoteBind() to specify a remote host address for the client socket.

  */
bool  TCPIP_TCP_Connect(TCP_SOCKET hTCP);



/******************************************************************************
  Function:
    void  TCPIP_TCP_Close(TCP_SOCKET hTCP)

  Summary:
	Disconnects an open socket and destroys the socket handle, releasing the associated resources.

  Description:
    1. If the graceful option is set for the socket (default):
        - a TCPIP_TCP_Disconnect will be tried.
          If the linger option is set (default) the TCPIP_TCP_Disconnect will try to send
          any queued TX data before issuing FIN.
          If the FIN send operation fails or the socket is not connected the abort is generated.

    2. If the graceful option is not set, or the previous step could not send the FIN:
       A TCPAbort() is called, sending a RST to the remote node. Communication is closed,
       the socket is no longer valid and the associated resources are freed.

  Precondition:
    TCP socket should have been opened with TCPIP_TCP_ServerOpen()/TCPIP_TCP_ClientOpen()().
    hTCP - valid socket

  Parameters:
    hTCP - Handle to the socket to disconnect and close.

  Returns:
    None
  */
void  TCPIP_TCP_Close(TCP_SOCKET hTCP);


/*****************************************************************************
  Function:
    bool TCPIP_TCP_SocketInfoGet(TCP_SOCKET hTCP, TCP_SOCKET_INFO* remoteInfo)

  Summary:
    Obtains information about a currently open socket.

  Description:
    Fills the provided TCP_SOCKET_INFO structure associated with this socket.  This
    contains the NODE_INFO structure with IP and MAC address (or gateway
    MAC) and the remote port.

  Precondition:
    TCP is initialized and the socket is connected.

  Parameters:
    hTCP - The socket to check.

  Returns:
    true if the call succeeded
    false if no such socket or the socket is not opened
 */
bool  TCPIP_TCP_SocketInfoGet(TCP_SOCKET hTCP, TCP_SOCKET_INFO* pInfo);


/*****************************************************************************
  Function:
    uint16_t TCPIP_TCP_PutIsReady(TCP_SOCKET hTCP)

  Summary:
    Determines how much free space is available in the TCP TX buffer.

  Description:
    Call this function to determine how many bytes can be written to the
    TCP TX buffer.  If this function returns zero, the application must
    return to the main stack loop before continuing in order to transmit
    more data.

  Precondition:
    TCP is initialized.

  Parameters:
    hTCP - The socket to check.

  Returns:
    The number of bytes available to be written in the TCP TX buffer.
 */
uint16_t  TCPIP_TCP_PutIsReady(TCP_SOCKET hTCP);


/*****************************************************************************
  Function:
    uint16_t TCPIP_TCP_ArrayPut(TCP_SOCKET hTCP, const uint8_t* data, uint16_t len)

  Description:
    Writes an array from RAM to a TCP socket.

  Precondition:
    TCP is initialized.

  Parameters:
    hTCP - The socket to which data is to be written.
    data - Pointer to the array to be written.
    len  - Number of bytes to be written.

  Returns:
    The number of bytes written to the socket.  If less than len, the
    buffer became full or the socket is not conected.
 */
uint16_t  TCPIP_TCP_ArrayPut(TCP_SOCKET hTCP, const uint8_t* Data, uint16_t Len);


/*****************************************************************************
  Function:
    const uint8_t* TCPIP_TCP_StringPut(TCP_SOCKET hTCP, const uint8_t* data)

  Description:
    Writes a null-terminated string from RAM to a TCP socket.  The
    null-terminator is not copied to the socket.

  Precondition:
    TCP is initialized.

  Parameters:
    hTCP - The socket to which data is to be written.
    data - Pointer to the string to be written.

  Returns:
    Pointer to the byte following the last byte written to the socket.  If
    this pointer does not dereference to a NUL byte, the buffer became full
    or the socket is not connected.

  Remarks:
    The return value of this function differs from that of TCPIP_TCP_ArrayPut.  To
    write long strings in a single state, initialize the *data pointer to the
    first byte, then call this function repeatedly (breaking to the main
    stack loop after each call) until the return value dereferences to a NUL
    byte.  Save the return value as the new starting *data pointer otherwise.
 */
const uint8_t*      TCPIP_TCP_StringPut(TCP_SOCKET hTCP, const uint8_t* Data);


/*****************************************************************************
  Function:
    bool TCPIP_TCP_Flush(TCP_SOCKET hTCP)

  Summary:
    Immediately transmits all pending TX data.

  Description:
    This function immediately transmits all pending TX data with a PSH
    flag.  If this function is not called, data will automatically be sent
    when either a) the TX buffer is half full or b) the
    TCP_AUTO_TRANSMIT_TIMEOUT_VAL (default: 40ms) has elapsed.

  Precondition:
    TCP is initialized and the socket is connected.

  Parameters:
    hTCP - The socket whose data is to be transmitted.

  Returns:
    None

  Remarks:
    SSL application data is automatically flushed, so this function has
    no effect for SSL sockets.
 */
bool  TCPIP_TCP_Flush(TCP_SOCKET hTCP);


/*****************************************************************************
  Function:
    uint16_t TCPIP_TCP_FifoTxFullGet(TCP_SOCKET hTCP)

  Description:
    Determines how many bytes are pending in the TCP TX FIFO.

  Precondition:
    TCP is initialized.

  Parameters:
    hTCP - The socket to check.

  Returns:
    Number of bytes pending to be flushed in the TCP TX FIFO.
 */
uint16_t  TCPIP_TCP_FifoTxFullGet(TCP_SOCKET hTCP);


/******************************************************************************
  Macro:
    TCPIP_TCP_FifoTxFreeGet(TCP_SOCKET hTCP)

  Summary:
    TCP Get TX First In, First Out Free

  Description:
    Alias to TCPIP_TCP_PutIsReady provided for API completeness

  Parameters:
    hTCP - The socket to check.

  Returns:
    The number of bytes available to be written in the TCP TX buffer.
*/
#define  TCPIP_TCP_FifoTxFreeGet(a)  TCPIP_TCP_PutIsReady(a)


/******************************************************************************
  Function:
    uint16_t  TCPIP_TCP_Put(TCP_SOCKET hTCP, uint8_t byte)

  Description:
    Writes a single byte to a TCP socket.

  Precondition:
    TCP socket should have been opened with TCPIP_TCP_ServerOpen()/TCPIP_TCP_ClientOpen()().
    hTCP - valid socket

  Parameters:
    hTCP - The socket to which data is to be written.
    byte - The byte to write.

  Return Values:
    0 - The byte was written to the transmit buffer.
    1 - The transmit buffer was full, or the socket is not connected.

  Remarks:
    Note that the following function is inefficient.
    A buffered approach (TCPIP_TCP_ArrayPut) should be preferred
  */
uint16_t  TCPIP_TCP_Put(TCP_SOCKET hTCP, uint8_t byte);


/*****************************************************************************
  Function:
    uint16_t TCPIP_TCP_GetIsReady(TCP_SOCKET hTCP)

  Summary:
    Determines how many bytes can be read from the TCP RX buffer.

  Description:
    Call this function to determine how many bytes can be read from the
    TCP RX buffer.  If this function returns zero, the application must
    return to the main stack loop before continuing in order to wait for
    more data to arrive.

  Precondition:
    TCP is initialized.

  Parameters:
    hTCP - The socket to check.

  Returns:
    The number of bytes available to be read from the TCP RX buffer.
  */
uint16_t  TCPIP_TCP_GetIsReady(TCP_SOCKET hTCP);


/*****************************************************************************
  Function:
    uint16_t TCPIP_TCP_ArrayGet(TCP_SOCKET hTCP, uint8_t* buffer, uint16_t len)

  Description:
    Reads an array of data bytes from a TCP socket's receive FIFO.  The data
    is removed from the FIFO in the process.

  Precondition:
    TCP is initialized.

  Parameters:
    hTCP - The socket from which data is to be read.
    buffer - Pointer to the array to store data that was read.
    len  - Number of bytes to be read.

  Returns:
    The number of bytes read from the socket.  If less than len, the
    RX FIFO buffer became empty or the socket is not conected.
 */
uint16_t  TCPIP_TCP_ArrayGet(TCP_SOCKET hTCP, uint8_t* buffer, uint16_t count);


/*****************************************************************************
  Function:
    uint8_t TCPIP_TCP_Peek(TCP_SOCKET hTCP, uint16_t wStart)

  Summary:
    Peaks at one byte in the TCP RX FIFO without removing it from the buffer.

  Description:
    Peaks at one byte in the TCP RX FIFO without removing it from the buffer.

  Precondition:
    TCP is initialized.

  Parameters:
    hTCP - The socket to peak from (read without removing from stream).
    wStart - Zero-indexed starting position within the FIFO to peek from.

  Return Values:
    Byte peeked from the RX FIFO.  If there is no data in the buffer or an
    illegal wStart starting offset is given, then an indeterminate value is
    returned.  The caller must ensure that valid parameters are passed to avoid
    (i.e ensure that TCPIP_TCP_GetIsReady() returns a number that is less than wStart
    before calling TCPIP_TCP_Peek()).

  Remarks:
    Use the TCPIP_TCP_ArrayPeek() function to read more than one byte.  It will
    perform better than calling TCPIP_TCP_Peek() in a loop.
 */
uint8_t  TCPIP_TCP_Peek(TCP_SOCKET hTCP, uint16_t wStart);


/*****************************************************************************
  Function:
    uint16_t TCPIP_TCP_ArrayPeek(TCP_SOCKET hTCP, uint8_t *vBuffer, uint16_t wLen, uint16_t wStart)

  Summary:
    Reads a specified number of data bytes from the TCP RX FIFO without
    removing them from the buffer.

  Description:
    Reads a specified number of data bytes from the TCP RX FIFO without
    removing them from the buffer.  No TCP control actions are taken as a
    result of this function (ex: no window update is sent to the remote node).

  Precondition:
    TCP is initialized.

  Parameters:
    hTCP - The socket to peak from (read without removing from stream).
    vBuffer - Destination to write the peeked data bytes.
    wLen - Length of bytes to peak from the RX FIFO and copy to vBuffer.
    wStart - Zero-indexed starting position within the FIFO to start peeking
        from.

  Return Values:
    Number of bytes actually peeked from the stream and copied to vBuffer.
    This value can be less than wLen if wStart + wLen is greater than the
    deepest possible character in the RX FIFO.

  Remarks:
    None
 */
uint16_t  TCPIP_TCP_ArrayPeek(TCP_SOCKET hTCP, uint8_t *vBuffer, uint16_t wLen, uint16_t wStart);


/*****************************************************************************
  Function:
    uint16_t TCPIP_TCP_FifoRxFreeGet(TCP_SOCKET hTCP)

  Description:
    Determines how many bytes are free in the RX FIFO.

  Precondition:
    TCP is initialized.

  Parameters:
    hTCP - The socket to check.

  Returns:
    The number of bytes free in the TCP RX FIFO.  If zero, no additional
    data can be received until the application removes some data using one
    of the TCPIP_TCP_Get family functions.
 */
uint16_t  TCPIP_TCP_FifoRxFreeGet(TCP_SOCKET hTCP);


// *****************************************************************************
/*
  Macro:
    TCPIP_TCP_FifoRxFullGet

  Summary:
    TCP Get Rx First In, First Out Full

  Description:
    Alias to TCPIP_TCP_GetIsReady provided for API completeness
*/
#define  TCPIP_TCP_FifoRxFullGet(a)  TCPIP_TCP_GetIsReady(a)


/*****************************************************************************
  Function:
    uint16_t TCPIP_TCP_Discard(TCP_SOCKET hTCP)

  Description:
    Discards any pending data in the TCP RX FIFO.

  Precondition:
    TCP is initialized.

  Parameters:
    hTCP - The socket whose RX FIFO is to be cleared.

  Returns:
    Number of bytes that have been discarded from the RX buffer.
 */
uint16_t TCPIP_TCP_Discard(TCP_SOCKET hTCP);


// *****************************************************************************
/*
  Function:
    uint16_t  TCPIP_TCP_Get(TCP_SOCKET hTCP, uint8_t* byte)

  Description:
    Retrieves a single byte to a TCP socket.

  Precondition:
    TCP socket should have been opened with TCPIP_TCP_ServerOpen()/TCPIP_TCP_ClientOpen()().
    hTCP - valid socket

  Parameters:
    hTCP - The socket from which to read.
    byte - Pointer to location in which the read byte should be stored.

  Return Values:
    1 - A byte was read from the buffer.
    0 - The buffer was empty, or the socket is not connected.

  Remarks:
    Note that the following function is inefficient.
    A buffered approach (TCPIP_TCP_ArrayGet) should be preferred
  */
uint16_t  TCPIP_TCP_Get(TCP_SOCKET hTCP, uint8_t* byte);


/*****************************************************************************
  Function:
    uint16_t TCPIP_TCP_Find(TCP_SOCKET hTCP, uint8_t cFind, uint16_t wStart, uint16_t wSearchLen, bool bTextCompare)

  Summary:
    Searches for a byte in the TCP RX buffer.

  Description:
    This function finds the first occurrance of a byte in the TCP RX
    buffer.  It can be used by an application to abstract searches
    out of their own application code.  For increased efficiency, the
    function is capable of limiting the scope of search to a specific
    range of bytes.  It can also perform a case-insensitive search if
    required.

    For example, if the buffer contains "I love PIC MCUs!" and the cFind
    byte is ' ', a value of 1 will be returned.

  Precondition:
    TCP is initialized.

  Parameters:
    hTCP - The socket to search within.
    cFind - The byte to find in the buffer.
    wStart - Zero-indexed starting position within the buffer.
    wSearchLen - Length from wStart to search in the buffer.
    bTextCompare - true for case-insensitive text search, false for binary search

  Return Values:
    0xFFFF - Search array not found
    Otherwise - Zero-indexed position of the first occurrance

  Remarks:
    Since this function usually must transfer data from external storage
    to internal RAM for comparison, its performance degrades significantly
    when the buffer is full and the array is not found.  For better
    performance, try to search for characters that are expected to exist or
    limit the scope of the search as much as possible.  The HTTP module,
    for example, uses this function to parse headers.  However, it searches
    for newlines, then the separating colon, then reads the header name to
    RAM for final comparison.  This has proven to be significantly faster
    than searching for full header name strings outright.
 */
uint16_t  TCPIP_TCP_Find(TCP_SOCKET hTCP, uint8_t cFind, uint16_t wStart, uint16_t wSearchLen, bool bTextCompare);


/*****************************************************************************
  Function:
    uint16_t TCPIP_TCP_ArrayFind(TCP_SOCKET hTCP, uint8_t* cFindArray, uint16_t wLen, uint16_t wStart, uint16_t wSearchLen, bool bTextCompare)

  Summary:
    Searches for a string in the TCP RX buffer.

  Description:
    This function finds the first occurrance of an array of bytes in the
    TCP RX buffer.  It can be used by an application to abstract searches
    out of their own application code.  For increased efficiency, the
    function is capable of limiting the scope of search to a specific
    range of bytes.  It can also perform a case-insensitive search if
    required.

    For example, if the buffer contains "I love PIC MCUs!" and the search
    array is "love" with a length of 4, a value of 2 will be returned.

  Precondition:
    TCP is initialized.

  Parameters:
    hTCP - The socket to search within.
    cFindArray - The array of bytes to find in the buffer.
    wLen - Length of cFindArray.
    wStart - Zero-indexed starting position within the buffer.
    wSearchLen - Length from wStart to search in the buffer.
    bTextCompare - true for case-insensitive text search, false for binary search

  Return Values:
    0xFFFF - Search array not found
    Otherwise - Zero-indexed position of the first occurrance

  Remarks:
    Since this function usually must transfer data from external storage
    to internal RAM for comparison, its performance degrades significantly
    when the buffer is full and the array is not found.  For better
    performance, try to search for characters that are expected to exist or
    limit the scope of the search as much as possible.  The HTTP module,
    for example, uses this function to parse headers.  However, it searches
    for newlines, then the separating colon, then reads the header name to
    RAM for final comparison.  This has proven to be significantly faster
    than searching for full header name strings outright.
 */
uint16_t  TCPIP_TCP_ArrayFind(TCP_SOCKET hTCP, const uint8_t* cFindArray, uint16_t wLen, uint16_t wStart, uint16_t wSearchLen, bool bTextCompare);


/*****************************************************************************
  Function:
    bool TCPIP_TCP_FifoSizeAdjust(TCP_SOCKET hTCP, uint16_t wMinRXSize, uint16_t wMinTXSize, TCP_ADJUST_FLAGS vFlags)

  Summary:
    Adjusts the relative sizes of the RX and TX buffers.

  Description:
    This function can be used to simultaneously adjust the sizes
    of the RX and TX FIFOs.

    Adjusting the size of the TX/RX FIFO on the fly can allow for optimal transmission speed
    for one-sided application protocols.
    For example, HTTP typically begins by receiving large amounts of data from the client,
    then switches to serving large amounts of data back.
    Adjusting the FIFO at these points can increase performance in systems that have
    limited resources.
    Once the FIFOs are adjusted, a window update is sent.

    The TCP_ADJUST_FLAGS control the distribution of the remaining available space
    between the TX and RX FIFOs.
    If neither or both of TCP_ADJUST_GIVE_REST_TO_TX and
    TCP_ADJUST_GIVE_REST_TO_RX are set, the function distributes the
    remaining space (if any) equally.
    If the new requested FIFOs space is greater that the old existing FIFOs space
    the TCP_ADJUST_GIVE_REST_TO_TX and TCP_ADJUST_GIVE_REST_TO_RX are ignored.

    TCP_ADJUST_PRESERVE_RX and TCP_ADJUST_PRESERVE_TX request the
    preserving of the existing data.
    Existing data can be preserved as long as the old data in the buffer
    does not exceed the capacity of the new buffer.

  Precondition:
    TCP is initialized.

  Parameters:
    hTCP        - The socket to be adjusted
    wMinRXSize  - Minimum number of bytes for the RX FIFO
    wMinTXSize  - Minimum number of bytes for the TX FIFO
    vFlags      - If TCP_ADJUST_TX_ONLY or TCP_ADJUST_RX_ONLY  are not set,
                    then the TX and RX bufferrs are evaluated together and any
                    combination of the following flags is valid:
                    TCP_ADJUST_GIVE_REST_TO_RX, TCP_ADJUST_GIVE_REST_TO_TX
                    TCP_ADJUST_PRESERVE_RX, TCP_ADJUST_PRESERVE_TX
                - If TCP_ADJUST_TX_ONLY or TCP_ADJUST_RX_ONLY is set
                    then TX and RX buffers are treated individually
                    and TCP_ADJUST_GIVE_REST_TO_TX, TCP_ADJUST_GIVE_REST_TO_RX
                    values are irrelevant.
                - TCP_ADJUST_TX_ONLY and TCP_ADJUST_RX_ONLY both set is invalid.


  Return Values:
    true - The FIFOs were adjusted successfully
    false - New RX and/or TX buffers could not be allocated
            and therefore the socket was left unchanged.

  Remarks:
    The function will automatically maintain minimal values for both TX and RX buffers.

    To avoid having a socket with no associated buffers, the function first
    allocates the new buffers and, if succeeded, it frees the old ones.

    The TX and RX FIFOs (buffers) associated with a socket
    are completely separate and independent.
    However, when TCP_ADJUST_TX_ONLY or TCP_ADJUST_RX_ONLY are not set,
    for the purpose of this function, the TX and RX FIFOs are considered
    to be contiguous so that the total FIFO space is divided between
    the TX and RX FIFOs.
    This provides bacward compatibility with previous versions of this function.

    The new flags TCP_ADJUST_TX_ONLY and TCP_ADJUST_RX_ONLY allow changing
    the size of TX and RX buffers independently.
    This is the preferred option.

    TX or RX associated buffer sizes can be changed too using the socket options.
    See TCPIP_TCP_OptionsSet.
 */
bool  TCPIP_TCP_FifoSizeAdjust(TCP_SOCKET hTCP, uint16_t wMinRXSize, uint16_t wMinTXSize, TCP_ADJUST_FLAGS vFlags);


/*****************************************************************************
  Function:
    bool TCPIP_TCP_SocketNetSet(TCP_SOCKET hTCP, TCPIP_NET_HANDLE hNet)

  Summary:
    Sets the interface for an TCP socket

  Description:
    This function sets the network interface for an TCP socket

  Precondition:
    TCP socket should have been opened with _TCP_Open().
    hTCP - valid socket

  Parameters:
    hTCP - The TCP socket
    hNet - interface handle.

  Returns:
    true if success
    false otherwise.

  Note: None
 */
bool   TCPIP_TCP_SocketNetSet(TCP_SOCKET hTCP, TCPIP_NET_HANDLE hNet);


/*****************************************************************************
  Function:
TCPIP_NET_HANDLE  TCPIP_TCP_SocketNetGet(TCP_SOCKET hTCP);

  Summary:
    Gets the MAC interface of an TCP socket

  Description:
	This function returns the interface handle of an TCP socket

  Precondition:
    TCP socket should have been opened with _TCP_Open().
    hTCP - valid socket

  Parameters:
    hTCP - The TCP socket

  Returns:
    the handle of the local interface this socket is bound to.
 */
TCPIP_NET_HANDLE  TCPIP_TCP_SocketNetGet(TCP_SOCKET hTCP);

#endif  // __TCP_H__

/******************************************************************************
 End of File
*/
