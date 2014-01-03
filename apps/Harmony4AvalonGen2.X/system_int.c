/*******************************************************************************
 System Interrupt Source File

  File Name:
    system_int.c

  Summary:
    Raw ISR definitions.

  Description:
    This file contains a definitions of the raw ISRs required to support the
    interrupt sub-system.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2011-2012 released Microchip Technology Inc.  All rights reserved.

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
// DOM-IGNORE-END

#include <xc.h>
#include <sys/attribs.h>
#include "app.h"

int _intCounter = 0;

void __attribute__((interrupt(ipl5), vector(_TIMER_3_VECTOR)))
Timer2Handler(void)
{
    _intCounter++;

    // call the driver tasks routine
    DRV_TMR_Tasks(appObject.TimerObjectHandle);
}

void __attribute__((interrupt(ipl3), vector(_SPI_2_VECTOR)))
SPI2_Transmit_Handler(void)
{
    // determine what the intettupt is for (3 possiblities)
    if (SYS_INT_SourceStatusGet(INT_SOURCE_SPI_2_TRANSMIT))
    {
        // SYS_INT_SourceStatusClear(INT_SOURCE_SPI_2_TRANSMIT);
        // FIXME: Reconfigure SS0 Select pin such that it is an input pin, then
        // physicslly connnect this pin to an output pin.
        //PLIB_PORTS_PinClear( PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_2);
        DRV_SPI_Tasks(appObject.spiConfig);
        //PLIB_PORTS_PinSet( PORTS_ID_0, PORT_CHANNEL_B, PORTS_BIT_POS_2);
    }
}

void __attribute__((interrupt(ipl3), vector(_SPI_1_VECTOR)))
SPI1_Receive_Handler(void)
{
    // determine what the intettupt is for (3 possiblities)
    if (SYS_INT_SourceStatusGet(INT_SOURCE_SPI_1_RECEIVE))
    {
        //SYS_INT_SourceStatusClear(INT_SOURCE_SPI_1_RECEIVE);
        DRV_SPI_Tasks(appObject.spiReport);
    }
}

void __attribute__((interrupt(ipl5)))
_DefaultInterrupt(void)
{
}


/*******************************************************************************
 End of File
 */


