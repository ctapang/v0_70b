/*******************************************************************************
  TMR Device Driver Definition for the alarm features

  Company:
    Microchip Technology Incorported

  FileName:
    drv_tmr_alarm.c

  Summary:
    TMR Device Driver Definition for the alarm features

  Description:
    The TMR device driver provides a simple interface to manage the TMR modules
    on Microchip microcontrollers.  This file defines the interface definition
    for the TMR driver in alarm feature mode.
    While building the driver from source, use this file in the build when
    DRV_TMR_ALARM_ENABLE is defined in the system configuration.
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
// Section: Generic File includes
// *****************************************************************************
// *****************************************************************************


#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "tmr/src/drv_tmr_local.h"


// *****************************************************************************
// *****************************************************************************
// Section: File Scope Functions
// *****************************************************************************
// *****************************************************************************

/******************************************************************************
  Function:
    void DRV_TMR_AlarmSet ( DRV_HANDLE handle,
                            const DRV_TMR_ALARM_CONFIG *config)

  Summary:
    Registers an Alarm with the client

  Description:
    Registers an Alarm with the client

  Parameters:
    handle      - A valid open-instance handle, returned from the driver's
                  open routine
    config      - Pointer to the alarm configuration structure containing any 
                  data necessary to initialize TMR Alarms.

  Returns:
    None
*/

void _DRV_TMR_MAKE_NAME( AlarmSet )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_TMR_MC_ARG_COMMA( DRV_HANDLE handle )
    const DRV_TMR_ALARM_CONFIG *config
)
{
    _DRV_TMR_MC( DRV_TMR_CLIENT_OBJ clientObj = (DRV_TMR_CLIENT_OBJ) 0 );
    _DRV_TMR_DYN( DRV_TMR_OBJ dObj = (DRV_TMR_OBJ) 0 );

    /* Get the Client object from the handle passed */
    _DRV_TMR_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_TMR_MC_Test( clientObj < DRV_TMR_INSTANCES_NUMBER), "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_TMR_MULTI_CLIENT_DOBJ ( clientObj , dObj ) ;

    _DRV_TMR_OBJ ( dObj , alarmInUse ) = true ;

    /* update the HW Instance with the callback associated with alarm */
    _DRV_TMR_OBJ ( dObj , alarmCallback ) = config->callback ;

    /* Clear the alarm counter */
    _DRV_TMR_OBJ ( dObj , alarmCount ) = 0 ;

} /* DRV_TMR_AlarmSet */


/******************************************************************************
  Function:
    uint32_t DRV_TMR_AlarmCountGet ( DRV_HANDLE handle )

  Summary:
    Returns the number of times alarm is generated since the last time it was
    cleared

  Description:
    Returns the number of times alarm is generated since the last time it was
    cleared

  Parameters:
    handle      - A valid open-instance handle, returned from the driver's
                  open routine

  Returns:
    alarm count value
*/

unsigned int _DRV_TMR_MAKE_NAME ( AlarmCountGet )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_TMR_MC_ARG( DRV_HANDLE handle )
)
{
    _DRV_TMR_MC( DRV_TMR_CLIENT_OBJ clientObj = (DRV_TMR_CLIENT_OBJ) 0 );
    _DRV_TMR_DYN( DRV_TMR_OBJ dObj = (DRV_TMR_OBJ) 0 );
    uint32_t alCount;

    /* Get the Client object from the handle passed */
    _DRV_TMR_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_TMR_MC_Test( clientObj < DRV_TMR_INSTANCES_NUMBER), "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_TMR_MULTI_CLIENT_DOBJ ( clientObj , dObj ) ;

    //for (alarmInd = 0; alarmInd < hwInstance->alarmObj; alarmInd++)
    {
        /* Update the counter value */
        alCount = _DRV_TMR_OBJ ( dObj , alarmCount ) ;
    }

    return alCount;

} /* DRV_TMR_AlarmCountGet */


/******************************************************************************
  Function:
    void DRV_TMR_AlarmCountClear ( DRV_HANDLE handle )

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

void _DRV_TMR_MAKE_NAME ( AlarmCountClear )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_TMR_MC_ARG( DRV_HANDLE handle )
)
{
    _DRV_TMR_MC( DRV_TMR_CLIENT_OBJ clientObj = (DRV_TMR_CLIENT_OBJ) 0 );
    _DRV_TMR_DYN( DRV_TMR_OBJ dObj = (DRV_TMR_OBJ) 0 );

    /* Get the Client object from the handle passed */
    _DRV_TMR_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_TMR_MC_Test( clientObj < DRV_TMR_INSTANCES_NUMBER), "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_TMR_MULTI_CLIENT_DOBJ ( clientObj , dObj ) ;

    //for (alarmInd = 0; alarmInd < hwInstance->alarmObj; alarmInd++)
    {
        /* Clear the Alarm counter */
        _DRV_TMR_OBJ ( dObj , alarmCount ) = 0 ;
    }

} /* DRV_TMR_AlarmCountClear */


/*******************************************************************************
End of File
*/

