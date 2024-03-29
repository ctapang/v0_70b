/*******************************************************************************
  EBI Peripheral Library Template Implementation

  File Name:
    ebi_WriteOutputControl_Default.h

  Summary:
    EBI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : WriteOutputControl
    and its Variant : Default
    For following APIs :
        PLIB_EBI_WriteOutputControlSet
        PLIB_EBI_ExistsWriteOutputControl

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

#ifndef _EBI_WRITEOUTPUTCONTROL_DEFAULT_H
#define _EBI_WRITEOUTPUTCONTROL_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _EBI_EBIWEEN_VREG(index)
    _EBI_EBIOEEN_VREG(index)

  MASKs: 
    _EBI_EBIWEEN_MASK(index)
    _EBI_EBIOEEN_MASK(index)

  POSs: 
    _EBI_EBIWEEN_POS(index)
    _EBI_EBIOEEN_POS(index)

  LENs: 
    _EBI_EBIWEEN_LEN(index)
    _EBI_EBIOEEN_LEN(index)

*/


//******************************************************************************
/* Function :  EBI_WriteOutputControlSet_Default

  Summary:
    Implements Default variant of PLIB_EBI_WriteOutputControlSet 

  Description:
    This template implements the Default variant of the PLIB_EBI_WriteOutputControlSet function.
*/

PLIB_TEMPLATE void EBI_WriteOutputControlSet_Default( EBI_MODULE_ID index , bool WriteEnable , bool OutputEnable )
{
    _SFR_BIT_WRITE(_EBI_EBIWEEN_VREG(index), _EBI_EBIWEEN_POS(index), WriteEnable);
    _SFR_BIT_WRITE(_EBI_EBIOEEN_VREG(index), _EBI_EBIOEEN_POS(index), OutputEnable);
}


//******************************************************************************
/* Function :  EBI_ExistsWriteOutputControl_Default

  Summary:
    Implements Default variant of PLIB_EBI_ExistsWriteOutputControl

  Description:
    This template implements the Default variant of the PLIB_EBI_ExistsWriteOutputControl function.
*/

PLIB_TEMPLATE bool EBI_ExistsWriteOutputControl_Default( EBI_MODULE_ID index )
{
    return true;
}


#endif /*_EBI_WRITEOUTPUTCONTROL_DEFAULT_H*/

/******************************************************************************
 End of File
*/

