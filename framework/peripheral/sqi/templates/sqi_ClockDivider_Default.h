/*******************************************************************************
  SQI Peripheral Library Template Implementation

  File Name:
    sqi_ClockDivider_Default.h

  Summary:
    SQI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ClockDivider
    and its Variant : Default
    For following APIs :
        PLIB_SQI_ClockDividerSet
        PLIB_SQI_ExistsClockDivider

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

#ifndef _SQI_CLOCKDIVIDER_DEFAULT_H
#define _SQI_CLOCKDIVIDER_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are

  VREGs:
    _SQI_CLOCK_DIVIDER_VREG(index)

  MASKs:
    _SQI_CLOCK_DIVIDER_MASK(index)

  POSs:
    _SQI_CLOCK_DIVIDER_POS(index)

  LENs:
    _SQI_CLOCK_DIVIDER_LEN(index)

*/


//******************************************************************************
/* Function :  SQI_ClockDividerSet_Default

  Summary:
    Implements Default variant of PLIB_SQI_ClockDividerSet

  Description:
    This template implements the Default variant of the PLIB_SQI_ClockDividerSet function.
*/

PLIB_TEMPLATE void SQI_ClockDividerSet_Default( SQI_MODULE_ID index , SQI_CLK_DIV clkDivider )
{
	switch (clkDivider)
	{
		case CLK_DIV_256:
			_SFR_FIELD_WRITE (_SQI_CLOCK_DIVIDER_VREG(index),
							  _SQI_CLOCK_DIVIDER_MASK(index),
							  _SQI_CLOCK_DIVIDER_POS(index),
							  CLK_DIV_256);
		break;
		case CLK_DIV_128:
			_SFR_FIELD_WRITE (_SQI_CLOCK_DIVIDER_VREG(index),
							  _SQI_CLOCK_DIVIDER_MASK(index),
							  _SQI_CLOCK_DIVIDER_POS(index),
							  CLK_DIV_128);
		break;
		case CLK_DIV_64:
			_SFR_FIELD_WRITE (_SQI_CLOCK_DIVIDER_VREG(index),
							  _SQI_CLOCK_DIVIDER_MASK(index),
							  _SQI_CLOCK_DIVIDER_POS(index),
							  CLK_DIV_64);
		break;
		case CLK_DIV_32:
			_SFR_FIELD_WRITE (_SQI_CLOCK_DIVIDER_VREG(index),
							  _SQI_CLOCK_DIVIDER_MASK(index),
							  _SQI_CLOCK_DIVIDER_POS(index),
							  CLK_DIV_32);
		break;
		case CLK_DIV_16:
			_SFR_FIELD_WRITE (_SQI_CLOCK_DIVIDER_VREG(index),
							  _SQI_CLOCK_DIVIDER_MASK(index),
							  _SQI_CLOCK_DIVIDER_POS(index),
							  CLK_DIV_16);
		break;
		case CLK_DIV_8:
			_SFR_FIELD_WRITE (_SQI_CLOCK_DIVIDER_VREG(index),
							  _SQI_CLOCK_DIVIDER_MASK(index),
							  _SQI_CLOCK_DIVIDER_POS(index),
							  CLK_DIV_8);
		break;
		case CLK_DIV_4:
			_SFR_FIELD_WRITE (_SQI_CLOCK_DIVIDER_VREG(index),
							  _SQI_CLOCK_DIVIDER_MASK(index),
							  _SQI_CLOCK_DIVIDER_POS(index),
							  CLK_DIV_4);
		break;
		case CLK_DIV_2:
			_SFR_FIELD_WRITE (_SQI_CLOCK_DIVIDER_VREG(index),
							  _SQI_CLOCK_DIVIDER_MASK(index),
							  _SQI_CLOCK_DIVIDER_POS(index),
							  CLK_DIV_2);
		break;
		case CLK_DIV_1:
			_SFR_FIELD_WRITE (_SQI_CLOCK_DIVIDER_VREG(index),
							  _SQI_CLOCK_DIVIDER_MASK(index),
							  _SQI_CLOCK_DIVIDER_POS(index),
							  CLK_DIV_1);
		break;
		default:
			_SFR_FIELD_WRITE (_SQI_CLOCK_DIVIDER_VREG(index),
							  _SQI_CLOCK_DIVIDER_MASK(index),
							  _SQI_CLOCK_DIVIDER_POS(index),
							  CLK_DIV_1);

	}
}


//******************************************************************************
/* Function :  SQI_ExistsClockDivider_Default

  Summary:
    Implements Default variant of PLIB_SQI_ExistsClockDivider

  Description:
    This template implements the Default variant of the PLIB_SQI_ExistsClockDivider function.
*/

PLIB_TEMPLATE bool SQI_ExistsClockDivider_Default( SQI_MODULE_ID index )
{
    return true;
}


#endif /*_SQI_CLOCKDIVIDER_DEFAULT_H*/

/******************************************************************************
 End of File
*/

