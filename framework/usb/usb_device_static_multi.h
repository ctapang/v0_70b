/*******************************************************************************
  USB device layer Interface Declarations for static multi instance driver

  Company:
    Microchip Technology Inc.

  File Name:
    usb_device_static_multi.h

  Summary:
    USB device layer interface Declarations for static multi instance driver

  Description:
    The USB device layer provides a simple interface to manage the USB bus
    enumeration in USB device stack. This file defines the interface
    Declarations for the static multi-instance variants of the USB
    device layer interface routines.
    
  Remarks:
    Static multi-instance interfaces encorporate the device layer instance number
    within the names of the routines, eliminating the need for an object ID or 
    object handle.
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

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
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

#ifndef _USB_DEVICE_STATIC_MULTI_H_
#define _USB_DEVICE_STATIC_MULTI_H_


// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance 0 for the static single open driver
// *****************************************************************************
// *****************************************************************************

void USB_DEVICE0multi_Initialize( const SYS_MODULE_INIT * const init);
void USB_DEVICE0multi_Deinitialize( void );


#endif // #ifndef _DRV_SPI_STATIC_MULTI_H

/*******************************************************************************
 End of File
*/
