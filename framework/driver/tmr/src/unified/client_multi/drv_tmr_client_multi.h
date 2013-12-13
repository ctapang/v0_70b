/*******************************************************************************
  Timer Driver Build Variant implementation for dynamic driver

  Company:
    Microchip Technology Inc.

  File Name:
    drv_tmr_client_multi.h

  Summary:
    Timer driver build variant implementation for dynamic driver configurations.

  Description:
    This file defines the build variant implementations for dynamic driver
    configurations.
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


#ifndef _DRV_TMR_CLIENT_MULTI_H
#define _DRV_TMR_CLIENT_MULTI_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "tmr/src/drv_tmr_local.h"


// *****************************************************************************
// *****************************************************************************
// Section: Multi-Client Macros
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/* Macro: _DRV_TMR_CLIENT_OBJ(obj,mem)

  Summary:
    Returns the appropriate client member.

  Description:
    This macro returns either the static object or the indexed dynamic object.
    This macro has variations for dynamic or static driver.
*/

#define _DRV_TMR_CLIENT_OBJ(obj,mem)    gDrvTMRClientObj[obj].mem


// *****************************************************************************
/* Macro: _DRV_TMR_MC( statement )

  Summary:
    Allows removal of code statements only needed for multi client configurations

  Description:
    This macro allows removal of code statements that are only needed for
    multi client configurations.

  Remarks:
    Do not put multiple statements or compound statements within this macro.
    The statement must not include a comma (,).
*/

#define _DRV_TMR_MC(statement)  statement


// *****************************************************************************
/* Macro: _DRV_TMR_MC_ARG(arg)

  Summary:
    Allows removal of function arguments only needed for multi client configurations.

  Description:
    This macro allows removal of function arguments that are only needed for
    multi client configurations.

  Remarks:
    This macro is only for single or Right-most arguments in a function's formal
    parameter list.
*/

#define _DRV_TMR_MC_ARG(arg)  arg


// *****************************************************************************
/* Macro: _DRV_TMR_MC_ARG_COMMA(arg)

  Summary:
    Allows removal of multiple function arguments only needed for multi-client
    configurations.

  Description:
    This macro allows removal of multiple function arguments that are only
    needed for multi-client configurations.

  Remarks:
    This macro is only for use on arguments that preceed (or are to the Left of)
    other arguments in a function's formal parameter list because it embeds a
    comma (,) at the end of the argument declaration.
*/

#define _DRV_TMR_MC_ARG_COMMA(arg) arg,


// *****************************************************************************
/* Macro: _DRV_TMR_MC_RETURN_TYPE(type)

  Summary:
    Multi-client return type.

  Description:
    Multi-client interface return type, single client voids out and multi-client
    returns the client handle.
*/

#define _DRV_TMR_MC_RETURN_TYPE(type)   type


// *****************************************************************************
/* Macro: _DRV_TMR_MC_RETURN(handle)

  Summary:
    Switches "return(handle)" statements needed in multi-client builds to just
    "return" in single client builds.

  Description:
    This macro switches "return(handle)" statements needed in multi-client builds
    to  just "return" in single client builds.
*/

#define _DRV_TMR_MC_RETURN(handle)   return(handle)


// *****************************************************************************
/* Macro: _DRV_TMR_ClientObjectAllocate(drvId)

  Summary:
    Create the client instance.

  Description:
    This macro creates the client instance.
*/

#define _DRV_TMR_ClientObjectAllocate(drvId)        (drvId)


// *****************************************************************************
/* Macro: _DRV_TMR_MULTI_CLIENT_DOBJ(clientObj, dObj)

  Summary:
    Gets the driver object from the client instance.

  Description:
    This macro gets the driver object from the client instance.
*/

#define _DRV_TMR_MULTI_CLIENT_DOBJ(clientObj, dObj)          \
        (dObj=_DRV_TMR_CLIENT_OBJ(clientObj, driverObject))


// *****************************************************************************
/* Macro: _DRV_TMR_MC_Test(c)

  Summary:
    Checks for exclusive access.

  Description:
    This macro checks for exclusive access.

*/

#define  _DRV_TMR_MC_Test(c)    (c)


#endif // _DRV_TMR_CLIENT_MULTI_H

/*******************************************************************************
 End of File
*/

