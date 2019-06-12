#ifndef __GX_OEM_H__
#define __GX_OEM_H__

#include <stdint.h>
#include <gxcore.h>

__BEGIN_DECLS

#define OEM_RUNNING_ON_GXBUS                    (0)
#define OEM_RUNNING_ON_GXCORE                   (1)

#define OEM_RUNNING_LAYER                       OEM_RUNNING_ON_GXBUS

/*GoXceed System Partition Name List*/
#define GX_PARTITION_BOOT                       ("BOOT")
#define GX_PARTITION_LOGO                       ("LOGO")
#define GX_PARTITION_I_OEM                      ("I_OEM")
#define GX_PARTITION_V_OEM                      ("V_OEM")
#define GX_PARTITION_KERNEL                     ("KERNEL")
#define GX_PARTITION_ROOT                       ("ROOT")
#define GX_PARTITION_DOWNLOADER                 ("OTA")
#define GX_PARTITION_DOWNLOADER_BAK             ("OTA_BAK")
/*GoXceed System Partition Type List*/
#define PARTITION_TYPE_RAW     0
#define PARTITION_TYPE_ROMFS   1
#define PARTITION_TYPE_CRAMFS  2
#define PARTITION_TYPE_JFFS2   3
#define PARTITION_TYPE_YAFFS2  4
#define PARTITION_TYPE_RAMFS   5
#define PARTITION_TYPE_MINIFS  127
/*GoXceed System Partition Mode List*/

#ifndef O_RDONLY
#define O_RDONLY                                (1<<0)
#endif

#ifndef O_WRONLY
#define O_WRONLY                                (1<<1)
#endif

#ifndef O_RDWR
#define O_RDWR                                  (O_RDONLY|O_WRONLY)
#endif

typedef struct partition_info  GxPartition;

typedef struct partition  GxPartitionTable;

int     GxOem_Init              (void);
int     GxOem_PartitionTableGet (GxPartitionTable* table);
int     GxOem_PartitionTableSet (const GxPartitionTable* table);
int     GxOem_PartitionClean    (const char* name);
int     GxOem_PartitionRead     (const char* name, uint8_t* buf, int size);
int     GxOem_PartitionWrite    (const char* name, uint8_t* buf, int size);
char*   GxOem_GetValue          (const char* section, const char* parameter);
int     GxOem_SetValue          (const char* section, const char* parameter, const char* value);
int     GxOem_Save              (void);
int     GxOem_destroy           (void);

__END_DECLS

#endif
