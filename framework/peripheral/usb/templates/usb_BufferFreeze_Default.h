/*******************************************************************************
  USB Peripheral Library Template Implementation

  File Name:
    usb_BufferFreeze_Default.h

  Summary:
    USB PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : BufferFreeze
    and its Variant : Default
    For following APIs :
        PLIB_USB_PingPongFreeze
        PLIB_USB_PingPongUnfreeze
        PLIB_USB_ExistsBufferFreeze

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

#ifndef _USB_BUFFERFREEZE_DEFAULT_H
#define _USB_BUFFERFREEZE_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _USB_FREEZE_BUFFERS_VREG(index)

  MASKs: 
    _USB_FREEZE_BUFFERS_MASK(index)

  POSs: 
    _USB_FREEZE_BUFFERS_POS(index)

  LENs: 
    _USB_FREEZE_BUFFERS_LEN(index)

*/


//******************************************************************************
/* Function :  USB_PingPongFreeze_Default

  Summary:
    Implements Default variant of PLIB_USB_PingPongFreeze 

  Description:
    This template implements the Default variant of the PLIB_USB_PingPongFreeze function.
*/

PLIB_TEMPLATE void USB_PingPongFreeze_Default( USB_MODULE_ID index )
{
    _SFR_BIT_SET(_USB_FREEZE_BUFFERS_VREG(index),
                 _USB_FREEZE_BUFFERS_POS(index) );
}


//******************************************************************************
/* Function :  USB_PingPongUnfreeze_Default

  Summary:
    Implements Default variant of PLIB_USB_PingPongUnfreeze 

  Description:
    This template implements the Default variant of the PLIB_USB_PingPongUnfreeze function.
*/

PLIB_TEMPLATE void USB_PingPongUnfreeze_Default( USB_MODULE_ID index )
{
    _SFR_BIT_CLEAR(_USB_FREEZE_BUFFERS_VREG(index),
                   _USB_FREEZE_BUFFERS_POS(index) );
}

//******************************************************************************
/* Function :  USB_PingPongReset_Default

  Summary:
    Implements Default variant of PLIB_USB_PingPongReset 

  Description:
    This template implements the Default variant of the PLIB_USB_PingPongReset function.
*/

PLIB_TEMPLATE void USB_PingPongReset_Default( USB_MODULE_ID index )
{
    SFR_TYPE * vreg = _USB_FREEZE_BUFFERS_VREG(index);
    unsigned int pos = _USB_FREEZE_BUFFERS_POS(index);

   _SFR_BIT_SET(vreg, pos );
   _SFR_BIT_CLEAR(vreg, pos);

}


//******************************************************************************
/* Function :  USB_ExistsBufferFreeze_Default

  Summary:
    Implements Default variant of PLIB_USB_ExistsBufferFreeze

  Description:
    This template implements the Default variant of the PLIB_USB_ExistsBufferFreeze function.
*/

PLIB_TEMPLATE bool USB_ExistsBufferFreeze_Default( USB_MODULE_ID index )
{
    return true;
}


#endif /*_USB_BUFFERFREEZE_DEFAULT_H*/

/******************************************************************************
 End of File
*/

