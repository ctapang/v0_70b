/*******************************************************************************
  SPI Peripheral Library Template Implementation

  File Name:
    spi_FrameSyncPulseDirection_Default.h

  Summary:
    SPI PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : FrameSyncPulseDirection
    and its Variant : Default
    For following APIs :
        PLIB_SPI_FrameSyncPulseDirectionSelect
        PLIB_SPI_ExistsFrameSyncPulseDirection

*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2012 released Microchip Technology Inc.  All rights reserved.

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

#ifndef _SPI_FRAMESYNCPULSEDIRECTION_DEFAULT_H
#define _SPI_FRAMESYNCPULSEDIRECTION_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _SPI_FRAME_SYNC_PULSE_DIRECTION_VREG(index)

  MASKs: 
    _SPI_FRAME_SYNC_PULSE_DIRECTION_MASK(index)

  POSs: 
    _SPI_FRAME_SYNC_PULSE_DIRECTION_POS(index)

  LENs: 
    _SPI_FRAME_SYNC_PULSE_DIRECTION_LEN(index)

*/


//******************************************************************************
/* Function :  SPI_FrameSyncPulseDirectionSelect_Default

  Summary:
    Implements Default variant of PLIB_SPI_FrameSyncPulseDirectionSelect 

  Description:
    This template implements the Default variant of the PLIB_SPI_FrameSyncPulseDirectionSelect function.
*/

PLIB_TEMPLATE void SPI_FrameSyncPulseDirectionSelect_Default( SPI_MODULE_ID index , SPI_FRAME_PULSE_DIRECTION direction )
{
    switch( direction )
    {
        case SPI_FRAME_PULSE_DIRECTION_INPUT:
                _SFR_BIT_SET( _SPI_FRAME_SYNC_PULSE_DIRECTION_VREG( index ),
                              _SPI_FRAME_SYNC_PULSE_DIRECTION_POS( index ) );
            break;
        case SPI_FRAME_PULSE_DIRECTION_OUTPUT:
                _SFR_BIT_CLEAR( _SPI_FRAME_SYNC_PULSE_DIRECTION_VREG( index ),
                                _SPI_FRAME_SYNC_PULSE_DIRECTION_POS( index ) );
            break;
        default:
            break;
    }
}


//******************************************************************************
/* Function :  SPI_ExistsFrameSyncPulseDirection_Default

  Summary:
    Implements Default variant of PLIB_SPI_ExistsFrameSyncPulseDirection

  Description:
    This template implements the Default variant of the PLIB_SPI_ExistsFrameSyncPulseDirection function.
*/

PLIB_TEMPLATE bool SPI_ExistsFrameSyncPulseDirection_Default( SPI_MODULE_ID index )
{
    return true;
}


#endif /*_SPI_FRAMESYNCPULSEDIRECTION_DEFAULT_H*/

/******************************************************************************
 End of File
*/

