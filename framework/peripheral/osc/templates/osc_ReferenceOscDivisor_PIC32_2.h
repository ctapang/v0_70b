/*******************************************************************************
  OSC Peripheral Library Template Implementation

  File Name:
    osc_ReferenceOscDivisor_PIC32_2.h

  Summary:
    OSC PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ReferenceOscDivisor
    and its Variant : PIC32_2
    For following APIs :
        PLIB_OSC_ExistsReferenceOscDivisor
        PLIB_OSC_ReferenceOscDivisorValueSet

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

#ifndef _OSC_REFERENCEOSCDIVISOR_PIC32_2_H
#define _OSC_REFERENCEOSCDIVISOR_PIC32_2_H

// *****************************************************************************
/* Reference divisor type

  Summary:
    Defines Reference clock devisor type.

  Description:
    This macro defines Reference clock divisor type.

  Remarks:
    None
*/

#define OSC_REF_DIVISOR_TYPE  				SFR_TYPE

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _OSC_REF_CLK_OUTPUT_DIV_1_VREG(index)
    _OSC_REF_CLK_OUTPUT_DIV_2_VREG(index)
    _OSC_REF_CLK_OUTPUT_DIV_3_VREG(index)
    _OSC_REF_CLK_OUTPUT_DIV_4_VREG(index)

  MASKs: 
    _OSC_REF_CLK_OUTPUT_DIV_1_MASK(index)
    _OSC_REF_CLK_OUTPUT_DIV_2_MASK(index)
    _OSC_REF_CLK_OUTPUT_DIV_3_MASK(index)
    _OSC_REF_CLK_OUTPUT_DIV_4_MASK(index)

  POSs: 
    _OSC_REF_CLK_OUTPUT_DIV_1_POS(index)
    _OSC_REF_CLK_OUTPUT_DIV_2_POS(index)
    _OSC_REF_CLK_OUTPUT_DIV_3_POS(index)
    _OSC_REF_CLK_OUTPUT_DIV_4_POS(index)

  LENs: 
    _OSC_REF_CLK_OUTPUT_DIV_1_LEN(index)
    _OSC_REF_CLK_OUTPUT_DIV_2_LEN(index)
    _OSC_REF_CLK_OUTPUT_DIV_3_LEN(index)
    _OSC_REF_CLK_OUTPUT_DIV_4_LEN(index)

*/


//******************************************************************************
/* Function :  OSC_ExistsReferenceOscDivisor_PIC32_2

  Summary:
    Implements PIC32_2 variant of PLIB_OSC_ExistsReferenceOscDivisor

  Description:
    This template implements the PIC32_2 variant of the PLIB_OSC_ExistsReferenceOscDivisor function.
*/

PLIB_TEMPLATE bool OSC_ExistsReferenceOscDivisor_PIC32_2( OSC_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  OSC_ReferenceOscDivisorValueSet_PIC32_2

  Summary:
    Implements PIC32_2 variant of PLIB_OSC_ReferenceOscDivisorValueSet 

  Description:
    This template implements the PIC32_2 variant of the PLIB_OSC_ReferenceOscDivisorValueSet function.
*/

PLIB_TEMPLATE void OSC_ReferenceOscDivisorValueSet_PIC32_2( OSC_MODULE_ID index , OSC_REFERENCE referenceOsc , OSC_REF_DIVISOR_TYPE refOscValue )
{
	switch(referenceOsc)
	{
    case OSC_REFERENCE_1: 	
    	_SFR_FIELD_WRITE(_OSC_REF_CLK_OUTPUT_DIV_1_VREG(index),
						 _OSC_REF_CLK_OUTPUT_DIV_1_MASK(index),
						 _OSC_REF_CLK_OUTPUT_DIV_1_POS(index) ,
						 refOscValue );
		break;
		
	case OSC_REFERENCE_2: 	
		_SFR_FIELD_WRITE(_OSC_REF_CLK_OUTPUT_DIV_2_VREG(index),
						 _OSC_REF_CLK_OUTPUT_DIV_2_MASK(index),
						 _OSC_REF_CLK_OUTPUT_DIV_2_POS(index) ,
						 refOscValue );
		break;
		
	case OSC_REFERENCE_3: 	
		_SFR_FIELD_WRITE(_OSC_REF_CLK_OUTPUT_DIV_3_VREG(index),
						 _OSC_REF_CLK_OUTPUT_DIV_3_MASK(index),
						 _OSC_REF_CLK_OUTPUT_DIV_3_POS(index) ,
						 refOscValue );
		break;
		
	case OSC_REFERENCE_4: 	
		_SFR_FIELD_WRITE(_OSC_REF_CLK_OUTPUT_DIV_4_VREG(index),
						 _OSC_REF_CLK_OUTPUT_DIV_4_MASK(index),
						 _OSC_REF_CLK_OUTPUT_DIV_4_POS(index) ,
						 refOscValue );
		break;
	}
}


#endif /*_OSC_REFERENCEOSCDIVISOR_PIC32_2_H*/

/******************************************************************************
 End of File
*/

