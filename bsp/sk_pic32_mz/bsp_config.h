/*******************************************************************************
 Board support configuration file.

 Company:      
    Microchip Technology Incorported

 File Name:    
    bsp_config.h

 Summary:      
    Board support configuration file.

 Description:
    This contains all the configuration that is required to be done for the 
    application running on PIC32 USB starter kit
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

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
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
#include "peripheral/ports/plib_ports.h"


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

// *****************************************************************************
/* pixelclock Pin Constants

  Summary:
    Defines the constants which identifies PIXELCLOCK pins

  Description:
    These constants identifies PIXELCLOCK pins
*/

#define PIXELCLOCK        LATDbits.LATD5
#define PIXELCLOCK_TRIS   TRISDbits.TRISD5

// *****************************************************************************
/* BSP Switch.

  Summary:
    Holds Switch numbers.

  Description:
    This enumeration defines the Switch numbers.

  Remarks:
    None.
*/

typedef enum
{
    /* SWITCH 1 */
     SWITCH_1 = PORTS_BIT_POS_12,

    /* SWITCH 2 */
     SWITCH_2 = PORTS_BIT_POS_13,

    /* SWITCH 3 */
     SWITCH_3 = PORTS_BIT_POS_14

}BSP_SWITCH;


// *****************************************************************************
/* BSP Switch state.

  Summary:
    Holds Switch status.

  Description:
    This enumeration defines the switch state.

  Remarks:
    None.
*/

typedef enum
{
    /* Switch pressed */
    BSP_SWITCH_STATE_PRESSED = 0,

   /* Switch not pressed */
    BSP_SWITCH_STATE_RELEASED = 1
}BSP_SWITCH_STATE;


// *****************************************************************************
/* LED Number.

  Summary:
    Holds LED numbers.

  Description:
    This enumeration defines the LED numbers.

  Remarks:
    None.
*/

typedef enum
{
    /* LED 1 on SK */
    LED_1 = PORTS_BIT_POS_0,

    /* RED_LED on SK */
    LED_RED = PORTS_BIT_POS_0,

    /* LED 2 on SK */
    LED_2 = PORTS_BIT_POS_1,

    /* YELLOW_LED on SK */
    LED_YEL = PORTS_BIT_POS_1,

    /* LED 3 on SK */
    LED_3 = PORTS_BIT_POS_2,

    /* GREEN_LED on SK */
    LED_GRN = PORTS_BIT_POS_2

}BSP_LED;

// *****************************************************************************
/* Port bit number for BT module control.

  Summary:
    Holds port bit number for BT module control.

  Description:
    This enumeration is used to enable or disable the BT module. It is required as
    the same pin is used for BT and SD card communication. For certain demos which
    uses SD card, the BT module is disabled.

  Remarks:
    None.
*/
typedef enum
{
    /* Bluetooth disable pin */
    BT_EN = PORTS_BIT_POS_2
            
}BSP_BT_CONTROL;


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

/**************************************************************************
  Function:
     void BSP_Initialize(void);
    
  Summary:
    Performs the necessary actions to initialize a board
  Description:
    This routine performs the neccassary actions to initialize a board
  Parameters:
    None
  Return:
    None
  Conditions:
    None   
*/

void BSP_Initialize(void);

// *****************************************************************************
/* Function: void BSP_SwitchONLED(BSP_LED led)

  Summary:
 Turns ON specified LED on the board.

  Description:
 This fucntion turns ON specified LED on the board.
  Parameters:
    led: LED ID as specified by BSP_LED enum.
  Return:
    None
  Conditions:
    BSP should be initialized by calling void BSP_Initialize(void) function.
*/

void BSP_SwitchONLED(BSP_LED led);

// *****************************************************************************
/* Function:
    void BSP_SwitchOFFLED(BSP_LED led)

  Summary:
 Turns OFF specified LED on the board.

  Description:
 This fucntion turns OFF specified LED on the board.
  Parameters:
    led: LED ID as specified by BSP_LED enum.
  Return:
    None
  Conditions:
    BSP should be initialized by calling void BSP_Initialize(void) function.
*/

void BSP_SwitchOFFLED(BSP_LED led);


// *****************************************************************************
/* Function: void BSP_ToggleLED(BSP_LED led)

  Summary:
 Toggles specified LED on the board.

  Description:
 This fucntion Toggles specified LED on the board.
  Parameters:
    led: LED ID as specified by BSP_LED enum.
  Return:
    None
  Conditions:
    BSP should be initialized by calling void BSP_Initialize(void) function.
*/

void BSP_ToggleLED(BSP_LED led);
// *****************************************************************************
/* Function: unsigned int SYSTEMConfigPerformance(unsigned int sys_clock)

  Summary:
    Configures the system cache and flash wait states for maximum performance.

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
/* Function: BSP_SWITCH_STATE BSP_ReadSwitch( BSP_SWITCH bspSwitch);

  Summary:
    Reads the switch state.

  Description:
    Reads the switch state.
  Parameters:
    bspSwitch: Switch ID as specified by BSP_SWITCH enum.
  Return Values:
    BSP_SWITCH_STATE_PRESSED  - Switch is pressed. 
    BSP_SWITCH_STATE_RELEASED - Switch is not pressed.
  Conditions:
    None

*/

BSP_SWITCH_STATE BSP_ReadSwitch( BSP_SWITCH bspSwitch);



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
