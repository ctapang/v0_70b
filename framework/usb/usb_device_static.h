/*******************************************************************************
  USB device layer Interface Declarations for static single instance driver

  Company:
    Microchip Technology Inc.

  File Name:
    usb_device_static.h

  Summary:
    USB device layer interface Declarations for static single instance driver

  Description:
    The USB device layer provides a simple interface to manage the USB bus
    enumeration in USB device stack. This file defines the interface
    Declarations for the static single-instance variant of the USB
    device layer interface routines.
    
  Remarks:
    Static single-instance interfaces encorporate the device layer instance number
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

#ifndef _USB_DEVICE_STATIC_H
#define _USB_DEVICE_STATIC_H


// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance 0 for the static single open device
// *****************************************************************************
// *****************************************************************************

void USB_DEVICE0_Initialize( const SYS_MODULE_INIT * const init);

void USB_DEVICE0_Initialize( const SYS_MODULE_INIT * const init);

void USB_DEVICE0_Deinitialize( void );

SYS_STATUS USB_DEVICE0_Status( void );

void USB_DEVICE0_Tasks( void );

void USB_DEVICE0_Open( const DRV_IO_INTENT intent );

void USB_DEVICE0_Close( void );

DRV_CLIENT_STATUS USB_DEVICE0_ClientStatus( void );

USB_ERROR USB_DEVICE0_EventCallBackSet( const USB_DEVICE_CALLBACK callBackFunc );

USB_DEVICE_STATE USB_DEVICE0_GetDeviceState( void );

uint16_t USB_DEVICE0_GetConfigurationValue( void );

USB_SPEED USB_DEVICE0_GetDeviceSpeed( void );

// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance 1 for the static single open device
// *****************************************************************************
// *****************************************************************************

void USB_DEVICE1_Initialize( const SYS_MODULE_INIT * const init);

void USB_DEVICE1_Initialize( const SYS_MODULE_INIT * const init);

void USB_DEVICE1_Deinitialize( void );

SYS_STATUS USB_DEVICE1_Status( void );

void USB_DEVICE1_Tasks( void );

void USB_DEVICE1_Open( const DRV_IO_INTENT intent );

void USB_DEVICE1_Close( void );

DRV_CLIENT_STATUS USB_DEVICE1_ClientStatus( void );

USB_ERROR USB_DEVICE1_EventCallBackSet( const USB_DEVICE_CALLBACK callBackFunc );

USB_DEVICE_STATE USB_DEVICE1_GetDeviceState( void );

uint16_t USB_DEVICE1_GetConfigurationValue( void );

USB_SPEED USB_DEVICE1_GetDeviceSpeed( void );

														
// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance 2 for the static single open device
// *****************************************************************************
// *****************************************************************************

void USB_DEVICE2_Initialize( const SYS_MODULE_INIT * const init);

void USB_DEVICE2_Initialize( const SYS_MODULE_INIT * const init);

void USB_DEVICE2_Deinitialize( void );

SYS_STATUS USB_DEVICE2_Status( void );

void USB_DEVICE2_Tasks( void );

void USB_DEVICE2_Open( const DRV_IO_INTENT intent );

void USB_DEVICE2_Close( void );

DRV_CLIENT_STATUS USB_DEVICE2_ClientStatus( void );

USB_ERROR USB_DEVICE2_EventCallBackSet( const USB_DEVICE_CALLBACK callBackFunc );

USB_DEVICE_STATE USB_DEVICE2_GetDeviceState( void );

uint16_t USB_DEVICE2_GetConfigurationValue( void );

USB_SPEED USB_DEVICE2_GetDeviceSpeed( void );



/* Called by the controller driver upon reception of a setup packet */

void USB_DEVICE_EventHandler( DRV_USB_EVENT eventType, void * eventData );


#endif // #ifndef _USB_DEVICE_STATIC_H

/*******************************************************************************
 End of File
*/
