#ifndef _FIRMWARE_H_
#define _FIRMWARE_H_

#ifdef __cplusplus
extern "C"{
#endif

typedef enum gxav_load_flag {
	GXAV_LOAD_START        = 0x1,
	GXAV_LOAD_CONTINUE     = 0x2,
} GxAvLoadFlag;

typedef enum gxav_firmware_id {
	GXAV_FMID_MPEG12A      = 0x001,
	GXAV_FMID_AVSA         = 0x002,
	GXAV_FMID_DOLBY        = 0x003,
	GXAV_FMID_RA_AAC       = 0x004,
	GXAV_FMID_RA_RA8LBR    = 0x005,
	GXAV_FMID_DRA          = 0x006,
	GXAV_FMID_MPEG4_AAC    = 0x007,
	GXAV_FMID_WMA          = 0x008,
	GXAV_FMID_OGG          = 0x009,
	GXAV_FMID_PCM          = 0x00A,
	GXAV_FMID_DTS          = 0x00B,
	GXAV_FMID_H264         = 0x100,
	GXAV_FMID_AVSV         = 0x101,
	GXAV_FMID_MPEG4V       = 0x102,
	GXAV_FMID_RV           = 0x103,
	GXAV_FMID_RV_BITSTREAM = 0x104,
	GXAV_FMID_H263         = 0x105,
	GXAV_FMID_AUDIO        = 0x106,
	GXAV_FMID_VIDEO        = 0x108,

	GXAV_FMID_JPEG         = 0x200
} GxAvDecoderType;

struct gxav_firmware_info {
	enum gxav_firmware_id func_id;
	unsigned char* func_addr;
	unsigned int   func_size;
	unsigned int   load_size;
	unsigned char  active;
	unsigned char  used;
	unsigned char  fix;  // if fix=1, don't free.
};

typedef struct gxav_firmware_load_info {
	unsigned char* addr;
	unsigned int   func_len;
	unsigned int   func_id;
	unsigned int   size;
	unsigned int   active;
	GxAvLoadFlag   flag;
} GxAvFirmwareLoad;

struct gxav_codec_register {
	unsigned char*       start;
	unsigned int         size;
	unsigned int         type;
};

int  gxav_firmware_init(void);
void gxav_firmware_uninit(void);
int  gxav_firmware_load(void * info, void *(*copy)(void *, const void *, int));
int  gxav_firmware_unload(unsigned int id);
int  gxav_firmware_fetch(unsigned int func_id, unsigned int*addr, unsigned int *size);
int  gxav_firmware_add_static(struct gxav_firmware_info *firmware);
int  gxav_firmware_register(void *info);
int  gxav_firmware_check_static(void);

#ifdef __cplusplus
}
#endif

#endif

