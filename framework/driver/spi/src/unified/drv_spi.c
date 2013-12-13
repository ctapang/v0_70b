/*******************************************************************************
  SPI Device Driver Definition

  Company:
    Microchip Technology Incorported

  File Name:
    drv_spi.c

  Summary:
    SPI Device Driver Implementation

  Description:
    The SPI device driver provides a simple interface to manage the SPI
    modules on Microchip microcontrollers.  This file Implements the core 
    interface routines for the SPI driver.
    
    While building the driver from source, ALWAYS use this file in the build.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

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
//DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************

#include "system_config.h"
#include "driver/spi/src/drv_spi_local.h"


// *****************************************************************************
// *****************************************************************************
// Section: File Scope Functions
// *****************************************************************************
// *****************************************************************************


//******************************************************************************
/* Function:
    static void _DRV_SPI_PortSetup( const SPI_MODULE_ID    plibId,
                                    DRV_SPI_PORTS_CONFIG   * portsConfig )

  Summary:
    Sets up the ports from the initialization structure

  Description:
    This routine sets up the ports from the initialization structure.

  Remarks:
    Called
*/

static void _DRV_SPI_PortSetup
(
    /* Function Parameters: (Dynamic arguments are removed from static builds.) */
    _DRV_SPI_DYN_ARG_COMMA( const SPI_MODULE_ID plibId )
    DRV_SPI_PORTS_CONFIG    * portsConfig
)
{
    /* Check if the PORTS configuration is through remapping ? */
    if( true == DRV_SPI_PORTS_REMAP_USAGE )
    {
        /* MISO - Input Mapping */
        SYS_PORTS_InputRemapping( portsConfig->inputFunc, portsConfig->inputPin );

        /* MOSI - Output Mapping */
        SYS_PORTS_OutputRemapping( portsConfig->outputPin, portsConfig->outputFunc );

        /* SCK - Mapping */
        if ( DRV_SPI_MODE_MASTER == DRV_SPI_USAGE_MODE )
        {
            /* SCK - Output Mapping */
            SYS_PORTS_OutputRemapping( portsConfig->clockOutputPin, portsConfig->clockOutputFunc );
        }
        else /* ( DRV_SPI_MODE_SLAVE == DRV_SPI_USAGE_MODE ) */
        {
            /* SCK - Input Mapping */
            SYS_PORTS_InputRemapping( portsConfig->clockInputFunc, portsConfig->clockInputPin );
        }

        /* /SS - Mapping */
        if ( DRV_SPI_MODE_MASTER == DRV_SPI_USAGE_MODE )
        {
            /* /SS - Output Mapping */
            SYS_PORTS_OutputRemapping( portsConfig->ssOutputPin, portsConfig->ssOutputFunc );
        }
        else /* ( DRV_SPI_MODE_SLAVE == DRV_SPI_USAGE_MODE ) */
        {
            /* /SS - Input Mapping */
            SYS_PORTS_InputRemapping( portsConfig->ssInputFunc, portsConfig->ssInputPin );
        }
    }
    else /* ( false == DRV_SPI_PORTS_REMAP_USAGE ) */
    {
        /* MISO - Input Enabling */
        _DRV_SPI_PinEnable( _DRV_SPI_PERIPHERAL_ID_GET( plibId ), SPI_PIN_DATA_IN );

        /* MOSI - Output Enabling */
        _DRV_SPI_PinEnable( _DRV_SPI_PERIPHERAL_ID_GET( plibId ), SPI_PIN_DATA_OUT );

        /* SCK - Enabling */
        _DRV_SPI_PinEnable( _DRV_SPI_PERIPHERAL_ID_GET( plibId ), SPI_PIN_SERIAL_CLOCK );

        if ( false == DRV_SPI_SLAVE_SELECT_MANUAL )
        {
            /* Slave Select - Input Enabling */
            _DRV_SPI_PinEnable( _DRV_SPI_PERIPHERAL_ID_GET( plibId ), SPI_PIN_SLAVE_SELECT );
        }
        else
        {
            /* /SS - Configuration for Manual mode */
            if ( DRV_SPI_MODE_MASTER == DRV_SPI_USAGE_MODE )
            {
                /* /SS - Output */
                _DRV_SPI_PinDirectionWriteSet( portsConfig->portId, portsConfig->pinNumber );
            }
            else /* ( DRV_SPI_MODE_SLAVE == DRV_SPI_USAGE_MODE ) */
            {
                /* /SS - Input */
                _DRV_SPI_PinDirectionReadSet( portsConfig->portId, portsConfig->pinNumber );
            }
        }
    }

} /* _DRV_SPI_PortSetup */


//******************************************************************************
/* Function:
    static void _DRV_SPI_SetupHardware( const SPI_MODULE_ID    plibId,
                                        DRV_SPI_OBJ            dObj,
                                        DRV_SPI_INIT           *spiInit )

  Summary:
    Sets up the hardware from the initialization structure

  Description:
    This routine sets up the hardware from the initialization structure.
 
  Remarks:
    Called 
*/

static void _DRV_SPI_SetupHardware
( 
    /* Function Parameters: (Dynamic arguments are removed from static builds.) */
    _DRV_SPI_DYN_ARG_COMMA( const SPI_MODULE_ID plibId )
    _DRV_SPI_DYN_ARG_COMMA( DRV_SPI_OBJ dObj )
    DRV_SPI_INIT * spiInit
)
{
    /* Initialize the Interrupt Sources */
    _DRV_SPI_STATIC_INT_SRC( _DRV_SPI_OBJ(dObj, interruptSource) =
            _DRV_SPI_INT_SRC_GET(spiInit->interruptSource) );
    _DRV_SPI_STATIC_INT_SRC( _DRV_SPI_OBJ(dObj, rxInterruptSource) =
            _DRV_SPI_GET_INT_SRC_RX(spiInit->rxInterruptSource) );
    _DRV_SPI_STATIC_INT_SRC( _DRV_SPI_OBJ(dObj, errInterruptSource) =
            _DRV_SPI_GET_INT_SRC_ERROR(spiInit->errInterruptSource) );

    /* Power state initialization */
    _DRV_SPI_PowerState( _DRV_SPI_PERIPHERAL_ID_GET(plibId) , spiInit );

    /* Usage Mode Master/Slave */
    _DRV_SPI_UsageMode( _DRV_SPI_PERIPHERAL_ID_GET(plibId),
                        _DRV_SPI_USAGE_MODE_GET(spiInit->spiMode) );
    _DRV_SPI_OBJ( dObj, spiMode ) = _DRV_SPI_USAGE_MODE_GET(spiInit->spiMode);

    /* Primary Prescaler Selection */
    _DRV_SPI_PrimaryPrescale( _DRV_SPI_PERIPHERAL_ID_GET(plibId),
                              _DRV_SPI_PRIMARY_PRESCALE_GET(spiInit->priPrescale) );
    _DRV_SPI_OBJ(dObj, priPrescale) = _DRV_SPI_PRIMARY_PRESCALE_GET(spiInit->priPrescale);

    /* Secondary Prescaler Selection */
    _DRV_SPI_SecondaryPrescale( _DRV_SPI_PERIPHERAL_ID_GET(plibId),
                                _DRV_SPI_SECONDARY_PRESCALE_GET(spiInit->secPrescale) );
    _DRV_SPI_OBJ(dObj, secPrescale) = _DRV_SPI_SECONDARY_PRESCALE_GET(spiInit->secPrescale);

    /* Communication Width Selection */
    _DRV_SPI_CommunicationWidthSelect( _DRV_SPI_PERIPHERAL_ID_GET(plibId),
                                       _DRV_SPI_COMMUNICATION_WIDTH_GET(spiInit->commWidth) );
    _DRV_SPI_OBJ(dObj, commWidth) = _DRV_SPI_COMMUNICATION_WIDTH_GET(spiInit->commWidth);

    /* Input Clock Frequency */
    _DRV_SPI_InputClockFrequency( _DRV_SPI_PERIPHERAL_ID_GET(plibId),
                                  _DRV_SPI_INPUT_CLOCK_GET(spiInit->inputClkFrequency) );

    /* Baudrate selection */
    _DRV_SPI_BaudRateSet( _DRV_SPI_PERIPHERAL_ID_GET(plibId),
                          _DRV_SPI_BAUD_RATE_VALUE_GET(spiInit->baudRate) );

    /* Protocol Selection */
    _DRV_SPI_ProtocolUsage( _DRV_SPI_PERIPHERAL_ID_GET(plibId),
                            _DRV_SPI_PROTOCOL_USAGE_TYPE_GET(spiInit->spiProtocolType) );
    _DRV_SPI_OBJ(dObj, spiProtocolType) = _DRV_SPI_PROTOCOL_USAGE_TYPE_GET(spiInit->spiProtocolType);

    /* Buffer type selection */
    _DRV_SPI_BufferUsageType( _DRV_SPI_PERIPHERAL_ID_GET(plibId),
                              _DRV_SPI_BUFFER_USAGE_TYPE_GET(spiInit->bufferType) );
    _DRV_SPI_OBJ(dObj, bufferType) = _DRV_SPI_BUFFER_USAGE_TYPE_GET(spiInit->bufferType);

    /* Clock Mode */
    _DRV_SPI_ClockMode( _DRV_SPI_PERIPHERAL_ID_GET(plibId),
                        _DRV_SPI_CLOCK_OPERATION_MODE_GET(spiInit->clockMode) );
    _DRV_SPI_OBJ(dObj, clockMode) = _DRV_SPI_CLOCK_OPERATION_MODE_GET(spiInit->clockMode);

    /* SPI Port Setup */
    _DRV_SPI_PortSetup( _DRV_SPI_PERIPHERAL_ID_GET(plibId), spiInit->portsConfig );
    _DRV_SPI_OBJ(dObj, portsConfig) = spiInit->portsConfig;

} /* _DRV_SPI_SetupHardware */


// *****************************************************************************
// *****************************************************************************
// Section: Driver Interface Function Definitions
// *****************************************************************************
// *****************************************************************************

//******************************************************************************
/* Function:
    SYS_MODULE_OBJ DRV_SPI_Initialize ( const SYS_MODULE_INDEX  index,
                                        const SYS_MODULE_INIT * const init )

  Summary:
    Initializes hardware and data for the given instance of the SPI module

  Description:
    This routine initializes hardware for the instance of the SPI module,
    using the hardware initialization given data.  It also initializes all 
    necessary internal data.

  Parameters:
    index           - Identifies the driver instance to be initialized
    
    init            - Pointer to the data structure containing all data
                      necessary to initialize the hardware. This pointer may
                      be null if no data is required and static initialization 
                      values are to be used.

  Returns:
    If successful, returns a valid handle to a driver instance object.
    Otherwise, it returns SYS_MODULE_OBJ_INVALID.
*/

_DRV_SPI_DYN_RETURN_TYPE(SYS_MODULE_OBJ) _DRV_SPI_MAKE_NAME(Initialize)
(
    /* Function Parameters: (Dynamic arguments are removed from static builds.) */
    _DRV_SPI_DYN_ARG_COMMA( const SYS_MODULE_INDEX        drvIndex )
                               const SYS_MODULE_INIT * const init
)
{
    _DRV_SPI_DYN( DRV_SPI_OBJ dObj = (DRV_SPI_OBJ) 0 );
    DRV_SPI_INIT * spiInit = NULL;

    /* Validate the driver index */
    if ( _DRV_SPI_INDEX_GET(drvIndex) >= DRV_SPI_INDEX_COUNT )
    {
        _DRV_SPI_DYN_RETURN( SYS_MODULE_OBJ_INVALID );
    }

    /* Assign to the local pointer the init data passed */
    spiInit = ( DRV_SPI_INIT * ) init;

    /* Allocate the driver object and set the operation flag to be in use */
    _DRV_SPI_DYN( dObj = _DRV_SPI_OBJ_ALLOCATE(drvIndex) );

    /* TODO : Initialize any other SPI specific members */

    /* Check that the object is valid */
    SYS_ASSERT( _DRV_SPI_DYN_Test( dObj < DRV_SPI_INSTANCES_NUMBER ), "Hardware Object is invalid" );

    /* Object is valid, set it in use */
    _DRV_SPI_OBJ( dObj, inUse ) = true;

    /* Update the SPI Module Index */
    _DRV_SPI_DYN(_DRV_SPI_OBJ( dObj , spiId ) = _DRV_SPI_PERIPHERAL_ID_GET( spiInit->spiId ));

    /* Setup the Hardware */
    _DRV_SPI_SetupHardware( _DRV_SPI_DYN_PARAM_COMMA( _DRV_SPI_PERIPHERAL_ID_GET(spiInit->spiId) )
                               _DRV_SPI_DYN_PARAM_COMMA( dObj )
                               spiInit );

    /* Enable the SPI module */
    _DRV_SPI_Enable( _DRV_SPI_PERIPHERAL_ID_GET(spiInit->spiId) ) ;

    /* Update the object index */
    _DRV_SPI_OBJ( dObj, objIndex ) = drvIndex;

    /* Update the necessary inter nal data for Buffer operations */
    _DRV_SPI_OBJ( dObj , qHeadPtr)  = (uint8_t *)_DRV_SPI_BYTEQ( drvIndex );
    _DRV_SPI_OBJ( dObj , qTailPtr )  = (uint8_t *)_DRV_SPI_BYTEQ( drvIndex );
    /* Buffer is initially empty */
    _DRV_SPI_OBJ( dObj , isBufferEmpty ) = true;
    /* Buffer is initially can never be full */
    _DRV_SPI_OBJ( dObj , isBufferFull ) = false;

    /* Reset the number of clients */
    _DRV_SPI_MC( _DRV_SPI_OBJ( dObj, numClients ) = 0 ) ;

    /* Interrupt flag cleared on the safer side */
    _DRV_SPI_InterruptSourceClear( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ(dObj, interruptSource) ) );
    _DRV_SPI_InterruptSourceClear( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ(dObj, rxInterruptSource) ) );
    _DRV_SPI_InterruptSourceClear( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ(dObj, errInterruptSource) ) );
    
    /* Enable the interrupt source in case of interrupt mode */
    _DRV_SPI_InterruptSourceEnable( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ(dObj, interruptSource) ) );
    _DRV_SPI_InterruptSourceEnable( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ(dObj, rxInterruptSource) ) );
    _DRV_SPI_InterruptSourceEnable( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ(dObj, errInterruptSource) ) );

    /* Set the current driver state */
    _DRV_SPI_OBJ( dObj , status ) = SYS_STATUS_READY;

    /* Return the driver handle */
    _DRV_SPI_DYN_RETURN( (SYS_MODULE_OBJ)dObj );
} /* DRV_SPI_Initialize */


//******************************************************************************
/* Function:
    void DRV_SPI_Reinitialize ( SYS_MODULE_OBJ          object,
                                const SYS_MODULE_INIT * const init )

  Summary:
    Reinitializes and refreshes the hardware for the instance of the SPI
    module

  Description:
    This routine reinitializes and refreshes the hardware for the instance
    of the SPI module using the hardware initialization given data.
    It does not clear or reinitialize internal data structures

  Parameters:
    object          - Identifies the Driver Object returned by the Initialize
                      interface
    init            - Pointer to the data structure containing any data
                      necessary to initialize the hardware.

  Returns:
    None
*/

void _DRV_SPI_MAKE_NAME( Reinitialize )
(
    /* Function Parameters: (Dynamic arguments are removed from static builds.) */
    _DRV_SPI_DYN_ARG_COMMA( SYS_MODULE_OBJ object )
    const SYS_MODULE_INIT * const init 
)
{
    _DRV_SPI_DYN( DRV_SPI_OBJ dObj = (DRV_SPI_OBJ) object );
    DRV_SPI_INIT * spiInit = NULL;

    /* Check for the valid driver object passed */
    SYS_ASSERT( _DRV_SPI_DYN_Test( dObj < DRV_SPI_INSTANCES_NUMBER ), "Driver Object is invalid" );

    /* Valid init structure is present */
    spiInit = ( DRV_SPI_INIT * ) init;

    /* Stop/Disable the device if needed */
    _DRV_SPI_Disable ( _DRV_SPI_PERIPHERAL_ID_GET(spiInit->spiId) ) ;

    /* Set the current driver state */
    _DRV_SPI_OBJ( dObj , status ) = SYS_STATUS_UNINITIALIZED ;

    /* Setup the Hardware */
    _DRV_SPI_SetupHardware( _DRV_SPI_DYN_PARAM_COMMA( spiInit->spiId )
                            _DRV_SPI_DYN_PARAM_COMMA( dObj )
                            spiInit );

    /* Update the necessary internal data for Buffer operations */
    _DRV_SPI_OBJ( dObj , qHeadPtr )  = (uint8_t *)_DRV_SPI_BYTEQ( _DRV_SPI_OBJ( dObj, objIndex ) );
    _DRV_SPI_OBJ( dObj , qTailPtr )  = (uint8_t *)_DRV_SPI_BYTEQ( _DRV_SPI_OBJ( dObj, objIndex ) );
    /* Buffer is initially empty */
    _DRV_SPI_OBJ( dObj , isBufferEmpty ) = true;
    /* Buffer is initially can never be full */
    _DRV_SPI_OBJ( dObj , isBufferFull ) = false;

    /* Start/Enable the device if it was stop/disabled */
    _DRV_SPI_Enable ( _DRV_SPI_PERIPHERAL_ID_GET(spiInit->spiId) ) ;

    /* Set the curent driver state */
    _DRV_SPI_OBJ( dObj , status ) = SYS_STATUS_READY;

} /* DRV_SPI_Reinitialize */


//******************************************************************************
/* Function:
    void DRV_SPI_Deinitialize ( SYS_MODULE_OBJ object )

  Summary:
    Deinitializes the specific module instance of the SPI module

  Description:
    Deinitializes the specific module instancedisabling its operation (and any
    hardware for driver modules).  Resets all the internal data structures and
    fields for the specified instance to the default settings.

  Parameters:
    object          - Identifies the Driver Object returned by the Initialize
                      interface

  Returns:
    None
*/

void _DRV_SPI_MAKE_NAME( Deinitialize )
(
    /* Function Parameter: (Dynamic arguments are removed from static builds.) */
    _DRV_SPI_DYN_ARG( SYS_MODULE_OBJ object )
)
{
    _DRV_SPI_DYN( DRV_SPI_OBJ dObj = (DRV_SPI_OBJ) object );

    /* Check for the valid driver object passed */
    SYS_ASSERT( _DRV_SPI_DYN_Test( dObj < DRV_SPI_INSTANCES_NUMBER ), "Driver Object is invalid" );

    /* Interrupt De-Registration */
    _DRV_SPI_InterruptSourceDisable( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ(dObj, interruptSource) ) );
    _DRV_SPI_InterruptSourceDisable( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ(dObj, rxInterruptSource) ) );
    _DRV_SPI_InterruptSourceDisable( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ(dObj, errInterruptSource) ) );

    /* Stop/Disable the device if needed */
    _DRV_SPI_Disable( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( dObj , spiId ) ) ) ;

    /* SPI Port Deselect */
    if( false == DRV_SPI_PORTS_REMAP_USAGE )
    {
        /* MISO - Input Enabling */
        _DRV_SPI_PinDisable( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( dObj , spiId ) ), SPI_PIN_DATA_IN );

        /* MOSI - Output Enabling */
        _DRV_SPI_PinDisable( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( dObj , spiId ) ), SPI_PIN_DATA_OUT );

        /* SCK - Enabling */
        _DRV_SPI_PinDisable( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( dObj , spiId ) ), SPI_PIN_SERIAL_CLOCK );

        if ( false == DRV_SPI_SLAVE_SELECT_MANUAL )
        {
            /* Slave Select - Input Enabling */
            _DRV_SPI_PinDisable( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( dObj , spiId ) ), SPI_PIN_SLAVE_SELECT );
        }
    }
    else
    {

    }

    /* Set the Device Status */
    _DRV_SPI_OBJ( dObj , status ) = SYS_MODULE_DEINITIALIZED;

    /* Remove the driver usage */
    _DRV_SPI_OBJ( dObj , inUse ) = false;

} /* DRV_SPI_Deinitialize */


//******************************************************************************
/* Function:
    SYS_STATUS DRV_SPI_Status ( SYS_MODULE_OBJ object )

  Summary:
    Provides the current status of the hardware instance of the SPI module

  Description:
    This routine Provides the current status of the hardware instance of the
    SPI module.

  Parameters:
    object          - Identifies the Driver Object returned by the Initialize
                      interface

  Returns:
    SYS_STATUS_READY    Indicates that any previous module operation for the
                        specified module has completed
                        
    SYS_STATUS_BUSY     Indicates that a previous module operation for the
                        specified module has not yet completed
                        
    SYS_STATUS_ERROR    Indicates that the specified module is in an error state
*/

SYS_STATUS _DRV_SPI_MAKE_NAME( Status )
(
    /* Function Parameter: (Dynamic arguments are removed from static builds.) */
    _DRV_SPI_DYN_ARG( SYS_MODULE_OBJ object )
)
{
    _DRV_SPI_DYN( DRV_SPI_OBJ dObj = (DRV_SPI_OBJ) object );

    /* Check for the valid driver object passed */
    SYS_ASSERT( _DRV_SPI_DYN_Test( dObj < DRV_SPI_INSTANCES_NUMBER ), "Driver Object is invalid" );

    /* Return the status associated with the driver handle */
    return ( _DRV_SPI_OBJ( dObj , status ) );

} /* DRV_SPI_Status */


//******************************************************************************
/* Function:
    void DRV_SPI_Tasks ( SYS_MODULE_OBJ object )

  Summary:
    Used to maintain the driver's state machine and implement its ISR

  Description:
    This routine is used to maintain the driver's internal state machine and
    implement its ISR for interrupt-driven implementations.

  Parameters:
    object          - Identifies the Driver Object returned by the Initialize
                      interface

  Returns:
    None.
*/

void _DRV_SPI_MAKE_NAME( Tasks )
(
    /* Function Parameter: (Dynamic arguments are removed from static builds.) */
    _DRV_SPI_DYN_ARG( SYS_MODULE_OBJ object )
)
{
    _DRV_SPI_DYN( DRV_SPI_OBJ dObj = (DRV_SPI_OBJ) object );
    SPI_BUFFER byte ;

    /* Check for the valid driver object passed */
    SYS_ASSERT( _DRV_SPI_DYN_Test( dObj < DRV_SPI_INSTANCES_NUMBER ), "Driver Object is invalid" );

    /* Check for the interrupt flag */

    if( true == _DRV_SPI_InterruptSourceStatusGet( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ(dObj, interruptSource) ) ) )
    {
        /* Transmit till the TX buffer is empty */
        while( _DRV_SPI_TransmitterEmpty( _DRV_SPI_OBJ( dObj , spiId ) ) )
        {
            /* Is the buffer empty ? */
            if( true == _DRV_SPI_OBJ( dObj , isBufferEmpty ) )
            {
                /* Disable the interrupt */
                _DRV_SPI_InterruptSourceDisable( _DRV_SPI_GET_INT_SRC_TX( _DRV_SPI_OBJ( dObj, interruptSource) ) );
                break;
            }

            /* Get the data to be transmitted from the buffer */
            byte = *_DRV_SPI_OBJ( dObj , qHeadPtr );
            /* Increment the buffer pointer */
            _DRV_SPI_OBJ( dObj , qHeadPtr )++;

            if( _DRV_SPI_OBJ( dObj , qHeadPtr ) == (uint8_t *)_DRV_SPI_BYTEQ( _DRV_SPI_OBJ( dObj, objIndex ) ) +
                                                      sizeof( _DRV_SPI_BYTEQ( _DRV_SPI_OBJ( dObj, objIndex ) ) ) )
            {
                _DRV_SPI_OBJ( dObj , qHeadPtr ) = (uint8_t *)_DRV_SPI_BYTEQ( _DRV_SPI_OBJ( dObj, objIndex ) );
            }

            _DRV_SPI_OBJ( dObj , isBufferFull ) = false;

            /* Send the byte */
            _DRV_SPI_TransmitterByteSend( _DRV_SPI_PLIB_ID_GET( _DRV_SPI_OBJ( dObj , spiId ) ) , byte ) ;

            if( _DRV_SPI_OBJ( dObj , qHeadPtr ) == _DRV_SPI_OBJ( dObj , qTailPtr ) )
            {
                _DRV_SPI_OBJ( dObj , isBufferEmpty ) = true;
                break;
            }
        }

        /* Clear Interrupt/Status Flag */
        _DRV_SPI_InterruptSourceClear( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ(dObj, interruptSource) ) );

    }
    else if( true == _DRV_SPI_InterruptSourceStatusGet( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ( dObj, rxInterruptSource ) ) ) )
    {
        while( _DRV_SPI_ReceiverDataAvailable( _DRV_SPI_OBJ( dObj , moduleId ) ) )  // Do not loop in a tasks routine waiting for HW. -Bud
        {
            /* If a read request is recieved and data is available to read this
             state does all the work of reading the data from the RX buffer */

            /* Receive a byte in the buffer */
            byte = _DRV_SPI_ReceiverByteReceive( _DRV_SPI_PLIB_ID_GET( _DRV_SPI_OBJ( dObj , moduleId ) ) );

            /* Sets the flag data present */
            *_DRV_SPI_OBJ( dObj , qTailPtr ) = byte;
            _DRV_SPI_OBJ( dObj , qTailPtr )++;

            if( _DRV_SPI_OBJ( dObj , qTailPtr ) == ((uint8_t *)_DRV_SPI_BYTEQ_RX( objIndex )) + sizeof( _DRV_SPI_BYTEQ_RX( objIndex ) ) )
            {
                _DRV_SPI_OBJ( dObj , qTailPtr ) = (uint8_t *)_DRV_SPI_BYTEQ_RX( _DRV_SPI_OBJ( dObj, objIndex ) );
            }

            if( _DRV_SPI_OBJ( dObj , qTailPtr ) == _DRV_SPI_OBJ( dObj , qHeadPtr ) )
            {
                /* Sets the flag RX full */
                _DRV_SPI_OBJ( dObj , isBufferFull ) = true;
            }
            _DRV_SPI_OBJ( dObj , isBufferEmpty ) = false;
        }

        /* Clear Interrupt/Status Flag */
        _DRV_SPI_InterruptSourceClear( _DRV_SPI_GET_INT_SRC_RX( _DRV_SPI_OBJ(dObj, rxInterruptSource)) ) ;

    }
    else if( true == _DRV_SPI_InterruptSourceStatusGet( _DRV_SPI_INT_SRC_GET( _DRV_SPI_OBJ( dObj, errInterruptSource ) ) ) )
    {
        /* This state is encountered when an error interrupt has occured.
           or an error has occured during read */

        if( _DRV_SPI_ReceiverHasOverflowed ( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ(dObj, moduleId) ) ) )
        {
            _DRV_SPI_ReceiverOverflowClear ( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ(dObj, moduleId) ) ) ;
        }

        /* Clear Interrupt/Status Flag */
        _DRV_SPI_InterruptSourceClear( _DRV_SPI_GET_INT_SRC_ERROR( _DRV_SPI_OBJ(dObj, errInterruptSource ) ) );
    }

} /* DRV_SPI_Tasks */


//******************************************************************************
/* Function:
    DRV_HANDLE DRV_SPI_Open ( const SYS_MODULE_INDEX    index,
                              const DRV_IO_INTENT       intent )

  Summary:
    Opens the specific module instance and returns a handle

  Description:
    This routine opens a driver for use by any client module and provides a
    handle that must be provided to any of the other driver operations to
    identify the caller and the instance of the driver/hardware module.

  Parameters:
    index           - Identifier for the instance to be initialized
    ioIntent        - Possible values from the enumeration DRV_IO_INTENT

  Returns:
    If successful, the routine returns a valid open-instance handle (a number
    identifying both the caller and the module instance)
    If an error occurs, the return value is DRV_HANDLE_INVALID
*/

_DRV_SPI_MC_RETURN_TYPE( DRV_HANDLE ) _DRV_SPI_MAKE_NAME( Open )
(
    /* Function Parameters: (Dynamic arguments are removed from static builds.) */
    _DRV_SPI_DYN_ARG_COMMA( const SYS_MODULE_INDEX drvIndex )
    const DRV_IO_INTENT ioIntent
)
{
    /* Multi client variables are removed from single client builds. */
    _DRV_SPI_MC( DRV_SPI_CLIENT_OBJ clientObj = (DRV_SPI_CLIENT_OBJ) 0 );
    _DRV_SPI_MC( DRV_SPI_OBJ dObj = 0 );
    
    /* Validate the driver index */
    if( _DRV_SPI_INDEX_GET(drvIndex) >= DRV_SPI_INDEX_COUNT )
    {
        _DRV_SPI_MC_RETURN( DRV_HANDLE_INVALID );
    }

    /* Check for exclusive access */
    if(( _DRV_SPI_MC_Test( _DRV_SPI_OBJ( dObj , IsExclusive ) == true )) ||
       ( _DRV_SPI_MC_Test( _DRV_SPI_OBJ( dObj , numClients ) > 0) && DRV_IO_ISEXCLUSIVE( ioIntent )))
    {
        /* Set that the hardware instance is opened in exclusive mode */
        _DRV_SPI_MC_RETURN( DRV_HANDLE_INVALID ) ;
    }

    /* Check if max number of clients open */
    if( _DRV_SPI_MC_Test( _DRV_SPI_OBJ( dObj, numClients ) > DRV_SPI_CLIENTS_NUMBER ) )
    {
        /* Set that the hardware instance is opened with max clients */
        _DRV_SPI_MC_RETURN( DRV_HANDLE_INVALID ) ;
    }

    /* Setup client operations */

    /* To Do: OSAL - Lock Mutex */

    /* Allocate the client object and set the flag as in use */
    _DRV_SPI_MC( clientObj = _DRV_SPI_ClientObjectAllocate( _DRV_SPI_INDEX_GET( drvIndex) ) ) ;

    /* Check for the client object */
    SYS_ASSERT( _DRV_SPI_MC_Test( clientObj < DRV_SPI_CLIENTS_NUMBER ) , "Invalid Client Object" );

    _DRV_SPI_CLIENT_OBJ( clientObj , inUse ) = true;
    _DRV_SPI_CLIENT_OBJ( clientObj , driverObject ) = _DRV_SPI_INDEX_GET( drvIndex );

    /* Increment the client in case of Multi client support, otherwise remove
       the below statement */
    _DRV_SPI_MC(dObj = _DRV_SPI_CLIENT_OBJ(clientObj, driverObject));
    _DRV_SPI_MC( _DRV_SPI_OBJ(dObj, numClients)++ ) ;

    /* Update that, the client is opened in exclusive access mode */
    if( DRV_IO_ISEXCLUSIVE( ioIntent ) )
    {
        _DRV_SPI_OBJ( dObj , IsExclusive ) = true;
    }

    /* To Do: OSAL - Unlock Mutex */

    /* Update the Client Status */
    _DRV_SPI_CLIENT_OBJ( clientObj , status ) = DRV_SPI_CLIENT_STATUS_READY;

    /* Return the client object */
    _DRV_SPI_MC_RETURN( ( DRV_HANDLE ) clientObj );

} /* DRV_SPI_Open */


//******************************************************************************
/* Function:
    void DRV_SPI_Close ( DRV_HANDLE handle )

  Summary:
    Closes an opened-instance of a driver

  Description:
    This routine closes an opened-instance of a driver, invalidating the given
    handle.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    None
*/

void _DRV_SPI_MAKE_NAME( Close )
( 
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_SPI_MC_ARG( DRV_HANDLE handle )
)
{
    /* Multi client variables are removed from single client builds. */
    _DRV_SPI_MC( DRV_SPI_CLIENT_OBJ clientObj );

    /* Get the Client object from the handle passed */
    _DRV_SPI_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_SPI_MC_Test( clientObj < DRV_SPI_CLIENTS_NUMBER ), "Invalid Client Object" ) ;

    /* To Do: OSAL - lock Mutex */

    /* Free the Client Instance */
    _DRV_SPI_CLIENT_OBJ( clientObj , inUse ) = false ;

    /* To Do: OSAL - unlock Mutex */

    /* Update the Client Status */
    _DRV_SPI_CLIENT_OBJ( clientObj , status ) = DRV_SPI_CLIENT_STATUS_INVALID;

} /* DRV_SPI_Close */


//******************************************************************************
/* Function:
    DRV_SPI_CLIENT_STATUS DRV_SPI_ClientStatus (DRV_HANDLE handle)

  Summary:
    Gets the status of the module instance associated with the handle

  Description:
    This routine gets the status of the module instance associated with the
    handle.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    DRV_SPI_CLIENT_STATUS value describing the current status of the driver
*/

DRV_SPI_CLIENT_STATUS _DRV_SPI_MAKE_NAME( ClientStatus )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_SPI_MC_ARG( DRV_HANDLE handle )
)
{
    /* Multi client variables are removed from single client builds. */
    _DRV_SPI_MC( DRV_SPI_CLIENT_OBJ clientObj = (DRV_SPI_CLIENT_OBJ) 0 );

    /* Get the Client object from the handle passed */
    _DRV_SPI_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_SPI_MC_Test( clientObj < DRV_SPI_CLIENTS_NUMBER ), "Invalid Client Object" ) ;

    /* Return the client status associated with the handle passed */
    return( _DRV_SPI_CLIENT_OBJ( clientObj , status ) );

} /* DRV_SPI_ClientStatus */


// *****************************************************************************
/* Function:
    void DRV_SPI_CommunicationSetup ( DRV_HANDLE                        handle,
                                      const DRV_SPI_COMM_CONFIG * const config )

  Summary:
    Sets up the device communication parameters

  Description:
    This function sets up the device communication parameters

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

    config       - Communication parameters indetified by DRV_SPI_COMM_CONFIG

  Returns:
    None
*/

void _DRV_SPI_MAKE_NAME( CommunicationSetup )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_SPI_MC_ARG_COMMA( DRV_HANDLE handle )
    const DRV_SPI_COMM_CONFIG * const config
)
{
    /* Multi client variables are removed from single client builds. */
    _DRV_SPI_MC( DRV_SPI_CLIENT_OBJ clientObj = (DRV_SPI_CLIENT_OBJ) 0 );

    /* Get the Client object from the handle passed */
    _DRV_SPI_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_SPI_MC_Test( clientObj < DRV_SPI_CLIENTS_NUMBER ), "Invalid Client Object" ) ;

        /* Get the driver object from the client */
    _DRV_SPI_DYN( dObj = _DRV_SPI_CLIENT_OBJ( clientObj, driverObject ) );

     /* Stop/Disable the device */
    _DRV_SPI_Disable( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( dObj , spiId ) ) ) ;

    /* Usage Mode Master/Slave */
    _DRV_SPI_UsageMode( _DRV_SPI_PERIPHERAL_ID_GET(_DRV_SPI_OBJ( dObj , spiId )),
                        _DRV_SPI_USAGE_MODE_GET(config->spiMode) );
    _DRV_SPI_OBJ( dObj, spiMode ) = _DRV_SPI_USAGE_MODE_GET(config->spiMode);

    /* Input Clock Frequency */
    _DRV_SPI_InputClockFrequency( _DRV_SPI_PERIPHERAL_ID_GET(_DRV_SPI_OBJ( dObj , spiId )),
                                  _DRV_SPI_INPUT_CLOCK_GET(config->inputClkFrequency) );

    /* Baudrate selection */
    _DRV_SPI_BaudRateSet( _DRV_SPI_PERIPHERAL_ID_GET(_DRV_SPI_OBJ( dObj , spiId )),
                          _DRV_SPI_BAUD_RATE_VALUE_GET(config->baudRate) );

    /* Clock Mode */
    _DRV_SPI_ClockMode( _DRV_SPI_PERIPHERAL_ID_GET(_DRV_SPI_OBJ( dObj , spiId )),
                        _DRV_SPI_CLOCK_OPERATION_MODE_GET(config->clockMode) );
    _DRV_SPI_OBJ(dObj, clockMode) = _DRV_SPI_CLOCK_OPERATION_MODE_GET(config->clockMode);

    /* Primary Prescaler Selection */
    _DRV_SPI_PrimaryPrescale( _DRV_SPI_PERIPHERAL_ID_GET(_DRV_SPI_OBJ( dObj , spiId )),
                              _DRV_SPI_PRIMARY_PRESCALE_GET(config->priPrescale) );
    _DRV_SPI_OBJ(dObj, priPrescale) = _DRV_SPI_PRIMARY_PRESCALE_GET(config->priPrescale);

    /* Secondary Prescaler Selection */
    _DRV_SPI_SecondaryPrescale( _DRV_SPI_PERIPHERAL_ID_GET(_DRV_SPI_OBJ( dObj , spiId )),
                                _DRV_SPI_SECONDARY_PRESCALE_GET(config->secPrescale) );
    _DRV_SPI_OBJ(dObj, secPrescale) = _DRV_SPI_SECONDARY_PRESCALE_GET(config->secPrescale);

    /* SPI Port Setup */
    _DRV_SPI_PortSetup( _DRV_SPI_PERIPHERAL_ID_GET(_DRV_SPI_OBJ( dObj , spiId )), config->portsConfig );
    _DRV_SPI_OBJ(dObj, portsConfig) = config->portsConfig;

    /* Register the callback */
    _DRV_SPI_OBJ(dObj, callback) = config->callback;

     /* Restart the device */
    _DRV_SPI_Disable( _DRV_SPI_PERIPHERAL_ID_GET( _DRV_SPI_OBJ( dObj , spiId ) ) ) ;

} /* DRV_SPI_CommunicationSetup */


// *****************************************************************************
/* Function:
    void DRV_SPI_SlaveSelectSet ( DRV_HANDLE handle, bool slaveSel,
                                  PORT_MODULE_ID port, unsigned int pinNum )

  Summary:
    Sets the SPI Slave Select Signal

  Description:
    This function sets the SPI Slave Select Signal

  Precondition:
    The DRV_SPI_Initialize routine must have been called.

    DRV_SPI_Open must have been called to obtain a valid opened device handle.

    DRV_IO_INTENT_READ or DRV_IO_INTENT_READWRITE must have been specified in
    the DRV_SPI_Open call.

  Parameters:
    handle      - A valid open-instance handle, returned from the driver's
                   open routine
    slaveSel    - true drives the SS high, false drives it low
    port        - Identifies the Port Number through PORT_MODULE_ID
    pinNum      - Identifies the Port Pin position for Slave Select

  Returns:
    None
*/

void _DRV_SPI_MAKE_NAME( SlaveSelectSet )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_SPI_MC_ARG_COMMA( DRV_HANDLE handle )
    bool slaveSel,
    PORT_MODULE_ID port,
    unsigned int pinNum
)
{
    /* Multi client variables are removed from single client builds. */
    _DRV_SPI_MC( DRV_SPI_CLIENT_OBJ clientObj = (DRV_SPI_CLIENT_OBJ) 0 );

    /* Get the Client object from the handle passed */
    _DRV_SPI_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_SPI_MC_Test( clientObj < DRV_SPI_CLIENTS_NUMBER ), "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_SPI_DYN( dObj = _DRV_SPI_CLIENT_OBJ( clientObj, driverObject ) );


    
} /* DRV_SPI_SlaveSelectSet */


// *****************************************************************************
/* Function:
    SPI_BUFFER DRV_SPI_Read ( DRV_HANDLE handle )

  Summary:
    Reads a byte or word data from the SPI

  Description:
    This routine reads a byte or word data from the SPI.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    A byte or word Data received by the SPI driver.
*/

SPI_BUFFER _DRV_SPI_MAKE_NAME( Read )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_SPI_MC_ARG( DRV_HANDLE handle )
)
{
    /* Multi client variables are removed from single client builds. */
    _DRV_SPI_MC( DRV_SPI_CLIENT_OBJ clientObj = (DRV_SPI_CLIENT_OBJ) 0 );
    _DRV_SPI_DYN( DRV_SPI_OBJ dObj = (DRV_SPI_OBJ) 0 );
    SPI_BUFFER bData;

    /* Get the Client object from the handle passed */
    _DRV_SPI_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_SPI_MC_Test( clientObj < DRV_SPI_CLIENTS_NUMBER ), "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_SPI_DYN( dObj = _DRV_SPI_CLIENT_OBJ( clientObj, driverObject ) );

    /* Check if the receive buffer is EMPTY */
    if ( true == _DRV_SPI_OBJ( dObj , isBufferEmpty ) )
    {
        /* Update the Client Status */
        _DRV_SPI_CLIENT_OBJ( clientObj , status ) = DRV_SPI_CLIENT_STATUS_ERROR;
        /* Return the max value that can be held */
        return ( (SPI_BUFFER) 0xFFFFFFFF );
    }

    /* Get the data from the head */
    bData = *_DRV_SPI_OBJ(dObj , qHeadPtr);
    /* Update the head pointer */
    _DRV_SPI_OBJ(dObj , qHeadPtr)++;

    if(_DRV_SPI_OBJ(dObj , qHeadPtr) == (uint8_t *)_DRV_SPI_BYTEQ(_DRV_SPI_OBJ(dObj, objIndex))
                                          + sizeof(_DRV_SPI_BYTEQ(_DRV_SPI_OBJ(dObj, objIndex))))
    {
        _DRV_SPI_OBJ(dObj , qHeadPtr) = (uint8_t *)_DRV_SPI_BYTEQ(_DRV_SPI_OBJ(dObj, objIndex));
    }

    /* Check if the queue has reached tail end */
    if(_DRV_SPI_OBJ(dObj , qHeadPtr) == _DRV_SPI_OBJ(dObj , qTailPtr))
    {
        /* Update status saying the receive buffer is empty */
        _DRV_SPI_OBJ(dObj , isBufferEmpty) = true;
    }

    /* Update status saying receive buffer is not full */
    _DRV_SPI_OBJ(dObj , isBufferFull) = false;

    return bData;

} /* DRV_SPI_Read */


// *****************************************************************************
/* Function:
    void DRV_SPI_Write ( DRV_HANDLE handle, const SPI_BUFFER buffer )

  Summary:
    Writes a byte or word data to the SPI

  Description:
    This routine writes a byte or word data to the SPI.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

    buffer       - A byte or word data to be written to the SPI

  Returns:
    None.
*/

void _DRV_SPI_MAKE_NAME( Write )
( 
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_SPI_MC_ARG_COMMA( DRV_HANDLE handle )
    const SPI_BUFFER buffer
)
{
    /* Multi client variables are removed from single client builds. */
    _DRV_SPI_MC( DRV_SPI_CLIENT_OBJ clientObj = (DRV_SPI_CLIENT_OBJ) 0 );

    /* Get the Client object from the handle passed */
    _DRV_SPI_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_SPI_MC_Test( clientObj < DRV_SPI_CLIENTS_NUMBER ), "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_SPI_DYN( dObj = _DRV_SPI_CLIENT_OBJ( clientObj, driverObject ) );

    /* Check if the receive buffer is FULL */
    if( isBufferFull == _DRV_SPI_OBJ( dObj , bufferStatus ) )
    {
        /* Update the Client Status */
        _DRV_SPI_CLIENT_OBJ( clientObj , status ) = DRV_SPI_CLIENT_STATUS_ERROR;
        return;
    }

    /* Update the tail with the newest data received */
    *_DRV_SPI_OBJ(dObj , qTailPtr) = byte;
    /* Update the tail pointer */
    _DRV_SPI_OBJ(dObj , qTailPtr)++;

    if( _DRV_SPI_OBJ(dObj , qTailPtr) == (uint8_t *)_DRV_SPI_BYTEQ(_DRV_SPI_OBJ(dObj, objIndex))
                                           + sizeof(_DRV_SPI_BYTEQ(_DRV_SPI_OBJ(dObj, objIndex))))
    {
        _DRV_SPI_OBJ(dObj , qTailPtr) = (uint8_t *)_DRV_SPI_BYTEQ(_DRV_SPI_OBJ(dObj, objIndex));
    }

    /* Check if the queue has reached the head */
    if( _DRV_SPI_OBJ(dObj , qTailPtr) == _DRV_SPI_OBJ(dObj , qHeadPtr))
    {
        /* Update status saying the receive buffer is full */
        _DRV_SPI_OBJ(dObj , isBufferFull) = true;
    }

    /* Update status saying receive buffer is not empty */
    _DRV_SPI_OBJ(dObj , isBufferEmpty) = false;

} /* DRV_SPI_Write */


// *****************************************************************************
/* Function:
    unsigned int DRV_SPI_ReadBuffer ( DRV_HANDLE handle, SPI_BUFFER *buffer,
                                      const unsigned int bytes )

  Summary:
    Reads a buffered data from SPI

  Description:
    This routine reads a buffered data from the SPI.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

    buffer       - Buffer into which the data read from the SPI instance
                   will be placed.

    numbytes     - Total number of bytes that need to be read from the module
                   instance (must be equal to or less than the size of the
                   buffer)

  Returns:
    Number of bytes actually copied into the caller's buffer or -1 if there
    is an error (call DRV_SPI_ClientStatus to identify the error).
*/

unsigned int _DRV_SPI_MAKE_NAME( ReadBuffer )
( 
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_SPI_MC_ARG_COMMA( DRV_HANDLE handle )
    SPI_BUFFER *buffer,
    const unsigned int bytes
)
{
    /* Multi client variables are removed from single client builds. */
    _DRV_SPI_MC( DRV_SPI_CLIENT_OBJ clientObj = (DRV_SPI_CLIENT_OBJ) 0 );
     unsigned int bytesRead = 0 ;

    /* Get the Client object from the handle passed */
    _DRV_SPI_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_SPI_MC_Test( clientObj < DRV_SPI_CLIENTS_NUMBER ), "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_SPI_DYN( dObj = _DRV_SPI_CLIENT_OBJ( clientObj, driverObject ) );

    /* Block till the requested bytes are read */
    while ( bytesRead < ( bytes - 1 ) )
    {
        /* Check if the buffer is not empty */
        if( false == _DRV_SPI_OBJ( dObj , isBufferEmpty ) )
        {
            /* Update the data read from the buffer */
            buffer[bytesRead++] = _DRV_SPI_MAKE_NAME( Read ) ( _DRV_SPI_MC_PARAM( handle )) ;
        }
        else
        {
            /* Receive buffer full, return the number of bytes till now read */
            return bytesRead;
        }
    }

    /* Return the number of bytes read */
    return bytesRead ;

} /* DRV_SPI_ReadBuffer */


// *****************************************************************************
/* Function:
    unsigned int DRV_SPI_WriteBuffer ( DRV_HANDLE handle, const SPI_BUFFER *buffer,
                                       const unsigned int bytes )

  Summary:
    Writes a buffered data to the SPI

  Description:
    This routine writes a buffered data to the SPI.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

    buffer       - Buffer containing the data write to the SPI instance

    numbytes     - Total number of bytes that to write to the SPI instance
                   (must be equal to or less than the size of the buffer)

  Returns:
    Number of bytes actually written to the SPI or -1 if there is an error
    (call DRV_SPI_ClientStatus to identify the error)
*/

unsigned int _DRV_SPI_MAKE_NAME( WriteBuffer )
( 
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_SPI_MC_ARG_COMMA( DRV_HANDLE handle )
    const SPI_BUFFER *buffer,
    const unsigned int bytes
)
{
    /* Multi client variables are removed from single client builds. */
    _DRV_SPI_MC( DRV_SPI_CLIENT_OBJ clientObj = (DRV_SPI_CLIENT_OBJ) 0 );
    unsigned int bytesWritten = 0;

    /* Get the Client object from the handle passed */
    _DRV_SPI_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_SPI_MC_Test( clientObj < DRV_SPI_CLIENTS_NUMBER ), "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_SPI_DYN( dObj = _DRV_SPI_CLIENT_OBJ( clientObj, driverObject ) );

    /* Block till the requested bytes are written */
    while ( bytesWritten < ( bytes - 1 ))
    {
        /* Check if the buffer is not full */
        if( false == _DRV_SPI_OBJ( dObj , isBufferFull ) )
        {
            /* Update the data into the buffer */
            _DRV_SPI_MAKE_NAME( Write ) ( _DRV_SPI_MC_PARAM_COMMA( handle )
                                          buffer[bytesWritten++] );
        }
        else
        {
            /* Receive buffer full, return the number of bytes till now written */
            return bytesWritten;
        }
    }

    /* Return the number of bytes written */
    return bytesWritten;

} /* DRV_SPI_WriteBuffer */


// *****************************************************************************
/* Function:
    DRV_SPI_TRANSFER_STATUS DRV_SPI_TransferStatus ( DRV_HANDLE handle )

  Summary:
    Returns the transmitter and receiver transfer status

  Description:
    This returns the transmitter and receiver transfer status.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    A DRV_SPI_TRANSFER_STATUS value describing the current status of the
    transfer.
*/

DRV_SPI_TRANSFER_STATUS _DRV_SPI_MAKE_NAME( TransferStatus )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_SPI_MC_ARG( DRV_HANDLE handle )
)
{
    /* Multi client variables are removed from single client builds. */
    _DRV_SPI_MC( DRV_SPI_CLIENT_OBJ clientObj = (DRV_SPI_CLIENT_OBJ) 0 );
    _DRV_SPI_DYN( DRV_SPI_OBJ dObj = (DRV_SPI_OBJ) 0 );
    DRV_SPI_TRANSFER_STATUS status = 0;

    /* Get the Client object from the handle passed */
    _DRV_SPI_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_SPI_MC_Test( clientObj < DRV_SPI_CLIENTS_NUMBER ), "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_SPI_DYN( dObj = _DRV_SPI_CLIENT_OBJ( clientObj, driverObject ) );

    /* Is buffer EMPTY ? */
    if( true == _DRV_SPI_OBJ( dObj , isBufferEmpty ) )
    {
        /* Update status saying the buffer is empty */
        status |= DRV_SPI_TRANSFER_STATUS_EMPTY;
    }
    /* Is buffer FULL ? */
    else if( true == _DRV_SPI_OBJ( dObj , isBufferFull ) )
    {
        /* Update status saying the buffer is full */
        status |= DRV_SPI_TRANSFER_STATUS_FULL;
    }
    else
    {
        /* Indicate that the data is present in the buffer */
        status |= DRV_SPI_TRANSFER_STATUS_DATA_PRESENT;
    }

    /* return the status information */
    return status;

} /* DRV_SPI_TransferStatus */


// *****************************************************************************
/* Function:
    DRV_SPI_TRANSFER_STATUS DRV_SPI_BufferTransferStatus ( DRV_HANDLE handle )

  Summary:
    Returns the transmitter and receiver transfer status

  Description:
    This returns the transmitter and receiver transfer status.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    A DRV_SPI_TRANSFER_STATUS value describing the current status of the
    transfer.
*/

DRV_SPI_TRANSFER_STATUS _DRV_SPI_MAKE_NAME( BufferTransferStatus )
( 
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_SPI_MC_ARG( DRV_HANDLE handle )
)
{
    /* Multi client variables are removed from single client builds. */
    _DRV_SPI_MC( DRV_SPI_CLIENT_OBJ clientObj = (DRV_SPI_CLIENT_OBJ) 0 );

    /* Get the Client object from the handle passed */
    _DRV_SPI_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_SPI_MC_Test( clientObj < DRV_SPI_CLIENTS_NUMBER ), "Invalid Client Object" ) ;


} /* DRV_SPI_BufferTransferStatus */


//******************************************************************************
/* Function:
    unsigned int DRV_SPI_VersionGet( const SYS_MODULE_INDEX drvIndex )

  Summary:
    Gets SPI driver version in numerical format.

  Description:
    This routine gets the SPI driver version. The version is encoded as
    major * 10000 + minor * 100 + patch. The stringized version can be obtained
    using DRV_SPI_VersionStrGet()

  Parameters:
    None.

  Returns:
    Current driver version in numerical format.
*/

unsigned int _DRV_SPI_MAKE_NAME( VersionGet )( const SYS_MODULE_INDEX drvIndex )
{
    return( ( _DRV_SPI_VERSION_MAJOR * 10000 ) +
            ( _DRV_SPI_VERSION_MINOR * 100 ) +
            ( _DRV_SPI_VERSION_PATCH ) );

} /* DRV_SPI_VersionGet */


// *****************************************************************************
/* Function:
    char * DRV_SPI_VersionStrGet( const SYS_MODULE_INDEX drvIndex )

  Summary:
    Gets SPI driver version in string format.

  Description:
    This routine gets the SPI driver version. The version is returned as
    major.minor.path[type], where type is optional. The numertical version can
    be obtained using DRV_SPI_VersionGet()

  Parameters:
    None.

  Returns:
    Current SPI driver version in the string format.

  Remarks:
    None.
*/

char * _DRV_SPI_MAKE_NAME( VersionStrGet )( const SYS_MODULE_INDEX drvIndex )
{
    return _DRV_SPI_VERSION_STR;

} /* DRV_SPI_VersionStrGet */


/*******************************************************************************
End of File
*/



