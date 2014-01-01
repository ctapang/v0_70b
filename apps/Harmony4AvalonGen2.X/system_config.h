/*******************************************************************************
  MPLAB Harmony Demo Configuration Header

  Company:
    Microchip Technology Incorporated

  File Name:
    system_config.h

  Summary:
    Top-level configuration header file.

  Description:
    This file is the top-level configuration header for the Harmony Demo
    application for the Explorer-16 board with PIC32MX795F512L.
*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

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

// processor type
#define __PIC32MX__   1
#define __32MX250F128B__  1

#define hwGLOBAL_INTERRUPT_BIT			( 0x01UL )

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section Includes other configuration headers necessary to completely
    define this configuration.
*/


// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************

#define DRV_USB_DEVICE_SUPPORT      1

#define DRV_USB_HOST_SUPPORT        0

#define DRV_USB_ENDPOINTS_NUMBER    3

//#define DRV_USB_INSTANCES_NUMBER    1

#define DRV_USB_INTERRUPT_MODE      1

#define USB_DEVICE_MAX_INSTANCES    1

#define USB_DEVICE_MAX_CLIENTS      1

#define USB_DEVICE_MAX_FUNCTION_DRIVER  1

#define USB_DEVICE_EP0_BUFFER_SIZE  64

#define USB_DEVICE_CDC_INSTANCES_NUMBER  1

//#define DRV_USB_CLIENTS_NUMBER  1

#define USB_DEVICE_HID_INSTANCES_NUMBER  1

#define USB_DEVICE_HID_FUNC_INDEX  0

#define USB_DEVICE_CDC_QUEUE_DEPTH_COMBINED  6




// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************

// Timer
#define DRV_TMR_COUNT_WIDTH 32
#define SYS_TMR_MAX_PERIODIC_EVENTS 4
#define DRV_TMR_INDEX 0
#define DRV_TMR_INTERRUPT_MODE 1
#define DRV_TMR_INSTANCES_NUMBER 4
#define DRV_TMR_CLIENTS_NUMBER 4
#define DRV_TMR_ALARM_ENABLE 1


// *****************************************************************************
// Section: SPI Driver Configuration
// *****************************************************************************
// *****************************************************************************

#define DRV_SPI_INSTANCES_NUMBER                    2

#define DRV_SPI_CLIENTS_NUMBER                      1

#define DRV_SPI_INTERRUPT_MODE                      true

#define DRV_SPI_PORTS_REMAP_USAGE                   true

#define DRV_SPI_BUFFER_SIZE                         64

#define DRV_SPI_FRAME_SYNC_PULSE_DIRECTION          SPI_FRAME_PULSE_DIRECTION_INPUT

#define DRV_SPI_FRAME_SYNC_PULSE_POLARITY           SPI_FRAME_PULSE_POLARITY_ACTIVE_HIGH

#define DRV_SPI_FRAME_SYNC_PULSE_EDGE               SPI_FRAME_PULSE_EDGE_COINCIDES_FIRST_BIT_CLOCK


// *****************************************************************************
// *****************************************************************************
// Section: System Clock Service Configuration
// *****************************************************************************
// *****************************************************************************

#define SYS_CLK_CONFIG_USBPLL_ENABLE              true

#define SYS_CLK_PRIMARY_CLOCK                     80000000L

#define SYS_CLK_SECONDARY_CLOCK                   80000000

#define SYS_CLK_CLOCK_CONFIG_ERROR                10

#define SYS_CLK_CONFIG_USBPLL_DIVISOR             2

#define SYS_CLK_CONFIG_SYSCLK_INP_DIVISOR         2

#define SYS_CLK_CONFIG_SYSCLK_OP_DIVISOR          1

#define SYS_CLK_ON_WAIT_IDLE                      1

#define SYS_CLK_ON_WAIT_SLEEP                     0

#define SYS_CLK_EXTERNAL_CLOCK                    4000000


// *****************************************************************************
// *****************************************************************************
// Section: System Timer Service Configuration
// *****************************************************************************
// *****************************************************************************




#endif // _SYS_CONFIG_H
/*******************************************************************************
 End of File
*/


