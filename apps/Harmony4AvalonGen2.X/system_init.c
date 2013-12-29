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
/* SYSCLK = 80 MHz (8MHz Crystal / FPLLIDIV * FPLLMUL / FPLLODIV)
   PBCLK = 80 MHz (SYSCLK / FPBDIV) */
// DEVCFG3
// USERID = No Setting
#pragma config PMDL1WAY = ON            // Peripheral Module Disable Configuration (Allow only one reconfiguration)
#pragma config IOL1WAY = ON             // Peripheral Pin Select Configuration (Allow only one reconfiguration)
#pragma config FUSBIDIO = ON            // USB USID Selection (Controlled by the USB Module)
#pragma config FVBUSONIO = ON           // USB VBUS ON Selection (Controlled by USB Module)

// DEVCFG2
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider (3x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (15x Multiplier)
#pragma config FPLLODIV = DIV_256       // System PLL Output Clock Divider (PLL Divide by 256)

// DEVCFG1
#pragma config FNOSC = FRCDIV           // Oscillator Selection Bits (Fast RC Osc w/Div-by-N (FRCDIV))
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disabled)
#pragma config IESO = OFF               // Internal/External Switch Over (Disabled)
#pragma config POSCMOD = OFF            // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_8           // Peripheral Clock Divisor (Pb_Clk is Sys_Clk/8)
#pragma config FCKSM = CSDCMD           // Clock Switching and Monitor Selection (Clock Switch Disable, FSCM Disabled)
#pragma config WDTPS = PS1048576        // Watchdog Timer Postscaler (1:1048576)
#pragma config WINDIS = OFF             // Watchdog Timer Window Enable (Watchdog Timer is in Non-Window Mode)
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (WDT Disabled (SWDTEN Bit Controls))
#pragma config FWDTWINSZ = WISZ_25      // Watchdog Timer Window Size (Window Size is 25%)

// DEVCFG0
#pragma config JTAGEN = ON              // JTAG Enable (JTAG Port Enabled)
#pragma config ICESEL = ICS_PGx2        // ICE/ICD Comm Channel Select (Communicate on PGEC2/PGED2)
#pragma config PWP = OFF                // Program Flash Write Protect (Disable)
#pragma config BWP = OFF                // Boot Flash Write Protect bit (Protection Disabled)
#pragma config CP = OFF                 // Code Protect (Protection Disabled)

#define SYS_FREQUENCY 80000000L

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

    .dataDirection = HALF_DUPLEX,

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

    .dataDirection = HALF_DUPLEX,

    /* SPI Baud Rate Value */
    .baudRate = 10000000,

    /* SPI Buffer Type */
    .bufferType  = DRV_SPI_BUFFER_TYPE_STANDARD,

    /* FIFO RX Interrupt Mode */
    .rxInterruptMode = SPI_FIFO_INTERRUPT_WHEN_RECEIVE_BUFFER_IS_NOT_EMPTY,

    /* FIFO TX Interrupt Mode */
    .txInterruptMode = SPI_FIFO_INTERRUPT_WHEN_TRANSMISSION_IS_COMPLETE,

    /* SPI Clock mode */
    .clockMode = DRV_SPI_CLOCK_MODE_IDLE_LOW_EDGE_RISE,

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

SYS_MODULE_OBJ TimerObjectHandle;
SYS_MODULE_OBJ TimerDriverHandle;
SYS_TMR_INIT TimerInitConfig;

#define ONE_SECOND 31250
#define TEN_SECONDS 10

DRV_TMR_INIT   timerInit =
{
    .tmrId = TMR_ID_2,
    .timerPeriod = ONE_SECOND,
    .clockSource = TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK,
    .interruptSource = INT_SOURCE_TIMER_3,
    .prescale = TMR_PRESCALE_VALUE_256,
    .postscale = TMR_POSTSCALE_NOT_SUPPORTED,
    .sourceEdge = TMR_CLOCK_SOURCE_EDGE_NONE,
    .moduleInit.value = SYS_MODULE_POWER_RUN_FULL,
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

bool TickInit();
void TimerHandler();

extern APP_DATA appObject;

void SYS_Initialize ( void* data )
{
    /*Refer to the C32 peripheral library documentation for more
    information on the SYTEMConfig function.

    This function sets the PB divider, the Flash Wait States, and the DRM
    /wait states to the optimum value.  It also enables the cacheability for
    the K0 segment.  It could has side effects of possibly alter the pre-fetch
    buffer and cache.  It sets the RAM wait states to 0.  Other than
    the SYS_FREQ, this takes these parameters.  The top 3 may be '|'ed
    together:*/

    SYSTEMConfigPerformance(SYS_FREQUENCY);


    /* Initialize the BSP (Power Supply Voltage and SPI pins and interrupts) */
    BSP_Initialize ( );

    // initialize the timer that manages the tick counter
    TickInit();

    //Initialize input SPI
    appObject.spiReport = DRV_SPI_Initialize ( DRV_SPI_INDEX_0, (SYS_MODULE_INIT *)&drvSPIInit1 );

    /* Remap the SPI1 pin */
    PLIB_SPI_PinEnable(SPI_ID_1, SPI_PIN_DATA_IN);
    SYS_PORTS_RemapInput(PORTS_ID_0, INPUT_FUNC_SDI1, INPUT_PIN_RPB1);

    // Initialize output SPI
    appObject.spiConfig = DRV_SPI_Initialize ( DRV_SPI_INDEX_0, (SYS_MODULE_INIT *)&drvSPIInit2 );

    /* Remap the SPI2 pins */
    PLIB_SPI_PinEnable(SPI_ID_2, SPI_PIN_DATA_OUT);
    SYS_PORTS_RemapOutput(PORTS_ID_0, OTPUT_FUNC_SDO2, OUTPUT_PIN_RPB3); // pin 4
    PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_3);

    // Set Pin for clock
    PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_15);

    /* Slave select should be managed by us*/
    //SYS_PORTS_RemapOutput(PORTS_ID_0, OTPUT_FUNC_SS2, OUTPUT_PIN_RPB2);  // pin 3
    //PLIB_SPI_PinEnable(SPI_ID_2, SPI_PIN_DATA_IN);
    PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_2);
    PLIB_PORTS_PinSet( PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_2);

    //Initialize the USB device layer (this also calls DRV_USB_Initialize)
    //USB_DEVICE_Initialize(  0, (SYS_MODULE_INIT *)&usbCDInitData  );

    //Interrupt
    SYS_INT_Initialize();

    /* Initialize the Application */
    APP_Initialize ( );

}

bool TickInit()
{
    TimerInitConfig.moduleInit.value = SYS_MODULE_POWER_RUN_FULL;
    TimerInitConfig.drvIndex = DRV_TMR_INDEX_0;
    TimerInitConfig.alarmPeriod = TEN_SECONDS; // 10 one-second cycles

    TimerDriverHandle = DRV_TMR_Initialize(SYS_TMR_INDEX_0, (SYS_MODULE_INIT*)&timerInit);

    if (TimerDriverHandle == SYS_MODULE_OBJ_INVALID){
        return false;
    }

    TimerObjectHandle = SYS_TMR_Initialize(SYS_TMR_INDEX_0, (SYS_MODULE_INIT*)&TimerInitConfig);

    if (TimerObjectHandle == SYS_MODULE_OBJ_INVALID){
        return false;
    }

    TimerObjectHandle = SYS_TMR_CallbackPeriodic (1, &TimerHandler);

    return true;
}


// *****************************************************************************
// *****************************************************************************
// Section: Interrupt Service Routine
// *****************************************************************************
// *****************************************************************************

extern void BSP_SetVoltage(BSP_VOLTAGE delta);

void TimerHandler(void)
{
    BSP_SetVoltage(1);
}


/*******************************************************************************/
/*******************************************************************************
 End of File
*/
