/***********************************************************************************/
/*  Copyright (c) 2002-2009, Silicon Image, Inc.  All rights reserved.             */
/*  No part of this work may be reproduced, modified, distributed, transmitted,    */
/*  transcribed, or translated into any language or computer format, in any form   */
/*  or by any means without written permission of: Silicon Image, Inc.,            */
/*  1060 East Arques Avenue, Sunnyvale, California 94085                           */
/***********************************************************************************/
#include "string.h"
#include "gfx/src/common_legacy/i2c.h"

#include <sys/attribs.h>
#include <sys/kmem.h>

uint8_t I2C_ReadBlock(uint8_t deviceID, uint8_t offset, uint8_t *buffer, uint16_t length);
uint8_t I2C_WriteBlock(uint8_t deviceID, uint8_t offset, uint8_t buffer, uint16_t length);
bool I2CBusIsIdle( I2C_MODULE id );
bool I2CByteWasAcknowledged ( I2C_MODULE id );
uint8_t I2CGetByte ( I2C_MODULE id );
bool I2CReceivedDataIsAvailable ( I2C_MODULE id );
I2C_RESULT I2CReceiverEnable ( I2C_MODULE id, bool enable );
I2C_RESULT I2CSendByte ( I2C_MODULE id, uint8_t data );
I2C_RESULT I2CStart( I2C_MODULE id );
void I2CStop ( I2C_MODULE id );
bool I2CTransmissionHasCompleted ( I2C_MODULE id );
bool I2CTransmitterIsReady ( I2C_MODULE id );

#define OVM7690_I2C_BUS              I2C1

void I2C_Init(void)
{
    TRISEbits.TRISE8 = 1; // Input for INT pin for PCAP

    IEC0bits.INT1IE = 0; // disable INT1
    INTCONbits.INT1EP = 1; // rising edge trigger
    IPC2bits.INT1IP = 5;
    IFS0bits.INT1IF = 0; // clear the interrupt flag
    IEC0bits.INT1IE = 1; // enable INT0

    I2C1CONbits.ON =0;

    I2C1BRG = 50; // 50 kHz Baudrate

    I2C1CONbits.ON =1;

    SYS_TMR_DelayMS(500);
}

/*******************************************************************************
  Function:
    BOOL StartTransfer( BOOL restart )

  Summary:
    Starts (or restarts) a transfer to/from the EEPROM.

  Description:
    This routine starts (or restarts) a transfer to/from the EEPROM, waiting (in
    a blocking loop) until the start (or re-start) condition has completed.

  Precondition:
    The I2C module must have been initialized.

  Parameters:
    restart - If FALSE, send a "Start" condition
            - If TRUE, send a "Restart" condition

  Returns:
    TRUE    - If successful
    FALSE   - If a collision occured during Start signaling

  Example:
    <code>
    StartTransfer(FALSE);
    </code>

  Remarks:
    This is a blocking routine that waits for the bus to be idle and the Start
    (or Restart) signal to complete.
  *****************************************************************************/

bool StartTransfer( bool restart )
{

    // Wait for the bus to be idle, then start the transfer
      while(!I2CBusIsIdle(OVM7690_I2C_BUS));


    if(I2CStart(OVM7690_I2C_BUS) != I2C_SUCCESS)
    {
         return false;
    }

    // Wait for the signal to complete
    while(I2C1STATbits.S == 0);
    
    return true;
}

/*******************************************************************************
  Function:
    BOOL TransmitOneByte( UINT8 data )

  Summary:
    This transmits one byte to the EEPROM.

  Description:
    This transmits one byte to the EEPROM, and reports errors for any bus
    collisions.

  Precondition:
    The transfer must have been previously started.

  Parameters:
    data    - Data byte to transmit

  Returns:
    TRUE    - Data was sent successfully
    FALSE   - A bus collision occured

  Example:
    <code>
    TransmitOneByte(0xAA);
    </code>

  Remarks:
    This is a blocking routine that waits for the transmission to complete.
  *****************************************************************************/

bool TransmitOneByte( uint8_t data )
{
 
    // Wait for the transmitter to be ready
    while(!I2CTransmitterIsReady(OVM7690_I2C_BUS));

    // Transmit the byte
    if(I2CSendByte(OVM7690_I2C_BUS, data) == I2C_MASTER_BUS_COLLISION)
    {
        return false;
    }

   // Wait for the transmission to finish
    while(!I2CTransmissionHasCompleted(OVM7690_I2C_BUS));
 
    return true;
}

/*******************************************************************************
  Function:
    void StopTransfer( void )

  Summary:
    Stops a transfer to/from the EEPROM.

  Description:
    This routine Stops a transfer to/from the EEPROM, waiting (in a
    blocking loop) until the Stop condition has completed.

  Precondition:
    The I2C module must have been initialized & a transfer started.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    StopTransfer();
    </code>

  Remarks:
    This is a blocking routine that waits for the Stop signal to complete.
***************************************************************************/

void StopTransfer( void )
{

    I2C_STATUS status;

    // Send the Stop signal
    I2CStop(OVM7690_I2C_BUS);

    while(I2C1STATbits.P == 0)
    {
        I2C1CONSET = 0x00000004; // I2C1CONbits.PEN = 1;
    }

    I2C1CONbits.ON = 0;  //Reset Status Registers
    I2C1CONbits.ON = 1;

}

//------------------------------------------------------------------------------
// Function: I2C_WriteByte
// Description: Write one byte to the spacifed I2C slave address at the specified offset.
//              The offset address is one byte (8 bit offset only).
//              No error information is returned.
//------------------------------------------------------------------------------
void I2C_WriteByte(uint8_t deviceID, uint8_t offset, uint8_t value)
{
//    I2C_WriteBlock( deviceID, offset, value, 1 );
}


//------------------------------------------------------------------------------
// Function: I2C_ReadByte
// Description: Read one byte from the spacifed I2C slave address at the specified offset.
//              The offset address is one byte (8 bit offset only).
//              The read data is returned.  There is no indication in case of error.
//------------------------------------------------------------------------------
uint8_t I2C_ReadByte(uint8_t deviceID, uint8_t offset)
{
    uint8_t returnData = 0;

    I2C_ReadBlock( deviceID, offset, &returnData, 1 );

    return( returnData );
}

//------------------------------------------------------------------------------
// Function: I2C_ReadBlock
// Description: Read a block of bytes from the spacifed I2C slave address at the specified offset.
//              The offset address is one byte (8 bit offset only).
//              The return code is always 0.  There is no indication in case of error.
//------------------------------------------------------------------------------
uint8_t I2C_ReadBlock(uint8_t deviceID, uint8_t offset, uint8_t *buffer, uint16_t length)
{
    uint8_t write_buffer[2] = {0x00};
    uint8_t count =0;
    bool Success = true;

    write_buffer[0] = deviceID;
    write_buffer[1] = offset;

    I2C1CONbits.ACKDT = 0;

    // Start the transfer to write data to the EEPROM
    if(!StartTransfer(false) )
    {
        return(1);
    }

   // Transmit the address with the READ bit set
   deviceID |= 0x01;

   TransmitOneByte(deviceID);
   
    // Verify that the byte was acknowledged
    if(!I2CByteWasAcknowledged(OVM7690_I2C_BUS))
    {
        Success = false;
        return(1);
    }

    for(count=0;count<length;count++)
    {

        // Read the data from the desired address
        if(I2CReceiverEnable(OVM7690_I2C_BUS, true) == I2C_RECEIVE_OVERFLOW)
        {
            Success = false;
            return(1);
        }
        else
        {
            while(!I2CReceivedDataIsAvailable(OVM7690_I2C_BUS));
            *buffer  = I2C1RCV;
            buffer++;

          if(count == (length-1))
          {
           // I2C1CONbits.ACKDT = 1;
            I2C1CONSET = 0x20;
          }

            I2C1CONbits.ACKEN = 1;		// initiate bus acknowledge sequence

            while(I2C1CONbits.ACKEN == 1);
        }

    }

    // End the transfer (stop here if an error occured)
    StopTransfer();

    return(0);
}

bool I2CBusIsIdle( I2C_MODULE id )
{
    // Check the status of the Start & Stop bits to determine if the bus is idle.
    return ( (I2C1STATbits.S == 0 && I2C1STATbits.P == 0 ) ||
             (I2C1STATbits.S == 0 && I2C1STATbits.P == 1 )   );
}

bool I2CByteWasAcknowledged ( I2C_MODULE id )
{
	return(!I2C1STATbits.ACKSTAT);
}

uint8_t I2CGetByte ( I2C_MODULE id )
{
	return(I2C1RCV);
}

bool I2CReceivedDataIsAvailable ( I2C_MODULE id )
{
	return(I2C1STATbits.RBF);
}

I2C_RESULT I2CReceiverEnable ( I2C_MODULE id, bool enable )
{
    // Enable the receiver
    I2C1CONbits.RCEN = enable;
	
    // Check for an overflow condition
    if(I2C1STATbits.I2COV)
    {
		return(I2C_RECEIVE_OVERFLOW); 
    }
	else
    {
		return(I2C_SUCCESS);
    }
}

I2C_RESULT I2CSendByte ( I2C_MODULE id, uint8_t data )
{
    // Send the byte
    I2C1TRN = data;
        
    // Check for collisions
    if((I2C1STATbits.BCL == 1) || (I2C1STATbits.IWCOL == 1))
    {
		return(I2C_MASTER_BUS_COLLISION); 
    }
	else
    {
		return(I2C_SUCCESS);
    }
}

I2C_RESULT I2CStart( I2C_MODULE id )
{
    // Enable the Start condition
    I2C1CONSET = 0x00000001;//I2C1CONbits.SEN = 1;

    // Check for collisions
    if(I2C1STATbits.BCL)
    {
		return(I2C_MASTER_BUS_COLLISION); 
    }
	else
    {
		return(I2C_SUCCESS);
    }		
}

void I2CStop ( I2C_MODULE id )
{
    // Enable the Stop condition
   I2C1CONSET = 0x00000004;// I2C1CONbits.PEN = 1;

}

bool I2CTransmissionHasCompleted ( I2C_MODULE id )
{
	return(!I2C1STATbits.TRSTAT);
}

bool I2CTransmitterIsReady ( I2C_MODULE id )
{
	return(!I2C1STATbits.TBF);
}

//#endif //Used only when debug command handler is enabled
