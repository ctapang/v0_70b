/*******************************************************************************
  EBI Peripheral Library Template Implementation

  File Name:
    ebi_AddressPinEnableBits_Default.h

  Summary:
    EBI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : AddressPinEnableBits
    and its Variant : Default
    For following APIs :
        PLIB_EBI_AddressPinEnableBitsSet
        PLIB_EBI_ExistsAddressPinEnableBits

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

#ifndef _EBI_ADDRESSPINENABLEBITS_DEFAULT_H
#define _EBI_ADDRESSPINENABLEBITS_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _EBI_EBIA0EN_VREG(index)

  MASKs: 
    _EBI_EBIA0EN_MASK(index)

  POSs: 
    _EBI_EBIA0EN_POS(index)

  LENs: 
    _EBI_EBIA0EN_LEN(index)

*/


//******************************************************************************
/* Function :  EBI_AddressPinEnableBitsSet_Default

  Summary:
    Implements Default variant of PLIB_EBI_AddressPinEnableBitsSet 

  Description:
    This template implements the Default variant of the PLIB_EBI_AddressPinEnableBitsSet function.
*/

PLIB_TEMPLATE void EBI_AddressPinEnableBitsSet_Default( EBI_MODULE_ID index , EBI_ADDRESS_PORT AddressPort )
{
    uint32_t tmp;
    tmp = _SFR_BIT_READ(_EBI_EBIPINEN_VREG(index),_EBI_EBIPINEN_POS(index));
    tmp = tmp << 31;
    tmp = tmp & 0x80000000;
    _SFR_WRITE(_EBI_EBIA0EN_VREG(index),  (tmp| AddressPort));

}


//******************************************************************************
/* Function :  EBI_ExistsAddressPinEnableBits_Default

  Summary:
    Implements Default variant of PLIB_EBI_ExistsAddressPinEnableBits

  Description:
    This template implements the Default variant of the PLIB_EBI_ExistsAddressPinEnableBits function.
*/

PLIB_TEMPLATE bool EBI_ExistsAddressPinEnableBits_Default( EBI_MODULE_ID index )
{
    return true;
}


#endif /*_EBI_ADDRESSPINENABLEBITS_DEFAULT_H*/

/******************************************************************************
 End of File
*/

