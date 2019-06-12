#ifndef GXCORE_OS_FILESYS
#define GXCORE_OS_FILESYS

#include "gxtype.h"
#include "gxcore_os_core.h"
#include "gxcore_version.h"
#include "common/list.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum {
	GX_SEEK_SET = 0,//SEEK_SET,
	GX_SEEK_CUR = 1,//SEEK_CUR,
	GX_SEEK_END = 2,//SEEK_END,
} GxSeek;

typedef enum {
	GX_FILE_NONE = -1,
	GX_FILE_REGULAR = 0,
	GX_FILE_DIRECTORY = 1,
	GX_FILE_DEVICE = 2,
	GX_FILE_SOCKET = 3,
}GxFileInfoType;

typedef struct {
	GxFileInfoType  type;
	char            perms;
	char            flags;
	uint64_t        size_by_bytes;
	uint32_t        last_access_time;
	uint32_t        last_modify_time;
	uint32_t        attrib;
}GxFileInfo;

typedef struct {
	void *plink;
	void *dirp;
	char **ents;
	unsigned int nents;
}GxDir;

typedef struct {
	GxFileInfoType ftype; /*  type of file; not supported by all file system types */
	char*          fname; /*  filename */
	long long      fsize;
	int            fmtime;
} GxDirent;

typedef enum {
	CLUSTER_4096 = 4096,
	CLUSTER_8192 = 8192,
	CLUSTER_16K = (16*1024),
	CLUSTER_32K = (32*1024),
	CLUSTER_64K = (64*1024),
}GxCstSize;

typedef struct {
	GxCstSize cluster_size;		/* -c, format with this cluster-size */
	char *label;			/* -L, volume label */
}GxMkfsOpts;

enum fstype {
	FS_TYPE_FAT32,
	FS_TYPE_NTFS,
	FS_TYPE_EXFAT,
	FS_TYPE_OTHER,
	FS_TYPE_UNKNOWN = 0xffffffff
};

typedef struct {
	unsigned long long total_size;
	unsigned long long used_size;
	unsigned long long freed_size;
	unsigned long      block_size;
	enum fstype        type;
}GxDiskInfo;

#define HUB_NUM_MAX 12
#define PARTITION_NUM_MAX 24
#define HOT_DEVICE_IN_USED_MAX    12

#define MS_MOUNTED    0
#define MS_UNMOUNTING 1
#define MS_UNMOUNTED  2

struct gxfs_partition {
	int                     id;
	int                     active;
	char                    dev_name[32];		// /dev/usb0/1
	char                    path_name[32];		// /mnt/usb0_1
	char                    fs_type[8];		// fatfs
	struct gxfs_hot_device  *dev;
	void                    *priv;
	struct gxlist_head      head;
	int                     mount_status;
};

typedef enum {
	USB = 0,
	SD = 1,
	CF = 2,
}GxFsDevType;

typedef enum {
	PLUG_IN    = 1,
	PLUG_OUT   = 2,
	PLUG_CLEAN = 3,
}GxFsActionType;

typedef enum {
	PLUG_SUCCESS             = 0,
	PLUG_ERROR_FS_NO_SUPPORT = 1,
	PLUG_ERROR_NO_PARTITION  = 2,
} GxHotplugError;

struct gxfs_hot_device {
	int                     id;
	char                    dev_name[32];
	int                     active;
	GxFsDevType             type;            // usb, sd, cf
	GxFsActionType          action;          // PLUG-IN PLUG-OUT
	int                     partition_count;
	struct gxlist_head      partition_head;
	struct gxlist_head      head;
	int                     hot;
	GxHotplugError          error;
	void *priv;
};

struct GxDiskPartition
{
	char devname[32];
	char pathname[32];
	GxDiskInfo disk_info;
};

struct gx_usbwifi_hot_device {
	int                     id;
	int                     active;
	GxFsActionType          action;          // PLUG-IN PLUG-OUT
	struct gxlist_head      head;
	int                     hot;
	GxHotplugError          error;
	void *priv;
};

struct gx_usb3g_hot_device {
	int                     id;
	int                     active;
	GxFsActionType          action;          // PLUG-IN PLUG-OUT
	struct gxlist_head      head;
	int                     hot;
	GxHotplugError          error;
	void *priv;
};


void      GxCore_GetFileInfo  (const char *path, GxFileInfo *Info);
void      GxCore_GetFileStat  (handle_t file, GxFileInfo *Info);
handle_t  GxCore_GetTempDir   (char *dst, size_t len);
handle_t  GxCore_FileExists   (const char *path);
handle_t  GxCore_FileDelete   (const char *path);
handle_t  GxCore_Open         (const char *path, const char *mode);
handle_t  GxCore_Close        (handle_t file);
ssize_t   GxCore_Read         (handle_t file, void *buf, size_t size, size_t nmemb);
ssize_t   GxCore_ReadAt       (handle_t file, void *buf, size_t size, size_t nmemb, long pos);
ssize_t   GxCore_Write        (handle_t file, void *buf, size_t size, size_t nmemb);
ssize_t   GxCore_WriteAt      (handle_t file, void *buf, size_t size, size_t nmemb, long pos);
int32_t   GxCore_Sync         (handle_t file);
//int32_t   GxCore_Ioctl        (handle_t file, int cmd, ... );
int32_t   GxCore_Select       (int32_t nfd, void *in, void *out, void *ex, GxTime *tv);
int32_t   GxCore_Seek         (handle_t file, long off, GxSeek whence);
int32_t   GxCore_Mkdir        (const char *path);
int32_t   GxCore_Rmdir        (const char *path);
int32_t   GxCore_Chdir        (const char *path);
int32_t   GxCore_MkFs         (const char *devname, const char *fsname, GxMkfsOpts *opts);
int32_t   GxCore_DiskInfo     (const char *pathname, GxDiskInfo *disk_info);
int32_t   GxCore_ModExist     (char *fs_type);
void      GxCore_Cwd          (char *dst, size_t len);
GxDir*    GxCore_Opendir      (const char *path);
void      GxCore_Closedir     (void *dir);

int       GxCore_GetDir       (const char *dir, GxDirent **ents, const char *filter);
int       GxCore_FreeDir      (GxDirent *ents, int count);
int       GxCore_SortDir      (GxDirent *ents, int count, int (*compar)(const void *, const void*));
int       GxCore_Rename       (const char *oldpath, const char *newpath);
int       GxCore_VertDevListFree(struct gxfs_hot_device *node);

char      *GxCore_CatPath     (const char *dir, const char *file);
char      *GxCore_BasePath    (const char *dir, char *path);

void GxCore_HotplugInit(void);
void GxCore_HotplugLock(void);
void GxCore_HotplugUnlock(void);
void GxCore_Hotplug_Priority_down(void);
void GxCore_Hotplug_Priority_up(void);
int  GxCore_HotplugClean(void);

int GxCore_HotplugWaitKernelMsg(char*p );
struct gxfs_hot_device *GxCore_HotplugWait(void);
struct gxfs_hot_device *GxCore_HotplugGetFirst(void);
struct gxfs_hot_device *GxCore_HotplugGetNext(struct gxfs_hot_device *dev);

void GxCore_UsbwifiHotplugInit(void);
int  GxCore_UsbwifiHotplugClean(void);
struct gx_usbwifi_hot_device *GxCore_UsbwifiHotplugWait(void);
struct gx_usbwifi_hot_device *GxCore_UsbwifiHotplugGetFirst(void);
struct gx_usbwifi_hot_device *GxCore_UsbwifiHotplugGetNext(struct gx_usbwifi_hot_device *dev);

void GxCore_Usb3gHotplugInit(void);
int  GxCore_Usb3gHotplugClean(void);
struct gx_usb3g_hot_device *GxCore_Usb3gHotplugWait(void);
struct gx_usb3g_hot_device *GxCore_Usb3gHotplugGetFirst(void);
struct gx_usb3g_hot_device *GxCore_Usb3gHotplugGetNext(struct gx_usb3g_hot_device *dev);

//范例： dev_name = "/dev/usb0/" path_name = "/mnt/usb0/2" fs_type="ntfs"
void GxCore_HotplugModifyPartition(char *dev_name, char *path_name, char *fs_type);

int32_t GxCore_GetDiskPartitons(char *dev_name, int part_num,
		struct GxDiskPartition *part[], int *act_part_num);

#ifdef __cplusplus
}
#endif

#endif
