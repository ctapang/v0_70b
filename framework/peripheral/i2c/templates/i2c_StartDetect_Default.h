/*******************************************************************************
  I2C Peripheral Library Template Implementation

  File Name:
    i2c_StartDetect_Default.h

  Summary:
    I2C PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : StartDetect
    and its Variant : Default
    For following APIs :
        PLIB_I2C_StartWasDetected
        PLIB_I2C_StartClear
        PLIB_I2C_ExistsStartDetect

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

#ifndef _I2C_STARTDETECT_DEFAULT_H
#define _I2C_STARTDETECT_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _I2C_START_DETECT_VREG(index)

  MASKs: 
    _I2C_START_DETECT_MASK(index)

  POSs: 
    _I2C_START_DETECT_POS(index)

  LENs: 
    _I2C_START_DETECT_LEN(index)

*/


//******************************************************************************
/* Function :  I2C_StartWasDetected_Default

  Summary:
    Implements Default variant of PLIB_I2C_StartWasDetected 

  Description:
    This template implements the Default variant of the PLIB_I2C_StartWasDetected function.
*/

PLIB_TEMPLATE bool I2C_StartWasDetected_Default( I2C_MODULE_ID index )
{
    return _SFR_BIT_READ(_I2C_START_DETECT_VREG(index),
                             _I2C_START_DETECT_POS(index) );
}


//******************************************************************************
/* Function :  I2C_StartClear_Default

  Summary:
    Implements Default variant of PLIB_I2C_StartClear 

  Description:
    This template implements the Default variant of the PLIB_I2C_StartClear function.
*/

PLIB_TEMPLATE void I2C_StartClear_Default( I2C_MODULE_ID index )
{
    _SFR_BIT_CLEAR(_I2C_START_DETECT_VREG(index),
                             _I2C_START_DETECT_POS(index) );
}


//******************************************************************************
/* Function :  I2C_ExistsStartDetect_Default

  Summary:
    Implements Default variant of PLIB_I2C_ExistsStartDetect

  Description:
    This template implements the Default variant of the PLIB_I2C_ExistsStartDetect function.
*/

PLIB_TEMPLATE bool I2C_ExistsStartDetect_Default( I2C_MODULE_ID index )
{
    return true;
}


#endif /*_I2C_STARTDETECT_DEFAULT_H*/

/******************************************************************************
 End of File
*/

