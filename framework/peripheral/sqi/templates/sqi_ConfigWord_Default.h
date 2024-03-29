/*******************************************************************************
  SQI Peripheral Library Template Implementation

  File Name:
    sqi_ConfigWord_Default.h

  Summary:
    SQI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ConfigWord
    and its Variant : Default
    For following APIs :
        PLIB_SQI_ConfigWordSet
        PLIB_SQI_ConfigWordGet
        PLIB_SQI_ExistsConfigWord

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

#ifndef _SQI_CONFIGWORD_DEFAULT_H
#define _SQI_CONFIGWORD_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are

  VREGs:
    _SQI_TRANSFER_MODE_CONTROL_OR_CFG_VREG(index)

  MASKs:
    _SQI_TRANSFER_MODE_CONTROL_OR_CFG_MASK(index)

  POSs:
    _SQI_TRANSFER_MODE_CONTROL_OR_CFG_POS(index)

  LENs:
    _SQI_TRANSFER_MODE_CONTROL_OR_CFG_LEN(index)

*/


//******************************************************************************
/* Function :  SQI_ConfigWordSet_Default

  Summary:
    Implements Default variant of PLIB_SQI_ConfigWordSet

  Description:
    This template implements the Default variant of the PLIB_SQI_ConfigWordSet function.
*/

PLIB_TEMPLATE void SQI_ConfigWordSet_Default( SQI_MODULE_ID index ,
											  bool sqiEnable ,
											  SQI_CS_OEN csPins ,
											  SQI_DATA_OEN dataPins ,
											  bool reset ,
											  bool burstEn ,
											  bool hold ,
											  bool writeProtect ,
											  bool rxLatch ,
											  SQI_DATA_FORMAT lsbf ,
											  SQI_DATA_MODE dataMode ,
											  SQI_XFER_MODE xferMode )
{
	_SFR_WRITE (_SQI_TRANSFER_MODE_CONTROL_OR_CFG_VREG(index),
				sqiEnable << 31 |
				csPins << 24 |
				dataPins << 20 |
				reset << 16 |
				burstEn << 12 |
				hold << 10 |
				writeProtect << 9 |
				rxLatch << 7 |
				lsbf << 5 |
				dataMode << 3 |
				xferMode);

}


//******************************************************************************
/* Function :  SQI_ConfigWordGet_Default

  Summary:
    Implements Default variant of PLIB_SQI_ConfigWordGet

  Description:
    This template implements the Default variant of the PLIB_SQI_ConfigWordGet function.
*/

PLIB_TEMPLATE uint32_t SQI_ConfigWordGet_Default( SQI_MODULE_ID index )
{
    return (uint32_t) _SFR_READ (_SQI_TRANSFER_MODE_CONTROL_OR_CFG_VREG(index));
}


//******************************************************************************
/* Function :  SQI_ExistsConfigWord_Default

  Summary:
    Implements Default variant of PLIB_SQI_ExistsConfigWord

  Description:
    This template implements the Default variant of the PLIB_SQI_ExistsConfigWord function.
*/

PLIB_TEMPLATE bool SQI_ExistsConfigWord_Default( SQI_MODULE_ID index )
{
    return true;
}


#endif /*_SQI_CONFIGWORD_DEFAULT_H*/

/******************************************************************************
 End of File
*/

