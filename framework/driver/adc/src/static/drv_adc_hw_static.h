/*******************************************************************************
  ADC Driver build variant implementation for static driver

  Company:
    Microchip Technology Inc.

  File Name:
    drv_adc_hw_static.h
  
  Summary:
    ADC Driver build variant implementation for the static driver.

  Description:
    This file defines the build variant implementations for the static driver.
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

#ifndef _DRV_ADC_HW_STATIC_H
#define _DRV_ADC_HW_STATIC_H


// *****************************************************************************
/* Macro: _DRV_ADC_OBJ(obj,mem)

  Summary:
    Returns the appropriate Driver object member.

  Description:
    This macro returns either the static object or the indexed dynamic object.
    This macro has variations for dynamic or static driver.

*/

#define _DRV_ADC_OBJ(obj,mem)                           _DRV_ADC_OBJ_MAKE_NAME(gDrvADCObj).mem



// *****************************************************************************
/* Macro: _DRV_ADC_INDEX_GET(drvIndex)

  Summary:
    Returns the appropriate driver id for the configuration.

  Description:
    This macro returns either the statically declared driver id or the dynamic index
    passed into the macro. This macro has variations for dynamic or static
    driver

*/

#define _DRV_ADC_INDEX_GET(drvIndex)                            DRV_ADC_INDEX


// *****************************************************************************
/* Macro: _DRV_ADC_DYN( statement )

  Summary:
    Allows removal of code statements only needed for dynamic configurations.

  Description:
    This macro allows removal of code statements that are only needed for
    dynamic configurations.

  Remarks:
    Do not put multiple statements or compound statements within this macro.
    The statement must not include a comma (,).
*/

#define _DRV_ADC_DYN(statement)


// *****************************************************************************
/* Macro: _DRV_ADC_DYN( arg )

  Summary:
    Allows removal of function arguments only needed for dynamic configurations

  Description:
    This macro allows removal of function arguments that are only needed for
    dynamic configurations.

  Remarks:
    This macro is only for single or Right-most arguments in a function's formal
    parameter list.
*/

#define _DRV_ADC_DYN_ARG(arg)


// *****************************************************************************
/* Macro: _DRV_ADC_DYN_ARG_COMMA(arg)

  Summary:
    Allows removal of multiple function arguments only needed for dynamic
    configurations

  Description:
    This macro allows removal of multiple function arguments that are only
    needed for dynamic configurations.

  Remarks:
    This macro is only for use on arguments that preceed (or are to the Left of)
    other arguments in a function's formal parameter list because it embeds a
    comma (,) at the end of the argument declaration.
*/

#define _DRV_ADC_DYN_ARG_COMMA(arg)


// *****************************************************************************
/* Macro: _DRV_ADC_DYN_RETURN_TYPE(type)

  Summary:
    Switches return types needed in dynamic builds to "void" in static builds.

  Description:
    This macro switches return types needed in dynamic builds to "void" in
    static builds.
*/

#define _DRV_ADC_DYN_RETURN_TYPE(type)      void


// *****************************************************************************
/* Macro: _DRV_ADC_DYN_RETURN(retVal)

  Summary:
    Switches "return(value)" statements needed in dynamic builds to just
    "return" in static builds.

  Description:
    This macro switches "return(value)" statements needed in dynamic builds to
    just "return" in static builds.
*/

#define _DRV_ADC_DYN_RETURN(retVal)         return


// *****************************************************************************
/* Macro: _DRV_ADC_DYN_PARAM(param)

  Summary:
    Allows removal of function parameters only needed for dynamic configurations

  Description:
    This macro allows removal of function parameters that are only needed for
    dynamic configurations.

  Remarks:
    This macro is only for single or Right-most parameters in a function's actual
    parameter list.

*/

#define _DRV_ADC_DYN_PARAM(param)


// *****************************************************************************
/* Macro: _DRV_ADC_DYN_PARAM_COMMA(param)

  Summary:
    Allows removal of multiple function parameters only needed for dynamic
    configurations

  Description:
    This macro allows removal of multiple function arguments that are only
    needed for dynamic configurations.

  Remarks:
    This macro is only for use on parameters that preceed (or are to the Left of)
    other arguments in a function's actual parameter list because it embeds a
    comma (,) at the end of the argument declaration.
*/

#define _DRV_ADC_DYN_PARAM_COMMA(param)


// *****************************************************************************
/* Macro: _DRV_ADC_OBJ_ALLOCATE(drvIndex)

  Summary:
    Macro to create the object instance

  Description:
    Macro to create the object instance

*/

#define _DRV_ADC_OBJ_ALLOCATE(drvIndex)


// *****************************************************************************
/* Macro: _DRV_ADC_ObjectIsValid( dObj )

  Summary:
    Returns the information on whether the object handle is valid or not

  Description:
    Returns the information on whether the object handle is valid or not

*/

#define _DRV_ADC_ObjectIsValid(dObj)        (true)


// *****************************************************************************
/* Macro: _DRV_ADC_INSTANCES_NUMBER

  Summary:
    The ADC driver objects number

  Description:
    Returns the ADC driver objects number.

*/

#define _DRV_ADC_INSTANCES_NUMBER        1


#endif // _DRV_ADC_HW_STATIC_H

/*******************************************************************************
 End of File
*/