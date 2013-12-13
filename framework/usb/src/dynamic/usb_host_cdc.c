/*******************************************************************************
 USB CDC HOST Class Driver

  Company:
    Microchip Technology Inc.

  File Name:
    usb_host_cdc.c

  Summary:
    USB CDC Host class driver.

  Description:
    USB CDC Host class driver.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
 Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

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

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include "system_config.h"
#include "usb/usb_host.h"
#include "usb/src/usb_host_local.h"
#include "usb/usb_host_cdc.h"
#include "usb/src/usb_host_cdc_local.h"
#include "usb/usb_cdc.h"


USB_HOST_CDC_DRIVER_INFO  gcdcDriverObj[USB_HOST_CDC_INSTANCES];

USB_HOST_DRIVER cdcDriver =
{
    /*name of the driver */
    .driverName =  "CDC ",
    .initializeDeviceDriver = NULL ,
    .initializeInterfaceDriver = USB_HOST_CDC_InterfaceInitialize ,
    .deInitializeDriver = USB_HOST_CDC_DeInitialize ,
    .matchFlag       = USB_MATCH_CLASS ,
    .task           = USB_HOST_CDC_Tasks

};


/*************************************************************************/

/* Function:
   USB_HOST_STATUS      USB_HOST_CDC_InterfaceInitialize( HC_DEVICE_ID id ,
                                                       uint8_t interfaceId,
                                                       uint8_t *cdcinstance,
													   uint8_t speed)

  Summary:
    Initialize the CDC host driver.

  Description:
    After enumeration (set_Configuration )Host will initialize the CDC driver

  Parameters:
     HC_DEVICE_ID                           id ,
     uint8_t                                interfaceId,
     uint8_t *                              cdcinstance

  Returns:
    None
*/
 USB_ERROR      USB_HOST_CDC_InterfaceInitialize( HC_DEVICE_ID id ,
                                                       uint8_t interfaceId,
                                                       uint8_t *cdcinstance,
													   uint8_t speed)
{
    USB_HOST_DRIVER_QUERY  cdcQuery;
    USB_HOST_STATUS  status;
    USB_INTERFACE_DESCRIPTOR *interfaceDesc;
    USB_ENDPOINT_DESCRIPTOR *bulkInendPointDesc ,
                            *bulkOutendPointDesc ,
                            *interruptInendPointDesc ;
    USB_ENDPOINT_DESCRIPTOR controlendPointDesc;
    uint8_t    protocol;
    uint8_t    subClass;
    USB_HOST_CDC_DRIVER_INFO *cdcDriverInfo;
    uint8_t     count;

    /* Find the free space for CDC instance*/
    for(count = 0 ; count < USB_HOST_CDC_INSTANCES ; count ++)
    {
        cdcDriverInfo = &(gcdcDriverObj[count]);
        if (cdcDriverInfo->assigned == 0x00 )
            break;
    }
    /* Validate the instance*/
    if ( count >= USB_HOST_CDC_INSTANCES)
    {
        return USB_HOST_MAX_INSTANCES_INVALID;
    }
    
    //  *cdcinstance = count;
    cdcDriverInfo->assigned = 1;
    cdcDriverInfo->cdcDeviceId = id;
    cdcDriverInfo->instanceNumber = count;
    cdcDriverInfo->interfaceNumber = interfaceId;

    cdcQuery.id = id;
    /* active configuration number will change after*/
    cdcQuery.configurationNumber = 0;
    cdcQuery.interfaceClass = 0x02;
    cdcQuery.interfaceSubClass = 0x02;
    cdcQuery.interfaceProtocol = 0x01;
    /* class match */
    cdcQuery.flags = USB_MATCH_CLASS;
    cdcQuery.interfaceNumber = interfaceId;
    cdcQuery.alternateSettingNumber = 0;
    // multiple interfaces
    cdcDriverInfo->communicationInterfaceNumber = 0;
    cdcDriverInfo->datainterfaceNumber = 1;
    /* find alternate setting of interface */
    status = USB_HOST_FindInterface(&(cdcQuery), &(interfaceDesc));
    subClass = interfaceDesc->bInterfaceSubClass;
    protocol = interfaceDesc->bInterfaceProtocol;
     /* supporting only ACM protocol */
    if (protocol != USB_CDC_PROTOCOL_AT_V250 &&
            subClass != USB_CDC_SUBCLASS_ABSTRACT_CONTROL_MODEL)
    {
        return USB_ERROR_HOST_DRIVER_NOT_FOUND;
    }
    cdcQuery.alternateSettingNumber++;
    /* InterruptIn */
    cdcQuery.alternateSettingNumber = interfaceDesc->bAlternateSetting;
    cdcQuery.endpointAddress = 0 ; // we have to get temp
    cdcQuery.endpointType = 3;
    cdcQuery.endpointDirection = USB_DATA_DIRECTION_DEVICE_TO_HOST ;
    cdcQuery.flags = USB_MATCH_ENDPOINT_TYPE | USB_MATCH_ENDPOINT_DIRECTION;
    /* Find the Interrupt endpoint descriptor */
    status = USB_HOST_FindEndpoint (&(cdcQuery), &(interruptInendPointDesc));
    /* Create Interrupt pipe */
    cdcDriverInfo->interruptinpipeHandle = USB_HOST_PipeSetup (
                                id ,  interruptInendPointDesc ,speed );
    /* Fill Interrupt IRP*/
    cdcDriverInfo->interruptinIRP.callback =
                                    _USB_HOST_CDC_InterruptInTransferComplete;
    cdcDriverInfo->interruptinIRP.status = USB_HOST_IRP_STATUS_PENDING;
    cdcDriverInfo->interruptinIRP.size = 64 ;
     cdcDriverInfo->interruptinIRP.userData = (uintptr_t)cdcDriverInfo;
    /* Get control pipe information */
    controlendPointDesc.bmAttributes =  (USB_TRANSFER_TYPE_CONTROL )& 0x03;
    cdcDriverInfo->controlpipeHandle =  USB_HOST_PipeSetup
                                ( id ,  &controlendPointDesc , speed );
    /* Fill Control IRP */
    cdcDriverInfo->controlIRP.callback = _USB_HOST_CDC_ControlTransferComplete;
    cdcDriverInfo->controlIRP.status  = USB_HOST_IRP_STATUS_PENDING;
     cdcDriverInfo->controlIRP.userData = (uintptr_t)cdcDriverInfo;
    /* Fine bulkIn endpoint descriptor */
    cdcQuery.alternateSettingNumber = interfaceDesc->bAlternateSetting;
    cdcQuery.endpointAddress = 0 ; // we have to get temp
    cdcQuery.endpointType = 2;
    cdcQuery.endpointDirection = USB_DATA_DIRECTION_DEVICE_TO_HOST;
    cdcQuery.interfaceNumber = cdcDriverInfo->datainterfaceNumber;
    cdcQuery.flags = USB_MATCH_ENDPOINT_TYPE | USB_MATCH_ENDPOINT_DIRECTION;
    status = USB_HOST_FindEndpoint (&(cdcQuery), &(bulkInendPointDesc));
    /* Create Bulkin pipe */
    cdcDriverInfo->bulkinpipeHandle = USB_HOST_PipeSetup
                                ( id ,  bulkInendPointDesc , speed );
    /* Fill Bulkin IRP */
    cdcDriverInfo->bulkinIRP.callback =
                            (void * )_USB_HOST_CDC_BulkInTransferComplete;
    cdcDriverInfo->bulkinIRP.status = USB_HOST_IRP_STATUS_PENDING;
    cdcDriverInfo->bulkinIRP.size = 64 ;
    cdcDriverInfo->bulkinIRP.userData = (uintptr_t)cdcDriverInfo;
     /* Fill the cdcQuery to find bulkOut endpoint */
    cdcQuery.alternateSettingNumber = interfaceDesc->bAlternateSetting;
    cdcQuery.endpointAddress = 0 ; // we have to get temp
    cdcQuery.endpointType = 2;
    cdcQuery.endpointDirection = USB_DATA_DIRECTION_HOST_TO_DEVICE;
    cdcQuery.flags = USB_MATCH_ENDPOINT_TYPE | USB_MATCH_ENDPOINT_DIRECTION;
    /* Find the bulkout endpoint descriptor */
    status = USB_HOST_FindEndpoint (&(cdcQuery), &(bulkOutendPointDesc));
    /* Create Bulkout pipe */
    cdcDriverInfo->bulkoutpipeHandle = USB_HOST_PipeSetup
                                ( id ,  bulkOutendPointDesc ,speed);
    /* Fill Bulk out piep */
    cdcDriverInfo->bulkoutIRP.callback = _USB_HOST_CDC_BulkOutTransferComplete;
    cdcDriverInfo->bulkoutIRP.status = USB_HOST_IRP_STATUS_PENDING;
    cdcDriverInfo->bulkoutIRP.size = 64 ;
    cdcDriverInfo->bulkoutIRP.userData = (uintptr_t )cdcDriverInfo;
    /* State the default state for cdc device */
    cdcDriverInfo->cdcState =  CDC_STATE_INITIALIZE_DEVICE ;
    /* Sent attach event to the application */
    cdcDriverInfo->appEventCallBack(cdcDriverInfo->instanceNumber,
      USB_HOST_CDC_EVENT_ATTACH,&(cdcDriverInfo->cdcDeviceId.deviceID),
                                    cdcDriverInfo->context);
    return status;
}


/*************************************************************************/

/* Function:
   void  USB_HOST_CDC_DeInitialize(HC_DEVICE_ID id )

  Summary:
    DeInitialize the CDC host driver.

  Description:
    After deenumeration Host will Deinitialize the CDC driver

  Parameters:
     HC_DEVICE_ID                           id ,

  Returns:
        void
*/

void  USB_HOST_CDC_DeInitialize ( HC_DEVICE_ID id )
 {
      USB_HOST_CDC_DRIVER_INFO *cdcDriverInfo;
      uint8_t cdcInstance;
      /* Find CDC instance */
      cdcInstance = _USB_HOST_CDC_findInstance( id );
      /* CDC Driver info */
      cdcDriverInfo = &(gcdcDriverObj[cdcInstance]);
      /* inform to the cdc device detach event to the application */
      cdcDriverInfo->appEventCallBack(cdcDriverInfo->instanceNumber,
                                USB_HOST_CDC_EVENT_DETACH,
                                &(cdcDriverInfo->cdcDeviceId.deviceID),
                                  cdcDriverInfo->context);
      /* Close CDC device related pipes */
      USB_HOST_PipeClose( cdcDriverInfo->bulkinpipeHandle );
      USB_HOST_PipeClose( cdcDriverInfo->bulkoutpipeHandle );
      USB_HOST_PipeClose( cdcDriverInfo->interruptinpipeHandle );
      /* change function driver state */
      /* close the instance */
      cdcDriverInfo->assigned = 0x0;
     // memset(cdcDriverInfo , 0 ,sizeof( USB_HOST_CDC_DRIVER_INFO));
 }
// ***********************************************************************
/* Function:
    USB_HOST_CDC_RESULT USB_HOST_CDC_Read(USB_HOST_CDC_INDEX index,
        USB_HOST_CDC_TRANSFER_HANDLE * transferHandle, void * dest,
        size_t length);

  Summary:
    This function reads data from the attached CDC device.

  Description:
    This function reads data from the attached CDC device. The function will
    schedule a read transfer. If successful, the transferHandle parameter will
    contain a valid transfer handle, else it will contain
    USB_HOST_CDC_TRANSFER_HANDLE_INVALID. When completed, the CDC class driver
    will generate a USB_HOST_CDC_EVENT_READ_COMPLETE event. Multiple read
    requests can be queued. In such a case, the transfer handle for each request
    will be unique.

  Precondition:
    None.

  Parameters:
    index - CDC Class Driver Instance Index where the request should be scheduled.

    transferHandle  - Pointer to USB_HOST_CDC_TRANSFER_HANDLE type of a variable.
                      This will contain a valid transfer handle if the request
                      was successful.

    dest            - pointer to the buffer where the read data will be stored.

    length          - Amount of data to read (in bytes).

  Returns:
    USB_HOST_CDC_RESULT_OK - The operation was successful. transferHandle will
    contain a valid transfer handle.
    USB_HOST_CDC_RESULT_ERROR_INSTANCE_INVALID - The specified instance does
    not exist.
    USB_HOST_CDC_RESULT_ERROR_TRANSFER_QUEUE_FULL - The transfer queue is full
    and the requested transfer cannot be scheduled.
    USB_HOST_CDC_RESULT_ERROR_INSTANCE_NOT_READY - The specified instance does
    not have a CDC device associated with it. This can happen if the attached
    device was disconnected or the read function was called with an CDC class
    driver instance that was not attached to a CDC device.
    USB_HOST_CDC_RESULT_ERROR_PARAMETER_INVALID - The destination buffer pointer
    is NULL or the length parameter is zero.

  Example:
    <code>
    // The following code snippet shows an example of scheduling a CDC Class
    // Driver read. In this example, the class driver reads 64 bytes from the
    // attached device.

    USB_HOST_CDC_TRANSFER_HANDLE transferHandle;
    USB_HOST_CDC_RESULT result;
    uint8_t buffer[64];

    result = USB_HOST_CDC_Read(USB_HOST_CDC_0, &transferHandle, buffer, 64);

    if(USB_HOST_CDC_RESULT_OK != result)
    {
        // Error handling here
    }

    // The completion of the read request can be tracked by using the
    // USB_HOST_CDC_EVENT_READ_COMPLETE.

    </code>

  Remarks:
    None.

 */
 
USB_HOST_CDC_RESULT USB_HOST_CDC_Read
( 
    USB_HOST_CDC_INDEX index,
    USB_HOST_CDC_TRANSFER_HANDLE * transferHandle,
    void * destination,
    size_t length
)
{
    USB_HOST_CDC_DRIVER_INFO *cdcDriverInfo;
    USB_HOST_IRP *irp;
    /* Get CDC driver info*/
    cdcDriverInfo = &gcdcDriverObj[index];
    /* IRP*/
    irp = &(cdcDriverInfo->bulkinIRP);
    /* Transfer handle to get the data*/
    transferHandle = (USB_HOST_CDC_TRANSFER_HANDLE  *)&(cdcDriverInfo->bulkinIRP);
    cdcDriverInfo->rxHandle = ( USB_HOST_CDC_TRANSFER_HANDLE) transferHandle;
    /* Fill IRP*/
    irp->data = destination;
    irp->size = length;
    irp->callback = (void * )_USB_HOST_CDC_BulkInTransferComplete;
    irp->userData = (uintptr_t)cdcDriverInfo;
    /* Set CDC states for to Submit IRP */
    cdcDriverInfo->cdcState = CDC_STATE_RUNNING | SUBSTATE_SEND_READ_REQ ;
    /* return status */
    return USB_HOST_CDC_RESULT_OK;
}

// *****************************************************************************
/* Function:
    USB_HOST_CDC_RESULT USB_HOST_CDC_Write(USB_HOST_CDC_INDEX index,
        USB_HOST_CDC_TRANSFER_HANDLE * transferHandle, void * source,
        size_t length);

  Summary:
    This function writes data to the attached CDC device.

  Description:
    This function writes data to the attached CDC device. The function will
    schedule a write transfer. If successful, the transferHandle parameter will
    contain a valid transfer handle, else it will contain
    USB_HOST_CDC_TRANSFER_HANDLE_INVALID. When completed, the CDC class driver
    will generate a USB_HOST_CDC_EVENT_WRITE_COMPLETE event. Multiple write
    requests can be queued. In such a case, the transfer handle for each request
    will be unique.

  Precondition:
    None.

  Parameters:
    index - CDC Class Driver Instance Index where the request should be scheduled.

    transferHandle  - Pointer to USB_HOST_CDC_TRANSFER_HANDLE type of a variable.
                      This will contain a valid transfer handle if the request
                      was successful.

    source          - pointer to the buffer containing data to be written to the
                      device.

    length          - Amount of data to written (in bytes).

  Returns:
    USB_HOST_CDC_RESULT_OK - The operation was successful. transferHandle will
    contain a valid transfer handle.
    USB_HOST_CDC_RESULT_ERROR_INSTANCE_INVALID - The specified instance does
    not exist.
    USB_HOST_CDC_RESULT_ERROR_TRANSFER_QUEUE_FULL - The transfer queue is full
    and the requested transfer cannot be scheduled.
    USB_HOST_CDC_RESULT_ERROR_INSTANCE_NOT_READY - The specified instance does
    not have a CDC device associated with it. This can happen if the attached
    device was disconnected or the write function was called with an CDC class
    driver instance that was not attached to a CDC device.
    USB_HOST_CDC_RESULT_ERROR_PARAMETER_INVALID - The source buffer pointer
    is NULL or the length parameter is zero.

  Example:
    <code>
    // The following code snippet shows an example of scheduling a CDC Class
    // Driver Write. In this example, the class driver writes 64 bytes to the
    // attached device.

    USB_HOST_CDC_TRANSFER_HANDLE transferHandle;
    USB_HOST_CDC_RESULT result;
    uint8_t buffer[64];

    result = USB_HOST_CDC_Write(USB_HOST_CDC_0, &transferHandle, buffer, 64);

    if(USB_HOST_CDC_RESULT_OK != result)
    {
        // Error handling here
    }

    // The completion of the write request can be tracked by using the
    // USB_HOST_CDC_EVENT_WRITE_COMPLETE.

    </code>

  Remarks:
    None.

*/

USB_HOST_CDC_RESULT USB_HOST_CDC_Write (
                                  USB_HOST_CDC_INDEX index,
                                  USB_HOST_CDC_TRANSFER_HANDLE * transferHandle,
                                  void * source, size_t length)
{
     USB_HOST_CDC_DRIVER_INFO *cdcDriverInfo;
     USB_HOST_IRP *irp;

    /* Get CDC driver info*/
    cdcDriverInfo = &gcdcDriverObj[index];
    irp = &(cdcDriverInfo->bulkoutIRP);
    transferHandle = (USB_HOST_CDC_TRANSFER_HANDLE  *) &(cdcDriverInfo->bulkoutIRP);
    cdcDriverInfo->txHandle = (USB_HOST_CDC_TRANSFER_HANDLE )transferHandle;
    /* Fill IRP */
    irp->data = source;
    irp->size = length;
    irp->callback = _USB_HOST_CDC_BulkOutTransferComplete;
    irp->userData = (uintptr_t)cdcDriverInfo;
     /* Set CDC Task states for to Submit IRP */
    cdcDriverInfo->cdcState = CDC_STATE_RUNNING | SUBSTATE_SEND_WRITE_REQ ;
    return USB_HOST_CDC_RESULT_OK;
}

// *****************************************************************************
/* Function:
    USB_HOST_CDC_RESULT USB_HOST_CDC_LineCodingGet(USB_HOST_CDC_INDEX index,
        USB_HOST_CDC_TRANSFER_HANDLE * transferHandle,
        USB_CDC_LINE_CODING * lineCoding);

  Summary:
    This function requests line coding from the attached CDC device.

  Description:
    This function requests line coding from the attached CDC device. The
    function schedules a GET LINE CODING control transfer.  If successful, the
    transferHandle parameter will contain a valid transfer handle, else it will
    contain USB_HOST_CDC_TRANSFER_HANDLE_INVALID. When completed, the CDC class
    driver will generate a USB_HOST_CDC_EVENT_GET_LINE_CODING_COMPLETE event.
    When completed, the lineCoding parameter will contain the line coding. The
    CDC Class driver does not support queuing of control transfers. If a control
    transfer is in progress, this function will return with an error.

  Precondition:
    None.

  Parameters:
    index - CDC Class Driver Instance Index where the request should be scheduled.

    transferHandle  - Pointer to USB_HOST_CDC_TRANSFER_HANDLE type of a variable.
                      This will contain a valid transfer handle if the request
                      was successful.

    lineCoding      - pointer to the buffer where the line coding data will be
                      stored.

  Returns:
    USB_HOST_CDC_RESULT_OK - The operation was successful. transferHandle will
    contain a valid transfer handle.
    USB_HOST_CDC_RESULT_ERROR_INSTANCE_INVALID - The specified instance does
    not exist.
    USB_HOST_CDC_RESULT_ERROR_TRANSFER_QUEUE_FULL - Another control transfer is
    in progress and this transfer cannot be scheduled.
    USB_HOST_CDC_RESULT_ERROR_INSTANCE_NOT_READY - The specified instance does
    not have a CDC device associated with it. This can happen if the attached
    device was disconnected or the get request was called with an CDC class
    driver instance that was not attached with a CDC device.
    USB_HOST_CDC_RESULT_ERROR_PARAMETER_INVALID - The lineCoding buffer pointer
    is NULL.

  Example:
    <code>
    // The following code snippet shows an example of scheduling a CDC Class
    // Driver Get Line Coding Request.

    USB_HOST_CDC_TRANSFER_HANDLE transferHandle;
    USB_HOST_CDC_RESULT result;
    USB_CDC_LINE_CODING * buffer;

    result = USB_HOST_CDC_LineCodingGet(USB_HOST_CDC_0,
                                        &transferHandle, buffer);

    if(USB_HOST_CDC_RESULT_OK != result)
    {
        // Error handling here
    }

    // The completion of the get request can be tracked by using the
    // USB_HOST_CDC_EVENT_GET_LINE_CODING_COMPLETE event.

    </code>

  Remarks:
    None.

*/
USB_HOST_CDC_RESULT USB_HOST_CDC_LineCodingGet ( USB_HOST_CDC_INDEX index,
                                USB_HOST_CDC_TRANSFER_HANDLE * transferHandle,
                                USB_CDC_LINE_CODING * lineCoding)
{
     USB_HOST_CDC_DRIVER_INFO *cdcDriverInfo;
     USB_HOST_IRP *irp;

     /* Get CDC driver info*/
     cdcDriverInfo = &gcdcDriverObj[index];
     irp = &(cdcDriverInfo->bulkoutIRP);
     /* Transfer handle for Application*/
     transferHandle = (USB_HOST_CDC_TRANSFER_HANDLE  *)&(cdcDriverInfo->controlIRP);
     cdcDriverInfo->rxHandle = ( USB_HOST_CDC_TRANSFER_HANDLE) transferHandle;
    /*Fill setup packet */
    cdcDriverInfo->setupPacket[0] = USB_SETUP_DIRN_DEVICE_TO_HOST |
                                    USB_SETUP_TYPE_CLASS |
                                    USB_SETUP_RECIPIENT_INTERFACE;
    cdcDriverInfo->setupPacket[1] = USB_CDC_GET_LINE_CODING;
    cdcDriverInfo->setupPacket[2] = 0;
    cdcDriverInfo->setupPacket[3] = 0;
    cdcDriverInfo->setupPacket[4] = 0;
    // communication interface
    cdcDriverInfo->setupPacket[5] = cdcDriverInfo->interfaceNumber;
    cdcDriverInfo->setupPacket[6] = USB_CDC_LINE_CODING_LENGTH;
    cdcDriverInfo->setupPacket[7] = 0;
    /* Data Buffer for get line code */
    cdcDriverInfo->controlIRP.data = (uint8_t *) lineCoding;
    cdcDriverInfo->controlIRP.setup = cdcDriverInfo->setupPacket;
    cdcDriverInfo->controlIRP.size = USB_CDC_LINE_CODING_LENGTH;
    /* set the CDC Task states for submit IRP*/
    cdcDriverInfo->cdcState = CDC_STATE_INITIALIZE_DEVICE |
                              SUBSTATE_GET_LINE_CODING;
    return USB_HOST_CDC_RESULT_OK;
  }

// *****************************************************************************
/* Function:
    USB_HOST_CDC_RESULT USB_HOST_CDC_LineCodingSet(USB_HOST_CDC_INDEX index,
        USB_HOST_CDC_TRANSFER_HANDLE * transferHandle,
        USB_CDC_LINE_CODING * lineCoding);

  Summary:
    This function sets the line coding of the attached CDC device.

  Description:
    This function sets the line coding of the attached CDC device. The function
    schedules a SET LINE CODING control transfer.  If successful, the
    transferHandle parameter will contain a valid transfer handle, else it will
    contain USB_HOST_CDC_TRANSFER_HANDLE_INVALID. When completed, the CDC class
    driver will generate a USB_HOST_CDC_EVENT_SET_LINE_CODING_COMPLETE event.
    The lineCoding parameter contain the line coding to be sent to the attached
    device. The CDC Class driver does not support queuing of control transfers.
    If a control transfer is in progress, this function will return with an
    error.

  Precondition:
    None.

  Parameters:
    index - CDC Class Driver Instance Index where the request should be scheduled.

    transferHandle  - Pointer to USB_HOST_CDC_TRANSFER_HANDLE type of a variable.
                      This will contain a valid transfer handle if the request
                      was successful.

    lineCoding      - pointer to the buffer containing line coding data to be
                      sent to the device

  Returns:
    USB_HOST_CDC_RESULT_OK - The operation was successful. transferHandle will
    contain a valid transfer handle.
    USB_HOST_CDC_RESULT_ERROR_INSTANCE_INVALID - The specified instance does
    not exist.
    USB_HOST_CDC_RESULT_ERROR_TRANSFER_QUEUE_FULL - Another control transfer is
    in progress and this transfer cannot be scheduled.
    USB_HOST_CDC_RESULT_ERROR_INSTANCE_NOT_READY - The specified instance does
    not have a CDC device associated with it. This can happen if the attached
    device was disconnected or the set request was called with an CDC class
    driver instance that was not attached with a CDC device.
    USB_HOST_CDC_RESULT_ERROR_PARAMETER_INVALID - The lineCoding buffer pointer
    is NULL.

  Example:
    <code>
    // The following code snippet shows an example of scheduling a CDC Class
    // Driver Set Line Coding Request.

    USB_HOST_CDC_TRANSFER_HANDLE transferHandle;
    USB_HOST_CDC_RESULT result;
    USB_CDC_LINE_CODING * buffer;

    result = USB_HOST_CDC_LineCodingSet(USB_HOST_CDC_0,
                                        &transferHandle, buffer);

    if(USB_HOST_CDC_RESULT_OK != result)
    {
        // Error handling here
    }

    // The completion of the set request can be tracked by using the
    // USB_HOST_CDC_EVENT_SET_LINE_CODING_COMPLETE event.

    </code>

  Remarks:
    None.

*/


USB_HOST_CDC_RESULT USB_HOST_CDC_LineCodingSet ( USB_HOST_CDC_INDEX index,
                            USB_HOST_CDC_TRANSFER_HANDLE * transferHandle,
                            USB_CDC_LINE_CODING * lineCoding)
{
    USB_HOST_CDC_DRIVER_INFO *cdcDriverInfo;
    /* Get CDC driver info*/
    cdcDriverInfo = &gcdcDriverObj[index];
    /* Transfer Handle*/
    transferHandle = (USB_HOST_CDC_TRANSFER_HANDLE *)&(cdcDriverInfo->controlIRP);
    cdcDriverInfo->rxHandle = (USB_HOST_CDC_TRANSFER_HANDLE) transferHandle;
    /* Fill Setup packet */
    cdcDriverInfo->setupPacket[0] = USB_SETUP_DIRN_HOST_TO_DEVICE |
                                    USB_SETUP_TYPE_CLASS |
                                    USB_SETUP_RECIPIENT_INTERFACE;
    cdcDriverInfo->setupPacket[1] = USB_CDC_SET_LINE_CODING;
    cdcDriverInfo->setupPacket[2] = 0;
    cdcDriverInfo->setupPacket[3] = 1; /* Type */
    cdcDriverInfo->setupPacket[4] = 0;
    /* communication interface */
    cdcDriverInfo->setupPacket[5] =
                            cdcDriverInfo->communicationInterfaceNumber;
    cdcDriverInfo->setupPacket[6] = USB_CDC_LINE_CODING_LENGTH;
    cdcDriverInfo->setupPacket[7] = 0;
    /* Fill control irp */
    cdcDriverInfo->controlIRP.data = (uint8_t *) lineCoding;
    cdcDriverInfo->controlIRP.setup = cdcDriverInfo->setupPacket;
    cdcDriverInfo->controlIRP.size = USB_CDC_LINE_CODING_LENGTH;
    /* Set CDC states for submit IRP */
    cdcDriverInfo->cdcState = CDC_STATE_INITIALIZE_DEVICE |
                              SUBSTATE_SET_LINE_CODING;
    return USB_HOST_CDC_RESULT_OK;
}

// *****************************************************************************
/* Function:
    USB_HOST_CDC_RESULT USB_HOST_CDC_ControlLineStateSet ( USB_HOST_CDC_INDEX index,
                        USB_HOST_CDC_TRANSFER_HANDLE * transferHandle,
                        USB_CDC_CONTROL_LINE_STATE * controlLineState)
  Summary:
    This function sets the control line state of the attached CDC device.

  Description:
    This function sets the control line state of the attached CDC device.
    The function schedules a SET CONTROL LINE control transfer.  If successful, the
    transferHandle parameter will contain a valid transfer handle, else it will
    contain USB_HOST_CDC_TRANSFER_HANDLE_INVALID. When completed, the CDC class
    driver will generate a USB_HOST_CDC_EVENT_SET_CONTROL_LINE_STATE_COMPLETE event.
    The lineCoding parameter contain the line coding to be sent to the attached
    device. The CDC Class driver does not support queuing of control transfers.
    If a control transfer is in progress, this function will return with an
    error.

  Precondition:
    None.

  Parameters:
    index - CDC Class Driver Instance Index where the request should be scheduled.

    transferHandle  - Pointer to USB_HOST_CDC_TRANSFER_HANDLE type of a variable.
                      This will contain a valid transfer handle if the request
                      was successful.

    lineCoding      - pointer to the buffer containing line coding data to be
                      sent to the device

  Returns:
    USB_HOST_CDC_RESULT_OK - The operation was successful. transferHandle will
    contain a valid transfer handle.
    USB_HOST_CDC_RESULT_ERROR_INSTANCE_INVALID - The specified instance does
    not exist.
    USB_HOST_CDC_RESULT_ERROR_TRANSFER_QUEUE_FULL - Another control transfer is
    in progress and this transfer cannot be scheduled.
    USB_HOST_CDC_RESULT_ERROR_INSTANCE_NOT_READY - The specified instance does
    not have a CDC device associated with it. This can happen if the attached
    device was disconnected or the set request was called with an CDC class
    driver instance that was not attached with a CDC device.
    USB_HOST_CDC_RESULT_ERROR_PARAMETER_INVALID - The lineCoding buffer pointer
    is NULL.

  Example:
    <code>
    // The following code snippet shows an example of scheduling a CDC Class
    // Driver Set Line Coding Request.

    USB_HOST_CDC_TRANSFER_HANDLE transferHandle;
    USB_HOST_CDC_RESULT result;
    USB_CDC_CONTROL_LINE_STATE * controlLineState;

    result = USB_HOST_CDC_ControlLineStateSet(USB_HOST_CDC_0,
                                        &transferHandle, controlLineState);

    if(USB_HOST_CDC_RESULT_OK != result)
    {
        // Error handling here
    }

    // The completion of the set request can be tracked by using the
    // USB_HOST_CDC_EVENT_SET_LINE_CODING_COMPLETE event.

    </code>

  Remarks:
    None.

*/
USB_HOST_CDC_RESULT USB_HOST_CDC_ControlLineStateSet ( USB_HOST_CDC_INDEX index,
                        USB_HOST_CDC_TRANSFER_HANDLE * transferHandle,
                        USB_CDC_CONTROL_LINE_STATE * controlLineState) {
    USB_HOST_CDC_DRIVER_INFO *cdcDriverInfo;
    // USB_HOST_IRP *irp;

    /* Get CDC driver info*/
    cdcDriverInfo = &gcdcDriverObj[index];
    transferHandle = (USB_HOST_CDC_TRANSFER_HANDLE *)
            &(cdcDriverInfo->bulkoutIRP);
    cdcDriverInfo->txHandle = (USB_HOST_CDC_TRANSFER_HANDLE) transferHandle;

    cdcDriverInfo->setupPacket[0] = USB_SETUP_DIRN_HOST_TO_DEVICE |
            USB_SETUP_TYPE_CLASS |
            USB_SETUP_RECIPIENT_INTERFACE;
    cdcDriverInfo->setupPacket[1] = USB_CDC_SET_CONTROL_LINE_STATE;
    cdcDriverInfo->setupPacket[2] = 0;
    cdcDriverInfo->setupPacket[3] =
            *(uint8_t *) controlLineState;
    cdcDriverInfo->setupPacket[4] = 0;
    // communication interface
    cdcDriverInfo->setupPacket[5] = cdcDriverInfo->interfaceNumber;
    cdcDriverInfo->setupPacket[6] = USB_CDC_CONTROL_LINE_LENGTH;
    cdcDriverInfo->setupPacket[7] = 0;
    /* Fill irp */
    cdcDriverInfo->controlIRP.data =
            (uint8_t *) controlLineState;
    cdcDriverInfo->controlIRP.setup = cdcDriverInfo->setupPacket;
    cdcDriverInfo->controlIRP.size = USB_CDC_CONTROL_LINE_LENGTH;
    /* Set CDC Task state for submit IRP */
    cdcDriverInfo->cdcState = CDC_STATE_INITIALIZE_DEVICE |
                              SUBSTATE_SET_CONTROL_LINE_STATE;
    return USB_HOST_CDC_RESULT_OK;

}
/**********************************************************************/
USB_HOST_CDC_RESULT USB_HOST_CDC_SerialStateNotificationGet
        (USB_HOST_CDC_INDEX index, USB_HOST_CDC_TRANSFER_HANDLE *transferHandle,
         USB_HOST_CDC_SERIAL_STATE_NOTIFICATION_DATA * dest)
{

    /* Support Next release */
    return USB_HOST_CDC_RESULT_OK;
}


/*************************************************************************/

/* Function:
   USB_HOST_CDC_RESULT USB_HOST_CDC_EventHandlerSet (
                                  USB_HOST_CDC_INSTANCE CDCindex ,
                                  USB_HOST_CDC_APP_EVENT_HANDLER appCDCHandler )

  Summary:
        Application will register the handler

  Description:


  Parameters:
    USB_HOST_CDC_INSTANCE               CDCindex ,
    USB_HOST_CDC_APP_EVENT_HANDLER      appCDCHandler
  Returns:
        USB_HOST_CDC_RESULT
*/

USB_HOST_CDC_RESULT USB_HOST_CDC_EventHandlerSet (USB_HOST_CDC_INDEX index,
                                        USB_HOST_CDC_EVENT_HANDLER eventHandler,
                                        uintptr_t context)
{
    /* validate the function driver index */
    if ( ( index < 0 ) || ( index >= USB_HOST_CDC_INSTANCES ) )
    {
        return USB_HOST_CDC_RESULT_ERROR_INSTANCE_INVALID;
    }
    /* validate the event handler */
    if ( eventHandler )
    {
        /* update the event handler for this instance */
        gcdcDriverObj[index].appEventCallBack = eventHandler;
        gcdcDriverObj[index].context = context;
        /* return success */
        return USB_HOST_CDC_RESULT_OK;
    }
    /* Invalid arguments */
    return USB_HOST_CDC_RESULT_ERROR_PARAMETER_INVALID;
}

/*******************************************************************/
USB_HOST_CDC_RESULT USB_HOST_CDC_BreakSend ( USB_HOST_CDC_INDEX index,
                        USB_HOST_CDC_TRANSFER_HANDLE * transferHandle,
                        uint16_t breakDuration)
{
     USB_HOST_CDC_DRIVER_INFO *cdcDriverInfo;
    /* Get CDC driver info*/
    cdcDriverInfo = &gcdcDriverObj[index];
    /* Transfer Handle*/
    transferHandle = (USB_HOST_CDC_TRANSFER_HANDLE *)
                            &(cdcDriverInfo->controlIRP);
    //cdcDriverInfo->txHandle = transferHandle;
    cdcDriverInfo->setupPacket[0] = USB_SETUP_DIRN_HOST_TO_DEVICE |
            USB_SETUP_TYPE_CLASS |
            USB_SETUP_RECIPIENT_INTERFACE;
    cdcDriverInfo->setupPacket[1] = USB_CDC_SEND_BREAK;
    cdcDriverInfo->setupPacket[2] = 0;
    cdcDriverInfo->setupPacket[3] = 2;
    cdcDriverInfo->setupPacket[4] = 0;
    // communication interface
    cdcDriverInfo->setupPacket[5] = cdcDriverInfo->interfaceNumber;
    cdcDriverInfo->setupPacket[6] = USB_CDC_CONTROL_LINE_LENGTH;
    cdcDriverInfo->setupPacket[7] = 0;
    /* Fill irp */
    cdcDriverInfo->controlIRP.data =
            &breakDuration;
    cdcDriverInfo->controlIRP.setup = cdcDriverInfo->setupPacket;
    cdcDriverInfo->controlIRP.size = 2;
    /*Set CDC state for Submit IRP*/
    /* support next release */
    //cdcDriverInfo->cdcState = SUBSTATE_WAIT_FOR_SET_CONTROL_LINE_STATE;
     return USB_HOST_CDC_RESULT_OK;
}

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

uint8_t  _USB_HOST_CDC_findInstance(HC_DEVICE_ID id )
 {
    USB_HOST_CDC_DRIVER_INFO *cdcDriverInfo;
    uint8_t count;
    for (count = 0; count < USB_HOST_CDC_INSTANCES; count++) {
        /*Device info*/
        cdcDriverInfo = &(gcdcDriverObj[count]);
        /* Validate the correct match */
        if (USB_HOST_MATCH_HC_DEVICE_ID(cdcDriverInfo->cdcDeviceId, id)) {
            return count;
        }
    }
    /* Invalid instance */
    return USB_HOST_CDC_RESULT_ERROR_INSTANCE_INVALID;
}



/*************************************************************************/

/* Function:
   void USB_HOST_CDC_Tasks(void)

  Summary:
        State machine of the CDC device

  Description:


  Parameters:
        None

  Returns:
        None
*/

void USB_HOST_CDC_Tasks(void)
{
    uint8_t instance;
    USB_HOST_CDC_DRIVER_INFO *cdcDriverInfo;
    USB_HOST_CDC_EVENT_DATA_READ_COMPLETE readCompleteEventData;
    USB_HOST_CDC_EVENT_DATA_WRITE_COMPLETE writeCompleteEventData;

    /* find instance */
    for (instance = 0; instance < USB_HOST_CDC_INSTANCES; instance++)
    {
        cdcDriverInfo = &(gcdcDriverObj[instance]);
        if (cdcDriverInfo->assigned == 0x00)
            continue;
        /*state */
        switch (cdcDriverInfo->cdcState & CDC_STATE_MASK)
        {
            case CDC_STATE_DETACHED:
                break;
            case CDC_STATE_INITIALIZE_DEVICE:
                if (cdcDriverInfo->cdcDeviceId.deviceID > 0)
                {
                    switch (cdcDriverInfo->cdcState & CDC_SUBSTATE_MASK)
                    {
                        case SUBSTATE_GET_LINE_CODING:
                            USB_HOST_IRPSubmit(cdcDriverInfo->controlpipeHandle,
                                    &(cdcDriverInfo->controlIRP));
                            cdcDriverInfo->cdcState = CDC_STATE_INITIALIZE_DEVICE |
                                SUBSTATE_WAIT_FOR_GET_LINE_CODING;
                            break;
                        case SUBSTATE_WAIT_FOR_GET_LINE_CODING:
                            if (cdcDriverInfo->controlIRP.status ==
                                    USB_HOST_IRP_STATUS_COMPLETED)
                            {
                                cdcDriverInfo->appEventCallBack(
                                        cdcDriverInfo->instanceNumber,
                                        USB_HOST_CDC_EVENT_GET_LINE_CODING_COMPLETE,
                                        (cdcDriverInfo->controlIRP.data),
                                        cdcDriverInfo->context);
                                cdcDriverInfo->cdcState = CDC_STATE_RUNNING;
                            }
                            break;

                        case SUBSTATE_SET_LINE_CODING:
                            cdcDriverInfo->cdcState = CDC_STATE_INITIALIZE_DEVICE |
                                SUBSTATE_WAIT_FOR_SET_LINE_CODING;
                            USB_HOST_IRPSubmit(cdcDriverInfo->controlpipeHandle,
                                    &(cdcDriverInfo->controlIRP));
                            break;

                        case SUBSTATE_WAIT_FOR_SET_LINE_CODING:
                            if (cdcDriverInfo->controlIRP.status ==
                                    USB_HOST_IRP_STATUS_COMPLETED)
                            {
                                cdcDriverInfo->appEventCallBack(
                                        cdcDriverInfo->instanceNumber,
                                        USB_HOST_CDC_EVENT_SET_LINE_CODING_COMPLETE,
                                        (cdcDriverInfo->controlIRP.data),
                                        cdcDriverInfo->context);
                                cdcDriverInfo->cdcState = CDC_STATE_RUNNING;
                            }


                            break;
                        case SUBSTATE_SET_CONTROL_LINE_STATE:
                            cdcDriverInfo->cdcState = CDC_STATE_INITIALIZE_DEVICE |
                                SUBSTATE_WAIT_FOR_SET_CONTROL_LINE_STATE;
                            USB_HOST_IRPSubmit(cdcDriverInfo->controlpipeHandle,
                                    &(cdcDriverInfo->controlIRP));
                            break;

                        case SUBSTATE_WAIT_FOR_SET_CONTROL_LINE_STATE:
                            if (cdcDriverInfo->controlIRP.status ==
                                    USB_HOST_IRP_STATUS_COMPLETED)
                            {
                                cdcDriverInfo->appEventCallBack(
                                        cdcDriverInfo->instanceNumber,
                                        USB_HOST_CDC_EVENT_SET_CONTROL_LINE_STATE_COMPLETE,
                                        (cdcDriverInfo->controlIRP.data),
                                        cdcDriverInfo->context);
                                cdcDriverInfo->cdcState = CDC_STATE_RUNNING;

                            }
                            break;
                        case SUBSTATE_SEND_RESET:
                            cdcDriverInfo->setupPacket[0] =
                                USB_SETUP_DIRN_HOST_TO_DEVICE |
                                USB_SETUP_TYPE_CLASS |
                                USB_SETUP_RECIPIENT_INTERFACE;
                            cdcDriverInfo->setupPacket[1] = USB_CDC_RESET;
                            cdcDriverInfo->setupPacket[2] = 0;
                            cdcDriverInfo->setupPacket[3] = 0; /* Type */
                            cdcDriverInfo->setupPacket[4] = 0;
                            cdcDriverInfo->setupPacket[5] =
                                cdcDriverInfo->interfaceNumber;
                            cdcDriverInfo->setupPacket[6] =
                                cdcDriverInfo->cdcReportLenth;
                            cdcDriverInfo->setupPacket[7] = 0;
                            /* Fill control IRP*/
                            cdcDriverInfo->controlIRP.data = cdcDriverInfo->data;
                            cdcDriverInfo->controlIRP.setup =
                                cdcDriverInfo->setupPacket;
                            cdcDriverInfo->controlIRP.size =
                                cdcDriverInfo->cdcReportLenth;
                            cdcDriverInfo->request = CONTROL_OUT_REQUEST;
                            cdcDriverInfo->cdcState = CDC_STATE_INITIALIZE_DEVICE |
                                SUBSTATE_WAIT_FOR_RESET;
                            USB_HOST_IRPSubmit(cdcDriverInfo->controlpipeHandle,
                                    &(cdcDriverInfo->controlIRP));


                        case SUBSTATE_WAIT_FOR_RESET:

                            if (cdcDriverInfo->controlIRP.status ==
                                    USB_HOST_IRP_STATUS_COMPLETED)
                            {
                                //Reset completed
                                cdcDriverInfo->cdcState = CDC_STATE_RUNNING;
                            }
                            break;
                        default:
                            break;
                    }

                }
                break;
            case CDC_STATE_RUNNING:
                switch (cdcDriverInfo->cdcState & CDC_SUBSTATE_MASK)
                {
                    case SUBSTATE_SEND_READ_REQ:
                        cdcDriverInfo->cdcState = CDC_STATE_RUNNING |
                            SUBSTATE_READ_REQ_WAIT;
                        USB_HOST_IRPSubmit(
                                cdcDriverInfo->bulkinpipeHandle,
                                &(cdcDriverInfo->bulkinIRP));

                        break;
                    case SUBSTATE_READ_REQ_WAIT:

                        if (cdcDriverInfo->bulkinIRP.status <
                                USB_HOST_IRP_STATUS_PENDING)
                        {
                            /* This means the Read IRP has terminated */

                            readCompleteEventData.length = cdcDriverInfo->bulkinIRP.size;
                            readCompleteEventData.transferHandle = cdcDriverInfo->rxHandle;

                            if((cdcDriverInfo->bulkinIRP.status == USB_HOST_IRP_STATUS_COMPLETED)
                                    || (cdcDriverInfo->bulkinIRP.status == USB_HOST_IRP_STATUS_COMPLETED_SHORT))
                            {
                                /* Transfer was successful */
                                readCompleteEventData.transferStatus = USB_HOST_CDC_TRANSFER_STATUS_OK;
                            }
                            else
                            {
                                /* Transfer failed */
                                readCompleteEventData.transferStatus = USB_HOST_CDC_TRANSFER_STATUS_ERROR;
                            }

                            cdcDriverInfo->bytesTransfered =
                                cdcDriverInfo->bulkinIRP.size;
                            cdcDriverInfo->cdcState = CDC_STATE_RUNNING ;
                            cdcDriverInfo->appEventCallBack( cdcDriverInfo->instanceNumber,
                                    USB_HOST_CDC_EVENT_READ_COMPLETE, &readCompleteEventData, cdcDriverInfo->context);
                        }

                        break;
                    case SUBSTATE_SEND_WRITE_REQ:
                        cdcDriverInfo->cdcState = CDC_STATE_RUNNING |
                            SUBSTATE_WRITE_REQ_WAIT;
                        USB_HOST_IRPSubmit(cdcDriverInfo->bulkoutpipeHandle,
                                &(cdcDriverInfo->bulkoutIRP));

                        break;

                    case SUBSTATE_WRITE_REQ_WAIT:
                          if (cdcDriverInfo->bulkoutIRP.status <
                                USB_HOST_IRP_STATUS_PENDING)
                        {

                          /* This means the Read IRP has terminated */

                            writeCompleteEventData.length = cdcDriverInfo->bulkoutIRP.size;
                            writeCompleteEventData.transferHandle = cdcDriverInfo->txHandle;

                        if ((cdcDriverInfo->bulkoutIRP.status ==
                                    USB_HOST_IRP_STATUS_COMPLETED) ||
                                (cdcDriverInfo->bulkoutIRP.status ==
                                 USB_HOST_IRP_STATUS_COMPLETED_SHORT))
                        {
                            
                             /* Transfer was successful */
                                writeCompleteEventData.transferStatus =
                                        USB_HOST_CDC_TRANSFER_STATUS_OK;
                        }
                            else
                            {
                                /* Transfer failed */
                                writeCompleteEventData.transferStatus =
                                        USB_HOST_CDC_TRANSFER_STATUS_ERROR;
                            }
                            cdcDriverInfo->bytesTransfered =
                                cdcDriverInfo->bulkoutIRP.size;
                            cdcDriverInfo->cdcState = CDC_STATE_RUNNING;

                            cdcDriverInfo->appEventCallBack(
                                    cdcDriverInfo->instanceNumber,
                                    USB_HOST_CDC_EVENT_WRITE_COMPLETE,
                                    (cdcDriverInfo->controlIRP.data),
                                    cdcDriverInfo->context);
                        }
                        break;
                }

        }
    }
}

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
 void  _USB_HOST_CDC_ControlTransferComplete( USB_HOST_IRP *irp )
{
     USB_HOST_CDC_DRIVER_INFO *cdcDriverInfo;
     USB_HOST_STATUS status;
     cdcDriverInfo = ((USB_HOST_CDC_DRIVER_INFO *) (irp->userData));
     if(irp->status != USB_HOST_IRP_STATUS_COMPLETED )
    {
        if( irp->status == USB_HOST_IRP_STATUS_ERROR_NAK_TIMEOUT)
        {
            // Timing problem will resend the same packet
        }
        if( irp->status == USB_HOST_IRP_STATUS_ERROR_DATA ||
                 irp->status == USB_HOST_IRP_STATUS_ERROR_BUS )
        {
            // Resend the request
        }
          if( irp->status == USB_HOST_IRP_STATUS_ERROR_STALL)
        {
              status = USB_HOST_ClearEndpointHalt (cdcDriverInfo->cdcDeviceId ,
                      (uint8_t )0 );
            //clear the stall
        }
     }

}
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

 uint8_t _USB_HOST_CDC_BulkInTransferComplete(USB_HOST_IRP *irp)
 {
    USB_HOST_CDC_TRANSFER_HANDLE rxHandle;
    uint16_t data;
    uint8_t cdcInstance;
    static uint8_t errorCount = 0;
    USB_HOST_CDC_DRIVER_INFO *cdcDriverInfo;
    if (irp->status == USB_HOST_IRP_STATUS_COMPLETED || irp->status == USB_HOST_IRP_STATUS_COMPLETED_SHORT)
    {
        cdcDriverInfo = ((USB_HOST_CDC_DRIVER_INFO *) (irp->userData));
        cdcInstance = cdcDriverInfo->instanceNumber;
        rxHandle = cdcDriverInfo->rxHandle;
        data = irp->size;
        /* inform the application */
      //  cdcDriverInfo->appEventCallBack(cdcInstance,
      //                                   USB_HOST_CDC_EVENT_READ_COMPLETE,&data);
        return true; // Bulkin successfull
    }
    else
    {
        //TODO handle error status
        errorCount++;
    }
    return false;
}

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
void _USB_HOST_CDC_BulkOutTransferComplete( USB_HOST_IRP *irp)
{
    USB_HOST_CDC_TRANSFER_HANDLE txHandle;
    uint16_t data;
    uint8_t cdcInstance;
    USB_HOST_CDC_DRIVER_INFO *cdcDriverInfo;
    static uint8_t errorCount = 0;
    if (irp->status == USB_HOST_IRP_STATUS_COMPLETED || irp->status == USB_HOST_IRP_STATUS_COMPLETED_SHORT)
    {
        cdcDriverInfo = ((USB_HOST_CDC_DRIVER_INFO *) (irp->userData));
        cdcInstance = cdcDriverInfo->instanceNumber;
        txHandle = cdcDriverInfo->txHandle;
        data = irp->size;
        /* inform the application */
    //    cdcDriverInfo->appEventCallBack(cdcInstance,
    //                            USB_HOST_CDC_EVENT_WRITE_COMPLETE, &data);
        errorCount = 0; // Bulk out successfull
    }
}

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
void _USB_HOST_CDC_InterruptInTransferComplete( USB_HOST_IRP *irp)
{
     USB_HOST_CDC_DRIVER_INFO *cdcDriverInfo;

    cdcDriverInfo = ((USB_HOST_CDC_DRIVER_INFO *) (irp->userData));
    if(irp->status != USB_HOST_IRP_STATUS_COMPLETED )
    {
        if( irp->status == USB_HOST_IRP_STATUS_ERROR_NAK_TIMEOUT)
        {
            // Timing problem will resend the same packet
        }
        if( irp->status == USB_HOST_IRP_STATUS_ERROR_DATA ||
                 irp->status == USB_HOST_IRP_STATUS_ERROR_BUS )
        {
            // Resend the request
        }
   }
}


/***************  End of  File ************************************/




