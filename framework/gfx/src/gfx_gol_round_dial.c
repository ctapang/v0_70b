/*******************************************************************************
  Graphics Library Implementation

  Company:
    Microchip Technology Inc.

  FileName:
    gfx_gol_round_dial.c

  Summary:
    This implements the round dial object of the GOL.

  Description:
    Refer to Microchip Graphics Library for complete documentation of the
    RoundDial Object.
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


#include "gfx/gfx_gol_round_dial.h"

#include <math.h>

/*********************************************************************
* Function: GFX_GOL_ROUNDDIAL  *GFX_GOL_RoundDialCreate(uint16_t ID, uint16_t x, uint16_t y, uint16_t radius,
*						uint16_t state, uint16_t res, uint16_t value, uint16_t max,
*						GFX_GOL_SCHEME *pScheme)
*
*
* Notes: Creates a ROUNDDIAL object and adds it to the current active list.
*        If the creation is successful, the pointer to the created Object 
*        is returned. If not successful, NULL is returned.
*
********************************************************************/
GFX_GOL_ROUNDDIAL *GFX_GOL_RoundDialCreate
(
    uint16_t    ID,
    uint16_t       x,
    uint16_t       y,
    uint16_t       radius,
    uint16_t    state,
    uint16_t       res,
    uint16_t       value,
    uint16_t       max,
    GFX_GOL_SCHEME  *pScheme
)
{
    GFX_GOL_ROUNDDIAL   *pDia = NULL;

    pDia = (GFX_GOL_ROUNDDIAL *)GFX_malloc(sizeof(GFX_GOL_ROUNDDIAL));
    if(pDia == NULL)
        return (NULL);

    //pDia->hdr.instance = instance;
    pDia->hdr.ID = ID;              // unique id assigned for referencing
    pDia->hdr.pNxtObj = NULL;       // initialize pointer to NULL
    pDia->hdr.type = GFX_GOL_ROUNDDAIL_TYPE; // set object type
    pDia->xCenter = x;				// x coordinate of center
    pDia->yCenter = y;				// y coordinate of center
    pDia->radius = radius;			// radius of dial
    pDia->res = res;
    pDia->value = value;
    pDia->max = max;
    pDia->hdr.state = state;        // state
    #ifdef USE_KEYBOARD
    pDia->vAngle = 0;				// initial position
    #endif
    pDia->curr_xPos = x + radius * 2 / 3;
    pDia->curr_yPos = y;
    pDia->hdr.DrawObj = GFX_GOL_RoundDialDraw;				// draw function
    pDia->hdr.actionGet = GFX_GOL_RoundDailActionGet;		// message function
    pDia->hdr.actionSet = GFX_GOL_RoundDailActionSet;	// default message function
    pDia->hdr.FreeObj = NULL;					// free function

    pDia->hdr.left = x - radius;    // left position
    pDia->hdr.top = y - radius;     // top position
    pDia->hdr.right = x + radius;   // right position
    pDia->hdr.bottom = y + radius;  // bottom position

    // Set the color scheme to be used
    if(pScheme == NULL)
        pDia->hdr.pGolScheme = _pDefaultGolScheme;
    else
        pDia->hdr.pGolScheme = (GFX_GOL_SCHEME *)pScheme;

    GFX_GOL_ObjectAdd((GFX_GOL_OBJ_HEADER *)pDia);

    return (pDia);
}

/*********************************************************************
* Function: GFX_GOL_RoundDailActionSet(uint16_t translatedMsg, void *pObj, GFX_GOL_MESSAGE* pMsg)
*
*
* Notes: This the default operation to change the state of the dial.
*		 Called inside GFX_GOL_Message() when GFX_GOL_MessageCallback() returns a 1.
*
********************************************************************/
void GFX_GOL_RoundDailActionSet(uint16_t translatedMsg, void *pObj, GFX_GOL_MESSAGE *pMsg)
{
    GFX_GOL_ROUNDDIAL *pDia;

    pDia = (GFX_GOL_ROUNDDIAL *)pObj;

    switch(translatedMsg)
    {
        case GFX_GOL_ROUNDDIAL_MSG_CLOCKWISE:      GFX_GOL_ObjectStateSet(pDia, GFX_GOL_ROUNDDIAL_ROT_CW | GFX_GOL_ROUNDDIAL_DRAW);    // set rotate left and redraw
            break;
        case GFX_GOL_ROUNDDIAL_MSG_CTR_CLOCKWISE:  GFX_GOL_ObjectStateSet(pDia, GFX_GOL_ROUNDDIAL_ROT_CCW | GFX_GOL_ROUNDDIAL_DRAW);   // set rotate right and redraw
            break;
    }
}

/*********************************************************************
* Function: short RdiaCosine(short v)
*
*
* Notes: Returns the cosine of the dial position.
*
********************************************************************/
    #ifdef USE_KEYBOARD

// Dimple position table for 15 degree increments
short   _cosine[GFX_GOL_ROUNDDIAL_QUADRANT_POSITIONS] = { 100, 97, 87, 71, 50, 26};

/* */
short RdiaCosine(short v)
{
    if(v >= GFX_GOL_ROUNDDIAL_QUADRANT_POSITIONS * 3)
    {
        v -= GFX_GOL_ROUNDDIAL_QUADRANT_POSITIONS * 3;
        return (_cosine[GFX_GOL_ROUNDDIAL_QUADRANT_POSITIONS - 1 - v]);
    }
    else if(v >= GFX_GOL_ROUNDDIAL_QUADRANT_POSITIONS * 2)
    {
        v -= GFX_GOL_ROUNDDIAL_QUADRANT_POSITIONS * 2;
        return (-(_cosine[v]));
    }
    else if(v >= GFX_GOL_ROUNDDIAL_QUADRANT_POSITIONS)
    {
        v -= GFX_GOL_ROUNDDIAL_QUADRANT_POSITIONS;
        return (-(_cosine[GFX_GOL_ROUNDDIAL_QUADRANT_POSITIONS - 1 - v]));
    }
    else
    {
        return (_cosine[v]);
    }
}

/*********************************************************************
* Function: short RdiaSine(short v)
*
*
* Notes: Returns the sine of the dial position.
*
********************************************************************/
short RdiaSine(short v)
{
    if(v >= GFX_GOL_ROUNDDIAL_QUADRANT_POSITIONS * 3)
    {
        v -= GFX_GOL_ROUNDDIAL_QUADRANT_POSITIONS * 3;
        return (-(_cosine[v]));
    }
    else if(v >= GFX_GOL_ROUNDDIAL_QUADRANT_POSITIONS * 2)
    {
        v -= GFX_GOL_ROUNDDIAL_QUADRANT_POSITIONS * 2;
        return (-(_cosine[GFX_GOL_ROUNDDIAL_QUADRANT_POSITIONS - 1 - v]));
    }
    else if(v >= GFX_GOL_ROUNDDIAL_QUADRANT_POSITIONS)
    {
        v -= GFX_GOL_ROUNDDIAL_QUADRANT_POSITIONS;
        return (_cosine[v]);
    }
    else
    {
        return (_cosine[GFX_GOL_ROUNDDIAL_QUADRANT_POSITIONS - 1 - v]);
    }
}
    #endif

/*********************************************************************
* Function: uint16_t RdiaTranslateMsg(void *pObj, GFX_GOL_MESSAGE *pMsg)
*
*
* Notes: Evaluates the message if the object will be affected by the 
*		 message or not.
*
********************************************************************/
uint16_t GFX_GOL_RoundDailActionGet(void *pObj, GFX_GOL_MESSAGE *pMsg)
{
    GFX_GOL_ROUNDDIAL *pDia;
    uint16_t   messageID = GFX_GOL_OBJECT_ACTION_INVALID;

    pDia = (GFX_GOL_ROUNDDIAL *)pObj;

        #ifdef USE_TOUCHSCREEN

    short           touchRadius, touchX, touchY;
    static short    prevX = -1, prevY = -1;

    // Evaluate if the message is for the button
    // Check if disabled first
    if(GFX_GOL_ObjectStateGet(pDia, GFX_GOL_ROUNDDIAL_DISABLED))
        return (GFX_GOL_OBJECT_ACTION_INVALID);

    if((pMsg->type == TYPE_TOUCHSCREEN) && (pMsg->uiEvent == EVENT_MOVE))
    {

        // Check if it falls in the dial's face
        // to check this the x,y position must be within the circle
        // (x - xCenter)^2 + (y - yCenter)^2 = r^2  where x and y are the points
        // to test, the distance between x,y position of touch and center must be
        // greater than or equal to the radius of the dial
        if
        (
            ((pDia->xCenter - pDia->radius) < pMsg->param1) &&
            ((pDia->xCenter + pDia->radius) > pMsg->param1) &&
            ((pDia->yCenter - pDia->radius) < pMsg->param2) &&
            ((pDia->yCenter + pDia->radius) > pMsg->param2)
        )
        {

            // first get the radius of the touch point
            touchX = pMsg->param1 - pDia->xCenter;
            touchY = pMsg->param2 - pDia->yCenter;
            touchRadius = sqrt(touchX * touchX + touchY * touchY);

            if(touchRadius <= pDia->radius)
            {

                // difference of 3 is used to remove jitter caused by noise or sensitivity of the touchscreen
                if((abs(prevX - pMsg->param1) > 3) || (abs(prevY - pMsg->param2) > 3))
                {

                    // The first MOVE event is used to record the current position only. The second MOVE event
                    // will be used together with the previous MOVE and determine if the movement is in the
                    // clockwise or counter clockwise direction.
                    if((prevX == -1) || (prevY == -1))
                    {
                        prevX = pMsg->param1;
                        prevY = pMsg->param2;
                        messageID = GFX_GOL_OBJECT_ACTION_INVALID;
                    }
                    else
                    {

                        // this makes the sampling area a ring where the max radius is the dial radius
                        // and min radius is 5
                        if(touchRadius > 5)
                        {
                            pDia->new_xPos = (pDia->radius * 2 / 3) * (pMsg->param1 - pDia->xCenter) / touchRadius;
                            pDia->new_yPos = (pDia->radius * 2 / 3) * (pMsg->param2 - pDia->yCenter) / touchRadius;

                            // check if moving in clockwise direction or counter clockwise direction
                            if((pDia->xCenter >= pMsg->param1) && (pDia->yCenter > pMsg->param2))
                            {
                                if((prevX < pMsg->param1) && (prevY >= pMsg->param2))
                                    messageID = GFX_GOL_ROUNDDIAL_MSG_CLOCKWISE;
                                else if((prevX >= pMsg->param1) && (prevY < pMsg->param2))
                                    messageID = GFX_GOL_ROUNDDIAL_MSG_CTR_CLOCKWISE;
                            }

                            if((pDia->xCenter < pMsg->param1) && (pDia->yCenter > pMsg->param2))
                            {
                                if((prevX < pMsg->param1) && (prevY <= pMsg->param2))
                                    messageID = GFX_GOL_ROUNDDIAL_MSG_CLOCKWISE;
                                else if((prevX >= pMsg->param1) && (prevY > pMsg->param2))
                                    messageID = GFX_GOL_ROUNDDIAL_MSG_CTR_CLOCKWISE;
                            }

                            if((pDia->xCenter < pMsg->param1) && (pDia->yCenter <= pMsg->param2))
                            {
                                if((prevX > pMsg->param1) && (prevY <= pMsg->param2))
                                    messageID = GFX_GOL_ROUNDDIAL_MSG_CLOCKWISE;
                                else if((prevX <= pMsg->param1) && (prevY > pMsg->param2))
                                    messageID = GFX_GOL_ROUNDDIAL_MSG_CTR_CLOCKWISE;
                            }

                            if((pDia->xCenter >= pMsg->param1) && (pDia->yCenter <= pMsg->param2))
                            {
                                if((prevX > pMsg->param1) && (prevY >= pMsg->param2))
                                    messageID = GFX_GOL_ROUNDDIAL_MSG_CLOCKWISE;
                                else if((prevX <= pMsg->param1) && (prevY < pMsg->param2))
                                    messageID = GFX_GOL_ROUNDDIAL_MSG_CTR_CLOCKWISE;
                            }
                        }
                        else
                            messageID = GFX_GOL_OBJECT_ACTION_INVALID;

                        prevX = pMsg->param1;
                        prevY = pMsg->param2;
                    }
                }
                else
                    messageID = GFX_GOL_OBJECT_ACTION_INVALID;

                // determine the movement clockwise or counter clockwise
                // this is important to update the value variable
                return (messageID);
            }
            else
            {
                prevX = -1;
                prevY = -1;
            }
        }
    }

        #endif
       #ifdef USE_KEYBOARD

    short   newValue;

    // Evaluate if the message is for the Dial
    // Check if disabled first
    if(GFX_GOL_ObjectStateGet(pDia, GFX_GOL_ROUNDDIAL_DISABLED))
        return (OBJ_MSG_INVALID);

    if((pMsg->type == TYPE_KEYBOARD) && ((uint16_t)pMsg->param1 == pDia->hdr.ID) && (pMsg->uiEvent == EVENT_KEYSCAN))
    {
        if(pMsg->param2 == SCAN_RIGHT_PRESSED)
        {
            newValue = pDia->value + pDia->res;
            if(newValue > pDia->max)
            {
                newValue -= (pDia->max + 1);
            }

            pDia->vAngle += 1;
            messageID = GFX_GOL_ROUNDDIAL_MSG_CLOCKWISE;
        }

        if(pMsg->param2 == SCAN_LEFT_PRESSED)
        {
            newValue = pDia->value - pDia->res;
            if(newValue < 0)
            {
                newValue += (pDia->max + 1);
            }

            pDia->vAngle -= 1;
            messageID = GFX_GOL_ROUNDDIAL_MSG_CTR_CLOCKWISE;
        }
        
        if (pDia->vAngle > (GFX_GOL_ROUNDDIAL_MAX_POSITIONS - 1))
           	pDia->vAngle = 0;
        else if (pDia->vAngle < 0)
           	pDia->vAngle = (GFX_GOL_ROUNDDIAL_MAX_POSITIONS - 1);
           	
        pDia->new_xPos = pDia->radius * 2 * RdiaCosine(pDia->vAngle) / 100 / 3;
        pDia->new_yPos = pDia->radius * 2 * RdiaSine(pDia->vAngle) / 100 / 3;
    }

        #endif
    return (messageID);
}

/*********************************************************************
* Function: uint16_t RoundDialDraw(void *pObj)
*
*
* Notes: This is the state machine to draw the dial.
*
********************************************************************/
uint16_t GFX_GOL_RoundDialDraw(void *pObj)
{
    typedef enum
    {
        REMOVE,
        RND_PANEL_DRAW,
        RND_PANEL_TASK,
        ERASE_POSITION,
        DRAW_POSITION,
        DRAW_POSITION_1,
        DRAW_POSITION_2,
        WAIT
    } GFX_GOL_ROUNDDIAL_DRAW_STATES;

    static GFX_GOL_ROUNDDIAL_DRAW_STATES state = REMOVE;
    static short dimpleRadius;
    static GFX_COLOR faceClr;
    static GFX_STATUS index = GFX_STATUS_FAILURE;

    GFX_GOL_ROUNDDIAL *pDia;

    pDia = (GFX_GOL_ROUNDDIAL *)pObj;

    while(1)
    {  
        switch(state)
        {
            case REMOVE:

                if(GFX_GOL_ObjectStateGet(pDia, GFX_GOL_ROUNDDIAL_HIDE))
                {   // Hide the dial (remove from screen)
                    GFX_ColorSet(pDia->hdr.pGolScheme->CommonBkColor);
                    if
                    (
                        GFX_RectangleFillDraw
                            (
                                pDia->xCenter - pDia->radius,
                                pDia->yCenter - pDia->radius,
                                pDia->xCenter + pDia->radius,
                                pDia->yCenter + pDia->radius
                            ) == GFX_STATUS_FAILURE
                    )
                    return (GFX_STATUS_FAILURE);

                    return (GFX_STATUS_SUCCESS);
                }
    
                dimpleRadius = (pDia->radius >> 3) + 1;
//kj
                if(GFX_GOL_ObjectStateGet(pDia, GFX_GOL_ROUNDDIAL_ROT_CCW | GFX_GOL_ROUNDDIAL_ROT_CW))
                {
                    GFX_ColorSet(pDia->hdr.pGolScheme->Color0);
                    state = ERASE_POSITION;
                    break;
                }
    
                state = RND_PANEL_DRAW;
    
            case RND_PANEL_DRAW:
                if(!GFX_GOL_ObjectStateGet(pDia, GFX_GOL_ROUNDDIAL_DISABLED))
                {
                    faceClr = pDia->hdr.pGolScheme->Color0;
                }
                else
                {
                    faceClr = pDia->hdr.pGolScheme->ColorDisabled;
                }
    
                GFX_LineTypeSet(SOLID);

                GFX_GOL_PanelParameterSet
                (
                    
                    pDia->xCenter,
                    pDia->yCenter,
                    pDia->xCenter,
                    pDia->yCenter,
                    pDia->radius,
                    faceClr,
                    pDia->hdr.pGolScheme->EmbossLtColor,
                    pDia->hdr.pGolScheme->EmbossDkColor,
                    NULL,
                    GFX_FILL_STYLE_COLOR,
                    GFX_GOL_EMBOSS_SIZE
                );
                state = RND_PANEL_TASK;
    
            case RND_PANEL_TASK:
                if(GFX_GOL_PanelDraw()==GFX_STATUS_FAILURE)
                {
                    return (GFX_STATUS_FAILURE);
                }
    
                state = DRAW_POSITION;
                break;
    
            case ERASE_POSITION:
                if 
                (
                    GFX_RectangleFillDraw
                        (   
                            pDia->curr_xPos - dimpleRadius,
                            pDia->curr_yPos - dimpleRadius,
                            pDia->curr_xPos + dimpleRadius,
                            pDia->curr_yPos + dimpleRadius
                        ) == GFX_STATUS_FAILURE
                ) return (GFX_STATUS_FAILURE);
    
                // determine if the value will increment or decrement
                if(GFX_GOL_ObjectStateGet(pDia, GFX_GOL_ROUNDDIAL_ROT_CW))
                {
                    pDia->value = pDia->value + pDia->res;
                    if(pDia->value > pDia->max)
                    {
                        pDia->value -= (pDia->max + 1);
                    }
                }
                else if(GFX_GOL_ObjectStateGet(pDia, GFX_GOL_ROUNDDIAL_ROT_CCW))
                {
                    pDia->value = pDia->value - pDia->res;
                    if(pDia->value < 0)
                    {
                        pDia->value += (pDia->max + 1);
                    }
                }
    
                // else do not update counter yet
                // locate the new position of the dimple	
                pDia->curr_xPos = pDia->xCenter + pDia->new_xPos;
                pDia->curr_yPos = pDia->yCenter + pDia->new_yPos;
    
                GFX_GOL_ObjectStateClear(pDia, GFX_GOL_ROUNDDIAL_ROT_CW | GFX_GOL_ROUNDDIAL_ROT_CCW); // make sure this is cleared to avoid
    
                // unwanted redraw
                state = DRAW_POSITION;
    
            case DRAW_POSITION:

                GFX_ColorSet(pDia->hdr.pGolScheme->EmbossLtColor);
                GFX_LineTypeSet(SOLID);
                state = DRAW_POSITION_1;

            case DRAW_POSITION_1:
                if(GFX_CircleFillDraw(pDia->curr_xPos, pDia->curr_yPos, dimpleRadius) == GFX_STATUS_FAILURE)
                    return (GFX_STATUS_FAILURE);
                GFX_ColorSet(pDia->hdr.pGolScheme->EmbossDkColor);
                state = DRAW_POSITION_2;

            case DRAW_POSITION_2:
                index = GFX_CircleFillDraw(pDia->curr_xPos, pDia->curr_yPos, dimpleRadius - 1);
                if(index == GFX_STATUS_FAILURE)
                {
                    return (GFX_STATUS_FAILURE);
                }
            state = WAIT;
            case WAIT:
//            if(index->type != DONE) // Wait until renderring is complete
//            {
//                 return(GFX_STATUS_FAILURE);
//            }
                state = REMOVE;
                return (GFX_STATUS_SUCCESS);

        } // end of switch()
    } // end of while(1)
}
