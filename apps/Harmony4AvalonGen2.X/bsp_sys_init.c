/*******************************************************************************
 Board initialization file for Condo Hash Unit

 Company:
    Centerus Inc.

 File Name:
    bsp_sys_init.c

 Summary:
    Board initialization file for Condo Hash Unit

 Description:
    This file contains the initialization of board specific I/O.
 *******************************************************************************/



// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "app.h"

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
    .commWidth = SPI_COMMUNICATION_WIDTH_32BITS,

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
    .commWidth = SPI_COMMUNICATION_WIDTH_32BITS,

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
// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function: void BSP_Initialize(void)

  Summary:
    Performs the neccassary actions to initialize a board

  Description:
    This routine performs the neccassary actions to initialize a board

  Remarks:
    This routine performs direct register accesses, when the PORTS PLIB and
    system service become available, these register accesses will be be replaced
    by the PLIB\system service interfaces.

*/

void SpinDelay(uint16_t delay);
void BSP_SetVoltage(char level);

void BSP_Initialize(void )
{
    // Set LM10011 Voltage Control Pins:
    // VIDA == bit 0 in first word, bit 3 in second
    // VIDB == bit 1 in first word, bit 4 in second
    // VIDC == bit 2 in first word, bit 5 in second (total six bits resolution)
    // VIDS == latch control: first word during high-to-low transition,
    //         second word during low-to-high transition.
    //
    // Pin Assignment:
    // VIDA: Pin 6 (OSC1, RA2)
    // VIDB: Pin 7 (Osc2, RA3)
    // VIDC: Pin 8 (RB4)
    // VIDS: Pin 9 (RA4)

    //PLIB_PORTS_DirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_A, VIDA );
    PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_A, VIDA );
    PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_A, VIDB );
    PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_B, VIDC );
    PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_A, VIDS );

    PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_A, VIDA );
    PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_A, VIDB );
    PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_B, VIDC );
    PLIB_PORTS_PinSet( PORTS_ID_0, PORT_CHANNEL_A, VIDS);

    // Allow the logic levels to stabilize on the LM10011
    SpinDelay((uint16_t)22);

    // Set voltage to about 0.9V (0.872 + level * 0.00345)
    BSP_SetVoltage((char)9);

    // Set SPI (both ports)
    //
    // SPI1 is used for REPORT signal input, it is a SLAVE
    // SCK1 is on Pin22/RB14 (not configurable), and
    // SDI1 is on Pin2/RB1 (no SS and no SDO)
    //
    // SPI2 is used for CONFIG output signal, it is a MASTER
    // SCK2 is on Pin23 (not configurable)
    // SDO2 is on Pin4/RB3 (no SDI)
    // SS2  is on Pin3/RB2

    //Initialize input SPI (connected to REPORT signal from Avalon Gen2 chips)
    appObject.spiReport = DRV_SPI_Initialize ( DRV_SPI_INDEX_0, (SYS_MODULE_INIT *)&drvSPIInit1 );

    /* Remap the SPI1 pin */
    PLIB_SPI_PinEnable(SPI_ID_1, SPI_PIN_DATA_IN);
    SYS_PORTS_RemapInput(PORTS_ID_0, INPUT_FUNC_SDI1, INPUT_PIN_RPB1);

    // Initialize output SPI (connected to CONFIG signal to Avalon Gen2 chips)
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

    /* set priority for SPI interrupt source */
    SYS_INT_VectorPrioritySet(INT_VECTOR_SPI2, INT_PRIORITY_LEVEL3);
    SYS_INT_VectorPrioritySet(INT_VECTOR_SPI1, INT_PRIORITY_LEVEL3);
    SYS_INT_VectorSubprioritySet(INT_VECTOR_SPI2, INT_SUBPRIORITY_LEVEL1);
    SYS_INT_VectorSubprioritySet(INT_VECTOR_SPI1, INT_SUBPRIORITY_LEVEL1);

    SYS_INT_SourceEnable(INT_SOURCE_SPI_1_RECEIVE);
    SYS_INT_SourceEnable(INT_SOURCE_SPI_2_TRANSMIT);
}

// Input level can be from 0 to 64. Every increment is +3.45 mV.
void BSP_SetVoltage(char level)
{
    SYS_ASSERT( (level >= 0) && (level < 64), "Voltage level input invalid." );
    if ((level < 0) || (level > 63))
        return; // FIXME: This should be an exception
    
    char shifter = 1;
    if (shifter & level)
        PLIB_PORTS_PinSet( PORTS_ID_0, PORT_CHANNEL_A, VIDA);
    else
        PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_A, VIDA );
    shifter <<= 1; // shift by one to the left
    if (shifter & level)
        PLIB_PORTS_PinSet( PORTS_ID_0, PORT_CHANNEL_A, VIDB);
    else
        PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_A, VIDB );
    shifter <<= 1; // shift by one to the left
    if (shifter & level)
        PLIB_PORTS_PinSet( PORTS_ID_0, PORT_CHANNEL_B, VIDC);
    else
        PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_B, VIDC );
    shifter <<= 1; // shift by one to the left

    // latch first three bits (falling VIDS latches)
    PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_A, VIDS );

    // LM10011 needs at least 20uS hold time
    // Let's give it plenty of time: 220 loops of 4 instructions = 880 * 25nS = 22uS.
    // Note that if interrupts are enabled, this delay can be longer.
    SpinDelay((uint16_t)22);

    // now continue with higher 3 bits
    if (shifter & level)
        PLIB_PORTS_PinSet( PORTS_ID_0, PORT_CHANNEL_A, VIDA);
    else
        PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_A, VIDA );
    shifter <<= 1; // shift by one to the left
    if (shifter & level)
        PLIB_PORTS_PinSet( PORTS_ID_0, PORT_CHANNEL_A, VIDB);
    else
        PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_A, VIDB);
    shifter <<= 1; // shift by one to the left
    if (shifter & level)
        PLIB_PORTS_PinSet( PORTS_ID_0, PORT_CHANNEL_B, VIDC);
    else
        PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_B, VIDC);

    // latch higher 3 bits (rising VIDS does this)
    PLIB_PORTS_PinSet( PORTS_ID_0, PORT_CHANNEL_A, VIDS);
}


// Delay by delay uSecs. (Input param should be in units of uSecs.)
// Each CPU cycle lasts 25nSec, so to delay by 1uSec, we need
// 40 cycles (1uSec = 1000 nSec = 1000 / 25 = 40 CPU cycles.
void SpinDelay(uint16_t delay)
{
    SYS_ASSERT( delay < 1000, "For delays longer than 1000 uSec, use timer." );

    uint16_t nanoSecsPerCycle = (1000000000L / SYS_FREQUENCY);

    SYS_ASSERT( nanoSecsPerCycle > 10, "System clock maybe too high forthis." );

    uint16_t loopsPerMicroSec = (1000L / nanoSecsPerCycle) / 4; // about 4 instructions per loop
    uint16_t loops = delay * loopsPerMicroSec;

    int x = 0; // just so the loop below does not get optimized out
    uint16_t i = 0;
    for (; i < loops; i++)
        x++;
}


uint32_t BSP_ReadCoreTimer()
{
    uint32_t timer;

    // get the count reg
    asm volatile("mfc0   %0, $9" : "=r"(timer));

    return(timer);
}


/******************************************************************************/
/******************************************************************************/


/*******************************************************************************
 End of File
*/
