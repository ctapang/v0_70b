/*******************************************************************************
  USB Device Driver Static Interface

  Company:
    Microchip Technology Incorported

  FileName:
    drv_usb_static.h

  Summary:
    USB Device Driver Interface File

  Description:
    The USB device driver provides a simple interface to manage the "USB"
    peripheral.  This file defines the interface definitions for the static
    single client version of the driver. Static interfaces incorporate the 
    the instance index within the name of the routines thus eliminating the
    need for an object ID or an object handle.  
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

#ifndef _DRV_USB_STATIC_H
#define _DRV_USB_STATIC_H

// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance 0 for the static single open driver
// *****************************************************************************
// *****************************************************************************

void DRV_USB0_Initialize( const SYS_MODULE_INIT * const init);

void DRV_USB0_Deinitialize( void );

SYS_STATUS DRV_USB0_Status( void );

void DRV_USB0_Tasks_ISR ( void );

DRV_HANDLE DRV_USB0_Open( const DRV_IO_INTENT intent );

void DRV_USB0_Close( void );

DRV_USB_CLIENT_STATUS DRV_USB0_ClientStatus( void );

void DRV_USB0_ClientEventCallBackSet(uintptr_t hReferenceData, 
    DRV_USB_EVENT_CALLBACK eventCallBack); 

void DRV_USB0_DEVICE_AddressSet(uint8_t address);

USB_SPEED DRV_USB0_DEVICE_CurrentSpeedGet(void);

unsigned int DRV_USB0_VersionGet( void );

char* DRV_USB0_VersionStrGet( void );

// *****************************************************************************
// *****************************************************************************
// Section: Interface Headers for Instance 1 for the static single open driver
// *****************************************************************************
// *****************************************************************************

SYS_MODULE_OBJ DRV_USB1_Initialize( const SYS_MODULE_INIT * const init);

void DRV_USB1_Deinitialize( void );

SYS_STATUS DRV_USB1_Status( void );

void DRV_USB1_Tasks ( void );

DRV_HANDLE DRV_USB1_Open( const DRV_IO_INTENT intent );

void DRV_USB1_Close( void );

DRV_USB_CLIENT_STATUS DRV_USB1_ClientStatus( void );

unsigned int DRV_USB1_VersionGet( void );

char* DRV_USB1_VersionStrGet( void );

#endif

