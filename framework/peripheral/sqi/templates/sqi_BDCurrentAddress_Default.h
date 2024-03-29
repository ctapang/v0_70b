/*******************************************************************************
  SQI Peripheral Library Template Implementation

  File Name:
    sqi_BDCurrentAddress_Default.h

  Summary:
    SQI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : BDCurrentAddress
    and its Variant : Default
    For following APIs :
        PLIB_SQI_DMABDCurrentAddressGet
        PLIB_SQI_ExistsBDCurrentAddress

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

#ifndef _SQI_BDCURRENTADDRESS_DEFAULT_H
#define _SQI_BDCURRENTADDRESS_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are

  VREGs:
    _SQI_CURRENT_BD_ADDRESS_VREG(index)

  MASKs:
    _SQI_CURRENT_BD_ADDRESS_MASK(index)

  POSs:
    _SQI_CURRENT_BD_ADDRESS_POS(index)

  LENs:
    _SQI_CURRENT_BD_ADDRESS_LEN(index)

*/


//******************************************************************************
/* Function :  SQI_DMABDCurrentAddressGet_Default

  Summary:
    Implements Default variant of PLIB_SQI_DMABDCurrentAddressGet

  Description:
    This template implements the Default variant of the PLIB_SQI_DMABDCurrentAddressGet function.
*/

PLIB_TEMPLATE void* SQI_DMABDCurrentAddressGet_Default( SQI_MODULE_ID index )
{
	return (void*) _SFR_READ(_SQI_CURRENT_BD_ADDRESS_VREG(index));
}


//******************************************************************************
/* Function :  SQI_ExistsBDCurrentAddress_Default

  Summary:
    Implements Default variant of PLIB_SQI_ExistsBDCurrentAddress

  Description:
    This template implements the Default variant of the PLIB_SQI_ExistsBDCurrentAddress function.
*/

PLIB_TEMPLATE bool SQI_ExistsBDCurrentAddress_Default( SQI_MODULE_ID index )
{
    return true;
}


#endif /*_SQI_BDCURRENTADDRESS_DEFAULT_H*/

/******************************************************************************
 End of File
*/

