/*******************************************************************************
  PMP Peripheral Library Template Implementation

  File Name:
    pmp_AddressPortPinControl_Basic.h

  Summary:
    PMP PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : AddressPortPinControl
    and its Variant : Basic
    For following APIs :
        PLIB_PMP_ExistsAddressPortPinControl
        PLIB_PMP_AddressPortEnable
        PLIB_PMP_AddressPortDisable

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

#ifndef _PMP_ADDRESSPORTPINCONTROL_BASIC_H
#define _PMP_ADDRESSPORTPINCONTROL_BASIC_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _PMP_ADDRESS_PORT_CONTROL_VREG(index)

  MASKs: 
    _PMP_ADDRESS_PORT_CONTROL_MASK(index)

  POSs: 
    _PMP_ADDRESS_PORT_CONTROL_POS(index)

  LENs: 
    _PMP_ADDRESS_PORT_CONTROL_LEN(index)

*/


//******************************************************************************
/* Function :  PMP_ExistsAddressPortPinControl_Basic

  Summary:
    Implements Basic variant of PLIB_PMP_ExistsAddressPortPinControl

  Description:
    This template implements the Basic variant of the PLIB_PMP_ExistsAddressPortPinControl function.
*/

PLIB_TEMPLATE bool PMP_ExistsAddressPortPinControl_Basic( PMP_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  PMP_AddressPortEnable_Basic

  Summary:
    Implements Basic variant of PLIB_PMP_AddressPortEnable 

  Description:
    This template implements the Basic variant of the PLIB_PMP_AddressPortEnable function.
*/

PLIB_TEMPLATE void PMP_AddressPortEnable_Basic( PMP_MODULE_ID index , PMP_ADDRESS_PORT portfunctions )
{
    _SFR_FIELD_WRITE(
						_PMP_ADDRESS_PORT_CONTROL_VREG(index),
						_PMP_ADDRESS_PORT_CONTROL_MASK(index),
						_PMP_ADDRESS_PORT_CONTROL_POS(index),
						( portfunctions )
    );
}


//******************************************************************************
/* Function :  PMP_AddressPortDisable_Basic

  Summary:
    Implements Basic variant of PLIB_PMP_AddressPortDisable 

  Description:
    This template implements the Basic variant of the PLIB_PMP_AddressPortDisable function.
*/

PLIB_TEMPLATE void PMP_AddressPortDisable_Basic( PMP_MODULE_ID index , PMP_ADDRESS_PORT portfunctions )
{
     _SFR_FIELD_CLEAR(
						_PMP_ADDRESS_PORT_CONTROL_VREG(index),
						_PMP_ADDRESS_PORT_CONTROL_MASK(index),
						_PMP_ADDRESS_PORT_CONTROL_POS(index),
						( portfunctions )
    );
}


#endif /*_PMP_ADDRESSPORTPINCONTROL_BASIC_H*/

/******************************************************************************
 End of File
*/

