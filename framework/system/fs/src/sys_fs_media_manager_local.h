#ifndef _SYS_FS_MEDIA_MANAGER_LOCAL_H_
#define _SYS_FS_MEDIA_MANAGER_LOCAL_H_

#include "system_config.h"
#include "system/int/sys_int.h"
#include "system/common/sys_module.h"
#include "system/fs/sys_fs_media_manager.h"
#include "system/fs/fat_fs/src/hardware_access/diskio.h"

// *****************************************************************************
/* Media manager task states

  Summary:
    Identifies the various states that the media manager goes through.

  Description:
    This enumeration identifies the states of media manager task.

  Remarks:
    None.
*/
typedef enum _SYS_FS_MEDIA_MANAGER_TASK_STATES
{
    /* Media manager to select a new media for analysis */
    SYS_FS_MEDIA_MANAGER_TASK_STATE_SELECT_NEW_REGISTERED_DISK = 0,
    /* State of Media manager, when media is detached */
    SYS_FS_MEDIA_MANAGER_TASK_STATE_DETACHED,
    /* Media manager to open the media driver */
    SYS_FS_MEDIA_MANAGER_TASK_STATE_OPEN_MEDIA,
    /* Media manager is polliing if the media driver is opened */
    SYS_FS_MEDIA_MANAGER_TASK_STATE_OPENING_MEDIA,
    /* Media manager checking the status of the media */
    SYS_FS_MEDIA_MANAGER_TASK_STATE_CHECK_ATTACHED_MEDIA,
    /* Task state when media is attached */
    SYS_FS_MEDIA_MANAGER_TASK_STATE_ATTACHED,
    /* Media manager task state, when media is being analyzed */
    SYS_FS_MEDIA_MANAGER_TASK_STATE_ANALYZING_FILE_SYSTEM,
    /* After analysis, media manager is allocating volumes to each partition of the media */
    SYS_FS_MEDIA_MANAGER_TASK_STATE_ALLOCATING_VOLUME,
    /* Media is all analyzed. Now, media manager will pick the next disk for analysis */
    SYS_FS_MEDIA_MANAGER_TASK_STATE_ANALYZED,
}
SYS_FS_MEDIA_MANAGER_TASK_STATES;

// *****************************************************************************
/* Media object

  Summary:
    Defines the media object.

  Description:
    This structure defines the object that defines a media. Whenever a media is
 * connected, the media calls the function "SYS_FS_MEDIA_MANAGER_Register" to
 * register itself to the media manager. This object holds the property of media.

  Remarks:
    None.
*/
typedef struct _SYS_FS_MEDIA
{
    /* If the media object is in use or is it free */
    bool inUse;
    /* Media driver index. The index is used to open the media driver */
    SYS_MODULE_INDEX  index;
    /* List of functions for the media driver */
    const SYS_FS_MEDIA_FUNCTIONS * mediaDriverFunctions;
    /* State of the media (Registered,  opened, attached, analyzed) */
    SYS_FS_MEDIA_STATE mediaState;
    /* Media driver object. This object is used to run the media task routine */
    SYS_MODULE_OBJ mediaDriverObject;
    /* Handle received after the media driver is opened */
    DRV_HANDLE  mediaDriverClientHandle;
    /* Type of the media */
    SYS_FS_MEDIA_TYPE   mediaType;
    /* Handle received when trying to read or write a sector from the media */
    SYS_FS_MEDIA_BUFFER_HANDLE  mediaBufferHandle;
    /* Status of media -- attached or detached */
    SYS_FS_MEDIA_STATUS mediaStatus;
    /* Number of partitions available in the media */
    uint8_t numberOfPartitions;
    /* Number identifying the media. This number keeps on incrementing
     for every new media registered with the media manager */
    uint8_t mediaNumber;
}
SYS_FS_MEDIA;

// *****************************************************************************
/* Volume object

  Summary:
    Defines the volume object.

  Description:
    This structure defines the object that defines a volume. A volume is assigned
    for a media, if there is only 1 partition. If there are multipartitions, then,
    each volume is assigned to each partition.

  Remarks:
    None.
*/
typedef struct _SYS_FS_VOLUME
{
    /* If the volume object is in use or is it free */
    bool inUse;
    /* Name of volume (nvma1 or mmcblka1 etc..) */
    char devName[13];
    /* Starting sector # for the volume */
    unsigned long startSector;
    /* Number of sectors in the volume */
    unsigned long numberOfSector;
    /* Type of file system implemented for the volume */
    unsigned char fileSystemType;
    /* Pointer to the media, which is parent the volume */
    SYS_FS_MEDIA *obj;
}
SYS_FS_VOLUME;

// *****************************************************************************
/* Media manager task object

  Summary:
    Defines the object required for the operation and control of media manger task.

  Description:
    This structure defines the object required for the opeation of the media
    manager task.

  Remarks:
    None.
*/
typedef struct
{
    /* Number of NVM media registered with media maanger */
    uint32_t NVMMediaCounter;
    /* Number of SD card media registered with media maanger */
    uint32_t SDCardMediaCounter;
    /* Number of MSD media registered with media maanger */
    uint32_t MSDMediaCounter;
    /* Number of RAM media registered with media maanger */
    uint32_t RAMMediaCounter;

    /* Number of volumes in each of NVM media registered with media maanger */
    uint32_t NVMVolumeCounter;
    /* Number of volumes in each SD card media registered with media maanger */
    uint32_t SDCardVolumeCounter;
    /* Number of volumes in each MSD media registered with media maanger */
    uint32_t MSDVolumeCounter;
    /* Number of volumes in each RAM media registered with media maanger */
    uint32_t RAMVolumeCounter;

    /* Variable to hold the media # that the media manager task has chosen
     to analyze and carry on with the media manager tasks */
    uint16_t diskIndex;
    /* Pointer to the media */
    SYS_FS_MEDIA *disk;
    /* State of media manager task */
    SYS_FS_MEDIA_MANAGER_TASK_STATES taskState;
    /* Buffer to hold the value of each sector of media read */
    uint8_t buffer[512];
}
SYS_FS_MEDIA_MANAGER_TASK_OPERATION;

/***************************************************************
 * The following structure was added to enable the "multipartition"
 * feature of FAT FS. This strucre is already declared in ff.h and
 * the intention was to make as little change on ff.h
 * To use multipartition on FAT FS, we need to enable "_MULTI_PARTITION".
 * And, when we do that, the FAT FS code expects an array named "VolToPart".
 * The explanation for each element of the array is given below, and
 * this function places the elements of this array.
 *
 * Lets consider a case where 2 media are attached = SD card with 4 partitions
 * and NVM with 1 partition.
 *
 * PARTITION VolToPart[SYS_FS_VOLUME_NUMBER] = {
 *        {0, 1},    // 0th volume # assigned by sys_fs_media_manager (mmcblka1), media # = 0 (SD card), partition # = 1
 *        {0, 2},    // 1st volume # assigned by sys_fs_media_manager (mmcblka2), media # = 0 (SD card), partition # = 2
 *        {0, 3},    // 2nd volume # assigned by sys_fs_media_manager (mmcblka3), media # = 0 (SD card), partition # = 3
 *        {0, 4},    // 3rd volume # assigned by sys_fs_media_manager (mmcblka4), media # = 0 (SD card), partition # = 4
 *        {1, 1}     // 4th volume # assigned by sys_fs_media_manager (nvma1), media # = 1 (NVM), partition # = 1
 *    };
 ***************************************************************/
void _SYS_FS_MEDIA_MANAGER_updateVolToPart(uint8_t volNumber, uint8_t pd, uint8_t pt);

#endif
