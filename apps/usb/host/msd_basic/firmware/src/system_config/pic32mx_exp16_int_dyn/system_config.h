/*******************************************************************************
  USB Host MSD Demo Configuration Header
  
  Company:      
    Microchip Technology Incorported
  
  File Name:    
    sys_config.h

  Summary:
    Top-level configuration header for the PIC32 USB Starter kit.

  Description:
    This file is the top-level configuration header for the MSD Basic demo
    application for the PIC32 USB starter kit.
*******************************************************************************/

// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END

#ifndef _SYS_CONFIG_H    
#define _SYS_CONFIG_H

#include "peripheral/usb/plib_usb.h"


#define USB_HOST_MAX_DRIVER_SUPPORTED        1    /* Based on TPL list.  */
#define USB_HOST_INSTANCES_NUMBER      1   /* Maximum Host layer instances */
#define USB_HOST_MAX_DEVICE_SUPPORTED        1    /* This is max per bus including root hub */
#define USB_HOST_MAX_CONFIGURATION       1    /* Host support configurations per device */
#define USB_HOST_MAX_INTERFACES          1    /* Max interfaces per device */
#define USB_HOST_MAX_ALTERNATE_SETTINGS  1    /* Max alternate setting per device */
#define USB_HOST_CLIENTS_NUMBER     1
#define USB_HOST_INDEX_0            0
#define USB_HOST_DEVICE_INFORMATION_STRING_LENGTH 31
#define  USB_HOST_MAX_ALTERNATE_SETTINGS      1


#define  USB_HOST_MSD_INSTANCES   1
#define USB_DEVICE_INFORMATION_STRING_LENGTH 31
#define USB_HOST_MSD_DRIVE_MAX            1



// *****************************************************************************
// *****************************************************************************
// Section: SYS FS Configuration
// *****************************************************************************
// *****************************************************************************

/* This is the maximum number for files
 * that can be opened. */
#define SYS_FS_MAX_FILES    2
#define SYS_FS_MEDIA_NUMBER 2
#define SYS_FS_VOLUME_NUMBER              2
#define SYS_FS_MAX_FILE_SYSTEM_TYPE       1
#define USB_HOST_SCSI_INSTANCES_NUMBER  2
// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************

#define DRV_USB_INSTANCES_NUMBER  			1
#define DRV_USB_CLIENTS_NUMBER  			1
#define DRV_USB_INDEX  						DRV_USB_INDEX_0
#define DRV_USB_INTERRUPT_MODE  			true
#define DRV_USB_HOST_SUPPORT		 	true
#define DRV_USB_DEVICE_SUPPORT	 		false
#define DRV_USB_HOST_PIPES_NUMBER 			8
#define DRV_USB_HOST_IRP_PER_FRAME_NUMBER 	        5
#define DRV_USB_HOST_IRP_NUMBER 			5
#define DRV_USB_ENDPOINTS_NUMBER			1
#define DRV_USB_HOST_NAK_LIMIT				200
/* EP0 buffer size. Used by controller driver */
#define USB_EP0_BUFF_SIZE 64

#define DRV_USB_HOST_MAXIMUM_ENDPOINTS_NUMBER     8






// *****************************************************************************
// *****************************************************************************
// Section: Constants
// *****************************************************************************
// *****************************************************************************

#define _DEFAULT    (0x01<<7)       //Default Value (Bit 7 is set)
#define _SELF       (0x01<<6)       //Self-powered (Supports if set)


// *****************************************************************************
/* USB Interrupt And Polled Mode Operation Control

  Summary:
    Macro controls operation of the driver in the interrupt or polled mode

  Description:
    This macro controls the operation of the driver in the interrupt
    mode of operation. The possible values of this macro is

    - true  - Select if interrupt mode of timer operation is desired

    - false - Select if polling mode of timer operation is desired

    Not defining this option to true or false will result in build error.

  Remarks:
    None.
*/

#define DRV_USB_INTERRUPT_MODE  /*DOM-IGNORE-BEGIN*/true/*DOM-IGNORE-END*/



// *****************************************************************************
/* USB Interrupt Source

  Summary:
    USB peripheral interrupt source.

  Description:
    Defines an override of the interrupt source in case of static driver. This
    is an initialization override of the interruptSource member of the driver
    initialization configuration.

  Remarks:
    Refer to the INT PLIB document for more information on INT_SOURCE
    enumeration.

*/

#define DRV_USB_INTERRUPT_SOURCE  INT_SOURCE_USB_1




		



#endif // _SYS_CONFIG_H
/*******************************************************************************
 End of File
*/

