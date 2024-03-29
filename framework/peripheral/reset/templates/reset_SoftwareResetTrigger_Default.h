/*******************************************************************************
  RESET Peripheral Library Template Implementation

  File Name:
    reset_SoftwareResetTrigger_Default.h

  Summary:
    RESET PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : SoftwareResetTrigger
    and its Variant : Default
    For following APIs :
        PLIB_RESET_ExistsSoftwareResetTrigger
        PLIB_RESET_SoftwareResetEnable

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

#ifndef _RESET_SOFTWARERESETTRIGGER_DEFAULT_H
#define _RESET_SOFTWARERESETTRIGGER_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _RESET_SOFTWARE_RESET_TRIGGER_VREG(index)
    _RESET_REGISTER_LOCK_VREG(index)

  MASKs: 
    _RESET_SOFTWARE_RESET_TRIGGER_MASK(index)
    _RESET_REGISTER_LOCK_MASK(index)

  POSs: 
    _RESET_SOFTWARE_RESET_TRIGGER_POS(index)
    _RESET_REGISTER_LOCK_POS(index)

  LENs: 
    _RESET_SOFTWARE_RESET_TRIGGER_LEN(index)
    _RESET_REGISTER_LOCK_LEN(index)

*/


//******************************************************************************
/* Function :  RESET_ExistsSoftwareResetTrigger_Default

  Summary:
    Implements Default variant of PLIB_RESET_ExistsSoftwareResetTrigger

  Description:
    This template implements the Default variant of the PLIB_RESET_ExistsSoftwareResetTrigger function.
*/

PLIB_TEMPLATE bool RESET_ExistsSoftwareResetTrigger_Default( RESET_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  RESET_SoftwareResetEnable_Default

  Summary:
    Implements Default variant of PLIB_RESET_SoftwareResetEnable 

  Description:
    This template implements the Default variant of the PLIB_RESET_SoftwareResetEnable function.
*/

PLIB_TEMPLATE void RESET_SoftwareResetEnable_Default( RESET_MODULE_ID index )
{
	 _SFR_WRITE(_RESET_REGISTER_LOCK_VREG(index), 0);
     _SFR_WRITE(_RESET_REGISTER_LOCK_VREG(index), 0xAA996655);
     _SFR_WRITE(_RESET_REGISTER_LOCK_VREG(index), 0x556699AA);
	 
     _SFR_BIT_SET(_RESET_SOFTWARE_RESET_TRIGGER_VREG(index),
                     _RESET_SOFTWARE_RESET_TRIGGER_POS(index) );
					 
	 _SFR_READ(_RESET_SOFTWARE_RESET_TRIGGER_VREG(index));
    Nop();
    Nop();
	Nop();
}


#endif /*_RESET_SOFTWARERESETTRIGGER_DEFAULT_H*/

/******************************************************************************
 End of File
*/

