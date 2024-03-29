/*******************************************************************************
  Trivial File Transfer Protocol (TFTP) Client

  Summary:
    Module for Microchip TCP/IP Stack
    
  Description:
    -Provides unreliable file upload and download services to other 
     applications which wish to connect to a remote UDP based TFTP 
     server.
    -Reference: RFC 1350
*******************************************************************************/

/*******************************************************************************
FileName:   TFTPc.c
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

#define __TFTPC_C

#include "tcpip_private.h"

#if defined(TCPIP_STACK_USE_TFTP_CLIENT)

// The TFTP state machine
typedef enum
{
    SM_TFTP_WAIT = 0,
    SM_TFTP_READY,
    SM_TFTP_WAIT_FOR_DATA,
    SM_TFTP_WAIT_FOR_ACK,
    SM_TFTP_DUPLICATE_ACK,
    SM_TFTP_SEND_ACK,
    SM_TFTP_SEND_LAST_ACK
} TFTP_STATE;

// Enumeration of TFTP opcodes
typedef enum
{
    TFTP_OPCODE_RRQ = 1,        // Get
    TFTP_OPCODE_WRQ,            // Put
    TFTP_OPCODE_DATA,           // Actual data
    TFTP_OPCODE_ACK,            // Ack for Get/Put
    TFTP_OPCODE_ERROR           // Error
} TFTP_OPCODE;


UDP_SOCKET _tftpSocket;         // TFTP Socket for TFTP server link
uint16_t _tftpError;                // Variable to preserve error condition causes for later transmission

static union
{
    struct
    {
        NODE_INFO _hostInfo;
    } group1;

    struct
    {
        TCPIP_UINT16_VAL _tftpBlockNumber;
        TCPIP_UINT16_VAL _tftpDuplicateBlock;
        TCPIP_UINT16_VAL _tftpBlockLength;
    } group2;
} MutExVar;     // Mutually Exclusive variable groups to conserve RAM.

// TFTP state machine tracker variable
static TFTP_STATE _tftpState;
// Tracker variable for the number of TFTP retries
static uint8_t _tftpRetries;
// Timing variable used to detect timeout conditions
static SYS_TICK _tftpStartTick;

// TFTP status flags
static union
{
    struct
    {
        unsigned int bIsFlushed : 1;
        unsigned int bIsAcked : 1;
        unsigned int bIsClosed : 1;
        unsigned int bIsClosing : 1;
        unsigned int bIsReading : 1;
    } bits;
    uint8_t Val;
} _tftpFlags;


// Private helper function
static void _TFTPSendFileName(TFTP_OPCODE command, uint8_t *fileName);
// Private helper function
static void _TFTPSendAck(TCPIP_UINT16_VAL blockNumber);


// Blank out DEBUG statements if not enabled.
#if defined(TFTP_DEBUG)
    #define DEBUG(a)        a
#else
    #define DEBUG(a)
#endif

// TCPIP_TFTP_RAMFileUploadToHost(), TCPIP_TFTP_FragRAMFileUploadToHost() and 
// TCPIP_TFTP_UploadStatusGet() functions require the DNS client module to be enabled 
// for them to work.  The RAM and const resources for these functions can be 
// preserved if the DNS client module isn't enabled.
#if defined(TCPIP_STACK_USE_DNS)

static const uint8_t *vUploadRemoteHost;
static const uint8_t *vUploadFilename;
static TFTP_CHUNK_DESCRIPTOR *uploadChunkDescriptor;
static uint16_t wUploadChunkOffset;
static int8_t smUpload = TFTP_UPLOAD_COMPLETE;
static TFTP_CHUNK_DESCRIPTOR *uploadChunkDescriptorForRetransmit;
static uint16_t wUploadChunkOffsetForRetransmit;

/*****************************************************************************
  Function:
	void TCPIP_TFTP_RAMFileUploadToHost(const uint8_t *vRemoteHost, 
								 const uint8_t *vFilename, 
								 uint8_t *vData, 
								 uint16_t wDataLength)

  Summary:
	Uploads a contiguous array of RAM bytes as a file to a remote TFTP server.
	
  Description:
	Uploads a contiguous array of RAM bytes as a file to a remote TFTP server.
	
  Precondition:
	None

  Parameters:
	vRemoteHost: const string of the remote TFTP server to upload to (ex: 
		"www.myserver.com").  For device architectures that make no distinction 
		between RAM and const pointers (PIC24, dsPIC and PIC32), this string must 
		remain allocated and unmodified in RAM until the TFTP upload process 
		completes (as indicated by TCPIP_TFTP_UploadStatusGet()).  
	vFilename: const string of the remote file to create/overwrite (ex: 
		"status.txt").  For device architectures that make no distinction 
		between RAM and const pointers (PIC24, dsPIC and PIC32), this string must 
		remain allocated and unmodified in RAM until the TFTP upload process 
		completes (as indicated by TCPIP_TFTP_UploadStatusGet()).
	vData: Pointer to a RAM array of data to write to the file.
	wDataLength: Number of bytes pointed to by vData.  This will be the final 
		file size of the uploaded file.  Note that since this is defined as a 
		uint16_t type, the maximum possible file size is 65535 bytes.  For longer 
		files, call the TCPIP_TFTP_FragRAMFileUploadToHost() function instead.

  Returns:
  	None
  
  Remarks:
	The DNS client module must be enabled to use this function.  i.e. 
	TCPIP_STACK_USE_DNS must be defined in tcpip_config.h.

  	Call the TCPIP_TFTP_UploadStatusGet() function to determine the status of the file 
  	upload.
  	
  	It is only possible to have one TFTP operation active at any given time.  
  	After starting a TFTP operation by calling TCPIP_TFTP_RAMFileUploadToHost() or 
  	TCPIP_TFTP_FragRAMFileUploadToHost(), you must wait until 
  	TCPIP_TFTP_UploadStatusGet() returns a completion status code (<=0) before calling 
  	any other TFTP API functions.
  ***************************************************************************/
void TCPIP_TFTP_RAMFileUploadToHost(const uint8_t *vRemoteHost, const uint8_t *vFilename, uint8_t *vData, uint16_t wDataLength)
{
	static TFTP_CHUNK_DESCRIPTOR chunk[2];
	chunk[0].vDataPointer = vData;
	chunk[0].wDataLength = wDataLength;
	chunk[1].vDataPointer = NULL;
	TCPIP_TFTP_FragRAMFileUploadToHost(vRemoteHost, vFilename, chunk);
}

/*****************************************************************************
  Function:
	void TCPIP_TFTP_FragRAMFileUploadToHost(const uint8_t *vRemoteHost, 
										   const uint8_t *vFilename, 
										   TFTP_CHUNK_DESCRIPTOR *vFirstChunkDescriptor)
  Summary:
	Uploads an random, potentially non-contiguous, array of RAM bytes as a file 
	to a remote TFTP server.
	
  Description:
	Uploads an random, potentially non-contiguous, array of RAM bytes as a file 
	to a remote TFTP server.
	
  Precondition:
	None

  Parameters:
	vRemoteHost: const string of the remote TFTP server to upload to (ex: 
		"www.myserver.com").  For device architectures that make no distinction 
		between RAM and const pointers (PIC24, dsPIC and PIC32), this string must 
		remain allocated and unmodified in RAM until the TFTP upload process 
		completes (as indicated by TCPIP_TFTP_UploadStatusGet()).  
	vFilename: const string of the remote file to create/overwrite (ex: 
		"status.txt").  For device architectures that make no distinction 
		between RAM and const pointers (PIC24, dsPIC and PIC32), this string must 
		remain allocated and unmodified in RAM until the TFTP upload process 
		completes (as indicated by TCPIP_TFTP_UploadStatusGet()).
	vFirstChunkDescriptor: Pointer to a static or global (persistent) array of 
		TFTP_CHUNK_DESCRIPTOR structures describing what RAM memory addresses 
		the file contents should be obtained from.  The 
		TFTP_CHUNK_DESCRIPTOR.vDataPointer field should be set to the memory 
		address of the data to transmit, and the 
		TFTP_CHUNK_DESCRIPTOR.wDataLength field should be set to the number of 
		bytes to transmit from the given pointer.  The TFTP_CHUNK_DESCRIPTOR 
		array must be terminated by a dummy descriptor whos 
		TFTP_CHUNK_DESCRIPTOR.vDataPointer pointer is set to NULL.  Refer to the 
		TCPIP_TFTP_RAMFileUploadToHost() API for an example calling sequence since it 
		merely a wrapper to this TCPIP_TFTP_FragRAMFileUploadToHost() function.

  Returns:
  	None
  
  Remarks:
	The DNS client module must be enabled to use this function.  i.e. 
	TCPIP_STACK_USE_DNS must be defined in tcpip_config.h.

  	Call the TCPIP_TFTP_UploadStatusGet() function to determine the status of the file 
  	upload.
  	
  	It is only possible to have one TFTP operation active at any given time.  
  	After starting a TFTP operation by calling TCPIP_TFTP_RAMFileUploadToHost() or 
  	TCPIP_TFTP_FragRAMFileUploadToHost(), you must wait until 
  	TCPIP_TFTP_UploadStatusGet() returns a completion status code (<=0) before calling 
  	any other TFTP API functions.
  ***************************************************************************/
void TCPIP_TFTP_FragRAMFileUploadToHost(const uint8_t *vRemoteHost, const uint8_t *vFilename, TFTP_CHUNK_DESCRIPTOR *vFirstChunkDescriptor)
{
	vUploadRemoteHost = vRemoteHost;
	vUploadFilename = vFilename;
	uploadChunkDescriptor = vFirstChunkDescriptor;
	uploadChunkDescriptorForRetransmit = vFirstChunkDescriptor;
	wUploadChunkOffset = 0;
	wUploadChunkOffsetForRetransmit = 0;
	if(smUpload == TFTP_UPLOAD_RESOLVE_HOST)
		TCPIP_DNS_UsageEnd();
	smUpload = TFTP_UPLOAD_GET_DNS;
}


/*****************************************************************************
  Function:
	int8_t TCPIP_TFTP_UploadStatusGet(void)
	
  Summary:
	Returns the TFTP file upload status started by calling the 
	TCPIP_TFTP_RAMFileUploadToHost() or TCPIP_TFTP_FragRAMFileUploadToHost() functions.
	
  Description:
	Returns the TFTP file upload status started by calling the 
	TCPIP_TFTP_RAMFileUploadToHost() or TCPIP_TFTP_FragRAMFileUploadToHost() functions.
	
  Precondition:
	None

  Parameters:
	None

  Returns:
  	A status code.  Negative results are fatal errors.  Positive results 
  	indicate the TFTP upload operation is still being processed.  A zero result 
  	indicates successful file upload completion (TFTP API is now idle and 
  	available for further calls).  Specific return values are as follows:
  	0 (TFTP_UPLOAD_COMPLETE): Upload completed successfully
  	1 (TFTP_UPLOAD_GET_DNS): Attempting to obtain DNS client module
  	2 (TFTP_UPLOAD_RESOLVE_HOST): Attempting to resolve TFTP hostname
  	3 (TFTP_UPLOAD_CONNECT): Attempting to ARP and contact the TFTP server
  	4 (TFTP_UPLOAD_SEND_FILENAME): Attempting to send the filename and receive 
  		acknowledgement.
  	5 (TFTP_UPLOAD_SEND_DATA): Attempting to send the file contents and receive 
  		acknowledgement.
  	6 (TFTP_UPLOAD_WAIT_FOR_CLOSURE): Attempting to send the final packet of 
  		file contents and receive acknowledgement.
  	-1 (TFTP_UPLOAD_HOST_RESOLVE_TIMEOUT): Couldn't resolve hostname
  	-2 (TFTP_UPLOAD_CONNECT_TIMEOUT): Couldn't finish ARP and reach server
  	-3 (TFTP_UPLOAD_SERVER_ERROR): TFTP server returned an error (ex: access 
  		denial) or file upload failed due to a timeout (partial file may have 
  		been uploaded).
  
  Remarks:
	The DNS client module must be enabled to use this function.  i.e. 
	TCPIP_STACK_USE_DNS must be defined in tcpip_config.h.
  ***************************************************************************/
int8_t TCPIP_TFTP_UploadStatusGet(void)
{
	TFTP_RESULT result;
	IPV4_ADDR ipRemote;
	uint16_t w, w2;
	uint8_t *vData;

	if(TCPIP_UDP_IsOpened(_tftpSocket)== false)
	{

		_tftpSocket = _TCPIP_UDP_SocketOpen((uint32_t)(ROM_PTR_BASE)vUploadRemoteHost,
										 UDP_OPEN_ROM_HOST,TFTP_CLIENT_PORT,
										 TFTP_SERVER_PORT);
		smUpload = TFTP_UPLOAD_CONNECT;
	}

	switch(smUpload)
	{
#if 0
	case TFTP_UPLOAD_GET_DNS:
        if(TCPIP_DNS_UsageBegin(0) != DNS_RES_OK)
			break;
		TCPIP_DNS_Resolve(vUploadRemoteHost, DNS_TYPE_A);
		smUpload = TFTP_UPLOAD_RESOLVE_HOST;
		break;

	case TFTP_UPLOAD_RESOLVE_HOST:
        DNS_RESULT dnsRes = TCPIP_DNS_IsResolved(vUploadRemoteHost, &ipRemote);
        if(dnsRes == DNS_RES_PENDING)
        {        
			break;
        }

		TCPIP_DNS_UsageEnd(pDnsIf);
        if(dnsRes < 0)
		{
			smUpload = TFTP_UPLOAD_HOST_RESOLVE_TIMEOUT;
			break;
		}
		TCPIP_TFTP_Open(&ipRemote);
		smUpload = TFTP_UPLOAD_CONNECT;
		break;
#endif
	case TFTP_UPLOAD_CONNECT:
		switch(TCPIP_TFTP_IsOpen())
		{
		case TFTP_OK:
			TFTPOpenFile(vUploadFilename, TFTP_FILE_MODE_WRITE);
			smUpload = TFTP_UPLOAD_SEND_FILENAME;
			break;
		case TFTP_TIMEOUT:
			smUpload = TFTP_UPLOAD_CONNECT_TIMEOUT;
			break;
		default:
			break;
		}
		break;

	case TFTP_UPLOAD_SEND_FILENAME:
		result = TCPIP_TFTP_FileIsOpen();
		switch(result)
		{
		case TFTP_OK:
			smUpload = TFTP_UPLOAD_SEND_DATA;
			break;
		case TFTP_RETRY:
			TFTPOpenFile(vUploadFilename, TFTP_FILE_MODE_WRITE);
			break;
		case TFTP_TIMEOUT:
			smUpload = TFTP_UPLOAD_CONNECT_TIMEOUT;
			break;
		case TFTP_ERROR:
			smUpload = TFTP_UPLOAD_SERVER_ERROR;
			break;
		default:
			break;
		}
		if(result != TFTP_OK)
			break;
		// No break when TCPIP_TFTP_FileIsOpen() returns TFTP_OK -- we need to immediately start sending data

	case TFTP_UPLOAD_SEND_DATA:
		switch(TCPIP_TFTP_IsReadyForPut())
		{
		case TFTP_OK:
			// Write blocksize bytes of data
			uploadChunkDescriptorForRetransmit = uploadChunkDescriptor;
			wUploadChunkOffsetForRetransmit = wUploadChunkOffset;
			vData = uploadChunkDescriptor->vDataPointer + wUploadChunkOffset;
			w = TFTP_BLOCK_SIZE;
			while(w)
			{
				w2 = uploadChunkDescriptor->wDataLength - wUploadChunkOffset;
				if(w2 > w)
					w2 = w;
				w -= w2;
				wUploadChunkOffset += w2;
				if(vData == NULL)
				{
					TCPIP_TFTP_FileClose();
					smUpload = TFTP_UPLOAD_WAIT_FOR_CLOSURE;
					break;
				}
				while(w2--)
				{
					TCPIP_TFTP_DataBytePut(*vData++);
				}
				if(wUploadChunkOffset == uploadChunkDescriptor->wDataLength)
				{
					uploadChunkDescriptor++;
					wUploadChunkOffset = 0;
					vData = uploadChunkDescriptor->vDataPointer;
				}
			}
			break;

		case TFTP_RETRY:
			uploadChunkDescriptor = uploadChunkDescriptorForRetransmit;
			wUploadChunkOffset = wUploadChunkOffsetForRetransmit;
			break;

		case TFTP_TIMEOUT:
		case TFTP_ERROR:
			smUpload = TFTP_UPLOAD_SERVER_ERROR;
			break;

		default:
			break;
		}
		break;

	case TFTP_UPLOAD_WAIT_FOR_CLOSURE:
		switch(TCPIP_TFTP_FileIsClosed())
		{
		case TFTP_OK:
			smUpload = TFTP_UPLOAD_COMPLETE;
			TCPIP_UDP_Close(_tftpSocket);
			break;
		case TFTP_RETRY:
			uploadChunkDescriptor = uploadChunkDescriptorForRetransmit;
			wUploadChunkOffset = wUploadChunkOffsetForRetransmit;
			smUpload = TFTP_UPLOAD_SEND_DATA;
			break;
		case TFTP_TIMEOUT:
		case TFTP_ERROR:
			smUpload = TFTP_UPLOAD_SERVER_ERROR;
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}
	
	return smUpload;
}
#endif


/*********************************************************************
 * Function:        void TCPIP_TFTP_Open(IPV4_ADDR *host)
 *
 * Summary:         Initializes TFTP module.
 *
 * PreCondition:    UDP module is already initialized
 *                  and at least one UDP socket is available.
 *
 * Input:           host        - IP address of remote TFTP server
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Initiates ARP for given host and prepares
 *                  TFTP module for next sequence of function calls.
 *
 * Note:            Use TCPIP_TFTP_IsOpen() to check if a connection was
 *                  successfully opened or not.
 *
 ********************************************************************/
void TCPIP_TFTP_Open(IPV4_ADDR *host)
{
    DEBUG(printf("Opening a connection..."));

    // Remember this address locally.
    MutExVar.group1._hostInfo.IPAddr.Val = host->Val;

    // Initiate ARP resolution.
   // TCPIP_ARP_Resolve(&MutExVar.group1._hostInfo.IPAddr);

    // Wait for ARP to get resolved.
    _tftpState = SM_TFTP_WAIT;

    // Mark this as start tick to detect timeout condition.
    _tftpStartTick = SYS_TICK_Get();

    // Forget about all previous attempts.
    _tftpRetries = 1;

}



/*********************************************************************
 * Function:        TFTP_RESULT TCPIP_TFTP_IsOpen(void)
 *
 * Summary:         Determines if the TFTP connection is open.
 *
 * PreCondition:    TCPIP_TFTP_Open() is already called.
 *
 * Input:           None
 *
 * Output:          TFTP_OK if previous call to TCPIP_TFTP_Open is complete
 *
 *                  TFTP_TIMEOUT if remote host did not respond to
 *                          previous ARP request.
 *
 *                  TFTP_NOT_READY if remote has still not responded
 *                          and timeout has not expired.
 *
 * Side Effects:    None
 *
 * Overview:        Waits for ARP reply and opens a UDP socket
 *                  to perform further TFTP operations.
 *
 * Note:            Once opened, application may keep TFTP socket
 *                  open and future TFTP operations.
 *                  If TFTPClose() is called to close the connection
 *                  TCPIP_TFTP_Open() must be called again before performing
 *                  any other TFTP operations.
 ********************************************************************/
TFTP_RESULT TCPIP_TFTP_IsOpen(void)
{
    switch(_tftpState)
    {
    default:
		_tftpState = SM_TFTP_READY;
#if 0
        DEBUG(printf("Resolving remote IP...\n"));

        // Check to see if adddress is resolved.
        if ( TCPIP_ARP_IsResolved(&MutExVar.group1._hostInfo.IPAddr,
                           &MutExVar.group1._hostInfo.MACAddr) )
        {
            _tftpSocket = _TCPIP_UDP_SocketOpen(TFTP_CLIENT_PORT,
                                  &MutExVar.group1._hostInfo,
                                  TFTP_SERVER_PORT);
            _tftpState = SM_TFTP_READY;
        }
        else
            break;
#endif		

    case SM_TFTP_READY:
        // Wait for UDP to be ready.  Immediately after this user will
        // may TFTPGetFile or TFTPPutFile and we have to make sure that
        // UDP is read to transmit.  These functions do not check for
        // UDP to get ready.
        if ( UDPIsPutReady(_tftpSocket) )
            return TFTP_OK;
    }

    // Make sure that we do not do this forever.
    if ( SYS_TICK_Get() - _tftpStartTick >= (TFTP_ARP_TIMEOUT_VAL * SYS_TICK_TicksPerSecondGet()) )
    {
        _tftpStartTick = SYS_TICK_Get();

        // Forget about all previous attempts.
        _tftpRetries = 1;

        return TFTP_TIMEOUT;
    }

    return TFTP_NOT_READY;
}



/*********************************************************************
 * Function:        void TFTPOpenFile(const char *fileName,
 *                                    TFTP_FILE_MODE mode)
 *
 * Summary:         Prepares and sends TFTP file name and mode packet.
 *
 * PreCondition:    TFPTIsFileOpenReady() = true
 *
 * Input:           fileName        - File name that is to be opened.
 *                  mode            - Mode of file access
 *                                    Must be
 *                                      TFTP_FILE_MODE_READ for read
 *                                      TFTP_FILE_MODE_WRITE for write
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Prepares and sends TFTP file name and mode packet.
 *
 * Note:            By default, this funciton uses "octet" or binary
 *                  mode of file transfer.
 *                  Use TCPIP_TFTP_FileIsOpen() to check if file is
 *                  ready to be read or written.
 ********************************************************************/
void TFTPOpenFile(const uint8_t *fileName, TFTP_FILE_MODE mode)
{
    DEBUG(printf("Opening file...\n"));

    // Set TFTP Server port.  If this is the first call, remotePort
    // must have been set by TCPIP_TFTP_Open().  But if caller does not do
    // TCPIP_TFTP_Open for every transfer, we must reset remote port.
    // Most TFTP servers accept connection TFTP port. but once
    // connection is established, they use other temp. port,
    UDPSocketDcpt[_tftpSocket].remotePort = TFTP_SERVER_PORT;

    // Tell remote server about our intention.
    _TFTPSendFileName(mode, fileName);

    // Clear all flags.
    _tftpFlags.Val = 0;

    // Remember start tick for this operation.
    _tftpStartTick = SYS_TICK_Get();

    // Depending on mode of operation, remote server will respond with
    // specific block number.
    if ( mode == TFTP_FILE_MODE_READ )
    {
        // Remember that we are reading a file.
        _tftpFlags.bits.bIsReading = true;


        // For read operation, server would respond with data block of 1.
        MutExVar.group2._tftpBlockNumber.Val = 1;

        // Next packet would be the data packet.
        _tftpState = SM_TFTP_WAIT_FOR_DATA;
    }

    else
    {
        // Remember that we are writing a file.
        _tftpFlags.bits.bIsReading = false;

        // For write operation, server would respond with data block of 0.
        MutExVar.group2._tftpBlockNumber.Val = 0;

        // Next packet would be the ACK packet.
        _tftpState = SM_TFTP_WAIT_FOR_ACK;
    }
}




/*********************************************************************
 * Function:        TFTP_RESULT TCPIP_TFTP_FileIsOpen(void)
 *
 * Summary:         Determines if file has been opened.
 *
 * PreCondition:    TFTPOpenFile() is called.
 *
 * Input:           None
 *
 * Output:          TFTP_OK if file is ready to be read or written
 *
 *                  TFTP_RETRY if previous attempt was timed out
 *                  needs to be retried.
 *
 *                  TFTP_TIMEOUT if all attempts were exhausted.
 *
 *                  TFTP_ERROR if remote server responded with
 *                  error
 *
 *                  TFTP_NOT_READY if file is not yet opened.
 *
 * Side Effects:    None
 *
 * Overview:        Waits for remote server response regarding
 *                  previous attempt to open file.
 *                  If no response is received within specified
 *                  timeout, fnction returns with TFTP_RETRY
 *                  and application logic must issue another
 *                  TFTPFileOpen().
 *
 * Note:            None
 ********************************************************************/
TFTP_RESULT TCPIP_TFTP_FileIsOpen(void)
{
    if ( _tftpFlags.bits.bIsReading )
        return TCPIP_TFTP_DataIsGetReady();

    else
        return TCPIP_TFTP_IsReadyForPut();
}




/*********************************************************************
 * Function:        TFTP_RESULT TCPIP_TFTP_DataIsGetReady(void)
 *
 * Summary:         Determines if a data block is ready to be read.
 *
 * PreCondition:    TFTPOpenFile() is called with TFTP_FILE_MODE_READ
 *                  and TCPIP_TFTP_FileIsOpen() returned with true.
 *
 * Input:           None
 *
 * Output:          TFTP_OK if it there is more data byte available
 *                  to read
 *
 *                  TFTP_TIMEOUT if timeout occurred waiting for
 *                  new data.
 *
 *                  TFTP_END_OF_FILE if end of file has reached.
 *
 *                  TFTP_ERROR if remote server returned ERROR.
 *                      Actual error code may be read by calling
 *                      TFTPGetError()
 *
 *                  TFTP_NOT_READY if still waiting for new data.
 *
 * Side Effects:    None
 *
 * Overview:        Waits for data block.  If data block does not
 *                  arrive within specified timeout, it automatically
 *                  sends out ack for previous block to remind
 *                  server to send next data block.
 *                  If all attempts are exhausted, it returns with
 *                  TFTP_TIMEOUT.
 *
 * Note:            By default, this funciton uses "octet" or binary
 *                  mode of file transfer.
 ********************************************************************/
TFTP_RESULT TCPIP_TFTP_DataIsGetReady(void)
{
    TCPIP_UINT16_VAL opCode;
    TCPIP_UINT16_VAL blockNumber;
    bool bTimeOut;


    // Check to see if timeout has occurred.
    bTimeOut = false;
    if ( SYS_TICK_Get() - _tftpStartTick >= (TFTP_GET_TIMEOUT_VAL * SYS_TICK_TicksPerSecondGet()) )
    {
        bTimeOut = true;
        _tftpStartTick = SYS_TICK_Get();
    }


    switch(_tftpState)
    {
    case SM_TFTP_WAIT_FOR_DATA:
        // If timeout occurs in this state, it may be because, we have not
        // even received very first data block or some in between block.
        if ( bTimeOut == true )
        {
            bTimeOut = false;

            if ( _tftpRetries++ > (TFTP_MAX_RETRIES-1) )
            {
                DEBUG(printf("TCPIP_TFTP_DataIsGetReady(): Timeout.\n"));

                // Forget about all previous attempts.
                _tftpRetries = 1;

                return TFTP_TIMEOUT;
            }

            // If we have not even received first block, ask application
            // retry.
            if ( MutExVar.group2._tftpBlockNumber.Val == 1u )
            {
                DEBUG(printf("TCPIP_TFTP_DataIsGetReady(): TCPIP_TFTP_Open Retry.\n"));
                return TFTP_RETRY;
            }
            else
            {
                DEBUG(printf("TCPIP_TFTP_DataIsGetReady(): ACK Retry #%d...,\n", _tftpRetries));

                // Block number was already incremented in last ACK attempt,
                // so decrement it.
                MutExVar.group2._tftpBlockNumber.Val--;

                // Do it.
                _tftpState = SM_TFTP_SEND_ACK;
                break;
            }
        }

        // For Read operation, server will respond with data block.
        if ( !TCPIP_UDP_GetIsReady(_tftpSocket) )
            break;

        // Get opCode
        TCPIP_UDP_Get(&opCode.v[1]);
        TCPIP_UDP_Get(&opCode.v[0]);

        // Get block number.
        TCPIP_UDP_Get(&blockNumber.v[1]);
        TCPIP_UDP_Get(&blockNumber.v[0]);

        // In order to read file, this must be data with block number of 0.
        if ( opCode.Val == (uint16_t)TFTP_OPCODE_DATA )
        {
            // Make sure that this is not a duplicate block.
            if ( MutExVar.group2._tftpBlockNumber.Val == blockNumber.Val )
            {
                // Mark that we have not acked this block.
                _tftpFlags.bits.bIsAcked = false;

                // Since we have a packet, forget about previous retry count.
                _tftpRetries = 1;

                _tftpState = SM_TFTP_READY;
                return TFTP_OK;
            }

            // If received block has already been received, simply ack it
            // so that Server can "get over" it and send next block.
            else if ( MutExVar.group2._tftpBlockNumber.Val > blockNumber.Val )
            {
                DEBUG(printf("TCPIP_TFTP_DataIsGetReady(): "\
                            "Duplicate block %d received - droping it...\n", \
                            blockNumber.Val));
                MutExVar.group2._tftpDuplicateBlock.Val = blockNumber.Val;
                _tftpState = SM_TFTP_DUPLICATE_ACK;
            }
#if defined(TFTP_DEBUG)
            else
            {
                DEBUG(printf("TCPIP_TFTP_DataIsGetReady(): "\
                             "Unexpected block %d received - droping it...\n", \
                             blockNumber.Val));
            }
#endif
        }
        // Discard all unexpected and error blocks.
        TCPIP_UDP_Discard();

        // If this was an error, remember error code for later delivery.
        if ( opCode.Val == (uint16_t)TFTP_OPCODE_ERROR )
        {
            _tftpError = blockNumber.Val;
            return TFTP_ERROR;
        }

        break;

    case SM_TFTP_DUPLICATE_ACK:
        if ( UDPIsPutReady(_tftpSocket) )
        {
            _TFTPSendAck(MutExVar.group2._tftpDuplicateBlock);
            _tftpState = SM_TFTP_WAIT_FOR_DATA;
        }
        break;

    case SM_TFTP_READY:
        if ( TCPIP_UDP_GetIsReady(_tftpSocket) )
        {
            _tftpStartTick = SYS_TICK_Get();
            return TFTP_OK;
        }

        // End of file is reached when data block is less than 512 bytes long.
        // To reduce code, only MSB compared against 0x02 (of 0x200 = 512) to
        // determine if block is less than 512 bytes long or not.
        else if ( MutExVar.group2._tftpBlockLength.Val == 0u ||
                  MutExVar.group2._tftpBlockLength.v[1] < TFTP_BLOCK_SIZE_MSB )
            _tftpState = SM_TFTP_SEND_LAST_ACK;
        else
            break;


    case SM_TFTP_SEND_LAST_ACK:
    case SM_TFTP_SEND_ACK:
        if ( UDPIsPutReady(_tftpSocket) )
        {
            _TFTPSendAck(MutExVar.group2._tftpBlockNumber);

            // This is the next block we are expecting.
            MutExVar.group2._tftpBlockNumber.Val++;

            // Remember that we have already acked current block.
            _tftpFlags.bits.bIsAcked = true;

            if ( _tftpState == SM_TFTP_SEND_LAST_ACK )
                return TFTP_END_OF_FILE;

            _tftpState = SM_TFTP_WAIT_FOR_DATA;
        }
        break;

	// Suppress compiler warnings on unhandled SM_TFTP_WAIT and 
	// SM_TFTP_WAIT_FOR_ACK states.
    default:	
    	break;
    }



    return TFTP_NOT_READY;
}



/*********************************************************************
 * Function:        uint8_t TCPIP_TFTP_DataByteGet(void)
 *
 * Summary:         Gets a data byte from data that was read.
 *
 * PreCondition:    TFTPOpenFile() is called with TFTP_FILE_MODE_READ
 *                  and TCPIP_TFTP_DataIsGetReady() = true
 *
 * Input:           None
 *
 * Output:          data byte as received from remote server.
 *
 * Side Effects:    None
 *
 * Overview:        Fetches next data byte from TFTP socket.
 *                  If end of data block is reached, it issues
 *                  ack to server so that next data block can be
 *                  received.
 *
 * Note:            Use this function to read file from server.
 ********************************************************************/
uint8_t TCPIP_TFTP_DataByteGet(void)
{
    uint8_t v;

    // Read byte from UDP
    TCPIP_UDP_Get(&v);

    // Update block length
    MutExVar.group2._tftpBlockLength.Val++;

    // Check to see if entire data block is fetched.
    // To reduce code, MSB is compared for 0x02 (of 0x200 = 512).
    if ( MutExVar.group2._tftpBlockLength.v[1] == TFTP_BLOCK_SIZE_MSB )
    {
        // Entire block was fetched.  Discard everything else.
        TCPIP_UDP_Discard();

        // Remember that we have flushed this block.
        _tftpFlags.bits.bIsFlushed = true;

        // Reset block length.
        MutExVar.group2._tftpBlockLength.Val = 0;

        // Must send ACK to receive next block.
        _tftpState = SM_TFTP_SEND_ACK;
    }

    return v;
}




/*********************************************************************
 * Function:        void TCPIP_TFTP_FileClose(void)
 *
 * Summary:         Sends file closing messages.
 *
 * PreCondition:    TFTPOpenFile() was called and TCPIP_TFTP_FileIsOpen()
 *                  had returned with TFTP_OK.
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        If file is opened in read mode, it makes sure
 *                  that last ACK is sent to server
 *                  If file is opened in write mode, it makes sure
 *                  that last block is sent out to server and
 *                  waits for server to respond with ACK.
 *
 * Note:            TCPIP_TFTP_FileIsClosed() must be called to confirm
 *                  if file was really closed.
 ********************************************************************/
void TCPIP_TFTP_FileClose(void)
{
    // If a file was opened for read, we can close it immediately.
    if ( _tftpFlags.bits.bIsReading )
    {
        // If this was premature close, make sure that we discard
        // current block.
        if ( !_tftpFlags.bits.bIsFlushed )
        {
            _tftpFlags.bits.bIsFlushed = true;
            TCPIP_UDP_GetIsReady(_tftpSocket);
            TCPIP_UDP_Discard();
        }

        if ( _tftpFlags.bits.bIsAcked )
        {
            _tftpFlags.bits.bIsClosed = true;
            _tftpFlags.bits.bIsClosing = false;
            return;
        }

        else
        {
            _tftpState = SM_TFTP_SEND_LAST_ACK;
            _tftpFlags.bits.bIsClosing = true;
        }
        return;
    }

    // For write mode, if we have not flushed last block, do it now.
    if ( !_tftpFlags.bits.bIsFlushed )
    {
        _tftpFlags.bits.bIsFlushed = true;
        UDPIsPutReady(_tftpSocket);
        TCPIP_UDP_Flush();
    }

    // For write mode, if our last block was ack'ed by remote server,
    // file is said to be closed.
    if ( _tftpFlags.bits.bIsAcked )
    {
        _tftpFlags.bits.bIsClosed = true;
        _tftpFlags.bits.bIsClosing = false;
        return;
    }

    _tftpState = SM_TFTP_WAIT_FOR_ACK;
    _tftpFlags.bits.bIsClosing =  true;

}



/*********************************************************************
 * Function:        TFTP_RESULT TCPIP_TFTP_FileIsClosed(void)
 *
 * Summary:         Determines if the file was closed.
 *
 * PreCondition:    TCPIP_TFTP_FileClose() is already called.
 *
 * Input:           None
 *
 * Output:          TFTP_OK if file was successfully closdd
 *
 *                  TFTP_RETRY if file mode was Write and remote
 *                  server did not receive last packet.
 *                  Application must retry with last block.
 *
 *                  TFTP_TIMEOUT if all attempts were exhausted
 *                  in closing file.
 *
 *                  TFTP_ERROR if remote server sent an error
 *                  in response to last block.
 *                  Actual error code may be read by calling
 *                  TFTPGetError()
 *
 *                  TFTP_NOT_READY if file is not closed yet.
 *
 * Side Effects:    None
 *
 * Overview:        If file mode is Read, it simply makes that
 *                  last block is acknowledged.
 *                  If file mode is Write, it waits for server ack.
 *                  If no ack was received within specified timeout
 *                  instructs appliaction to resend last block.
 *                  It keeps track of retries and declares timeout
 *                  all attempts were exhausted.
 *
 * Note:            None
 ********************************************************************/
TFTP_RESULT TCPIP_TFTP_FileIsClosed(void)
{
    if ( _tftpFlags.bits.bIsReading )
        return TCPIP_TFTP_DataIsGetReady();

    else
        return TCPIP_TFTP_IsReadyForPut();
}




/*********************************************************************
 * Function:        TFTP_RESULT TCPIP_TFTP_IsReadyForPut(void)
 *
 * Summary:         Determines if data can be written to a file.
 *
 * PreCondition:    TFTPOpenFile() is called with TFTP_FILE_MODE_WRITE
 *                  and TCPIP_TFTP_FileIsOpen() returned with true.
 *
 * Input:           None
 *
 * Output:          TFTP_OK if it is okay to write more data byte.
 *
 *                  TFTP_TIMEOUT if timeout occurred waiting for
 *                  ack from server
 *
 *                  TFTP_RETRY if all server did not send ack
 *                  on time and application needs to resend
 *                  last block.
 *
 *                  TFTP_ERROR if remote server returned ERROR.
 *                  Actual error code may be read by calling
 *                  TFTPGetError()
 *
 *                  TFTP_NOT_READY if still waiting...
 *
 * Side Effects:    None
 *
 * Overview:        Waits for ack from server.  If ack does not
 *                  arrive within specified timeout, it it instructs
 *                  application to retry last block by returning
 *                  TFTP_RETRY.
 *
 *                  If all attempts are exhausted, it returns with
 *                  TFTP_TIMEOUT.
 *
 * Note:            None
 ********************************************************************/
TFTP_RESULT TCPIP_TFTP_IsReadyForPut(void)
{
    TCPIP_UINT16_VAL opCode;
    TCPIP_UINT16_VAL blockNumber;
    bool bTimeOut;

    // Check to see if timeout has occurred.
    bTimeOut = false;
    if ( SYS_TICK_Get() - _tftpStartTick >= (TFTP_GET_TIMEOUT_VAL * SYS_TICK_TicksPerSecondGet()) )
    {
        bTimeOut = true;
        _tftpStartTick = SYS_TICK_Get();
    }

    switch(_tftpState)
    {
    case SM_TFTP_WAIT_FOR_ACK:
        // When timeout occurs in this state, application must retry.
        if ( bTimeOut )
        {
            if ( _tftpRetries++ > (TFTP_MAX_RETRIES-1) )
            {
                DEBUG(printf("TCPIP_TFTP_IsReadyForPut(): Timeout.\n"));

                // Forget about all previous attempts.
                _tftpRetries = 1;

                return TFTP_TIMEOUT;
            }

            else
            {
                DEBUG(printf("TCPIP_TFTP_IsReadyForPut(): Retry.\n"));
                _tftpState = SM_TFTP_WAIT;
                MutExVar.group2._tftpBlockNumber.Val--;	// Roll back by one so proper block number ID is sent for the next packet
                return TFTP_RETRY;
            }
        }

        // Must wait for ACK from server before we transmit next block.
        if ( !TCPIP_UDP_GetIsReady(_tftpSocket) )
            break;

        // Get opCode.
        TCPIP_UDP_Get(&opCode.v[1]);
        TCPIP_UDP_Get(&opCode.v[0]);

        // Get block number.
        TCPIP_UDP_Get(&blockNumber.v[1]);
        TCPIP_UDP_Get(&blockNumber.v[0]);

        // Discard everything else.
        TCPIP_UDP_Discard();

        // This must be ACK or else there is a problem.
        if ( opCode.Val == (uint16_t)TFTP_OPCODE_ACK )
        {
            // Also the block number must match with what we are expecting.
            if ( MutExVar.group2._tftpBlockNumber.Val == blockNumber.Val )
            {
                // Mark that block we sent previously has been ack'ed.
                _tftpFlags.bits.bIsAcked = true;

                // Since we have ack, forget about previous retry count.
                _tftpRetries = 1;

                // If this file is being closed, this must be last ack.
                // Declare it as closed.
                if ( _tftpFlags.bits.bIsClosing )
                {
                    _tftpFlags.bits.bIsClosed = true;
                    return TFTP_OK;
                }

                // Or else, wait for put to become ready so that caller
                // can transfer more data blocks.
                _tftpState = SM_TFTP_WAIT;
            }

            else
            {
                DEBUG(printf("TCPIP_TFTP_IsReadyForPut(): "\
                    "Unexpected block %d received - droping it...\n", \
                    blockNumber.Val));
                return TFTP_NOT_READY;
            }
        }

        else if ( opCode.Val == (uint16_t)TFTP_OPCODE_ERROR )
        {
            // For error opCode, remember error code so that application
            // can read it later.
            _tftpError = blockNumber.Val;

            // Declare error.
            return TFTP_ERROR;
        }
        else
            break;


    case SM_TFTP_WAIT:
        // Wait for UDP is to be ready to transmit.
        if ( UDPIsPutReady(_tftpSocket) )
        {
            // Put next block of data.
            MutExVar.group2._tftpBlockNumber.Val++;
            TCPIP_UDP_Put(0);
            TCPIP_UDP_Put(TFTP_OPCODE_DATA);

            TCPIP_UDP_Put(MutExVar.group2._tftpBlockNumber.v[1]);
            TCPIP_UDP_Put(MutExVar.group2._tftpBlockNumber.v[0]);

            // Remember that this block is not yet flushed.
            _tftpFlags.bits.bIsFlushed = false;

            // Remember that this block is not acknowledged.
            _tftpFlags.bits.bIsAcked = false;

            // Now, TFTP module is ready to put more data.
            _tftpState = SM_TFTP_READY;

            return TFTP_OK;
        }
        break;

    case SM_TFTP_READY:
        // TFTP module is said to be ready only when underlying UDP
        // is ready to transmit.
        if ( UDPIsPutReady(_tftpSocket) )
            return TFTP_OK;

	// Suppress compiler warnings on unhandled SM_TFTP_WAIT_FOR_DATA, 
	// SM_TFTP_DUPLICATE_ACK, SM_TFTP_SEND_ACK, SM_TFTP_SEND_LAST_ACK enum 
	// states.
    default:	
    	break;
    }

    return TFTP_NOT_READY;
}



/*********************************************************************
 * Function:        void TCPIP_TFTP_DataBytePut(uint8_t c)
 *
 * Summary:         Write a byte to a file.
 *
 * PreCondition:    TFTPOpenFile() is called with TFTP_FILE_MODE_WRITE
 *                  and TCPIP_TFTP_IsReadyForPut() = true
 *
 * Input:           c       - Data byte that is to be written
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Puts given data byte into TFTP socket.
 *                  If end of data block is reached, it
 *                  transmits entire block.
 *
 * Note:            Use this function to write file to server.
 ********************************************************************/
void TCPIP_TFTP_DataBytePut(uint8_t c)
{
    // Put given byte directly to UDP
    TCPIP_UDP_Put(c);

    // One more byte in data block.
    ++MutExVar.group2._tftpBlockLength.Val;

    // Check to see if data block is full.
    if ( MutExVar.group2._tftpBlockLength.v[1] == TFTP_BLOCK_SIZE_MSB )
    {
        // If it is, then transmit this block.
        TCPIP_UDP_Flush();

        // Remember that current block is already flushed.
        _tftpFlags.bits.bIsFlushed = true;

        // Prepare for next block.
        MutExVar.group2._tftpBlockLength.Val = 0;

        // Need to wait for ACK from server before putting
        // next block of data.
        _tftpState = SM_TFTP_WAIT_FOR_ACK;
    }
}




static void _TFTPSendFileName(TFTP_OPCODE opcode, uint8_t *fileName)
{
    uint8_t c;

	// Select the proper UDP socket and wait until we can write to it
    if(!UDPIsPutReady(_tftpSocket))
    {
        return;
    }

    // Write opCode
    TCPIP_UDP_Put(0);
    TCPIP_UDP_Put(opcode);

    // write file name, including NULL.
    do
    {
        c = *fileName++;
        TCPIP_UDP_Put(c);
    } while ( c != '\0' );

    // Write mode - always use octet or binay mode to transmit files.
    TCPIP_UDP_Put('o');
    TCPIP_UDP_Put('c');
    TCPIP_UDP_Put('t');
    TCPIP_UDP_Put('e');
    TCPIP_UDP_Put('t');
    TCPIP_UDP_Put(0);

    // Transmit it.
    TCPIP_UDP_Flush();

    // Reset data block length.
    MutExVar.group2._tftpBlockLength.Val = 0;
}


static void _TFTPSendAck(TCPIP_UINT16_VAL blockNumber)
{
    // Write opCode.
    TCPIP_UDP_Put(0);
    TCPIP_UDP_Put(TFTP_OPCODE_ACK);

    // Write block number for this ack.
    TCPIP_UDP_Put(blockNumber.v[1]);
    TCPIP_UDP_Put(blockNumber.v[0]);

    // Transmit it.
    TCPIP_UDP_Flush();
}



#endif //#if defined(TCPIP_STACK_USE_TFTP_CLIENT)
