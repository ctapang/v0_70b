/*******************************************************************************
 Module for Microchip Graphics Library - Graphic Object Layer

  Company:
    Microchip Technology Inc.

  File Name:
    gfx_gol.h

  Summary:
    Graphics Object Layer of the Microchip Graphics Library.

  Description:
    This module implements the common routines for the Graphics Object Layer
    of the Microchip Graphics Library. The routines are independent of the
    Display Driver Layer and should be compatible with any Display Driver
    that is compliant with the requirements of the Display Driver
    Layer of the Graphics Library.
    The module utilizes the Graphics Primitive Layer to render the objects.
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

#ifndef _GFX_GOL_H
    #define _GFX_GOL_H

/*********************************************************************
 * Section: Includes
 *********************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include "system_config.h"
#include "gfx/gfx_primitive.h"
#include "driver/gfx/drv_gfx_display.h"
#include "gfx/gfx_colors.h"
#include "gfx/gfx_gol_scheme.h"

// *****************************************************************************
/* GFX_GOL_OBJ_TYPE

  Summary
    Specifies the different object types used in the library.

  Description
    This enumeration specifies the different object types
    used in the library.

  Remarks:
    None.
*/
// *****************************************************************************
typedef enum
{
    GFX_GOL_ANALOGCLOCK_TYPE,       // Type defined for Analog Clock Object.
    GFX_GOL_BUTTON_TYPE,            // Type defined for Button Object.
    GFX_GOL_CHART_TYPE,             // Type defined for Chart Object.
    GFX_GOL_CHECKBOX_TYPE,          // Type defined for Check Box Object.
    GFX_GOL_DIGITALMETER_TYPE,      // Type defined for Digital Meter Object.
    GFX_GOL_EDITBOX_TYPE,           // Type defined for Edit Box Object.
    GFX_GOL_GRID_TYPE,              // Type defined for Grid Object.
    GFX_GOL_GROUPBOX_TYPE,          // Type defined for Group Box Object.
    GFX_GOL_LISTBOX_TYPE,           // Type defined for List Box Object.
    GFX_GOL_METER_TYPE,             // Type defined for Meter Object.
    GFX_GOL_PICTURECONTROL_TYPE,    // Type defined for Picture Control Object.
    GFX_GOL_PROGRESSBAR_TYPE,       // Type defined for Progress Bar Object.
    GFX_GOL_RADIOBUTTON_TYPE,       // Type defined for Radio Button Object.
    GFX_GOL_SCROLLBAR_TYPE,         // Type defined for Slider or
                                    // Scroll Bar Object.
    GFX_GOL_STATICTEXT_TYPE,        // Type defined for Static Text Object.
    GFX_GOL_TEXTENTRY_TYPE,         // Type defined for Text-Entry Object.
    GFX_GOL_WINDOW_TYPE,            // Type defined for Window Object.
    GFX_GOL_CUSTOM_TYPE,            // Type defined for Custom Object.
    GFX_GOL_UNKNOWN_TYPE            // Type is undefined and not supported
                                    // by the library.
} GFX_GOL_OBJ_TYPE;

// *****************************************************************************
/* GFX_GOL_MESSAGE

  Summary
    Specifies message structure used in the library.

  Description
    Specifies message structure used in the library.
    - The types must be one of the INPUT_DEVICE_TYPE:
        - TYPE_UNKNOWN
        - TYPE_KEYBOARD
        - TYPE_TOUCHSCREEN
        - TYPE_MOUSE
    - uiEvent must be one of the INPUT_DEVICE_EVENT.
        - for touch screen:
            - EVENT_INVALID
            - EVENT_MOVE
            - EVENT_PRESS
            - EVENT_STILLPRESS
            - EVENT_RELEASE
        - for keyboard:
            - EVENT_KEYSCAN (param2 contains scan code)
            - EVENT_KEYCODE (param2 contains character code)
    - param1:
        - for touch screen is the x position
        - for keyboard ID of object receiving the message
    - param2
        - for touch screen y position
        - for keyboard scan or key code

  Remarks:
    None.
*/
// *****************************************************************************
typedef struct
{
    uint8_t   type;                 // Type of input device.
    uint8_t   uiEvent;              // The generic events for input device.
    int16_t   param1;               // Parameter 1, definition and usage is
                                    // dependent on the type of input device.
    int16_t   param2;               // Parameter 2, definition and usage is
                                    // dependent on the type of input device.
} GFX_GOL_MESSAGE;

// *****************************************************************************
/* INPUT_DEVICE_TYPE

  Summary
    Specifies the different user input devices supported in the library.

  Description
    This enumeration specifies the different user input devices supported
    in the library.

  Remarks:
    None.
*/
// *****************************************************************************
typedef enum
{
    TYPE_UNKNOWN    = 0,            // Unknown device.
    TYPE_KEYBOARD,                  // Keyboard.
    TYPE_TOUCHSCREEN,               // Touchscreen.
    TYPE_MOUSE,                     // Mouse.
    TYPE_TIMER,                     // Timer.
    TYPE_SYSTEM                     // System Messages.
} INPUT_DEVICE_TYPE;

// *****************************************************************************
/* INPUT_DEVICE_EVENT

  Summary
    Specifies the different user input device events supported in the library.

  Description
    This enumeration specifies the different user input device events
    supported in the library.

  Remarks:
    None.
*/
// *****************************************************************************
typedef enum
{
    EVENT_INVALID   = 0,            // An invalid event.
    EVENT_MOVE,                     // A move event.
    EVENT_PRESS,                    // A press event.
    EVENT_STILLPRESS,               // A continuous press event.
    EVENT_RELEASE,                  // A release event.
    EVENT_KEYSCAN,                  // A keyscan event, parameters has
                                    // the object ID keyboard scan code.
    EVENT_CHARCODE,                 // Character code is presented at
                                    // the parameters.
    EVENT_SET,                      // A generic set event.
    EVENT_SET_STATE,                // A set state event.
    EVENT_CLR_STATE                 // A clear state event.
} INPUT_DEVICE_EVENT;

// *****************************************************************************
/* GFX_GOL_TRANSLATED_ACTION

  Summary
    Specifies the different object actions supported in the library.

  Description
    This enumeration specifies the different object actions
    supported in the library.

  Remarks:
    None.
*/
// *****************************************************************************
typedef enum
{
    GFX_GOL_OBJECT_ACTION_INVALID = 0x3500, // Invalid message response.
    GFX_GOL_OBJECT_ACTION_PASSIVE,          // Passive message response. No change
                                            // in object needed.
    GFX_GOL_ANALOGCLOCK_ACTION_PRESSED,     // Analog Clock Pressed Action
    GFX_GOL_ANALOGCLOCK_ACTION_RELEASED,    // Analog Clock Released Action

    GFX_GOL_BUTTON_ACTION_PRESSED,          // Button pressed action ID.
    GFX_GOL_BUTTON_ACTION_STILLPRESSED,     // Button is continuously pressed ID.
    GFX_GOL_BUTTON_ACTION_RELEASED,         // Button released action ID.
    GFX_GOL_BUTTON_ACTION_CANCELPRESS,      // Button released action ID with
                                            // button press canceled.
    GFX_GOL_CHART_ACTION_SELECTED,          // Chart selected action ID

    GFX_GOL_CHECKBOX_ACTION_CHECKED,        // Check Box check action ID.
    GFX_GOL_CHECKBOX_ACTION_UNCHECKED,      // Check Box un-check action ID.

    GFX_GOL_CUSTOMCONTROL_ACTION_SELECTED,  // Custom Control selected action ID.

    GFX_GOL_DIGITALMETER_ACTION_SELECTED,   // Digital Meter selected action ID.

    GFX_GOL_EDITBOX_ACTION_ADD_CHAR,            // Edit Box insert character action ID.
    GFX_GOL_EDITBOX_ACTION_DEL_CHAR,             // Edit Box remove character action ID.
    GFX_GOL_EDITBOX_ACTION_TOUCHSCREEN,     // Edit Box touchscreen selected action ID.

    GFX_GOL_GRID_ACTION_TOUCHED,            // Grid item touched action ID.
    GFX_GOL_GRID_ACTION_ITEM_SELECTED,      // Grid item selected action ID.
    GFX_GOL_GRID_ACTION_UP,                 // Grid up action ID.
    GFX_GOL_GRID_ACTION_DOWN,               // Grid down action ID.
    GFX_GOL_GRID_ACTION_LEFT,               // Grid left action ID.
    GFX_GOL_GRID_ACTION_RIGHT,              // Grid right action ID.

    GFX_GOL_GROUPBOX_ACTION_SELECTED,       // Group Box selected action ID.

    GFX_GOL_LISTBOX_ACTION_SELECTED,        // List Box item select action ID.
    GFX_GOL_LISTBOX_ACTION_MOVE,            // List Box item move action ID.
    GFX_GOL_LISTBOX_ACTION_TOUCHSCREEN,     // List Box touchscreen selected action ID.

    GFX_GOL_METER_ACTION_SET,               // Meter set value action ID.

    GFX_GOL_PICTURECONTROL_ACTION_SELECTED, // Picture selected action ID.

    GFX_GOL_PROGRESSBAR_ACTION_SELECTED,    // Progress Bar selected action ID.

    GFX_GOL_RADIOBUTTON_ACTION_CHECKED,     // Radio Button check action ID.

    GFX_GOL_SCROLLBAR_ACTION_INC,           // Slider or Scroll Bar increment action ID.
    GFX_GOL_SCROLLBAR_ACTION_DEC,           // Slider or Scroll Bar decrement action ID.

    GFX_GOL_STATICTEXT_ACTION_SELECTED,     // Static Text selected action ID.

    GFX_GOL_TEXTENTRY_ACTION_RELEASED,      // TextEntry released action ID
    GFX_GOL_TEXTENTRY_ACTION_PRESSED,       // TextEntry pressed action ID
    GFX_GOL_TEXTENTRY_ACTION_ADD_CHAR,      // TextEntry add character action ID
    GFX_GOL_TEXTENTRY_ACTION_DELETE,        // TextEntry delete character action ID
    GFX_GOL_TEXTENTRY_ACTION_SPACE,         // TextEntry add space character action ID
    GFX_GOL_TEXTENTRY_ACTION_ENTER,         // TextEntry enter action ID

    GFX_GOL_WINDOW_ACTION_CLIENT,           // Window client area selected action ID.
    GFX_GOL_WINDOW_ACTION_TITLE,            // Window title bar selected action ID.

} GFX_GOL_TRANSLATED_ACTION;

// DOM-IGNORE-BEGIN

/*********************************************************************
 Overview: Object draw function pointer typedef

*********************************************************************/
typedef GFX_STATUS (*DRAW_FUNC)(void *);

/*********************************************************************
 Overview: Object free draw function pointer typedef

*********************************************************************/
typedef void (*FREE_FUNC)(void *);

/*********************************************************************
 Overview: Object action get function pointer typedef

*********************************************************************/
typedef GFX_GOL_TRANSLATED_ACTION (*ACTIONGET_FUNC)     \
                            (   void *,                 \
                                GFX_GOL_MESSAGE *       \
                            );

/*********************************************************************
 Overview: Object action set function pointer typedef

*********************************************************************/
typedef void (*ACTIONSET_FUNC)                              \
                            (   GFX_GOL_TRANSLATED_ACTION,  \
                                void *, GFX_GOL_MESSAGE *   \
                            );

// DOM-IGNORE-END

// *****************************************************************************
/* GFX_GOL_OBJ_HEADER

  Summary
    Specifies Graphics Object Layer structure used in objects.

  Description
    This structure defines the Graphics Object Layer header used in all
    objects in the Graphics Library.

  Remarks:
    None.
*/
// *****************************************************************************
typedef struct
{
    uint16_t            ID;             // Unique id assigned for referencing.
    void                *pNxtObj;       // A pointer to the next object.
    GFX_GOL_OBJ_TYPE    type;           // Identifies the type of GOL object.
    uint16_t            state;          // State of object.
    uint16_t            left;           // Left position of the Object.
    uint16_t            top;            // Top position of the Object.
    uint16_t            right;          // Right position of the Object.
    uint16_t            bottom;         // Bottom position of the Object.
    GFX_GOL_OBJ_SCHEME  *pGolScheme;    // Pointer to the scheme used.
    DRAW_FUNC           DrawObj;        // function pointer to the object's
                                        // draw function.
    FREE_FUNC           FreeObj;        // function pointer to the object's
                                        // free function.
    ACTIONGET_FUNC      actionGet;      // function pointer to the object's
                                        // action get function.
    ACTIONSET_FUNC      actionSet;      // function pointer to the object's
                                        // action set function.

    bool                imageStored;    //Used for alpha blending

} GFX_GOL_OBJ_HEADER;

// *****************************************************************************
/*  Function:
    typedef bool (*GFX_GOL_DRAW_CALLBACK_FUNC) (void);

    Summary:
        Draw callback function defintion. This application defined
        function allows the application to perform application specific
        rendering.

    Description:
        This callback function is implemented by the application.
        This is called inside the GFX_GOL_ObjectListDraw()
        function when the drawing of objects in the active list is
        completed.

        Any application specific rendering must be performed on this
        callback function so no object rendering will be affected by the
        application calls to primitive rendering functions.
        Application setting the drawing color, line style, fill style,
        text string  cursor position and current font will not affect
        the object rendering. This is also the safe place to modify the
        active list.

        When the application has performed its own primitive rendering
        calls, this function must return true to inform
        the GFX_GOL_ObjectListDraw() that it is done rendering and
        checking for object drawing or redrawing can continue.

    Precondition:
        None.

    Parameters:
        None.

    Returns:
        true  - is returned when application rendering is done.
        false - is returned when application rendering is not
                yet finished.

    Example:
        None.

*/
// *****************************************************************************
typedef bool (*GFX_GOL_DRAW_CALLBACK_FUNC) (void);

// *****************************************************************************
/*  Function:
    typedef bool (*GFX_GOL_MESSAGE_CALLBACK_FUNC)
                    (   GFX_GOL_TRANSLATED_ACTION,
                        GFX_GOL_OBJ_HEADER *,
                        GFX_GOL_MESSAGE *
                    );

    Summary:
        Message callback function defintion. This application defined
        function allows the application to perform application specific
        processing of user messsages.

    Description:
        This application defined function is called by the
        GFX_GOL_ObjectMessage() function allowing the application
        the opportunity to process the user messages and customize
        object behavior as well as application controlled functions.

        GFX_GOL_ObjectMessage() calls this function when a valid message
        for an object  in the active list is received. Application
        implements any action for the message in this callback function.
        If this callback function returns true, the message for the
        object will be processed using the default action of the object.
        If false is returned, the default action will not be performed.
        In this case, it is assumed that this callback function has
        performed the appropriate changes to the states of the objects.

    Precondition:
        None.

    Parameters:
        GFX_GOL_TRANSLATED_ACTION - Translated message for the object
        GFX_GOL_OBJ_HEADER * - Pointer to the object that processed the
                               message.
        GFX_GOL_MESSAGE * - Pointer to the message from user.

    Returns:
        true  - When true is returned, the object will set its state
                depending on the translated messages.
        false - When false is returned, the object will not process the
                translated message and will assume the application has
                performed necessary action on the message.

    Example:
        None.

*/
// *****************************************************************************
typedef bool (*GFX_GOL_MESSAGE_CALLBACK_FUNC)       \
                    (   GFX_GOL_TRANSLATED_ACTION,  \
                        GFX_GOL_OBJ_HEADER *,       \
                        GFX_GOL_MESSAGE *           \
                    );


// *****************************************************************************
/* GOL_PANEL_PARAM

  Summary
    Specifies panel parameters.

  Description
    This structure defines the panel parameters when rendering a panel.

  Remarks:
    None.
*/
// *****************************************************************************
typedef struct
{
    int16_t             panelLeft;
    int16_t             panelTop;
    int16_t             panelRight;
    int16_t             panelBottom;
    GFX_COLOR           panelFaceColor;
    GFX_COLOR           panelEmbossLtColor;
    GFX_COLOR           panelEmbossDkColor;
    uint16_t            panelEmbossSize;
    uint16_t            panelRadius;
    GFX_RESOURCE_HDR    *pPanelImage;
    GFX_FILL_STYLE      panelFillStyle;

#ifndef GFX_CONFIG_GRADIENT_DISABLE
    GFX_COLOR           panelGradientStartColor;
    GFX_COLOR           panelGradientEndColor;
#endif

#if !defined GFX_CONFIG_ALPHABLEND_DISABLE || defined USE_ALPHABLEND_LITE
    uint16_t            panelAlpha;
#endif

} GOL_PANEL_PARAM;

extern GOL_PANEL_PARAM                  GfxPanel;

// DOM-IGNORE-BEGIN

/*********************************************************************
* Overview: The following are the common Object States.
*
*********************************************************************/

// Focus state bit.
#define GFX_GOL_FOCUSED     0x0001

// Disabled state bit.
#define GFX_GOL_DISABLED    0x0002

// Object hide state bit. Object will be hidden from the
// screen by drawing over it the common background color.
#define GFX_GOL_HIDE        0x8000

// Object redraw state bit. The whole Object must be redrawn.
#define GFX_GOL_DRAW        0x7C00

// Focus redraw state bit. The focus rectangle must be redrawn.
#define GFX_GOL_DRAW_FOCUS  0x2000

// Partial Object redraw state bit. A part or parts of
// of the Object must be redrawn to show updated state.
#define GFX_GOL_DRAW_UPDATE 0x3C00

/*********************************************************************
* Overview: The following are the global variables of GOL.
*
*********************************************************************/

///*********************************************************************
//* Overview: This option defines the default 3-D effect emboss size
//*           for objects.
//*
//*********************************************************************/
//    #ifndef GFX_LIB_CFG_GOL_EMBOSS_SIZE
//        #define GFX_LIB_CFG_GOL_EMBOSS_SIZE 3
//    #endif
// DOM-IGNORE-END

/*********************************************************************
* Overview: The default font GOLFontDefault is declared in
*           GOLFontDefault.c file included in the Graphics Library.
*           To use this default font, GFX_LIB_CFG_USE_GOL must be defined in
*           GraphicsConfig.h.
*           To replace this default font, add the appropriate
*           declaration in the GraphicsConfig.h:
*           - #define FONTDEFAULT FontName - This macro is deprecated.
*                                       use FONTDEFAULT_FLASH instead.
*                                       This is for default font
*                                       located in flash memory.
*           - #define FONTDEFAULT_FLASH FontName - This is for default
*                                       font located in flash memory.
*           - #define FONTDEFAULT_EXTERNAL FontName - This is for default
*                                       font located in external memory.
*           Then in the project the "FontName" must be added.
*           The Graphics Library will then use the font that the user
*           supplied.
*
*  Note: When the default font is placed in external resource (or memory),
*        any calls  to OutText(), OutTextXY() and OutChar() will not
*        work if the external resource is not programmed with the font
*        table.
*********************************************************************/

// *****************************************************************************
/*  Function:
    void GFX_GOL_MessageCallbackSet(
                                GFX_GOL_MESSAGE_CALLBACK_FUNC pFunc)
    Summary:
        This function sets the message callback function that the
        application will use to evaluate user inputs that affects
        the objects and application behavior.

    Description:
        This function sets the message callback function that the
        application will use to evaluate user inputs that affects
        the objects and application behavior. The callback function
        location is specified by the function pointer supplied in
        the call. See GFX_GOL_MESSAGE_CALLBACK_FUNC definition for
        details on the message callback function.

    Precondition:
        None.

    Parameters:
        pFunc - pointer to the message callback function.

    Returns:
        None.

    Example:
        None.

*/
// *****************************************************************************
void GFX_GOL_MessageCallbackSet( GFX_GOL_MESSAGE_CALLBACK_FUNC pFunc);

// *****************************************************************************
/*  Function:
    void GFX_GOL_DrawCallbackSet(
                                GFX_GOL_DRAW_CALLBACK_FUNC pFunc)
    Summary:
        This function sets the draw callback function that the
        application will use to render application specific rendering.

    Description:
        This function sets the draw callback function that the
        application will use to call primitive function to implement
        application specific shapes.See GFX_GOL_DRAW_CALLBACK_FUNC
        definition for details on the draw callback function.

    Precondition:
        None.

    Parameters:
        pFunc - pointer to the draw callback function.

    Returns:
        None.

    Example:
        None.

*/
// *****************************************************************************
void GFX_GOL_DrawCallbackSet( GFX_GOL_DRAW_CALLBACK_FUNC pFunc);

// *****************************************************************************
/*  Function:
    GFX_STATUS GFX_GOL_ObjectCanBeFocused(GFX_GOL_OBJ_HEADER *pObject)

    Summary:
        Checks if the object can be focused.

    Description:
        This function checks if the object can be focused or not.
        If the object can be focused, it returns GFX_STATUS_SUCCESS.
        If it cannot be focused, it returns GFX_STATUS_FAILURE.
        Selected objects have the focus feature. Refer to the object
        documentation for details.

        Objects that do not support focus feature will ignore any focus
        settings.

        If the object is disabled it cannot be set to focused state.

    Precondition:
        None.

    Parameters:
        pObject - pointer to the object.

    Returns:
        GFX_STATUS_SUCCESS - when the object can be focused
        GFX_STATUS_FAILURE - when the object cannot be focused or
                             do not support the focus feature.

    Example:
        <code>
            TODO: Add example code here
        </code>

*/
// *****************************************************************************
GFX_STATUS GFX_GOL_ObjectCanBeFocused(GFX_GOL_OBJ_HEADER *pObject);

// *****************************************************************************
/*  Function:
    GFX_GOL_OBJ_HEADER *GFX_GOL_ObjectFocusPrevGet(void)

    Summary:
        This function returns the pointer to the previous object
        in the active list of objects which can be focused.

    Description:
        This function returns the pointer to the previous object
        in the active list of objects which can be focused.

        The reference point is the currently focused object. If there
        is no currently focused object, the searched starts from the
        beginning of the active list of objects.

        Objects that can be focused are those objects that can receive
        keyboard inputs.

        If there is no object capable of receiving keyboard
        inputs (i.e. none can be focused) NULL is returned.

    Precondition:
        None.

    Parameters:
        None.

    Returns:
        The pointer to the object that can be focused.

    Example:
        <code>
            TODO: Add example code here
        </code>

*/
// *****************************************************************************
GFX_GOL_OBJ_HEADER  *GFX_GOL_ObjectFocusPrevGet(void);

// *****************************************************************************
/*  Function:
    GFX_GOL_OBJ_HEADER *GFX_GOL_ObjectFocusNextGet(void)

    Summary:
        This function returns the pointer to the next object
        in the active list of objects which can be focused.

    Description:
        This function returns the pointer to the next object
        in the active list of objects which can be focused.

        The reference point is the currently focused object. If there
        is no currently focused object, the searched starts from the
        beginning of the active list of objects.

        Objects that can be focused are those objects that can receive
        keyboard inputs.

        If there is no object capable of receiving keyboard
        inputs (i.e. none can be focused) NULL is returned.

    Precondition:
        None.

    Parameters:
        None.

    Returns:
        The pointer to the object that can be focused.

    Example:
        <code>
            TODO: Add example code here
        </code>

*/
// *****************************************************************************
GFX_GOL_OBJ_HEADER  *GFX_GOL_ObjectFocusNextGet(void);

// *****************************************************************************
/*  Function:
    GFX_STATUS *GFX_GOL_ObjectFocusSet(GFX_GOL_OBJ_HEADER *pObject)

    Summary:
        This function sets the object to be focused.

    Description:
        This function sets the specified object to be focused.

        If the object cannot accept keyboard messages, the object will
        not be set to focused state. If the object can accept keyboard
        messages, then the focus state will be set and will be marked
        to be redrawn to show the focus when the focus feature is enabled.

        Objects that can be focused are those objects that can receive
        keyboard inputs.

    Precondition:
        None.

    Parameters:
        pObject - pointer to the object.

    Returns:
        GFX_STATUS_SUCCESS - when the object can be focused
        GFX_STATUS_FAILURE - when the object cannot be focused or
                             do not support the focus feature.

    Example:
        <code>
            TODO: Add example code here
        </code>

*/
// *****************************************************************************
GFX_STATUS  GFX_GOL_ObjectFocusSet(GFX_GOL_OBJ_HEADER *pObject);

// *****************************************************************************
/*  Function:
    GFX_GOL_OBJ_HEADER *GFX_GOL_ObjectFocusGet(void)

    Summary:
        This function returns the pointer to the object that is currently
        receiving keyboard input (or focused).

    Description:
        This function returns the pointer to the object that is currently
        receiving keyboard input (or focused).

        If there are no object that can accept keyboard messages, then the
        function will return NULL.

        Objects that can be focused are those objects that can receive
        keyboard inputs.

    Precondition:
        None.

    Parameters:
        None.

    Returns:
        The pointer the currently focused object. Returns NULL if there
        is no object currently set.

    Example:
        <code>
            TODO: Add example code here
        </code>

*/
// *****************************************************************************
GFX_GOL_OBJ_HEADER *GFX_GOL_ObjectFocusGet(void);

// *****************************************************************************
/*  Function:
    GFX_GOL_OBJ_TYPE GFX_GOL_ObjectTypeGet(GFX_GOL_OBJ_HEADER *pObject)

    Summary:
        This function returns the object type.

    Description:
        This function returns the object type. The object type is one
        of the defined enumerated types of GFX_GOL_OBJ_TYPE.

    Precondition:
        None.

    Parameters:
        Pointer to the object of interest.

    Returns:
        The type of the object. The type is one of the defined
        enumerated types of GFX_GOL_OBJ_TYPE.

    Example:
        <code>
            TODO: Add example code here
        </code>

*/
// *****************************************************************************
GFX_GOL_OBJ_TYPE GFX_GOL_ObjectTypeGet(GFX_GOL_OBJ_HEADER *pObject);

// *****************************************************************************
/*  Function:
    uint16_t GFX_GOL_ObjectIDGet(GFX_GOL_OBJ_HEADER *pObject)

    Summary:
        This function returns the object ID.

    Description:
        This function returns the user defined ID assigned to the object.

    Precondition:
        None.

    Parameters:
        Pointer to the object of interest.

    Returns:
        The user defined ID of the object.

    Example:
        <code>
            void ExampleUsageOfGettingID(GFX_GOL_OBJ_HEADER *pObject)
            {
                uint16_t id;

                switch(id = GFX_GOL_ObjectIDGet(pObject))
                {
                    case ID_WINDOW1:
                        // do something
                    case ID_WINDOW2:
                        // do something else
                    case ID_WINDOW3:
                        // do something else
                    default:
                        // do something else
                }
            }
        </code>

*/
// *****************************************************************************
uint16_t GFX_GOL_ObjectIDGet(GFX_GOL_OBJ_HEADER *pObject);

// *****************************************************************************
/*  Function:
    GFX_GOL_OBJ_HEADER *GFX_GOL_ObjectNextGet(GFX_GOL_OBJ_HEADER *pObject)

    Summary:
        This function returns the pointer to next object in the list
        after the specified object.

    Description:
        This function returns the pointer to next object in the list
        after the specified object.

    Precondition:
        None.

    Parameters:
        Pointer to the object of interest.

    Returns:
        The pointer to the next object in the list.

    Example:
        <code>
            void RedrawButtons(void)
            {

                GFX_GOL_OBJ_HEADER *pCurr;

                // get active list
                pCurr = GFX_GOL_ObjectListGet();

                while(pCurr->pNxtObj != NULL)
                {
                    // just select button objects and redraw them
                    if (GFX_GOL_ObjectTypeGet(pCurr) == BUTTON)
                    {
                        // set to be redrawn
                        pCurr->state = BTN_DRAW;
                    }
                    pCurr = GFX_GOL_ObjectNextGet(pCurr);
                }
                // redraw all buttons in the active list
                GFX_GOL_ObjectListDraw();
            }
        </code>

*/
// *****************************************************************************
GFX_GOL_OBJ_HEADER *GFX_GOL_ObjectNextGet(GFX_GOL_OBJ_HEADER *pObject);

// *****************************************************************************
/*  Function:
    GFX_GOL_OBJ_HEADER *GFX_GOL_ObjectFind(uint16_t ID)

    Summary:
        This function returns the pointer to object in the list
        with the user defined ID assigned to it.

    Description:
        This function returns the pointer to object in the list
        with the user defined ID assigned to it.

    Precondition:
        None.

    Parameters:
        User defined ID of the object of interest.

    Returns:
        The pointer to the object in the list with the given ID.

    Example:
        <code>
            void CopyObject(GFX_GOL_OBJ_HEADER *pSrcList,
                            GFX_GOL_OBJ_HEADER *pDstList,
                            uint16_t ID)
            {
                GFX_GOL_OBJ_HEADER *pTemp;

                // find the object
                pTemp = GFX_GOL_ObjectFind(ID);

                if (pTemp != NULL)
                {
                    // destination as active list
                    GFX_GOL_ObjectSetList(pDstList);

                    // add object to active list
                    GFX_GOL_ObjectAdd(pTemp);
                }
            }
        </code>

*/
// *****************************************************************************
GFX_GOL_OBJ_HEADER *GFX_GOL_ObjectFind(uint16_t ID);

// *****************************************************************************
/*  Function:
    void GFX_GOL_ObjectAdd(GFX_GOL_OBJ_HEADER *pObject)

    Summary:
        This function adds an object to the tail of the
        currently active list.

    Description:
        This function adds an object to the tail of the
        currently active list. The new list tail is set
        to point to NULL after the new object is added.

    Precondition:
        None.

    Parameters:
        Pointer to the object that will be added to the list.

    Returns:
        None.

    Example:
        <code>
            void MoveObject(    GFX_GOL_OBJ_HEADER *pSrcList,
                                GFX_GOL_OBJ_HEADER *pDstList,
                                GFX_GOL_OBJ_HEADER *pObjtoMove)
            {
                GFX_GOL_OBJ_HEADER *pTemp = pSrcList;

                if(pTemp != pObjtoMove)
                {
                    while(pTemp->pNxtObj != pObjtoMove)
                        pTemp = pTemp->pNxtObj;
        }

                pTemp->pNxtObj = pObjtoMove ->pNxt; // remove object from list
                GFX_GOL_ObjectListSet(pDstList);    // destination as active list
                GFX_GOL_ObjectAdd(pObjtoMove);      // add object to active list
    }

        </code>

*/
// *****************************************************************************
void    GFX_GOL_ObjectAdd(GFX_GOL_OBJ_HEADER *pObject);

// *****************************************************************************
/*  Function:
    GFX_STATUS GFX_GOL_ObjectDelete(GFX_GOL_OBJ_HEADER *pObject)

    Summary:
        This function removes an object from the currently
        active list.

    Description:
        This function removes an object from the currently
        active list. Aside from the removal of the object
        from the list, the RAM resources consumed by the object
        is also freed.

    Precondition:
        None.

    Parameters:
        Pointer to the object that will removed from the list.

    Returns:
        GFX_STATUS_SUCCESS - is returned if the removal was successful.
        GFX_STATUS_FAILURE - is returned if the removal was not successful.

    Example:
        <code>
            TODO: Add example code
        </code>

*/
// *****************************************************************************
GFX_STATUS GFX_GOL_ObjectDelete(GFX_GOL_OBJ_HEADER *pObject);

// *****************************************************************************
/*  Function:
    GFX_STATUS GFX_GOL_ObjectByIDDelete(uint16_t id)

    Summary:
        This function removes an object with the given user
        defined ID from the currently active list.

    Description:
        This function removes an object with the given user
        defined ID from the currently active list.
        Aside from the removal of the object from the list,
        the RAM resources consumed by the object is also freed.

        If there is no object with the given ID, the function exits
        with GFX_STATUS_FAILURE.

    Precondition:
        None.

    Parameters:
        Pointer to the object that will removed from the list.

    Returns:
        GFX_STATUS_SUCCESS - is returned if the removal was successful.
        GFX_STATUS_FAILURE - is returned if the removal was not successful.

    Example:
        <code>
            TODO: Add example code
        </code>

*/
// *****************************************************************************
GFX_STATUS GFX_GOL_ObjectByIDDelete(uint16_t id);


// *****************************************************************************
/*  Function:
    GFX_STATUS GFX_GOL_ObjectListNew(void)

    Summary:
        This function removes an object with the given user
        defined ID from the currently active list.

    Description:
        This function starts a new linked list of objects and
        resets the keyboard focus to none. This function assigns
        the current active list and current focused object
        (receiving keyboard inputs) object pointers to NULL.
        Any keyboard inputs at this point will be ignored.

        This function does not erase the objects in the previous
        list. Application must save the previous list to
        another pointer if to be referenced later. If not needed
        anymore, memory used by that list should be freed by
        GFX_GOL_ObjectListFree() function. In this case, freeing
        the list with GFX_GOL_ObjectListFree() function has the same
        effect as GFX_GOL_ObjectListNew() where the current active
        list is empty.

    Precondition:
        None.

    Parameters:
        None.

    Returns:
        GFX_STATUS_SUCCESS - is returned if the new list start was successful.
        GFX_STATUS_FAILURE - is returned if the new list start was not
                             successful.

    Example:
        <code>
            // assume pointers to objects (pButton, pWindow and pSlider
            // are initialized to objects already created
            // GFX_GOL_OBJ_HEADER *pButton;
            // GFX_GOL_OBJ_HEADER *pWindow;
            // GFX_GOL_OBJ_HEADER *pSlider;

            GFX_GOL_OBJ_HEADER *pSave;

            // save current list
            pSave = GFX_GOL_ObjectListGet();

            // start the new list, after the start of the list, the
            // current active list is empty.
            GFX_GOL_ObjectListNew();

            // assume that objects are already created
            // you can now add objects to the new list
            GFX_GOL_ObjectAdd(pButton);
            GFX_GOL_ObjectAdd(pWindow);
            GFX_GOL_ObjectAdd(pSlider);

        </code>

*/
// *****************************************************************************
GFX_STATUS GFX_GOL_ObjectListNew(void);

// *****************************************************************************
/*  Function:
    GFX_GOL_OBJ_HEADER *GFX_GOL_ObjectListGet(void)

    Summary:
        This function returns the current active list.

    Description:
        This function returns the pointer to the current active.

    Precondition:
        None.

    Parameters:
        None.

    Returns:
        Pointer (type GFX_GOL_OBJ_HEADER) to the current active list.

    Example:
        See GFX_GOL_ObjectListNew() for example code.

*/
// *****************************************************************************
GFX_GOL_OBJ_HEADER *GFX_GOL_ObjectListGet(void);

// *****************************************************************************
/*  Function:
    GFX_STATUS *GFX_GOL_ObjectListSet(GFX_GOL_OBJ_HEADER *pList)

    Summary:
        This function sets the active list to the new list.

    Description:
        This function sets the active list to the new list.
        The previous list will still exist in memory. Application
        must save the previous list before the set is called if the
        previous list will be referenced later. If the previous list
        is not needed anymore, then the list must be removed from
        memory by GFX_GOL_ObjectListFree() function.

        Setting the active list to the new list will reset the focused
        pointer object to NULL.

    Precondition:
        None.

    Parameters:
        Pointer to the new list.

    Returns:
        GFX_STATUS_SUCCESS - is returned if the set was successful.
        GFX_STATUS_FAILURE - is returned if the set was not successful.

    Example:
       <code>
            GFX_GOL_OBJ_HEADER *pSave;

            // save current list
            pSave = GFX_GOL_ObjectListSet();

            // start the new list
            GFX_GOL_ObjectListNew();

            // you can now add objects to the current list
            // assume that objects are already created
            GFX_GOL_ObjectAdd(pButton);
            GFX_GOL_ObjectAdd(pWindow);
            GFX_GOL_ObjectAdd(pSlider);

            // do something here on the new list

            // return the old list
            GOLSetList(pSave);
       </code>

*/
// *****************************************************************************
GFX_STATUS GFX_GOL_ObjectListSet(GFX_GOL_OBJ_HEADER *pList);

// *****************************************************************************
/*  Function:
    GFX_STATUS GFX_GOL_ObjectListFree(void)

    Summary:
        This function sets the active list to the new list.

    Description:
        This function frees all the memory used by objects in
        the active list and initializes the active list pointer
        to NULL to start a new empty list. This function must
        be called only inside the GFX_GOL_ObjectDrawCallback()
        function when using GFX_GOL_ObjectListDraw() and
        GFX_GOL_ObjectMessage() functions. This requirement
        assures that primitive rendering settings are not altered
        by the rendering state machines of the objects.

    Precondition:
        None.

    Parameters:
        None.

    Returns:
        GFX_STATUS_SUCCESS - is returned if the free was successful.
        GFX_STATUS_FAILURE - is returned if the free was not successful.

    Example:
       <code>
            void DeletePage(GFX_GOL_OBJ_HEADER *pPage)
            {
                GFX_GOL_OBJ_HEADER *pTemp;

                // assuming pPage is different from the current active list
                // save the active list
        pTemp = GFX_GOL_ObjectListGet();

                // set list as active list
                GFX_GOL_ObjectListSet(pPage);

                // pPage objects are deleted
        GFX_GOL_ObjectListFree();

                // restore the active list
        GFX_GOL_ObjectListSet(pTemp);
            }
       </code>

*/
// *****************************************************************************
GFX_STATUS GFX_GOL_ObjectListFree(void);

// *****************************************************************************
/*  Function:
    GFX_STATUS GFX_GOL_ObjectStateSet(
                                GFX_GOL_OBJ_HEADER *pObject,
                                uint16_t stateBits);

    Summary:
        This function sets the state bits of the given object.

    Description:
        This function sets the state bits of the given object. Object
        must be redrawn to display the changes. It is possible to set
        several state bits with this function.

    Precondition:
        None.

    Parameters:
        pObject - Pointer to the object.
        stateBits - Defines which state bits are to be  cleared.
                    Please refer to specific objects for object
                    state bits definition for details

    Returns:
        GFX_STATUS_SUCCESS - is returned if the set was successful.
        GFX_STATUS_FAILURE - is returned if the set was not successful.

    Example:
        <code>
            void SetMessage(uint16_t msg, GFX_GOL_BUTTON* pB)
            {
                switch(msg)
                {
                    case GFX_GOL_BUTTON_ACTION_PRESSED:
                        // set pressed and redraw
                        GFX_GOL_ObjectStateSet(pB, BTN_PRESSED|BTN_DRAW);
                        break;
                    case GFX_GOL_BUTTON_ACTION_RELEASED:
                        // reset pressed
                        GFX_GOL_ObjectStateClear(pB, BTN_PRESSED);
                        // redraw
                        GFX_GOL_ObjectStateSet(pB, BTN_DRAW);
                        break;
                    default:
                        break;
                }
            }
        </code>

*/
// *****************************************************************************
#define GFX_GOL_ObjectStateSet(pObject, stateBits)      \
                ((((GFX_GOL_OBJ_HEADER*)pObject)->state) |= stateBits)


// *****************************************************************************
/*  Function:
    GFX_STATUS GFX_GOL_ObjectStateClear(
                                GFX_GOL_OBJ_HEADER *pObject,
                                uint16_t stateBits);

    Summary:
        This function clears the state bits of the given object.

    Description:
        This function clears the state bits of the given object. Object
        must be redrawn to display the changes. It is possible to set
        several state bits with this function.

    Precondition:
        None.

    Parameters:
        pObject - Pointer to the object.
        stateBits - Defines which state bits are to be  cleared.
                    Please refer to specific objects for object
                    state bits definition for details
    Returns:
        GFX_STATUS_SUCCESS - is returned if the clear was successful.
        GFX_STATUS_FAILURE - is returned if the clear was not successful.

    Example:
        See GFX_GOL_ObjectStateSet() for code example.

*/
// *****************************************************************************
#define GFX_GOL_ObjectStateClear(pObject, stateBits)        \
                ((((GFX_GOL_OBJ_HEADER*)pObject)->state) &= (~(stateBits)))

// *****************************************************************************
/*  Function:
    uint16_t GFX_GOL_ObjectStateGet(
                                GFX_GOL_OBJ_HEADER *pObject,
                                uint16_t stateBits);

    Summary:
        This function retrieves the current value of the state bits of
        an object.

    Description:
        This function retrieves the current value of the state bits of
        an object. It is possible to get several state bits.

    Precondition:
        None.

    Parameters:
        pObject - Pointer to the object.
        stateBits - Defines which state bits are to be retrieved.
                    Please refer to specific objects for object
                    state bits definition for details
    Returns:
        The current status of the specified state bits.

    Example:
        <code>

            #define BTN_HIDE 0x8000

            GFX_GOL_BUTTON *pB;
            // pB is created and initialized
            // do something here to set state

            // Hide the button (remove from screen)
            if (GFX_GOL_ObjectStateGet(pB, GFX_GOL_BUTTON_HIDE_STATE))
            {
                GFX_ColorSet(pB->pGolScheme->CommonBkColor);
                GFX_BarDraw(pB->left, pB->top,pB->right,pB->bottom);
            }
        </code>
*/
// *****************************************************************************
#define GFX_GOL_ObjectStateGet(pObject, stateBits)      \
                (((GFX_GOL_OBJ_HEADER*)pObject)->state & stateBits)

// *****************************************************************************
/*  Function:
    GFX_STATUS GFX_GOL_ObjectListDraw(void)

    Summary:
        This function redraws all objects in the current active list
        that has the rendering state bits set.

    Description:
        This function loops through the active list and redraws
        objects that need to be redrawn. Partial redrawing or
        full redraw is performed depending on the drawing states
        of the objects.

        GFX_GOL_ObjectDrawCallback() function is called by
        GFX_GOL_ObjectListDraw() when drawing of objects in the
        active list is completed. GFX_GOL_ObjectDrawCallback()
        is an application implemented function that allows the
        application the opportunity to insert application specific
        rendering using Primitive Layer rendering functions.

        The GFX_GOL_ObjectListDraw() function can return with GFX_STATUS_BUSY.
        In this case, it indicates that the currently redrawn object is
        not able to continue. Application needs to call GFX_GOL_ObjectListDraw()
        again to continue the redraw of the objects in the list.

    Precondition:
        None.

    Parameters:
        None.

    Returns:
        GFX_STATUS_SUCCESS - is returned when the active list is completely
                             parsed and redrawn.
        GFX_STATUS_BUSY    - is returned when the active list is not completely
                             parsed and redrawn.

    Example:
        <code>
            // Assume objects are created & states are set to draw objects
            while(1)
            {
                // parse active list and redraw objects
                // that needs to be redrawn
        if( GFX_GOL_ObjectListDraw() == GFX_STATUS_SUCCESS)
                {
                    // at this point drawing is completed
                    // it is safe to modify objects states and linked list

                    // evaluate messages from touch screen device
                    TouchGetMsg(&msg);

                    // evaluate each object is affected by the message
                    GFX_GOL_ObjectMessage(&msg);
                }
            }
        </code>
*/
// *****************************************************************************
GFX_STATUS GFX_GOL_ObjectListDraw(void);

// *****************************************************************************
/*  Function:
    void GFX_GOL_ObjectRectangleRedraw(
                                uint16_t left,
                                uint16_t top,
                                uint16_t right,
                                uint16_t bottom)

    Summary:
        This function marks all objects in the active list intersected
        by the given rectangular area to be redrawn.

    Description:
        This function marks all objects in the active list intersected
        by the given rectangular area to be redrawn.

        After calling this function, the next call to GFX_GOL_ObjectListDraw()
        will redraw all objects that are marked for redraw.

    Precondition:
        None.

    Parameters:
        left   - Defines the left most border of the rectangle area.
        top    - Defines the top most border of the rectangle area.
        right  - Defines the right most border of the rectangle area.
        bottom - Defines the bottom most border of the rectangle area.

    Returns:
        None.

    Example:
        <code>
            GFX_GOL_OBJ_HEADER *pTemp;
            GFX_GOL_OBJ_HEADER *pAllObjects;

            // assume *pAllObjects points to a list of all existing objects
            // created and initialized

            // mark all objects inside the rectangle to be redrawn
            GOLRedrawRec(10,10,100,100);

            // save the current active list
            pTemp = pAllObjects;

            // reset active list
            GFX_GOL_ObjectListNew();

            // build the new active list with only those objects that
            // are marked to be redrawn
            while(pTemp->pNxtObj != NULL)
            {
                if (pTemp->state&0x7C00)
                    GFX_GOL_ObjectAdd(pTemp);

                pTemp = pTemp->pNxtObj;
            }

             // redraw active list
            GFX_GOL_ObjectListDraw();
        </code>
*/
// *****************************************************************************
void GFX_GOL_ObjectRectangleRedraw( uint16_t left,
                                    uint16_t top,
                                    uint16_t right,
                                    uint16_t bottom);

// *****************************************************************************
/*  Function:
    void GFX_GOL_ObjectDrawEnable(GFX_GOL_OBJ_HEADER *pObject)

    Summary:
        This function sets the object to be redraw.

    Description:
        This function sets the object to be redrawn. For the redraw
        to be effective, the object must be in the current active list.
        If not, the redraw action will not be performed until the list
        where the object is currently inserted will be set as the active
        list.

    Precondition:
        None.

    Parameters:
        pObject - pointer to the object that will be redrawn.

    Returns:
        None.

    Example:
        <code>
            void GOLRedrawRec(uint16_t left, uint16_t top,
                              uint16_t right, uint16_t bottom)
            {

                GFX_GOL_OBJ_HEADER  *pCurrentObj;
                int                 overlapX, overlapY;

                pCurrentObj = _pGolObjects;

                while(pCurrentObj != NULL)
                {
                    overlapX = overlapY = 0;

                    // check overlaps in x direction
                    if (((pCurrentObj->left <= left)  && (pCurrentObj->right >= left))  ||   \
                        ((pCurrentObj->left <= right) && (pCurrentObj->right >= right)) ||   \
                        ((pCurrentObj->left <= left)  && (pCurrentObj->right >= right)) ||   \
                        ((pCurrentObj->left >= left)  && (pCurrentObj->right <= right))      \
                      )
                        overlapX = 1;

                    // check overlaps in y direction
                    if (((pCurrentObj->top <= top)    && (pCurrentObj->bottom >= top))    ||   \
                        ((pCurrentObj->top <= bottom) && (pCurrentObj->bottom >= bottom)) ||   \
                        ((pCurrentObj->top <= top)    && (pCurrentObj->bottom >= bottom)) ||   \
                        ((pCurrentObj->top >= top)    && (pCurrentObj->bottom <= bottom))      \
                      )
                        overlapY = 1;

                    // when any portion of the widget is touched by the defined rectangle the
                    // x and y overlaps will exist.
                    if (overlapX & overlapY) {
                        GFX_GOL_ObjectRedraw(pCurrentObj);
                    }

                    pCurrentObj = (GFX_GOL_OBJ_HEADER *)pCurrentObj->pNxtObj;
                }   //end of while

            }
        </code>
*/
// *****************************************************************************
void GFX_GOL_ObjectDrawEnable(GFX_GOL_OBJ_HEADER *pObject);

// *****************************************************************************
/*  Function:
    void GFX_GOL_ObjectDrawDisable(GFX_GOL_OBJ_HEADER *pObject)

    Summary:
        This function resets the drawing state bits of the object.

    Description:
        This function resets the drawing state bits of the object.
        This function can be called to cancel any drawing state bits
        that has been set or clears all the drawing state bits after
        the object has been redrawn.

    Precondition:
        None.

    Parameters:
        pObject - pointer to the object.

    Returns:
        None.

    Example:
        None.

*/
// *****************************************************************************
void GFX_GOL_ObjectDrawDisable(GFX_GOL_OBJ_HEADER *pObject);

// *****************************************************************************
/*  Function:
    bool GFX_GOL_ObjectIsRedrawSet(
                                GFX_GOL_OBJ_HEADER *pObject)

    Summary:
        This function checks if the object needs to be redrawn or not.

    Description:
        This function checks if the object needs to be redrawn or not.
        The function returns true if it is to be redrawn
        or false if it is not to be redrawn.

    Precondition:
        None.

    Parameters:
        pObject - pointer to the object that will be checked.

    Returns:
        true - when the object needs to be redrawn.
        false - when the object does not need to be redrawn.

    Example:
        <code>
            int DrawButtonWindowOnly()
            {
                static GFX_GOL_OBJ_HEADER *pCurrentObj = NULL;
                uint16_t done = 0;

                if (pCurrentObj == NULL)
                {
                    // get current list
                   pCurrentObj = GFX_GOL_ObjectListGet();
                }

                while(pCurrentObj != NULL)
                {
                    if(GFX_GOL_ObjectIsRedrawSet(pCurrentObj) == true)
                    {
                        done = pCurrentObj->draw(pCurrentObj);

                        // reset state of object if done
                        if (done)
                            GOLDrawComplete(pCurrentObj)
                            // Return if not done. This means that Button Draw function
                            // was not able to finish redrawing the object
                            // and must be called again to finish rendering of
                            // objects in the list that have new states.
                        else
                            return 0;
                    }
                    // go to the next object in the list
                    pCurrentObj = pCurrentObj->pNxtObj;
                }
                return 1;
            }
        </code>
*/
// *****************************************************************************
bool GFX_GOL_ObjectIsRedrawSet(GFX_GOL_OBJ_HEADER *pObject);


// *****************************************************************************
/*  Function:
    void  GFX_GOL_ObjectMessage(GFX_GOL_MESSAGE *pMessage)

    Summary:
        This function process the received message from the user
        to determine the affected objects. Depending on the message
        and the affected objects, object states are modified based
        on the default behaviour or user defined behaviour.

    Description:
        This function receives a GFX_GOL_MESSAGE message from user and
        loops through the active list of objects to check which object
        is affected by the message. For affected objects the message
        is translated and GFX_GOL_ObjectMessageCallback() is called.
        In the call back function, user has the ability to implement
        action for the message. If the call back function returns
        non-zero, OBJMsgDefault() is called to process message for
        the object by default.
        If zero is returned OBJMsgDefault() is not called.
        Please refer to GOL Messages section for details.

    Precondition:
        None.

    Parameters:
        pMessage - Pointer to the message from user.

    Returns:
        None.

    Example:
        <code>
            // Assume objects are created & states are set to draw objects
            while (1)
            {
                if(GOLDraw())
                {
                    // GOL drawing is completed here
                    // it is safe to change objects

                    // from user interface module
                    TouchGetMsg(&msg);
                    // process the message
                    GFX_GOL_ObjectMessage(&msg);
                }
            }
        </code>
*/
// *****************************************************************************
void  GFX_GOL_ObjectMessage(GFX_GOL_MESSAGE *pMsg);

// DOM-IGNORE-BEGIN
// *****************************************************************************
/*  Function:
    void GFX_GOL_PanelParameterSet(
                                uint16_t left,
                                uint16_t top,
                                uint16_t right,
                                uint16_t bottom,
                                uint16_t radius,
                                GFX_COLOR faceClr,
                                GFX_COLOR embossLtClr,
                                GFX_COLOR embossDkClr,
                                GFX_RESOURCE_HDR *pBitmap,
                                GFX_FILL_STYLE fillStyle,
                                uint16_t embossSize)

    Summary:
        This function sets the parameters to draw a panel.

    Description:
        This function sets the parameters to draw a panel.
        Panel is not an object. It is a routine to draw a basic
        component of objects. The actual drawing of the panel
        is performed by the GFX_GOL_PanelDraw(). After the parameters
        are set, call GFX_GOL_PanelDraw() to render the panel.
        The panel is drawn using the following:
        1. Panel width is determined by right - left.
        2. Panel height is determined by top - bottom.
        3. Panel radius - specifies if the panel will have a rounded
                          edge. If zero then the panel will have
                          sharp (cornered) edge.
        4. If 2*radius = height = width, the panel is circular.
        5. If the panel is drawn with an image, pBitmap should point
           to an image resource.
        6. If the panel face is drawn with the fill style specified
           by fillStyle. When gradient fill is used, set the gradient
           colors using GFX_GOL_PanelGradientParameterSet(). When
           alpha blending fill is used, set the alpha blending value
           using GFX_GOL_PanelAlphaParameterSet().

    Precondition:
        None.

    Parameters:
        left - defines the left most pixel of the panel.
        top - defines the top most pixel of the panel.
        right - defines the right most pixel of the panel.
        bottom - defines the bottom most pixel of the panel.
        radius - defines the radius of the rounded corner. A zero value
                 will result in a rectangular panel drawn.
        faceClr - the color used for the face of the panel.
        embossLtClr - the color used for the light emboss color
                      for 3D effect.
        embossDkClr - the color used for the dark emboss color
                      for 3D effect.
        pBitmap - pointer to the image resource of the panel.
        fillStyle - fill style use for the face of the panel.
        embossSize - when this is not zero, the embossLtClr and embossDkClr
                     are used to draw the 3D effect. When this is set
                     to zero, there will be no 3D effect.

    Returns:
        None.

    Example:
        None.
*/
// *****************************************************************************
// DOM-IGNORE-END
void GFX_GOL_PanelParameterSet(
                                uint16_t left,
                                uint16_t top,
                                uint16_t right,
                                uint16_t bottom,
                                uint16_t radius,
                                GFX_COLOR faceClr,
                                GFX_COLOR embossLtClr,
                                GFX_COLOR embossDkClr,
                                GFX_RESOURCE_HDR *pBitmap,
                                GFX_FILL_STYLE fillStyle,
                                uint16_t embossSize);

// DOM-IGNORE-BEGIN
// *****************************************************************************
/*  Function:
    void GFX_GOL_PanelBackgroundSet(GFX_GOL_OBJ_HEADER *pObjectHeader)

    Summary:
        This function sets panel background information.

    Description:
        This function sets panel background information.
        This is an internal function and should not be called
        by the application.

    Precondition:
        None.

    Parameters:
        pObjectHeader - the object header of the object that needs to
                        draw a panel with background.

     Returns:
        None.

    Example:
        None.
*/
// *****************************************************************************
// DOM-IGNORE-END
void GFX_GOL_PanelBackgroundSet(GFX_GOL_OBJ_HEADER *pObjectHeader);


// DOM-IGNORE-BEGIN
// *****************************************************************************
/*  Function:
    void GFX_GOL_PanelGradientParameterSet(
                                GFX_COLOR startColor,
                                GFX_COLOR endColor)

    Summary:
        This function sets the gradient fill start and end colors
        of a panel.

    Description:
        This function sets the gradient fill start and end colors
        of a panel. This along with the parameters set by the function
        GFX_GOL_PanelParameterSet() will determine how the panel will
        be drawn. The actual drawing of the panel is performed by
        GFX_GOL_PanelDraw().

    Precondition:
        None.

    Parameters:
        startColor - the gradient fill start color.
        endColor - the gradient fill end color.

    Returns:
        None.

    Example:
        None.
*/
// *****************************************************************************
// DOM-IGNORE-END
#ifndef GFX_CONFIG_GRADIENT_DISABLE
void GFX_GOL_PanelGradientParameterSet(
                                GFX_COLOR startColor,
                                GFX_COLOR endColor);
#endif


// DOM-IGNORE-BEGIN
// *****************************************************************************
/*  Function:
    void GFX_GOL_PanelAlphaParameterSet(
                                uint16_t alphaValue)

    Summary:
        This function sets the alpha blending value when using
        alpha blending in panels.

    Description:
        This function sets the alpha blending value when using
        alpha blending in panels. This along with the parameters set
        by the function GFX_GOL_PanelParameterSet() will determine
        how the panel will be drawn. The actual drawing of the panel
        is performed by GFX_GOL_PanelDraw().

    Precondition:
        None.

    Parameters:
        alphaVlaue - the alpha value used to render alpha blended panels.

    Returns:
        None.

    Example:
        None.
*/
// *****************************************************************************
// DOM-IGNORE-END
#ifndef GFX_CONFIG_ALPHABLEND_DISABLE
void GFX_GOL_PanelAlphaParameterSet(
                                uint16_t alphaValue);
#endif

// DOM-IGNORE-BEGIN
// *****************************************************************************
/*  Function:
    GFX_STATUS GFX_GOL_PanelDraw(void)

    Summary:
        This function renders the panel.

    Description:
        This function renders the panel. Panel parameters are
        set by the GFX_GOL_PanelParameterSet() and
        GFX_GOL_PanelGradientParameterSet() or GFX_GOL_PanelAlphaParameterSet().
        The function returns success (GFX_STATUS_SUCCESS) when the panel
        is rendered. If the function returned not success this function
        must be called again until success is returned.

    Precondition:
        Panel parameters must be set first using GFX_GOL_PanelParameterSet()
        and GFX_GOL_PanelGradientParameterSet() or
        GFX_GOL_PanelAlphaParameterSet().

    Parameters:
        None.

    Returns:
        GFX_STATUS_SUCCESS - when the panel rendering is done.
        GFX_STATUS_FAILURE - when the panel rendering is not yet done.

    Example:
        None.

*/
// *****************************************************************************
// DOM-IGNORE-END
GFX_STATUS GFX_GOL_PanelDraw(void);

// DOM-IGNORE-BEGIN
// *****************************************************************************
/*  Function:
    GFX_STATUS GFX_GOL_TwoTonePanelDraw(void)

    Summary:
        This function renders the two-tone panel.

    Description:
        This function renders the two-tone panel. Panel parameters are
        set by the GFX_GOL_PanelParameterSet(). The function returns
        success (GFX_STATUS_SUCCESS) when the panel is rendered. If
        the function returned not success this function must be
        called again until success is returned.

    Precondition:
        Panel parameters must be set first using GFX_GOL_PanelParameterSet().

    Parameters:
        None.

    Returns:
        GFX_STATUS_SUCCESS - when the panel rendering is done.
        GFX_STATUS_FAILURE - when the panel rendering is not yet done.

    Example:
        None.
*/
// *****************************************************************************
// DOM-IGNORE-END
GFX_STATUS GFX_GOL_TwoTonePanelDraw(void);

// DOM-IGNORE-BEGIN
// *****************************************************************************
/*  Function:
    GFX_STATUS GFX_GOL_ObjectHideDraw(GFX_GOL_OBJ_HEADER *pObject)

    Summary:
        This function performs the hiding of an object from the screen.

    Description:
        This function performs the hiding of an object from the screen.
        If the object's style scheme is set to have a background, the
        background is taken into account.

    Precondition:
        None.

    Parameters:
        None.

    Returns:
        GFX_STATUS_SUCCESS - when the hiding is done.
        GFX_STATUS_FAILURE - when the hiding is not yet done.

    Example:
        None.
*/
// *****************************************************************************
// DOM-IGNORE-END
GFX_STATUS GFX_GOL_ObjectHideDraw(GFX_GOL_OBJ_HEADER *pObject);

// *****************************************************************************
/*  Function:
    GFX_STATUS GFX_GOL_ObjectBackGroundSet(GFX_GOL_OBJ_HEADER *pObject)

    Summary:
        This function sets the background information.

    Description:
        This function sets the background information. This is an internal
        function and should not be called by the application. This function
        is used by object's drawing functions to set the background
        information.

    Precondition:
        None.

    Parameters:
        None.

    Returns:
        None.

    Example:
        None.
*/
// *****************************************************************************
void GFX_GOL_ObjectBackGroundSet(GFX_GOL_OBJ_HEADER *pObjectHeader);


///*********************************************************************
// * Overview: Pointer to the GOL default scheme (GFX_OBJ_SCHEME). This
// *			scheme is created in GFX_Initialize() function. GOL scheme
// *			defines the style scheme to be used by an object.
// *			Use GFX_GOL_SchemeDefaultGet() to get this pointer.
// *
// *********************************************************************/
//extern GFX_GOL_OBJ_SCHEME *_pDefaultGolScheme;
//
///*********************************************************************
// * Overview: The default font GOLFontDefault is declared in
// *           GOLFontDefault.c file included in the Graphics Library.
// *           To use this default font, USE_GOL must be defined in
// *           GraphicsConfig.h.
// *           To replace this default font, add the appropriate
// *           declaration in the GraphicsConfig.h:
// *           - #define FONTDEFAULT FontName - This macro is deprecated.
// *                                       use FONTDEFAULT_FLASH instead.
// *                                       This is for default font
// *                                       located in flash memory.
// *           - #define FONTDEFAULT_FLASH FontName - This is for default
// *                                       font located in flash memory.
// *           - #define FONTDEFAULT_EXTERNAL FontName - This is for default
// *                                       font located in external memory.
// *           Then in the project the "FontName" must be added.
// *           The Graphics Library will then use the font that the user
// *           supplied.
// *
// *  Note: When the default font is placed in external resource (or memory),
// *        any calls  to GFX_PRIM_TextStringPut(), OutTextXY() and GFX_PRIM_TextCharPut() will not
// *        work if the external resource is not programmed with the font
// *        table.
// *********************************************************************/
//#if ((defined(FONTDEFAULT_FLASH) || defined (FONTDEFAULT)) && defined(FONTDEFAULT_EXTERNAL))
//
//// Error check.
//#error "Cannot define two default fonts"
//
//#elif !defined(FONTDEFAULT_FLASH) && !defined(FONTDEFAULT_EXTERNAL) && !defined(FONTDEFAULT)
//
//// Use the default GOL font in GOLFontDefault.c
//#define FONTDEFAULT GOLFontDefault
//// Default GOL font.
//extern const GFX_RESOURCE_HDR FONTDEFAULT;
//
//#elif defined(FONTDEFAULT)
//
//// for existing projects using FONTDEFAULT macro to define default font
//// Default GOL font.
//extern const GFX_RESOURCE_HDR FONTDEFAULT;
//
//#elif defined(FONTDEFAULT_FLASH)
//
//// Default GOL font.
//#define FONTDEFAULT FONTDEFAULT_FLASH
//extern const GFX_RESOURCE_HDR FONTDEFAULT_FLASH;
//
//#elif defined(FONTDEFAULT_EXTERNAL)
//
//// Default GOL font.
//#define FONTDEFAULT FONTDEFAULT_EXTERNAL
//extern const FONT_EXTERNAL FONTDEFAULT_EXTERNAL;
//
//#endif

#endif // _GOL_H
