/*******************************************************************************
  Timer Driver Build Variant implementation for dynamic driver

  Company:
    Microchip Technology Inc.

  File Name:
    drv_tmr_hw_dynamic.h

  Summary:
    Timer driver build variant implementation for dynamic driver.

  Description:
    This file defines the build variant implementations for the dynamic driver.
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


#ifndef _DRV_TMR_HW_DYNAMIC_H
#define _DRV_TMR_HW_DYNAMIC_H

#include "tmr/src/drv_tmr_local.h"


// *****************************************************************************
/* Macro: _DRV_TMR_OBJ(obj,mem)

  Summary:
    Returns the appropriate driver object member.

  Description:
    This macro returns either the static object or the indexed dynamic object.
    This macro has variations for dynamic or static driver.

*/

#define _DRV_TMR_OBJ(obj,mem)               gDrvTMRObj[obj].mem


// *****************************************************************************
/* Macro: _DRV_TMR_INDEX_GET(drvIndex)

  Summary:
    Returns the appropriate driver id for the configuration.

  Description:
    This macro returns either the statically declared driver ID or the dynamic index
    passed into the macro. This macro has variations for dynamic or static
    driver.

*/

#define _DRV_TMR_INDEX_GET(drvIndex)            (drvIndex)


// *****************************************************************************
/* Macro: _DRV_TMR_DYN( statement )

  Summary:
    Allows removal of code statements only needed for dynamic configurations.

  Description:
    This macro allows removal of code statements that are only needed for 
    dynamic configurations.
    
  Remarks:
    Do not put multiple statements or compound statements within this macro.
    The statement must not include a comma (,).    
*/

#define _DRV_TMR_DYN(statement)             statement


// *****************************************************************************
/* Macro: _DRV_TMR_DYN_ARG(arg)

  Summary:
    Allows removal of function arguments only needed for dynamic configurations.

  Description:
    This macro allows removal of function arguments that are only needed for 
    dynamic configurations.
    
  Remarks:
    This macro is only for single or Right-most arguments in a function's formal
    parameter list.
*/

#define _DRV_TMR_DYN_ARG(arg)               arg


// *****************************************************************************
/* Macro: _DRV_TMR_DYN_ARG_COMMA(arg)

  Summary:
    Allows removal of multiple function arguments only needed for dynamic 
    configurations.

  Description:
    This macro allows removal of multiple function arguments that are only 
    needed for dynamic configurations.
    
  Remarks:
    This macro is only for use on arguments that preceed (or are to the Left of)
    other arguments in a function's formal parameter list because it embeds a 
    comma (,) at the end of the argument declaration.
*/

#define _DRV_TMR_DYN_ARG_COMMA(arg)         arg,


// *****************************************************************************
/* Macro: _DRV_TMR_DYN_RETURN_TYPE(type)

  Summary:
    Switches return types needed in dynamic builds to "void" in static builds.

  Description:
    This macro switches return types needed in dynamic builds to "void" in 
    static builds.
*/

#define _DRV_TMR_DYN_RETURN_TYPE(type)      type


// *****************************************************************************
/* Macro: _DRV_TMR_DYN_RETURN(retVal)

  Summary:
    Switches "return(value)" statements needed in dynamic builds to just 
    "return" in static builds.

  Description:
    This macro switches "return(value)" statements needed in dynamic builds to 
    just "return" in static builds.
*/

#define _DRV_TMR_DYN_RETURN(retVal)         return(retVal)


// *****************************************************************************
/* Macro: _DRV_TMR_DYN_PARAM(param)

  Summary:
    Allows removal of function parameters only needed for dynamic configurations.

  Description:
    This macro allows removal of function parameters that are only needed for
    dynamic configurations.

  Remarks:
    This macro is only for single or Right-most parameters in a function's actual
    parameter list.

*/

#define _DRV_TMR_DYN_PARAM(param)           param


// *****************************************************************************
/* Macro: _DRV_TMR_DYN_PARAM_COMMA(param)

  Summary:
    Allows removal of multiple function parameters only needed for dynamic
    configurations.

  Description:
    This macro allows removal of multiple function arguments that are only
    needed for dynamic configurations.

  Remarks:
    This macro is only for use on parameters that preceed (or are to the Left of)
    other arguments in a function's actual parameter list because it embeds a
    comma (,) at the end of the argument declaration.
*/

#define _DRV_TMR_DYN_PARAM_COMMA(param)     param,


// *****************************************************************************
/* Macro: _DRV_TMR_ObjectIsValid( dObj )

  Summary:
    Returns the information on whether or note the object handle is valid.

  Description:
    Returns the information on whether or not the object handle is valid.

*/

#define _DRV_TMR_ObjectIsValid(dObj)        (dObj < DRV_TMR_INSTANCES_NUMBER)


// *****************************************************************************
/* Macro: _DRV_TMR_OBJ_ALLOCATE(drvIndex)

  Summary:
    Allocates the driver object instance.

  Description:
    This macro allocates the driver object instance.
*/

#define _DRV_TMR_OBJ_ALLOCATE(drvIndex)     drvIndex


// *****************************************************************************
/* Macro:
    _DRV_TMR_ExternalClockSyncEnable(index)

  Summary:
    Enables external clock synchronization.

  Description:
    This macro enables the external clock synchronization.

  Remarks:
    None
*/

#define _DRV_TMR_ExternalClockSyncEnable(index)     PLIB_TMR_ExternalClockSynchronizationEnable(index)


// *****************************************************************************
/* Macro:
    _DRV_TMR_ExternalClockSyncDisable(index)

  Summary:
    Disables external clock synchronization.

  Description:
    This macro disables the external clock synchronization.

  Remarks:
    None.
*/

#define _DRV_TMR_ExternalClockSyncDisable(index)    PLIB_TMR_ExternalClockSynchronizationDisable(index)

    
#endif // _DRV_TMR_HW_DYNAMIC_H

/*******************************************************************************
 End of File
*/
