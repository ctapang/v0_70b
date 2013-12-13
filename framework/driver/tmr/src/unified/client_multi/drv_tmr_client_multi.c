/*******************************************************************************
  Timer Driver Client Dynamic Handling Interfaces

  Company:
    Microchip Technology Inc.

  FileName:
    drv_tmr_client_multi.c

  Summary:
    Timer driver client dynamic handling interfaces.

  Description:
    This file implements the functions for the multiple client support. 
    While building the driver from source, use this file in the build when
    DRV_TMR_CLIENTS_NUMBER is defined in the system configuration
    or when DRV_TMR_INSTANCES_NUMBER is defined in the system
    configuration. 
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
/* Driver Client instance objects.

  Summary:
    Defines the client instances objects that are available on the device.

  Description:
    This data type defines the client instance objects that are available on
    the device, so as to capture the Client state of the instance.

  Remarks:
    None.
*/

DRV_TMR_CLIENT_OBJECT   gDrvTMRClientObj[DRV_TMR_INSTANCES_NUMBER] ;


/*******************************************************************************
End of File
*/

