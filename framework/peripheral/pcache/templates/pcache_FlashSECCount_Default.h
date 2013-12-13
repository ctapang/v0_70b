/*******************************************************************************
  PCACHE Peripheral Library Template Implementation

  File Name:
    pcache_FlashSECCount_Default.h

  Summary:
    PCACHE PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : FlashSECCount
    and its Variant : Default
    For following APIs :
        PLIB_PCACHE_ExistsFlashSECCount
        PLIB_PCACHE_FlashSECCountSet
        PLIB_PCACHE_FlashSECCountGet

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

#ifndef _PCACHE_FLASHSECCOUNT_DEFAULT_H
#define _PCACHE_FLASHSECCOUNT_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _PCACHE_FLASH_SEC_COUNT_VREG(index)

  MASKs: 
    _PCACHE_FLASH_SEC_COUNT_MASK(index)

  POSs: 
    _PCACHE_FLASH_SEC_COUNT_POS(index)

  LENs: 
    _PCACHE_FLASH_SEC_COUNT_LEN(index)

*/


//******************************************************************************
/* Function :  PCACHE_ExistsFlashSECCount_Default

  Summary:
    Implements Default variant of PLIB_PCACHE_ExistsFlashSECCount

  Description:
    This template implements the Default variant of the PLIB_PCACHE_ExistsFlashSECCount function.
*/

PLIB_TEMPLATE bool PCACHE_ExistsFlashSECCount_Default( PCACHE_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  PCACHE_FlashSECCountSet_Default

  Summary:
    Implements Default variant of PLIB_PCACHE_FlashSECCountSet 

  Description:
    This template implements the Default variant of the PLIB_PCACHE_FlashSECCountSet function.
*/

PLIB_TEMPLATE void PCACHE_FlashSECCountSet_Default( PCACHE_MODULE_ID index , uint8_t count )
{
    _SFR_FIELD_WRITE(_PCACHE_FLASH_SEC_COUNT_VREG(index),
                     _PCACHE_FLASH_SEC_COUNT_MASK(index),
                     _PCACHE_FLASH_SEC_COUNT_POS(index), count);
}


//******************************************************************************
/* Function :  PCACHE_FlashSECCountGet_Default

  Summary:
    Implements Default variant of PLIB_PCACHE_FlashSECCountGet 

  Description:
    This template implements the Default variant of the PLIB_PCACHE_FlashSECCountGet function.
*/

PLIB_TEMPLATE uint8_t PCACHE_FlashSECCountGet_Default( PCACHE_MODULE_ID index )
{
    return _SFR_FIELD_READ(_PCACHE_FLASH_SEC_COUNT_VREG(index),
                           _PCACHE_FLASH_SEC_COUNT_MASK(index),
                           _PCACHE_FLASH_SEC_COUNT_POS(index));
}


#endif /*_PCACHE_FLASHSECCOUNT_DEFAULT_H*/

/******************************************************************************
 End of File
*/
