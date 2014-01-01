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
#pragma config FPLLIDIV = DIV_1         // PLL Input Divider (1x Divider)
#pragma config FPLLMUL = MUL_20         // PLL Multiplier (20x Multiplier, with an overall result of 10x)
#pragma config FPLLODIV = DIV_2         // System PLL Output Clock Divider (PLL Divide by 2)

// DEVCFG1
// NOTE: It seems that for the simulator, no matter what FNOSC is set to, the simulator
// DEVCFG1 register always shows FNOSC = 0.
#pragma config FNOSC = FRCPLL           // Oscillator Selection Bits (Fast RC Osc w/ multipliers and dividers)
#pragma config FSOSCEN = OFF            // Secondary Oscillator Enable (Disabled)
#pragma config IESO = OFF               // Internal/External Switch Over (Disabled)
#pragma config POSCMOD = OFF            // Primary Oscillator Configuration (Primary osc disabled)
#pragma config OSCIOFNC = OFF           // CLKO Output Signal Active on the OSCO Pin (Disabled)
#pragma config FPBDIV = DIV_2           // Peripheral Clock Divisor (Pb_Clk == Sys_Clk / 2)
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

/*Timer load values. Values differ for each processor based on the clock settings*/
/*The given count values are valid only if the device config registers are
 programmed as shown below (see above for the system clock settings)*/
// Explorer 16 Board, XTAL = 8MHz
// PLLIDIV = 2, Freq = 4MHz
// PLLMUL = 20, Freq = 80MHz
// PLLODIV = 1, Freq = 80MHz
// PBDIV = 1,   Freq = 80MHz
// TMR Module I/P = 80MHz
// TMR Prescaler = 1:256 = 312500Hz
// TMR Step = 3.2uS/Count
#define APP_TMR_1S      0x0004C4B4

#define APP_TMR_500mS   0x0002625A

#define APP_TMR_200mS   0x0000F424

#define APP_TMR_100mS   0x00007A12

#define APP_TMR_50mS	0x00003D09

#define APP_TMR_10mS    0x00000C35

#define APP_TMR_1mS     0x00000138

#define ONE_SECOND 312500
#define TEN_SECONDS 1  // FIXME: should be 10, but something's wrong

DRV_TMR_INIT   timerInit =
{
    .moduleInit.value = SYS_MODULE_POWER_RUN_FULL,
    .tmrId = TMR_ID_2,
    .clockSource = TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK,
    .timerPeriod = ONE_SECOND, // FIXME: see alarmPeriod below (this is not really needed because sys_tmr.c calculates this from h/w.)
    .prescale = TMR_PRESCALE_VALUE_256,
    .sourceEdge = TMR_CLOCK_SOURCE_EDGE_NONE,
    .postscale = TMR_POSTSCALE_NOT_SUPPORTED,
    .syncMode = DRV_TMR_SYNC_MODE_SYNCHRONOUS_INTERNAL,
    .interruptSource = INT_SOURCE_TIMER_3, // timer 2 and timer 3 are joined together
};

// "PRIVATE" methods

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

    //Initialize the USB device layer (this also calls DRV_USB_Initialize)
    //USB_DEVICE_Initialize(  0, (SYS_MODULE_INIT *)&usbCDInitData  );

    //Interrupt
    SYS_INT_Initialize();

    // Disable interrrupts for now
    //SYS_INT_Disable();

    /* Initialize the BSP (Power Supply Voltage and SPI pins and interrupts) */
    BSP_Initialize ( );

    // initialize the timer that manages the tick counter
    TickInit();

    /* Initialize the Application */
    APP_Initialize ( );

    /* Enable all defined interrupts */
    SYS_INT_Enable();
}

bool TickInit()
{
    TimerInitConfig.moduleInit.value = SYS_MODULE_POWER_RUN_FULL;
    TimerInitConfig.drvIndex = DRV_TMR_INDEX_0;
    TimerInitConfig.alarmPeriod = TEN_SECONDS;

    clkObject.peripheralClock = SYS_FREQUENCY;

    TimerDriverHandle = DRV_TMR_Initialize(SYS_TMR_INDEX_0, (SYS_MODULE_INIT*)&timerInit);

    if (TimerDriverHandle == SYS_MODULE_OBJ_INVALID){
        return false;
    }

    TimerObjectHandle = SYS_TMR_Initialize(SYS_TMR_INDEX_0, (SYS_MODULE_INIT*)&TimerInitConfig);

    if (TimerObjectHandle == SYS_MODULE_OBJ_INVALID){
        return false;
    }

    // The first param must be a multiple of TimerInitConfig.alarmPeriod (see above).
    TimerObjectHandle = SYS_TMR_CallbackPeriodic (TEN_SECONDS, &TimerHandler);


     /* set priority for Timer 3 interrupt source */
    SYS_INT_VectorPrioritySet(INT_VECTOR_T3, INT_PRIORITY_LEVEL5);

    /* set sub-priority for Timer 3 interrupt source */
    SYS_INT_VectorSubprioritySet(INT_VECTOR_T3, INT_SUBPRIORITY_LEVEL3);

    return true;
}


// *****************************************************************************
// *****************************************************************************
// Section: Interrupt Service Routine
// *****************************************************************************
// *****************************************************************************

extern void BSP_SetVoltage(BSP_VOLTAGE delta);

int j = 0;

void TimerHandler(void)
{
    j++;
    BSP_SetVoltage(j);
    if (j > 63)
        j = 0;
}


/*******************************************************************************/
/*******************************************************************************
 End of File
*/
