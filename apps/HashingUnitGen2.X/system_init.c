/**************************************************************************
 USB Device Layer Implementation

  Company:
    Microchip Technology Inc.

  File Name:
    usb_device.c

  Summary:
    This file contains implementations of both private and public functions
    of the USB Device Layer.

  Description:
    This file contains the USB device layer implementation.
  **************************************************************************/

// DOM-IGNORE-BEGIN
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
// DOM-IGNORE-END



#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

//#include "system_config.h"
//#include "usb/usb_common.h"
//#include "usb/usb_chapter_9.h"
//#include "usb/usb_device.h"
//#include "usb/src/usb_device_local.h"
#include "app.h"
#include "system_init.h"

/*******************************************************************************
  Validate the following macros
*/
#if ( USB_DEVICE_MAX_INSTANCES == 0 )
    #error( " USB_DEVICE_MAX_INSTANCES must be > 0 ");
#endif

#if ( USB_DEVICE_MAX_CLIENTS == 0 )
    #error( " USB_DEVICE_MAX_CLIENTS must be > 0 ");
#endif



typedef struct __attribute__ ((packed))
{
    uint8_t bLength;
    uint8_t bDescriptorType;
}USB_DEVICE_SERVICE_DESCRIPTOR_HEAD;


// ****************************************************************************
// ****************************************************************************
// Section: Configuration Bits
// ****************************************************************************
// ****************************************************************************

/*
 System PLL Output Clock Divider (FPLLODIV)     = Divide by 1
 PLL Multiplier (FPLLMUL)                       = Multiply by 20
 PLL Input Divider (FPLLIDIV)                   = Divide by 2
 Watchdog Timer Enable (FWDTEN)                 = Disabled
 Clock Switching and Monitor Selection (FCKSM)  = Clock Switch Enable,
                                                  Fail Safe Clock Monitoring Enable
 Peripheral Clock Divisor (FPBDIV)              = Divide by 1
 */
#pragma config FPLLODIV = DIV_1, FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FWDTEN = OFF, FCKSM = CSECME, FPBDIV = DIV_1

/*
 CLKO Output Signal Active on the OSCO Pin(OSCIOFNC)    = Enable
 Primary Oscillator Configuration(POSCMOD)              = External
 Secondary Oscillator Enable(FSOSCEN)                   = Enable
 Oscillator Selection Bits(FNOSC)                       = Primary osc with PLL
 */
#pragma config OSCIOFNC = ON, POSCMOD = HS, FSOSCEN = ON, FNOSC = PRIPLL

/* Enable USB PLL */
#pragma config UPLLEN   = ON

/* USB PLL input devider */
#pragma config UPLLIDIV = DIV_2

#pragma config ICESEL = ICS_PGx2


// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* USB Device layer Initialization Data

  Summary:
    Defines the device layer initialization data

  Description
    This structure defines the device layer's initialization data.

  Remarks:
    None.
*/

USB_DEVICE_INIT usbDevInitData =
{
    /* System module initialization */
    {SYS_MODULE_POWER_RUN_FULL},

    /* USB device driver client index*/
    DRV_USB_INDEX_0,

    false, // never stop USB

    false, // never suspend USB

    INT_SOURCE_USB_1,  // interrupt source (specific to PIC32MX250F128B)

    (void *)NULL,   // end point table

    USB_DEVICE_INSTANCES_NUMBER,    // registered func count

    /* Function driver table registered to this instance of the USB device layer*/
    (USB_DEVICE_FUNC_REGISTRATION_TABLE*)funcRegistrationTable,

    /* Pointer to USB Descriptor structure */
    (USB_MASTER_DESCRIPTOR*)&usbMasterDescriptor,

    USB_SPEED_HIGH
};


// *****************************************************************************
/* USB controller driver Initialization Data

  Summary:
    Defines the USB controller driver Initialization Data

  Description
    This structure defines the USB controller driver Initialization Data.

  Remarks:
    None.
*/

DRV_USB_INIT usbCDInitData =
{
    /* System module initialization */
    {SYS_MODULE_POWER_RUN_FULL},

    /* Identifies peripheral (PLIB-level) ID */
    USB_ID_1,

    /* stop in idle */
    false,

    /* suspend in sleep */
    false,

    /* interrupt source */
    INT_SOURCE_USB_1,

    /* USB Speed */
    USB_SPEED_HIGH,

    /* USB Op Mode */
    USB_OPMODE_DEVICE,

    /* Endpoint Descriptor Table buffer */
    (void*)NULL
};

// Timer


#if defined (HARMONY_TMR_PORTING)
SYS_MODULE_OBJ TimerObjectHandle;
SYS_MODULE_OBJ TimerDriverHandle;
SYS_TMR_INIT TimerInitConfig;

DRV_TMR_INIT   timerInit =
{
    .tmrId = APP_TMR_ID,
    .timerPeriod = DRV_TMR_CONFIG_INIT_INITIAL_COUNT,
    .clockSource = TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK,
    .interruptSource = DRV_TMR_CONFIG_INIT_INTERRUPT_SOURCE, //TMR_INT_SOURCE,
    .prescale = TMR_PRESCALE_VALUE_8,
    .postscale = TMR_POSTSCALE_NOT_SUPPORTED,
    .sourceEdge = TMR_CLOCK_SOURCE_EDGE_NONE,
    .moduleInit = SYS_MODULE_POWER_RUN_FULL
};
#endif


// *****************************************************************************
/* Driver objects.

  Summary:
    Contains driver objects.

  Description:
    This structure contains driver objects returned by the driver init routines
    to the application. These objects are passed to the driver tasks routines.
*/

APP_DRV_OBJECTS appDrvObject;


// *****************************************************************************
// *****************************************************************************
// Section: Driver Initialization Data
// *****************************************************************************
// *****************************************************************************


// global data
//
volatile SYS_TICK               _SystemTickCount = 0;
volatile unsigned int           _SystemTickResolution = 0;

// local data
//
static unsigned long             _SystemTickUpdateRate;
static int32_t                   _SystemClockFreq = -1;

//static sTickNode*               _tickHead = 0;
//static sTickNode*               _tickTail = 0;


// *****************************************************************************
// *****************************************************************************
// Section: System Initialization
// *****************************************************************************
// *****************************************************************************
/*******************************************************************************
  Function:
    void SYS_Initialize ( SYS_INIT_DATA *data )

  Summary:
    Initializes the board, services, drivers, application and other modules

  Description:
    This routine initializes the board, services, drivers, application and other
    modules as configured at build time.  In a bare-metal environment (where no
    OS is supported), this routine should be called almost immediately after
    entering the "main" routine.

  Precondition:
    The C-language run-time environment and stack must have been initialized.

  Parameters:
    data        - Pointer to the system initialzation data structure containing
                  pointers to the board, system service, and driver
                  initialization routines
  Returns:
    None.

  Example:
    <code>
    SYS_INT_Initialize(NULL);
    </code>

  Remarks:
    Basic System Initialization Sequence:

    1.  Initilize minimal board services and processor-specific items
        (enough to use the board to initialize drivers and services)
    2.  Initialize all supported system services
    3.  Initialize all supported modules
        (libraries, drivers, middleware, and application-level modules)
    4.  Initialize the main (static) application, if present.

    The order in which services and modules are initialized and started may be
    important.

    For a static system (a system not using the ISP's dynamic implementation
    of the initialization and "Tasks" services) this routine is implemented
    for the specific configuration of an application.
 */

void SYS_Initialize ( void *data )
{
    /* Initialize the BSP */
    //BSP_Initialize ( );

    /*  Initialize the Timer driver */
    appDrvObject.tmrObject = DRV_TMR_Initialize ( APP_TMR_INDEX, &timerInit );

    /* Initialize the ADC driver */
    //appDrvObject.adcObject = DRV_ADC_Initialize ( APP_ADC_INDEX, NULL );

    /* Initialize the USART driver */
    //appDrvObject.usartObject = DRV_USART_Initialize ( APP_USART_INDEX, NULL );

    /* Note:  NULL is passed as the address of the init configuration structure
       to demonstrate the capability of ISP device drivers to accept static init
       parameters. */

    /* Set the Timer Interrupt priority to level 3  */
    //SYS_INT_PrioritySet ( APP_TMR_INT_SOURCE, PLIB_INT_PRIORITY_LEVEL3 ); // TODO: fix this

    /* Set the ADC Interrupt priority to level 1 */
    //SYS_INT_PrioritySet ( APP_ADC_INT_SOURCE, PLIB_INT_PRIORITY_LEVEL1 );

    /* Set the UART-2 Interrupt priority to level 2 */
    //SYS_INT_PrioritySet ( APP_USART_INT_SOURCE_TX, PLIB_INT_PRIORITY_LEVEL2 );

    /* Initialize the interrupt sub system module */
    SYS_INT_Initialize ( );

    /* Initialize the Application */
    APP_Initialize ( );
}



/*********************************************************************
 * Function:        void INTEnableSystemMultiVectoredInt(void)
 *
 * PreCondition:    EBASE and IntCtl.VS set up
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    System interrupts are turned on
 *
 * Overview:        Enables system wide multi-vectored interrupts
 ********************************************************************/
void __attribute__ ((nomips16)) INTEnableSystemMultiVectoredInt(void)
{
    unsigned int val;

    // set the CP0 cause IV bit high
    asm volatile("mfc0   %0,$13" : "=r"(val));
    val |= 0x00800000;
    asm volatile("mtc0   %0,$13" : "+r"(val));

    INTCONSET = _INTCON_MVEC_MASK;

    // set the CP0 status IE bit high to turn on interrupts
    INTEnableInterrupts();

}



// *****************************************************************************
/* Device layer instance objects.

  Summary:
    Holds all of the variables required by the instance.

  Description:
    This structure holds all of the variables required by the instance.

  Remarks:
    None.
*/

static USB_DEVICE_INSTANCE_STRUCT usbDeviceInstance[USB_DEVICE_MAX_INSTANCES];

// *****************************************************************************
/* Driver Client instance objects.

  Summary:
    Defines the client instances objects that are available on the device.

  Description:
    This data type defines the client instance objects that are available on
    the device, so as to capture the Client state of the instance.

  Remarks:
    None.
*/

static USB_DEVICE_CLIENT_STRUCT usbDeviceClients[USB_DEVICE_MAX_INSTANCES][USB_DEVICE_MAX_CLIENTS + 1];


// *****************************************************************************
/* Function:
    static USB_DEVICE_CONTROL_TRANSFER_RESULT _USB_DEVICE_ControlTransferHandler(
                                                SYS_MODULE_INDEX iUSBDev,
                                                USB_DEVICE_CONTROL_TRANSFER_STATE transferState,
                                                SETUP_PKT* setupPkt,
                                                USB_DEVICE_CONTROL_TRANSFER_DATA_OBJECT * controlXferDataObj
                                                )

  Summary:
    USB device layer's own control trasfer handler.

  Description:
    This function processes the setup packet.

  Precondition:
    None.

  Parameters:
    iUSBDev             -   Device layer index.
    setupPkt            -   Pointer to the setup packet.
    transfer state      -   Control transfer state.
    controlXferDataObj  -   Control transfer data object.

  Returns:
    USB_DEVICE_CONTROL_TRANSFER_RESULT_SUCCESS if successful.
    USB_DEVICE_CONTROL_TRANSFER_RESULT_FAILED  if failed.

  Example:
    <code>

    </code>

  Remarks:
    None.

*/

static void  _USB_DEVICE_ControlTransferHandler(    USB_DEVICE_CONTROL_TRANSFER_HANDLE xferhandle,
                                                    SYS_MODULE_INDEX handlerIndex,
                                                    USB_DEVICE_CONTROL_TRANSFER_EVENT transferEvent,
                                                    USB_DEVICE_CONTROL_TRANSFER_EVENT_DATA * eventData );


// *****************************************************************************
/* Function:
    static USB_DEVICE_CONTROL_TRANSFER_RESULT
             _USB_DEVICE_ProcessStandardSetRequests(USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance,
                                            SETUP_PKT *setupPkt,
                                            USB_DEVICE_CONTROL_TRANSFER_DATA_OBJECT * controlTransferData)


  Summary:
    Processes the standard "set" requests.

  Description:
    This function processes the standard "set" requests.

  Precondition:
    None.

  Parameters:

    usbDeviceInstance    -   This instance of the USB device layer
    setupPkt             -   Pointer to the setup packet
    controlTransferData  -   Control transfer data object.

  Returns:
    USB_DEVICE_CONTROL_TRANSFER_RESULT_SUCCESS if successful.
    USB_DEVICE_CONTROL_TRANSFER_RESULT_FAILED  if failed.

  Example:
    <code>

    </code>

  Remarks:
    None.

*/

static void _USB_DEVICE_ProcessStandardSetRequests( USB_DEVICE_INSTANCE_STRUCT * usbDeviceInstance,
                                            USB_SETUP_PACKET * setupPkt);


// *****************************************************************************
/* Function:
   static USB_DEVICE_CONTROL_TRANSFER_RESULT _USB_DEVICE_ProcessStandardGetRequests(
                                USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance,
                                SETUP_PKT* setupPkt,
                                USB_DEVICE_CONTROL_TRANSFER_DATA_OBJECT * controlTransferData)


  Summary:
    Processes the standard "get" requests.

  Description:
    This function processes the standard "get" requests.

  Precondition:
    None.

  Parameters:
    usbDeviceInstance    -   This instance of the USB device layer
    setupPkt             -   Pointer to the setup packet
    controlTransferData  -   Control transfer data object.

  Returns:
    USB_DEVICE_CONTROL_TRANSFER_RESULT_SUCCESS if successful.
    USB_DEVICE_CONTROL_TRANSFER_RESULT_FAILED  if failed.

  Example:
    <code>

    </code>

  Remarks:
    None.

*/

static void _USB_DEVICE_ProcessStandardGetRequests( USB_DEVICE_INSTANCE_STRUCT * usbDeviceInstance,
                                                    USB_SETUP_PACKET * setupPkt );


// *****************************************************************************
/* Function:
    static void _USB_DEVICE_ProcessOtherRequests(
                                USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance,
                                SETUP_PKT *setupPkt,
                                USB_DEVICE_CONTROL_TRANSFER_DATA_OBJECT * controlTransferData)


  Summary:
    Processes "other" requests.

  Description:
    This function processes "other" requests.

  Precondition:
    None.

  Parameters:
    usbDeviceInstance    -   This instance of the USB device layer
    setupPkt             -   Pointer to the setup packet
    controlTransferData  -   Control transfer data object.

  Returns:
    USB_DEVICE_CONTROL_TRANSFER_RESULT_SUCCESS if successful.
    USB_DEVICE_CONTROL_TRANSFER_RESULT_FAILED  if failed.

  Example:
    <code>

    </code>

  Remarks:
    None.

*/

static void _USB_DEVICE_ProcessOtherRequests(
                            USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance ,
                            USB_SETUP_PACKET * setupPkt );


// *****************************************************************************
/* Function:
    static void _USB_DEVICE_EventHandler(void* referenceHandle,
            DRV_USB_CLIENT_STATUS eventType, DRV_USB_EVENT_DATA * eventData )

  Summary:
    Handles the events originating from the USB Controller driver.

  Description:
    This function is registered into the USB Controller driver as a callback
    function. The USB Controller driver calls this function in case of events
    from the USB Controller driver.

  Precondition:
    None.

  Parameters:
    referenceHandle           - USB device instance
    eventType                 - Event type
    eventData                 - Data associated with the event


  Returns:
    None.

  Example:
    <code>

    </code>

  Remarks:
    None.

*/

void _USB_DEVICE_EventHandler(uintptr_t referenceHandle,
            DRV_USB_EVENT eventType, void * eventData );


/******************************************************************************
  Function:
    static void _USB_DEVICE_BroadcastEventToClients
       ( USB_DEVICE_EVENT event, USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance )

  Summary:
    Broadcasts events to the application client.

  Description:
    This function broadcasts device layer events to all application level clients.

  Parameters:
    event             - Device layer event
    usbDeviceInstance - USB device instance

  Returns:
    None.

  Example:
    <code>

    </code>

  Remarks:
    None.
*/

static void _USB_DEVICE_BroadcastEventToClients( USB_DEVICE_EVENT event, USB_DEVICE_EVENT_DATA * eventData,
                               USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance );


/******************************************************************************
  Function:
    static void _USB_DEVICE_PerformFunctionDriverRoutines(USB_DEVICE_EVENT event,
                                    USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance )


  Summary:
    Calls all function driver routines here.

  Description:
    Deinitialization routines and task routines of the function driver
    are called here.

  Parameters:
    event             - Device layer event
    usbDeviceInstance - USB device instance

  Returns:
    None.

  Example:
    <code>

    </code>

  Remarks:
    None.
*/

static void _USB_DEVICE_BroadcastControlXferEventsToAppClients( USB_DEVICE_CONTROL_TRANSFER_HANDLE handle,
                                                         SYS_MODULE_INDEX handlerIndex,
                                                         USB_DEVICE_CONTROL_TRANSFER_EVENT event,
                                                         void * eventData);


/******************************************************************************
    Tx Endpoint constants
*/

static const USB_ENDPOINT controlEndpointTx = 0x80;


/******************************************************************************
    Endpoint constants
*/

static const USB_ENDPOINT controlEndpointRx  = 0x00;



/******************************************************************************
  Function:
    static void _USB_DEVICE_Ep0ReceiveCompleteCallback( USB_DEVICE_IRP * handle )

  Summary:
    Control receive complete callback.

  Description:
    This callback is called when either data/setup packet is received
   on the control endpoint.

  Parameters:
    handle - IRP handle.

  Returns:
    None.

*/

static void _USB_DEVICE_Ep0ReceiveCompleteCallback( USB_DEVICE_IRP * handle )
{
    USB_DEVICE_IRP * irpHandle = (USB_DEVICE_IRP *)handle;
    USB_DEVICE_INSTANCE_STRUCT * usbDeviceThisInstance;
    USB_DEVICE_CONTROL_TRANSFER_EVENT controlEvent = USB_DEVICE_CONTROL_TRANSFER_NO_EVENT;
    USB_DEVICE_CONTROL_TRANSFER_STRUCT * controlTransfer;

    if(irpHandle->status == USB_DEVICE_IRP_STATUS_ABORTED)
    {
        return;
    }

    usbDeviceThisInstance = (USB_DEVICE_INSTANCE_STRUCT *)irpHandle->userData;

    controlTransfer = &usbDeviceThisInstance->controlTransfer;


    // Something is received on EP0.
    if(irpHandle->status == USB_DEVICE_IRP_STATUS_SETUP)
    {

        if( controlTransfer->inProgress )
        {
            // Abort any previous transfer
            controlTransfer->handler(
                                        controlTransfer->handle,
                                        controlTransfer->handlerIndex,
                                       USB_DEVICE_CONTROL_TRANSFER_ABORTED ,
                                       NULL );
        }
        // Mark the control transfer as "in progress".
        controlTransfer->inProgress = true;

        // Now change the transfer handler back to USB device layer handler.
        controlTransfer->handler = &_USB_DEVICE_ControlTransferHandler;

        controlTransfer->handlerIndex = usbDeviceThisInstance->usbDevLayerIndex;

        controlEvent = USB_DEVICE_CONTROL_SETUP_REQUEST;


    }
    else if( irpHandle->size == 0)
    {
        // ZLP received. This marks the completion of control transfer.
        // Inform the handler.
        controlTransfer->inProgress = false;

        controlEvent = USB_DEVICE_CONTROL_DATA_SENT;

    }
    else if( irpHandle->size &&  controlTransfer->inProgress )
    {
        // We are in the data stage of the control transfer.
        // See if the control transfer handler was expecting the data.

        if(controlTransfer->rxDataCount <  controlTransfer->expectedRxDataCount)
        {
            // Copy the rx buffer to control transfer handler given driver buffer and advance the buffer.
            memcpy(&usbDeviceThisInstance->controlTransfer.rxBuffer[controlTransfer->rxDataCount],
                usbDeviceThisInstance->ep0RxBuffer, irpHandle->size );

            controlTransfer->rxDataCount += irpHandle->size;
        }
        if(controlTransfer->rxDataCount >=  controlTransfer->expectedRxDataCount)
        {
            controlEvent = USB_DEVICE_CONTROL_DATA_RECEIVED;

        }
    }

    if(controlEvent)
    {

         controlTransfer->handler(  controlTransfer->handle,
                                    controlTransfer->handlerIndex,
                                    controlEvent ,
                                    (USB_DEVICE_CONTROL_TRANSFER_EVENT_DATA *)usbDeviceThisInstance->ep0RxBuffer);
    }



     usbDeviceThisInstance->irpEp0Rx.size = USB_DEVICE_EP0_BUFFER_SIZE;


     /* Submit IRP to endpoint 0 to receive the setup packet */
     (void)DRV_USB_DEVICE_IRPSubmit( usbDeviceThisInstance->usbCDHandle,
                                         controlEndpointRx ,
                                         &usbDeviceThisInstance->irpEp0Rx);

}


/******************************************************************************
  Function:
    static void _USB_DEVICE_Ep0TransmitCompleteCallback( void * handle)

  Summary:
    EP0 transmit complete callback.

  Description:
    This function is called by the controller driver after the completing the
    EP0 transmit.

  Parameters:
     handle - IRP handle.

  Returns:
    None.

*/

static void _USB_DEVICE_Ep0TransmitCompleteCallback(USB_DEVICE_IRP * handle)
{
    USB_DEVICE_IRP * irpHandle = (USB_DEVICE_IRP *)handle;
    USB_DEVICE_INSTANCE_STRUCT * usbDeviceThisInstance;
    USB_DEVICE_CONTROL_TRANSFER_STRUCT * controlTransfer;

    controlTransfer = &usbDeviceInstance->controlTransfer;


    usbDeviceThisInstance = (USB_DEVICE_INSTANCE_STRUCT *)irpHandle->userData;

    if(irpHandle->status == USB_DEVICE_IRP_STATUS_ABORTED)
    {
        return;
    }

    if(usbDeviceThisInstance->setAddressPending)
    {
        DRV_USB_DEVICE_AddressSet(usbDeviceThisInstance->usbCDHandle, usbDeviceThisInstance->deviceAddress);
        usbDeviceThisInstance->setAddressPending = false;
    }

    if(irpHandle->status == USB_DEVICE_IRP_STATUS_COMPLETED)
    {
        if( irpHandle->size == 0 )
        {
            // Just completed transmitting ZLP.
            controlTransfer->inProgress = false;
        }
    }
}



/******************************************************************************
  Function:
    static void _USB_DEVICE_ProcessSetupPacket(SETUP_PKT* setupPkt,
                                USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance)

  Summary:
    Processes the setup packet received from the USB Controller driver.

  Description:
    This function processes the setup packet received from the USB Controller
    driver.

  Parameters:
    setupPkt           - Setup packet buffer
    usbDeviceInstance  - This instance of the USB device layer

  Returns:
    None.

*/

static void  _USB_DEVICE_ControlTransferHandler(
                                                    USB_DEVICE_CONTROL_TRANSFER_HANDLE xferhandle,
                                                    SYS_MODULE_INDEX handlerIndex,
                                                    USB_DEVICE_CONTROL_TRANSFER_EVENT transferEvent,
                                                    USB_DEVICE_CONTROL_TRANSFER_EVENT_DATA * eventData )
{
    USB_DEVICE_INSTANCE_STRUCT * usbDeviceThisInstance =
                    (USB_DEVICE_INSTANCE_STRUCT *)&usbDeviceInstance[handlerIndex];

    USB_SETUP_PACKET * setupPkt = ( USB_SETUP_PACKET *) eventData;

    if( transferEvent == USB_DEVICE_CONTROL_SETUP_REQUEST )
    {
        // Cancel any IRP that is in the pipe.
        DRV_USB_DEVICE_IRPCancelAll( usbDeviceInstance->usbCDHandle,
                                                        controlEndpointTx );

        if(setupPkt->bmRequestType == ( USB_SETUP_DIRN_HOST_TO_DEVICE |
                                        USB_SETUP_TYPE_STANDARD |
                                        USB_SETUP_RECIPIENT_DEVICE  ) )
        {
            // Serve standard SET requests
            _USB_DEVICE_ProcessStandardSetRequests( usbDeviceThisInstance, setupPkt );
        }
        else if( setupPkt->bmRequestType == ( USB_SETUP_DIRN_DEVICE_TO_HOST |
                                             USB_SETUP_TYPE_STANDARD |
                                             USB_SETUP_RECIPIENT_DEVICE ) )
        {

            // Serve standard GET requests
            _USB_DEVICE_ProcessStandardGetRequests( usbDeviceThisInstance, setupPkt );
        }
        else
        {
            // Serve any requests that is not "standard" type and whose
            // recipient is not "device". (Any request whose recipient is interface/endpoint
            // must be handled by the function driver. This is because function driver has all the information
            // about endpoint and interface)
            _USB_DEVICE_ProcessOtherRequests( usbDeviceThisInstance, setupPkt);
        }
    }
}


/******************************************************************************
  Function:
    static void _USB_DEVICE_ProcessStandardGetRequests(SETUP_PKT* setupPkt,
                                USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance)

  Summary:
    Processes the standard "get" requests received from the USB Controller driver.

  Description:
    This function processes the standard "get" requests received from the USB
    Controller driver.

  Parameters:
    setupPkt           - Setup packet buffer
    usbDeviceInstance  - This instance of the USB device layer

  Returns:
    None.

*/

static void _USB_DEVICE_ProcessStandardGetRequests( USB_DEVICE_INSTANCE_STRUCT * usbDeviceInstance,
                                                    USB_SETUP_PACKET * setupPkt )
{

    USB_CONFIGURATION_DESCRIPTOR* lConfigDescriptor = NULL;
    uint8_t* stringDesc;
    uint16_t size = 0;
    void*  pData = NULL;
    uint8_t index;

    USB_MASTER_DESCRIPTOR * ptrMasterDescTable ;

    // Copy the Master decriptor table to a local pointer.
    ptrMasterDescTable = usbDeviceInstance->ptrMasterDescTable ;

    if(setupPkt->bRequest == USB_REQUEST_GET_DESCRIPTOR)
    {
        switch(setupPkt->bDescriptorType)
        {
            case USB_DESCRIPTOR_DEVICE:
                if(usbDeviceInstance->usbSpeed == USB_SPEED_HIGH)
                {
                    // high speed descriptor.
                    SYS_ASSERT( ( ptrMasterDescTable->ptrHighSpeedDeviceDescriptor != NULL ),
                                                              "High speed device descriptor is NULL" );
                    // pointer to high speed device descriptor.
                    pData = ( (uint8_t*) ptrMasterDescTable->ptrHighSpeedDeviceDescriptor );
                }
                else
                {
                    // Full/low speed descriptor.
                    SYS_ASSERT( ( ptrMasterDescTable->ptrDeviceDescriptor != NULL ),
                                                            "Full/Low speed device descriptor is NULL");
                    // full/low speed device descriptor pointeusbDeviceInstance->ptrMasterDescTabler.
                    pData = ( (uint8_t*) ptrMasterDescTable->ptrDeviceDescriptor );
                }
                // Total size of the device descriptor (Its always 18).
                size = 18;
                break;

            case USB_DESCRIPTOR_CONFIGURATION:
                // Get correct pointer to the descriptor based on config value.
                // setupPkt->bDscIndex indicates the host requested configuration index.
                // Make sure that the requested configuration index is with in the limits.
                if( (setupPkt->bDscIndex) < usbDeviceInstance->maxConfigs )
                {
                    lConfigDescriptor =
                        ( USB_CONFIGURATION_DESCRIPTOR* )usbDeviceInstance->configDescriptorsPtr[setupPkt->bDscIndex];
                    // Assert that pointer is not NULL
                    SYS_ASSERT( ( lConfigDescriptor != NULL ),
                        "USB Device Layer: Invalid pointer to configuration descriptor");
                    // Total Size of the descriptor to be sent to Host.
                    size = lConfigDescriptor->wTotalLength;

                }
                pData  = (uint8_t *)lConfigDescriptor;
                break;

            case USB_DESCRIPTOR_DEVICE_QUALIFIER:
                if( usbDeviceInstance->usbSpeed == USB_SPEED_HIGH )
                {
                    // For high speed, respond with the other speed (full speed) device_qualifier.
                    pData  = (uint8_t*) ptrMasterDescTable->ptrFullSpeedDeviceQualifier;
                }
                else
                {
                    // For full speed, repond with the other speed (high speed) device_qualifier.
                    pData  = ((uint8_t*) ptrMasterDescTable->ptrHighSpeedDeviceQualifier );
                }

                // Size of device_qualifier descriptor is always 10.
                size = 10;
                break;


            case USB_DESCRIPTOR_STRING:
                index = setupPkt->bDscIndex;
                // Check the string descriptor index
                if(setupPkt->bDscIndex < ptrMasterDescTable->stringDescCount )
                {
                    // Get correct string descriptor
                    stringDesc = (uint8_t*)( ptrMasterDescTable->ptrStringDesc[setupPkt->bDscIndex] );

                    // Prepare the response
                    pData = (uint8_t *)stringDesc;

                    // Length of the string is the first byte in the setring descriptor.
                    size = stringDesc[0];
                }
                break;

            default:

                break;
        }
    }
    else if (setupPkt->bRequest == USB_REQUEST_GET_CONFIGURATION)
    {
        pData = (uint8_t *)&usbDeviceInstance->activeConfiguration;
        size = 1;
    }
    else if (setupPkt->bRequest == USB_REQUEST_GET_STATUS)
    {
        usbDeviceInstance->getStatusResponse.status = 0;
        usbDeviceInstance->getStatusResponse.selfPowered = usbDeviceInstance->selfPowered;
        usbDeviceInstance->getStatusResponse.remoteWakeup = usbDeviceInstance->remoteWakeupStatus;
        pData = (uint8_t *)&usbDeviceInstance->getStatusResponse;
        size = 2;
    }


    if(pData == NULL)
    {
        // STALL the transfer
        USB_DEVICE_ControlStatus(   usbDeviceInstance->hClientInternalOperation,
                                    usbDeviceInstance->controlTransfer.handle,
                                    USB_DEVICE_CONTROL_STATUS_ERROR );
    }
    else
    {
        // Limit the size.
        if( size > setupPkt->wLength )
        {
            size = setupPkt->wLength;
        }

        // Prepare data stage
        USB_DEVICE_ControlSend( usbDeviceInstance->hClientInternalOperation,
                                usbDeviceInstance->controlTransfer.handle,
                                pData,
                                size );
    }
}




/******************************************************************************
  Function:
    static void _USB_DEVICE_ConfigureDevice( USB_DEVICE_INSTANCE_STRUCT* usbDeviceThisInstance )

  Summary:
    This function configures the device.

  Description:
    The initialization of all the function drivers and opening of all endpoints
    are done here.

  Parameters:
    interfaceNumber         - Interface number.
    usbDeviceThisInstance   - This instance of the USB device layer.

  Returns:
    None.

*/

static void _USB_DEVICE_ConfigureDevice( USB_DEVICE_INSTANCE_STRUCT* usbDeviceThisInstance )
{

    uint16_t parsedLength= 0;
    uint16_t confTotalLength;
    uint8_t * pDescriptor = usbDeviceInstance->pActiveConfigDesc;
    uint8_t descriptorType;
    uint8_t interfaceNumber = 0;
    uint8_t alternateSetting = 0;
    USB_DEVICE_FUNC_REGISTRATION_TABLE * pFunctionRegTable = NULL;

    confTotalLength = ((USB_CONFIGURATION_DESCRIPTOR *)pDescriptor)->wTotalLength;

    while(parsedLength < confTotalLength)
    {
        descriptorType = ((USB_DEVICE_SERVICE_DESCRIPTOR_HEAD *)pDescriptor)->bDescriptorType;
        if(descriptorType == USB_DESCRIPTOR_INTERFACE)
        {
            pFunctionRegTable = NULL;
            interfaceNumber = ((USB_INTERFACE_DESCRIPTOR * )pDescriptor)->bInterfaceNumber;
            alternateSetting = ((USB_INTERFACE_DESCRIPTOR * )pDescriptor)->bAlternateSetting;
            // Find out which function driver owns this interface in the function registration table
            pFunctionRegTable = (USB_DEVICE_FUNC_REGISTRATION_TABLE *)_USB_DEVICE_GetFunctionDriverEntryByInterface( interfaceNumber ,
                                                                                    usbDeviceThisInstance);
        }
        if( pFunctionRegTable != NULL )
        {
            pFunctionRegTable->driver->initializeByDescriptor(pFunctionRegTable->funcDriverIndex,
                                                  usbDeviceThisInstance->hClientInternalOperation,
                                                  pFunctionRegTable->funcDriverInit,
                                                  interfaceNumber, alternateSetting,
                                                  descriptorType, pDescriptor);
        }

        parsedLength += ((USB_DEVICE_SERVICE_DESCRIPTOR_HEAD *)pDescriptor)->bLength;
        pDescriptor += ((USB_DEVICE_SERVICE_DESCRIPTOR_HEAD *)pDescriptor)->bLength;
    }
}



/******************************************************************************
  Function:
    static void _USB_DEVICE_ProcessStandardSetRequests(SETUP_PKT* setupPkt,
    DRV_USB_XFER_HANDLE hTransfer, USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance)

  Summary:
    Processes the standard "set" requests received from the USB Controller driver.

  Description:
    This function processes the standard "set" requests received from the USB
    Controller driver.

  Parameters:
    setupPkt           - Setup packet buffer
    usbDeviceInstance  - This instance of the USB device layer

  Returns:
    None.

*/

static void _USB_DEVICE_ProcessStandardSetRequests( USB_DEVICE_INSTANCE_STRUCT * usbDeviceInstance,
                                            USB_SETUP_PACKET * setupPkt)
{
    uint8_t count;
    USB_DEVICE_EVENT_DATA eventData;

    switch(setupPkt->bRequest)
    {
        case USB_REQUEST_SET_ADDRESS:
            //Got set address command. Change the address only after responding to the current request.
            usbDeviceInstance->setAddressPending = true;
            usbDeviceInstance->deviceAddress = setupPkt->bDevADR;
            break;

        case USB_REQUEST_SET_CONFIGURATION:
            // Device falls back to addressed state if configuration value is 0, and
            // if the device is already in configured state.
            if((setupPkt->wValue == 0) && (usbDeviceInstance->usbDeviceState == USB_DEVICE_STATE_CONFIGURED))
            {
                // Configuration value 0 means, host is trying to deconfigure the device.
                // Set a event here. USB device layer task will deinitialize the function drivers later.
                usbDeviceInstance->event = USB_DEVICE_EVENT_DECONFIGURED;
                 // Deinit all function drivers.
                _USB_DEVICE_DeInitializeAllFunctionDrivers ( usbDeviceInstance );
                // Change the current active configuration to Zero
                usbDeviceInstance->activeConfiguration = 0;
                // Change the state to Addressed
                usbDeviceInstance->usbDeviceState = USB_DEVICE_STATE_ADDRESSED;
            }
            else
            {
                // Proceed only if new configuration value is different from
                // current configuration value.
                if( usbDeviceInstance->activeConfiguration != (uint8_t)setupPkt->wValue)
                {
                     for(count = 0; count < usbDeviceInstance->maxConfigs; count++)
                     {
                        // 5th byte in the configuration descriptor table specifies the
                        // configuration value.
                        if( usbDeviceInstance->configDescriptorsPtr[count][5] == setupPkt->bConfigurationValue )
                        {
                            // Got a configuration match. Get the pointer to configuration
                            // descriptor. We have to pass this to function driver, so that
                            // function driver can parse configuration descriptor and get the required info.
                            usbDeviceInstance->pActiveConfigDesc = usbDeviceInstance->configDescriptorsPtr[count];
                        }
                     }

                    // Save the current active configuration.
                    // This may be required for clients to know which configuration is presently active.
                    usbDeviceInstance->activeConfiguration = (uint8_t)setupPkt->wValue;

                    // Initialize all function drivers and change to configured state only if
                    // all function drivers are initialized successfully.
                    //USB_DEVICE_SERVICE_ParseDescriptor(usbDeviceInstance->pActiveConfigDesc, &_USB_DEVICE_ConfigureDevice, usbDeviceInstance);
                    _USB_DEVICE_ConfigureDevice(usbDeviceInstance);

                    // Change the state to configured.
                    usbDeviceInstance->usbDeviceState = USB_DEVICE_STATE_CONFIGURED;
                    // Set an event, so that application and function drivers are informed
                    // about the same.
                    eventData.eventConfigured.configurationValue = (uint8_t)setupPkt->wValue;
                    eventData.eventConfigured.speed = usbDeviceInstance->usbSpeed;
                    _USB_DEVICE_BroadcastEventToClients( USB_DEVICE_EVENT_CONFIGURED, &eventData,
                                                        usbDeviceInstance );

                }
            }
            break;

        default:
            // Respond with a request error.
            // Stall the endpoint.
             // Stall the EP0 TX.
            USB_DEVICE_ControlStatus( usbDeviceInstance->hClientInternalOperation,
                                      usbDeviceInstance->controlTransfer.handle,
                                      USB_DEVICE_CONTROL_STATUS_ERROR);
            break;
    }

    // Send ZLP
    USB_DEVICE_ControlStatus( usbDeviceInstance->hClientInternalOperation,
                              usbDeviceInstance->controlTransfer.handle,
                              USB_DEVICE_CONTROL_STATUS_OK);
}


/******************************************************************************
  Function:
    static USB_DEVICE_CONTROL_TRANSFER_STATE _USB_DEVICE_ProcessOtherRequests(
                            USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance ,
                            SETUP_PKT* setupPkt,
                            USB_DEVICE_CONTROL_TRANSFER_DATA_OBJECT * controlXferData)

  Summary:
    Processes the setup requests that are not targeted to the device but to endpoint/interface.


  Description:
    This funcion processes the setup reequests that are not targeted to the device.
    This function handles endpoint and interface specific setup packets.
    The interface specific setup packets are forwarded to function drivers or
    handled by the endpoint.

  Parameters:
    usbDeviceInstance  - This instance of the USB device layer
    setupPkt           - Setup packet buffer
    controlXferData    - Control transfer data object
  Returns:
    USB_DEVICE_CONTROL_TRANSFER_RESULT_SUCCESS - if the setup packet is processed..

*/
static void _USB_DEVICE_ProcessOtherRequests(
                            USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance ,
                            USB_SETUP_PACKET * setupPkt )
{
    USB_DEVICE_FUNC_REGISTRATION_TABLE * lFuncDriverRegTable;
    USB_ENDPOINT usbEndpoint;
    USB_DEVICE_CONTROL_TRANSFER_STRUCT * controlTransfer = &usbDeviceInstance->controlTransfer;
    USB_DEVICE_CONTROL_STATUS controlStatus = USB_DEVICE_CONTROL_STATUS_ERROR;
    USB_DEVICE_CONTROL_TRANSFER_EVENT_DATA eventData;

    if ( setupPkt->Recipient == USB_SETUP_RECIPIENT_ENDPOINT )
    {
        usbEndpoint = setupPkt->bEPID;

        if( setupPkt->DataDir == USB_SETUP_DIRN_HOST_TO_DEVICE )
        {
            if( setupPkt->bRequest == USB_REQUEST_CLEAR_FEATURE )
            {
                if( setupPkt->wValue == USB_FEATURE_SELECTOR_ENDPOINT_HALT )
                {
                    //TBD: Implement device state check here.
                    DRV_USB_DEVICE_EndpointStallClear(usbDeviceInstance->usbCDHandle, usbEndpoint );
                    controlStatus = USB_DEVICE_CONTROL_STATUS_OK;
                }
                else if( setupPkt->wValue == USB_FEATURE_SELECTOR_DEVICE_REMOTE_WAKEUP )
                {
                    // Remote wakeup disabled.
                    usbDeviceInstance->remoteWakeupStatus
                                            = USB_DEVICE_REMOTE_WAKEUP_DISABLED ;
                    controlStatus = USB_DEVICE_CONTROL_STATUS_OK;
                }
            }
            else if (setupPkt->bRequest == USB_REQUEST_SET_FEATURE )
            {
                if( setupPkt->wValue == USB_FEATURE_SELECTOR_ENDPOINT_HALT )
                {
                    usbEndpoint = setupPkt->bEPID;
                    DRV_USB_DEVICE_EndpointStall(usbDeviceInstance->usbCDHandle,
                                                                usbEndpoint );
                    controlStatus = USB_DEVICE_CONTROL_STATUS_OK;
                }
                else if( setupPkt->wValue == USB_FEATURE_SELECTOR_DEVICE_REMOTE_WAKEUP )
                {
                    usbDeviceInstance->remoteWakeupStatus
                                            = USB_DEVICE_REMOTE_WAKEUP_ENABLED ;
                    controlStatus = USB_DEVICE_CONTROL_STATUS_OK;
                }
            }

            USB_DEVICE_ControlStatus( usbDeviceInstance->hClientInternalOperation,
                                      usbDeviceInstance->controlTransfer.handle,
                                      controlStatus );
        }
        else if( setupPkt->bRequest == USB_REQUEST_GET_STATUS )
        {
            usbDeviceInstance->getStatusResponse.status = 0x00;
            usbDeviceInstance->getStatusResponse.endPointHalt
                    =  DRV_USB_DEVICE_EndpointIsStalled(usbDeviceInstance->usbCDHandle, usbEndpoint );

            USB_DEVICE_ControlSend( usbDeviceInstance->hClientInternalOperation,
                                    usbDeviceInstance->controlTransfer.handle,
                                    (uint8_t *)&usbDeviceInstance->getStatusResponse,
                                    2 );

        }
    }
    else
    {
        // This is a function driver /vendor specific setup packet.
         // Check which function driver has to handle this setup packet.

        lFuncDriverRegTable = (USB_DEVICE_FUNC_REGISTRATION_TABLE *)_USB_DEVICE_GetFunctionDriverEntryByInterface( setupPkt->bIntfID, usbDeviceInstance);

        eventData.setupRequest = setupPkt;

        if( (lFuncDriverRegTable != NULL)
                && (lFuncDriverRegTable->driver->controlTransferNotification != NULL))
        {
            // Save the callback and index for future use.
            // Here we change the handler to function driver specific handler.
            // All further control transfer stage must be handled by the
            // function driver control transfer handler.
            controlTransfer->handler = (void *)lFuncDriverRegTable->driver->controlTransferNotification;
            controlTransfer->handlerIndex = lFuncDriverRegTable->funcDriverIndex;

            // This function driver owns the setup packet.
            controlTransfer->handler( controlTransfer->handle,
                                      controlTransfer->handlerIndex,
                                      USB_DEVICE_CONTROL_SETUP_REQUEST,
                                                              &eventData);
        }
        else
        {
            controlTransfer->handler = (void *)&_USB_DEVICE_BroadcastControlXferEventsToAppClients;
            controlTransfer->handlerIndex = usbDeviceInstance->usbDevLayerIndex ;
            //let app clients handle the setup packet.
            _USB_DEVICE_BroadcastControlXferEventsToAppClients( controlTransfer->handle,
                                                                controlTransfer->handlerIndex,
                                                                USB_DEVICE_CONTROL_SETUP_REQUEST,
                                                                &eventData);
        }
    }
}


/******************************************************************************
  Function:
    static void _USB_DEVICE_BroadcastEventToClients
       ( USB_DEVICE_EVENT event, USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance )

  Summary:
    Broadcasts events to the application client.

  Description:
    This function broadcasts device layer events to all application level clients.

  Parameters:
    event             - Device layer event
    usbDeviceInstance - USB device instance.

  Returns:
    None.

*/

static void _USB_DEVICE_BroadcastEventToClients( USB_DEVICE_EVENT event, USB_DEVICE_EVENT_DATA * eventData,
                                 USB_DEVICE_INSTANCE_STRUCT* usbDeviceInstance )
{
    uint16_t count;
    USB_DEVICE_CLIENT_STRUCT * usbDeviceClientPtr;

    // Inform all application layer clients about the event.
    for(count = 1; count < USB_DEVICE_MAX_CLIENTS+1; count++)
    {
        // Copy the client to local pointer.
        usbDeviceClientPtr = &usbDeviceClients[ usbDeviceInstance->usbDevLayerIndex ][count];

        if( usbDeviceClientPtr->clientState == DRV_CLIENT_STATUS_READY)
        {
            if( usbDeviceClientPtr->callBackFunc != NULL)
            {
                // Pass event to application
                usbDeviceClientPtr->callBackFunc(event, eventData);
            }
        }
    }
}



/******************************************************************************
  Function:
    static void _USB_DEVICE_BroadcastControlXferEventsToAppClients
                                   ( USB_DEVICE_CONTROL_TRANSFER_HANDLE handle,
                                                 SYS_MODULE_INDEX handlerIndex,
                                       USB_DEVICE_CONTROL_TRANSFER_EVENT event,
                                                            void * eventData)

  Summary:
    This function broadcasts control transfer events to application clients.

  Description:


  Parameters:
    handle            - USB device handle
    handlerIndex      - Index
    event             - Event
    eventData         - Event data

  Returns:
    None.

*/

static void _USB_DEVICE_BroadcastControlXferEventsToAppClients( USB_DEVICE_CONTROL_TRANSFER_HANDLE handle,
                                                         SYS_MODULE_INDEX handlerIndex,
                                                         USB_DEVICE_CONTROL_TRANSFER_EVENT event,
                                                         void * eventData)
{
    uint8_t count;
    USB_DEVICE_CLIENT_STRUCT * client = &usbDeviceClients[handlerIndex][1];
    for( count = 1; count < USB_DEVICE_MAX_CLIENTS; count++)
    {
        if( (client->clientState == DRV_CLIENT_STATUS_READY)
                && (client->controlTransferEventCallback != NULL) )
        {
            client->controlTransferEventCallback(client->usbDeviceInstance->controlTransfer.handle,
                                                 event, eventData );

            client++;
        }
    }
}



/********************End of file********************************/
