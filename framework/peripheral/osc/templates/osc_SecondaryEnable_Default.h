/*******************************************************************************
  OSC Peripheral Library Template Implementation

  File Name:
    osc_SecondaryEnable_Default.h

  Summary:
    OSC PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : SecondaryEnable
    and its Variant : Default
    For following APIs :
        PLIB_OSC_ExistsSecondaryEnable
        PLIB_OSC_SecondaryEnable
        PLIB_OSC_SecondaryDisable
        PLIB_OSC_SecondaryIsEnabled

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

#ifndef _OSC_SECONDARYENABLE_DEFAULT_H
#define _OSC_SECONDARYENABLE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _OSC_SECONDARY_ENABLE_VREG(index)
    _OSC_OSC_REGISTER_LOCK_VREG(index)

  MASKs: 
    _OSC_SECONDARY_ENABLE_MASK(index)
    _OSC_OSC_REGISTER_LOCK_MASK(index)

  POSs: 
    _OSC_SECONDARY_ENABLE_POS(index)
    _OSC_OSC_REGISTER_LOCK_POS(index)

  LENs: 
    _OSC_SECONDARY_ENABLE_LEN(index)
    _OSC_OSC_REGISTER_LOCK_LEN(index)

*/


//******************************************************************************
/* Function :  OSC_ExistsSecondaryEnable_Default

  Summary:
    Implements Default variant of PLIB_OSC_ExistsSecondaryEnable

  Description:
    This template implements the Default variant of the PLIB_OSC_ExistsSecondaryEnable function.
*/

PLIB_TEMPLATE bool OSC_ExistsSecondaryEnable_Default( OSC_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  OSC_SecondaryEnable_Default

  Summary:
    Implements Default variant of PLIB_OSC_SecondaryEnable 

  Description:
    This template implements the Default variant of the PLIB_OSC_SecondaryEnable function.
*/

PLIB_TEMPLATE void OSC_SecondaryEnable_Default( OSC_MODULE_ID index )
{
     _SFR_WRITE(_OSC_OSC_REGISTER_LOCK_VREG(index), 0);
     _SFR_WRITE(_OSC_OSC_REGISTER_LOCK_VREG(index), 0xAA996655);
     _SFR_WRITE(_OSC_OSC_REGISTER_LOCK_VREG(index), 0x556699AA);

    _SFR_BIT_SET(_OSC_SECONDARY_ENABLE_VREG(index),
                     _OSC_SECONDARY_ENABLE_POS(index) );
    
    _SFR_WRITE(_OSC_OSC_REGISTER_LOCK_VREG(index), 0);
}


//******************************************************************************
/* Function :  OSC_SecondaryDisable_Default

  Summary:
    Implements Default variant of PLIB_OSC_SecondaryDisable 

  Description:
    This template implements the Default variant of the PLIB_OSC_SecondaryDisable function.
*/

PLIB_TEMPLATE void OSC_SecondaryDisable_Default( OSC_MODULE_ID index )
{
    _SFR_WRITE(_OSC_OSC_REGISTER_LOCK_VREG(index), 0);
    _SFR_WRITE(_OSC_OSC_REGISTER_LOCK_VREG(index), 0xAA996655);
    _SFR_WRITE(_OSC_OSC_REGISTER_LOCK_VREG(index), 0x556699AA);

    _SFR_BIT_CLEAR(_OSC_SECONDARY_ENABLE_VREG(index),
         _OSC_SECONDARY_ENABLE_POS(index) );

    _SFR_WRITE(_OSC_OSC_REGISTER_LOCK_VREG(index), 0);
}


//******************************************************************************
/* Function :  OSC_SecondaryIsEnabled_Default

  Summary:
    Implements Default variant of PLIB_OSC_SecondaryIsEnabled 

  Description:
    This template implements the Default variant of the PLIB_OSC_SecondaryIsEnabled function.
*/

PLIB_TEMPLATE bool OSC_SecondaryIsEnabled_Default( OSC_MODULE_ID index )
{
   return (_SFR_BIT_READ(_OSC_SECONDARY_ENABLE_VREG(index),
                     _OSC_SECONDARY_ENABLE_POS(index) ));
}


#endif /*_OSC_SECONDARYENABLE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

