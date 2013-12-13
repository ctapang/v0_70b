/*******************************************************************************
  SQI Peripheral Library Template Implementation

  File Name:
    sqi_XIPModeBytes_Default.h

  Summary:
    SQI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : XIPModeBytes
    and its Variant : Default
    For following APIs :
        PLIB_SQI_XIPModeBytesSet
        PLIB_SQI_XIPModeBytesGet
        PLIB_SQI_ExistsXIPModeBytes

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

#ifndef _SQI_XIPMODEBYTES_DEFAULT_H
#define _SQI_XIPMODEBYTES_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are

  VREGs:
    _SQI_XIP_NUMBER_OF_MODE_BYTES_VREG(index)

  MASKs:
    _SQI_XIP_NUMBER_OF_MODE_BYTES_MASK(index)

  POSs:
    _SQI_XIP_NUMBER_OF_MODE_BYTES_POS(index)

  LENs:
    _SQI_XIP_NUMBER_OF_MODE_BYTES_LEN(index)

*/


//******************************************************************************
/* Function :  SQI_XIPModeBytesSet_Default

  Summary:
    Implements Default variant of PLIB_SQI_XIPModeBytesSet

  Description:
    This template implements the Default variant of the PLIB_SQI_XIPModeBytesSet function.
*/

PLIB_TEMPLATE void SQI_XIPModeBytesSet_Default( SQI_MODULE_ID index , SQI_MODE_BYTES bytes )
{
	switch (bytes)
	{
		case MODE_BYTES_3:
			_SFR_FIELD_WRITE (_SQI_XIP_NUMBER_OF_MODE_BYTES_VREG(index),
							  _SQI_XIP_NUMBER_OF_MODE_BYTES_MASK(index),
							  _SQI_XIP_NUMBER_OF_MODE_BYTES_POS(index),
							  MODE_BYTES_3);
		break;
		case MODE_BYTES_2:
			_SFR_FIELD_WRITE (_SQI_XIP_NUMBER_OF_MODE_BYTES_VREG(index),
							  _SQI_XIP_NUMBER_OF_MODE_BYTES_MASK(index),
							  _SQI_XIP_NUMBER_OF_MODE_BYTES_POS(index),
							  MODE_BYTES_2);
		break;
		case MODE_BYTES_1:
			_SFR_FIELD_WRITE (_SQI_XIP_NUMBER_OF_MODE_BYTES_VREG(index),
							  _SQI_XIP_NUMBER_OF_MODE_BYTES_MASK(index),
							  _SQI_XIP_NUMBER_OF_MODE_BYTES_POS(index),
							  MODE_BYTES_1);
		break;
		case MODE_BYTES_0:
			_SFR_FIELD_WRITE (_SQI_XIP_NUMBER_OF_MODE_BYTES_VREG(index),
							  _SQI_XIP_NUMBER_OF_MODE_BYTES_MASK(index),
							  _SQI_XIP_NUMBER_OF_MODE_BYTES_POS(index),
							  MODE_BYTES_0);
		break;
		default:
			_SFR_FIELD_WRITE (_SQI_XIP_NUMBER_OF_MODE_BYTES_VREG(index),
							  _SQI_XIP_NUMBER_OF_MODE_BYTES_MASK(index),
							  _SQI_XIP_NUMBER_OF_MODE_BYTES_POS(index),
							  MODE_BYTES_0);
	}
}


//******************************************************************************
/* Function :  SQI_XIPModeBytesGet_Default

  Summary:
    Implements Default variant of PLIB_SQI_XIPModeBytesGet

  Description:
    This template implements the Default variant of the PLIB_SQI_XIPModeBytesGet function.
*/

PLIB_TEMPLATE SQI_MODE_BYTES SQI_XIPModeBytesGet_Default( SQI_MODULE_ID index )
{
	return _SFR_FIELD_READ (_SQI_XIP_NUMBER_OF_MODE_BYTES_VREG(index),
							_SQI_XIP_NUMBER_OF_MODE_BYTES_MASK(index),
							_SQI_XIP_NUMBER_OF_MODE_BYTES_POS(index));
}


//******************************************************************************
/* Function :  SQI_ExistsXIPModeBytes_Default

  Summary:
    Implements Default variant of PLIB_SQI_ExistsXIPModeBytes

  Description:
    This template implements the Default variant of the PLIB_SQI_ExistsXIPModeBytes function.
*/

PLIB_TEMPLATE bool SQI_ExistsXIPModeBytes_Default( SQI_MODULE_ID index )
{
    return true;
}


#endif /*_SQI_XIPMODEBYTES_DEFAULT_H*/

/******************************************************************************
 End of File
*/
