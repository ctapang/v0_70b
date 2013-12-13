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

#define HARMONY_TMR_PORTING 1

#define USB_DEVICE_MAX_INSTANCES  1

#define USB_DEVICE_MAX_CLIENTS  2

#define USB_DEVICE_MAX_FUNCTION_DRIVER  1

#define USB_DEVICE_EP0_BUFF_SIZE  64
#define USB_DEVICE_EP0_BUFFER_SIZE  64

#define USB_DEVICE_INSTANCES_NUMBER  1

#define USB_DEVICE_HID_INSTANCES_NUMBER  0

#define USB_DEVICE_HID_FUNC_INDEX  0

#define USB_DEVICE_HID_QUEUE_DEPTH_COMBINED  12

#define SYS_CLK_CONFIG_USBPLL_ENABLE true

#define SYS_CLK_CONFIG_USBPLL_DIVISOR 2

#define SYS_CLK_SECONDARY_CLOCK 80000000

#define SYS_CLK_EXTERNAL_CLOCK 4000000

#define SYS_CLK_PRIMARY_CLOCK 80000000L

#define SYS_CLK_CLOCK_CONFIG_ERROR 10

#define SYS_CLK_CONFIG_SYSCLK_INP_DIVISOR 2


// *****************************************************************************
// *****************************************************************************
// Section: Driver Configuration
// *****************************************************************************
// *****************************************************************************

#define DRV_USB_HOST_PIPES_NUMBER 2

#define DRV_USB_CLIENTS_NUMBER  1

#define DRV_USB_HOST_SUPPORT false

#define DRV_USB_DEVICE_SUPPORT true

#define DRV_USB_ENDPOINTS_NUMBER  3

//#define DRV_USB_INSTANCES_NUMBER   1

#define DRV_USB_INTERRUPT_MODE  1

#define DRV_USB_INDEX 0

// SPI

#define DRV_SPI_UNIFIED true // TODO: what should this be?

#define DRV_SPI_INSTANCES_NUMBER 2 // TODO: what should this be?

#define DRV_SPI_CLIENTS_NUMBER 2 // TODO: what should this be?

#define DRV_SPI_INTERRUPT_MODE true

#define DRV_SPI_FRAME_SYNC_PULSE_DIRECTION 1 // TODO: what should this be?

#define DRV_SPI_FRAME_SYNC_PULSE_POLARITY 1 // TODO: what should this be?

#define DRV_SPI_FRAME_SYNC_PULSE_EDGE 0 // TODO: what should this be?


// *****************************************************************************
// *****************************************************************************
// Section: System Clock Service Configuration
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
// Section: Application Configuration
// *****************************************************************************
// *****************************************************************************
/*  These definitions select the configuration options for the application
*/

// *****************************************************************************
/* OSC Clock

  Summary:
    Defines the OSC clock

  Description:
    This constant defines the OSC clock.

  Remarks:
    This is a placeholder implementation of the system services.
*/

#define SYS_CLK_CONFIG_OSC_CLOCK_FREQUENCY                       8000000


// *****************************************************************************
/* Peripheral Clock

  Summary:
    Defines the peripheral clock

  Description:
    This constant defines the peripheral clock.

  Remarks:
    This is a placeholder implementation of the system services.
*/

#define SYS_CLK_CONFIG_PERIPHERAL_CLOCK_FREQUENCY                       80000000


// ****************************************************************************
/* Timer Period Values

  Summary:
    Timer period values necessary to achieve desired event timing

  Description:
    These constants define the timer period values necessary to achive the
    desired timer events.

  Remarks:
    Timer values differ for each processor based on the clock settings.  The
    given count values are valid only if the device config registers are
    programmed as shown below:

    Explorer 16 Board, XTAL = 8MHz
    PLLIDIV = 2, Freq = 4MHz
    PLLMUL = 20, Freq = 80MHz
    PLLODIV = 1, Freq = 80MHz
    PBDIV = 1,   Freq = 80MHz
    TMR Module I/P = 80MHz
    TMR Prescaler = 1:256 = 312500Hz
    TMR Step = 3.2uS/Count
*/

#define APP_TMR_1S      0x0004C4B4

#define APP_TMR_500mS   0x0002625A

#define APP_TMR_200mS   0x0000F424

#define APP_TMR_100mS   0x00007A12

#define APP_TMR_50mS    0x00003D09

#define APP_TMR_10mS    0x00000C35

#define APP_TMR_1mS     0x00000138


// ****************************************************************************
/* APP_TMR_ID

  Summary:
    The timer ID to be used for the application

  Description:
    This constatnt defines the the PLIB ID for the Timer used.
*/

#define APP_TMR_ID      TMR_ID_1

// ****************************************************************************
/* APP_TMR_INDEX

  Summary:
    ADC driver instance index used for the application

  Description:
    This constatnt defines the the module index for the USART used.
*/

#define APP_TMR_INDEX   DRV_TMR_INDEX_0

// ****************************************************************************
/* APP_TMR_INT_SOURCE

  Summary:
    Interrupt source ID for Timer.

  Description:
    This constant defines the interrupt source ID for timer.
*/

#define PLIB_INT_SOURCE_TIMER_1 1  // TODO: look for the file that has this def

#define APP_TMR_INT_SOURCE      PLIB_INT_SOURCE_TIMER_1



// *****************************************************************************
// *****************************************************************************
// Section: TMR Driver Configuration
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* TMR Interrupt And Polled Mode Operation Control

  Summary:
    Macro controls operation of the driver in the interrupt or polled mode

  Description:
    This macro controls the operation of the driver in the interrupt
    mode of operation. The possible values of this macro is
    - true - Select if interrupt mode of timer operation is desired
    - false - Select if polling mode of timer operation is desired.
    Not defining this option to true or false will result in build error.

  Remarks:
    None.
*/

#define DRV_TMR_CONFIG_TASKS_MODE_INTERRUPT_ENABLE          true


// *****************************************************************************
/* TMR driver objects configuration

  Summary
    Sets up the maximum number of hardware instances that can be supported

  Description
    Sets up the maximum number of hardware instances that can be supported

  Remarks:
    None
*/

#define DRV_TMR_CONFIG_DRIVER_OBJECTS_NUMBER 1


// *****************************************************************************
/* TMR Client Count Configuration

  Summary
    Sets up the maximum number of clients that can be connected to any hardware
    instance.

  Description
    Sets up the maximum number of clients that can be connected to any hardware
    instance.

  Remarks:
    None
*/

#define DRV_TMR_CONFIG_CLIENT_OBJECTS_NUMBER 1


// *****************************************************************************
/* TMR Static PLIB ID Selection

   Summary
    TMR Static PLIB ID Selection

   Description
    TMR Static PLIB ID Selection

   Remarks:
    Note: Some devices also support TMR_ID_0
*/

#define DRV_TMR_CONFIG_INIT_PLIB_ID                              APP_TMR_ID


// *****************************************************************************
/* TMR Interrupt Source

   Summary:
    Macro to define the interrupt source in case of static driver

   Description:
    Macro to define the interrupt source in case of static driver

   Remarks:
    Refer to the INT PLIB document for more information on PLIB_INT_SOURCE
    enumeration
 */

#define DRV_TMR_CONFIG_INIT_INTERRUPT_SOURCE                  APP_TMR_INT_SOURCE


// *****************************************************************************
/* TMR mode configuration

  Summary:
    Macro controls mode of the TMR

  Description:
    This macro controls the mode of the TMR, it selects that the timer needs
    to support 8 bit, 16 bit or 32 bit mode. The acceptable values of this
    configuration is
         - 8, (Use this for 8 bit timers)
         - 16 (Use this for 16 bit timers)
         - 32 (Use this for 32 bit timers)

  Remarks:
    This is a Mandatory config option, which enables the TMR count width.
*/

#define DRV_TMR_CONFIG_TIMER_MODE_SELECT        16


// *****************************************************************************
/* TMR Operating mode configuration

   Summary:
    Macro controls Operating mode of the TMR

   Description:
    This macro controls the Operating mode of the TMR
    It takes in one of the possible values of the enumeration
    DRV_TMR_SYNC_MODE

   Remarks:
    If defined in the configuration, takes priority over the initialization
    option
*/

#define DRV_TMR_CONFIG_INIT_SYNC_MODE    DRV_TMR_SYNC_MODE_SYNCHRONOUS_INTERNAL


// *****************************************************************************
/* TMR Value Initial Value

   Summary:
    TMR value for an overflow or a period match based timer

   Description:
    TMR value for an overflow or a period match based timer

   Remarks:
    If defined in the configuration, takes priority over the initialization
    option
    Note: User is required to give the count value. Driver will internally
    adjust the value as required for the TMR hardware based on the overflow or
    period match functionality
*/

#define DRV_TMR_CONFIG_INIT_INITIAL_COUNT    APP_TMR_10mS


// *****************************************************************************
/* TMR Clock Source

   Summary:
    TMR module clock source selection

   Description:
    TMR module clock source selection, based on the enumeration


   Remarks:
    If defined in the configuration, takes priority over the initialization
    option
    Refer to the processor peripheral header for more information
*/

#define DRV_TMR_CONFIG_INIT_CLOCK_SOURCE     PLIB_TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK


// *****************************************************************************
/* TMR Prescale

   Summary:
    TMR module prescale value

   Description:
    TMR module prescale value

   Remarks:
    If defined in the configuration, takes priority over the initialization
    option
    Refer to the processor peripheral header for more information
*/

#define DRV_TMR_CONFIG_INIT_PRESCALE     PLIB_TMR_PRESCALE_TX_VALUE_256


// *****************************************************************************
/* Selecting the alarm functionality

  Summary:
    Alarm Functionality

  Description:
    This feature enables the alarm functionality inside the TMR driver.

   Remarks:
    This is an additional feature
*/

#define DRV_TMR_CONFIG_OPT_ALARM


// *****************************************************************************
/* Alarm type configuration option for periodic alarm

  Summary:
    Alarm type configuration

  Description:
    This value, if used enables Alarm type
    - DRV_TMR_CONFIG_OPT_ALARM_PERIODIC    false - Periodic Alarm

   Remarks:
    Continuous or a periodic alarm
*/

#define DRV_TMR_CONFIG_OPT_ALARM_PERIODIC    true


// *****************************************************************************
/* TMR alarm Callback notification Configuration

   Summary
    Sets up notification mechanism in the TMR driver through alarms

   Description
    Sets up the notification mechanism in the TMR driver alarms
    When this is defined the driver will call the callback functions if
    registered when the transactions are complete.

   Remarks:
    None
*/

#define DRV_TMR_CONFIG_OPT_ALARM_CALLBACKS


// *****************************************************************************
/* TMR post scale configuration

   Summary:
    Macro controls post scale of the TMR

   Description:
    This macro controls the post scale of the TMR

   Remarks:
    Note: This feature may not be available in the device or the TMR module
    selected
*/

#define DRV_TMR_CONFIG_INIT_POSTSCALE_SELECT 0


// *****************************************************************************
/* TMR power state configuration

  Summary:
    Macro controls power state of the TMR

  Description:
    This macro controls the power state of the TMR

  Remarks:
    Note: This feature may not be available in the device or the TMR module
    selected
*/

#define DRV_TMR_CONFIG_INIT_POWER_STATE                 SYS_MODULE_POWER_IDLE_STOP




// *****************************************************************************
// *****************************************************************************
// Section: System Timer Service Configuration
// *****************************************************************************
// *****************************************************************************

#define DRV_TMR_COUNT_WIDTH 16 // Max 16 for Timer 0

#define SYS_TMR_MAX_PERIODIC_EVENTS 2 // TODO: what should this be?

#define DRV_TMR_INDEX 1 // TODO: what should this be?

#define DRV_TMR_INTERRUPT_MODE 0
#define DRV_TMR_INSTANCES_NUMBER 4
#define DRV_TMR_CLIENTS_NUMBER 4

#endif // _SYS_CONFIG_H
/*******************************************************************************
 End of File
*/


