/*******************************************************************************
  DEVCON Peripheral Library Template Implementation

  File Name:
    devcon_JTAGUsesTDO_Default.h

  Summary:
    DEVCON PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : JTAGUsesTDO
    and its Variant : Default
    For following APIs :
        PLIB_DEVCON_2WireJTAGEnableTDO
        PLIB_DEVCON_2WireJTAGDisableTDO
        PLIB_DEVCON_ExistsJTAGUsesTDO

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

#ifndef _DEVCON_JTAGUSESTDO_DEFAULT_H
#define _DEVCON_JTAGUSESTDO_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are

  VREGs:
    _DEVCON_JTAG_TDO_USE_ENABLE_VREG(index)

  MASKs:
    _DEVCON_JTAG_TDO_USE_ENABLE_MASK(index)

  POSs:
    _DEVCON_JTAG_TDO_USE_ENABLE_POS(index)

  LENs:
    _DEVCON_JTAG_TDO_USE_ENABLE_LEN(index)

*/


//******************************************************************************
/* Function :  DEVCON_2WireJTAGEnableTDO_Default

  Summary:
    Implements Default variant of PLIB_DEVCON_2WireJTAGEnableTDO

  Description:
    This template implements the Default variant of the PLIB_DEVCON_2WireJTAGEnableTDO function.
*/

PLIB_TEMPLATE void DEVCON_2WireJTAGEnableTDO_Default( DEVCON_MODULE_ID index )
{
    _SFR_BIT_SET(_DEVCON_JTAG_TDO_USE_ENABLE_VREG(index),_DEVCON_JTAG_TDO_USE_ENABLE_POS(index));
}


//******************************************************************************
/* Function :  DEVCON_2WireJTAGDisableTDO_Default

  Summary:
    Implements Default variant of PLIB_DEVCON_2WireJTAGDisableTDO

  Description:
    This template implements the Default variant of the PLIB_DEVCON_2WireJTAGDisableTDO function.
*/

PLIB_TEMPLATE void DEVCON_2WireJTAGDisableTDO_Default( DEVCON_MODULE_ID index )
{
    _SFR_BIT_CLEAR(_DEVCON_JTAG_TDO_USE_ENABLE_VREG(index),_DEVCON_JTAG_TDO_USE_ENABLE_POS(index));
}


//******************************************************************************
/* Function :  DEVCON_ExistsJTAGUsesTDO_Default

  Summary:
    Implements Default variant of PLIB_DEVCON_ExistsJTAGUsesTDO

  Description:
    This template implements the Default variant of the PLIB_DEVCON_ExistsJTAGUsesTDO function.
*/

PLIB_TEMPLATE bool DEVCON_ExistsJTAGUsesTDO_Default( DEVCON_MODULE_ID index )
{
    return true;
}


#endif /*_DEVCON_JTAGUSESTDO_DEFAULT_H*/

/******************************************************************************
 End of File
*/

