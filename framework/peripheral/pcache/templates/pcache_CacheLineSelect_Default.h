/*******************************************************************************
  PCACHE Peripheral Library Template Implementation

  File Name:
    pcache_CacheLineSelect_Default.h

  Summary:
    PCACHE PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : CacheLineSelect
    and its Variant : Default
    For following APIs :
        PLIB_PCACHE_ExistsCacheLine
        PLIB_PCACHE_CacheLineSelect
        PLIB_PCACHE_CacheLineDeselect

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

#ifndef _PCACHE_CACHELINESELECT_DEFAULT_H
#define _PCACHE_CACHELINESELECT_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _PCACHE_CACHE_LINE_INDEX_VREG(index)
    _PCACHE_CACHE_LINE_ENABLE_VREG(index)

  MASKs: 
    _PCACHE_CACHE_LINE_INDEX_MASK(index)
    _PCACHE_CACHE_LINE_ENABLE_MASK(index)

  POSs: 
    _PCACHE_CACHE_LINE_INDEX_POS(index)
    _PCACHE_CACHE_LINE_ENABLE_POS(index)

  LENs: 
    _PCACHE_CACHE_LINE_INDEX_LEN(index)
    _PCACHE_CACHE_LINE_ENABLE_LEN(index)

*/


//******************************************************************************
/* Function :  PCACHE_ExistsCacheLine_Default

  Summary:
    Implements Default variant of PLIB_PCACHE_ExistsCacheLine

  Description:
    This template implements the Default variant of the PLIB_PCACHE_ExistsCacheLine function.
*/

PLIB_TEMPLATE bool PCACHE_ExistsCacheLine_Default( PCACHE_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  PCACHE_CacheLineSelect_Default

  Summary:
    Implements Default variant of PLIB_PCACHE_CacheLineSelect 

  Description:
    This template implements the Default variant of the PLIB_PCACHE_CacheLineSelect function.
*/

PLIB_TEMPLATE void PCACHE_CacheLineSelect_Default( PCACHE_MODULE_ID index , uint32_t cache_line )
{
    _SFR_FIELD_WRITE(_PCACHE_CACHE_LINE_INDEX_VREG(index),
                     _PCACHE_CACHE_LINE_INDEX_MASK(index),
                     _PCACHE_CACHE_LINE_INDEX_POS(index), cache_line);

    _SFR_BIT_SET(_PCACHE_CACHE_LINE_ENABLE_VREG(index), _PCACHE_CACHE_LINE_ENABLE_POS(index));
}


//******************************************************************************
/* Function :  PCACHE_CacheLineDeselect_Default

  Summary:
    Implements Default variant of PLIB_PCACHE_CacheLineDeselect 

  Description:
    This template implements the Default variant of the PLIB_PCACHE_CacheLineDeselect function.
*/

PLIB_TEMPLATE void PCACHE_CacheLineDeselect_Default( PCACHE_MODULE_ID index , uint32_t cache_line )
{
    _SFR_FIELD_WRITE(_PCACHE_CACHE_LINE_INDEX_VREG(index),
                     _PCACHE_CACHE_LINE_INDEX_MASK(index),
                     _PCACHE_CACHE_LINE_INDEX_POS(index), cache_line);

    _SFR_BIT_CLEAR(_PCACHE_CACHE_LINE_ENABLE_VREG(index), _PCACHE_CACHE_LINE_ENABLE_POS(index));
}


#endif /*_PCACHE_CACHELINESELECT_DEFAULT_H*/

/******************************************************************************
 End of File
*/

