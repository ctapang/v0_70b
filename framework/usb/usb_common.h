/*******************************************************************************
  USB Common Defintions File

  Company:
    Microchip Technology Incorported

  FileName:
    usb_common.h 

  Summary:
    USB Common Defintions File

  Description:
    This file contains defintions that are used by various components of the 
    USB stack.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip  Technology  Inc.   All  rights  reserved.

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
//DOM-IGNORE-END

#ifndef _USB_COMMON_H_
#define _USB_COMMON_H_

#include <limits.h>

// *****************************************************************************
/* USB Device IRP Status Enumeration

  Summary:
    Enumerates the possible status options of USB Device IRP.

  Description:
    Enumerates the possible status options of USB Device IRP.

  Remarks:
    The  application   that   schedules   the   IRP   can   check   the   status
    member  of  the  USB  Device   IRP   at   any   time   to   obtain   current
    status of the IRP.
*/

typedef enum
{
    /* USB Device IRP was aborted */
    USB_DEVICE_IRP_STATUS_ABORTED       = -2,
    
    /* An error occurred on the bus when the IRP was being
     * processed */
    USB_DEVICE_IRP_STATUS_ERROR         = -1,
    
    /* The IRP was completed */
    USB_DEVICE_IRP_STATUS_COMPLETED  = 0,
   
    /* The IRP was completed but the amount of
     * data received was less than the requested
     * size */
    USB_DEVICE_IRP_STATUS_COMPLETED_SHORT  = 1,
    
    /* The IRP was completed and the received
     * token was a SETUP token. This is applicable
     * to IRP scheduled on CONTROL endpoint */
    USB_DEVICE_IRP_STATUS_SETUP         = 2,

    /* The IRP is pending in the queue */
    USB_DEVICE_IRP_STATUS_PENDING       = 3,

    /* The IRP is currently being processed */
    USB_DEVICE_IRP_STATUS_IN_PROGRESS   = 4,

   
}
USB_DEVICE_IRP_STATUS;

// *****************************************************************************
/* USB Host IRP Status Enumeration

  Summary:
    Enumerates the possible status options of USB Host IRP.

  Description:
    Enumerates the possible status options of USB Host IRP.

  Remarks:
    The  application that schedules the IRP can check the status
    member of the USB Host IRP at any time to obtain current
    status of the IRP.
*/
typedef enum _USB_HOST_IRP_STATUS
{
    /* IRP was terminated due to an unknown error */
    USB_HOST_IRP_STATUS_ERROR_UNKNOWN = -6,

    /* IRP was terminated by the application */
    USB_HOST_IRP_STATUS_ABORTED = -5,

    /* IRP was terminated due to a bus error */
    USB_HOST_IRP_STATUS_ERROR_BUS = -4,

    /* IRP was terminated due to data error */
    USB_HOST_IRP_STATUS_ERROR_DATA = -3,

    /* IRP was terminated because of a NAK timeout */
    USB_HOST_IRP_STATUS_ERROR_NAK_TIMEOUT = -2,

    /* IRP was terminated because of a STALL */
    USB_HOST_IRP_STATUS_ERROR_STALL = -1,
    
    /* IRP has been completed */
    USB_HOST_IRP_STATUS_COMPLETED = 0,

    /* IRP has been completed but the 
     * amount of data processed was less 
     * than requested. */
    
    USB_HOST_IRP_STATUS_COMPLETED_SHORT = 1,

    /* IRP is waiting in queue */
    USB_HOST_IRP_STATUS_PENDING = 2,
    
    /* IRP is currently being processed */
    USB_HOST_IRP_STATUS_IN_PROGRESS = 3,
   
}
USB_HOST_IRP_STATUS;

// *****************************************************************************
/* USB Device IRP Flags

  Summary:
    USB Device IRP flags enumeration

  Description:
    This enumeration defines the possible flags that can be specified while 
    adding the IRP.

  Remarks:
    Not all flags are applicable in all conditions. Refer to API documentation
    for more details
*/

typedef enum
{
    /* Using this flag indicates that there is no
     * more data pending in the IRP. When data moves
     * from device to host, and if the IRP size is
     * a multiple of endpoint size, specifying this
     * flag sends the ZLP. The size is not a 
     * multiple of endpoint size, no ZLP will be sent. */
    USB_DEVICE_IRP_FLAG_DATA_COMPLETE = 1,

    /* In case of data moving from device to host, and if the
     * size parameter of the IRP is an exact multiple of the
     * endpoint maximum packet size, specifying this flag, does
     * send the ZLP. If the size is less than endpoint size, 
     * specifying this flag will return an error. If the size
     * is more than endpoint size but not a multiple, only
     * endpoitn multiple size of data is sent.*/

    USB_DEVICE_IRP_FLAG_DATA_PENDING = 2
}
USB_DEVICE_IRP_FLAG;

// *****************************************************************************
/* USB Host IRP Flags

  Summary:
    USB Host IRP flags enumeration

  Description:
    This enumeration defines the possible flags that can be specified while 
    adding the IRP.

  Remarks:
    Not all flags are applicable in all conditions. Refer to API documentation
    for more details
*/

typedef enum
{
    /* Does not do anything */
    USB_HOST_IRP_FLAG_NONE = 0,

    /* In case of data moving from host to device, and if the
     * size parameter of the IRP is an exact multiple of the
     * endpoint maximum packet size, specifying this flag sends
     * a Zero Length Packet before the IRP is completed. */

    USB_HOST_IRP_FLAG_SEND_ZLP,

    /* In case of data moving device to host, and if the
     * size parameter of the IRP is an exact multiple of 
     * the endpoint maximum packet size, specifying this 
     * flag will cause the IRP to completed only when the
     * a ZLP was requested and acknowledged and the amount
     * of data was a multiple of endpoint maximum packet size. */
    USB_HOST_IRP_WAIT_FOR_ZLP 

}
USB_HOST_IRP_FLAG;

// *****************************************************************************
/* USB Endpoint and Direction Type

  Summary:
    Defines a type to store Endpoint and Direction. The MSB defines the 
    direction. The lower 4 bits defines the endpoint.

  Description:
    Defines a type to store Endpoint and Direction. The MSB defines the 
    direction. The lower 4 bits defines the endpoint.

  Remarks:
    None.
*/

typedef uint8_t USB_ENDPOINT;

// *****************************************************************************
/* USB Endpoint and Direction helper macro

  Summary:
   This macro helps in setting up the USB_ENDPOINT type. 

  Description:
   This macro helps in setting up the USB_ENDPOINT type. Here 
   x is the direction and can be either USB_DATA_DIRECTION_HOST_TO_DEVICE
   or USB_DATA_DIRECTION_DEVICE_TO_HOST. y is the endpoint.

  Remarks:
    None.
*/

#define USB_ENDPOINT_AND_DIRECTION(x, y) ((uint8_t)((x << 7) | y))


// *****************************************************************************
/* USB Device Mode I/O Request Packet
 
  Summary:
    This structure defines the USB Device Mode IRP data structure.

  Description:
    This structure defines the USB Device Mode IRP data structure.

  Remarks:
    None.
*/

typedef struct _USB_DEVICE_IRP 
{
    /* Pointer to the data buffer */
    void * data;

    /* Size of the data buffer */
    unsigned int size;

    /* Status of the IRP */
    USB_DEVICE_IRP_STATUS status;

    /* IRP Callback. If this is NULL,
     * then there is no callback generated */
    void (*callback)(struct _USB_DEVICE_IRP * irp);

    /* Request specific flags */
    USB_DEVICE_IRP_FLAG flags;

    /* User data */
    uintptr_t userData;

    /***********************************
     * The following members should not
     * be modified by the client
     ***********************************/
    uint32_t privateData[3];
}
USB_DEVICE_IRP;


// *****************************************************************************
/* USB Host Mode I/O Request Packet
 
  Summary:
    This structure defines the USB Host Mode IRP data structure.

  Description:
    This structure defines the USB Host Mode IRP data structure.

  Remarks:
    None.
*/

typedef struct _USB_HOST_IRP
{
    /* Points to the 8 byte setup command
     * packet in case this is a IRP is 
     * scheduled on a CONTROL pipe. Should
     * be NULL otherwise */
    void * setup;

    /* Pointer to data buffer */
    void * data;
    
    /* Size of the data buffer */
    unsigned int size;
    
    /* Status of the IRP */ 
    USB_HOST_IRP_STATUS status;

    /* Request specific flags */
    USB_HOST_IRP_FLAG flags;

    /* User data */
    uintptr_t userData;

    /* Pointer to function to be called
     * when IRP is terminated. Can be 
     * NULL, in which case the function
     * will not be called. */
    void (*callback)(struct _USB_HOST_IRP * irp);

    /****************************************
     * These members of the IRP should not be
     * modified by client
     ****************************************/
   uintptr_t privateData[5]; 
}
USB_HOST_IRP;

// *****************************************************************************
/* USB Error Codes
 
  Summary:
    Enumeration of all possible error codes that are returned by various 
    components functions in the USB Stack.

  Description:
    Enumeration of all possible error codes that are returned by various 
    components functions in the USB Stack.

  Remarks:
    None.
*/

typedef enum
{

     /* IRP Queue Full Error */
    USB_ERROR_IRP_QUEUE_FULL = SCHAR_MIN ,

    /* IRP Size parameter invalid */
    USB_ERROR_IRP_SIZE_INVALID ,

    /* Some function parameter was not valid */
    USB_ERROR_PARAMETER_INVALID ,

    /* Device endpoint is not valid */
    USB_ERROR_DEVICE_ENDPOINT_INVALID ,
    
   /* IRP is already in use */
    USB_ERROR_DEVICE_IRP_IN_USE ,

    /* Client is not ready */
    USB_ERROR_CLIENT_NOT_READY ,
            
    /* Free IRP object unavailable */
    USB_ERROR_IRP_OBJECTS_UNAVAILABLE ,

    /* Function Driver instance was not provisioned */
    USB_ERROR_DEVICE_FUNCTION_INSTANCE_INVALID ,

    /* Function Driver instance is not configured */
    USB_ERROR_DEVICE_FUNCTION_NOT_CONFIGURED ,
            
    /* Endpoint is not configured */         
    USB_ERROR_ENDPOINT_NOT_CONFIGURED ,

    /* Device COntrol Transfer Failed */
    USB_ERROR_DEVICE_CONTROL_TRANSFER_FAILED ,
        /* Host driver instance invalid */
   USB_ERROR_HOST_DRIVER_INSTANCE_INVALID,
     /* Host driver not ready for communication*/
   USB_ERROR_HOST_DRIVER_NOT_READY,
   /* Host driver not found */
   USB_ERROR_HOST_DRIVER_NOT_FOUND,

     /* No Error, Operation was successful */
    USB_ERROR_NONE = 0,
}USB_ERROR;

// *****************************************************************************
/* USB Communication direction definitions

  Summary:
    Defines the communication direction

  Description:
    This definitions define the communication direction and can be used to
    specify direction while using the DRV_USB_ENDPOINT type.

  Remarks:
    None.
*/

#define USB_DATA_DIRECTION_DEVICE_TO_HOST    1
#define USB_DATA_DIRECTION_HOST_TO_DEVICE    0


// *****************************************************************************
/* USB 2.0 Speeds Enumeration

  Summary:
    Provides enumeration of USB 2.0 speeds.

  Description:
    Provides enumeration of USB 2.0 speeds.

  Remarks:
    None.
*/

typedef enum
{
    USB_SPEED_LOW = 1,   // USB module is at low speed
    USB_SPEED_FULL = (USB_SPEED_LOW << 1) ,   // USB module is at full speed
    USB_SPEED_HIGH = (USB_SPEED_FULL << 1)    // USB module is at high speed

} USB_SPEED;

#endif




