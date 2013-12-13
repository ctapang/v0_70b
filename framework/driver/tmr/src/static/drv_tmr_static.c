/*******************************************************************************
  Timer Device Driver Definition

  Company:
    Microchip Technology Inc.

  FileName:
    drv_tmr_static.c

  Summary:
    Timer device driver static single client implementation.

  Description:
    The Timer device driver provides a simple interface to manage the Timer modules
    on Microchip microcontrollers.  This file Implements the core interface 
    routines for the Timer driver.
    While building the driver from source, ALWAYS use this file in the build.
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
//DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Include Files
// *****************************************************************************
// *****************************************************************************

#include "driver/tmr/src/drv_tmr_local.h"



// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Driver hardware instance objects

  Summary:
    Defines the hardware instances objects that are available on the device.

  Description:
    This data type defines the hardware instance objects that are available on
    the device, so as to capture the hardware state of the instance.

  Remarks:
    Not all modes are available on all devices.
*/

DRV_TMR_OBJ                         _DRV_TMR_OBJ_MAKE_NAME( gDrvTMRObj ) ;


// *****************************************************************************
/* Driver Client instance objects.

  Summary:
    Defines the client instance objects that are available on the device.

  Description:
    This data type defines the client instance objects that are available on
    the device, so as to capture the Client state of the instance.

  Remarks:
    None.
*/

DRV_TMR_CLIENT_OBJ                  _DRV_TMR_OBJ_MAKE_NAME( gDrvTMRClientObj ) ;


// *****************************************************************************
// Section: File Scope Macros
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Macro: _DRV_TMR_OBJ(obj,mem)

  Summary:
    Returns the appropriate driver object member.

  Description:
    This macro returns either the static object or the indexed dynamic object.
    This macro has variations for dynamic or static driver.

*/

#define _DRV_TMR_OBJ(obj,mem)       _DRV_TMR_OBJ_MAKE_NAME(gDrvTMRObj).mem


// *****************************************************************************
/* Macro: _DRV_TMR_CLIENT_OBJ(obj,mem)

  Summary:
    Returns the appropriate client member.

  Description:
    This macro returns either the static object or the indexed dynamic object.
    This macro has variations for dynamic or static driver.
*/

#define _DRV_TMR_CLIENT_OBJ(obj,mem)    _DRV_TMR_OBJ_MAKE_NAME(gDrvTMRClientObj).mem


// *****************************************************************************
/* Macro:
    _DRV_TMR_ExternalClockSyncEnable(index)

  Summary:
    Enables external clock synchronization.

  Description:
    This macro Macro enables the external clock synchronization.

  Remarks:
    None.
*/

#define _DRV_TMR_ExternalClockSyncEnable(index)     PLIB_TMR_ClockSourceExternalSyncEnable(index)


// *****************************************************************************
/* Macro:
    _DRV_TMR_ExternalClockSyncDisable(index)

  Summary:
    Disables external clock synchronization.

  Description:
    This macro Macro disables the external clock synchronization

  Remarks:
    None.
*/

#define _DRV_TMR_ExternalClockSyncDisable(index)    PLIB_TMR_ClockSourceExternalSyncDisable(index)


// *****************************************************************************
// *****************************************************************************
// Section: File Scope Functions
// *****************************************************************************
// *****************************************************************************

/******************************************************************************
  Function:
    static void _DRV_TMR_SyncModeControl ( DRV_TMR_SYNC_MODE newMode )

  Summary:
    Sets the new sync mode.

  Description:
    This internal Timer driver function sets the new sync mode in the hardware.

  Remarks:
    None.
*/

static void _DRV_TMR_SyncModeControl( DRV_TMR_SYNC_MODE newMode )
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
    static void _DRV_TMR_SetupHardware ( DRV_TMR_INIT   *tmrInit )

  Summary:
    Sets up the hardware from the initialzation structure.

  Description:
    This routine sets up the hardware from the initialzation structure.
 
  Remarks:
    Called.
*/

static void _DRV_TMR_SetupHardware( DRV_TMR_INIT * tmrInit )
{
    /* Initialize the Interrupt Source */
    _DRV_TMR_STATIC_INT_SRC( _DRV_TMR_OBJ(DRV_TMR_INDEX, interruptSource) = _DRV_TMR_INT_SRC_GET(tmrInit->interruptSource) );

    /* Power state initialization */
    if( PLIB_TMR_ExistsStopInIdleControl( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) ) )
    {
        if( _DRV_TMR_POWER_STATE_GET( tmrInit->moduleInit.sys.powerState ) == SYS_MODULE_POWER_IDLE_STOP )
        {
            PLIB_TMR_StopInIdleEnable( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) );
        }
        else if( ( _DRV_TMR_POWER_STATE_GET( tmrInit->moduleInit.sys.powerState ) == SYS_MODULE_POWER_IDLE_RUN ) ||
                 ( _DRV_TMR_POWER_STATE_GET( tmrInit->moduleInit.sys.powerState ) == SYS_MODULE_POWER_RUN_FULL ) )
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
    if( PLIB_TMR_ExistsMode8Bit( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) ) && ( DRV_TMR_COUNT_WIDTH == 8 ) )
    {
        PLIB_TMR_Mode8BitEnable( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) );
    }
    else if( PLIB_TMR_ExistsMode16Bit( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) ) && ( DRV_TMR_COUNT_WIDTH == 16 ) )
    {
        PLIB_TMR_Mode16BitEnable( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) );
    }
    else if( PLIB_TMR_ExistsMode32Bit( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) ) && ( DRV_TMR_COUNT_WIDTH == 32 ) )
    {
        PLIB_TMR_Mode32BitEnable( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) );
    }

    /* Timer Mode Configuration */
    /* Clock Source Selection - Internal or External */
    if( PLIB_TMR_ExistsClockSource( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) ) )
    {
        PLIB_TMR_ClockSourceSelect( _DRV_TMR_PERIPHERAL_ID_GET( plibId ), _DRV_TMR_CLOCK_SOURCE_GET(tmrInit->clockSource) );
    }

    _DRV_TMR_SyncModeControl( _DRV_TMR_SYNC_MODE_GET(tmrInit->syncMode) );

    /* Update the operating mode of the Timer initialized */
    _DRV_TMR_OBJ( DRV_TMR_INDEX, syncMode ) = _DRV_TMR_SYNC_MODE_GET(tmrInit->syncMode);

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
   

    _DRV_TMR_OBJ( DRV_TMR_INDEX, prescale ) = _DRV_TMR_PRESCALE_GET(tmrInit->prescale);

    /* Output Post scaler selection */
    if( PLIB_TMR_ExistsPostscale( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) ) )
    {
        PLIB_TMR_PostscaleSelect( _DRV_TMR_PERIPHERAL_ID_GET( plibId ), _DRV_TMR_POSTSCALE_GET(tmrInit->postscale) );
    }

    /* Source Edge Selection */
    if( PLIB_TMR_ExistsClockSourceEdge( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) ) )
    {
        PLIB_TMR_ClockSourceEdgeSelect( _DRV_TMR_PERIPHERAL_ID_GET( plibId ), _DRV_TMR_SOURCE_EDGE_GET(tmrInit->sourceEdge) );
    }

    /* Asynchronous Write Control */
    if( PLIB_TMR_ExistsCounterAsyncWriteControl( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) ) )
    {
        if( DRV_TMR_ASYNC_WRITE_ENABLE == true )
        {
            PLIB_TMR_CounterAsyncWriteEnable( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) );
        }
        else if( DRV_TMR_ASYNC_WRITE_ENABLE == false )
        {
            PLIB_TMR_CounterAsyncWriteDisable( _DRV_TMR_PERIPHERAL_ID_GET( plibId ) );
        }
    }

    /* Update the Timer data value */
    _DRV_TMR_PeriodSet( _DRV_TMR_PERIPHERAL_ID_GET(plibId), _DRV_TMR_VALUE_GET(tmrInit->timerPeriod) );
    
    _DRV_TMR_OBJ( DRV_TMR_INDEX, timerPeriod ) = _DRV_TMR_VALUE_GET(tmrInit->timerPeriod);

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
    Initializes hardware and data for the specified instance of the Timer module.

  Description:
    This function initializes hardware for the instance of the Timer module,
    using the specified hardware initialization data.  It also initializes all 
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

void _DRV_TMR_MAKE_NAME(Initialize)( const SYS_MODULE_INIT * const init )
{
    DRV_TMR_INIT * tmrInit = NULL;

    /* Assign to the local pointer the init data passed */
    tmrInit = ( DRV_TMR_INIT * ) init;

    /* Set the operation flag to be in use */
    _DRV_TMR_OBJ( DRV_TMR_INDEX, inUse ) = true;

    /* Setup the Hardware */
    _DRV_TMR_SetupHardware( tmrInit );

    /* Interrupt flag cleared on the safer side */
    _DRV_TMR_InterruptSourceClear( _DRV_TMR_INT_SRC_GET( _DRV_TMR_OBJ(DRV_TMR_INDEX, interruptSource) ) );

    /* Enable the interrupt source in case of interrupt mode */
    _DRV_TMR_InterruptSourceEnable( _DRV_TMR_INT_SRC_GET( _DRV_TMR_OBJ(DRV_TMR_INDEX, interruptSource) ) );

    /* Create the required mutexes. */
    OSAL_ASSERT( (OSAL_MUTEX_Create(&_DRV_TMR_OBJ( DRV_TMR_INDEX , clientObjectMutex )) == OSAL_RESULT_TRUE),
                 "Unable to create client object mutex" );
    
    /* Set the current driver state */
    _DRV_TMR_OBJ( DRV_TMR_INDEX , status ) = SYS_STATUS_READY;

} /* DRV_TMR_Initialize */


/******************************************************************************
  Function:
    void DRV_TMR_Reinitialize( SYS_MODULE_OBJ object,
                               const SYS_MODULE_INIT* const init )

  Summary:
    Reinitializes and refreshes the hardware for the instance of the Timer
    module.

  Description:
    This function reinitializes and refreshes the hardware for the instance
    of the Timer module using the hardware initialization given data.
    It does not clear or reinitialize internal data structures

  Parameters:
    object          - Identifies the driver object returned by the Initialize
                      interface
    init            - Pointer to the data structure containing any data
                      necessary to initialize the hardware.

  Returns:
    None.
*/

void _DRV_TMR_MAKE_NAME( Reinitialize )( const SYS_MODULE_INIT * const init )
{
    DRV_TMR_INIT * tmrInit = NULL;

    /* Valid init structure is present */
    tmrInit = ( DRV_TMR_INIT * ) init;

    /* Stop the Timer Module */
    if( PLIB_TMR_ExistsEnableControl( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ) ) )
    {
        PLIB_TMR_Stop( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ) );
    }

    /* Set the curent driver state */
    _DRV_TMR_OBJ( DRV_TMR_INDEX , status ) = SYS_STATUS_UNINITIALIZED ;

    /* Setup the Hardware */
    _DRV_TMR_SetupHardware( tmrInit );
    
    /* Re Start the Timer Module */
    if( PLIB_TMR_ExistsEnableControl( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ) ) )
    {
        PLIB_TMR_Start( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ) );
    }

    /* Create the required mutexes. */
    OSAL_ASSERT( (OSAL_MUTEX_Create(&_DRV_TMR_OBJ( DRV_TMR_INDEX , clientObjectMutex )) == OSAL_RESULT_TRUE),
                 "Unable to create client object mutex" );
    
    /* Set the curent driver state */
    _DRV_TMR_OBJ( DRV_TMR_INDEX , status ) = SYS_STATUS_READY;

} /* DRV_TMR_Reinitialize */


/******************************************************************************
  Function:
    void DRV_TMR_Deinitialize( SYS_MODULE_OBJ object )

  Summary:
    Deinitializes the specific module instance of the Timer module.

  Description:
    Deinitializes the specific module instance disabling its operation (and any
    hardware for driver modules).  Resets all the internal data structures and
    fields for the specified instance to the default settings.

  Parameters:
    object          - Identifies the driver object returned by the Initialize
                      interface

  Returns:
    None.
*/

void _DRV_TMR_MAKE_NAME( Deinitialize )( void )
{
    /* Interrupt De-Registration */
    _DRV_TMR_InterruptSourceDisable( _DRV_TMR_INT_SRC_GET( _DRV_TMR_OBJ(DRV_TMR_INDEX, interruptSource) ) );

    /* Set the Device Status */
    _DRV_TMR_OBJ( DRV_TMR_INDEX , status ) = SYS_STATUS_UNINITIALIZED;

    /* Remove the driver usage */
    _DRV_TMR_OBJ( DRV_TMR_INDEX , inUse ) = false;

    /* Reset the status information */
    _DRV_TMR_OBJ( DRV_TMR_INDEX , elapseStatus ) = false;

    /* Deleting the Mutexes */
    OSAL_ASSERT( (OSAL_MUTEX_Delete(&_DRV_TMR_OBJ( DRV_TMR_INDEX , clientObjectMutex )) == OSAL_RESULT_TRUE),
                 "Unable to delete client object mutex" );

} /* DRV_TMR_Deinitialize */


/******************************************************************************
  Function:
    SYS_STATUS DRV_TMR_Status( SYS_MODULE_OBJ object )

  Summary:
    Provides the current status of the hardware instance of the Timer module.

  Description:
    This function provides the current status of the hardware instance of the
    Timer module.

  Parameters:
    object          - Identifies the driver object returned by the Initialize
                      interface

  Returns:
    SYS_STATUS_READY  - Indicates that any previous module operation for the
                        specified module has completed
                        
    SYS_STATUS_BUSY   - Indicates that a previous module operation for the
                        specified module has not yet completed
                        
    SYS_STATUS_ERROR  - Indicates that the specified module is in an error state
*/

SYS_STATUS _DRV_TMR_MAKE_NAME( Status )( void )
{
    /* Return the status associated with the driver handle */
    return( _DRV_TMR_OBJ( DRV_TMR_INDEX , status ) );

} /* DRV_TMR_Status */


/******************************************************************************
  Function:
    void DRV_TMR_Tasks( SYS_MODULE_OBJ object)

  Summary:
    Maintains the driver's state machine and implement its ISR.

  Description:
    This function is used to maintain the driver's internal state machine and
    implement its ISR for interrupt-driven implementations.

  Parameters:
    object          - Identifies the driver object returned by the Initialize
                      interface

  Returns:
    None.
*/

void _DRV_TMR_MAKE_NAME( Tasks )( void )
{
    /* Check if the Timer Interrupt/Status is set */
    if ( true == _DRV_TMR_InterruptSourceStatusGet( _DRV_TMR_INT_SRC_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX, interruptSource ) ) ) )
    {
        /* Update counter values in case of a overflow based Timer */
        _DRV_TMR_PeriodSet( _DRV_TMR_OBJ( DRV_TMR_INDEX, tmrId ), _DRV_TMR_OBJ( DRV_TMR_INDEX, timerPeriod ) );

        /* Indicate to the application that the Timer has elapsed */
        _DRV_TMR_OBJ( DRV_TMR_INDEX , elapseStatus ) = true;

        /* Alarm Functionality */
        #if defined( DRV_TMR_ALARM_ENABLE )

            /* Check if the alarm is active */
            if ( _DRV_TMR_OBJ( DRV_TMR_INDEX, alarmInUse ) == true )
            {
                /* increment the alarm */
                _DRV_TMR_OBJ( DRV_TMR_INDEX, alarmCount ) = _DRV_TMR_OBJ( DRV_TMR_INDEX, alarmCount ) + 1;

                /* callback the application routine */
                if( _DRV_TMR_OBJ( DRV_TMR_INDEX, alarmCallback ) != NULL )
                {
                    _DRV_TMR_OBJ( DRV_TMR_INDEX, alarmCallback() );
                }

                #if ( DRV_TMR_ALARM_PERIODIC == false )

                    /* Alarm in one shot mode */
                    if ( _DRV_TMR_OBJ( DRV_TMR_INDEX, alarmCount ) == 1 )
                    {
                        /* first shot is done, deactivate it */
                        _DRV_TMR_OBJ( DRV_TMR_INDEX, alarmInUse ) = false;
                        _DRV_TMR_OBJ( DRV_TMR_INDEX, alarmCount ) = 0;
                        _DRV_TMR_OBJ( DRV_TMR_INDEX, alarmCallback ) = NULL;
                    }

                #endif // ( DRV_TMR_ALARM_PERIODIC == false )
            }

        #endif // DRV_TMR_ALARM_ENABLE

        /* Clear Timer Interrupt/Status Flag */
        _DRV_TMR_InterruptSourceClear( _DRV_TMR_INT_SRC_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX, interruptSource ) ) );
    }

} /* DRV_TMR_Tasks */


/******************************************************************************
  Function:
    DRV_HANDLE DRV_TMR_Open( const SYS_MODULE_INDEX index,
                             const DRV_IO_INTENT intent )

  Summary:
    Opens the specific module instance and returns a handle.

  Description:
    This function opens a driver for use by any client module and provides a
    handle that must be provided to any of the other driver operations to
    identify the caller and the instance of the driver/hardware module.

  Parameters:
    index           - Identifier for the instance to be initialized
    ioIntent        - Possible values from DRV_IO_INTENT

  Returns:
    If successful, the routine returns a valid open-instance handle (a number
    identifying both the caller and the module instance).
    If an error occurs, the return value is DRV_HANDLE_INVALID.
*/

void _DRV_TMR_MAKE_NAME( Open )( const DRV_IO_INTENT ioIntent )
{
    /* Setup client operations */

    /* OSAL - Lock Mutex */
    if (OSAL_MUTEX_Lock(_DRV_TMR_OBJ( DRV_TMR_INDEX , clientObjectMutex ), OSAL_WAIT_FOREVER) == OSAL_RESULT_TRUE)
    {
        /* Set the flag as in use */
        _DRV_TMR_CLIENT_OBJ( DRV_TMR_INDEX , inUse ) = true;
        _DRV_TMR_CLIENT_OBJ( DRV_TMR_INDEX , driverObject ) = DRV_TMR_INDEX;
    
        /* OSAL - Unlock Mutex */
        OSAL_ASSERT( (OSAL_MUTEX_Unlock(_DRV_TMR_OBJ( DRV_TMR_INDEX , clientObjectMutex )) == OSAL_RESULT_TRUE),
                     "Unable to unlock client object mutex" );
    }

    /* Update the Client Status */
    _DRV_TMR_CLIENT_OBJ( DRV_TMR_INDEX , status ) = DRV_TMR_CLIENT_STATUS_READY;

} /* DRV_TMR_Open */


/******************************************************************************
  Function:
    void DRV_TMR_Close( DRV_HANDLE handle )

  Summary:
    Closes an opened instance of a driver.

  Description:
    This function closes an openedcinstance of a driver, invalidating the specified
    handle.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    None.
*/

void _DRV_TMR_MAKE_NAME( Close )( void )
{
    /* OSAL - lock Mutex */
    if (OSAL_MUTEX_Lock(_DRV_TMR_OBJ( DRV_TMR_INDEX , clientObjectMutex ), OSAL_WAIT_FOREVER) == OSAL_RESULT_TRUE)
    {
        /* Free the Client Instance */
        _DRV_TMR_CLIENT_OBJ( DRV_TMR_INDEX , inUse ) = false ;
    
        /* OSAL - unlock Mutex */
        OSAL_ASSERT( (OSAL_MUTEX_Unlock(_DRV_TMR_OBJ( DRV_TMR_INDEX , clientObjectMutex )) == OSAL_RESULT_TRUE),
                     "Unable to unlock client object mutex" );
    }

    /* Update the Client Status */
    _DRV_TMR_CLIENT_OBJ( DRV_TMR_INDEX , status ) = DRV_TMR_CLIENT_STATUS_INVALID;

} /* DRV_TMR_Close */


/******************************************************************************
  Function:
    DRV_TMR_CLIENT_STATUS DRV_TMR_ClientStatus( DRV_HANDLE handle )

  Summary:
    Gets the status of the module instance associated with the handle.

  Description:
    This function gets the status of the module instance associated with the
    handle.

  Parameters:
    handle       - A valid open instance handle, returned from the driver's
                   open routine

  Returns:
    DRV_TMR_CLIENT_STATUS value describing the current status of the driver.
*/

DRV_TMR_CLIENT_STATUS _DRV_TMR_MAKE_NAME( ClientStatus )( void )
{
    /* Return the client status associated with the handle passed */
    return( _DRV_TMR_CLIENT_OBJ( DRV_TMR_INDEX , status ) );

} /* DRV_TMR_ClientStatus */


/******************************************************************************
  Function:
   void DRV_TMR_Period8BitSet( DRV_HANDLE handle, uint8_t value )

  Summary:
    Updates the 8-bit Timer value.

  Description:
    This function updates the 8-bit Timer value.

  Parameters:
    handle      - A valid open instance handle, returned from the driver's
                  open routine
    value       - 8-bit period value

  Returns:
    None.
*/

void _DRV_TMR_MAKE_NAME( Period8BitSet )( uint8_t value )
{
    /* Update the counter values */
    PLIB_TMR_Period8BitSet( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ), value );

    // OSAL Mutex Lock
	/* Client update with the new count value */
	_DRV_TMR_OBJ( DRV_TMR_INDEX , timerPeriod ) = value;

	/* Reset the status information */
	_DRV_TMR_OBJ( DRV_TMR_INDEX , elapseStatus ) = false;

	/* OSAL Mutex Unlock */
	
} /* DRV_TMR_Period8BitSet */


/******************************************************************************
  Function:
   void DRV_TMR_Period16BitSet( DRV_HANDLE handle, uint16_t value )

  Summary:
    Updates the 16-bit Timer value.

  Description:
    This function updates the 16-bit Timer value.

  Parameters:
    handle      - A valid open instance handle, returned from the driver's
                  open routine
    value       - 16-bit period value

  Returns:
    None.
*/

void _DRV_TMR_MAKE_NAME( Period16BitSet )( uint16_t value )
{
    /* Update the counter values */
    PLIB_TMR_Period16BitSet( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ), value );

    // OSAL Mutex Lock
	/* Client update with the new count value */
	_DRV_TMR_OBJ( DRV_TMR_INDEX , timerPeriod ) = value;

	/* Reset the status information */
	_DRV_TMR_OBJ( DRV_TMR_INDEX , elapseStatus ) = false;

	/* OSAL Mutex Unlock */

} /* DRV_TMR_Period16BitSet */


/******************************************************************************
  Function:
   void DRV_TMR_Period32BitSet( DRV_HANDLE handle, uint32_t value )

  Summary:
    Updates the 32-bit Timer value.

  Description:
    This function updates 32-bit Timer value.

  Parameters:
    handle      - A valid open instance handle, returned from the driver's
                  open routine
    value       - 32-bit period value

  Returns:
    None.
*/

void _DRV_TMR_MAKE_NAME( Period32BitSet )( uint32_t value )
{
    /* Update the counter values */
    PLIB_TMR_Period32BitSet( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ), value );

    // OSAL Mutex Lock
	/* Client update with the new count value */
	_DRV_TMR_OBJ( DRV_TMR_INDEX , timerPeriod ) = value;

	/* Reset the status information */
	_DRV_TMR_OBJ( DRV_TMR_INDEX , elapseStatus ) = false;

	/* OSAL Mutex Unlock */

} /* DRV_TMR_Period32BitSet */


/******************************************************************************
  Function:
   uint8_t DRV_TMR_Period8BitGet( DRV_HANDLE handle )

  Summary:
    Provides the Timer's 8-bit period value.

  Description:
    This function provides the Timer's 8-bit period value.

  Parameters:
    handle       - A valid open instance handle, returned from the driver's
                   open routine

  Returns:
    The Timer's 8-bit period value.
*/

uint8_t _DRV_TMR_MAKE_NAME( Period8BitGet )( void )
{
    uint8_t periodVal = 0xFF;

	// OSAL Mutex Lock

	/* get the timer period value and return it */
	periodVal = PLIB_TMR_Period8BitGet( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ) );

	/* OSAL Mutex Unlock */
		
    return( periodVal );

} /* DRV_TMR_Period8BitGet */


/******************************************************************************
  Function:
   uint16_t DRV_TMR_Period16BitGet( DRV_HANDLE handle )

  Summary:
    Provides the Timer's 16-bit period value.

  Description:
    This function provides the Timer's 16-bit period value.

  Parameters:
    handle       - A valid open instance handle, returned from the driver's
                   open routine

  Returns:
    The Timer's 16-bit period value.
*/

uint16_t _DRV_TMR_MAKE_NAME( Period16BitGet )( void )
{
    uint16_t periodVal = 0xFFFF;

    // OSAL Mutex Lock
	
	/* get the timer period value and return it */
	periodVal = PLIB_TMR_Period16BitGet( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ) );

	/* OSAL Mutex Unlock */
	
    return( periodVal );

} /* DRV_TMR_Period16BitGet */


/******************************************************************************
  Function:
   uint32_t DRV_TMR_Period32BitGet( DRV_HANDLE handle )

  Summary:
    Provides the Timer's 32-bit period value.

  Description:
    This function provides the Timer's 32-bit period value.

  Parameters:
    handle       - A valid open instance handle, returned from the driver's
                   open routine

  Returns:
    The Timer's 32-bit period value.
*/

uint32_t _DRV_TMR_MAKE_NAME( Period32BitGet )( void )
{
    uint32_t periodVal = 0xFFFFFFFF;

	// OSAL Mutex Lock
	/* get the timer period value and return it */
	periodVal = PLIB_TMR_Period32BitGet( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ) );

	/* OSAL Mutex Unlock */

    return( periodVal );

} /* DRV_TMR_Period32BitGet */


/******************************************************************************
  Function:
   void DRV_TMR_Counter8BitSet( DRV_HANDLE handle, uint8_t value )

  Summary:
    Updates the Timer's 8-bit value.

  Description:
    This function updates the Timer's 8-bit value.

  Parameters:
    handle      - A valid open instance handle, returned from the driver's
                  open routine
    value       - 8-bit counter value

  Returns:
    None.
*/

void _DRV_TMR_MAKE_NAME( Counter8BitSet )( uint8_t value )
{
    /* Update the counter values */
    PLIB_TMR_Counter8BitSet( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ), value );

    /* Reset the status information */
    _DRV_TMR_OBJ( DRV_TMR_INDEX , elapseStatus ) = false;

} /* DRV_TMR_Counter8BitSet */


/******************************************************************************
  Function:
   void DRV_TMR_Counter16BitSet( DRV_HANDLE handle, uint16_t value )

  Summary:
    Updates the Timer's 16-bit value.

  Description:
    This function updates the Timer's 16-bit value.

  Parameters:
    handle      - A valid open instance handle, returned from the driver's
                  open routine
    value       - 16-bit counter value

  Returns:
    None.
*/

void _DRV_TMR_MAKE_NAME( Counter16BitSet )( uint16_t value )
{
    /* Update the counter values */
    PLIB_TMR_Counter16BitSet( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ), value );

    /* Reset the status information */
    _DRV_TMR_OBJ( DRV_TMR_INDEX , elapseStatus ) = false;

} /* DRV_TMR_CounterSet */


/******************************************************************************
  Function:
   void DRV_TMR_Counter32BitSet( DRV_HANDLE handle, uint32_t value )

  Summary:
    Updates the Timer's 32-bit value.

  Description:
    This function updates the Timer's 32-bit value.

  Parameters:
    handle      - A valid open instance handle, returned from the driver's
                  open routine
    value       - 32-bit counter value

  Returns:
    None.
*/

void _DRV_TMR_MAKE_NAME( Counter32BitSet )( uint32_t value )
{
    /* Update the counter values */
    PLIB_TMR_Counter32BitSet( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ), value );

    /* Reset the status information */
    _DRV_TMR_OBJ( DRV_TMR_INDEX , elapseStatus ) = false;

} /* DRV_TMR_CounterSet */


/******************************************************************************
  Function:
   uint8_t DRV_TMR_Counter8BitGet( DRV_HANDLE handle )

  Summary:
    Provides the 8-bit current counter value.

  Description:
    This function provides the 8-bit current counter value.

  Parameters:
    handle       - A valid open instance handle, returned from the driver's
                   open routine

  Returns:
    The 8-bit current counter value.
*/

uint8_t _DRV_TMR_MAKE_NAME( Counter8BitGet )( void )
{
    uint8_t countVal = 0xFF;

    /* get the current counter value and return it */
    countVal = PLIB_TMR_Counter8BitGet( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ) );

    return( countVal );

} /* DRV_TMR_Counter8BitGet */


/******************************************************************************
  Function:
   uint16_t DRV_TMR_Counter16BitGet( DRV_HANDLE handle )

  Summary:
    Provides the 16-bit current counter value.

  Description:
    This function provides the 16-bit current counter value.

  Parameters:
    handle       - A valid open instance handle, returned from the driver's
                   open routine

  Returns:
    The 16-bit current counter value.
*/

uint16_t _DRV_TMR_MAKE_NAME( Counter16BitGet )( void )
{
    uint16_t countVal = 0xFFFF;

    /* get the current counter value and return it */
    countVal = PLIB_TMR_Counter16BitGet( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ) );

    return( countVal );

} /* DRV_TMR_Counter16BitGet */


/******************************************************************************
  Function:
   uint32_t DRV_TMR_Counter32BitGet( DRV_HANDLE handle )

  Summary:
    Provides the 32-bit current counter value.

  Description:
    This function provides the 32-bit current counter value.

  Parameters:
    handle       - A valid open instance handle, returned from the driver's
                   open routine

  Returns:
    The 32-bit current counter value.
*/

uint32_t _DRV_TMR_MAKE_NAME( Counter32BitGet )( void )
{
    uint32_t countVal = 0xFFFFFFFF;

    /* get the current counter value and return it */
    countVal = PLIB_TMR_Counter32BitGet( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ) );

    return( countVal );

} /* DRV_TMR_CounterGet */


/******************************************************************************
  Function:
   void DRV_TMR_SyncModeSet( DRV_HANDLE handle,
                             DRV_TMR_SYNC_MODE newMode )

  Summary:
    Changes the Timer Sync mode.

  Description:
    This function changes the Timer Sync mode.

  Parameters:
    handle       - A valid open instance handle, returned from the driver's
                   open routine
    newMode      - Possible values from DRV_TMR_SYNC_MODE

  Returns:
    None.
*/

void _DRV_TMR_MAKE_NAME( SyncModeSet )( DRV_TMR_SYNC_MODE newMode )
{
    /* if the new mode requested matches the existing one, simply return */
    if ( newMode == _DRV_TMR_OBJ( DRV_TMR_INDEX , syncMode ) )
        return;

    /* Timer Mode Re Configuration */

    /* Clock Source Selection - Internal or External */
    if ( ( DRV_TMR_SYNC_MODE_SYNCHRONOUS_INTERNAL == newMode ) ||
         ( DRV_TMR_SYNC_MODE_SYNCHRONOUS_INTERNAL_GATED == newMode ) )
    {
        if( PLIB_TMR_ExistsClockSource( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ) ) )
        {
            PLIB_TMR_ClockSourceSelect( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ), TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK );
        }
    }
    else /* External Clock Input */
    {
        if( PLIB_TMR_ExistsClockSource( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ) ) )
        {
            PLIB_TMR_ClockSourceSelect( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ), TMR_CLOCK_SOURCE_EXTERNAL_INPUT_PIN );
        }
    }

    /* Update the sync mode */
    _DRV_TMR_SyncModeControl(  newMode );

    /* Update the sync mode of the Timer initialized */
    _DRV_TMR_OBJ( DRV_TMR_INDEX , syncMode ) = newMode;

} /* DRV_TMR_SyncModeSet */


/******************************************************************************
  Function:
   DRV_TMR_SYNC_MODE DRV_TMR_SyncModeGet( DRV_HANDLE handle )

  Summary:
    Provides the Timer Sync mode.

  Description:
    This function provides the Timer Sync mode.

  Parameters:
    handle       - A valid open instance handle, returned from the driver's
                   open routine

  Returns:
    mode         - Possible values from DRV_TMR_SYNC_MODE
*/

DRV_TMR_SYNC_MODE _DRV_TMR_MAKE_NAME( SyncModeGet )( void )
{
    /* return the current sync mode */
    return ( _DRV_TMR_OBJ( DRV_TMR_INDEX , syncMode ) );

} /* DRV_TMR_SyncModeGet */


/******************************************************************************
  Function:
    void DRV_TMR_Start( DRV_HANDLE handle)

  Summary:
    Starts the Timer.

  Description:
    This function starts the Timer.

  Parameters:
    handle       - A valid open instance handle, returned from the driver's
                   open routine

  Returns:
    None.
*/

void _DRV_TMR_MAKE_NAME( Start )( void )
{
    /* Start the Timer */
    if( PLIB_TMR_ExistsEnableControl( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ) ) )
    {
        PLIB_TMR_Start( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ) );
    }

    /* Update the Client Status */
    _DRV_TMR_CLIENT_OBJ( DRV_TMR_INDEX , status ) = DRV_TMR_CLIENT_STATUS_STARTED;

} /* DRV_TMR_Start */


/******************************************************************************
  Function:
    void DRV_TMR_Stop( DRV_HANDLE handle)

  Summary:
    Stops the running timer.

  Description:
    This function stops the running timer.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine

  Returns:
    None.
*/

void _DRV_TMR_MAKE_NAME( Stop )( void )
{
    /* Stop the Timer from running */
    if( PLIB_TMR_ExistsEnableControl( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ) ) )
    {
        PLIB_TMR_Stop( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ) );
    }

    /* Update the Client Status */
    _DRV_TMR_CLIENT_OBJ( DRV_TMR_INDEX , status ) = DRV_TMR_CLIENT_STATUS_STOPPED;

} /* DRV_TMR_Stop */


/******************************************************************************
  Function:
    bool DRV_TMR_ElapsedStatusGetAndClear( DRV_HANDLE handle )

  Summary:
    Returns the Timer count elapse status.

  Description:
    This function returns the Timer count elapse status.

  Parameters:
    handle      - A valid open-instance handle, returned from the driver's
                  open routine

  Returns:
    - true            - Timer has elapsed
    - false           - Timer has not elapsed/processing
*/

bool _DRV_TMR_MAKE_NAME( ElapsedStatusGetAndClear )( void )
{
    bool status = false;

    /* Get the updated Timer elapse status */
    status = _DRV_TMR_OBJ( DRV_TMR_INDEX, elapseStatus );

    /* Check if the Timer elapsed */
    if ( status == true )
    {
        /* Reset the status information */
        _DRV_TMR_OBJ( DRV_TMR_INDEX, elapseStatus ) = false;
    }

    /* return the current elapse status */
    return ( status );

} /* DRV_TMR_ElapsedStatusGetAndClear */


/******************************************************************************
  Function:
    void DRV_TMR_AlarmSet( DRV_HANDLE handle,
                           const DRV_TMR_ALARM_CONFIG *config)

  Summary:
    Registers an Alarm with the client.

  Description:
    This function registers an alarm with the client.

  Parameters:
    handle      - A valid open-instance handle, returned from the driver's
                  open routine
    config      - Pointer to the alarm configuration structure containing any
                  data necessary to initialize Timer alarms

  Returns:
    None.
*/

void _DRV_TMR_MAKE_NAME( AlarmSet )( const DRV_TMR_ALARM_CONFIG *config )
{
    _DRV_TMR_OBJ( DRV_TMR_INDEX , alarmInUse ) = true ;

    /* update the HW Instance with the callback associated with alarm */
    _DRV_TMR_OBJ( DRV_TMR_INDEX , alarmCallback ) = config->callback ;

    /* Clear the alarm counter */
    _DRV_TMR_OBJ( DRV_TMR_INDEX , alarmCount ) = 0 ;

} /* DRV_TMR_AlarmSet */


/******************************************************************************
  Function:
    uint32_t DRV_TMR_AlarmCountGet( DRV_HANDLE handle )

  Summary:
    Returns the number of times an alarm is generated since the last time it was
    cleared.

  Description:
    This function returns the number of times an alarm is generated since the 
    last time it was cleared.

  Parameters:
    handle      - A valid open-instance handle, returned from the driver's
                  open routine

  Returns:
    The alarm count value.
*/

unsigned int _DRV_TMR_MAKE_NAME( AlarmCountGet )( void )
{
    return _DRV_TMR_OBJ( DRV_TMR_INDEX , alarmCount );

} /* DRV_TMR_AlarmCountGet */


/******************************************************************************
  Function:
    void DRV_TMR_AlarmCountClear( DRV_HANDLE handle )

  Summary:
    Clears the alarm counter

  Description:
    Clears the alarm counter

  Parameters:
    handle      - A valid open-instance handle, returned from the driver's
                  open routine

  Returns:
    None
*/

void _DRV_TMR_MAKE_NAME( AlarmCountClear )( void )
{
    /* Clear the Alarm counter */
    _DRV_TMR_OBJ( DRV_TMR_INDEX , alarmCount ) = 0 ;

} /* DRV_TMR_AlarmCountClear */


/******************************************************************************
  Function:
   uint32_t DRV_TMR_OperatingFrequencyGet( DRV_HANDLE handle )

  Summary:
    Provides the timer running frequency.

  Description:
    This function provides the timer running frequency.

  Parameters:
    handle      - A valid open-instance handle, returned from the driver
                  open routine
    tmrBaseFreq - Timer peripheral base frequency

  Returns:
    32-bit value corresponding to the timer running frequency.
*/

uint32_t _DRV_TMR_MAKE_NAME( OperatingFrequencyGet )( void )
{
    uint32_t prescale, tmrBaseFreq ;

    /* Get the Base frequency from the SYS CLK module */
    tmrBaseFreq = SYS_CLK_ClockFrequencyGet( CLK_PERIPHERAL );
    
    /* PreScale Used */
    if( PLIB_TMR_ExistsPrescale( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ) ) )
    {
        prescale = PLIB_TMR_PrescaleDivisorGet( _DRV_TMR_PERIPHERAL_ID_GET(_DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId)), _DRV_TMR_OBJ( DRV_TMR_INDEX , prescale) );
    }
    else
    {
        prescale = 1;
    }

    return( tmrBaseFreq / prescale ) ;

} /* DRV_TMR_OperatingFrequencyGet */


/******************************************************************************
  Function:
   uint32_t DRV_TMR_TickFrequencyGet( DRV_HANDLE handle )

  Summary:
    Provides the timer tick frequency.

  Description:
    This function provides the timer tick frequency.

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine
    tmrBaseFreq - Timer peripheral base frequency

  Returns:
    32-bit value corresponding to the running tick frequency. For example,
    if the tick period is 100 ms, the return value would be 10 Hz.
*/

uint32_t _DRV_TMR_MAKE_NAME( TickFrequencyGet )( void )
{
    uint32_t ticksUsed , ticksPerMs , prescale, tmrBaseFreq ;

    /* Get the Base frequency from the SYS CLK module */
    tmrBaseFreq = SYS_CLK_ClockFrequencyGet( CLK_PERIPHERAL );

    /* Get the ticks to be counted for calculating the freq */
    ticksUsed = _DRV_TMR_OBJ( DRV_TMR_INDEX , timerPeriod);

    ticksPerMs = ( ( uint32_t ) tmrBaseFreq / 1000 ) ;
    /* PreScale Used */
    if( PLIB_TMR_ExistsPrescale( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId ) ) ) )
    {
        prescale = PLIB_TMR_PrescaleDivisorGet( _DRV_TMR_PERIPHERAL_ID_GET(_DRV_TMR_OBJ( DRV_TMR_INDEX , tmrId)), _DRV_TMR_OBJ( DRV_TMR_INDEX , prescale) );
    }
    else
    {
        prescale = 1;
    }

    /* Considering the prescale information*/
    ticksPerMs = ticksPerMs / prescale ;

    return ( ( 1000 / (ticksUsed / ticksPerMs) ) ) ;

} /* DRV_TMR_TickFrequencyGet */


//******************************************************************************
/* Function:
    unsigned int DRV_TMR_VersionGet( const SYS_MODULE_INDEX drvIndex )

  Summary:
    Gets the Timer driver version in numerical format.

  Description:
    This function gets the Timer driver version. The version is encoded as
    major * 10000 + minor * 100 + patch. The stringed version can be obtained
    using DRV_TMR_VersionStrGet().

  Parameters:
    None.

  Returns:
    Current driver version in numerical format.
*/

unsigned int _DRV_TMR_MAKE_NAME( VersionGet )( void )
{
    return( ( _DRV_TMR_VERSION_MAJOR * 10000 ) +
            ( _DRV_TMR_VERSION_MINOR * 100 ) +
            ( _DRV_TMR_VERSION_PATCH ) );

} /* DRV_TMR_VersionGet */


// *****************************************************************************
/* Function:
    char * DRV_TMR_VersionStrGet( const SYS_MODULE_INDEX drvIndex )

  Summary:
    Gets the Timer driver version in string format.

  Description:
    This function gets the Timer driver version. The version is returned as
    major.minor.path[type], where type is optional. The numerical version can
    be obtained using DRV_TMR_VersionGet().

  Parameters:
    None.

  Returns:
    Current Timer driver version in the string format.

  Remarks:
    None.
*/

char * _DRV_TMR_MAKE_NAME( VersionStrGet )( void )
{
    return _DRV_TMR_VERSION_STR;

} /* DRV_TMR_VersionStrGet */


/*******************************************************************************
End of File
*/

