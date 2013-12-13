/*******************************************************************************
  USART Peripheral Library Template Implementation

  File Name:
    usart_Transmitter_Default.h

  Summary:
    USART PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : Transmitter
    and its Variant : Default
    For following APIs :
        PLIB_USART_ExistsTransmitter
        PLIB_USART_TransmitterByteSend

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

#ifndef _USART_TRANSMITTER_DEFAULT_H
#define _USART_TRANSMITTER_DEFAULT_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    _USART_TRANSMITTER_SEND_VREG(index)

  MASKs: 
    _USART_TRANSMITTER_SEND_MASK(index)

  POSs: 
    _USART_TRANSMITTER_SEND_POS(index)

  LENs: 
    _USART_TRANSMITTER_SEND_LEN(index)

*/


//******************************************************************************
/* Function :  USART_ExistsTransmitter_Default

  Summary:
    Implements Default variant of PLIB_USART_ExistsTransmitter

  Description:
    This template implements the Default variant of the PLIB_USART_ExistsTransmitter function.
*/

PLIB_TEMPLATE bool USART_ExistsTransmitter_Default( USART_MODULE_ID index )
{
    return true;
}


//******************************************************************************
/* Function :  USART_TransmitterByteSend_Default

  Summary:
    Implements Default variant of PLIB_USART_TransmitterByteSend 

  Description:
    This template implements the Default variant of the PLIB_USART_TransmitterByteSend function.
*/

PLIB_TEMPLATE void USART_TransmitterByteSend_Default( USART_MODULE_ID index , int8_t data )
{
    _SFR_FIELD_WRITE(_USART_TRANSMITTER_SEND_VREG(index),
                         _USART_TRANSMITTER_SEND_MASK(index),
                         _USART_TRANSMITTER_SEND_POS(index) ,
                         data);
}


#endif /*_USART_TRANSMITTER_DEFAULT_H*/

/******************************************************************************
 End of File
*/

