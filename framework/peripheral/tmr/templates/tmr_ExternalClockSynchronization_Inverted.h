/*******************************************************************************
  TMR Peripheral Library Template Implementation

  File Name:
    tmr_ExternalClockSynchronization_Inverted.h

  Summary:
    TMR PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ExternalClockSynchronization
    and its Variant : Inverted
    For following APIs :
        PLIB_TMR_ExternalClockSynchronizationEnable
        PLIB_TMR_ExternalClockSynchronizationDisable
        PLIB_TMR_ExistsExternalClockSynchronization

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

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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

#ifndef _TMR_EXTERNALCLOCKSYNCHRONIZATION_INVERTED_H
#define _TMR_EXTERNALCLOCKSYNCHRONIZATION_INVERTED_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _TMR_EXTERNAL_CLOCK_SYNC_INVERTED_VREG(index)

  MASKs: 
    _TMR_EXTERNAL_CLOCK_SYNC_INVERTED_MASK(index)

  POSs: 
    _TMR_EXTERNAL_CLOCK_SYNC_INVERTED_POS(index)

  LENs: 
    _TMR_EXTERNAL_CLOCK_SYNC_INVERTED_LEN(index)

*/


//******************************************************************************
/* Function :  TMR_ExternalClockSynchronizationEnable_Inverted

  Summary:
    Implements Inverted variant of PLIB_TMR_ExternalClockSynchronizationEnable 

  Description:
    This template implements the Inverted variant of the PLIB_TMR_ExternalClockSynchronizationEnable function.
*/

PLIB_TEMPLATE void TMR_ExternalClockSynchronizationEnable_Inverted( TMR_MODULE_ID index )
{
    _SFR_BIT_SET( _TMR_EXTERNAL_CLOCK_SYNC_INVERTED_VREG( index ),
                  _TMR_EXTERNAL_CLOCK_SYNC_INVERTED_POS( index ) );
}


//******************************************************************************
/* Function :  TMR_ExternalClockSynchronizationDisable_Inverted

  Summary:
    Implements Inverted variant of PLIB_TMR_ExternalClockSynchronizationDisable 

  Description:
    This template implements the Inverted variant of the PLIB_TMR_ExternalClockSynchronizationDisable function.
*/

PLIB_TEMPLATE void TMR_ExternalClockSynchronizationDisable_Inverted( TMR_MODULE_ID index )
{
    _SFR_BIT_CLEAR( _TMR_EXTERNAL_CLOCK_SYNC_INVERTED_VREG( index ),
                    _TMR_EXTERNAL_CLOCK_SYNC_INVERTED_POS( index ) );
}


//******************************************************************************
/* Function :  TMR_ExistsExternalClockSynchronization_Inverted

  Summary:
    Implements Inverted variant of PLIB_TMR_ExistsExternalClockSynchronization

  Description:
    This template implements the Inverted variant of the PLIB_TMR_ExistsExternalClockSynchronization function.
*/

PLIB_TEMPLATE bool TMR_ExistsExternalClockSynchronization_Inverted( TMR_MODULE_ID index )
{
    return true;
}


#endif /*_TMR_EXTERNALCLOCKSYNCHRONIZATION_INVERTED_H*/

/******************************************************************************
 End of File
*/

