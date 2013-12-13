/*******************************************************************************
  Module for Microchip Graphics Library - Graphic Object Layer

  Company:
    Microchip Technology Inc.

  FileName:
    gfx_gol_round_dial.h

  Summary:
    This is the header file for the round dial object of the GOL.

  Description:
   Refer to Microchip Graphics Library for complete documentation of the
   Round dial Object.
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


#ifndef _ROUNDDIAL_H
    #define _ROUNDDIAL_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

    #include <gfx/gfx_gol.h>

/*********************************************************************
* Object States Definition: 
*********************************************************************/
    #define GFX_GOL_ROUNDDIAL_DISABLED   0x0002  // Bit for disabled state.
    #define GFX_GOL_ROUNDDIAL_ROT_CW     0x0004  // Bit for rotate clockwise state.
    #define GFX_GOL_ROUNDDIAL_ROT_CCW    0x0008  // Bit for rotate counter clockwise state.
    #define GFX_GOL_ROUNDDIAL_DRAW       0x4000  // Bit to indicate object must be redrawn.
    #define GFX_GOL_ROUNDDIAL_HIDE       0x8000  // Bit to indicate object must be removed from screen.
#ifdef USE_KEYBOARD
    #define GFX_GOL_ROUNDDIAL_QUADRANT_POSITIONS 6
    #define GFX_GOL_ROUNDDIAL_MAX_POSITIONS      24
	extern short    _cosine[GFX_GOL_ROUNDDIAL_QUADRANT_POSITIONS];
	short           RdiaCosine(short v);
	short           RdiaSine(short v);
#endif


// *****************************************************************************
/*

  Summary:
     Defines the parameters required for a dial Object.

  Description:
    The curr_xPos, curr_yPos, new_xPos and new_yPos parameters
    are internally generated to aid in the redrawing of the
    dial. User must avoid modifying these values.

  Remarks:

*/
typedef struct
{
    GFX_GOL_OBJ_HEADER      hdr;        // Generic header for all Objects (see GFX_OBJ_HEADER).
    uint16_t           xCenter;        // x coordinate center position.
    uint16_t           yCenter;        // y coordinate center position.
    uint16_t           radius;         // Radius of the dial.
    uint16_t           value;          // Initial value of the dial.
    uint16_t        max;            // Maximum value of variable value (maximum = 65535).

    // Minimum is always zero.
    uint16_t        res;            // Resolution of movement.
    uint16_t           curr_xPos;      // Current x position.
    uint16_t           curr_yPos;      // Current y position.
    uint16_t           new_xPos;       // New x position.
    uint16_t           new_yPos;       // New y position.
    #ifdef USE_KEYBOARD
    short 			vAngle;
    #endif
} GFX_GOL_ROUNDDIAL;

/*********************************************************************
* Function: GFX_GOL_ROUNDDIAL  *GFX_GOL_RoundDialCreate(uint16_t ID, uint16_t x, uint16_t y, uint16_t radius,
*						uint16_t state, uint16_t res, uint16_t value, uint16_t max,
*						GFX_GOL_OBJ_SCHEME *pScheme);
*
* Summary: This function creates a ROUNDDIAL object with the parameters given.
*
*
* Description: It automatically attaches the new object into a global linked list of
*			objects and returns the address of the object.
*
* PreCondition: none
*
* Input: ID - Unique user defined ID for the object instance.
*        x - Location of the center of the dial in the x coordinate.
*        y - Location of the center of the dial in the y coordinate.
* 		 radius - Defines the radius of the dial. 
*        state - Sets the initial state of the object.
*        res - Sets the resolution of the dial when rotating clockwise or
*			   counter clockwise.
*        value - Sets the initial value of the dial.
*        max - Sets the maximum value of the dial.
*        pScheme - Pointer to the style scheme used.
*
* Returns: Returns the pointer to the object created.
*
* Example:
*   <CODE> 
*	GFX_GOL_OBJ_SCHEME *pScheme;
*	GFX_GOL_ROUNDDIAL *pDial;
*	uint16_t state;
*	
*		pScheme = GFX_GOL_SchemeCreate();
*		state = GFX_GOL_ROUNDDIAL_DRAW;
*
*		// creates a dial at (50,50) x,y location, with an initial value
*		// of 50, a resolution of 2 and maximum value of 100.
*		pDial = GFX_GOL_RoundDial_Create(1,50,50,25,118,0, state, 2, 50, 100, pScheme);
*		// check if dial was created
*		if (pDial == NULL)		
*		   return 0;
*
*		return 1;
*	</CODE> 
*
* Notes: none
*
********************************************************************/
GFX_GOL_ROUNDDIAL   *GFX_GOL_RoundDialCreate
            (
                uint16_t        ID,
                uint16_t      x,
                uint16_t       y,
                uint16_t       radius,
                uint16_t        state,
                uint16_t       res,
                uint16_t       value,
                uint16_t       max,
                GFX_GOL_OBJ_SCHEME  *pScheme
            );

/*********************************************************************
* Function: GFX_GOL_RoundDailActionGet(void *pObj, GFX_GOL_MESSAGE *pMsg)
*
* Overview: This function evaluates the message from a user if the 
*			message will affect the object or not. The table below enumerates the translated 
*			messages for each event of the touch screen inputs.
*
*	<TABLE>
*    	Translated Message      Input Source  Events        Description
*     	#####################   ############  ######        ###########
*     	RD_MSG_CLOCKWISE        Touch Screen  EVENT_MOVE	If events occurs and the x,y position falls in the face of the Dial and moving in the clockwise rotation.
*		RD_MSG_CTR_CLOCKWISE    Touch Screen  EVENT_MOVE	If events occurs and the x,y position falls in the face of the Dial and moving in the counter clockwise rotation.     					      			   
*		OBJ_MSG_INVALID		    Any		      Any			If the message did not affect the object.							 
*	</TABLE>
*
* PreCondition: none
*
* Input: pDia  - The pointer to the object where the message will be
*				 evaluated to check if the message will affect the object.
*        pMsg  - Pointer to the message struct containing the message from 
*        		 the user interface.
*
* Output: Returns the translated message depending on the received GOL message:
*		  - RD_MSG_CLOCKWISE – Dial is moved in a clockwise direction.
*         - RD_MSG_CTR_CLOCKWISE – Dial is moved in a counter clockwise direction.
*         - GFX_GOL_MSG_INVALID – Dial is not affected
*
* Example:
*   <CODE> 
*	void MyGOLMsg(GFX_GOL_MESSAGE *pMsg){
*
*		GFX_OBJ_HEADER *pCurrentObj;
*		uint16_t objMsg;
*			
*		if(pMsg->event == EVENT_INVALID)
*			return;
*		pCurrentObj = GFX_OBJ_ListGet();
*		
*		while(pCurrentObj != NULL){
*			// Process only ROUNDDIAL
*			if(!GFX_OBJ_IsUpdatePending(pCurrentObj)){
*				switch(pCurrentObj->type){
*					case OBJ_ROUNDIAL:
*						objMsg = RdiaTranslateMsg((ROUNDDIAL*)pCurrentObj, pMsg);
*						if(objMsg == OBJ_MSG_INVALID)
*							break;
*						if(GFX_GOL_MESSAGECallback(objMsg,pCurrentObj,pMsg))
*							RdiaMsgDefault(objMsg,(ROUNDDIAL*)pCurrentObj);
*						break;
*					default: break;	
*				}
*			}
*		}
*		pCurrentObj = pCurrentObj->pNxtObj;
*	}
*	</CODE> 
*
* Side Effects: none
*
********************************************************************/
uint16_t        GFX_GOL_RoundDailActionGet(void *pObj, GFX_GOL_MESSAGE *pMsg);

/*********************************************************************
* Function: GFX_GOL_RoundDailActionSet(uint16_t translatedMsg, void *pObj, GFX_GOL_MESSAGE* pMsg)
*
* Overview: This function performs the actual state change 
*			based on the translated message given. The following state changes 
*			are supported:
*	<TABLE>
*    	Translated Message   	Input Source  	Set/Clear State Bit		Description
*     	##################   	############  	######     				###########
*     	RD_MSG_CLOCKWISE	 	Touch Screen	Set GFX_GOL_ROUNDDIAL_ROT_CW,		Dial will be redrawn with clockwise update.
*										    	 Set GFX_GOL_ROUNDDIAL_DRAW
*		RD_MSG_CTR_CLOCKWISE 	Touch Screen  	Set GFX_GOL_ROUNDDIAL_ROT_CCW,		Dial will be redrawn with counter clockwise update.
*										    	 Set GFX_GOL_ROUNDDIAL_DRAW
*	</TABLE>
*
* PreCondition: none
*
* Input: translatedMsg - The translated message
*        pDia          - The pointer to the object whose state will be modified
*        pMsg          - The pointer to the GOL message
*        
* Output: none
*
* Example:
*	See RdiaTranslateMsg() example.
*
* Side Effects: none
*
********************************************************************/
void        GFX_GOL_RoundDailActionSet(uint16_t translatedMsg, void *pObj, GFX_GOL_MESSAGE *pMsg);

/*********************************************************************
* Macros:  GFX_GOL_RoundDialValueGet(pDia)
*
* Summary: Returns the current dial value. Value is always
*          in the 0-max range inclusive.
*
* Description:
*
* PreCondition: none
*
* Input: pDia - Pointer to the object.
*
* Returns: Returns the current value of the dial.
*
* Example:
*   <CODE> 
*	uint16_t currVal;
*	GFX_GOL_ROUNDDIAL *pDia;
*
*		// assuming pDia is initialized to an existing dial Object
*		currVal = GFX_GOL_RoundDial_ValGet(pDia);
*	</CODE> 
*
* Notes: none
*
********************************************************************/
    #define GFX_GOL_RoundDialValueGet(pDia)    (pDia)->value

/*********************************************************************
* Macros:  GFX_GOL_RoundDialValueSet(pDia, newVal)
*
* Summary: Sets the value to the given new value. Value set must be in 0-max
*	   range inclusive.
*
* Description:
*
* PreCondition: none
*
* Input: pDia - Pointer to the object. 
*	 newVal - New dial value.
*
* Returns: none
*
* Example:
*   <CODE> 
*	uint16_t updatedVal;
*	GFX_GOL_ROUNDDIAL *pDia;
*
*		// assuming pDia is initialized to an existing dial Object
*		// assume GetInput() is a function that retrieves source data
*		updatedVal = GetInput();
*		GFX_GOL_RoundDialValueSet(pDia, updatedVal);
*	</CODE> 
*
* Notes: none
*
********************************************************************/
    #define GFX_GOL_RoundDialValueSet(pDia, newVal)    (pDia)->value = newVal

/*********************************************************************
* Macros:  GFX_GOL_RoundDialValueIncrement(pDia)
*
* Summary: Used to directly increment the value. The delta
*           change used is the resolution setting (res).
*
* Description:
*
* PreCondition: none
*
* Input: pDia - Pointer to the object.
*
* Returns: none
*
* Example:
*   <CODE> 
*	uint16_t updatedVal, prevVal;
*	GFX_GOL_ROUNDDIAL *pDia;
*
*		// assuming pDia is initialized to an existing dial Object
*		// assume GetInput() is a function that retrieves source data
*		prevVal = GFX_GOL_RoundDial_ValGet(pDia);
*		updatedVal = GetInput();
*		if (updatedVal > prevVal)
*			GFX_GOL_RoundDial_ValInc(pDia);
*		if (updatedVal < prevVal)
*			GFX_GOL_RoundDial_ValDec(pDia);
*	</CODE> 
*
* Returns: none
*
********************************************************************/
    #define GFX_GOL_RoundDialValueIncrement(pDia)    GFX_GOL_RoundDial_ValSet(pDia, (pDia->val + pDia->res))

/*********************************************************************
* Macros:  GFX_GOL_RoundDialValueDecrement(pDia)
*
* Summary: Used to directly decrement the value. The delta
*           change used is the resolution setting (res).
*
* Description:
*
* PreCondition: none
*
* Input: pDia - Pointer to the object.
*
* Returns: none
*
* Example:
*   Refer to GFX_GOL_RoundDialValueIncrement() example.
*
* Notes: none
*
********************************************************************/
    #define GFX_GOL_RoundDialValueDecrement(pDia)    GFX_GOL_RoundDial_ValSet(pDia, (pDia->pos - pDia->res))

/*********************************************************************
* Function: uint16_t GFX_GOL_RoundDialDraw(void *pObj)
*
* Overview: This function renders the object on the screen using 
* 			the current parameter settings. Location of the object is 
*			determined by the center (x,y) postion and the radius parameters. 
*			The colors used are dependent on the state of the object. 
*			
*			When rendering objects of the same type, each object 
*			must be rendered completely before the rendering of the 
*			next object is started. This is to avoid incomplete 
*			object rendering.
*
* PreCondition: Object must be created before this function is called.
*
* Input: pDia - Pointer to the object 
*
* Output: Returns the status of the drawing
*		  - 1 - If the rendering was completed and 
*		  - 0 - If the rendering is not yet finished. 
*
* Side Effects: none
*
********************************************************************/
uint16_t GFX_GOL_RoundDialDraw(void *pObj);
#endif // _ROUNDDIAL_H
