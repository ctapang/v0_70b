/*******************************************************************************
  Application Header
  
  File Name:
    app.h

  Summary:
    NVM FAT Single Disk application definitions (advanced driver-based version)

  Description:
    This file contains the NVM FAT Single Disk demo application definitions.
 *******************************************************************************/

//DOM-IGNORE-BEGIN
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
//DOM-IGNORE-END

#ifndef _APP_HEADER_H
#define _APP_HEADER_H


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include "system_config.h"
#include "bsp_config.h"
#include "system/int/sys_int.h"
#include "system/ports/sys_ports.h"
#include "system/fs/mpfs/mpfs.h"
#include "system/fs/sys_fs.h"
#include "driver/nvm/drv_nvm.h"
#include "driver/nvm/drv_nvm_media.h"


// *****************************************************************************
// *****************************************************************************
// Section: Type Definitions
// *****************************************************************************
// *****************************************************************************


// *****************************************************************************
/* Application states

  Summary:
    Application states enumeration

  Description:
    This enumeration defines the valid application states.  These states
    determine the behaviour of the application at various times.
*/

typedef enum
{
	
	/* The app mounts the disk */
    APP_MOUNT_DISK = 0,
            
	/* The app opens the file_1 */ 
    APP_OPEN_FILE_1,            
            
	/* The app opens the file_2 */ 
    APP_OPEN_FILE_2,

        /* Check file status of 1st file */
    APP_CHECK_FILE_3_STAT,

    /* Check for file size */
    APP_DO_FILE_SIZE_CHECK,

    /* Perform a file seek */
    APP_DO_FILE_SEEK,
	
    /* The app reads and verfies the data */
    APP_READ_VERIFY_CONTENT,

    /* Check for end of file */
    APP_CHECK_EOF,

    /* The app closes the file and idles */
    APP_IDLE,

    /* An app error has occurred */
    APP_ERROR

} APP_STATES;


// *****************************************************************************
/* Application Data

  Summary:
    Holds application data

  Description:
    This structure holds the application's data.

  Remarks:
    Application strings and buffers are be defined outside this structure.
*/

typedef struct
{
    /* SYS_FS File handle for 1st file */
    SYS_FS_HANDLE      fileHandle_1;

    /* SYS_FS File handle for 2nd file */
    SYS_FS_HANDLE      fileHandle_2;
       
    /* Application's current state */
    APP_STATES              state;

    /* Application data buffer */
    uint8_t                 data[100];

    uint32_t            nBytesWritten;

    uint32_t            nBytesRead;

    SYS_FS_FSTAT        fileStatus;

} APP_DATA;


// *****************************************************************************
/* Driver objects.

  Summary:
    Holds driver objects.

  Description:
    This structure contains driver objects returned by the driver init routines
    to the application. These objects are passed to the driver tasks routines.

  Remarks:
    None.
*/

typedef struct
{
    /* NVM Driver Object  */
    SYS_MODULE_OBJ              drvNVMObject;

    /* NVM Media Driver Object */
    SYS_MODULE_OBJ              drvNVMMediaObject;

} APP_DRV_OBJECTS;


// *****************************************************************************
// *****************************************************************************
// Section: Application Initialization and State Machine Functions
// *****************************************************************************
// *****************************************************************************

/*******************************************************************************
  Function:
    void APP_Initialize ( void )

  Summary:
     This routine intializes the application object.

  Description:
    This routine initializes the application object. The application state is
    set to wait for media attach.

  Precondition:
    All other system initialization routines should be called before calling
    this routine (in "SYS_Initialize").

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Initialize();
    </code>

  Remarks:
    This routine must be called from the SYS_Initialize function.
*/

void APP_Initialize ( void );


/*******************************************************************************
  Function:
    void APP_Tasks ( void )

  Summary:
    NVM FAT Single Disk Demo application tasks function

  Description:
    NVM FAT Single Disk Demo application tasks function. This routine implements
    the application in a non blocking manner.

  Precondition:
    The system and application initialization ("SYS_Initialize") should be
    called before calling this function.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    APP_Tasks();
    </code>

  Remarks:
    This routine must be called from SYS_Tasks() routine.
*/

void APP_Tasks ( void );

// *****************************************************************************
// *****************************************************************************
// Section: extern declarations
// *****************************************************************************
// *****************************************************************************

/* This is a container object for all application
 * related data. */
extern APP_DATA appData;

/* This is a container object for the SYS_MODULE_OBJ
 * returned by the driver initialization routines. */
extern APP_DRV_OBJECTS appDrvObjects;

/* The demo app writes this string to the file */
extern const uint8_t writeData[];

#endif /* _APP_HEADER_H */

/*******************************************************************************
 End of File
*/

