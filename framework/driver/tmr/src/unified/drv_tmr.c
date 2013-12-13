/*******************************************************************************
  TMR Device Driver Definition

  Company:
    Microchip Technology Incorported

  FileName:
    drv_tmr.c

  Summary:
    TMR Device Driver Implementation

  Description:
    The TMR device driver provides a simple interface to manage the TMR modules
    on Microchip microcontrollers.  This file Implements the core interface 
    routines for the TMR driver.
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

#include "tmr/src/drv_tmr_local.h"


// *****************************************************************************
// *****************************************************************************
// Section: File Scope Functions
// *****************************************************************************
// *****************************************************************************

/******************************************************************************
  Function:
    static void _DRV_TMR_SyncModeControl ( TMR_MODULE_ID plibId,
                                           DRV_TMR_SYNC_MODE newMode )

  Summary:
    Sets the new sync mode

  Description:
    This internal TMR driver routine sets the new sync mode in the hardwware.

  Remarks:
    None
*/

static void _DRV_TMR_SyncModeControl
( 
    /* Function Parameters: (Dynamic arguments are removed from static builds.) */
    _DRV_TMR_DYN_ARG_COMMA( const TMR_MODULE_ID plibId )
    DRV_TMR_SYNC_MODE newMode 
)
{
    if ( DRV_TMR_SYNC_MODE_SYNCHRONOUS_INTERNAL == _DRV_TMR_SYNC_MODE_GET(newMode) )
    {
        /* Clock Source Internal */
    }
    else if ( DRV_TMR_SYNC_MODE_SYNCHRONOUS_INTERNAL_GATED == _DRV_TMR_SYNC_MODE_GET(newMode) )
    {
        /* Clock Source Internal */

        /* Gated Operation Control */
        if( PLIB_TMR_ExistsGatedTimeAccumulation( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) ) )
        {
            PLIB_TMR_GateEnable(_DRV_TMR_PERIPHERAL_ID_GET( plibId ));
        }
    }
    else if ( DRV_TMR_SYNC_MODE_SYNCHRONOUS_EXTERNAL_WITHOUT_CLKSYNC == _DRV_TMR_SYNC_MODE_GET(newMode) )
    {
        /* Clock Source External */

        /* External Clock Syncronization */
        _DRV_TMR_ExternalClockSyncDisable( _DRV_TMR_PERIPHERAL_ID_GET(plibId) );
    }
    else if ( DRV_TMR_SYNC_MODE_SYNCHRONOUS_EXTERNAL_WITH_CLKSYNC == _DRV_TMR_SYNC_MODE_GET(newMode) )
    {
        /* Clock Source External */

        /* External Clock Syncronization */
        _DRV_TMR_ExternalClockSyncEnable( _DRV_TMR_PERIPHERAL_ID_GET(plibId) );
    }
    else if ( DRV_TMR_SYNC_MODE_ASYNCHRONOUS_EXTERNAL_WITHOUT_CLKSYNC == _DRV_TMR_SYNC_MODE_GET(newMode) )
    {
        /* External Clock Syncronization */
        _DRV_TMR_SyncModeAsyncExtWithoutClockSync( _DRV_TMR_PERIPHERAL_ID_GET(plibId) );
    }
    else /* ( DRV_TMR_SYNC_MODE_ASYNCHRONOUS_EXTERNAL_WITH_CLKSYNC == _DRV_TMR_SYNC_MODE_GET(newMode) ) */
    {
        /* External Clock Syncronization */
        _DRV_TMR_SyncModeAsyncExtWithClockSync( _DRV_TMR_PERIPHERAL_ID_GET(plibId) );
    }

} /* _DRV_TMR_SyncModeControl */


/******************************************************************************
  Function:
    static void _DRV_TMR_SetupHardware ( TMR_MODULE_ID   plibId,
                                         DRV_TMR_OBJ     dObj,
                                         DRV_TMR_INIT   *tmrInit )

  Summary:
    Sets up the hardware from the initialzation structure

  Description:
    This routine sets up the hardware from the initialzation structure.
 
  Remarks:
    Called 
*/

static void _DRV_TMR_SetupHardware
( 
    /* Function Parameters: (Dynamic arguments are removed from static builds.) */
    _DRV_TMR_DYN_ARG_COMMA( const TMR_MODULE_ID plibId )
    _DRV_TMR_DYN_ARG_COMMA( DRV_TMR_OBJ dObj )
    DRV_TMR_INIT * tmrInit
)
{
    /* Initialize the Interrupt Source */
    _DRV_TMR_STATIC_INT_SRC( _DRV_TMR_OBJ(dObj, interruptSource) = _DRV_TMR_GET_INT_SRC(tmrInit->interruptSource) );

    /* Power state initialization */
    if( PLIB_TMR_ExistsStopInIdleControl( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) ) )
    {
        if( DRV_TMR_POWER_STATE == SYS_MODULE_POWER_IDLE_STOP )
        {
            PLIB_TMR_StopInIdleEnable( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) );
        }
        else if( ( DRV_TMR_POWER_STATE == SYS_MODULE_POWER_IDLE_RUN ) ||
                 ( DRV_TMR_POWER_STATE == SYS_MODULE_POWER_RUN_FULL ) )
        {
            PLIB_TMR_StopInIdleDisable( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) );
        }
        else
        {
            if( _DRV_TMR_POWER_STATE_GET( tmrInit->moduleInit.sys.powerState ) == SYS_MODULE_POWER_IDLE_STOP )
            {
                PLIB_TMR_StopInIdleEnable( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) );
            }
        }
    }

    /* Enable the configured 8bit or 16bit or 32bit timer mode. */
    if( PLIB_TMR_ExistsMode8Bit( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) ) && ( DRV_TMR_COUNT_WIDTH == _DRV_TMR_8BIT ) )
    {
        PLIB_TMR_Mode8BitEnable( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) );
    }
    else if( PLIB_TMR_ExistsMode16Bit( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) ) && ( DRV_TMR_COUNT_WIDTH == _DRV_TMR_16BIT ) )
    {
        PLIB_TMR_Mode16BitEnable( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) );
    }
    else if( PLIB_TMR_ExistsMode32Bit( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) ) && ( DRV_TMR_COUNT_WIDTH == _DRV_TMR_32BIT ) )
    {
        PLIB_TMR_Mode32BitEnable( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) );
    }

    /* Timer Mode Configuration */
    /* Clock Source Selection - Internal or External */
    if( PLIB_TMR_ExistsClockSource( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) ) )
    {
        PLIB_TMR_ClockSourceSelect( _DRV_TMR_PERIPHERAL_ID_GET( plibId ), _DRV_TMR_CLOCK_SOURCE_GET(tmrInit->clockSource) );
    }

    _DRV_TMR_SyncModeControl( _DRV_TMR_DYN_PARAM_COMMA(_DRV_TMR_PERIPHERAL_ID_GET(plibId))
                              _DRV_TMR_SYNC_MODE_GET(tmrInit->syncMode) );

    /* Update the operating mode of the TMR initialized */
    _DRV_TMR_OBJ( dObj, syncMode ) = _DRV_TMR_SYNC_MODE_GET(tmrInit->syncMode);

    /* Prescaler Assignment Control */
    if( PLIB_TMR_ExistsPrescalerAssignment( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) ) )
    {
        if( DRV_TMR_PRESCALER_ENABLE == false )
        {
            PLIB_TMR_PrescalerDisable( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) );
        }
        else if( DRV_TMR_PRESCALER_ENABLE == true )
        {
            PLIB_TMR_PrescalerEnable( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) );
        }
    }

    /* Prescaler selection */
    if( PLIB_TMR_ExistsPrescale( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) ) )
    {
        PLIB_TMR_PrescaleSelect( _DRV_TMR_PERIPHERAL_ID_GET( plibId ), _DRV_TMR_PRESCALE_GET(tmrInit->prescale) );
    }
    _DRV_TMR_OBJ( dObj, prescale ) = _DRV_TMR_PRESCALE_GET(tmrInit->prescale);

    /* Output Post scaler selection */
    if( PLIB_TMR_ExistsPostscale( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) ) )
    {
        PLIB_TMR_PostscaleSelect( _DRV_TMR_PERIPHERAL_ID_GET( plibId ), _DRV_TMR_POSTSCALE_GET(tmrInit->postscale) );
    }

    /* Source Edge Selection */
    if( PLIB_TMR_ExistsSourceEdgeControl( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) ) )
    {
        PLIB_TMR_SourceEdgeSelect( _DRV_TMR_PERIPHERAL_ID_GET( plibId ), _DRV_TMR_SOURCE_EDGE_GET(tmrInit->sourceEdge) );
    }

    /* Asynchronous Write Control */
    if( PLIB_TMR_ExistsAsynchronousCounterWrite( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) ) )
    {
        if( DRV_TMR_ASYNC_WRITE_ENABLE == true )
        {
            PLIB_TMR_AsynchronousCounterWriteEnable( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) );
        }
        else if( DRV_TMR_ASYNC_WRITE_ENABLE == false )
        {
            PLIB_TMR_AsynchronousCounterWriteDisable( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) );
        }
    }

    /* Update the TMR data value */
    _DRV_TMR_PeriodSet( _DRV_TMR_PERIPHERAL_ID_GET(plibId), _DRV_TMR_VALUE_GET(tmrInit->timerPeriod) );
    
    _DRV_TMR_OBJ( dObj, timerPeriod ) = _DRV_TMR_VALUE_GET(tmrInit->timerPeriod);

} /* _DRV_TMR_SetupHardware */


// *****************************************************************************
// *****************************************************************************
// Section: Driver Interface Function Definitions
// *****************************************************************************
// *****************************************************************************

/******************************************************************************
  Function:
    SYS_MODULE_OBJ DRV_TMR_Initialize( const SYS_MODULE_INDEX index,
                                       const SYS_MODULE_INIT * const init )

  Summary:
    Initializes hardware and data for the given instance of the TMR module

  Description:
    This routine initializes hardware for the instance of the TMR module,
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

_DRV_TMR_DYN_RETURN_TYPE(SYS_MODULE_OBJ) _DRV_TMR_MAKE_NAME(Initialize)
(
    /* Function Parameters: (Dynamic arguments are removed from static builds.) */
    _DRV_TMR_DYN_ARG_COMMA( const SYS_MODULE_INDEX drvIndex )
    const SYS_MODULE_INIT * const init 
)
{
    _DRV_TMR_DYN( DRV_TMR_OBJ dObj = (DRV_TMR_OBJ) 0 );
    DRV_TMR_INIT * tmrInit = NULL;

    /* Validate the driver index */
    if ( _DRV_TMR_INDEX_GET(drvIndex) >= DRV_TMR_INDEX_COUNT )
    {
        _DRV_TMR_DYN_RETURN( SYS_MODULE_OBJ_INVALID );
    }

    /* Assign to the local pointer the init data passed */
    tmrInit = ( DRV_TMR_INIT * ) init;

    /* Allocate the driver object and set the operation flag to be in use */
    _DRV_TMR_DYN( dObj = _DRV_TMR_OBJ_ALLOCATE(drvIndex) );
    _DRV_TMR_OBJ( dObj, inUse ) = true;

    /* Check that the object is valid */
    SYS_ASSERT( _DRV_TMR_ObjectIsValid(dObj), "Hardware Object is invalid" );

    /* Update the TMR Module Index */
    _DRV_TMR_DYN(_DRV_TMR_OBJ( dObj , tmrId ) = _DRV_TMR_PERIPHERAL_ID_GET( tmrInit->tmrId ));

    /* Setup the Hardware */
    _DRV_TMR_SetupHardware( _DRV_TMR_DYN_PARAM_COMMA( _DRV_TMR_PERIPHERAL_ID_GET(tmrInit->tmrId) )
                            _DRV_TMR_DYN_PARAM_COMMA( dObj )
                            tmrInit );

    /* Interrupt flag cleared on the safer side */
    _DRV_TMR_InterruptSourceClear( _DRV_TMR_GET_INT_SRC( _DRV_TMR_OBJ(dObj, interruptSource) ) );

    /* Enable the interrupt source in case of interrupt mode */
    _DRV_TMR_InterruptSourceEnable( _DRV_TMR_GET_INT_SRC( _DRV_TMR_OBJ(dObj, interruptSource) ) );

    /* Set the current driver state */
    _DRV_TMR_OBJ( dObj , status ) = SYS_STATUS_READY;

    /* Return the driver handle */
    _DRV_TMR_DYN_RETURN( (SYS_MODULE_OBJ)dObj );

} /* DRV_TMR_Initialize */


/******************************************************************************
  Function:
    void DRV_TMR_Reinitialize( SYS_MODULE_OBJ object,
                               const SYS_MODULE_INIT* const init )

  Summary:
    Reinitializes and refreshes the hardware for the instance of the TMR
    module

  Description:
    This routine reinitializes and refreshes the hardware for the instance
    of the TMR module using the hardware initialization given data.
    It does not clear or reinitialize internal data structures

  Parameters:
    object          - Identifies the Driver Object returned by the Initialize
                      interface
    init            - Pointer to the data structure containing any data
                      necessary to initialize the hardware.

  Returns:
    None
*/

void _DRV_TMR_MAKE_NAME( Reinitialize )
(
    /* Function Parameters: (Dynamic arguments are removed from static builds.) */
    _DRV_TMR_DYN_ARG_COMMA( SYS_MODULE_OBJ object )
    const SYS_MODULE_INIT * const init 
)
{
    _DRV_TMR_DYN( DRV_TMR_OBJ dObj = (DRV_TMR_OBJ) object );
    DRV_TMR_INIT * tmrInit = NULL;

    /* Check for the valid driver object passed */
    SYS_ASSERT( _DRV_TMR_ObjectIsValid(dObj), "Driver Object is invalid" );

    /* Valid init structure is present */
    tmrInit = ( DRV_TMR_INIT * ) init;

    /* Stop the TMR Module */
    if( PLIB_TMR_ExistsEnableControl( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( dObj , tmrId ) ) ) )
    {
        PLIB_TMR_Stop( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( dObj , tmrId ) ) );
    }
	
    /* Set the curent driver state */
    _DRV_TMR_OBJ( dObj , status ) = SYS_STATUS_UNINITIALIZED ;
	
    /* Setup the Hardware */
    _DRV_TMR_SetupHardware( _DRV_TMR_DYN_PARAM_COMMA( _DRV_TMR_PERIPHERAL_ID_GET(tmrInit->tmrId) )
                            _DRV_TMR_DYN_PARAM_COMMA( dObj )
                            tmrInit );
    /* Re Start the TMR Module */
    if( PLIB_TMR_ExistsEnableControl( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( dObj , tmrId ) ) ) )
    {
        PLIB_TMR_Start( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( dObj , tmrId ) ) );
    }

    /* Set the curent driver state */
    _DRV_TMR_OBJ( dObj , status ) = SYS_STATUS_READY;

} /* DRV_TMR_Reinitialize */


/******************************************************************************
  Function:
    void DRV_TMR_Deinitialize( SYS_MODULE_OBJ object )

  Summary:
    Deinitializes the specific module instance of the TMR module

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

void _DRV_TMR_MAKE_NAME( Deinitialize )
(
    /* Function Parameter: (Dynamic arguments are removed from static builds.) */
    _DRV_TMR_DYN_ARG( SYS_MODULE_OBJ object )
)
{
    _DRV_TMR_DYN( DRV_TMR_OBJ dObj = (DRV_TMR_OBJ) object );

    /* Check for the valid driver object passed */
    SYS_ASSERT( _DRV_TMR_ObjectIsValid(dObj), "Driver Object is invalid" );

    /* Interrupt De-Registration */
    _DRV_TMR_InterruptSourceDisable( _DRV_TMR_GET_INT_SRC( _DRV_TMR_OBJ(dObj, interruptSource) ) );

    /* Set the Device Status */
    _DRV_TMR_OBJ( dObj , status ) = SYS_MODULE_DEINITIALIZED;

    /* Remove the driver usage */
    _DRV_TMR_OBJ( dObj , inUse ) = false;

} /* DRV_TMR_Deinitialize */


/******************************************************************************
  Function:
    SYS_STATUS DRV_TMR_Status( SYS_MODULE_OBJ object )

  Summary:
    Provides the current status of the hardware instance of the TMR module

  Description:
    This routine Provides the current status of the hardware instance of the
    TMR module.

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

SYS_STATUS _DRV_TMR_MAKE_NAME( Status )
(
    /* Function Parameter: (Dynamic arguments are removed from static builds.) */
    _DRV_TMR_DYN_ARG( SYS_MODULE_OBJ object )
)
{
    _DRV_TMR_DYN( DRV_TMR_OBJ dObj = (DRV_TMR_OBJ) object );

    /* Check for the valid driver object passed */
    SYS_ASSERT( _DRV_TMR_ObjectIsValid(dObj), "Driver Object is invalid" );

    /* Return the status associated with the driver handle */
    return (_DRV_TMR_OBJ( dObj , status ) );

} /* DRV_TMR_Status */


/******************************************************************************
  Function:
    DRV_HANDLE DRV_TMR_Open( const SYS_MODULE_INDEX index,
                             const DRV_IO_INTENT intent )

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

_DRV_TMR_MC_RETURN_TYPE( DRV_HANDLE ) _DRV_TMR_MAKE_NAME( Open )
(
    /* Function Parameters: (Dynamic arguments are removed from static builds.) */
    _DRV_TMR_DYN_ARG_COMMA( const SYS_MODULE_INDEX drvIndex )
    const DRV_IO_INTENT ioIntent
)
{
    /* Multi client variables are removed from single client builds. */
    _DRV_TMR_MC( DRV_TMR_CLIENT_OBJ clientObj = (DRV_TMR_CLIENT_OBJ) 0 );

    /* Validate the driver index */
    if ( ( _DRV_TMR_INDEX_GET(drvIndex) >= DRV_TMR_INDEX_COUNT ) ||
         ( ioIntent != DRV_IO_INTENT_EXCLUSIVE ) )
    {
        _DRV_TMR_MC_RETURN( DRV_HANDLE_INVALID );
    }

    /* Setup client operations */

    /* To Do: OSAL - Lock Mutex */

    /* Allocate the client object and set the flag as in use */
    _DRV_TMR_MC(clientObj = _DRV_TMR_ClientObjectAllocate(_DRV_TMR_INDEX_GET(drvIndex))) ;
    _DRV_TMR_CLIENT_OBJ( clientObj , inUse ) = true;
    _DRV_TMR_CLIENT_OBJ( clientObj , driverObject ) = _DRV_TMR_INDEX_GET( drvIndex );

    /* Check for the client object */
    SYS_ASSERT( _DRV_TMR_MC_Test( clientObj < DRV_TMR_INSTANCES_NUMBER), "Invalid Client Object" );

    /* To Do: OSAL - Unlock Mutex */

    /* Update the Client Status */
    _DRV_TMR_CLIENT_OBJ( clientObj , status ) = DRV_TMR_CLIENT_STATUS_READY;

    /* Return the client object */
    _DRV_TMR_MC_RETURN( ( DRV_HANDLE ) clientObj );

} /* DRV_TMR_Open */


/******************************************************************************
  Function:
    void DRV_TMR_Close( DRV_Handle handle )

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

void _DRV_TMR_MAKE_NAME( Close )
( 
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_TMR_MC_ARG( DRV_HANDLE handle )
)
{
    /* Multi client variables are removed from single client builds. */
    _DRV_TMR_MC( DRV_TMR_CLIENT_OBJ clientObj );

    /* Get the Client object from the handle passed */
    _DRV_TMR_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_TMR_MC_Test( clientObj < DRV_TMR_INSTANCES_NUMBER), "Invalid Client Object" ) ;

    /* To Do: OSAL - lock Mutex */

    /* Free the Client Instance */
    _DRV_TMR_CLIENT_OBJ( clientObj , inUse ) = false ;

    /* To Do: OSAL - unlock Mutex */

    /* Update the Client Status */
    _DRV_TMR_CLIENT_OBJ( clientObj , status ) = DRV_TMR_CLIENT_STATUS_INVALID;

} /* DRV_TMR_Close */


/******************************************************************************
  Function:
    DRV_TMR_CLIENT_STATUS DRV_TMR_ClientStatus(DRV_HANDLE handle)

  Summary:
    Gets the status of the module instance associated with the handle

  Description:
    This routine gets the status of the module instance associated with the
    handle.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    DRV_TMR_CLIENT_STATUS value describing the current status of the driver
*/

DRV_TMR_CLIENT_STATUS _DRV_TMR_MAKE_NAME( ClientStatus )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_TMR_MC_ARG( DRV_HANDLE handle )
)
{
    /* Multi client variables are removed from single client builds. */
    _DRV_TMR_MC( DRV_TMR_CLIENT_OBJ clientObj = (DRV_TMR_CLIENT_OBJ) 0 );

    /* Get the Client object from the handle passed */
    _DRV_TMR_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_TMR_MC_Test( clientObj < DRV_TMR_INSTANCES_NUMBER), "Invalid Client Object" ) ;

    /* Return the client status associated with the handle passed */
    return (_DRV_TMR_CLIENT_OBJ( clientObj , status ) );

} /* DRV_TMR_ClientStatus */


/******************************************************************************
  Function:
   void DRV_TMR_PeriodSet ( DRV_HANDLE handle, TMR_COUNT countValue )

  Summary:
    Updates the timer value

  Description:
    This routine updates the timer value

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine
    countValue   - Counter value

  Returns:
    None
*/

void _DRV_TMR_MAKE_NAME( PeriodSet )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_TMR_MC_ARG_COMMA( DRV_HANDLE handle )
    TMR_COUNT countValue
)
{
    /* Multi client variables are removed from single client builds. */
    _DRV_TMR_MC( DRV_TMR_CLIENT_OBJ clientObj = (DRV_TMR_CLIENT_OBJ) 0 );
    _DRV_TMR_DYN( DRV_TMR_OBJ dObj = (DRV_TMR_OBJ) 0 );

    /* Get the Client object from the handle passed */
    _DRV_TMR_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_TMR_MC_Test( clientObj < DRV_TMR_INSTANCES_NUMBER), "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_TMR_MULTI_CLIENT_DOBJ( clientObj , dObj );

    /* Update the counter values */
    _DRV_TMR_PeriodSet( _DRV_TMR_OBJ( dObj , tmrId ) , countValue );

    // To Do: OSAL Mutex Lock

    /* Client update with the new count value */
    _DRV_TMR_OBJ( dObj , timerPeriod ) = countValue;

    // To Do: OSAL Mutex Unlock

} /* DRV_TMR_PeriodSet */


/******************************************************************************
  Function:
   TMR_COUNT DRV_TMR_PeriodGet ( DRV_HANDLE handle )

  Summary:
    Provides the timer period value

  Description:
    This routine provides the timer period value

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    TMR_COUNT type timer period value
*/

TMR_COUNT _DRV_TMR_MAKE_NAME( PeriodGet )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_TMR_MC_ARG( DRV_HANDLE handle )
)
{
    /* Multi client variables are removed from single client builds. */
    _DRV_TMR_MC( DRV_TMR_CLIENT_OBJ clientObj = (DRV_TMR_CLIENT_OBJ) 0 );
    _DRV_TMR_DYN( DRV_TMR_OBJ dObj = (DRV_TMR_OBJ) 0 );
    TMR_COUNT periodVal = (TMR_COUNT)0xFFFFFFFF;

    /* Get the Client object from the handle passed */
    _DRV_TMR_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_TMR_MC_Test( clientObj < DRV_TMR_INSTANCES_NUMBER), "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_TMR_MULTI_CLIENT_DOBJ( clientObj , dObj );

    // To Do: OSAL Mutex Lock

    /* get the timer period value and return it */
    periodVal = ( ( TMR_COUNT ) _DRV_TMR_PeriodGet( _DRV_TMR_OBJ( dObj , tmrId ) ) );

    // To Do: OSAL Mutex Unlock

    return (periodVal );

} /* DRV_TMR_PeriodGet */


/******************************************************************************
  Function:
   void DRV_TMR_CounterSet ( DRV_HANDLE handle, TMR_COUNT countValue )

  Summary:
    Updates the timer value

  Description:
    This routine updates the timer value

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine
    countValue   - Counter value

  Returns:
    None
*/

void _DRV_TMR_MAKE_NAME( CounterSet )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_TMR_MC_ARG_COMMA( DRV_HANDLE handle )
    TMR_COUNT countValue
)
{
    /* Multi client variables are removed from single client builds. */
    _DRV_TMR_MC( DRV_TMR_CLIENT_OBJ clientObj = (DRV_TMR_CLIENT_OBJ) 0 );
    _DRV_TMR_DYN( DRV_TMR_OBJ dObj = (DRV_TMR_OBJ) 0 );

    /* Get the Client object from the handle passed */
    _DRV_TMR_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_TMR_MC_Test( clientObj < DRV_TMR_INSTANCES_NUMBER), "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_TMR_MULTI_CLIENT_DOBJ( clientObj , dObj );

    /* Update the counter values */
    _DRV_TMR_CounterSet( _DRV_TMR_OBJ( dObj , tmrId ) , countValue );

} /* DRV_TMR_CounterSet */


/******************************************************************************
  Function:
   TMR_COUNT DRV_TMR_CounterGet ( DRV_HANDLE handle )

  Summary:
    Provides the current counter value

  Description:
    This routine provides the current counter value

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    TMR_COUNT type current counter value
*/

TMR_COUNT _DRV_TMR_MAKE_NAME( CounterGet )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_TMR_MC_ARG( DRV_HANDLE handle )
)
{
    /* Multi client variables are removed from single client builds. */
    _DRV_TMR_MC( DRV_TMR_CLIENT_OBJ clientObj = (DRV_TMR_CLIENT_OBJ) 0 );
    _DRV_TMR_DYN( DRV_TMR_OBJ dObj = (DRV_TMR_OBJ) 0 );
    TMR_COUNT countVal = (TMR_COUNT)0xFFFFFFFF;

    /* Get the Client object from the handle passed */
    _DRV_TMR_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_TMR_MC_Test( clientObj < DRV_TMR_INSTANCES_NUMBER), "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_TMR_MULTI_CLIENT_DOBJ( clientObj , dObj );

    /* get the current counter value and return it */
    countVal = ( ( TMR_COUNT ) _DRV_TMR_CounterGet( _DRV_TMR_OBJ( dObj , tmrId ) ) );

    return (countVal );

} /* DRV_TMR_CounterGet */


/******************************************************************************
  Function:
   void DRV_TMR_SyncModeSet ( DRV_HANDLE handle,
                              DRV_TMR_SYNC_MODE newMode )

  Summary:
    Changes the timer Sync mode

  Description:
    This routine changes the timer Sync mode

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine
    newMode      - Possible values from the enumeration DRV_TMR_SYNC_MODE

  Returns:
    None
*/

void _DRV_TMR_MAKE_NAME( SyncModeSet )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_TMR_MC_ARG_COMMA( DRV_HANDLE handle )
    DRV_TMR_SYNC_MODE newMode
)
{
    /* Multi client variables are removed from single client builds. */
    _DRV_TMR_MC( DRV_TMR_CLIENT_OBJ clientObj = (DRV_TMR_CLIENT_OBJ) 0 );
    _DRV_TMR_DYN( DRV_TMR_OBJ dObj = (DRV_TMR_OBJ) 0 );

    /* Get the Client object from the handle passed */
    _DRV_TMR_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_TMR_MC_Test( clientObj < DRV_TMR_INSTANCES_NUMBER), "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_TMR_MULTI_CLIENT_DOBJ( clientObj , dObj );

    /* if the new mode requested matches the existing one, simply return */
    if ( newMode == _DRV_TMR_OBJ( dObj , syncMode ) )
        return;

    /* Timer Mode Re Configuration */

    /* Clock Source Selection - Internal or External */
    if ( ( DRV_TMR_SYNC_MODE_SYNCHRONOUS_INTERNAL == newMode ) ||
         ( DRV_TMR_SYNC_MODE_SYNCHRONOUS_INTERNAL_GATED == newMode ) )
    {
        if( PLIB_TMR_ExistsClockSource( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( dObj , tmrId ) ) ) )
        {
            PLIB_TMR_ClockSourceSelect( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( dObj , tmrId ) ), TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK );
        }
    }
    else /* External Clock Input */
    {
        if( PLIB_TMR_ExistsClockSource( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( dObj , tmrId ) ) ) )
        {
            PLIB_TMR_ClockSourceSelect( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( dObj , tmrId ) ), TMR_CLOCK_SOURCE_EXTERNAL_INPUT_PIN );
        }
    }

    /* Update the sync mode */
    _DRV_TMR_SyncModeControl(  _DRV_TMR_DYN_PARAM_COMMA( _DRV_TMR_OBJ( dObj , tmrId ) )
                               newMode );

    /* Update the sync mode of the TMR initialized */
    _DRV_TMR_OBJ( dObj , syncMode ) = newMode;

} /* DRV_TMR_SyncModeSet */


/******************************************************************************
  Function:
   DRV_TMR_SYNC_MODE DRV_TMR_SyncModeGet ( DRV_HANDLE handle )

  Summary:
    Provides the timer Sync mode

  Description:
    This routine provides the timer Sync mode

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    mode         - Possible values from the enumeration DRV_TMR_SYNC_MODE
*/

DRV_TMR_SYNC_MODE _DRV_TMR_MAKE_NAME( SyncModeGet )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_TMR_MC_ARG( DRV_HANDLE handle )
)
{
    /* Multi client variables are removed from single client builds. */
    _DRV_TMR_MC( DRV_TMR_CLIENT_OBJ clientObj = (DRV_TMR_CLIENT_OBJ) 0 );
    _DRV_TMR_DYN( DRV_TMR_OBJ dObj = (DRV_TMR_OBJ) 0 );

    /* Get the Client object from the handle passed */
    _DRV_TMR_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_TMR_MC_Test( clientObj < DRV_TMR_INSTANCES_NUMBER), "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_TMR_MULTI_CLIENT_DOBJ( clientObj , dObj );

    /* rturn the current sync mode */
    return ( _DRV_TMR_OBJ( dObj , syncMode ) );

} /* DRV_TMR_SyncModeGet */


/******************************************************************************
  Function:
    void DRV_TMR_Start ( DRV_HANDLE handle)

  Summary:
    Starts the TMR

  Description:
    This routine starts the TMR

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    None
*/

void _DRV_TMR_MAKE_NAME( Start )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_TMR_MC_ARG( DRV_HANDLE handle )
)
{
    /* Multi client variables are removed from single client builds. */
    _DRV_TMR_MC( DRV_TMR_CLIENT_OBJ clientObj = (DRV_TMR_CLIENT_OBJ) 0 );
    _DRV_TMR_DYN( DRV_TMR_OBJ dObj = (DRV_TMR_OBJ) 0 );

    /* Get the Client object from the handle passed */
    _DRV_TMR_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_TMR_MC_Test( clientObj < DRV_TMR_INSTANCES_NUMBER), "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_TMR_MULTI_CLIENT_DOBJ( clientObj , dObj );

    /* Start the Timer */
    if( PLIB_TMR_ExistsEnableControl( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( dObj , tmrId ) ) ) )
    {
        PLIB_TMR_Start( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( dObj , tmrId ) ) );
    }

    /* Update the Client Status */
    _DRV_TMR_CLIENT_OBJ( clientObj , status ) = DRV_TMR_CLIENT_STATUS_STARTED;

} /* DRV_TMR_Start */


/******************************************************************************
  Function:
    void DRV_TMR_Stop ( DRV_HANDLE handle)

  Summary:
    Stops the running timer

  Description:
    This routine stops the running timer

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    None
*/

void _DRV_TMR_MAKE_NAME( Stop )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_TMR_MC_ARG( DRV_HANDLE handle )
)
{
    /* Multi client variables are removed from single client builds. */
    _DRV_TMR_MC( DRV_TMR_CLIENT_OBJ clientObj = (DRV_TMR_CLIENT_OBJ) 0 );
    _DRV_TMR_DYN( DRV_TMR_OBJ dObj = (DRV_TMR_OBJ) 0 );

    /* Get the Client object from the handle passed */
    _DRV_TMR_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_TMR_MC_Test( clientObj < DRV_TMR_INSTANCES_NUMBER), "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_TMR_MULTI_CLIENT_DOBJ( clientObj , dObj );

    /* Stop the Timer from running */
    if( PLIB_TMR_ExistsEnableControl( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( dObj , tmrId ) ) ) )
    {
        PLIB_TMR_Stop( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( dObj , tmrId ) ) );
    }

    /* Update the Client Status */
    _DRV_TMR_CLIENT_OBJ( clientObj , status ) = DRV_TMR_CLIENT_STATUS_STOPPED;

} /* DRV_TMR_Stop */


/******************************************************************************
  Function:
    bool DRV_TMR_ElapsedStatusGetAndClear( DRV_HANDLE handle )

  Summary:
    Returns the TMR count elapse status

  Description:
    Returns the TMR count elapse status

  Parameters:
    handle      - A valid open-instance handle, returned from the driver's
                  open routine

  Returns:
    true            - TMR Elapsed
    false           - TMR is not yet elapsed/processing
*/

bool _DRV_TMR_MAKE_NAME( ElapsedStatusGetAndClear )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_TMR_MC_ARG( DRV_HANDLE handle )
)
{
    /* Multi client variables are removed from single client builds. */
    _DRV_TMR_MC( DRV_TMR_CLIENT_OBJ clientObj = (DRV_TMR_CLIENT_OBJ) 0 );
    _DRV_TMR_DYN( DRV_TMR_OBJ dObj = (DRV_TMR_OBJ) 0 );
    bool status = false;

    /* Get the Client object from the handle passed */
    _DRV_TMR_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_TMR_MC_Test( clientObj < DRV_TMR_INSTANCES_NUMBER), "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_TMR_MULTI_CLIENT_DOBJ(clientObj, dObj);

    /* Get the updated TMR elapse status */
    status = _DRV_TMR_OBJ(dObj, elapseStatus);

    /* Check if the TMR elapsed */
    if ( status == true )
    {
        /* Reset the status information */
        _DRV_TMR_OBJ(dObj, elapseStatus) = false;
    }

    /* return the current elapse status */
    return ( status );

} /* DRV_TMR_ElapsedStatusGetAndClear */


/******************************************************************************
  Function:
    void DRV_TMR_Tasks( SYS_MODULE_OBJ object)

  Summary:
    Used to maintain the driver's state machine and implement its ISR

  Description:
    This routine is used to maintain the driver's internal state machine and
    implement its ISR for interrupt-driven implementations.

  Parameters:
    object          - Identifies the Driver Object returned by the Initialize
                      interface

  Returns:
    None
*/

void _DRV_TMR_MAKE_NAME( Tasks )
(
    /* Function Parameter: (Dynamic arguments are removed from static builds.) */
    _DRV_TMR_DYN_ARG( SYS_MODULE_OBJ object )
)
{
    _DRV_TMR_DYN( DRV_TMR_OBJ dObj = (DRV_TMR_OBJ) object );

    /* Check for the valid driver object passed */
    SYS_ASSERT( _DRV_TMR_ObjectIsValid(dObj), "Driver Object is invalid" );

    /* Check if the Timer Interrupt/Status is set */
    if ( true == _DRV_TMR_InterruptSourceStatusGet(_DRV_TMR_GET_INT_SRC(_DRV_TMR_OBJ(dObj, interruptSource))) )
    {
        /* Update counter values in case of a overflow based TMR */
        _DRV_TMR_PeriodSet( _DRV_TMR_OBJ(dObj, tmrId), _DRV_TMR_OBJ(dObj, timerPeriod) );

        /* Indicate to the application that the TMR has elapsed */
        _DRV_TMR_OBJ( dObj , elapseStatus ) = true;

        /* Alarm Functionality */
        #if defined( DRV_TMR_ALARM_ENABLE )

            /* Check if the alarm is active */
            if ( _DRV_TMR_OBJ(dObj, alarmInUse) == true )
            {
                /* increment the alarm */
                _DRV_TMR_OBJ(dObj, alarmCount) = _DRV_TMR_OBJ(dObj, alarmCount) + 1;

                /* callback the application routine */
                _DRV_TMR_OBJ(dObj, alarmCallback());

                #if ( DRV_TMR_ALARM_PERIODIC == false )
                
                    /* Alarm in one shot mode */
                    if ( _DRV_TMR_OBJ(dObj, alarmCount) == 1 )
                    {
                        /* first shot is done, deactivate it */
                        _DRV_TMR_OBJ(dObj, alarmInUse) = false;
                        _DRV_TMR_OBJ(dObj, alarmCount) = 0;
                        _DRV_TMR_OBJ(dObj, alarmCallback) = NULL;
                    }

                #endif // ( DRV_TMR_ALARM_PERIODIC == false )
            }

        #endif // DRV_TMR_ALARM_ENABLE

        /* Clear Timer Interrupt/Status Flag */
        _DRV_TMR_InterruptSourceClear( _DRV_TMR_GET_INT_SRC( _DRV_TMR_OBJ(dObj, interruptSource) ) );
    }
        
} /* DRV_TMR_Tasks */


//******************************************************************************
/* Function:
    unsigned int DRV_TMR_VersionGet( const SYS_MODULE_INDEX drvIndex )

  Summary:
    Gets TMR driver version in numerical format.

  Description:
    This routine gets the TMR driver version. The version is encoded as
    major * 10000 + minor * 100 + patch. The stringized version can be obtained
    using DRV_TMR_VersionStrGet()

  Parameters:
    None.

  Returns:
    Current driver version in numerical format.
*/

unsigned int _DRV_TMR_MAKE_NAME( VersionGet )( const SYS_MODULE_INDEX drvIndex )
{
    return( ( _DRV_TMR_VERSION_MAJOR * 10000 ) +
            ( _DRV_TMR_VERSION_MINOR * 100 ) +
            ( _DRV_TMR_VERSION_PATCH ) );

} /* DRV_TMR_VersionGet */


// *****************************************************************************
/* Function:
    char * DRV_TMR_VersionStrGet( const SYS_MODULE_INDEX drvIndex )

  Summary:
    Gets TMR driver version in string format.

  Description:
    This routine gets the TMR driver version. The version is returned as
    major.minor.path[type], where type is optional. The numertical version can
    be obtained using DRV_TMR_VersionGet()

  Parameters:
    None.

  Returns:
    Current TMR driver version in the string format.

  Remarks:
    None.
*/

char * _DRV_TMR_MAKE_NAME( VersionStrGet )( const SYS_MODULE_INDEX drvIndex )
{
    return _DRV_TMR_VERSION_STR;

} /* DRV_TMR_VersionStrGet */


/*******************************************************************************
End of File
*/

