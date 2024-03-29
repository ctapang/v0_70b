/*******************************************************************************
  Simple Mail Transfer Protocol (SMTP) Client

  Summary:
    Module for Microchip TCP/IP Stack
    
  Description:
*******************************************************************************/

/*******************************************************************************
FileName:  SMTP.h 
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

#ifndef __SMTP_H
#define __SMTP_H

/****************************************************************************
  Section:
	Data Type Definitions
  ***************************************************************************/
	#define SMTP_SUCCESS		(0x0000u)	// Message was successfully sent
	#define SMTP_RESOLVE_ERROR	(0x8000u)	// DNS lookup for SMTP server failed
	#define SMTP_CONNECT_ERROR	(0x8001u)	// Connection to SMTP server failed
	
/****************************************************************************
  Function:
      typedef struct SMTP_POINTERS
    
  Summary:
    Configures the SMTP client to send a message
    
  Description:
    This structure of pointers configures the SMTP Client to send an e-mail
    message.
    
  Parameters:
    Server -        the SMTP server to relay the message through
    Username -      the user name to use when logging into the SMTP server,
                    if any is required
    Password -      the password to supply when logging in, if any is required
    To -            the destination address for this message. May be a
                    comma\-separated list of addresss, and/or formatted.
    CC -            The CC addresses for this message, if any. May be a
                    comma\-separated list of addresss, and/or formatted.
    BCC -           The BCC addresses for this message, if any. May be a
                    comma\-separated list of addresss, and/or formatted.
    From -          The From address for this message. May be formatted.
    Subject -       The Subject header for this message.
    OtherHeaders -  Any additional headers for this message. Each additional 
                    header, including the last one, must be terminated with
                    a CRLF pair.
    Body -          When sending a message from memory, the location of the
    				body of this message in memory. Leave as NULL to build 
    				a message on\-the\-fly.
    UseSSL -        When TCPIP_STACK_USE_SSL_CLIENT is enabled, this flag causes
                    the SMTP client to make an SSL connection to the server.
    ServerPort -    (uint16_t value) Indicates the port on which to connect to the
                    remote SMTP server.

  Remarks:
    When formatting an e-mail address, the SMTP standard format for associating a
    printable name may be used. This format places the printable name in quotation
    marks, with the address following in pointed brackets, such as "John Smith"
    \<john.smith@domain.com\>                                                       
  ***************************************************************************/
typedef struct
{
	char* Server;
	char* Username;
	char* Password;
	char* To;
	char* CC;
	char* BCC;
	char* From;
	char* Subject;
	char* OtherHeaders;
	char* Body;
	bool  UseSSL;
	uint16_t ServerPort;
	
} SMTP_POINTERS;


typedef struct
{
}SMTP_CLIENT_MODULE_CONFIG;

	
/****************************************************************************
  Section:
	SMTP Function Prototypes
  ***************************************************************************/

/*****************************************************************************
  Function:
    bool TCPIP_SMTP_UsageBegin(void)

  Summary:
    Requests control of the SMTP client module.

  Description:
    Call this function before calling any other SMTP Client APIs.  This
    function obtains a lock on the SMTP Client, which can only be used by
    one stack application at a time.  Once the application is finished
    with the SMTP client, it must call TCPIP_SMTP_UsageEnd to release control
    of the module to any other waiting applications.

    This function initializes all the SMTP state machines and variables
    back to their default state.

  Precondition:
    None

  Parameters:
    None

  Return Values:
    true - The application has successfully obtained control of the module
    false - The SMTP module is in use by another application.  Call
        TCPIP_SMTP_UsageBegin again later, after returning to the main program loop
 */
bool TCPIP_SMTP_UsageBegin(void);

/*****************************************************************************
  Function:
    uint16_t TCPIP_SMTP_UsageEnd(void)

  Summary:
    Releases control of the SMTP client module.

  Description:
    Call this function to release control of the SMTP client module once
    an application is finished using it.  This function releases the lock
    obtained by TCPIP_SMTP_UsageBegin, and frees the SMTP client to be used by
    another application.

  Precondition:
    TCPIP_SMTP_UsageBegin returned true on a previous call.

  Parameters:
    None

  Return Values:
    SMTP_SUCCESS - A message was successfully sent
    SMTP_RESOLVE_ERROR - The SMTP server could not be resolved
    SMTP_CONNECT_ERROR - The connection to the SMTP server failed or was
        prematurely terminated
    1-199 and 300-399 - The last SMTP server response code
 */
uint16_t TCPIP_SMTP_UsageEnd(void);


/*****************************************************************************
  Function:
    void TCPIP_SMTP_MailSend(SMTP_POINTERS* smtpClientMessage)

  Summary:
    Initializes the message sending process.

  Description:
    This function starts the state machine that performs the actual
    transmission of the message.  Call this function after all the fields
    in SMTPClient have been set.

  Precondition:
    TCPIP_SMTP_UsageBegin returned true on a previous call.

  Parameters:
    smtpClientMessage   - message to send

  Returns:
    None
 */
void TCPIP_SMTP_MailSend(SMTP_POINTERS* smtpClientMessage);


/*****************************************************************************
  Function:
    bool TCPIP_SMTP_IsBusy(void)

  Summary:
    Determines if the SMTP client is busy.

  Description:
    Call this function to determine if the SMTP client is busy performing
    background tasks.  This function should be called after any call to
    TCPIP_SMTP_MailSend, TCPIP_SMTP_PutIsDone to determine if the stack has finished
    performing its internal tasks.  It should also be called prior to any
    call to TCPIP_SMTP_IsPutReady to verify that the SMTP client has not
    prematurely disconnected.  When this function returns false, the next
    call should be to TCPIP_SMTP_UsageEnd to release the module and obtain the
    status code for the operation.

  Precondition:
    TCPIP_SMTP_UsageBegin returned true on a previous call.

  Parameters:
    None

  Return Values:
    true - The SMTP Client is busy with internal tasks or sending an
        on-the-fly message.
    false - The SMTP Client is terminated and is ready to be released.
 */
bool TCPIP_SMTP_IsBusy(void);
/*****************************************************************************
  Function:
    uint16_t TCPIP_SMTP_IsPutReady(void)

  Summary:
    Determines how much data can be written to the SMTP client.

  Description:
    Use this function to determine how much data can be written to the SMTP
    client when generating an on-the-fly message.

  Precondition:
    TCPIP_SMTP_UsageBegin returned true on a previous call, and an on-the-fly
    message is being generated.  This requires that TCPIP_SMTP_MailSend was called
    with SMTPClient.Body set to NULL.

  Parameters:
    None

  Returns:
    The number of free bytes the SMTP TX FIFO.

  Remarks:
    This function should only be called externally when the SMTP client is
    generating an on-the-fly message.  (That is, TCPIP_SMTP_MailSend was called
    with SMTPClient.Body set to NULL.)
 */
uint16_t TCPIP_SMTP_IsPutReady(void);

/*****************************************************************************
  Function:
    bool TCPIP_SMTP_Put(char c)

  Description:
    Writes a single byte to the SMTP client.

  Precondition:
    TCPIP_SMTP_UsageBegin returned true on a previous call.

  Parameters:
    c - The byte to be written

  Return Values:
    true - The byte was successfully written
    false - The byte was not written, most likely because the buffer was full

  Remarks:
    This function should only be called externally when the SMTP client is
    generating an on-the-fly message.  (That is, TCPIP_SMTP_MailSend was called
    with SMTPClient.Body set to NULL.)
 */
bool TCPIP_SMTP_Put(char c);

/*****************************************************************************
  Function:
    uint16_t TCPIP_SMTP_ArrayPut(uint8_t* Data, uint16_t Len)

  Description:
    Writes a series of bytes to the SMTP client.

  Precondition:
    TCPIP_SMTP_UsageBegin returned true on a previous call.

  Parameters:
    Data - The data to be written
    Len - How many bytes should be written

  Returns:
    The number of bytes written.  If less than Len, then the TX FIFO became
    full before all bytes could be written.

  Remarks:
    This function should only be called externally when the SMTP client is
    generating an on-the-fly message.  (That is, TCPIP_SMTP_MailSend was called
    with SMTPClient.Body set to NULL.)

  Internal:
    TCPIP_SMTP_Put must be used instead of TCPIP_TCP_ArrayPut because "\r\n." must be
    transparently replaced by "\r\n..".
 */
uint16_t TCPIP_SMTP_ArrayPut(uint8_t* Data, uint16_t Len);


/*****************************************************************************
  Function:
    uint16_t TCPIP_SMTP_StringPut(char* Data)

  Description:
    Writes a string to the SMTP client.

  Precondition:
    TCPIP_SMTP_UsageBegin returned true on a previous call.

  Parameters:
    Data - The data to be written

  Returns:
    The number of bytes written.  If less than the length of Data, then the
    TX FIFO became full before all bytes could be written.

  Remarks:
    This function should only be called externally when the SMTP client is
    generating an on-the-fly message.  (That is, TCPIP_SMTP_MailSend was called
    with SMTPClient.Body set to NULL.)

  Internal:
    TCPIP_SMTP_Put must be used instead of TCPIP_TCP_StringPut because "\r\n." must be
    transparently replaced by "\r\n..".
 */
uint16_t TCPIP_SMTP_StringPut(char* Data);

/*****************************************************************************
  Function:
    void TCPIP_SMTP_Flush(void)

  Description:
    Flushes the SMTP socket and forces all data to be sent.

  Precondition:
    TCPIP_SMTP_UsageBegin returned true on a previous call.

  Parameters:
    None

  Returns:
    None

  Remarks:
    This function should only be called externally when the SMTP client is
    generating an on-the-fly message.  (That is, TCPIP_SMTP_MailSend was called
    with SMTPClient.Body set to NULL.)
  ***************************************************************************/
void TCPIP_SMTP_Flush(void);

/*****************************************************************************
  Function:
    void TCPIP_SMTP_PutIsDone(void)

  Description:
    Indicates that the on-the-fly message is complete.

  Precondition:
    TCPIP_SMTP_UsageBegin returned true on a previous call, and the SMTP client is
    generated an on-the-fly message.  (That is, TCPIP_SMTP_MailSend was called
    with SMTPClient.Body set to NULL.)

  Parameters:
    None

  Returns:
    None
 */

void TCPIP_SMTP_PutIsDone(void);


#endif
