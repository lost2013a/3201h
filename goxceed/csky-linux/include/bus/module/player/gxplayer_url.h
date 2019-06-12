#ifndef __GXPLAYER_URL_H__
#define __GXPLAYER_URL_H__

#include "gxcore.h"

__BEGIN_DECLS

#define GX_URL_MAX_LEN         (2048)

#define GX_URL_KEY_FRE         "fre"
#define GX_URL_KEY_SYM         "symbol"
#define GX_URL_KEY_QAM         "qam"
#define GX_URL_KEY_TUNER       "tuner"
#define GX_URL_KEY_TSID        "tsid"
#define GX_URL_KEY_DMXID       "dmxid"
#define GX_URL_KEY_POLAR       "polar"
#define GX_URL_KEY_BANDW       "bandwidth"
#define GX_URL_KEY_22K         "22k"
#define GX_URL_KEY_CWMODE      "workmode"
#define GX_URL_KEY_SCRAM       "scramble"
#define GX_URL_KEY_TSDELAY     "tsdelay"
#define GX_URL_KEY_DMXMODE     "dmxmode"
#define GX_URL_KEY_TSMODE      "tsmode"
#define GX_URL_KEY_UNICABLE_IF_INDEX      "ifindex"
#define GX_URL_KEY_UNICABLE_LNB_INDEX      "lnbindex"
#define GX_URL_KEY_UNICABLE_CENTRE_FRE      "centrefre"
#define GX_URL_KEY_UNICABLE_IF_FRE      "iffre"
#define GX_URL_KEY_DATA_PLPID     "data_plp_id"
#define GX_URL_KEY_COMM_PLPID     "common_plp_exist"
#define GX_URL_KEY_COMM_PLPID_EXIST "common_plp_id"

#define GX_URL_KEY_VPID        "vpid"
#define GX_URL_KEY_APID        "apid"
#define GX_URL_KEY_SPID        "subpid"
#define GX_URL_KEY_PCRPID      "pcrpid"
#define GX_URL_KEY_PMTPID      "pmt"
#define GX_URL_KEY_APID1       "adpid"

#define GX_URL_KEY_PID_TY      "typid"
#define GX_URL_KEY_PID_TUV     "tuvpid"
#define GX_URL_KEY_PID_BY      "bypid"
#define GX_URL_KEY_PID_BUV     "buvpid"
#define GX_URL_KEY_PID_SYNC    "syncpid"

#define GX_URL_KEY_VCODEC      "vcodec"
#define GX_URL_KEY_ACODEC      "acodec"
#define GX_URL_KEY_ACODEC1     "adcodec"
#define GX_URL_KEY_SYNC        "sync"

#define GX_URL_KEY_DVBT        "dvbt://"
#define GX_URL_KEY_DVBS        "dvbs://"
#define GX_URL_KEY_DVBC        "dvbc://"
#define GX_URL_KEY_DTMB        "dtmb://"

#define GX_URL_KEY_MEM         "mem://"
#define GX_URL_KEY_ADDR        "addr"
#define GX_URL_KEY_SIZE        "size"
#define GX_URL_KEY_FMT         "fmt"
#define GX_MEM_FMT_MP3         1
#define GX_MEM_FMT_ES          2
#define GX_MEM_FMT_PES         3

#define GX_URL_VAL_POLAR_V     0 // 13v
#define GX_URL_VAL_POLAR_H     1 // 18V

#define GX_URL_VAL_BAND_8M     8000
#define GX_URL_VAL_BAND_7M     7000
#define GX_URL_VAL_BAND_6M     6000

#define GX_URL_VAL_CW_DTMB     0
#define GX_URL_VAL_CW_DVBC     1

#define GX_URL_VAL_ACODEC_MPG1  0
#define GX_URL_VAL_ACODEC_MPG2  1
#define GX_URL_VAL_ACODEC_LATM  2
#define GX_URL_VAL_ACODEC_AC3   3
#define GX_URL_VAL_ACODEC_ATDS  4
#define GX_URL_VAL_ACODEC_EAC3  5
#define GX_URL_VAL_ACODEC_LPCM  6
#define GX_URL_VAL_ACODEC_DTS   7
#define GX_URL_VAL_ACODEC_DOLBY_TRUEHD 8
#define GX_URL_VAL_ACODEC_AC3_PLUS 9
#define GX_URL_VAL_ACODEC_DTS_HD   10
#define GX_URL_VAL_ACODEC_DTS_MA   11
#define GX_URL_VAL_ACODEC_AC3_PLUS_SEC 12
#define GX_URL_VAL_ACODEC_DTS_HD_SEC   13
#define GX_URL_VAL_ACODEC_DRA1         14

#define GX_URL_VAL_VCODEC_MPG2  0
#define GX_URL_VAL_VCODEC_AVS   1
#define GX_URL_VAL_VCODEC_H264  2
#define GX_URL_VAL_VCODEC_H265  3
#define GX_URL_VAL_VCODEC_MPG4  4
#define GX_URL_VAL_VCODEC_H263  5
#define GX_URL_VAL_VCODEC_REAL  6

#define GX_URL_VAL_SYNC_AVPTS   0
#define GX_URL_VAL_SYNC_VPTS    1
#define GX_URL_VAL_SYNC_APTS    2
#define GX_URL_VAL_SYNC_PCR     3

typedef enum {
	GX_URL_DVBT,
	GX_URL_DVBS,
	GX_URL_DVBC,
	GX_URL_DTMB,
	GX_URL_MEM,
}GxUrlType;

extern char* GxUrl_Create(GxUrlType urltype);
extern void  GxUrl_Destroy(char* url);
extern void  GxUrl_DelItem(char* url, const char* item);
extern void  GxUrl_SetItem(char* url, const char* item, int32_t itemval, int32_t max_len);
extern void  GxUrl_GetItem(const char* url, const char *item, int32_t *retVal);

__END_DECLS

#endif

