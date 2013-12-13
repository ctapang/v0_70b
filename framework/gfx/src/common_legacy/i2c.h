/*******************************************************************************
  I2C Library Interface Definition

  Summary:
    This file contains the Application Program Interface (API) definition  for 
    the I2C peripheral library.
    
  Description:
    This library provides a low-level abstraction of the I2C (Inter-Integrated
    Circuit) module on Microchip PIC32MX family microcontrollers with a 
    convenient C language interface.  It can be used to simplify low-level
    access to the module without the necessity of interacting directly with the 
    module's registers, thus hiding differences from one microcontroller 
    variant to another.
*******************************************************************************/
//DOM-IGNORE-BEGIN
/*******************************************************************************
FileName:       i2c.h
Processor:      PIC32MX
Compiler:       Microchip MPLAB XC32 v1.00 or higher

Copyright © 2008-2009 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY KIND,
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

#ifndef _I2C_H_
#define _I2C_H_

#include <stdint.h>
#include <stdbool.h>

#include <xc.h>

// *****************************************************************************
// *****************************************************************************
// Section: Constants & Data Types
// *****************************************************************************
// *****************************************************************************

#define _I2CCON_SEN_POSITION                    0x00000000
#define _I2CCON_SEN_MASK                        0x00000001
#define _I2CCON_SEN_LENGTH                      0x00000001

#define _I2CCON_RSEN_POSITION                   0x00000001
#define _I2CCON_RSEN_MASK                       0x00000002
#define _I2CCON_RSEN_LENGTH                     0x00000001

#define _I2CCON_PEN_POSITION                    0x00000002
#define _I2CCON_PEN_MASK                        0x00000004
#define _I2CCON_PEN_LENGTH                      0x00000001

#define _I2CCON_RCEN_POSITION                   0x00000003
#define _I2CCON_RCEN_MASK                       0x00000008
#define _I2CCON_RCEN_LENGTH                     0x00000001

#define _I2CCON_ACKEN_POSITION                  0x00000004
#define _I2CCON_ACKEN_MASK                      0x00000010
#define _I2CCON_ACKEN_LENGTH                    0x00000001

#define _I2CCON_ACKDT_POSITION                  0x00000005
#define _I2CCON_ACKDT_MASK                      0x00000020
#define _I2CCON_ACKDT_LENGTH                    0x00000001

#define _I2CCON_STREN_POSITION                  0x00000006
#define _I2CCON_STREN_MASK                      0x00000040
#define _I2CCON_STREN_LENGTH                    0x00000001

#define _I2CCON_GCEN_POSITION                   0x00000007
#define _I2CCON_GCEN_MASK                       0x00000080
#define _I2CCON_GCEN_LENGTH                     0x00000001

#define _I2CCON_SMEN_POSITION                   0x00000008
#define _I2CCON_SMEN_MASK                       0x00000100
#define _I2CCON_SMEN_LENGTH                     0x00000001

#define _I2CCON_DISSLW_POSITION                 0x00000009
#define _I2CCON_DISSLW_MASK                     0x00000200
#define _I2CCON_DISSLW_LENGTH                   0x00000001

#define _I2CCON_A10M_POSITION                   0x0000000A
#define _I2CCON_A10M_MASK                       0x00000400
#define _I2CCON_A10M_LENGTH                     0x00000001

#define _I2CCON_STRICT_POSITION                 0x0000000B
#define _I2CCON_STRICT_MASK                     0x00000800
#define _I2CCON_STRICT_LENGTH                   0x00000001

#define _I2CCON_SCLREL_POSITION                 0x0000000C
#define _I2CCON_SCLREL_MASK                     0x00001000
#define _I2CCON_SCLREL_LENGTH                   0x00000001

#define _I2CCON_SIDL_POSITION                   0x0000000D
#define _I2CCON_SIDL_MASK                       0x00002000
#define _I2CCON_SIDL_LENGTH                     0x00000001

#define _I2CCON_ON_POSITION                     0x0000000F
#define _I2CCON_ON_MASK                         0x00008000
#define _I2CCON_ON_LENGTH                       0x00000001

#define _I2CCON_IPMIEN_POSITION                 0x0000000B
#define _I2CCON_IPMIEN_MASK                     0x00000800
#define _I2CCON_IPMIEN_LENGTH                   0x00000001

#define _I2CCON_I2CSIDL_POSITION                0x0000000D
#define _I2CCON_I2CSIDL_MASK                    0x00002000
#define _I2CCON_I2CSIDL_LENGTH                  0x00000001

#define _I2CCON_I2CEN_POSITION                  0x0000000F
#define _I2CCON_I2CEN_MASK                      0x00008000
#define _I2CCON_I2CEN_LENGTH                    0x00000001

#define _I2CCON_w_POSITION                      0x00000000
#define _I2CCON_w_MASK                          0xFFFFFFFF
#define _I2CCON_w_LENGTH                        0x00000020

#define _I2CSTAT_TBF_POSITION                   0x00000000
#define _I2CSTAT_TBF_MASK                       0x00000001
#define _I2CSTAT_TBF_LENGTH                     0x00000001

#define _I2CSTAT_RBF_POSITION                   0x00000001
#define _I2CSTAT_RBF_MASK                       0x00000002
#define _I2CSTAT_RBF_LENGTH                     0x00000001

#define _I2CSTAT_R_W_POSITION                   0x00000002
#define _I2CSTAT_R_W_MASK                       0x00000004
#define _I2CSTAT_R_W_LENGTH                     0x00000001

#define _I2CSTAT_S_POSITION                     0x00000003
#define _I2CSTAT_S_MASK                         0x00000008
#define _I2CSTAT_S_LENGTH                       0x00000001

#define _I2CSTAT_P_POSITION                     0x00000004
#define _I2CSTAT_P_MASK                         0x00000010
#define _I2CSTAT_P_LENGTH                       0x00000001

#define _I2CSTAT_D_A_POSITION                   0x00000005
#define _I2CSTAT_D_A_MASK                       0x00000020
#define _I2CSTAT_D_A_LENGTH                     0x00000001

#define _I2CSTAT_I2COV_POSITION                 0x00000006
#define _I2CSTAT_I2COV_MASK                     0x00000040
#define _I2CSTAT_I2COV_LENGTH                   0x00000001

#define _I2CSTAT_IWCOL_POSITION                 0x00000007
#define _I2CSTAT_IWCOL_MASK                     0x00000080
#define _I2CSTAT_IWCOL_LENGTH                   0x00000001

#define _I2CSTAT_ADD10_POSITION                 0x00000008
#define _I2CSTAT_ADD10_MASK                     0x00000100
#define _I2CSTAT_ADD10_LENGTH                   0x00000001

#define _I2CSTAT_GCSTAT_POSITION                0x00000009
#define _I2CSTAT_GCSTAT_MASK                    0x00000200
#define _I2CSTAT_GCSTAT_LENGTH                  0x00000001

#define _I2CSTAT_BCL_POSITION                   0x0000000A
#define _I2CSTAT_BCL_MASK                       0x00000400
#define _I2CSTAT_BCL_LENGTH                     0x00000001

#define _I2CSTAT_TRSTAT_POSITION                0x0000000E
#define _I2CSTAT_TRSTAT_MASK                    0x00004000
#define _I2CSTAT_TRSTAT_LENGTH                  0x00000001

#define _I2CSTAT_ACKSTAT_POSITION               0x0000000F
#define _I2CSTAT_ACKSTAT_MASK                   0x00008000
#define _I2CSTAT_ACKSTAT_LENGTH                 0x00000001

#define _I2CSTAT_I2CPOV_POSITION                0x00000006
#define _I2CSTAT_I2CPOV_MASK                    0x00000040
#define _I2CSTAT_I2CPOV_LENGTH                  0x00000001

#define _I2CSTAT_w_POSITION                     0x00000000
#define _I2CSTAT_w_MASK                         0xFFFFFFFF
#define _I2CSTAT_w_LENGTH                       0x00000020

/* I2C Module

  Summary:
    I2C Modules Supported.

  Description:
    This enumeration identifies the available I2C modules.
    
  Remarks:
    The caller should not rely on the specific numbers assigned to any of 
    these values as they may change from one processor ot the next.
    
    Not all modules will be available on all microcontrollers.  Refer to the 
    data sheet for the specific controller in use.
*/

typedef enum
{
    // I2C Module 1 ID
    I2C1,
    // I2C Module 2 ID
    I2C2,
	// I2C Module 3 ID
    I2C3,
	// I2C Module 4 ID
    I2C4,
	// I2C Module 5 ID
    I2C5,
    // Number of available I2C modules.
    I2C_NUMBER_OF_MODULES

} I2C_MODULE;


// *****************************************************************************
/* I2C 7-Bit Address

  Summary:
    Structure of a 7-bit I2C address.

  Description:
    This union defines the format of a 7-bit I2C slave address.
*/

typedef union 
{
    // Access to the 8-bit format with the 7-bit address and the read/write 
    // direction defined.
    uint8_t       byte;

    struct
    {
        // The read/write bit of the I2C address.
        uint8_t   rw       : 1;

        // The 7-bit slave address.
        uint8_t   address  : 7;
    };

} I2C_7_BIT_ADDRESS;


// *****************************************************************************
/* I2C 10-Bit Address

  Summary:
    Structure of a 10-bit I2C address.

  Description:
    This union defines the format of a 10-bit I2C slave address.
*/

typedef union 
{
    // Access to the 16-bit format.
    uint16_t      both_bytes;

    struct
    {
        // Access to the first byte.
        uint8_t    first_byte;

        // Access to the second byte.
        uint8_t    second_byte;
    };

    struct
    {
        // The read/write bit of the I2C address.
        uint16_t  rw          : 1;

        // The 2 high-order bits of the 10-bit address.
        uint16_t  high_bits   : 2;

        // The 5 constant bits, indicating 10-bit addressing.
        uint16_t  const_bits  : 5;

        // The 8 low-order bits of the 10-bit address.
        uint16_t  low_bits    : 8;
    };

} I2C_10_BIT_ADDRESS;


// *****************************************************************************
// I2C Read/Write Bits

/* I2C Read Bit

  Summary:
    Used to indicate that the following data transfer is from slave to master.

  Description:
    This definition can be used to set the read/write direction bit 
    (indicating a read) when addressing I2C slave devices.
*/

#define I2C_READ    1


/* I2C Read Bit

  Summary:
    Used to indicate that the following data transfer is from master to slave.

  Description:
    This definition can be used to clear the read/write direction bit 
    (indicating a write) when addressing I2C slave devices.
*/

#define I2C_WRITE   0


// *****************************************************************************
// I2C Reserved Slave Addresses

/* I2C General Call Reserved Slave Addresses

  Summary:
    Used to send a long pulse to get the attention of a slow slave device.

  Description:
    The General Call address can be used to broadcast a message to every slave
    device at the same time.
*/

#define I2C_GENERAL_CALL_ADDRESS        0x00


/* I2C "Start Byte" Reserved Slave Addresses

  Summary:
    Used to send a long pulse.

  Description:
    The start byte can be used to send a long pulse to get the attention of a
    slow slave device.
*/

#define I2C_START_BYTE                  0x01


/* I2C 10-Bit Address Reserved Slave Addresses

  Summary:
    Used to form a 10-bit address.

  Description:
    This constant is used by the I2C_INITIALIZE_10_BIT_ADDRESS macro to form
    a 10-bit address so that it can be correctly transmitted and recognized
    as a 2-byte sequence.
*/

#define I2C_10_BIT_ADDRESS_CONST_BITS   0x1E


// *****************************************************************************
/* I2C Result Codes

  Summary:
    Defines the possible results of I2C operations that can succeed or fail.

  Description:
    This enumeration defines the possible results of any of the I2C operations
    that have the possiblity of failing.  This result should be checked to 
    ensure that the operation achieved the desired result.
    
  Remarks:
    I2C_SUCCESS is guaranteed to equal zero (0).  The caller should not rely
    on the number assigned to any of the other values.
*/

typedef enum 
{
    // The I2C operation was successful.
    I2C_SUCCESS = 0,

    // An error occurred during the I2C operation.
    I2C_ERROR,
    
    // Arbitration has been lost during a master transfer.
    I2C_MASTER_BUS_COLLISION,
    
    // Data was not read from the receive buffer quick enough and new data 
    // was lost.
    I2C_RECEIVE_OVERFLOW

} I2C_RESULT;


// *****************************************************************************
/* I2C Configuration Settings

  Summary:
    Supported configuration flags for the I2C module.

  Description:
    This enumeration defines the various configuration options for the I2C 
    module.  These values can be OR'd together to create a configuration mask
    passed to the I2CConfigure routine.
    
  Remarks:
    The caller should not rely on the specific numbers assigned to any of 
    these values as they may change from one processor ot the next.
*/

typedef enum
{
    // Setting this bit allows the software to throttle the clock (holding SCL 
    // low) between bytes using I2CSlaveClockHold and I2CSlaveClockRelease.  
    I2C_ENABLE_SLAVE_CLOCK_STRETCHING
        /*DOM-IGNORE-BEGIN*/ = 0x00000040 /*DOM-IGNORE-END*/,

    // Setting this bit switches the I2C module's signaling levels so that they
    // are compatible with the SM Bus specification.
    I2C_ENABLE_SMB_SUPPORT
        /*DOM-IGNORE-BEGIN*/ = 0x00000100 /*DOM-IGNORE-END*/,

    // Setting this bit switches the I2C module to high-speed I2C signaling.
    I2C_ENABLE_HIGH_SPEED
        /*DOM-IGNORE-BEGIN*/ = 0x00000200 /*DOM-IGNORE-END*/,

    // Setting this bit stops the I2C module when the processor enters Idle mode.
    I2C_STOP_IN_IDLE
        /*DOM-IGNORE-BEGIN*/ = 0x00002000 /*DOM-IGNORE-END*/

} I2C_CONFIGURATION;


// *****************************************************************************
/* I2C Slave Address Modes

  Summary:
    Supported I2C slave addressing modes

  Description:
    This enumeration defines the I2C addressing modes that can be recognized by
    the I2C module.
    
  Remarks:
    The caller should not rely on the specific numbers assigned to any of 
    these values as they may change from one processor ot the next.
*/

typedef enum
{
    // Enable recognition of 7-bit addresses in in slave mode.
    I2C_USE_7BIT_ADDRESS
        /*DOM-IGNORE-BEGIN*/ = 0x00000000 /*DOM-IGNORE-END*/,

    // Enable recognition of 10-bit addresses in in slave mode.
    I2C_USE_10BIT_ADDRESS
        /*DOM-IGNORE-BEGIN*/ = 0x00000400 /*DOM-IGNORE-END*/,

    // Enable general call address identification.  Setting this bit configures
    // the module to identify the general call address (0) in slave mode.
    I2C_ENABLE_GENERAL_CALL_ADDRESS
        /*DOM-IGNORE-BEGIN*/ = 0x00000080 /*DOM-IGNORE-END*/,

    // Disable reserved address protection, allowing respones to reserved 
    // addresses (violates I2C specification)
    I2C_USE_RESERVED_ADDRESSES
        /*DOM-IGNORE-BEGIN*/ = 0x00000800 /*DOM-IGNORE-END*/

} I2C_ADDRESS_MODE;


// *****************************************************************************
/* I2C Status Flags

  Summary:
    I2C status bitmask flags.

  Description:
    This enumeration defines the possible I2C status bits.  These values are  
    OR'd together to make up the bitmask returned by I2CGetStatus or passed to 
    I2CClearStatus.
    
  Remarks:
    The caller should not rely on the specific numbers assigned to any of 
    these values as they may change from one processor ot the next.
*/

typedef enum
{
    // Transmit buffer full.  Set if the transmit buffer is full (unable to
    // accept more data to transmit.
    I2C_TRANSMITTER_FULL
        /*DOM-IGNORE-BEGIN*/ = 0x00000001 /*DOM-IGNORE-END*/,

    // Received data available.  Set if data is available in the receiver
    // buffer.  Cleared if not.  (Valid for both master and slave transfers.)
    I2C_DATA_AVAILABLE
        /*DOM-IGNORE-BEGIN*/= 0x00000002 /*DOM-IGNORE-END*/,

    // Slave read.  Set if the current (or most recent) slave operation
    // was a read.  Cleared if it was a write.  (Not valid during master 
    // operations).
    I2C_SLAVE_READ
        /*DOM-IGNORE-BEGIN*/ = 0x00000004 /*DOM-IGNORE-END*/,

    // Start condition detected.
    I2C_START
        /*DOM-IGNORE-BEGIN*/ = 0x00000008 /*DOM-IGNORE-END*/,

    // Stop  condition detected.
    I2C_STOP
        /*DOM-IGNORE-BEGIN*/ = 0x00000010 /*DOM-IGNORE-END*/,

    // Slave data byte (sent or received).  If cleared, the most recently 
    // sent or received data byte was an address byte.
    I2C_SLAVE_DATA
        /*DOM-IGNORE-BEGIN*/ = 0x00000020 /*DOM-IGNORE-END*/,

    // Receiver overflow error.  Data was received while the receiver buffer
    // was full.  The incoming data was lost.
    I2C_RECEIVER_OVERFLOW
        /*DOM-IGNORE-BEGIN*/ = 0x00000040 /*DOM-IGNORE-END*/,

    // Transmitter overflow error.  The software attempted to write new data
    // to the transmitter buffer and the write was ignored.
    I2C_TRANSMITTER_OVERFLOW
        /*DOM-IGNORE-BEGIN*/ = 0x00000080 /*DOM-IGNORE-END*/,

    // A 10-bit slave address matching the current slave address and mask 
    // settings has been received.
    I2C_10BIT_ADDRESS
        /*DOM-IGNORE-BEGIN*/ = 0x00000100 /*DOM-IGNORE-END*/,

    // The General Call address has been received.
    I2C_GENERAL_CALL
        /*DOM-IGNORE-BEGIN*/ = 0x00000200 /*DOM-IGNORE-END*/,

    // A master transmitter has lost arbitration and transmission has been
    // aborted.
    I2C_ARBITRATION_LOSS
        /*DOM-IGNORE-BEGIN*/ = 0x00000400 /*DOM-IGNORE-END*/,

    // The module is currently transmitting data.
    I2C_TRANSMITTER_BUSY
        /*DOM-IGNORE-BEGIN*/ = 0x00004000 /*DOM-IGNORE-END*/,

    // The most recently transmitted byte was acknowledged by the receiver.
    I2C_BYTE_ACKNOWLEDGED
        /*DOM-IGNORE-BEGIN*/ = 0x00008000 /*DOM-IGNORE-END*/

} I2C_STATUS;


// *****************************************************************************
// *****************************************************************************
// Section: I2C Addressing Macros
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Macro:
    void I2C_FORMAT_7_BIT_ADDRESS( I2C_7_BIT_ADDRESS variable, BYTE address, 
                                   BOOL read )

  Summary:
    This macro simplifies the process of initializing a I2C_7_BIT_ADDRESS 
    variable 7-bit I2C slave address.

  Description:
    This is a convenience macro that simplifies the process of initializing a
    variable with a correctly formed 7-bit address.

  Precondition:
    None.

  Parameters:
    variable    - The variable to be initialized (by direct reference).
    
    address     - The 7-bit slave address, right-aligned.
    
    read        - One bit, indicating the desired Read/Write operation.
    
                  * I2C_READ    - if a Read operation is desired
                  * I2C_WRITE   - if a Write operation is desired
  
  Returns:
    None.

  Example:
    <code>
    I2C_7_BIT_ADDRESS slave7BitAddress;
    
    I2C_FORMAT_7_BIT_ADDRESS(slave7BitAddress, SLAVE_ADDRESS_7_BIT, I2C_READ);
    if (I2CTransmitterIsReady(I2C1))
    {
        result = I2CSendByte( I2C1, I2C_GET_7_BIT_ADDRESS_BYTE(slave7BitAddress) );
    }    
    </code>

  Remarks:
    This macro directly references the variable by name, so the first parameter
    must resolve to a valid C language L-value.
  *****************************************************************************/

#define I2C_FORMAT_7_BIT_ADDRESS(v,a,r) ( (v).address=(a), (v).rw=(r) )
 

/*******************************************************************************
  Macro:
    void I2C_GET_7_BIT_ADDRESS_BYTE( I2C_7_BIT_ADDRESS variable )

  Summary:
    This macro provides access to the byte value for a 7-bit I2C slave address.

  Description:
    This is a convenience macro that provides access to the byte value for 
    an appropriately initialized 7-bit slave address variable.

  Precondition:
    The variable must have been appropriately initialized using the 
    INITIALIZE_7_BIT_ADDRESS macro or equivalent.

  Parameters:
    variable    - The I2C_7_BIT_ADDRESS variable containing the desired address
                  byte value (accessed by direct reference).

  Returns:
    The I2C address byte value (as trasnferrred) from the correctly initialized 
    7-bit I2C slave address variable.

  Example:
    <code>
    I2C_7_BIT_ADDRESS slave7BitAddress;
    
    I2C_FORMAT_7_BIT_ADDRESS(slave7BitAddress, SLAVE_ADDRESS_7_BIT, I2C_READ);
    if (I2CTransmitterIsReady(I2C1))
    {
        result = I2CSendByte( I2C1, I2C_GET_7_BIT_ADDRESS_BYTE(slave7BitAddress) );
    }    
    </code>

  Remarks:
    This macro directly references the variable by name, so the first parameter
    must resolve to a valid C language L-value.
  *****************************************************************************/

#define I2C_GET_7_BIT_ADDRESS_BYTE(v) ( (v).byte )
 

/*******************************************************************************
  Macro:
    void I2C_FORMAT_10_BIT_ADDRESS( I2C_10_BIT_ADDRESS variable, uint16_t address,
                                    BOOL read )

  Summary:
    This macro simplifies the process of initializing a I2C_10_BIT_ADDRESS 
    variable with a 10-bit I2C slave address.

  Description:
    This is a convenience macro that simplifies the process of initializing a
    I2C_10_BIT_ADDRESS variable with a correctly formed 10-bit address.

  Precondition:
    None.

  Parameters:
    variable    - The variable to be initialized (by direct reference).
    
    address     - The 10-bit slave address, right-aligned.
    
    read        - One bit, indicating the desired Read/Write operation.
    
                  * I2C_READ    - if a Read operation is desired
                  * I2C_WRITE   - if a Write operation is desired
  
  Returns:
    None.

  Example:
    <code>
    I2C_10_BIT_ADDRESS slave10BitAddress;
    
    I2C_FORMAT_10_BIT_ADDRESS(slave10BitAddress, SLAVE_ADDRESS_10_BIT, I2C_READ);
    if (I2CTransmitterIsReady(I2C1))
    {
        result = I2CSendByte( I2C1, GET_1ST_BYTE_OF_10_BIT_ADDRESS(slave10BitAddress) );
    }    
    </code>

  Remarks:
    This macro directly references the variable by name, so the first parameter
    must resolve to a valid C language L-value.
  *****************************************************************************/

#define I2C_FORMAT_10_BIT_ADDRESS(v,a,r) ( (v).low_bits   = (a) & 0x00FF,                  \
                                           (v).const_bits = I2C_10_BIT_ADDRESS_CONST_BITS, \
                                           (v).high_bits  = ((a) & 0x0300) >> 8,           \
                                           (v).rw         = (r) )
 

/*******************************************************************************
  Macro:
    BYTE I2C_GET_1ST_BYTE_OF_10_BIT_ADDRESS( I2C_10_BIT_ADDRESS variable )

  Summary:
    This macro simplifies the process of accessing the first byte of a 10-bit 
    I2C slave address.

  Description:
    This is a convenience macro that simplifies the process of accessing the 
    first byte of a correctly formed 10-bit I2C slave address.

  Precondition:
    The I2C_10_BIT_ADDRESS variable passed by reference must have been properly
    initialized by the I2C_FORMAT_10_BIT_ADDRESS macro or equivalent.

  Parameters:
    variable    - The I2C_7_BIT_ADDRESS variable containing the desired address
                  byte value (accessed by direct reference).
  
  Returns:
    The first byte to be transmitted of the correctly formed 10-bit I2C slave
    address.

  Example:
    <code>
    I2C_10_BIT_ADDRESS slave10BitAddress;
    
    I2C_FORMAT_10_BIT_ADDRESS(slave10BitAddress, SLAVE_ADDRESS_10_BIT, I2C_READ);
    if (I2CTransmitterIsReady(I2C1))
    {
        result = I2CSendByte( I2C1, I2C_GET_1ST_BYTE_OF_10_BIT_ADDRESS(slave10BitAddress) );
    }    
    </code>

  Remarks:
    This macro directly references the variable by name, so the first parameter
    must resolve to a valid C language L-value.
  *****************************************************************************/

#define I2C_GET_1ST_BYTE_OF_10_BIT_ADDRESS(v) ( (v).first_byte )


/***************************************************************************************
  Summary:
    This macro simplifies the process of generating the second byte of a
    10-bit I2C slave address.
    
  Description:
    Macro: BYTE I2C_GET_2ND_BYTE_OF_10_BIT_ADDRESS( I2C_10_BIT_ADDRESS
    variable )
    
    This is a convenience macro that simplifies the process of accessing
    the second byte of a correctly formed 10-bit I2C slave address.
    
  Conditions:
    The I2C_10_BIT_ADDRESS variable passed by reference must have been
    properly initialized by the I2C_FORMAT_10_BIT_ADDRESS macro or
    equivalent.
    
  Input:
    variable -  The I2C_10_BIT_ADDRESS variable containing the desired
                address byte value (accessed by direct reference)
  Return:
    The second byte to be transmitted of the correctly formed 10-bit I2C
    slave address.
    
  Example:
    <code>
    if (I2CTransmitterIsReady(I2C1))
    {
        result = I2CSendByte( I2C1, I2C_GET_2ND_BYTE_OF_10_BIT_ADDRESS(slave10BitAddress) );
    }
    </code>
    
  Remarks:
    This macro directly references the variable by name, so the first
    parameter must resolve to a valid C language L-value.                               
  ***************************************************************************************/

#define I2C_GET_2ND_BYTE_OF_10_BIT_ADDRESS(v) ( (v).second_byte )

#endif // _I2C_h_

