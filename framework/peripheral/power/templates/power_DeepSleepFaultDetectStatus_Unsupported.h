/*******************************************************************************
  POWER Peripheral Library Template Implementation

  File Name:
    power_DeepSleepFaultDetectStatus_Unsupported.h

  Summary:
    POWER PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : DeepSleepFaultDetectStatus
    and its Variant : Unsupported
    For following APIs :
        PLIB_POWER_ExistsDeepSleepFaultDetect
        PLIB_POWER_DeepSleepFaultDetectStatus

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

//DOM-IGNORE-END

#ifndef _POWER_DEEPSLEEPFAULTDETECTSTATUS_UNSUPPORTED_H
#define _POWER_DEEPSLEEPFAULTDETECTSTATUS_UNSUPPORTED_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    None.

  MASKs: 
    None.

  POSs: 
    None.

  LENs: 
    None.

*/


//******************************************************************************
/* Function :  POWER_ExistsDeepSleepFaultDetect_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_POWER_ExistsDeepSleepFaultDetect

  Description:
    This template implements the Unsupported variant of the PLIB_POWER_ExistsDeepSleepFaultDetect function.
*/

PLIB_TEMPLATE bool POWER_ExistsDeepSleepFaultDetect_Unsupported( POWER_MODULE_ID index )
{
    return false;
}


//******************************************************************************
/* Function :  POWER_DeepSleepFaultDetectStatus_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_POWER_DeepSleepFaultDetectStatus 

  Description:
    This template implements the Unsupported variant of the PLIB_POWER_DeepSleepFaultDetectStatus function.
*/

PLIB_TEMPLATE bool POWER_DeepSleepFaultDetectStatus_Unsupported( POWER_MODULE_ID index )
{
    PLIB_ASSERT(false, "The device selected does not implement PLIB_POWER_DeepSleepFaultDetectStatus");

    return false;
}


#endif /*_POWER_DEEPSLEEPFAULTDETECTSTATUS_UNSUPPORTED_H*/

/******************************************************************************
 End of File
*/

