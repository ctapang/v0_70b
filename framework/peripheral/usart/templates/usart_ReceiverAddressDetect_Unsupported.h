/*******************************************************************************
  USART Peripheral Library Template Implementation

  File Name:
    usart_ReceiverAddressDetect_Unsupported.h

  Summary:
    USART PLIB Template Implementation

  Description:
    This header file contains template implementations
    For Feature : ReceiverAddressDetect
    and its Variant : Unsupported
    For following APIs :
        PLIB_USART_ExistsReceiverAddressDetect
        PLIB_USART_ReceiverAddressDetectEnable
        PLIB_USART_ReceiverAddressDetectDisable
        PLIB_USART_ReceiverAddressIsReceived

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

#ifndef _USART_RECEIVERADDRESSDETECT_UNSUPPORTED_H
#define _USART_RECEIVERADDRESSDETECT_UNSUPPORTED_H

//******************************************************************************
/* Routines available for accessing VREGS, MASKS, POS, LEN are 

  VREGs: 
    None.

  MASKs: 
    None.

  POSs: 
    None.

  LENs: 
    None.

*/


//******************************************************************************
/* Function :  USART_ExistsReceiverAddressDetect_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_USART_ExistsReceiverAddressDetect

  Description:
    This template implements the Unsupported variant of the PLIB_USART_ExistsReceiverAddressDetect function.
*/

PLIB_TEMPLATE bool USART_ExistsReceiverAddressDetect_Unsupported( USART_MODULE_ID index )
{
    return false;
}


//******************************************************************************
/* Function :  USART_ReceiverAddressDetectEnable_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_USART_ReceiverAddressDetectEnable 

  Description:
    This template implements the Unsupported variant of the PLIB_USART_ReceiverAddressDetectEnable function.
*/

PLIB_TEMPLATE void USART_ReceiverAddressDetectEnable_Unsupported( USART_MODULE_ID index )
{
    PLIB_ASSERT(false, "The device selected does not implement PLIB_USART_ReceiverAddressDetectEnable");
}


//******************************************************************************
/* Function :  USART_ReceiverAddressDetectDisable_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_USART_ReceiverAddressDetectDisable 

  Description:
    This template implements the Unsupported variant of the PLIB_USART_ReceiverAddressDetectDisable function.
*/

PLIB_TEMPLATE void USART_ReceiverAddressDetectDisable_Unsupported( USART_MODULE_ID index )
{
    PLIB_ASSERT(false, "The device selected does not implement PLIB_USART_ReceiverAddressDetectDisable");
}


//******************************************************************************
/* Function :  USART_ReceiverAddressIsReceived_Unsupported

  Summary:
    Implements Unsupported variant of PLIB_USART_ReceiverAddressIsReceived 

  Description:
    This template implements the Unsupported variant of the PLIB_USART_ReceiverAddressIsReceived function.
*/

PLIB_TEMPLATE bool USART_ReceiverAddressIsReceived_Unsupported( USART_MODULE_ID index )
{
    PLIB_ASSERT(false, "The device selected does not implement PLIB_USART_ReceiverAddressIsReceived");
}


#endif /*_USART_RECEIVERADDRESSDETECT_UNSUPPORTED_H*/

/******************************************************************************
 End of File
*/

