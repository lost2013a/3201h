#ifndef __GXPLAYER_DEMUXER_H__
#define __GXPLAYER_DEMUXER_H__

#include "gxplayer_common.h"

#define GX_DEMUXER_MAX_EXTPID_NUM (16)
typedef enum {
	DEMUX_PES_TYPE,
	DEMUX_PSI_TYPE,
	DEMUX_TS_TYPE
} GxDemuxerDataType;

typedef struct {
	int pid;
	int type;
}GxDemuxerStreamSwitch;

typedef struct {
	uint8_t* buffer;
	int      size;
}GxDemuxerPesData;

typedef struct {
	unsigned int is_rawts;
	unsigned int is_encrypt;
	unsigned int is_onlyRec;
	unsigned int is_inserttable;
	unsigned int service_id;
	unsigned int a_pid;
	unsigned int v_pid;
	unsigned int pmt_pid;
	unsigned int cat_pid;
	unsigned int v_ecm_pid;
	unsigned int a_ecm_pid;
	unsigned int ext_num;
	unsigned int ext_pids[GX_DEMUXER_MAX_EXTPID_NUM];
	// DEMUX_SLOT_AUDIO DEMUX_SLOT_VIDEO DEMUX_SLOT_PES DEMUX_SLOT_PSI ...
	unsigned int ext_types[GX_DEMUXER_MAX_EXTPID_NUM];
	unsigned int ext_encrypt[GX_DEMUXER_MAX_EXTPID_NUM];
}GxDemuxerRecordExtInfo;

typedef struct {
#define RECODER_HEADER_MAX_LEN 188
	unsigned int headerdata_len;
	char         headerdata[RECODER_HEADER_MAX_LEN];
}GxDemuxerRecordHeaderInfo;

typedef struct {
#define RECODER_TABLE_MAX_LEN (8*188)
	unsigned int tabledata_len;
	char         tabledata[RECODER_TABLE_MAX_LEN];
}GxDemuxerRecordTableInfo;

typedef struct {
#define RECODER_USER_MAX_LEN  (128*188)
#define RECODER_USER_MAX_COUNT 128
	unsigned int userdata_len;
	char         userdata[RECODER_USER_MAX_LEN];
}GxDemuxerRecordUserInfo;

typedef struct{
#define PLAYER_FILTER_MAX 64
	int vpid;
	int apid;
	int apid1;
	struct {
		int pid;
		GxDemuxerDataType type;
		int crc;
		int (*writeback)(int pid, GxDemuxerDataType type, unsigned char *buffer, unsigned int size);
	}callback[PLAYER_FILTER_MAX];
} GxDemuxerPlayTsExtInfo;

#endif
