/*******************************************************************************
  Timer Driver Build Variant implementation for static driver

  Company:
    Microchip Technology Inc.

  FileName:
    drv_tmr_hw_static.c

  Summary:
    Timer driver build variant implementation for static driver.

  Description:
    This file defines the build variant implementations for the static driver.
    While building the driver from source, use this file in the build when
    DRV_TMR_INSTANCES_NUMBER is not defined in system configuration.
*******************************************************************************/

//DOM-IGNORE-BEGIN
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
//DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: File includes
// *****************************************************************************
// *****************************************************************************

#include "tmr/src/drv_tmr_local.h"

// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Driver Hardware instance objects.

  Summary:
    Defines the hardware instances objects that are available on the device.

  Description:
    This data type defines the hardware instance objects that are available on
    the device, so as to capture the hardware state of the instance.

  Remarks:
    Not all modes are available on all devices.
*/

DRV_TMR_OBJECT   _DRV_TMR_OBJ_MAKE_NAME ( gDrvTMRObj ) ;

/*******************************************************************************
End of File
*/

