/*******************************************************************************
 Board support configuration file.

 Company:      
 Centerus, Inc.

 File Name:    
    bsp_config.h

 Summary:      
    Board support configuration file.

 Description:
    This contains all the configuration that is required to be done for the 
    application running on PIC32 USB condo hashing unit.
*******************************************************************************/

#ifndef _BSP_CONFIG_H
#define _BSP_CONFIG_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "tmr/src/sys_tmr_local.h"
//#include "system/ports/sys_ports.h"
#include "system/int/sys_int_mapping.h"
#include "peripheral/ports/plib_ports.h"
#include "peripheral/int/plib_int.h"
#include "peripheral/spi/plib_spi.h"
#include "peripheral/usb/plib_usb.h"
#include "driver/spi/src/drv_spi_local.h"
#include "driver/usb/src/drv_usb_local.h"

/******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Constants
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Input Constant

  Summary:
    Defines the constant which identifies input

  Description:
    This constant identifies input
*/

#define BSP_INPUT                               1


// *****************************************************************************
/* Output Constant

  Summary:
    Defines the constant which identifies output

  Description:
    This constant identifies output
*/

#define BSP_OUTPUT                              0


// *****************************************************************************
/* Digital Pin Constant

  Summary:
    Defines the constant which identifies digital pin

  Description:
    This constant identifies digital pin
*/

#define BSP_DIGITAL_PIN                         PORTS_PIN_MODE_DIGITAL

// *****************************************************************************
/* analog Pin Constant

  Summary:
    Defines the constant which identifies analog pin

  Description:
    This constant identifies analog pin
*/

#define BSP_ANALOG_PIN                          PORTS_PIN_MODE_ANALOG


// SPI Interrupt Sources

#define INT_VECTOR_SPI2_TX                      1 // FIXME
#define INT_VECTOR_SPI1_RX                      0 // FIXME

// *****************************************************************************
/* LM10011 Voltage Control Pins.

  Summary:
    Holds Voltage Control numbers.

  Description:
    This enumeration defines the Voltage Control numbers.

  Remarks:
    None.
*/

typedef enum
{
    /* VIDA */
    VIDA = PORTS_BIT_POS_2,

    /* VIDB */
    VIDB = PORTS_BIT_POS_3,

    /* VIDC */
    VIDC = PORTS_BIT_POS_4,

    /* VIDS */
    VIDS = PORTS_BIT_POS_4
}BSP_VOLTAGE;


// *****************************************************************************
// *****************************************************************************
// Section: UART Pins
// *****************************************************************************
// *****************************************************************************
/* The section below identifies the pins that are associated with the UART
   connected to RS232 on the board */


// *****************************************************************************
// *****************************************************************************
// Section: Analog Inputs Connected Potentiometer
// *****************************************************************************
// *****************************************************************************
/* The section below identifies the analog inputs connected to potentiometer */


// *****************************************************************************
// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Function: void BSP_Initialize(void)

  Summary:
    Performs the necessary actions to initialize a board
  Description:
    This function initializes all the Three LEDs and Three switches present
    on the board. This function must be called by the user before using any
    APIs present on this BSP.
  Parameters:
    None
  Return:
    None
  Conditions:
    None                                                                   
  **************************************************************************/

void BSP_Initialize(void);

// *****************************************************************************
/* Function: unsigned int SYSTEMConfigPerformance(unsigned int sys_clock)

  Summary:
    Configures the system cache and flash wait states for maximum performance

  Description:
    This function configures the system cache and flash wait states for
    maximum performance. 
  Parameters:
    sys_clock: Value of system clock
  Return values:
    Value of Peripheral clock
  Conditions:
    None
*/

unsigned int SYSTEMConfigPerformance(unsigned int sys_clock);





// *****************************************************************************
/* Function:
    uint32_t BSP_ReadCoreTimer()
  Summary:
    Returns the current core timer value.
  Description:
    Returns the current core timer value.
  Parameters:
    None
  Return Values:
    Current Core timer value.
  Conditions:
    None
*/

uint32_t BSP_ReadCoreTimer();



#endif //_BSP_CONFIG_H

/*******************************************************************************
 End of File
*/
