/*******************************************************************************
  Processor Selector File for the USART

  Company:
    Microchip Technology Incorporated

  File Name:
    processor.h

  Summary:
    Selects the appropriate header for the part family

  Description:
    This file selects the appropriate header for the part family
 *******************************************************************************/

// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END

#ifndef _USART_PROCESSOR_H    // Guards against multiple inclusion
#define _USART_PROCESSOR_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************
/*  This section lists the other files that are included in this file.
 */

#include <stdint.h>
#include <stdbool.h>

#if defined(__PIC16F__)
    #include "usart_p16fxxxx.h"

#elif defined(__18CXX)
    #include "usart_p18fxxxx.h"

#elif defined(_PIC18)
    #include "usart_p18fxxxx.h"

#elif defined(__PIC24F__)
    #include "usart_p24fxxxx.h"

#elif defined(__PIC24H__)
    #include "usart_p24hxxxx.h"

#elif defined(__dsPIC30F__)
    #include "usart_p30fxxxx.h"

#elif defined(__dsPIC33F__)
    #include "usart_p33fxxxx.h"

#elif defined(__PIC32MX__)
    #include "usart_p32mxxxxx.h"

#elif defined(__PIC32MZ__)
    #include "usart_p32mzxxxx.h"

#else

    #error "No Processor Family specified"

#endif //

#endif // _USART_PROCESSOR_H

/*******************************************************************************
 End of File
 */
