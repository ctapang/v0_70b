/*******************************************************************************
  TMR Peripheral Library Template Implementation

  File Name:
    tmr_Period32Bit_In16BitRegister_high.h

  Summary:
    TMR PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : Period32Bit
    and its Variant : In16BitRegister_high
    For following APIs :
        PLIB_TMR_Period32BitSet
        PLIB_TMR_Period32BitGet
        PLIB_TMR_ExistsPeriod32Bit

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

#ifndef _TMR_PERIOD32BIT_IN16BITREGISTER_HIGH_H
#define _TMR_PERIOD32BIT_IN16BITREGISTER_HIGH_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _TMR_PERIOD_REGISTER_16BIT_HIGH_VREG(index)

  MASKs: 
    _TMR_PERIOD_REGISTER_16BIT_HIGH_MASK(index)

  POSs: 
    _TMR_PERIOD_REGISTER_16BIT_HIGH_POS(index)

  LENs: 
    _TMR_PERIOD_REGISTER_16BIT_HIGH_LEN(index)

*/


//******************************************************************************
/* Function :  TMR_Period32BitSet_In16BitRegister_high

  Summary:
    Implements In16BitRegister_high variant of PLIB_TMR_Period32BitSet 

  Description:
    This template implements the In16BitRegister_high variant of the PLIB_TMR_Period32BitSet function.
*/

PLIB_TEMPLATE void TMR_Period32BitSet_In16BitRegister_high( TMR_MODULE_ID index , uint32_t period )
{
    /* Dummy */
}


//******************************************************************************
/* Function :  TMR_Period32BitGet_In16BitRegister_high

  Summary:
    Implements In16BitRegister_high variant of PLIB_TMR_Period32BitGet 

  Description:
    This template implements the In16BitRegister_high variant of the PLIB_TMR_Period32BitGet function.
*/

PLIB_TEMPLATE uint32_t TMR_Period32BitGet_In16BitRegister_high( TMR_MODULE_ID index )
{
    return 0;
}


//******************************************************************************
/* Function :  TMR_ExistsPeriod32Bit_In16BitRegister_high

  Summary:
    Implements In16BitRegister_high variant of PLIB_TMR_ExistsPeriod32Bit

  Description:
    This template implements the In16BitRegister_high variant of the PLIB_TMR_ExistsPeriod32Bit function.
*/

PLIB_TEMPLATE bool TMR_ExistsPeriod32Bit_In16BitRegister_high( TMR_MODULE_ID index )
{
    return true;
}


#endif /*_TMR_PERIOD32BIT_IN16BITREGISTER_HIGH_H*/

/******************************************************************************
 End of File
*/

