/** @defgroup pm_module PM Module*/

/*@{*/
#ifndef __GXPROGRAM_MANAGE_MINIDB_H__
#define __GXPROGRAM_MANAGE_MINIDB_H__

#include "gxtype.h"
#include "gxcore.h"
#ifdef LINUX_OS
#include <linux/dvb/frontend.h>
#else
#include "frontend/frontend.h"
#endif

__BEGIN_DECLS

/**
 * ˵������ͬ��tp���Ͽ������ڲ�ͬ���ŵ� �������ǵ�˫
 * tuner���� ����tunerӦ������tp����Ϊ��λ������
 * ��������ṹ���ڱ���tp���������һ��tuner,
 * �����������Ƶ��ʱ������ȷ�ϲ����ĸ�tuner,1-tuner1 2-tuner2.....
 */
typedef uint32_t GxBusPmDataSatTuner;

/*����Ϊ��������ʽ,�ڳ�ʼ�����ݿ��ʱ����,
  ����������ο��ƴ����ֵ�ĺϷ���???����û�����Ҵ� ���������*/
extern uint32_t MAX_SAT_COUNT;
extern uint32_t MAX_TP_COUNT;
extern uint32_t MAX_PROG_COUNT;

//#define MAX_SAT_COUNT   100   ///< ������������ɵ�sat����
//#define MAX_TP_COUNT    4000  ///< ������������ɵ�tp����
//#define MAX_PROG_COUNT  5000  ///< ������������ɵ�prog����
#define MAX_PROG_PER_TP   (300) ///< ����ÿ��tp��������ɵ�prog����
/****************************************************************/
#define MAX_SAT_NAME       (16)
#define MAX_PROG_NAME      (32)
#define MAX_FAV_GROUP_NAME (16)
#define MAX_CAS_NAME       (16)
#define MAX_CA_SYSTEM      (16)
#define CAS_ID_FREE        (0x1fff)
#define CAS_ID_UNKNOW      (0x1ffe)
#define MAX_IF_INDEX_NUM       (8)


//#define GXCORE_SUCCESS           (0)
//#define GXCORE_ERROR        (1)

#define GX_PM_DBASE_FULL (0x7fffffff)

#define GX_PM_MAX_PROG_URL_SIZE (256)

#define MAX_CMP_NAME (MAX_PROG_NAME)

/**
 *���ݿ�·��
 */
#define GX_PM_FILE_PATH1                "/home"
#define GX_PM_FILE_PATH2                "/home/gx"
#define GX_PM_FILE_PATH3                "/home/gx/db"


#define GX_PM_SAT_FILE_PATH             "/home/gx/sat.db"
#define GX_PM_TP_FILE_PATH              "/home/gx/tp.db"
#define GX_PM_PROG_FILE_PATH            "/home/gx/prog.db"
#define GX_PM_FAV_FILE_PATH             "/home/gx/fav.db"
#define GX_PM_STREAM_FILE_PATH          "/home/gx/stream.db"
#define GX_PM_VERIFY_FILE_PATH          "/home/gx/verify.db"
#define GX_PM_TV_USER_LIST_FILE_PATH    "/home/gx/tv_user_list.db"
#define GX_PM_RADIO_USER_LIST_FILE_PATH "/home/gx/radio_user_list.db"
#define GX_PM_PROG_EXT_FILE_PATH        "/home/gx/prog_ext.db"

/**
 * �ۿ�ģʽ�����ļ�·��
 */
#define GX_SYS_INFO_FILE_PATH1          "/home"
#define GX_SYS_INFO_FILE_PATH2          "/home/gx"
#define GX_SYS_INFO_FILE_PATH3          "/home/gx/db"
#define GX_SYS_INFO_FILE_NAME           "/home/gx/view_info_db"

/**
 * Ĭ�����ݿ��ļ���·��
 */
#define GX_PM_DEFAULT_PATH              "/default_data.db"
#define GX_PM_DEFAULT_SAT_FILE_PATH     "/sat.db"
#define GX_PM_DEFAULT_TP_FILE_PATH      "/tp.db"
#define GX_PM_DEFAULT_PROG_FILE_PATH    "/prog.db"


/* Exported Types --------------------------------------------------------- */

/**
 * ˵�������ݿ����ݵ�����
 * ������չҪ�����������µ�����
 */
typedef enum {
	GXBUS_PM_DATA_SAT = 0, // ������Ϣ
	GXBUS_PM_DATA_TP,      // Tp��Ϣ
	GXBUS_PM_DATA_PROG,    // ��Ŀ��Ϣ
} GxBusPmDataQueryType;

/**
 * ˵����Ҫ���ǵ�������֪�����Ĺ��� �������c��t�������
 * ���ǵĸ���
 */
typedef enum {
	GXBUS_PM_SAT_S = 0,  // s��tp���ϣ��������͵�tp���Ͼ���һ������
	GXBUS_PM_SAT_C,      // c��tp���ϣ�
	GXBUS_PM_SAT_T,      // t��tp����
	GXBUS_PM_SAT_DTMB,   // dtmb��tp����
	GXBUS_PM_SAT_DVBT2,  // dvbt2��tp����
	GXBUS_PM_SAT_ATSC_C, // atsc_c��tp����
	GXBUS_PM_SAT_ATSC_T, // atsc_t��tp����
} GxBusPmDataSatType;

/**
 *���Ǿ��ȵ�����ö��
 */
typedef enum {
	GXBUS_PM_SAT_LONGITUDE_DIRECT_EAST = 0, // ����
	GXBUS_PM_SAT_LONGITUDE_DIRECT_WEST,     // ����
} GxBusPmDataSatLongitudeDirect;

/**
 *����lnb power
 */
typedef enum {
	GXBUS_PM_SAT_LNB_POWER_OFF = 0, // ������
	GXBUS_PM_SAT_LNB_POWER_ON,      // ����
	GXBUS_PM_SAT_LNB_POWER_13V,     // ��13v��
	GXBUS_PM_SAT_LNB_POWER_18V,     // ��18v��
} GxBusPmSatLnbPower;

/**
 * LNB ����
 */
typedef enum {
	GXBUS_PM_SAT_LNB_UNIVERSAL = 0,
	GXBUS_PM_SAT_LNB_OCS,            // 5150/5700
	GXBUS_PM_SAT_LNB_USER,           // "5150","5700","5750","9750","10000","10600","10700","10750","11250","11300"
} GxBusPmSatLnbType;

/**
 *����22k����
 */
typedef enum {
	GXBUS_PM_SAT_22K_OFF = 0, // 22k��
	GXBUS_PM_SAT_22K_ON,      // 22k��
	GXBUS_PM_SAT_22K_AUTO,    // 22k�Զ�
} GxBusPmSat22kSwitch;

/**
 * ����12v����
 */
typedef enum {
	GXBUS_PM_SAT_12V_OFF = 0, // 12v��
	GXBUS_PM_SAT_12V_ON,      // 12v��
} GxBusPmSat12vSwitch;

/**
 * ����diseq�汾
 */
typedef enum {
	GXBUS_PM_SAT_DISEQC_OFF   = 1,   // ��ʹ��diseqc
	GXBUS_PM_SAT_DISEQC_1_0   = 2,   // diseqc1.0
	GXBUS_PM_SAT_DISEQC_1_1   = 4,   // diseqc1.1
	GXBUS_PM_SAT_DISEQC_1_2   = 8,   // diseqc1.2
	GXBUS_PM_SAT_DISEQC_USALS = 16,  // diseqc USALS
	GXBUS_PM_SAT_DISEQC_2_0   = 32,  // diseqc2.0
} GxBusPmSatDiseqcVersion;

/**
 * ����diseq1.0λ��
 */
typedef enum {
	GXBUS_PM_SAT_DISEQC1_0_OFF = 0, // ��ʹ��diseqc1.0
	GXBUS_PM_SAT_DISEQC1_0_1,       // diseqc1.0 λ��1
	GXBUS_PM_SAT_DISEQC1_0_2,       // diseqc1.0 λ��2
	GXBUS_PM_SAT_DISEQC1_0_3,       // diseqc1.0 λ��3
	GXBUS_PM_SAT_DISEQC1_0_4,       // diseqc1.0 λ��4
	GXBUS_PM_SAT_DISEQC1_0_A,       // diseqc1.0 miniA
	GXBUS_PM_SAT_DISEQC1_0_B,       // diseqc1.0 miniB
} GxBusPmSatDiseqc10;

/**
 * ˵����dtmbоƬ1501�ܹ�����������ģʽdtmb��dvb_c
 */
typedef enum {
	GXBUS_PM_SAT_1501_DTMB = 0, // 1501оƬ��dtmb������ʽ
	GXBUS_PM_SAT_1501_DVB_C,    // 1501оƬ��dvb_c������ʽ
} GxBusPmDataSat1501WorkType;

/**
*s����ʹ�õ����ǲ���
*/
typedef struct {
	/*4*4B */
	uint16_t centre_fre[MAX_IF_INDEX_NUM];  
	
	/*4B */
	uint16_t             	    if_channel;        
	uint8_t                       lnb_fre_index; 
	uint8_t                       sat_pos; 
} GxBusPmSatUnicable_s;

typedef struct {
	/*4B */
	uint16_t                      lnb1;                 // LNB Frequence.�ͱ���
	uint16_t                      lnb2;                 // LNB Frequence. �߱���.���Ϊ������,���ֵΪ0

	/*4B */
	uint8_t                       diseqc11;             // deseqc1.1 ��λ��ѡ�� 0-OFF 1 ... 16
	uint8_t                       diseqc12_pos;         // ��¼������deseqc�豸�еĴ洢λ��. 0 ����Ĭ��λ��. */

	GxBusPmSatDiseqcVersion       diseqc_version : 8;   // diseqc�İ汾 *Off,DiSEqC1.0, DiSEqC1.1, DiSEqC1.2, USALS, DiSEqC2.0
	GxBusPmSatDiseqc10            diseqc10 : 8;         // diseqc1.0��λ��/*OFF , 1, 2, 3, 4, mini A, mini B */

	/*4B */
	GxBusPmSatLnbPower            lnb_power : 4;        // ѡ�񹩵������
	GxBusPmSat22kSwitch           switch_22K : 2;       // 22K ����. */
	GxBusPmSat12vSwitch           switch_12V : 1;       // 12v����
	GxBusPmDataSatLongitudeDirect longitude_direct : 1; // ���ǵľ���ѡ�� 0-���� 1-���� */
	uint8_t                       reserved;

	uint16_t                      longitude;            // ����ľ��ȶ���

	/*4*4B */
	uint8_t sat_name[MAX_SAT_NAME];                     // ���ǵ�����

	GxBusPmSatUnicable_s		unicable_para;

} GxBusPmSat_s;

/**
 * c���������ǵĲ���,
 * ������ṹ���еĲ���Ӧ����
 * ���������������tp���ϵ�tp�������õĲ���
 */
typedef struct {
	uint32_t reserved;
} GxBusPmSat_c;

/**
 * t���������ǵĲ���,
 * ������ṹ���еĲ���Ӧ����
 * ���������������tp���ϵ�tp�������õĲ���
 */
typedef struct {
	uint32_t reserved;
} GxBusPmSat_t;

/**
 * DTMB���������ǵĲ���,
 * ������ṹ���еĲ���Ӧ����
 * ���������������tp���ϵ�tp�������õĲ���
 */
typedef struct {
	GxBusPmDataSat1501WorkType work_mode;
} GxBusPmSat_dtmb;

/**
 * DVBT2���������ǵĲ���,
 * ������ṹ���еĲ���Ӧ����
 * ���������������tp���ϵ�tp�������õĲ���
 */
typedef struct {
	uint32_t reserved;
} GxBusPmSat_dvbt2;

/**
 * ATSC-C���������ǵĲ���,
 * ������ṹ���еĲ���Ӧ����
 * ���������������tp���ϵ�tp�������õĲ���
 */
typedef struct {
	uint32_t reserved;//ATSC wait
} GxBusPmSat_atsc_c;

/**
 * ATSC-T���������ǵĲ���,
 * ������ṹ���еĲ���Ӧ����
 * ���������������tp���ϵ�tp�������õĲ���
 */
typedef struct {
	uint32_t reserved;//ATSC wait
} GxBusPmSat_atsc_t;

/**
 * �ýṹ��ÿ��tp���ϵ����Խṹ�壬
 * �������Ƿ�����˵�����һ������node��
 * ������ṹ���еĲ���Ӧ���Ƕ��������������tp���ϵ�tp�������õĲ�����
 * ���������еı���,�û��õ������ǲ����������½ṹ��
 */
typedef struct {
	uint32_t id;                    // ��tp���ϵ�id
	uint16_t tsid;
	uint16_t cur_tv;
	uint16_t cur_radio;
	GxBusPmDataSatType type;        // tp���ϵ����ͣ�ָ���ü�������s����c������t
	GxBusPmDataSatTuner tuner;      // ��tp���������ĸ�tuner
	union {
		GxBusPmSat_s sat_s;
		GxBusPmSat_c sat_c;
		GxBusPmSat_t sat_t;
		GxBusPmSat_dtmb sat_dtmb;
		GxBusPmSat_dvbt2 sat_dvbt2;
		GxBusPmSat_atsc_c sat_atsc_c;
		GxBusPmSat_atsc_t sat_atsc_t;
	};
} GxBusPmDataSat;

/**
 * ���Ƿ���tp ��������
 */
typedef enum {
	GXBUS_PM_TP_POLAR_H = 0, // ��������h
	GXBUS_PM_TP_POLAR_V,     // ��������v
	GXBUS_PM_TP_POLAR_AUTO,  // ���������Զ�
}GxBusPmTpPolar;

/**
 * S ������tp�Ĳ���
 */
typedef struct {
	uint32_t       symbol_rate;   // ������
	GxBusPmTpPolar polar;         // ��������
} GxBusPmTp_s;

/**
 * C ������tp�Ĳ���
 */
typedef struct {
	uint32_t        symbol_rate; // ������
	fe_modulation_t modulation;  // ���Ʒ�ʽ �ο�fe_modulation_t
} GxBusPmTp_c;

/**
 * T ������tp�Ĳ���
 */
typedef struct {
	fe_bandwidth_t bandwidth;
} GxBusPmTp_t;

/**
 * DTMB ������tp�Ĳ���
 */
typedef struct {
	uint32_t        symbol_rate; // ������,��1501����dvb_C����ģʽʱ������
	fe_modulation_t modulation;  // ���Ʒ�ʽ ��1501����dvb_C����ģʽʱ������
	fe_bandwidth_t bandwidth;
} GxBusPmTp_dtmb;

/**
 * DVBT2 ������TP�Ĳ���
 */
typedef struct {
	fe_bandwidth_t bandwidth;
} GxBusPmTp_dvbt2;

/**
 * ATSC_C ������TP�Ĳ���
 */
typedef struct {
	uint32_t reserved;//�ȴ�����demod���� ATSC wait
} GxBusPmTp_atsc_c;

/**
 * ATSC_T ������TP�Ĳ���
 */
typedef struct {
	uint32_t reserved;//�ȴ�����DEMOD���� ATSC WAIT
} GxBusPmTp_atsc_t;

/**
 * �ýṹ��ÿ��tp�����Խṹ��,��Ҫͨ��sat_id
 * ȷ�ϸ�tp���ڵ�tp���ϵ����ԣ�����ѡ����Ӧ�Ĺ���������
 * �û��õ���tp�����������½ṹ��
 */
typedef struct {
	uint32_t id;        // ��tp��id
	uint32_t sat_id;    // ��tp������tp���ϵ�id����������Ƿ�������������ǵ�id
	uint32_t frequency; // Ƶ���Ƶ�ʵ�λ MHz
	union {
		GxBusPmTp_s tp_s;
		GxBusPmTp_c tp_c;
		GxBusPmTp_t tp_t;
		GxBusPmTp_dtmb tp_dtmb;
		GxBusPmTp_dvbt2 tp_dvbt2;
		GxBusPmTp_atsc_c tp_atsc_c;
		GxBusPmTp_atsc_t tp_atsc_t;
	};
} GxBusPmDataTP;

/**
 * PROG ������ģʽ
 */
typedef enum {
	GXBUS_PM_PROG_AUDIO_MODE_LEFT = 0, // ������
	GXBUS_PM_PROG_AUDIO_MODE_RIGHT,    // ������
	GXBUS_PM_PROG_AUDIO_MODE_STEREO,   // ������
	GXBUS_PM_PROG_AUDIO_MODE_MONO,     // MONO
} GxBusPmDataProgAduioTrack;

/**
 * prog��bool�Ͳ���,����skip lock ����,subt��־ cc��־ ttx��־
 * ��bool�͵Ĳ���
 */
typedef enum {
	GXBUS_PM_PROG_BOOL_ENABLE = 1,  // ʹ��
	GXBUS_PM_PROG_BOOL_DISABLE = 0, // ��ʹ��
} GxBusPmDataProgSwitch;

/**
 * prog ������ ָ����prog�� tv����radio
 */
typedef enum {
	GXBUS_PM_PROG_TV = 0,     // tv��Ŀ
	GXBUS_PM_PROG_RADIO,      // radio��Ŀ
	GXBUS_PM_PROG_HD_SERVICE, // �����Ŀ
	GXBUS_PM_PROG_DATA,       // ���ݹ㲥
	GXBUS_PM_PROG_NVOD,       // nvod
	GXBUS_PM_PROG_USER1,      // ��������
	GXBUS_PM_PROG_USER2,      // ��������
	GXBUS_PM_PROG_USER3,      // ��������
	GXBUS_PM_PROG_USER4,      // ��������
	GXBUS_PM_PROG_USER5,      // ��������
	GXBUS_PM_PROG_USER6,      // ��������
	GXBUS_PM_PROG_USER7,      // ��������
	GXBUS_PM_PROG_USER8,      // ��������
	GXBUS_PM_PROG_USER9,      // ��������
	GXBUS_PM_PROG_USER10,     // ��������
	GXBUS_PM_PROG_ALL,        // ���н�Ŀ
} GxBusPmDataProgType;

/**
 *ָ����Ŀʱ���Ѿ�����
 */
typedef enum {
	GXBUS_PM_PROG_EXIST = 0, // ��Ŀ�����������������Ľ�Ŀ
	GXBUS_PM_PROG_NOT_EXIST, //��Ŀ�Ѿ�����
} GxBusPmDataProgExistFlag;

/**
 * prog����Ƶ���� ָ����prog����Ƶ��mepg�Ļ���avs��
 */
typedef enum {
	GXBUS_PM_PROG_MPEG = 0, // mepg2����
	GXBUS_PM_PROG_AVS,      // AVS����
	GXBUS_PM_PROG_H264,     // h.264����
	GXBUS_PM_PROG_H265,     // h.265����
	GXBUS_PM_PROG_MPEG4,    // mpeg4����
} GxBusPmDataProgVideoType;

/**
 * audio������ ָ����audio��pcm�Ļ���aac�Ļ�����ac3��
 */
typedef enum {
	GXBUS_PM_AUDIO_MPEG1 = 0,    // mpeg-1
	GXBUS_PM_AUDIO_MPEG2,        // mpeg-2
	GXBUS_PM_AUDIO_AAC_LATM,     // aac??Ƶ
	GXBUS_PM_AUDIO_AC3,          // ac3??Ƶ
	GXBUS_PM_AUDIO_AAC_ADTS,     // aac??Ƶ
	GXBUS_PM_AUDIO_EAC3,         // eac3
	GXBUS_PM_AUDIO_LPCM,
	GXBUS_PM_AUDIO_DTS,
	GXBUS_PM_AUDIO_DOLBY_TRUEHD,
	GXBUS_PM_AUDIO_AC3_PLUS,
	GXBUS_PM_AUDIO_DTS_HD,
	GXBUS_PM_AUDIO_DTS_MA,
	GXBUS_PM_AUDIO_AC3_PLUS_SEC,
	GXBUS_PM_AUDIO_DTS_HD_SEC,
	GXBUS_PM_AUDIO_DRA,
} GxBusPmDataProgAudioType;

/**
 * audio�ĵȼ�
 */
typedef enum {
	GXBUS_PM_PROG_AUDIO_LECEL_HIG = 0,  // �����ȼ���,�����Ƚϴ�
	GXBUS_PM_PROG_AUDIO_LECEL_MID,      // �����ȼ���
	GXBUS_PM_PROG_AUDIO_LECEL_LOW,      // �����ȼ���
} GxBusPmDataProgAudioLevel;


typedef enum {
	GXBUS_PM_PROG_SD = 0, // �����Ŀ
	GXBUS_PM_PROG_HD,     // �����Ŀ
} GxBusPmDataProgDefinition;

/**
 * �ýṹ��ÿ��prog�����Խṹ��,
 * �û��õ���prog�����������½ṹ��
 */
typedef struct {
	/*4B */
	uint16_t id;                                 // �ý�Ŀ��id
	uint16_t tp_id;                              // �ý�Ŀ����tp��id
	/*4B */
	GxBusPmDataProgType service_type:4;          // �����ý�Ŀ��tv ���� radio
	GxBusPmDataProgAduioTrack audio_mode:4;      // ����ģʽ left right ������stereo
	GxBusPmDataProgAudioLevel audio_level:4;     // ��Ƶ�ķŴ�ȼ�
	GxBusPmDataProgVideoType video_type:4;       // �����ý�Ŀ��mpeg ���� avs
	uint8_t sdt_version;
	uint8_t pat_version;

	/*4B */
	uint16_t sat_id;                             // ��tp������tp���ϵ�id����������Ƿ�������������ǵ�id
	uint16_t tuner;                              // �ý�Ŀ������tuner,��ʼֵ������sat��tuner.

	/*4B */
	uint16_t                  service_id;        // ��Ŀ��searvice id
	uint8_t                   audio_volume;      // ����
	GxBusPmDataProgSwitch     scramble_flag : 1; // ��Ŀ���ܱ�־λ
	GxBusPmDataProgSwitch     skip_flag     : 1; // �������
	GxBusPmDataProgSwitch     lock_flag     : 1; // ������־
	GxBusPmDataProgSwitch     ttx_flag      : 1; // ttx�Ƿ���ڵı�־
	GxBusPmDataProgSwitch     subt_flag     : 1; // subt�Ƿ���ڵı�־
	GxBusPmDataProgSwitch     cc_flag       : 1; // cc�Ƿ���ڵı�־
	GxBusPmDataProgSwitch     ac3_flag      : 1; // ac3�Ƿ���ڵı�־
	GxBusPmDataProgDefinition definition    : 1;

	/*4B */
	uint32_t favorite_flag;                      // ϲ����ǣ�����ý�Ŀ�����ĸ�ϲ���飬
	// ÿһλ����һ��ϲ���� ���� ��һλΪ1 �Ǿͱ�־�ý�Ŀ����ӽ���ϲ����1
	/*4B */
	uint16_t pcr_pid;                            // ��Ŀ��pcr pid
	uint16_t pmt_pid;                            // ��Ŀ��pmt pid

	/*4B */
	uint16_t bouquet_id;                         // ��Ŀ��bouquet pid
	uint16_t video_pid;                          // ��Ŀ��video pid

	/*4B */
	uint16_t ecm_pid_v;                          // ��Ƶ��ecm pid
	uint8_t pmt_version;                         // ��ǰʹ�õ�pmt�汾
	uint8_t audio_count;                         // �ý�Ŀ����Ƶ���� ������ac3

	/*4B */
	uint16_t ac3_pid;                            // ac3��pid
	//	uint16_t count;                              // �ò������������service�Ĺۿ�Ƶ��,����ɾ��epg��ʱ�����ж�
	uint16_t cur_audio_pid;                      // ��ǰ�����Ŀ���ŵ���Ƶ��id
	//	uint16_t cur_stream_id;                      // ��ǰ�����Ŀ���ŵ���Ƶ��stream_id

	/*4B*/
	uint16_t cur_audio_ecm_pid;                  // ��ǰ��Ƶ��ecm pid
	GxBusPmDataProgAudioType cur_audio_type:8;   // ��¼��ǰaudio��type ����Ҫ4B��ô���
	uint8_t logic_valid;//add by leixj

	/*4B*/
	uint16_t ts_id;                              // ts id
	uint16_t original_id;                        // �����Ŀ��ԭ������id

	/*4B */
	uint32_t cas_id;                             // ��Ŀʹ�õļ���ϵͳ��id


	/*5*4B */
	uint8_t prog_name[MAX_PROG_NAME];            // ��Ŀ�����ƽ�Ŀ��������atsc��׼������һ�����short name
	uint32_t nvod_service_id;

	/*4B */
	uint32_t ext_size;///<�ý�Ŀ��չ��Ϣ�Ĵ�С

	/*4B*/ //dvbt2ʹ�õ�3��id
	uint8_t data_plp_id;
	uint8_t common_plp_exist;
	uint8_t common_plp_id;
	uint8_t reserved2;

	/*����atsc��׼�Ľ�Ŀ��Ϣ*/
	/*4B*/
	uint16_t major_num;
	union {
		uint16_t minor_num;
		uint16_t logicnum;
	}u3;
	/*4B*/
	union {
		uint16_t source_id;
		uint16_t locator_id;
	}u1;

	uint8_t path_select;//cvtc����
	uint8_t out_of_band;//cvtc����

	/*5*4B */
	union {
		uint8_t long_name[MAX_PROG_NAME];
		uint8_t service_provider_name[MAX_PROG_NAME];
	}u2;
	/*4B*/
	uint32_t pos;                                // �������������
} GxBusPmDataProg;

typedef enum {
	GXBUS_PM_PROG_MODIFY_SKIP = 0, // �޸Ľ�Ŀ��skip״̬
	GXBUS_PM_PROG_MODIFY_LOCK,     // �޸Ľ�Ŀ��lock״̬
} GxBusPmProgModifyBoolType;

/**
 * ÿһ��ϲ���鶼�߱�����һ���ṹ
 */
typedef struct {
	uint32_t id;                          // ��ϲ���������ݿ��е�id
	uint16_t cur_tv;
	uint16_t cur_radio;
	uint8_t fav_name[MAX_FAV_GROUP_NAME]; // ϲ���������
} GxBusPmDataFavItem;

typedef struct {
	uint16_t cas_id_begin;          // �ü���ϵͳ����ʼid,ֻҪid����cas_id_begin��cas_id_end�ķ�Χ��,��ô����ͬһ������ϵͳ
	uint16_t cas_id_end;            // �ü���ϵͳ�Ľ���id,ֻҪid����cas_id_begin��cas_id_end�ķ�Χ��,��ô����ͬһ������ϵͳ
	uint8_t cas_name[MAX_CAS_NAME]; // �ü���ϵͳ������
} GxBusPmDataCasInfot;

/*stream�Ľṹ*/
typedef struct {
	uint32_t prog_id;                    // ��stream�����Ľ�Ŀ��id
	GxBusPmDataProgAudioType audio_type; // 0-pcm 1-ac3 2-acc
	uint16_t audio_pid;                  // audio pid
	uint16_t ecm_pid;                    // ecm pid
	uint8_t name[4];                     // ��stream�Ĺ��Ҵ���
} GxBusPmDataStream;


typedef enum {
	GXBUS_PM_PROG_MOVE_BEFORE = 0, // �ƶ���Ŀ��Ŀ��id֮ǰ
	GXBUS_PM_PROG_MOVE_AFTER,      // �ƶ���Ŀ��Ŀ��id֮��
} GxBusPmProgMoveType;

typedef enum {
	GROUP_MODE_ALL = 0,
	GROUP_MODE_SAT = 0x1,
	GROUP_MODE_FAV = 0x2,
	GROUP_MODE_USER = 0x3,
}GxBusPmViewInfoGroupMode;

typedef enum {
	TAXIS_MODE_NON = 0,
	TAXIS_MODE_CAS,
	TAXIS_MODE_LETTER,
	TAXIS_MODE_TP,
	TAXIS_MODE_TUNER,
	TAXIS_MODE_SCRAMBLE,
	TAXIS_MODE_SERVICE_ID,
	TAXIS_MODE_USER,
}GxBusPmViewInfoTaxisMode;

typedef enum {
	VIEW_INFO_ENABLE  = 0x2aa,
	VIEW_INFO_DISABLE = 0x155,
}GxBusPmViewInfoStatus;

typedef enum {
	VIEW_INFO_SKIP_CONTAIN  = 0,///<��Ŀ�б���������Ľ�Ŀ
	VIEW_INFO_SKIP_VANISH ,///<��Ŀ�б����������Ľ�Ŀ
}GxBusPmViewInfoSkipView;

typedef enum {
	VIEW_INFO_ID = 0,
	VIEW_INFO_POS,
}GxBusPmViewInfoCurProgType;

typedef enum {
	VIEW_INFO_ORDER = 0,///<��������
	VIEW_INFO_REVERSE,///<��������
}GxBusPmViewInfoOrder;

typedef struct
{
	uint32_t id;//��Ŀ��id������
	uint32_t params1;//�κ�������Ա���������������������
	uint8_t params2[MAX_PROG_NAME];//�κ��ַ�����Ա�������������������ֽ׶�ֻ��name
}GxBusPmProgSort;

/**
 * ˵�����ýṹ֪���˵�ǰϵͳ���õĹۿ�ģʽ���ڳ��õĹۿ�˳��Ӧ���������
 * ��ѡ��һ���� ������ѡ��һ��sat���������Ƿ�������ѡ����ĳ�����ǣ���
 * Ҳ������ѡ����һ��ϲ���顣���п��ܾ���all��֮����ѡ��һ������ʽ��
 * ���ӣ���ǰѡ����idΪ5��tp�����飬��������ĸ����ʽ ����ѡ����a��z��
 * ��ô����ֵӦ���ǣ�group_mode = 1��taxis_mode = 2, letter_pos = 0.
 * tp_aggregate_id = 5.���Ƹ��� �����������ϵ������ϳ����ֹۿ�ģʽ
 */
typedef struct {
	/*4B*/
	uint32_t  tv_prog_cur ;                     // ���һ�β��ŵ�tv��Ŀ���Լ�¼��Ŀ��idҲ������pos,
	// ����ǵ���id,��ôȡ��Ŀ��ʱ����Ҫ����GxBus_PmProgGetById,
	// ����ǵ���posʹ��,��ôȡ��Ŀ��ʱ����Ҫ����GxBus_PmProgGetByPos
	/*4B*/
	uint32_t  radio_prog_cur ;                  // ���һ�β��ŵ�radio��Ŀ���Լ�¼��Ŀ��idҲ������pos
	/*4B*/
	GxBusPmViewInfoGroupMode  group_mode :8;    // �ۿ������ģʽ ������ ����ϲ����:
	//   0 - all
	//   1 - tp����
	//   2 - ϲ����
	//   3 - �û��Զ�����ˣ����gx_pm_prog_check��gx_pm_prog_orderʹ��

	GxBusPmViewInfoTaxisMode  taxis_mode:8;     // ѡ�������ʽ
	//   0 - ������
	//   1 - cas����
	//   2 - ��ĸ����
	//   3 - tp����
	//   4 - tuner����
	//   5 - scramble
	//   6 - service_id ������

	GxBusPmDataProgType  stream_type : 4;       // tv ������raido ģʽ �Ժ���Ҫ����ģʽ�������������Ա
	GxBusPmViewInfoCurProgType type :1;         // ����tv_prog_cur��radio_prog_cur�Ǵ���pos����id
	GxBusPmViewInfoSkipView skip_view_switch:1; // �Ƿ���Ҫ��ʾ�����Ľ�Ŀ:
	//   VIEW_INFO_SKIP_CONTAIN��ʾ������ĿҲ��Ҫ���б���
	//   VIEW_INFO_SKIP_VANISH��ʾ�����Ľ�Ŀ���������б���

	uint32_t  fav_id : 6;                       // ��ϲ���������ѡ���ϲ���� ��ǰ�׶η������֧��32��ϲ��������5λ����
	GxBusPmViewInfoOrder order:1;               // ����������������������
	uint32_t  reserved1 : 3;
	/*4B*/
	uint32_t  sat_id;                           // ��ѡ���tp���ϵ�id �������Ƿ�����˵�������ǵ�id
	/*4B*/
	uint32_t  cas_id;                           // ��cas�����ѡ���cas��id
	/*4B*/
	uint32_t  tp_id;                            // ��tp�����ѡ���tp��id
	/*4B*/
	uint32_t  tuner_num;                        // ��tuner�����ѡ���tuner
	/*4B*/
	GxBusPmViewInfoStatus  status : 10;         // view _info�Ƿ���Ч�ı��,��:
	// �״ο���ʱ���ֵ��VIEW_INFO_DISABLE��ʹ�õ��˵�ע�����ֵ�Ŀ���,
	// �����Ŀɾ���ʱ��Ϳ��԰����ֵ����ΪVIEW_INFO_DISABLE

	uint32_t  pip_switch : 1;                   // pip�Ŀ���,��������pm����ʲô���Ľ�Ŀ�б�0-�����Ŀ�б� 1-С����Ľ�Ŀ�б�
	uint32_t  pip_main_tp_id : 16;              // ����С����ʱ����������tp id
	uint32_t  reserved2 : 6;

	uint8_t  letter[MAX_CMP_NAME];              // ����ĸ�����ѡ�����ĸ,���ڽ�֧��4���ַ�����:
	//   0000 - a~z
	//   ffff - other ������ĸֱ�������ַ� ,����cctv���ǲ���������cctv��ͷ�Ľ�Ŀ

	int32_t (*gx_pm_prog_check)(GxBusPmDataProg* prog, GxBusPmProgSort* list);//����Ŀ�Ƿ����Ҫ��Ļص�����������Ҫ���Ŀ��Ҫ����������ĳ�Ա��������listָ�벢�ҷ���0��������Ҫ�󷵻�-1����ʹ�øù����������NULL
	int32_t (*gx_pm_prog_order)(const void *p1, const void *p2);//qsortʹ�õ�������������Ĳ�����ʵ��GxBusPmProgSort,��ʹ�øù����������NULL
} GxBusPmViewInfo;

/**
 *˵������ö��ָ����ͬ����һ�����ݿ⣬��Ҫ�ڲ����˶�Ӧ�����ݿ��ͬ��һ��
 *���ݲ������Ĵ洢��ȥ
 */
typedef enum
{
	GXBUS_PM_SYNC_SAT = 0,
	GXBUS_PM_SYNC_TP,
	GXBUS_PM_SYNC_PROG,
	GXBUS_PM_SYNC_FAV,
	GXBUS_PM_SYNC_EXT_PROG,
}GxBusPmSyncType;

/* Exported Functions ----------------------------------------------------- */

/**
 * @brief ���ݿ��ʼ��,���ڴ����ݿ�,������ݿⲻ������Ҫ���� ���ҳ�ʼ��
 * @param uint32_t max_sat:��������֧�ֵ������������
 *		uint32_t max_tp:��������֧�ֵ����tp����
 *		uint32_t max_prog:��������֧�ֵ����prog����
 * 		uint8_t* default_path:���Ϊnull����Ĭ�ϵ�·��
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmDbaseInit(uint32_t max_sat,uint32_t max_tp,uint32_t max_prog,uint8_t* default_path);

/**
 * @brief	�ر����ݿ�,�´���ʹ��ǰ�����ٴε��ó�ʼ�������ݿ�
 * @param	dbp:��Ҫ�رյ����ݿ�ľ��,�رյ�ʱ����û��д���ļ����޸��Զ�д��
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmDbaseClose(void);

/**
 * @brief	�������ݿ��sat tp prog veritfy �ļ����������ָ�
 * @param
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmDbaseBackup(void);

/**
 * @brief	��GxBus_PmDbaseBackup���ݵ��ڴ��лָ����ݿ�
 * @param
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmDbaseComebackFromMem(void);

/**
 * @brief	�ͷ��ڴ��еı����ļ�
 * @param
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmDbaseBackupDel(void);

/**
 * @brief	��ȡ���ǵ�����
 * @param	void
 * @return	-1:��������
 *              ��������:��������
 */
int32_t GxBus_PmSatNumGet(void);


/**
 * @brief	ͨ��λ�û�ȡ���ǵ���Ϣ
 * @param	pos:��Ҫ��ȡ��Ϣ����ʼ���ǵ�λ��
 *		Num:��Ҫ��ȡ����������
 *		sat_arry:��ȡ����Ϣ��ָ��sat_arry:��ȡ����Ϣ��ָ��,�ɸú�����ʹ���߿��ٿռ�
 * @return	-1:��������
 *		��������:��ȡ����������������
 */
int32_t GxBus_PmSatsGetByPos(uint32_t pos, uint32_t num, GxBusPmDataSat * sat_arry);

/**
 * @brief	ͨ��id��ȡ���ǵ���Ϣ
 * @param	id:��Ҫ��ȡ��Ϣ�����ǵ�id
 *		sat:��ȡ����Ϣ��ָ��
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmSatGetById(uint32_t id, GxBusPmDataSat * sat);

/**
 * @brief	�༭���ǲ���,�༭ǰ��Ҫ�Ȼ�ȡԭʼ���� �ٽ����޸� ����id���ǲ��ܸĶ���
 * @param	sat:��Ϣ��ָ��
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmSatModify(GxBusPmDataSat * sat);

/**
 * @brief	ɾ������,֧������ɾ��
 * @param	id_arry:��Ҫɾ�������ǵ�id
 *		num:��Ҫɾ������������
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmSatDelete(uint32_t * id_arry, uint32_t num);

/**
 * @brief	�������
 * @param	sat:��ӵ�����
 *
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GX_PM_DBASE_FULL:���ݿ��Ѿ�����
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmSatAdd(GxBusPmDataSat * sat);

/**
 * @brief	��ȡtp������
 * @param	void
 *
 * @return	-1:��������
 *		��������:tp����
 */
int32_t GxBus_PmTpNumGet(void);

/**
 * @brief	��ȡĳ�������µ�tp������
 * @param	sat_id:��Ҫ���ҵ�����
 *
 *
 * @return	-1:��������
 *		��������:tp����
 */
int32_t GxBus_PmTpNumGetBySat(uint16_t sat_id);

/**
 * @brief	ͨ��λ�û�ȡtp����Ϣ
 * @param	pos:��Ҫ��ȡ��Ϣ����ʼtp��λ��
 *		Num:��Ҫ��ȡ��tp����
 *		tp_arry:��ȡ����Ϣ��ָ��tp_arry:��ȡ����Ϣ��ָ��,�ɸú�����ʹ���߿��ٿռ�
 * @return	-1:��������
 *		��������:��ȡ��������tp����
 */
int32_t GxBus_PmTpGetByPos(uint32_t pos, uint32_t num, GxBusPmDataTP * tp_arry);

/**
 * @brief	ͨ��λ�û�ȡtp����Ϣ,��GxBus_PmTpNumGetBySat���ʹ��
 * @param	pos:��Ҫ��ȡ��Ϣ����ʼtp��λ��
 *		Num:��Ҫ��ȡ��tp����
 *		tp_arry:��ȡ����Ϣ��ָ��tp_arry:��ȡ����Ϣ��ָ��,�ɸú�����ʹ���߿��ٿռ�
 * @return	-1:��������
 *		��������:��ȡ��������tp����
 */
int32_t GxBus_PmTpGetByPosInSat(uint32_t pos, uint32_t num, GxBusPmDataTP * tp_arry);

/**
 * @brief	ͨ��id��ȡtp����Ϣ
 * @param	id:��Ҫ��ȡ��Ϣ��tp��id
 *			tp:��ȡ����Ϣ��ָ��
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmTpGetById(uint32_t id, GxBusPmDataTP * tp);

/**
 * @brief	�༭tp����,�༭ǰ��Ҫ�Ȼ�ȡԭʼ���� �ٽ����޸� ����id���ǲ��ܸĶ���
 * @param	tp:��Ϣ��ָ��
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmTpModify(GxBusPmDataTP * tp);

/**
 * @brief	ɾ��tp,֧������ɾ��
 * @param	id_arry:��Ҫɾ����tp��id
 *		num:��Ҫɾ����tp����
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmTpDelete(uint32_t * id_arry, uint32_t num);

/**
 * @brief	���tp�Ƿ���� sat ȱ�ټ�������
 * @param	sat_id:��Ҫ����sat
 *		fre:��Ҫ����Ƶ��
 *		symbol:��Ҫ���ķ�����,�����c��t�ķ�����ֵ�������⴫
 *		polar:���ļ������� ֻ�����Ƿ�����tp����в���Ч
 *		modulation:�����Ʒ�ʽ��ֻ����c������tp������Ч
 *		tp_id:���������ͬtp�᷵�����һ����ͬ��tp��id����������Ϊ0
 *
 * @return	0  : ��tp������
 *		>0 : ��tp�Ѿ�����
 *		-1 : ʧ��
 */
int32_t GxBus_PmTpExistChek(uint16_t sat_id,
		uint32_t fre,
		uint32_t symbol,
		GxBusPmTpPolar polar,
		fe_modulation_t modulation,
		uint16_t* tp_id);

/**
 * @brief	���tp�Ƿ���� sat ȱ�ټ�������
 * @param	sat_id:��Ҫ����sat
 *		fre1,fre2:��Ҫ����Ƶ�� ��fre1<=...<=fre2ʱ ��Ϊ����ͬƵ��
 *		symbol1,symbol2:��Ҫ���ķ�����,�����c��t�ķ�����ֵ�������⴫ symbol1<=...<=symbol2
 *		polar:���ļ������� ֻ�����Ƿ�����tp����в���Ч
 *		modulation:�����Ʒ�ʽ��ֻ����c������tp������Ч
 *		tp_id:���������ͬtp�᷵�����һ����ͬ��tp��id����������Ϊ0
 *
 * @return	0  : ��tp������
 *		>0 : ��tp�Ѿ�����
 *		-1 : ʧ��
 */
int32_t GxBus_PmTpExistChekBound(uint16_t sat_id,
		uint32_t fre1,
		uint32_t fre2,
		uint32_t symbol1,
		uint32_t symbol2,
		GxBusPmTpPolar polar,
		fe_modulation_t modulation,
		uint16_t* tp_id);

/**
 * @brief	���tp
 * @param	tp:��ӵ�tp
 * @return	GXCORE_SUCCESS:ִ������
 *		GX_PM_DBASE_FULL:���ݿ���
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmTpAdd(GxBusPmDataTP * tp);

/**
 * @brief	��ȡprog������ ʹ�ô˽ӿ�ʱ��������˹ۿ�ģʽ
 *		Ӧ���ȸ���ϵͳ��Ϣ���view_info
 *		�ٵ��ô˽ӿڻ�ȡ�µĹۿ�ģʽ�µĽ�Ŀ����
 * @param	void
 * @return	-1:��������
 *               ��������:prog����
 */
int32_t GxBus_PmProgNumGet(void);

/**
 * @brief	ͨ��λ�û�ȡprog����Ϣ ʹ�ô˽ӿ�ʱ��������˹ۿ�ģʽ
 *		Ӧ���ȸ���ϵͳ��Ϣ���view_info
 *		�ٵ��ô˽ڿڸ��½�Ŀ�б�,����ע����ô˽ڿ�ǰһ��Ҫ����GxBus_PmProgNumGet
 *		ȷ�ϵ�ǰ��Ŀ������,���Ǳ�֤û��ɾ�����ӹ���Ŀ ��ô�ǲ���Ҫ�ظ�����GxBus_PmProgNumGet��
 * @param	pos:��Ҫ��ȡ��Ϣ����ʼprog��λ��
 *		Num:��Ҫ��ȡ��prog����
 *		prog_arry:��ȡ����Ϣ��ָ��prog_arry:��ȡ����Ϣ��ָ��,�ɸú�����ʹ���߿��ٿռ�
 * @return	-1:��������
 *		��������:��ȡ��������prog����
 */
int32_t GxBus_PmProgGetByPos(uint32_t pos, uint32_t num, GxBusPmDataProg * prog_arry);

/**
 * @brief	ͨ��id��ȡprog����Ϣ
 * @param	id:��Ҫ��ȡ��Ϣ��prog��id
 *		prog:��ȡ����Ϣ��ָ��
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmProgGetById(uint32_t id, GxBusPmDataProg * prog);
/**
 * @brief ��ȡָ����prog
 * @param uint32_t ts_id:��service_idȷ��һ��service �����Ĵ���0xffffffff
 uint32_t service_id:��ts_idȷ��һ��service �����Ĵ���0xffffffff
original_id:ȷ��һ��service �����Ĵ���0xffffffff
prog::��ȡ����Ϣ��ָ��

 * @return     	GXCORE_SUCCESS:ִ������
GXCORE_ERROR:ִ��ʧ��
 */
int32_t GxBus_PmProgGetBySpecialId(uint32_t ts_id,uint32_t service_id, uint32_t original_id, GxBusPmDataProg * prog);

/**
 * @brief	ͨ��id��ȡprog��url��Ϣ,����Ϣ��Ҫ��Ϊ�˸�player�����õ�,prog_url��
 *		�ռ�����ʹ�ýӿڵĵط������ ��СΪ GX_PM_MAX_PROG_URL_SIZE
 * @param	prog:��Ҫ��ȡurl��Ϣ��prog
 *		prog_url:��ȡ��url��Ϣ��buffer
 *		uint32_t size:buffer�Ĵ�С ���С��GX_PM_MAX_PROG_URL_SIZE�᷵�ش���
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmProgUrlGet(GxBusPmDataProg* prog, int8_t* prog_url,uint32_t size);

/**
 * @brief	ͨ��id�޸Ľ�Ŀ��Ϣ����bool��ʽ��ʾ����Ϣ,����skip:0-���� 1-������
 * @param	type:�޸ĵ�����
 *		id_arry:��Ҫ�޸ĵ�id
 *		num:��Ҫ�޸ĵĽ�Ŀ������

 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmProgBoolModify(GxBusPmProgModifyBoolType type, uint32_t * id_arry, uint32_t num);

/**
 * @brief	�޸Ľ�Ŀ��ϲ������Ϣ һ��һ��ϲ����,���ԭ�Ƚ�Ŀ�������ϲ������ô���
 *		�ӿڻ�ѽ�Ŀ��ϲ����ɾ��,�����Ŀԭ�Ȳ��������ϲ����,��ô����ӿڻ�ѽ�Ŀ��ӽ�ȥ
 * @param	fav_id:��Ҫ�޸ĵ�ϲ����
 *		id_arry:��Ҫ�޸ĵĽ�Ŀ��id
 *		Num:��Ҫ�޸ĵĽ�Ŀ������
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmProgFavModify(uint32_t fav_id, uint32_t * id_arry, uint32_t num);

/**
 * @brief	�༭prog����,�༭ǰ��Ҫ�Ȼ�ȡԭʼ���� �ٽ����޸� ����id���ǲ��ܸĶ���
 * @param	prog:��Ϣ��ָ��
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmProgInfoModify(GxBusPmDataProg * prog);

/**
 * @brief	ɾ��prog,֧������ɾ��
 * @param	id_arry:��Ҫɾ����prog��id
 *		num:��Ҫɾ����prog����
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmProgDelete(uint32_t * id_arry, uint32_t num);

/**
 * @brief	���prog
 * @param	prog:��ӵ�prog
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 *		GX_PM_DBASE_FULL:���ݿ��Ѿ�����
 */
status_t GxBus_PmProgAdd(GxBusPmDataProg * prog);

/**
 * @brief	�ƶ���Ŀ ע�� target_id���ܳ�����id_arry��
 * @param	id_arry:��Ҫ�ƶ��Ľ�Ŀid
 *		Num:��Ҫ�ƶ��Ľ�Ŀ����
 *		target_id:Ŀ��id,���� �β���Ϊ5 ����Ҫ��ѡ�еĽ�Ŀ�ƶ�����ĿidΪ5�Ľ�Ŀǰ
 *		type:�ƶ�ģʽ,���ƶ���Ŀ��id֮ǰ����֮��
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmProgMove(uint32_t * id_arry,
		uint32_t num,
		uint32_t target_id,
		GxBusPmProgMoveType type);

/**
 * @brief	����һ��������ƶ���Ŀ����Ҫ�ɵ��õ�����֯�õ�ǰ�ۿ�ģʽ�µ����н�Ŀ��˳��
 *		�磬��ǰ�ۿ�ģʽ����10��̨����ô��ʼ˳��϶���0~9�����Ҫ�����һ��
 *		̨�ƶ�����ǰ�棬��ôpos_arry={9,0,1,2,3,4,5,6,7,8};�����ƶ��������������
 * @param	pos_arry:���кõ�˳����СֵΪ0���ֵ�϶�Ϊnum��1
 *		Num:��Ҫ�ƶ��Ľ�Ŀ�������϶����ڵ�ǰģʽ�µĽ�Ŀ����
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmProgMoveSpecial(uint32_t * pos_arry, uint32_t num);

/**
 * @brief ����Ŀʱ�����,����������̨ʱ��ı���
 * @param tp_id:��Ҫ����tp_id
ts_id:��Ҫ����ts id
service_id:��Ҫ����service id
original_id:��Ҫ����ԭʼ����id
tuner:��Ҫ����tuner��
uint8_t data_plp_id: dvbt2��Ŀ���У������봫��0xff
uint8_t common_plp_exist: dvbt2��Ŀ���У������봫��0xff
uint8_t common_plp_id: dvbt2��Ŀ���У������봫��0xff

 * @return     	0:�ý�Ŀ������
 >1:�ý�Ŀ�Ѿ�����
 -1:ʧ��
 */
//����һ��tp id ������ԭʼ����id ������̨ʱ��Ҫ���Ӵ洢����
int32_t GxBus_PmProgExistChek(uint16_t tp_id,
		uint16_t ts_id,
		uint16_t service_id,
		uint16_t original_id,
		uint16_t tuner,
		uint8_t data_plp_id,
		uint8_t common_plp_exist,
		uint8_t common_plp_id);

/**
 * @brief	��ȡָ����prog��pos,��Ҫ����epgɾ��serviceʱ���ж�,
 * @param	uint32_t ts_id:��service_idȷ��һ��service
 *		uint32_t service_id:��ts_idȷ��һ��service
 *
 * @return	-1:��ȡʧ��
 *		����ֵ:��Ŀ��pos
 */
int32_t GxBus_PmProgPosGet(uint32_t ts_id,uint32_t service_id);

/**
 * @brief	��ȡָ����prog��pos,��Ҫ����epgɾ��serviceʱ���ж�
 * @param	uint32_t service_id:ȷ��һ��service
 *
 * @return	-1:��ȡʧ��
 *		����ֵ:��Ŀ��pos
 */
int32_t GxBus_PmProgPosGetByServiceId(uint32_t service_id);

/**
 * @brief	����view info���½�����Ŀ�б�һ���ǲ���Ҫ���õģ���ΪGxBus_PmSync
 *		��GxBus_PmViewInfoModify�����ؽ���Ŀ�б�����������Ҫ
 * @param
 *
 * @return	-1:��ȡʧ��
 *		����ֵ:�ÿģʽ�µ�prog����
 */

int32_t GxBus_PmProgListRebulid(void);
/**
 * @brief	�����Զ����Ŀ��һ���������Զ����Ŀ����ôview_info������
 *              ���ã���Ŀ��˳�򽫰����Զ����Ŀ�����С����ǵ���
 *              GxBus_PmProgUserListRemove.�Ƴ����Զ����б���ô��Ŀ�б��ֽ�
 *              �ָ���view info���Ƶ�״̬������Ҫע�⣬�ڸı��Ŀ����ǰ�������
 *              �����Զ����Ŀ���ٺ��ʵ�ʱ������save�Զ������Ȼ��Ŀ����ҡ�
 * @param	uint32_t* id_arry���洢��Ŀid�ŵĿռ䣬��Щid�����û��ź���ġ�
 *              uint32_t num��id_arry���м���id
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */

status_t GxBus_PmProgUserListSave(uint32_t* id_arry,uint32_t num);
/**
 * @brief	ɾ���Զ����Ŀ��һ���������Զ����Ŀ����ôview_info������
 *              ���ã���Ŀ��˳�򽫰����Զ����Ŀ�����С����ǵ���
 *              GxBus_PmProgUserListRemove.�Ƴ����Զ����б���ô��Ŀ�б��ֽ�
 *              �ָ���view info���Ƶ�״̬������Ҫע�⣬�ڸı��Ŀ����ǰ�������
 *              �����Զ����Ŀ���ٺ��ʵ�ʱ������save�Զ������Ȼ��Ŀ����ҡ�
 *              del�Զ����Ŀ�б��ʱ���������һ�α����view info �ؽ���Ŀ
 *              �б�
 * @param
 *
 * @return	GXCORE_SUCCESS:ִ������
 */
status_t GxBus_PmProgUserListDel(void);

/**
 * @brief	��ȡcas������
 * @param	void
 *
 * @return	-1:��������
 *              ��������:cas ��
 */
int32_t GxBus_PmCasNumGet(void);

/**
 * @brief	ͨ��λ�û�ȡcas��Ϣ
 * @param	pos:λ��
 *		Cas:cas��Ϣ
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmCasGetByPos(uint32_t pos, GxBusPmDataCasInfot * cas);

/**
 * @brief	��ȡ��Ŀ��cas,���ȵôӽ�Ŀ�л�ȡcas_id
 * @param	cas_id:cas��id
 *		cas:case��Ϣ
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmCasGetById(uint32_t cas_id, GxBusPmDataCasInfot * cas);

/**
 * @brief	��ȡϲ���������
 * @param	void
 *
 * @return     -1:��������
 *             ��������:��ȡ��fav group ��¼��
 */
int32_t GxBus_PmFavGroupNumGet(void);

/**
 * @brief	ͨ��λ�û�ȡfav group��Ϣ
 * @param	pos:λ��
 *		num:��Ҫ��ȡ������
 *		fav_arry:cas��Ϣ
 *
 * @return	-1:ʧ��
 *		��������:��ȡ����������
 */
int32_t GxBus_PmFavGroupGetByPos(uint32_t pos, uint32_t num, GxBusPmDataFavItem * fav_arry);

/**
 * @brief	ͨ��id��ȡϲ������Ϣ
 * @param	id:ϲ����id
 *		fav_arry:cas��Ϣ
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmFavGroupGetById(uint32_t id, GxBusPmDataFavItem * fav);

/**
 * @brief	�༭fav����,�༭ǰ��Ҫ�Ȼ�ȡԭʼ���� �ٽ����޸� ����id���ǲ��ܸĶ���
 * @param	fav:��Ϣ��ָ��
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmFavGroupModify(GxBusPmDataFavItem * fav);

/**
 * @brief	��ʼһ������ ����Ӧ��:������̨ʱ��search������Ʊ����Ŀ,berkeley�� ��û��ʵ��
 * @param	void
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmTransactionBegin(void);

/**
 * @brief	�ύһ������ ����Ӧ��:������̨ʱ��search������Ʊ����Ŀ,berkeley�� ��û��ʵ��
 * @param	void
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmTransactionCommit(void);

/**
 * @brief	�ع�һ������ ȡ����ʼ�������,�ָ�����ʼǰ��״̬,berkeley�� ��û��ʵ��
 * @param	void
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */

status_t GxBus_PmTransactionRollback(void);


status_t GxBus_PmViewInfoMemSet(GxBusPmViewInfo* sys);
status_t GxBus_PmViewInfoMemClear(void);

/**
 * @brief	��ȡ�ۿ�ģʽ
 *
 * @param	void
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmViewInfoGet(GxBusPmViewInfo* sys);

/**
 * @brief	�޸� �ۿ�ģʽ
 *
 * @param	void
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t  GxBus_PmViewInfoModify(GxBusPmViewInfo* sys);

/**
 * @brief	��ȡ��ǰ�ۿ��Ľ�Ŀ��Ϣ
 *
 * @param	uint32_t tp_id,
 *              uint32_t cur_prog   : ��ǰ�ۿ���Ŀ��pos����id ��GxBusPmViewInfo.type����
 *              uint32_t ts_id,
 *              uint32_t service_id
 *
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t  GxBus_PmViewInfoCurPlayGet(uint32_t* tp_id,
		uint32_t* cur_prog,
		uint32_t* ts_id,
		uint32_t* service_id);

/**
 * @brief     �ָ����ݿ��Ĭ����Ϣ
 *
 * @param     uint32_t max_sat      : ��������֧�ֵ������������
 *            uint32_t max_tp       : ��������֧�ֵ����tp����
 *            uint32_t max_prog     : ��������֧�ֵ����prog����
 *            uint8_t* default_path : ���Ϊnull����Ĭ�ϵ�·��
 *
 * @return    GXCORE_SUCCESS:ִ������
 *            GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmLoadDefault(uint32_t max_sat,uint32_t max_tp,uint32_t max_prog,uint8_t* default_path);

/**
 * @brief	ͬ�����ݿ� ִ�к����ݱ�����д�����ݿ�
 * @param	type:��Ҫͬ������������
 * @return	GXCORE_SUCCESS:ִ������
 *		GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmSync(GxBusPmSyncType type);
/**
 * @brief ������չ��Ϣ
 *
 * @param    prog_id : ������չ��Ϣ�Ľ�Ŀid
 *           size    : ��չ��Ϣ�Ĵ�С
 *           void* p : ��չ��Ϣ
 *
 * @return   GXCORE_SUCCESS:ִ������
 *           GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmProgExtInfoAdd(uint32_t prog_id,uint32_t size, void* p);

/**
 * @brief   ��ȡ��Ŀ��չ��Ϣ
 *
 * @param   prog_id : ��Ŀid
 *          size    : ��չ��Ϣ�Ĵ�С
 *          void* p : ���ڱ�����չ��Ϣ�Ŀռ�
 *
 * @return  GXCORE_SUCCESS : ִ������
 *          GXCORE_ERROR   : ִ��ʧ��
 */
status_t GxBus_PmProgExtInfoGet(uint32_t prog_id,uint32_t size, void* p);

/**
 * @brief ��ȡpm��ģ����
 *
 * @return   GXCORE_SUCCESS:ִ������
 *           GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmLock(void);

/**
 * @brief  �ͷ�pm��ģ����
 *
 * @return   GXCORE_SUCCESS:ִ������
 *           GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmUnlock(void);

/**
 * @brief  ��ȡ���ݿ�仯��¼�ţ������ж����ݿ��Ƿ����˱仯
 * @return  ��¼��
 */
int32_t GxBus_PmGetRecord(void);

/* @brief   �ѵ�ǰ���ݿ���Ϣ���ɷ���Ĭ�����ݿ⹤�߸�ʽ���ļ�
 *
 * @param   file_patch:�ļ�����·��
 *
 * @return  GXCORE_SUCCESS:ִ������
 *          GXCORE_ERROR:ִ��ʧ��
 */
status_t GxBus_PmCreateDefaultDb(int8_t* file_patch);

__END_DECLS

#endif

/*@}*/

