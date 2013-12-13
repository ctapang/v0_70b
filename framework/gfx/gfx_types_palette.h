/*****************************************************************************
 * FileName:        gfx_palette_types.h
 * Dependencies:    See Includes Section
 * Processor:       PIC24, PIC32
 * Compiler:       	XC16/XC32
 * Linker:          XC16/XC32
 * Company:         Microchip Technology Incorporated
 *
 *
 * Copyright � 2012 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).  
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 * OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 * BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
 * INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
 * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
 * OR OTHER SIMILAR COSTS.
 *
 *****************************************************************************/
#ifndef GFX_TYPES_PALETTE_H
    #define GFX_TYPES_PALETTE_H

/*****************************************************************************
 * SECTION: Includes
 *****************************************************************************/
#include <stdint.h>

/*********************************************************************
* Overview: Structure used for the palette entries. 
*           - For TFT: color is defined as 5-6-5 RGB format 
*             (5-bits for RED, 6-bits for GREEN and 5-bits for BLUE.
*           - For Monochrome: 4 bits are used to represent the luma.
*
*********************************************************************/
typedef union __attribute__ ((packed))
{
    uint16_t    value;                // a 16-bit value representing a color or palette entry
    struct __attribute__ ((packed))
    {
        uint16_t    r : 5;            // represents the RED component 
        uint16_t    g : 6;            // represents the GREEN component 
        uint16_t    b : 5;            // represents the BLUE component 
    } color;                          // color value in 5-6-5 RGB format

    struct __attribute__ ((packed))
    {
        uint16_t    reserved : 12;    // reserved, used as a filler 
        uint16_t    luma : 4;         // monochrome LUMA value
    } monochrome;                     // monochrome LUMA value

} GFX_PALETTE_ENTRY;

#endif  // GFX_TYPES_PALETTE_H
