/*******************************************************************************
  USB Device layer interface names mapping

  Company:
    Microchip Technology Inc.

  File Name:
    usb_device_mapping.h

  Summary:
    USB Device Layer Interface names mapping

  Description:
    This header file maps the interface prototypes in "usb_device.h" to
    static variants of these routines appropriate for the selcted configuration.
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

#ifndef _USB_DEVICE_MAPPING_H
#define _USB_DEVICE_MAPPING_H


// *****************************************************************************
// *****************************************************************************
// Section: File includes
// *****************************************************************************
// *****************************************************************************
/* Note:  See the bottom of file for implementation header include files.
*/

#include <stdint.h>
#include <stdbool.h>

#include "usb/usb_device_static.h"
#include "usb/usb_device_static_multi.h"
#include "usb/src/usb_device_local.h"


// *****************************************************************************
// *****************************************************************************
// Section: USB device layer Static API Name Generation
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Macro: _USB_DEVICE_MAKE_NAME(name)

  Summary:
    Creates an instance-specific static interface name

  Description:
     This macro creates the instance-specific name of the given static interface
     routine by inserting the index number into the name.

     Example USB_DEVICE_Initialize becomes USB_DEVICE1_Initialize for an index of 1.

  Remarks:
    Multi-client configurations add the word "multi" to the API name, single-
    client configurations do not.

    Example USB_DEVICE_Initialize becomes USB_DEVICE1multi_Initialize for an index
    of 1.
*/


#if !defined( USB_DEVICE_MAX_INSTANCES )

    // Static builds use static naming to reduce calling overhead.
    #if !defined( USB_DEVICE_MAX_CLIENTS )

        // Static Single-Client Interface Name Generation
        #define _USB_DEVICE_STATIC_API_SINGLE(index, name)     USB_DEVICE ## index ## _ ## name
        #define _USB_DEVICE_STATIC_API(index, name)            _USB_DEVICE_STATIC_API_SINGLE(index, name)

    #else // ( USB_DEVICE_CLIENTS_NUMBER >= 1 )

        // Static Multi-Client Interface Name Generation
        #define _USB_DEVICE_STATIC_API_MULTI(index, name)      USB_DEVICE ## index ## multi_ ## name
        #define _USB_DEVICE_STATIC_API(index, name)           _USB_DEVICE_STATIC_API_MULTI(index, name)

    #endif

    // Static naming Macros
    #define _USB_DEVICE_MAKE_NAME(name)                        _USB_DEVICE_STATIC_API(USB_DEVICE_INDEX, name)

#else // (USB_DEVICE_CONFIG_BUILD_TYPE == DRV_BUILD_TYPE_DYNAMIC)

    // Dynamic Interface Name Generation
    #define _USB_DEVICE_MAKE_NAME(name)                        USB_DEVICE_ ## name

#endif


// *****************************************************************************
// *****************************************************************************
// Section: USB Driver Static API Mapping
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Static Interface Mapping

  Summary:
    Maps the dynamic interface calls to appropriate static interface

  Description:
    These macros map calls to the dynamic interface routines to calls to the 
    appropriate instance-specific static interface routine when a static build
    (USB_DEVICE_INSTANCES_NUMBER is not defined) is configured.
    
    Example:
    
        USB_DEVICE_Status(USB_DEVICE_INDEX_1);
        
    Becomes:
    
        USB_DEVICE_Status();
        
  Remarks:
    Static configuration eliminate the need to pass the object parameter.  
    However, the index is "returned" as the object handle (from the 
    "Initialize" routine) to allow code written for the dynamic API to continue
    to build when using a static configuration.
    
    Example:
    
        object = USB_DEVICE_Initialize(USB_DEVICE_INDEX_1, &initData);
        
    Becomes:
    
        object = ( USB_DEVICE1_Initialize(&initData), USB_DEVICE_INDEX );
        
    Static single-client configurations also eliminate the client handle 
    parameter.  However, the index (the driver-object index) is "returned" from
    the "Open" routine to allow code written for multi-client drivers to build
    when using a static single-open configuration.
    
    Example:
    
        handle = USB_DEVICE_Open(USB_DEVICE_INDEX_1, intent);
        
    Becomes:
    
        handle = ( USB_DEVICE_Open(intent), USB_DEVICE_INDEX );
*/

#if !defined( USB_DEVICE_MAX_INSTANCES ) // static

    #if !defined( USB_DEVICE_MAX_CLIENTS ) // single client

        #define USB_DEVICE_Initialize(sysID, inData)            (_USB_DEVICE_MAKE_NAME(Initialize)(inData), USB_DEVICE_INDEX)

        #define USB_DEVICE_Reinitialize(sysObj, inData)         _USB_DEVICE_MAKE_NAME(Reinitialize)(inData)

        #define USB_DEVICE_Deinitialize(sysObj)                 _USB_DEVICE_MAKE_NAME(Deinitialize)()

        #define USB_DEVICE_Status(sysObj)                       _USB_DEVICE_MAKE_NAME(Status)()

        #define USB_DEVICE_Tasks(sysObj)                        _USB_DEVICE_MAKE_NAME(Tasks)()

        #define USB_DEVICE_Open(sysID, intent)                  (_USB_DEVICE_MAKE_NAME(Open)(intent), USB_DEVICE_INDEX)

        #define USB_DEVICE_Close(handle)                        _USB_DEVICE_MAKE_NAME(Close)()

        #define USB_DEVICE_ClientStatus(handle)                 _USB_DEVICE_MAKE_NAME(ClientStatus)()

        #define USB_DEVICE_EventCallBackSet(h, c)               _USB_DEVICE_MAKE_NAME(EventCallBackSet)(c)

        #define USB_DEVICE_EventCallBackSet(h, c)               _USB_DEVICE_MAKE_NAME(EventCallBackSet)(c)

        #define USB_DEVICE_GetDeviceState(h)                    _USB_DEVICE_MAKE_NAME(GetDeviceState)()

        #define USB_DEVICE_GetConfigurationValue(h)             _USB_DEVICE_MAKE_NAME(GetConfigurationValue)()

        #define USB_DEVICE_GetDeviceSpeed(h)                    _USB_DEVICE_MAKE_NAME(GetDeviceSpeed)()
		
        #define USB_DEVICE_ControlTransferRequest(a,b,c,d,e,f)  _USB_DEVICE_MAKE_NAME(ControlTransferRequest)(b,c,d,e,f)
		
        #define USB_DEVICE_ControlTransferPipeStall(a, b)       _USB_DEVICE_MAKE_NAME(ControlTransferPipeStall)(b)

    #else // multi-client

        #define USB_DEVICE_Initialize(sysID, inData)            (_USB_DEVICE_MAKE_NAME(Initialize)(inData), USB_DEVICE_INDEX)

        #define USB_DEVICE_Reinitialize(sysObj, inData)         _USB_DEVICE_MAKE_NAME(Reinitialize)(inData)

        #define USB_DEVICE_Deinitialize(sysObj)                 _USB_DEVICE_MAKE_NAME(Deinitialize)()

        #define USB_DEVICE_Status(sysObj)                       _USB_DEVICE_MAKE_NAME(Status)()

        #define USB_DEVICE_Tasks(sysObj)                        _USB_DEVICE_MAKE_NAME(Tasks)()

        #define USB_DEVICE_Open(sysID, intent)                  (_USB_DEVICE_MAKE_NAME(Open)(intent))

        #define USB_DEVICE_Close(handle)                        _USB_DEVICE_MAKE_NAME(Close)(handle)

        #define USB_DEVICE_ClientStatus(handle)                 _USB_DEVICE_MAKE_NAME(ClientStatus)(handle)

    #endif

#else // Dynamic Build

    // No Change in the Naming convention

#endif


// *****************************************************************************
// *****************************************************************************
// Section: USB Driver API Mapping to USB device layer API
// *****************************************************************************
// *****************************************************************************
#define USB_CD_HANDLE_mac (((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->usbCDHandle)

#define USB_DEVICE_EndpointEnable( handle, epAddrs, epType, epSize )   \
        DRV_USB_DEVICE_EndpointEnable( (((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->usbCDHandle), epAddrs, epType, epSize )
#define USB_DEVICE_EndpointDisable( handle, epAdrs )     \
        DRV_USB_DEVICE_EndpointDisable( (((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->usbCDHandle), epAdrs )
#define USB_DEVICE_EndpointStall( handle, epAdrs )      \
        DRV_USB_DEVICE_EndpointStall((((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->usbCDHandle), epAdrs )
#define USB_DEVICE_EndpointStallClear( handle, epAdrs )  \
        DRV_USB_DEVICE_EndpointStallClear( (((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->usbCDHandle), epAdrs )
#define USB_DEVICE_EndpointIsEnabled( handle, epAdrs )   \
        DRV_USB_DEVICE_EndpointIsEnabled( (((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->usbCDHandle), epAdrs )
#define USB_DEVICE_EndpointIsStalled( handle, epAdrs )   \
        DRV_USB_DEVICE_EndpointIsStalled( (((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->usbCDHandle), epAdrs )
#define USB_DEVICE_IRPSubmit( handle, epAdrs, irp )       \
        DRV_USB_DEVICE_IRPSubmit( (((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->usbCDHandle), epAdrs, irp )
#define USB_DEVICE_IRPCancelAll( handle, epAdrs )        \
        DRV_USB_DEVICE_IRPCancelAll( (((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->usbCDHandle), epAdrs )
#define USB_DEVICE_Attach( handle )     DRV_USB_DEVICE_Attach( ((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->usbCDHandle)
#define USB_DEVICE_Detach( handle )     DRV_USB_DEVICE_Detach( ((USB_DEVICE_CLIENT_STRUCT *)handle)->usbDeviceInstance->usbCDHandle)




#endif // #ifndef _USB_DEVICE_MAPPING_H

/*******************************************************************************
 End of File
*/

