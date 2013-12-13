/*******************************************************************************
  SQI Peripheral Library Template Implementation

  File Name:
    sqi_DMAEngineBusy_Default.h

  Summary:
    SQI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : DMAEngineBusy
    and its Variant : Default
    For following APIs :
        PLIB_SQI_DMABDIsBusy
        PLIB_SQI_ExistsDMAEngineBusy

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

#ifndef _SQI_DMAENGINEBUSY_DEFAULT_H
#define _SQI_DMAENGINEBUSY_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are

  VREGs:
    _SQI_DMA_IS_ACTIVE_VREG(index)

  MASKs:
    _SQI_DMA_IS_ACTIVE_MASK(index)

  POSs:
    _SQI_DMA_IS_ACTIVE_POS(index)

  LENs:
    _SQI_DMA_IS_ACTIVE_LEN(index)

*/


//******************************************************************************
/* Function :  SQI_DMABDIsBusy_Default

  Summary:
    Implements Default variant of PLIB_SQI_DMABDIsBusy

  Description:
    This template implements the Default variant of the PLIB_SQI_DMABDIsBusy function.
*/

PLIB_TEMPLATE bool SQI_DMABDIsBusy_Default( SQI_MODULE_ID index )
{
	return (bool) _SFR_BIT_READ (_SQI_DMA_IS_ACTIVE_VREG(index),
								 _SQI_DMA_IS_ACTIVE_POS(index));
}


//******************************************************************************
/* Function :  SQI_ExistsDMAEngineBusy_Default

  Summary:
    Implements Default variant of PLIB_SQI_ExistsDMAEngineBusy

  Description:
    This template implements the Default variant of the PLIB_SQI_ExistsDMAEngineBusy function.
*/

PLIB_TEMPLATE bool SQI_ExistsDMAEngineBusy_Default( SQI_MODULE_ID index )
{
    return true;
}


#endif /*_SQI_DMAENGINEBUSY_DEFAULT_H*/

/******************************************************************************
 End of File
*/
