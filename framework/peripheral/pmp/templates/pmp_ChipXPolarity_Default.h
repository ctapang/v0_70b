/*******************************************************************************
  PMP Peripheral Library Template Implementation

  File Name:
    pmp_ChipXPolarity_Default.h

  Summary:
    PMP PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ChipXPolarity
    and its Variant : Default
    For following APIs :
        PLIB_PMP_ExistsChipXPolarity
        PLIB_PMP_ChipSelectXPolaritySelect

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

#ifndef _PMP_CHIPXPOLARITY_DEFAULT_H
#define _PMP_CHIPXPOLARITY_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _PMP_CS1_POLARITY_VREG(index)

  MASKs: 
    _PMP_CS1_POLARITY_MASK(index)

  POSs: 
    _PMP_CS1_POLARITY_POS(index)

  LENs: 
    _PMP_CS1_POLARITY_LEN(index)

*/


//******************************************************************************
/* Function :  PMP_ExistsChipXPolarity_Default

  Summary:
    Implements Default variant of PLIB_PMP_ExistsChipXPolarity

  Description:
    This template implements the Default variant of the PLIB_PMP_ExistsChipXPolarity function.
*/

PLIB_TEMPLATE bool PMP_ExistsChipXPolarity_Default( PMP_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  PMP_ChipSelectXPolaritySelect_Default

  Summary:
    Implements Default variant of PLIB_PMP_ChipSelectXPolaritySelect 

  Description:
    This template implements the Default variant of the PLIB_PMP_ChipSelectXPolaritySelect function.
*/

PLIB_TEMPLATE void PMP_ChipSelectXPolaritySelect_Default( PMP_MODULE_ID index , PMP_CHIP_SELECT chipSelect , PMP_POLARITY_LEVEL polarity )
{
    _SFR_FIELD_WRITE( 	_PMP_CS1_POLARITY_VREG( index ),
						( _PMP_CS1_POLARITY_MASK( index ) << chipSelect ),
						( _PMP_CS1_POLARITY_POS(index) + chipSelect ),
						( polarity ));
}


#endif /*_PMP_CHIPXPOLARITY_DEFAULT_H*/

/******************************************************************************
 End of File
*/

