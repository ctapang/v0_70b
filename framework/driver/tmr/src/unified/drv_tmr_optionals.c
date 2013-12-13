/*******************************************************************************
  TMR Device Driver Definition for the optional features

  Company:
    Microchip Technology Incorported

  FileName:
    drv_tmr_optionals.c

  Summary:
    TMR Device Driver Definition for the optional features

  Description:
    The TMR device driver provides a simple interface to manage the TMR modules
    on Microchip microcontrollers.  This file defines the interface definition
    for the TMR driver in optional feature mode.
    While building the driver from source, use this file in the build when
    DRV_TMR_GET_FREQUENCIES_ENABLE is defined in the system configuration.
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
   uint32_t DRV_TMR_OperatingFrequencyGet ( DRV_HANDLE handle,
                                            uint32_t tmrBaseFreq)

  Summary:
    Provides the timer running frequency

  Description:
    This routine provides the timer running frequency

  Parameters:
    handle      - A valid open-instance handle, returned from the driver
                  open routine
    tmrBaseFreq - TMR peripheral base frequency

  Returns:
    32bit value corresponding to the timer running frequency
*/

uint32_t _DRV_TMR_MAKE_NAME ( OperatingFrequencyGet )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_TMR_MC_ARG_COMMA( DRV_HANDLE handle )
    uint32_t tmrBaseFreq
)
{
    _DRV_TMR_MC( DRV_TMR_CLIENT_OBJ clientObj = (DRV_TMR_CLIENT_OBJ) 0 );
    _DRV_TMR_DYN( DRV_TMR_OBJ dObj = (DRV_TMR_OBJ) 0 );
    uint32_t prescale ;

    /* Get the Client object from the handle passed */
    _DRV_TMR_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_TMR_MC_Test( clientObj < DRV_TMR_INSTANCES_NUMBER), "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_TMR_MULTI_CLIENT_DOBJ ( clientObj , dObj ) ;

    /* PreScale Used */
    if( PLIB_TMR_ExistsPrescale( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( dObj , tmrId ) ) ) )
    {
        prescale = PLIB_TMR_PrescaleDivisorGet( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( dObj , tmrId ) ), _DRV_TMR_OBJ( dObj , prescale ) );
    }
    else
    {
        prescale = 1;
    }

    return (tmrBaseFreq / prescale ) ;

} /* DRV_TMR_OperatingFrequencyGet */


/******************************************************************************
  Function:
   uint32_t DRV_TMR_TickFrequencyGet ( DRV_HANDLE handle,
                                       uint32_t tmrBaseFreq)

  Summary:
    Provides the timer tick frequency

  Description:
    This routine provides the timer tick frequency

  Parameters:
    handle       - A valid open-instance handle, returned from the driver's
                   open routine
    tmrBaseFreq - TMR peripheral base frequency
 
  Returns:
    32bit value corresponding to the running tick frequency
    say, if the tick period is 100ms, then the return value would be 10Hz
*/

uint32_t _DRV_TMR_MAKE_NAME ( TickFrequencyGet )
(
    /* Function Parameters: (Multi client arguments are removed from single client builds.) */
    _DRV_TMR_MC_ARG_COMMA( DRV_HANDLE handle )
    uint32_t tmrBaseFreq
)
{
    _DRV_TMR_MC( DRV_TMR_CLIENT_OBJ clientObj = (DRV_TMR_CLIENT_OBJ) 0 );
    _DRV_TMR_DYN( DRV_TMR_OBJ dObj = (DRV_TMR_OBJ) 0 );
    uint32_t countMax , ticksUsed , ticksPerMs , prescale ;

    /* Get the Client object from the handle passed */
    _DRV_TMR_MC( clientObj = handle );

    /* Check for the Client validity */
    SYS_ASSERT( _DRV_TMR_MC_Test( clientObj < DRV_TMR_INSTANCES_NUMBER), "Invalid Client Object" ) ;

    /* Get the driver object from the client */
    _DRV_TMR_MULTI_CLIENT_DOBJ ( clientObj , dObj ) ;

    /* Get the ticks to be counted for calculating the freq */
    ticksUsed = _DRV_TMR_OBJ ( dObj , timerPeriod ) ;

    ticksPerMs = ( ( uint32_t ) tmrBaseFreq / 1000 ) ;
    /* PreScale Used */
    if( PLIB_TMR_ExistsPrescale( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( dObj , tmrId ) ) ) )
    {
        prescale = PLIB_TMR_PrescaleDivisorGet( _DRV_TMR_PERIPHERAL_ID_GET( _DRV_TMR_OBJ( dObj , tmrId ), _DRV_TMR_OBJ( dObj , prescale ) );
    }
    else
    {
        prescale = 1;
    }

    /* Considering the prescale information*/
    ticksPerMs = ticksPerMs / prescale ;

    return ( ( 1000 / (ticksUsed / ticksPerMs) ) ) ;

} /* DRV_TMR_TickFrequencyGet */


/*******************************************************************************
End of File
*/

