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

#include "system_config.h"
#include "bsp_config.h"


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
                                       
    PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_A, VIDA );
    PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_A, VIDB );
    PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_B, VIDC );
    PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0, PORT_CHANNEL_A, VIDS );

    PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_A, VIDA );
    PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_A, VIDB );
    PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_B, VIDC );
    PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_A, VIDS );

    // pulse VIDS
    PLIB_PORTS_PinSet( PORTS_ID_0, PORT_CHANNEL_A, VIDS);
    PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_A, VIDS );

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


    /* Remap the SPI1 pin */
    SYS_PORTS_RemapInput(PORTS_ID_0, INPUT_FUNC_SDI1, INPUT_PIN_RPB1);

    /* Remap the SPI2 pins */
    SYS_PORTS_RemapOutput(PORTS_ID_0, OTPUT_FUNC_SDO2, OUTPUT_PIN_RPB3); // pin 4
    SYS_PORTS_RemapOutput(PORTS_ID_0, OTPUT_FUNC_SS2, OUTPUT_PIN_RPB2);  // pin 3

    /* set priority for SPI interrupt source */
    SYS_INT_VectorPrioritySet(INT_VECTOR_SPI2_TX, INT_PRIORITY_LEVEL3);
    SYS_INT_VectorPrioritySet(INT_VECTOR_SPI1_RX, INT_PRIORITY_LEVEL3);

    /* set sub-priority for SPI interrupt source */
    SYS_INT_VectorSubprioritySet(INT_VECTOR_SPI2_TX, INT_SUBPRIORITY_LEVEL3);
    SYS_INT_VectorSubprioritySet(INT_VECTOR_SPI1_RX, INT_SUBPRIORITY_LEVEL3);
    
}

void BSP_SetVoltage(BSP_VOLTAGE delta)
{

    /* TBD */
    //PLIB_PORTS_PinWrite ( PORTS_ID_0 ,
    //                     PORT_CHANNEL_D ,
    //                     led,
    //                     1 );

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