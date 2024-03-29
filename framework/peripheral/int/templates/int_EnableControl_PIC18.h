/*******************************************************************************
  INT Peripheral Library Template Implementation

  File Name:
    int_EnableControl_PIC18.h

  Summary:
    INT PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : EnableControl
    and its Variant : PIC18
    For following APIs :
        PLIB_INT_ExistsEnableControl
        PLIB_INT_Enable
        PLIB_INT_Disable
        PLIB_INT_IsEnabled

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

#ifndef _INT_ENABLECONTROL_PIC18_H
#define _INT_ENABLECONTROL_PIC18_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _INT_ENABLE_VREG(index)

  MASKs: 
    _INT_ENABLE_MASK(index)

  POSs: 
    _INT_ENABLE_POS(index)

  LENs: 
    _INT_ENABLE_LEN(index)

*/


//******************************************************************************
/* Function :  INT_ExistsEnableControl_PIC18

  Summary:
    Implements PIC18 variant of PLIB_INT_ExistsEnableControl

  Description:
    This template implements the PIC18 variant of the PLIB_INT_ExistsEnableControl function.
*/

PLIB_TEMPLATE bool INT_ExistsEnableControl_PIC18( INT_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  INT_Enable_PIC18

  Summary:
    Implements PIC18 variant of PLIB_INT_Enable 

  Description:
    This template implements the PIC18 variant of the PLIB_INT_Enable function.
*/

PLIB_TEMPLATE void INT_Enable_PIC18( INT_MODULE_ID index )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  INT_Disable_PIC18

  Summary:
    Implements PIC18 variant of PLIB_INT_Disable 

  Description:
    This template implements the PIC18 variant of the PLIB_INT_Disable function.
*/

PLIB_TEMPLATE void INT_Disable_PIC18( INT_MODULE_ID index )
{
    /* TODO  */
}


//******************************************************************************
/* Function :  INT_IsEnabled_PIC18

  Summary:
    Implements PIC18 variant of PLIB_INT_IsEnabled 

  Description:
    This template implements the PIC18 variant of the PLIB_INT_IsEnabled function.
*/

PLIB_TEMPLATE bool INT_IsEnabled_PIC18( INT_MODULE_ID index )
{
    /* TODO  */
}


#endif /*_INT_ENABLECONTROL_PIC18_H*/

/******************************************************************************
 End of File
*/

