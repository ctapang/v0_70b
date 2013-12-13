 /*******************************************************************************
  USB CDC class definitions

  Company:
    Microchip Technology Incorported

  FileName:
    usb_host_cdc_local.h

  Summary:
    USB CDC class definitions

  Description:
    This file describes the CDC class specific definitions.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to  you  the  right  to  use,  modify,  copy  and  distribute
Software only when embedded on a Microchip  microcontroller  or  digital  signal
controller  that  is  integrated  into  your  product  or  third  party  product
(pursuant to the  sublicense  terms  in  the  accompanying  license  agreement).

You should refer  to  the  license  agreement  accompanying  this  Software  for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS  WITHOUT  WARRANTY  OF  ANY  KIND,
EITHER EXPRESS  OR  IMPLIED,  INCLUDING  WITHOUT  LIMITATION,  ANY  WARRANTY  OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A  PARTICULAR  PURPOSE.
IN NO EVENT SHALL MICROCHIP OR  ITS  LICENSORS  BE  LIABLE  OR  OBLIGATED  UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,  BREACH  OF  WARRANTY,  OR
OTHER LEGAL  EQUITABLE  THEORY  ANY  DIRECT  OR  INDIRECT  DAMAGES  OR  EXPENSES
INCLUDING BUT NOT LIMITED TO ANY  INCIDENTAL,  SPECIAL,  INDIRECT,  PUNITIVE  OR
CONSEQUENTIAL DAMAGES, LOST  PROFITS  OR  LOST  DATA,  COST  OF  PROCUREMENT  OF
SUBSTITUTE  GOODS,  TECHNOLOGY,  SERVICES,  OR  ANY  CLAIMS  BY  THIRD   PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE  THEREOF),  OR  OTHER  SIMILAR  COSTS.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef _USB_HOST_CDC_LOCAL_H
#define _USB_HOST_CDC_LOCAL_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "usb/usb_host.h"
#include "usb/src/usb_host_local.h"
#include "usb/usb_host_cdc.h"


// Requests current DTE rate, stop-bits, parity, and number-of-character bits.
#define USB_CDC_GET_LINE_CODING             0x21

/* Number of bytes Line Coding transfer */
#define USB_CDC_LINE_CODING_LENGTH          0x07

// Configures DTE rate, stop-bits, parity, and number-of-character bits.
#define USB_CDC_SET_LINE_CODING             0x20

// [V24] signal used to tell the DCE device the DTE device is now present.
#define USB_CDC_SET_CONTROL_LINE_STATE      0x22
 /* Number of bytes Control line transfer */
#define USB_CDC_CONTROL_LINE_LENGTH         0x00
#define USB_CDC_SEND_BREAK                  0x23    // Sends special carrier modulation used to specify [V24] style break.


#define SEND_VENDER_COMMANDS                      0x40 //TODO temp

#define CDC_STATE_MASK                            0x000F
#define CDC_STATE_DETACHED                        0x0001
#define CDC_STATE_INITIALIZE_DEVICE               0x0002 //
#define CDC_STATE_RUNNING                        0x0003
#define CDC_STATE_HOLDING                        0x0004

#define CDC_SUBSTATE_MASK                            0x00F0

#define SUBSTATE_GET_LINE_CODING                  0x0010 //
#define SUBSTATE_WAIT_FOR_GET_LINE_CODING         0x0020 //
#define SUBSTATE_WAIT_FOR_SET_LINE_CODING         0x0030 //
#define SUBSTATE_SET_LINE_CODING                  0x0040
#define SUBSTATE_SET_CONTROL_LINE_STATE           0x0050 //
#define SUBSTATE_WAIT_FOR_SET_CONTROL_LINE_STATE  0x0060
#define SUBSTATE_WAITING_FOR_REQ                  0x0070 //
#define SUBSTATE_SEND_READ_REQ                    0x0080 //
#define SUBSTATE_READ_REQ_WAIT                    0x0090 //
#define SUBSTATE_SEND_WRITE_REQ                   0x00a0 //
#define SUBSTATE_WRITE_REQ_WAIT                   0x00b0 //
#define SUBSTATE_SEND_RESET                       0x00c0 //
#define SUBSTATE_WAIT_FOR_RESET                   0x00d0 //
#define SUBSTATE_RESET_COMPLETE                   0x00e0 //




#define  CONTROL_OUT_REQUEST    0x01
#define  CONTROL_IN_REQUEST     0x02
#define  BULKIN_REQUEST         0x03
#define  BULKOUT_REQUEST        0x04
#define  INTERRUPT_REQUEST      0x05
// Device Request code to reset the device
#define USB_CDC_RESET           (0xFF)
#define MARK_RESET_RECOVERY     (0x0E)  
// *****************************************************************************

/* USB HOST CDC Function Driver data structer

  Summary:
    USB HOST CDC Function Driver information

  Description:
    This structer has the details about USB HOST CDC Function Driver info
    event handler function , states of device , instance , pipes info
    contain all the information about the device driver.

  Remarks:
    None.
 */


typedef struct _USB_HOST_CDC_DRIVER_INFO_ {
    /* use or not*/
    uint8_t assigned;
    /* cdc driver state for state machine */
    uint8_t cdcState;
    /* instance number */
    uint8_t instanceNumber;
    uint8_t interfaceNumber;
    /* data interface */
    uint8_t datainterfaceNumber;
    /* communication interface*/
    uint8_t communicationInterfaceNumber;
    /* hcid + device id */
    HC_DEVICE_ID cdcDeviceId;
    /* IRPS for each endpoint */
    USB_HOST_IRP controlIRP;
    USB_HOST_IRP bulkinIRP;
    USB_HOST_IRP bulkoutIRP;
    USB_HOST_IRP interruptinIRP;
    /*Pipes for each endpoint */
    USB_HOST_PIPE_HANDLE controlpipeHandle;
    USB_HOST_PIPE_HANDLE bulkinpipeHandle;
    USB_HOST_PIPE_HANDLE bulkoutpipeHandle;
    USB_HOST_PIPE_HANDLE interruptinpipeHandle;
    /*Rx handle */
    USB_HOST_CDC_TRANSFER_HANDLE rxHandle;
    /*Tx handle */
    USB_HOST_CDC_TRANSFER_HANDLE txHandle;
    /* CDC command */
    uint8_t cdcCommand;
    uint8_t cdcReportLenth;
    uint8_t *data;
    uint8_t bytesTransfered;
    uint8_t request;
    /* setup packet information */
    uint8_t setupPacket[8];
    /*Ready for the transmit data */
    uint8_t deviceReady;
    /*connectd CDC devices*/
    uint8_t cdcConnectedDevices;
    /* Application callback */
    USB_HOST_CDC_EVENT_HANDLER appEventCallBack;

    uintptr_t context;

} USB_HOST_CDC_DRIVER_INFO;


/*************************************************************************/
/* Function:
   USB_HOST_STATUS      USB_HOST_CDC_InterfaceInitialize( HC_DEVICE_ID id ,
                                                       uint8_t interfaceId,
                                                       uint8_t *cdcinstance
													   uint8_t speed)
  Summary:
    Initialize the CDC host driver.

  Description:
    After enumeration Host will initialize the CDC driver.
    Application should not call this function

  Parameters:
     HC_DEVICE_ID                           id ,
     uint8_t                                interfaceId,
     uint8_t *                              cdcinstance

  Returns:
    None
*/
       /*Host Layer will call after Enumeration */
USB_ERROR      USB_HOST_CDC_InterfaceInitialize( HC_DEVICE_ID id ,
                                                       uint8_t interfaceId,
                                                       uint8_t *cdcinstance,
													   uint8_t  speed);

/*************************************************************************/

/* Function:
   void USB_HOST_CDC_Tasks(void)

  Summary:
        USB HOST CDC state machine
       USB Host layer calls the function driver tasks in this function.
    It also generates and forwards events to its clients.

  Description:
         This function be periodically called by the host layer.It also generates
    and forwards events to its clients.
    Application should not call this function

  Parameters:
        None

  Returns:
        None
*/
void USB_HOST_CDC_Tasks(void);

/*************************************************************************/

/* Function:
   void  USB_HOST_CDC_DeInitialize(HC_DEVICE_ID id )

  Summary:
    DeInitialize the CDC host driver.

  Description:
    After deenumeration Host will Deinitialize the CDC driver.
    Application should not call this function

  Parameters:
     HC_DEVICE_ID                           id ,

  Returns:
        void
*/

void  USB_HOST_CDC_DeInitialize(HC_DEVICE_ID id );
/*************************************************************************/
/* Function:
   void USB_HOST_CDC_Initbuffers(void))
  Summary:
    Initialize the defult values for the CDC device.
  Description:

  Parameters:
      None

  Returns:
    None
*/
void _USB_HOST_CDC_Initbuffers();
/*************************************************************************/

/* Function:
   _USB_HOST_CDC_findInstance(HC_DEVICE_ID id )

  Summary:
    Find the CDC instance

  Description:

  Parameters:
      HC_DEVICE_ID id

  Returns:
    uint8_t           instance
*/

uint8_t  _USB_HOST_CDC_findInstance(HC_DEVICE_ID id );


/*************************************************************************/

/* Function:
   _USB_HOST_CDC_ControlTransferComplete( USB_HOST_IRP *irp)

  Summary:
        Call back function for controltransfer status

  Description:


  Parameters:
      USB_HOST_IRP *irp

  Returns:
   void
*/
 void  _USB_HOST_CDC_ControlTransferComplete( USB_HOST_IRP *irp);

  /*************************************************************************/

/* Function:
   uint8_t _USB_HOST_CDC_BulkInTransferComplete(USB_HOST_IRP *irp)

  Summary:
        Call back function for Bulkin IRP status

  Description:


  Parameters:
        USB_HOST_IRP *irp

  Returns:
        None
*/

 uint8_t _USB_HOST_CDC_BulkInTransferComplete(USB_HOST_IRP *irp);

  /*************************************************************************/

/* Function:
   uint8_t _USB_HOST_CDC_BulkOutTransferComplete(USB_HOST_IRP *irp)

  Summary:
        Call back function for Bulkout IRP status

  Description:


  Parameters:
        USB_HOST_IRP *irp

  Returns:
        None
*/
void _USB_HOST_CDC_BulkOutTransferComplete( USB_HOST_IRP *irp);
  /*************************************************************************/

/* Function:
   uint8_t _USB_HOST_CDC_InterruptInTransferComplete(USB_HOST_IRP *irp)

  Summary:
        Call back function for Interrupt in IRP status

  Description:


  Parameters:
        USB_HOST_IRP *irp

  Returns:
        None
*/
void _USB_HOST_CDC_InterruptInTransferComplete( USB_HOST_IRP *irp);

  /*************************************************************************/

/* Function:
    uint8_t USB_HOST_CDC_DeviceDetect())

  Summary:
    Number of CDC devices connected

  Description:


  Parameters:


  Returns:
       uint8_t        count
*/
 uint8_t USB_HOST_CDC_DeviceDetect();

 USB_HOST_DRIVER cdcDriver;

#endif

 /************ End of file *************************************/
