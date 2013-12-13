/*******************************************************************************
  Graphics Library Implementation

  Company:
    Microchip Technology Inc.

  FileName:
    gfx_gol_custom_control.c

  Summary:
    This implements the custom control object of the GOL.

  Description:
    Refer to Microchip Graphics Library for complete documentation of the
    CustomControl Object.
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


#ifndef _CUSTOM_H
#define _CUSTOM_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
#include <gfx/gfx_gol.h>

// Control states
#define GFX_GOL_CUSTOMCONTROL_DISABLED 0x0002  // disabled
#define GFX_GOL_CUSTOMCONTROL_HIDE     0x8000  // must be removed from screen
#define GFX_GOL_CUSTOMCONTROL_DRAW_BAR 0x2000  // control bar should be redrawn
#define GFX_GOL_CUSTOMCONTROL_DRAW     0x4000  // whole control must be redrawn

// The structure contains data for the control
typedef struct {
//    uint8_t instance;
//    uint16_t ID; // instance unique ID
//    void *pNxtObj; // a pointer to the next object in the linked list
//    GFX_GOL_OBJ_TYPE type; // must be set to OBJ_CUSTOM
//    uint16_t state; // state
//    uint16_t left; // left border
//    uint16_t top; // top border
//    uint16_t right; // right border
//    uint16_t bottom; // bottom border
//    GFX_GOL_OBJ_SCHEME *pGolScheme; // the style scheme used
//    DRAW_FUNC draw;
//    FREE_FUNC FreeObj; // function pointer to the object free function
//    ACTIONGET_FUNC actionGet; // function pointer to the object message function
//    ACTIONSET_FUNC actionSet; // function pointer to the object default message function
    GFX_GOL_OBJ_HEADER hdr; // Generic header for all Objects (see GFX_OBJ_HEADER).
    uint8_t instance;
    uint16_t ID; // instance unique ID
    void *pNxtObj; // a pointer to the next object in the linked list
    GFX_GOL_OBJ_TYPE type; // must be set to OBJ_CUSTOM
    uint16_t state; // state
    uint16_t left; // left border
    uint16_t top; // top border
    uint16_t right; // right border
    uint16_t bottom; // bottom border
    GFX_GOL_OBJ_SCHEME *pGolScheme; // the style scheme used
    DRAW_FUNC draw;
    FREE_FUNC FreeObj; // function pointer to the object free function
    ACTIONGET_FUNC actionGet; // function pointer to the object message function
    ACTIONSET_FUNC actionSet; // function pointer to the object default message function
    uint16_t pos; // current position
    uint16_t prevPos; // previous position
} GFX_GOL_CUSTOMCONTROL;

/*********************************************************************
 * Macros:  GFX_GOL_CustomControlGetPos(pCc)
 *
 * PreCondition: none
 *
 * Input: pCc - pointer to the object
 *
 * Output: current position
 *
 * Side Effects: none
 *
 * Overview: returns position
 *
 * Note: none
 *
 ********************************************************************/
#define GFX_GOL_CustomControlGetPos(pCc)   pCc->pos

/*********************************************************************
 * Macros: GFX_GOL_CustomControlSetPos(pCc,position)
 *
 * PreCondition: none
 *
 * Input: pCc - the pointer to the object
 *        position - new position
 *
 * Output: none
 *
 * Overview: sets the current position of the control
 *
 * Note: none
 *
 ********************************************************************/
#define GFX_GOL_CustomControlSetPos(pCc, position) pCc->pos = position

/*********************************************************************
 * Function: GFX_GOL_CUSTOMCONTROL  *GFX_GOL_CustomControlCreate(uint16_t ID, uint16_t left, uint16_t top, uint16_t right,
 *                              uint16_t bottom, uint16_t state, GFX_GOL_OBJ_SCHEME *pScheme)
 *
 * PreCondition: none
 *
 * Input: ID - instance unique ID
 *        left, top, right, bottom - dimensions of the object
 *        state - state of the object
 *        pScheme - pointer to the style scheme
 *
 * Output: returns the pointer to the object created
 *
 * Side Effects: none
 *
 * Overview: creates the custom control
 *
 * Note: none
 *
 ********************************************************************/
GFX_GOL_CUSTOMCONTROL * GFX_GOL_CustomControlCreate(uint16_t ID, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint16_t state, GFX_GOL_OBJ_SCHEME * pScheme);

/*********************************************************************
 * Function: uint16_t GFX_GOL_CustomControlActionGet(void *pObj, GFX_GOL_MESSAGE *pMsg)
 *
 * PreCondition: none
 *
 * Input: pMsg - pointer to the GOL message
 *        pCc - the pointer to the custom control
 *
 * Output: translated message for the custom control
 *
 * Side Effects: none
 *
 * Overview: translates the GOL message for the custom control
 *
 * Note: none
 *
 ********************************************************************/
GFX_GOL_TRANSLATED_ACTION GFX_GOL_CustomControlActionGet(void *pObj, GFX_GOL_MESSAGE *pMsg);

/*********************************************************************
 * Function: void GFX_GOL_CustomControlActionSet(void *pObj, GFX_GOL_MESSAGE* pMsg)
 *
 * PreCondition: none
 *
 * Input: pMsg -  pointer to the GOL message
 *        pCc - the pointer to the custom control
 *
 * Output: none
 *
 * Side Effects: none
 *
 * Overview: changes the state of the object
 *
 * Note: none
 *
 ********************************************************************/
void GFX_GOL_CustomControlActionSet(GFX_GOL_TRANSLATED_ACTION translatedMsg, void *pObj, GFX_GOL_MESSAGE *pMsg);

/*********************************************************************
 * Function: uint16_t GFX_GOL_CustomControlDraw(CUSTOM *pCc)
 *
 * PreCondition: none
 *
 * Input: pCc - pointer to the custom control
 *
 * Output: returns the status of the drawing
 *		  0 - not completed
 *         1 - done
 *
 * Side Effects: none
 *
 * Overview: draws custom control
 *
 * Note: none
 *
 ********************************************************************/
GFX_STATUS GFX_GOL_CustomControlDraw(void *pObj);
#endif // _CUSTOM_H
