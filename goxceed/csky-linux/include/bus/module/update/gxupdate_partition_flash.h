#ifndef __GXUPDATE_PARTITION_ROOTFS_H__
#define __GXUPDATE_PARTITION_ROOTFS_H__

#include "gxcore.h"
#include "gxupdate_stream.h"

/*device name*/
#define FLASH_DEVICE_NAME                       "/dev/flash/0/0"
/*partition name*/
#define GXUPDATE_PARTITION_FLASH                "flash"
/*partition flash control key list*/
#define GXUPDATE_MAX_NUM_OPEN_FLASH             (2)
#define GXUPDATE_CONFIG_FLASH                   (0)

typedef struct {
	uint32_t    start_addr;
	size_t      size;
} GxUpdate_ConfigFlash;

extern GxUpdate_PartitionOps gxupdate_partition_flash;

#endif

