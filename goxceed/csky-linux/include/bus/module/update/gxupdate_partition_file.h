#ifndef __GXUPDATE_PARTITION_FILE_H__
#define __GXUPDATE_PARTITION_FILE_H__
#include "gxupdate_stream.h"
#include "gxcore.h"

__BEGIN_DECLS

/*partition name*/
#define GXUPDATE_PARTITION_FILE             "partition file"
/*the max number of opening*/
#define GXUPDATE_MAX_NUM_OPEN_FILE          (1)
/*the partition control key*/
#define GXUPDATE_CONFIG_FILE                (1)

typedef struct {
	char *file_name;
} GxUpdate_ConfigFile;

extern GxUpdate_PartitionOps gxupdate_partition_file;

__END_DECLS

#endif

