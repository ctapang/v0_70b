/*******************************************************************************
  BMX Peripheral Library Template Implementation

  File Name:
    bmx_ProgramFlashBootSize_Default.h

  Summary:
    BMX PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ProgramFlashBootSize
    and its Variant : Default
    For following APIs :
        PLIB_BMX_ExistsProgramFlashBootSize
        PLIB_BMX_ProgramFlashBootSizeGet

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

#ifndef _BMX_PROGRAMFLASHBOOTSIZE_DEFAULT_H
#define _BMX_PROGRAMFLASHBOOTSIZE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _BMX_BMXBOOTSZ_VREG(index)

  MASKs: 
    _BMX_BMXBOOTSZ_MASK(index)

  POSs: 
    _BMX_BMXBOOTSZ_POS(index)

  LENs: 
    _BMX_BMXBOOTSZ_LEN(index)

*/


//******************************************************************************
/* Function :  BMX_ExistsProgramFlashBootSize_Default

  Summary:
    Implements Default variant of PLIB_BMX_ExistsProgramFlashBootSize

  Description:
    This template implements the Default variant of the PLIB_BMX_ExistsProgramFlashBootSize function.
*/

PLIB_TEMPLATE bool BMX_ExistsProgramFlashBootSize_Default( BMX_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  BMX_ProgramFlashBootSizeGet_Default

  Summary:
    Implements Default variant of PLIB_BMX_ProgramFlashBootSizeGet 

  Description:
    This template implements the Default variant of the PLIB_BMX_ProgramFlashBootSizeGet function.
*/

PLIB_TEMPLATE size_t BMX_ProgramFlashBootSizeGet_Default( BMX_MODULE_ID index )
{
    return _SFR_READ(_BMX_BMXBOOTSZ_VREG(index));
}


#endif /*_BMX_PROGRAMFLASHBOOTSIZE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

