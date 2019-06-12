#ifndef __GX_HOTPLUG_H__
#define __GX_HOTPLUG_H__

#include "gxbus.h"
#include "gxcore.h"

__BEGIN_DECLS

typedef struct {
	char dev_name[32];
	int  error;
}GxMsgProperty_HotPlug;

typedef enum {
	HOTPLUG_TYPE_USB = 0,
	HOTPLUG_TYPE_MMC = 1
}HotplugType;


typedef struct {
	char partition_name[16];
	char partition_entry[32];
	char dev_name[16];
	char fs_type[8];
	char disk_id;
}HotplugPartition;

typedef struct {
	HotplugType type;
	int partition_num;
	HotplugPartition *partition;
}HotplugPartitionList;

HotplugPartitionList* GxHotplugPartitionGet(HotplugType type);

__END_DECLS

#endif /* __GX_HOTPLUG_H__ */

