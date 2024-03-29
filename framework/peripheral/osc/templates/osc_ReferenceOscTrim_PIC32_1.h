/*******************************************************************************
  OSC Peripheral Library Template Implementation

  File Name:
    osc_ReferenceOscTrim_PIC32_1.h

  Summary:
    OSC PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ReferenceOscTrim
    and its Variant : PIC32_1
    For following APIs :
        PLIB_OSC_ExistsReferenceOscTrim
        PLIB_OSC_ReferenceOscTrimSet

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

#ifndef _OSC_REFERENCEOSCTRIM_PIC32_1_H
#define _OSC_REFERENCEOSCTRIM_PIC32_1_H

// *****************************************************************************
/* Reference clock out trim type.

  Summary:
    Defines Reference clock out trim type.

  Description:
    This macro defines the Reference clock out trim type.

  Remarks:
    None
*/

#define OSC_REF_TRIM_TYPE						SFR_TYPE
//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _OSC_REF_OUTPUT_TRIM_VREG(index)

  MASKs: 
    _OSC_REF_OUTPUT_TRIM_MASK(index)

  POSs: 
    _OSC_REF_OUTPUT_TRIM_POS(index)

  LENs: 
    _OSC_REF_OUTPUT_TRIM_LEN(index)

*/


//******************************************************************************
/* Function :  OSC_ExistsReferenceOscTrim_PIC32_1

  Summary:
    Implements PIC32_1 variant of PLIB_OSC_ExistsReferenceOscTrim

  Description:
    This template implements the PIC32_1 variant of the PLIB_OSC_ExistsReferenceOscTrim function.
*/

PLIB_TEMPLATE bool OSC_ExistsReferenceOscTrim_PIC32_1( OSC_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  OSC_ReferenceOscTrimSet_PIC32_1

  Summary:
    Implements PIC32_1 variant of PLIB_OSC_ReferenceOscTrimSet 

  Description:
    This template implements the PIC32_1 variant of the PLIB_OSC_ReferenceOscTrimSet function.
*/

PLIB_TEMPLATE void OSC_ReferenceOscTrimSet_PIC32_1( OSC_MODULE_ID index , OSC_REFERENCE referenceOsc , OSC_REF_TRIM_TYPE trimValue )
{
     _SFR_FIELD_WRITE(_OSC_REF_OUTPUT_TRIM_VREG(index),
						_OSC_REF_OUTPUT_TRIM_MASK(index),
						_OSC_REF_OUTPUT_TRIM_POS(index) ,
						trimValue );
}


#endif /*_OSC_REFERENCEOSCTRIM_PIC32_1_H*/

/******************************************************************************
 End of File
*/

