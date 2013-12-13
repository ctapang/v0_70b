/*******************************************************************************
 System Initialization File

  File Name:
    system_init.c

  Summary:
    System Initialization.

  Description:
    This file contains source code necessary to initialize the system.
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

#include "app.h"


// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
// ****************************************************************************

/*
 System PLL Output Clock Divider (FPLLODIV)     = Divide by 1
 PLL Multiplier (FPLLMUL)                       = Multiply by 20
 PLL Input Divider (FPLLIDIV)                   = Divide by 2
 Watchdog Timer Enable (FWDTEN)                 = Disabled
 Clock Switching and Monitor Selection (FCKSM)  = Clock Switch Enable,
                                                  Fail Safe Clock Monitoring Enable
 Peripheral Clock Divisor (FPBDIV)              = Divide by 2
 */
// TODO configure the correct confiugraiton fuse settings for your part
#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FCKSM = CSECME, FPBDIV = DIV_1
#pragma config OSCIOFNC = ON, POSCMOD = XT, FSOSCEN = ON, FNOSC = PRIPLL
#pragma config CP = OFF, BWP = OFF, PWP = OFF
#pragma config ICESEL = ICS_PGx2


// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* SPI Driver Initialization Data

  Summary:
    Defines the SPI driver's initialization data

  Description
    This structure defines the SPI driver's initialization data, passed into
    the driver's initialization routine ("DRV_SPI_Initialize") by the
    system's ("SYS_Initialize") routine.

  Remarks:
    None.
*/

// SPI1 is set to slave, receive-only mode.
DRV_SPI_INIT drvSPIInit1 =
{
    /* Requested power state */
    .moduleInit.sys.powerState = SYS_MODULE_POWER_RUN_FULL,

    /* Identifies USART hardware module (PLIB-level) ID */
    .spiId = SPI_ID_1,

    /* Operation Modes of the SPI driver */
    .spiMode = DRV_SPI_MODE_SLAVE,

    /* SPI Protocol Type */
    .spiProtocolType = DRV_SPI_PROTOCOL_TYPE_STANDARD,

    /* SPI Communication Width */
    .commWidth = SPI_COMMUNICATION_WIDTH_8BITS,

    /* SPI Baud Rate Value */
    .baudRate = 10000000,

    /* SPI Buffer Type */
    .bufferType  = DRV_SPI_BUFFER_TYPE_STANDARD,

    /* FIFO RX Interrupt Mode */
    .rxInterruptMode = SPI_FIFO_INTERRUPT_WHEN_RECEIVE_BUFFER_IS_NOT_EMPTY,

    /* FIFO TX Interrupt Mode */
    .txInterruptMode = SPI_FIFO_INTERRUPT_WHEN_TRANSMISSION_IS_COMPLETE,

    /* SPI Clock mode */
    .clockMode = DRV_SPI_CLOCK_MODE_IDLE_HIGH_EDGE_FALL,

    /* SPI Input Sample Phase Selection. NOTE: ignored in this case (in slave mode) */
    .inputSamplePhase = SPI_INPUT_SAMPLING_PHASE_AT_END,

    /* Transmit Interrupt Source for SPI module NOTE: no transmit */
    .txInterruptSource = INT_SOURCE_SPI_1_TRANSMIT,

    /* Receive Interrupt Source for SPI module */
    .rxInterruptSource = INT_SOURCE_SPI_1_RECEIVE,

    /* Error Interrupt Source for SPI module */
    .errInterruptSource = INT_SOURCE_SPI_1_ERROR,
};

// SPI2 is set in master transmit-only mode.
DRV_SPI_INIT drvSPIInit2 =
{
    /* Requested power state */
    .moduleInit.sys.powerState = SYS_MODULE_POWER_RUN_FULL,

    /* Identifies USART hardware module (PLIB-level) ID */
    .spiId = SPI_ID_2,

    /* Operation Modes of the SPI driver */
    .spiMode = DRV_SPI_MODE_MASTER,

    /* SPI Protocol Type */
    .spiProtocolType = DRV_SPI_PROTOCOL_TYPE_STANDARD,

    /* SPI Communication Width */
    .commWidth = SPI_COMMUNICATION_WIDTH_8BITS,

    /* SPI Baud Rate Value */
    .baudRate = 10000000,

    /* SPI Buffer Type */
    .bufferType  = DRV_SPI_BUFFER_TYPE_STANDARD,

    /* FIFO RX Interrupt Mode */
    .rxInterruptMode = SPI_FIFO_INTERRUPT_WHEN_RECEIVE_BUFFER_IS_NOT_EMPTY,

    /* FIFO TX Interrupt Mode */
    .txInterruptMode = SPI_FIFO_INTERRUPT_WHEN_TRANSMISSION_IS_COMPLETE,

    /* SPI Clock mode */
    .clockMode = DRV_SPI_CLOCK_MODE_IDLE_HIGH_EDGE_RISE,

    /* SPI Input Sample Phase Selection. NOTE: this is for input, but this module is output only */
    .inputSamplePhase = SPI_INPUT_SAMPLING_PHASE_AT_END,

    /* Transmit Interrupt Source for SPI module */
    .txInterruptSource = INT_SOURCE_SPI_2_TRANSMIT,

    /* Receive Interrupt Source for SPI module. NOTE: no receive */
    .rxInterruptSource = INT_SOURCE_SPI_2_RECEIVE,

    /* Error Interrupt Source for SPI module */
    .errInterruptSource = INT_SOURCE_SPI_2_ERROR,
};



// *****************************************************************************
/* USB Device layer Initialization Data

  Summary:
    Defines the device layer initialization data

  Description
    This structure defines the device layer's initialization data.

  Remarks:
    None.
*/

//USB_DEVICE_INIT usbDevInitData =
//{
//    /* System module initialization */
//    {SYS_MODULE_POWER_RUN_FULL},
//
//    /* USB device driver client index*/
//    DRV_USB_INDEX_0,
//
//    false, // never stop USB
//
//    false, // never suspend USB
//
//    INT_SOURCE_USB_1,  // interrupt source (specific to PIC32MX250F128B)
//
//    (void *)NULL,   // end point table
//
//    USB_DEVICE_INSTANCES_NUMBER,    // registered func count
//
//    /* Function driver table registered to this instance of the USB device layer*/
//    (USB_DEVICE_FUNC_REGISTRATION_TABLE*)funcRegistrationTable,
//
//    /* Pointer to USB Descriptor structure */
//    (USB_MASTER_DESCRIPTOR*)&usbMasterDescriptor,
//
//    USB_SPEED_HIGH
//};


// *****************************************************************************
/* USB controller driver Initialization Data

  Summary:
    Defines the USB controller driver Initialization Data

  Description
    This structure defines the USB controller driver Initialization Data.

  Remarks:
    None.
*/

DRV_USB_INIT usbCDInitData =
{
    /* System module initialization */
    {SYS_MODULE_POWER_RUN_FULL},

    /* Identifies peripheral (PLIB-level) ID */
    USB_ID_1,

    /* stop in idle */
    false,

    /* suspend in sleep */
    false,

    /* interrupt source */
    INT_SOURCE_USB_1,

    /* USB Speed */
    USB_SPEED_HIGH,

    /* USB Op Mode */
    USB_OPMODE_DEVICE,

    /* Endpoint Descriptor Table buffer */
    (void*)NULL
};


// ****************************************************************************
// ****************************************************************************
// Section: System Initialization
// ****************************************************************************
// ****************************************************************************

/*******************************************************************************
  Function:
    void SYS_Initialize ( SYS_INIT_DATA *data )

  Summary:
    Initializes the board, services, drivers, application and other modules

  Description:
    This routine initializes the board, services, drivers, application and other
    modules as configured at build time.  In a bare-metal environment (where no
    OS is supported), this routine should be called almost immediately after
    entering the "main" routine.

  Precondition:
    The C-language run-time environment and stack must have been initialized.

  Parameters:
    data        - Pointer to the system initialzation data structure containing
                  pointers to the board, system service, and driver
                  initialization routines
  Returns:
    None.

  Example:
    <code>
    SYS_INT_Initialize(NULL);
    </code>

  Remarks:
    Basic System Initialization Sequence:

    1.  Initilize minimal board services and processor-specific items
        (enough to use the board to initialize drivers and services)
    2.  Initialize all supported system services
    3.  Initialize all supported modules
        (libraries, drivers, middleware, and application-level modules)
    4.  Initialize the main (static) application, if present.

    The order in which services and modules are initialized and started may be
    important.

    For a static system (a system not using the Harmony's dynamic implementation
    of the initialization and "Tasks" services) this routine is implemented
    for the specific configuration of an application.
 */

void SYS_Initialize ( void* data )
{

    /* Initialize the BSP */
    BSP_Initialize ( );

    // TODO perform inialization of the system

    // initialize the timer that manages the tick counter
    //TickInit();

    //Initialize SPI
    DRV_SPI_Initialize ( DRV_SPI_INDEX_0, (SYS_MODULE_INIT *)&drvSPIInit1 );
    DRV_SPI_Initialize ( DRV_SPI_INDEX_1, (SYS_MODULE_INIT *)&drvSPIInit2 );

    //Initialize the USB device layer (this also calls DRV_USB_Initialize)
    USB_DEVICE_Initialize(  0, (SYS_MODULE_INIT *)&usbCDInitData  );

    //Interrupt
    SYS_INT_Initialize();

    /* Initialize the Application */
    APP_Initialize ( );

}


/*******************************************************************************/
/*******************************************************************************
 End of File
*/
