/*******************************************************************************
  OSC Peripheral Library Template Implementation

  File Name:
    osc_PLLInputDivisor_Default.h

  Summary:
    OSC PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : PLLInputDivisor
    and its Variant : Default
    For following APIs :
        PLIB_OSC_ExistsSysPLLInputDivisor
        PLIB_OSC_SysPLLInputDivisorSet
        PLIB_OSC_SysPLLInputDivisorGet

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

#ifndef _OSC_PLLINPUTDIVISOR_DEFAULT_H
#define _OSC_PLLINPUTDIVISOR_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _OSC_OSC_INPUT_DIVISOR_VREG(index)
    _OSC_OSC_REGISTER_LOCK_VREG(index)

  MASKs: 
    _OSC_OSC_INPUT_DIVISOR_MASK(index)
    _OSC_OSC_REGISTER_LOCK_MASK(index)

  POSs: 
    _OSC_OSC_INPUT_DIVISOR_POS(index)
    _OSC_OSC_REGISTER_LOCK_POS(index)

  LENs: 
    _OSC_OSC_INPUT_DIVISOR_LEN(index)
    _OSC_OSC_REGISTER_LOCK_LEN(index)

*/


//******************************************************************************
/* Function :  OSC_ExistsSysPLLInputDivisor_Default

  Summary:
    Implements Default variant of PLIB_OSC_ExistsSysPLLInputDivisor

  Description:
    This template implements the Default variant of the PLIB_OSC_ExistsSysPLLInputDivisor function.
*/

PLIB_TEMPLATE bool OSC_ExistsSysPLLInputDivisor_Default( OSC_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  OSC_SysPLLInputDivisorSet_Default

  Summary:
    Implements Default variant of PLIB_OSC_SysPLLInputDivisorSet 

  Description:
    This template implements the Default variant of the PLIB_OSC_SysPLLInputDivisorSet function.
*/

PLIB_TEMPLATE void OSC_SysPLLInputDivisorSet_Default( OSC_MODULE_ID index , OSC_SYSPLL_IN_DIV PLLInDiv )
{
	 _SFR_WRITE(_OSC_OSC_REGISTER_LOCK_VREG(index), 0);
     _SFR_WRITE(_OSC_OSC_REGISTER_LOCK_VREG(index), 0xAA996655);
     _SFR_WRITE(_OSC_OSC_REGISTER_LOCK_VREG(index), 0x556699AA);

    _SFR_FIELD_WRITE(_OSC_OSC_INPUT_DIVISOR_VREG(index),
                     _OSC_OSC_INPUT_DIVISOR_MASK(index),
                     _OSC_OSC_INPUT_DIVISOR_POS(index) ,
                     PLLInDiv);

    _SFR_WRITE(_OSC_OSC_REGISTER_LOCK_VREG(index), 0);
    Nop();
    Nop();
}


//******************************************************************************
/* Function :  OSC_SysPLLInputDivisorGet_Default

  Summary:
    Implements Default variant of PLIB_OSC_SysPLLInputDivisorGet 

  Description:
    This template implements the Default variant of the PLIB_OSC_SysPLLInputDivisorGet function.
*/

PLIB_TEMPLATE OSC_SYSPLL_IN_DIV OSC_SysPLLInputDivisorGet_Default( OSC_MODULE_ID index )
{
     return _SFR_FIELD_READ(_OSC_OSC_INPUT_DIVISOR_VREG(index),
     						_OSC_OSC_INPUT_DIVISOR_MASK(index),
                            _OSC_OSC_INPUT_DIVISOR_POS(index) );
}


#endif /*_OSC_PLLINPUTDIVISOR_DEFAULT_H*/

/******************************************************************************
 End of File
*/

