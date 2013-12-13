/*******************************************************************************
  MRF24W SPI Driver

  FileName:  
    drv_wifi_spi.c  
  
  Summary:
    Module for Microchip TCP/IP Stack
    
  Description:

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

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>


#include "driver/spi/drv_spi.h"
#include "system/clk/sys_clk.h"
#include "system/int/sys_int.h"
#include "peripheral/dma/plib_dma.h"
#include <sys/attribs.h>



//#include "system/system_services.h"




static SYS_MODULE_OBJ              drvSPIObject;
static DRV_HANDLE                  drvSPIHandle;
static DRV_SPI_BUFFER_HANDLE spiBufferHandleTx, spiBufferHandleRx;

static DRV_SPI_INIT initConf_1 =
{
    .moduleInit.sys.powerState = SYS_MODULE_POWER_RUN_FULL,
    .spiId = SPI_ID_1,
    .spiMode = DRV_SPI_MODE_MASTER,
    .spiProtocolType = DRV_SPI_PROTOCOL_TYPE_STANDARD,
    .commWidth = SPI_COMMUNICATION_WIDTH_8BITS,
    .baudRate = 20000000,//20000000,
    .bufferType  = DRV_SPI_BUFFER_TYPE_STANDARD,
    .rxInterruptMode = SPI_FIFO_INTERRUPT_WHEN_TRANSMIT_BUFFER_IS_COMPLETELY_EMPTY,
    .txInterruptMode = SPI_FIFO_INTERRUPT_WHEN_RECEIVE_BUFFER_IS_NOT_EMPTY,
    .clockMode = DRV_SPI_CLOCK_MODE_IDLE_HIGH_EDGE_FALL,
    .inputSamplePhase = SPI_INPUT_SAMPLING_PHASE_IN_MIDDLE,
    .txInterruptSource = INT_SOURCE_SPI_1_TRANSMIT,
    .rxInterruptSource = INT_SOURCE_SPI_1_RECEIVE,
    .errInterruptSource = INT_SOURCE_SPI_1_ERROR,
};

bool Isp_initSpi(void) 
{
    drvSPIObject = DRV_SPI_Initialize(DRV_SPI_INDEX_0, (SYS_MODULE_INIT *)&initConf_1);

    drvSPIHandle = DRV_SPI_Open( DRV_SPI_INDEX_0, DRV_IO_INTENT_BLOCKING );
    if( drvSPIHandle== NULL )
    {
        //SYS_ASSERT(false, "SPI Open error");
        return false;
    }

    // Without the SPIFE bit set we can't run at 20MHz.  Not sure why as this bit
    // seems like it is only applicable in SPI frame mode, which we are not using.
    SPI1CONSET = 0x00000200;
    return true;
}

void Isp_SpiClose(void) 
{ 
    DRV_SPI_Close(drvSPIHandle); 
} 

bool IspSpi_Tx(unsigned char *buf, int size) 

{ 
    if(size==0) return true;
    
    spiBufferHandleTx  = DRV_SPI_BufferAddWrite ( drvSPIHandle, buf, size ) ; 
    if( spiBufferHandleTx == NULL  ) 

    { 
        //SYS_ASSERT(false, "SPI Write error");
        return false; 
    } 

    while(!(DRV_SPI_BUFFER_EVENT_COMPLETE  & DRV_SPI_BufferStatus (spiBufferHandleTx) )) //Check for the successful data transfer
    { 
        DRV_SPI_Tasks (drvSPIObject); 
    } 

    return true; 

} 

bool IspSpi_Rx(unsigned char *buf,int size) 

{ 
    if(size==0) return true;
    spiBufferHandleRx  = DRV_SPI_BufferAddRead ( drvSPIHandle, buf, size ) ; 

    if  ( spiBufferHandleRx == NULL  ) 
    { 
        //SYS_ASSERT(false, "SPI Read error");
        return false; 
    } 

    while(!(DRV_SPI_BUFFER_EVENT_COMPLETE  & DRV_SPI_BufferStatus (spiBufferHandleRx) ))//Check for the successful data transfer
    { 
        DRV_SPI_Tasks (drvSPIObject); 
    } 
    return true; 

} 
void IspSpiTxRx(unsigned char   *p_txBuf,  int  txLen, unsigned char   *p_rxBuf,int  rxLen)
{
    IspSpi_Tx(p_txBuf,  txLen);
    IspSpi_Rx(p_rxBuf,  rxLen);
}


static void Isp_initSystem(void)
{
    SYS_CLK_INIT generalInit;
    // 1. init system
    memset(&generalInit, 0, sizeof(generalInit));
    // Populate the oscillator initialization structure
    generalInit.systemClockSource = SYS_CLK_SOURCE_PRIMARY;
    generalInit.systemClockFrequency = 80000000L;

    generalInit.peripheralClockEnable = true;
    generalInit.peripheralClockSource = SYS_CLK_SOURCE_SYSCLK_OUT;
    generalInit.peripheralClockFrequency = 80000000L;

    SYS_CLK_Initialize (&generalInit);
}
void ISP_SPI_init(void)
{
    Isp_initSystem();
    Isp_initSpi();
}




#if 0    //DMA SPI
extern bool WF_EintIsDisabled(void);
extern void WF_EintDisable(void);
extern void WF_EintEnable(void);

#define MRF24W_SPI_CHN   1

void IspSpiDMA_Tx(uint8_t *pbuf,int length)
{
    uint8_t  rxTrash[3000];
    bool intDisabled;
    // pbuf points to uint8_t array of data to be transmitted to MRF
    // length indicates number of bytes to send
    // save state of external interrupt here
    intDisabled = WF_EintIsDisabled();
    WF_EintDisable();


    IEC1CLR=0x00030000; // disable DMA channel 0&1 interrupts
    IFS1CLR=0x00030000; // clear existing DMA channel 0&1 interrupt flag

    PLIB_DMA_Enable(0); // DMACONSET=0x00008000; // enable the DMA controller

    PLIB_DMA_ChannelXPrioritySelect(0,DMA_CHANNEL_0, DMA_CHANNEL_PRIORITY_3);//DCH0CONSET = 0x3; // channel off, pri 3, no chaining
    PLIB_DMA_ChannelXChainDisable(0,DMA_CHANNEL_0);
    PLIB_DMA_ChannelXPrioritySelect(0,DMA_CHANNEL_1, DMA_CHANNEL_PRIORITY_2);//    DCH1CONSET = 0x02;//0x62;        
    PLIB_DMA_ChannelXChainEnable(0,DMA_CHANNEL_1);

    DCH0ECONCLR=0xFFFFFFFF; // no start or stop irq?s, no pattern match
    DCH1ECONCLR=0xFFFFFFFF; // no start or stop irq?s, no pattern match

    // program the transfer
    PLIB_DMA_ChannelXSourceStartAddressSet     (0,DMA_CHANNEL_0, ((unsigned long int)pbuf) & 0x1FFFFFFFL);
    PLIB_DMA_ChannelXDestinationStartAddressSet(0,DMA_CHANNEL_1, ((unsigned long int)rxTrash)& 0x1FFFFFFFL);

    if( MRF24W_SPI_CHN == 1)
    {
        PLIB_DMA_ChannelXDestinationStartAddressSet(0,DMA_CHANNEL_0, ((unsigned long int)&SPI1BUF) & 0x1FFFFFFFL);
        PLIB_DMA_ChannelXSourceStartAddressSet     (0,DMA_CHANNEL_1, ((unsigned long int)&SPI1BUF) & 0x1FFFFFFFL);
    }
    else if( MRF24W_SPI_CHN == 2) 
    {
        PLIB_DMA_ChannelXDestinationStartAddressSet(0,DMA_CHANNEL_0, ((unsigned long int)&SPI2BUF) & 0x1FFFFFFFL);
        PLIB_DMA_ChannelXSourceStartAddressSet       (0,DMA_CHANNEL_1, ((unsigned long int)&SPI2BUF) & 0x1FFFFFFFL);
    }

    PLIB_DMA_ChannelXSourceSizeSet       (0,DMA_CHANNEL_0,length); 
    PLIB_DMA_ChannelXDestinationSizeSet(0,DMA_CHANNEL_0,1      );
    PLIB_DMA_ChannelXCellSizeSet       (0,DMA_CHANNEL_0,1      );

    PLIB_DMA_ChannelXSourceSizeSet       (0,DMA_CHANNEL_1,1); 
    PLIB_DMA_ChannelXDestinationSizeSet(0,DMA_CHANNEL_1,length);
    PLIB_DMA_ChannelXCellSizeSet       (0,DMA_CHANNEL_1,1      );


    DCH0INTCLR=0x00ff00ff; // clear existing events, disable all interrupts
    DCH1INTCLR=0x00ff00ff; // clear existing events, disable all interrupts
    
    PLIB_DMA_ChannelXEnable(0,DMA_CHANNEL_0);//DCH0CONSET=0x80; // turn channel on
    PLIB_DMA_ChannelXEnable(0,DMA_CHANNEL_1);//DCH1CONSET=0x80; // turn channel on
    
    // initiate a transfer
    PLIB_DMA_ChannelXStartIRQSet(0, DMA_CHANNEL_0, DMA_TRIGGER_SPI_1_TRANSMIT);//DCH0ECONSET=DMA_EV_START_IRQ_EN|DMA_EV_START_IRQ(_SPI1_TX_IRQ);
    PLIB_DMA_ChannelXTriggerEnable(0, DMA_CHANNEL_0, DMA_CHANNEL_TRIGGER_TRANSFER_START);

    PLIB_DMA_ChannelXStartIRQSet(0, DMA_CHANNEL_1, DMA_TRIGGER_SPI_1_RECEIVE);//DCH1ECONSET=DMA_EV_START_IRQ_EN|DMA_EV_START_IRQ(_SPI1_RX_IRQ);
    PLIB_DMA_ChannelXTriggerEnable(0, DMA_CHANNEL_1, DMA_CHANNEL_TRIGGER_TRANSFER_START);
//      DCH0ECONSET=0x00000080; // set CFORCE to 1
    // do something else
    // poll to see that the transfer was done
    while(true)
    {
        register int pollCnt; // use a poll counter.
        // continuously polling the DMA controller in a tight
        // loop would affect the performance of the DMA transfer
        int dma0Flags=DCH0INT;
        int dma1Flags = DCH1INT;
        if((dma0Flags&0xb)&&(dma1Flags&0xb))
        {            // one of CHERIF (DCHxINT<0>), CHTAIF (DCHxINT<1>)
                    // or CHBCIF (DCHxINT<3>) flags set
            break;    // transfer completed
        }
        pollCnt=length; // use an adjusted value here
        while(pollCnt--); // wait before reading again the DMA controller
    }


    PLIB_DMA_Disable(0);//DMACONCLR=0x00008000; // disable the DMA controller
    if(!intDisabled)
    {
        WF_EintEnable();
    }
}

void IspSpiDMA_Rx(uint8_t *pbuf,uint16_t length)
{
    bool intDisabled;
    unsigned char  txTrash[3000];
    // pbuf points to uint8_t array of data to be received from MRF
    // length indicates number of bytes to read
    intDisabled = WF_EintIsDisabled();
    WF_EintDisable();


    IEC1CLR=0x00030000; // disable DMA channel 0&1 interrupts
    IFS1CLR=0x00030000; // clear existing DMA channel 0&1 interrupt flag


    PLIB_DMA_Enable(0); // DMACONSET=0x00008000; // enable the DMA controller
    
    
    PLIB_DMA_ChannelXPrioritySelect(0,DMA_CHANNEL_0, DMA_CHANNEL_PRIORITY_3);//DCH0CONSET = 0x3; // channel off, pri 3, no chaining
    PLIB_DMA_ChannelXChainDisable(0,DMA_CHANNEL_0);
    PLIB_DMA_ChannelXPrioritySelect(0,DMA_CHANNEL_1, DMA_CHANNEL_PRIORITY_2);//    DCH1CONSET = 0x03;//0x62;
    PLIB_DMA_ChannelXChainEnable(0,DMA_CHANNEL_1);
    
    DCH0ECONCLR=0xFFFFFFFF; // no start or stop irq?s, no pattern match
    DCH1ECONCLR=0xFFFFFFFF; // no start or stop irq?s, no pattern match

    // program the transfer
    PLIB_DMA_ChannelXSourceStartAddressSet     (0,DMA_CHANNEL_0, ((unsigned long int)txTrash) & 0x1FFFFFFFL);
    PLIB_DMA_ChannelXDestinationStartAddressSet(0,DMA_CHANNEL_1, ((unsigned long int)pbuf)     & 0x1FFFFFFFL);
    
    if( MRF24W_SPI_CHN == 1)
    {
        PLIB_DMA_ChannelXDestinationStartAddressSet(0,DMA_CHANNEL_0, ((unsigned long int)&SPI1BUF) & 0x1FFFFFFFL);
        PLIB_DMA_ChannelXSourceStartAddressSet     (0,DMA_CHANNEL_1, ((unsigned long int)&SPI1BUF) & 0x1FFFFFFFL);
    }
    else if( MRF24W_SPI_CHN == 2) 
    {
        PLIB_DMA_ChannelXDestinationStartAddressSet(0,DMA_CHANNEL_0, ((unsigned long int)&SPI2BUF) & 0x1FFFFFFFL);
        PLIB_DMA_ChannelXSourceStartAddressSet       (0,DMA_CHANNEL_1, ((unsigned long int)&SPI2BUF) & 0x1FFFFFFFL);
    }

    PLIB_DMA_ChannelXSourceSizeSet     (0,DMA_CHANNEL_0,length); 
    PLIB_DMA_ChannelXDestinationSizeSet(0,DMA_CHANNEL_0,1     );
    PLIB_DMA_ChannelXCellSizeSet       (0,DMA_CHANNEL_0,1     );

    PLIB_DMA_ChannelXSourceSizeSet     (0,DMA_CHANNEL_1,1); 
    PLIB_DMA_ChannelXDestinationSizeSet(0,DMA_CHANNEL_1,length);
    PLIB_DMA_ChannelXCellSizeSet       (0,DMA_CHANNEL_1,1     );


    DCH0INTCLR=0x00ff00ff; // clear existing events, disable all interrupts
    DCH1INTCLR=0x00ff00ff; // clear existing events, disable all interrupts

    // initiate a transfer
    PLIB_DMA_ChannelXStartIRQSet(0, DMA_CHANNEL_0, DMA_TRIGGER_SPI_1_TRANSMIT);
    PLIB_DMA_ChannelXTriggerEnable(0, DMA_CHANNEL_0, DMA_CHANNEL_TRIGGER_TRANSFER_START);

    PLIB_DMA_ChannelXStartIRQSet(0, DMA_CHANNEL_1, DMA_TRIGGER_SPI_1_RECEIVE);
    PLIB_DMA_ChannelXTriggerEnable(0, DMA_CHANNEL_1, DMA_CHANNEL_TRIGGER_TRANSFER_START);


    PLIB_DMA_ChannelXEnable(0,DMA_CHANNEL_0);
    PLIB_DMA_ChannelXEnable(0,DMA_CHANNEL_1);
       
//      DCH0ECONSET=0x00000080; // set CFORCE to 1
    // do something else
    // poll to see that the transfer was done
    while(true)
    {
        register int pollCnt; // use a poll counter.
        // continuously polling the DMA controller in a tight
        // loop would affect the performance of the DMA transfer
        int dma0Flags=DCH0INT;
        int dma1Flags = DCH1INT;
        if((dma0Flags&0xb)&&(dma1Flags&0xb))
        {            // one of CHERIF (DCHxINT<0>), CHTAIF (DCHxINT<1>)
                    // or CHBCIF (DCHxINT<3>) flags set
            break;    // transfer completed
        }
        pollCnt=length<<1; // use an adjusted value here
        while(pollCnt--); // wait before reading again the DMA controller
    }


    PLIB_DMA_Disable(0);

    if(!intDisabled)
    {
        WF_EintEnable();
    }
}

#endif
//DOM-IGNORE-END
