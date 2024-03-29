/*******************************************************************************
 System Interrupt Source File

  File Name:
    sys_int.c

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
#include "driver/spi/drv_spi.h"

//void __ISR (_TIMER_1_VECTOR) _Timer1InterruptHandler(void)
//{
//    sTickNode   *pTick;
//
//    _SystemTickCount ++;
//
//    for(pTick=_tickHead; pTick!=0; pTick=pTick->next)
//    {
//        if(pTick->rate != 0)
//        {
//            if(--pTick->currCnt==0)
//            {
//                pTick->currCnt=pTick->rate;
//                (*pTick->tFunc)(_SystemTickCount);
//            }
//        }
//    }
//    SYS_INT_SourceStatusClear(INT_SOURCE_TIMER_1);
//}

bool SYS_INT_SourceRestore(INT_SOURCE src)
{
    bool isEnabled;

    isEnabled = SYS_INT_SourceDisable(src);

    if(isEnabled)
    {   
        SYS_INT_SourceEnable(src);
    }

    return isEnabled;
}

#if defined (SYS_FS_FILESYSTEM_FAT)
void __ISR ( _SPI2_RX_VECTOR,ipl4 ) _InterruptHandler_SPI_RX_stub ( void )
{
    DRV_SPI_Tasks((SYS_MODULE_OBJ)appDrvObjects.drvSPIObject);
}

void __ISR ( _SPI2_TX_VECTOR,ipl4 ) _InterruptHandler_SPI_TX_stub ( void )
{
    DRV_SPI_Tasks((SYS_MODULE_OBJ)appDrvObjects.drvSPIObject);
}
#endif

/*******************************************************************************
 End of File
 */


