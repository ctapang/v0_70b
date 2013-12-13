/*******************************************************************************

  Summary:
    
  Description:
*******************************************************************************/

/*******************************************************************************
FileName:  system_config.h 
Copyright ?2012 released Microchip Technology Inc.  All rights
reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED �AS IS" WITHOUT WARRANTY OF ANY KIND,
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

#ifndef _SYSTEM_CONFIG_H
#define _SYSTEM_CONFIG_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "system/common/sys_common.h"
#undef SYS_ASSERT // disable definition
#include "system/common/sys_module.h"

// *****************************************************************************
// *****************************************************************************
// Section: System Error Message Support
// *****************************************************************************
// *****************************************************************************


#if defined(USE_ISP_DEBUG) && defined(__MPLAB_DEBUGGER_PIC32MXSK)
#define PLIB_ASSERT(test,message)   ((void)( (test) ? 0 : AssertToIDE(#test,message,__LINE__,__FILE__), 0))
#endif

// *****************************************************************************
// *****************************************************************************
// Section: Ethernet PHY Configuration
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* ETHPHY hardware instance configuration

  Summary:
    Selects the maximum number of hardware instances that can be supported by
    the dynamic driver

  Description:
    This definition selects the maximum number of hardware instances that can be
    supported by the dynamic driver. Not defining it means using a static driver.

  Remarks:
    None
*/

#define DRV_ETHPHY_INSTANCES_NUMBER                1


// *****************************************************************************
/* ETHPHY Maximum Number of Clients

  Summary:
    Selects the miximum number of clients

  Description:
    This definition select the maximum number of clients that the ETHPHY driver can
    support at run time. Not defining it means using a single client.

  Remarks:
    None.

*/

#define DRV_ETHPHY_CLIENTS_NUMBER                1


// *****************************************************************************
/* ETHPHY Static Index Selection

  Summary:
    ETHPHY Static Index selection

  Description:
    ETHPHY Static Index selection for the driver object reference

  Remarks:
    This index is required to make a reference to the driver object
*/

#define DRV_ETHPHY_INDEX                                DRV_ETHPHY_INDEX_1


// *****************************************************************************
/* ETHPHY Interrupt And Polled Mode Operation Control

*/
// Ethernet PHY has no interrupts
//#define DRV_ETHPHY_INTERRUPT_MODE          true


// Section: Initialization Overrides
/* This section defines the initialization overrides */

// *****************************************************************************
/* ETHPHY Peripheral ID Selection

  Summary:
    Defines an override of the peripheral id.

  Description:
    Defines an override of the peripheral id, using macros

  Remarks:

    Note: Some devices also support ETHPHY_ID_0
*/

#define DRV_ETHPHY_PERIPHERAL_ID                         ETHPHY_ID_1


// *****************************************************************************
/* ETHPHY power state configuration

  Summary:
    Defines an override of the power state of the ETHPHY driver.

  Description:
    Defines an override of the power state of the ETHPHY driver.

  Remarks:
    Note: This feature may not be available in the device or the ETHPHY module
    selected.
*/

// Has no power modes
//#define DRV_ETHPHY_POWER_STATE                 SYS_MODULE_POWER_IDLE_STOP


// Additional Initialization Overrides

// Originally in eth_pic32_ext_phy.h

#define PHY_NEG_INIT_TMO  1       // negotiation initiation timeout, ms.

#define PHY_NEG_DONE_TMO  2000        // negotiation complete timeout, ms.
                        // based on IEEE 802.3 Clause 28 Table 28-9 autoneg_wait_timer value (max 1s)

#define PHY_RESET_CLR_TMO 500     // reset self clear timeout, ms.
                        // IEEE 802.3 Clause 22 Table 22-7 and paragraph "22.2.4.1.1 Reset" (max 0.5s)


#include "hardware_config.h"


// *****************************************************************************
// *****************************************************************************
// Section: Ethernet MAC Configuration
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Ethernet MAC hardware instance configuration

  Summary:
    Selects the maximum number of hardware instances that can be supported by
    the dynamic driver

  Description:
    This definition selects the maximum number of hardware instances that can be
    supported by the dynamic driver. Not defining it means using a static driver.

  Remarks:
    None
*/

#define DRV_ETHMAC_INSTANCES_NUMBER  1


// *****************************************************************************
/* Ethernet MAC Maximum Number of Clients

  Summary:
    Selects the miximum number of clients

  Description:
    This definition select the maximum number of clients that the Ethernet MAC
    driver can support at run time. Not defining it means using a single client.

  Remarks:
    None.

*/

#define DRV_ETHMAC_CLIENTS_NUMBER  1


// *****************************************************************************
/* Ethernet MAC Static Index Selection

  Summary:
    Ethernet MAC Static Index selection

  Description:
    Ethernet MAC Static Index selection for the driver object reference

  Remarks:
    This index is required to make a reference to the driver object
*/

#define DRV_ETHMAC_INDEX  DRV_ETHMAC_INDEX_1


// *****************************************************************************
/* Ethernet MAC Interrupt And Polled Mode Operation Control

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

#define DRV_ETHMAC_INTERRUPT_MODE  true


// Section: Initialization Overrides
/* This section defines the initialization overrides */

// *****************************************************************************
/* Ethernet MAC Peripheral ID Selection

  Summary:
    Defines an override of the peripheral id.

  Description:
    Defines an override of the peripheral id, using macros

  Remarks:

    Note: Some devices also support ETHMAC_ID_0
*/

#define DRV_ETHMAC_PERIPHERAL_ID  ETHMAC_ID_1


// *****************************************************************************
/* Ethernet MAC Interrupt Source

  Summary:
    Defines an override of the interrupt source in case of static driver.

  Description:
    Defines an override of the interrupt source in case of static driver.

  Remarks:
    Refer to the INT PLIB document for more information on INT_SOURCE
    enumeration.

*/

#define DRV_ETHMAC_INTERRUPT_SOURCE  INT_SOURCE_ETH_1


// *****************************************************************************
/* Ethernet MAC power state configuration

  Summary:
    Defines an override of the power state of the Ethernet MAC driver.

  Description:
    Defines an override of the power state of the Ethernet MAC driver.

  Remarks:
    Note: This feature may not be available in the device or the Ethernet MAC module
    selected.
*/

#define DRV_ETHMAC_POWER_STATE  SYS_MODULE_POWER_IDLE_STOP

#endif // _SYSTEM_CONFIG_H

#ifndef __SYSTEM_PROFILE_H_
#define __SYSTEM_PROFILE_H_

/*****************************************************************************
 * The number of ticks per second. 
 * This is used to define timeouts throughout the system.
 * This implementation uses the core timer
 *****************************************************************************/
#define SYS_TICKS_PER_SECOND        1000

/*****************************************************************************
 * The interrupt priority (1-lowest to 7-highest) and sub-priority (0 to 3) for the timer used to generate the system ticks
 *****************************************************************************/
#define	SYS_TICK_IPL		4
#define	SYS_TICK_SIPL		1


/*****************************************************************************
 * The system debug enable
 * Use to enable the debug messages.
 *****************************************************************************/
#define SYS_DEBUG_ENABLE


/*****************************************************************************
 * The current system error level
 * System error functions use this level 
 * to suppress/ or not the output of a
 * SYS_ERROR message.
 *****************************************************************************/
#define SYSTEM_CURRENT_ERROR_LEVEL  SYS_ERROR_DEBUG



/*****************************************************************************
 * The system debug peripheral
 * Specify the debug port.
 *****************************************************************************/
//#define SYS_DEBUG_PORT          SYS_MODULE_DBAPPIO
#define SYS_DEBUG_PORT          SYS_MODULE_UART_2

/*****************************************************************************
 * The system debug peripheral
 * Specify the debug port baud rate.
 *****************************************************************************/
#define SYS_DEBUG_BAUDRATE      115200

/*****************************************************************************
 * The system console enable
 * Use to enable the system console
 *****************************************************************************/
#define SYS_CONSOLE_ENABLE


/*****************************************************************************
 * The system console comm channel
 * Specify the console port.
 *****************************************************************************/
//#define SYS_CONSOLE_PORT          SYS_MODULE_DBAPPIO
#define SYS_CONSOLE_PORT          SYS_MODULE_UART_2

/*****************************************************************************
 * The system console comm channel
 * Specify the console bit rate.
 *****************************************************************************/
#define SYS_CONSOLE_BAUDRATE     115200

/*****************************************************************************
 * The system console buffer space
 * Specify the length of the buffering for the console operations.
 *****************************************************************************/
#define SYS_CONSOLE_BUFFER_LEN   200



/*****************************************************************************
 * Enable the system output functionality.
 * The output port is usually imnplemented
 * using an LCD on boards that support it.
 *****************************************************************************/
//#define SYS_OUT_ENABLE

/*****************************************************************************
 * The system out channel
 * Specify the output port.
 *****************************************************************************/
#define SYS_OUT_PORT          SYS_MODULE_CHAR_LCD



/*****************************************************************************
 * The system random module
 * Use to enable the system random functionality
 *****************************************************************************/
#define SYS_RANDOM_ENABLE

/*****************************************************************************
 * The system command parser module
 * Use to enable the system command parser functionality
 *****************************************************************************/
#define SYS_COMMAND_ENABLE

/*****************************************************************************
 * The system user io interface module
 * Use to enable the system user io functionality (buttons, LEDs, etc.)
 *****************************************************************************/
#define SYS_USERIO_ENABLE

/*****************************************************************************
 * The system File System module
 * Use to enable the File System functionality (see FS configuration file for details).
 *****************************************************************************/
#define SYS_FS_ENABLE

#include "drv_spi_config.h"
#include "sys_clk_config.h"

#endif	// __SYSTEM_PROFILE_H_

