/**@defgroup search_service Search Service*/
/*@{*/

#ifndef __GXSEARCH_H__
#define __GXSEARCH_H__

#include "gxmsg.h"
#include "gxbus.h"
#include "module/pm/gxpm_manage.h"
#include "module/si/si_parser.h"
#include "gxcore.h"

__BEGIN_DECLS

#define GX_SEARCH_ALL (3)                                    ///< �������н�Ŀ
//#define MAX_PROG_NAME (16)                                 ///< �������pm�����Ѿ��ɶ���,������ʱ����Ҫ���������¶�����

#define SI_MAX_MULTI_NAME_COUNT  (2)

#define GXBUS_SEARCH_LANG_PRIORITY "gxsearch_lang_priority"  ///< ����ʱ���ȴ洢�����ԣ��硰eng_chn�����һ��������ΪӢ��ڶ���������Ϊ���ģ�
                                                             ///< ��ͬ���Լ���_���������ҹ��Ҵ���Ҫ����iso9660�淶
#define  GXBUS_SEARCH_LANG_DEFAULT "eng_chn"                 ///< Ĭ��Ӣ������

#define GXBUS_SEARCH_UTF8 "gxsearch_utf8"                    ///< ����ʱ�Ƿ�ѽ�Ŀ����תΪutf-8

#define GXBUS_SEARCH_UTF8_YES 1                              ///< ����ʱ�Ƿ�ѽ�Ŀ����תΪutf-8
#define GXBUS_SEARCH_UTF8_NO  0                              ///< ����ʱ�Ƿ�ѽ�Ŀ����תΪutf-8

#define GXBUS_SEARCH_NIT_LOOP "gxsearch_nit_loop"            ///< nit����ʱ�Ƿ����nitѭ������
#define GXBUS_SEARCH_NIT_LOOP_YES 1                          ///< nit����ʱ����tp��ѭ������
#define GXBUS_SEARCH_NIT_LOOP_NO  0                          ///< nit����ʱ������tp��ѭ������

#define GXBUS_SEARCH_DTS_SUPPORT "gxsearch_dts_support"      ///< �Ƿ�֧��DTS
#define GXBUS_SEARCH_DTS_YES      1                         
#define GXBUS_SEARCH_DTS_NO  0                          


#ifndef TRUE
#  define TRUE    1
#  define FALSE   0
#endif

#if 0
/*äɨ������*/
#define     BLIND_SCAN_STEP_MHZ         (4)

/*äɨÿ��window�ķ�Χ*/
#define     BLIND_SCAN_WINDOW_SIZE_K    (16000)

/*äɨ��Ƶ�ʷ�Χ*/
#define     BLIND_SCAN_LOW_FREQ_MHZ     (1467)
#define     BLIND_SCAN_HIGH_FREQ_MHZ    (1492)
#endif


/* äɨ���� */
#define     BLIND_SCAN_POLAR_H          (0)//18V
#define     BLIND_SCAN_POLAR_V          (1)//13V
#define     BLIND_SCAN_POLAR_ALL        (2)
/* äɨ���� */
#define     BLIND_SCAN_LNB_OCS          (0)
#define     BLIND_SCAN_LNB_SINGLE       (1)
/* äɨ�������� */
#define     BLIND_SCAN_LNB_C            (0)
#define     BLIND_SCAN_LNB_KU           (1)
/* һ��äɨ������������tp���� */
#define     BLIND_SCAN_TP_COUNT         (200)

/*���caϵͳ�Ƿ���ȷ ����0����ca system���� ����1����ca system��ȷ*/
typedef uint32_t (*GxSearchCheckCa)(uint16_t ca_system_id,uint16_t ele_pid,uint16_t ecm_pid);

/*����̨ʱȷ���Ƿ���Ҫ���˸�pid��pmt*/
typedef bool (*GxSearchCheckPmtPid)(uint16_t pid,uint16_t prog_num);

/**�ýṹ���������˸���������ʽ��������������ʽ��Ҫ�ڴ˽ṹ�����ӡ�*/
typedef enum {
	GX_SEARCH_AUTO = 0, ///< auto����
	GX_SEARCH_MANUAL,   ///< manual����
	GX_SEARCH_PID,      ///< pid����
} GxSearchType;

typedef enum {
	GX_SEARCH_NIT_ENABLE = 0, ///< nit����ʹ��
	GX_SEARCH_NIT_DISABLE,    ///< nit������ʹ��
} GxSearchNitSwitch;

/**
 * ˵�������������Ϳ���������ṹ�����,
 * �ýṹ��GxSearchFtaCas �ṹ
 * ����������������������������Ӧ�õĲ�ͬ�������,
 * ����λԤ����Խ�ϸ��ַ�ʽ,
 * ����0x3����GX_SEARCH_TV ��GX_SEARCH_RADIO ������൱���ֽ׶ε�all����
 */
typedef enum {
	GX_SEARCH_TV           = 1,            ///< ֻ����TV��Ŀ
	GX_SEARCH_RADIO        = 2,            ///< ֻ����radio��Ŀ
	GX_SEARCH_TV_RADIO_ALL = GX_SEARCH_ALL ///< �������н�Ŀ
} GxSearchTVRadio;

/**
 * ˵�������������Ϳ���������ṹ�����,
 * �ýṹ��GxSearchTVRadio�ṹ
 * ����������������������������Ӧ�õĲ�ͬ�������,
 * ����λ������Խ�ϸ��ַ�ʽ,
 * ����0x3����GX_SEARCH_FTA ��GX_SEARCH_CAS ������൱���ֽ׶�all����
 */
typedef enum {
	GX_SEARCH_FTA         = 1,            ///< ֻ������ѽ�Ŀ
	GX_SEARCH_CAS         = 2,            ///< ֻ�������ܽ�Ŀ
	GX_SEARCH_FTA_CAS_ALL = GX_SEARCH_ALL ///< �������н�Ŀ
} GxSearchFtaCas;

/**
 * pid����ʱָ���ĸ���pid����,
 * ���Ժ�s�Լ�c t�������ṹ�����ʹ����ϳ�����pid������ʽ
 * pid����ʱ�����pid��ֵΪ0xffffffff�������Ա�
 */
typedef struct {
	uint32_t video_pid; ///< ��Ҫ�����Ľ�Ŀ��video pid
	uint32_t audio_pid; ///< ��Ҫ�����Ľ�Ŀ��audio pid
	uint32_t pcr_pid;   ///< ��Ҫ�����Ľ�Ŀ��pcr pid
} GxPidSearch;

/**
 * ���������Ĳ����ṹ��,
 * ���ʹauto�����Ļ� max_num����ָҪ���������ǵ�����,
 * id_ array �������ǵ�id������
 * tp������ʱ���������ָtp��������id
 */
typedef struct {
	uint32_t max_num;       ///< ��Ҫ������transport stream������sat������
	uint32_t *array;        ///< ��Ҫ������tp����sat���ϵ�id������
	uint32_t *ts;           ///< ��Ҫ������ts��,�����auto scan����ôts�ŵ�˳���id�������id˳��һһ��Ӧ,����Ҫ��ֵ��������null
	GxPidSearch params_pid; ///< ���scan_typeѡ����pid����,��ô�����Ա��ָ������Ҫƥ���pid
} GxSatSearch;

/**���������Ĳ����ṹ��*/
typedef struct {
	uint32_t sat_id;  ///< ����������id
	uint32_t max_num; ///< ��Ҫ������transport stream������
	uint32_t *array;  ///< ��Ҫ������tpid������
	uint32_t *ts;     ///< ��Ҫ������ts��,����Ҫ��ֵ��������null
} GxCableSearch;


/**T�����Ĳ����ṹ��*/
typedef struct {
	uint32_t sat_id;  ///< ����������id
	uint32_t max_num; ///< ��Ҫ������transport stream������
	uint32_t *array;  ///< ��Ҫ������tpid������
	uint32_t *ts;     ///< ��Ҫ������ts��,����Ҫ��ֵ��������null
} GxTSearch;

/**DTMB�����Ĳ����ṹ��*/
typedef struct {
	uint32_t sat_id;  ///< ����������id
	uint32_t max_num; ///< ��Ҫ������transport stream������
	uint32_t *array;  ///< ��Ҫ������tpid������
	uint32_t *ts;     ///< ��Ҫ������ts��,����Ҫ��ֵ��������null
} GxDtmbSearch;

/**
 * ��̨������չ����Ҫ�û�������Ҫ���˵ı��Լ�ƥ������������ע��һ��������˽�к���
 * ����lcn�ռ���ø���չʵ�ֽ���
 */
typedef struct {
	uint16_t pid;                         ///< ���pid ��ֵ
	uint16_t time_out;

	uint8_t  match_depth;                 ///< ƥ�����
	uint32_t reserve:24;

	uint8_t  match[18];                   ///< ƥ��ֵ
	uint8_t  mask[18];                    ///< ƥ��ֵ�����룬��ӦλΪ1����ƥ������㹻���Żᰴƥ��ֵ������
	private_table_parser table_parse_fun; ///< ˽�н�������ָ��;
} GxSearchExtend;

/**
 * ����ʱ����ű�ĳ�ʱʱ������,��λΪms�����Ϊ0����ô��ʹ��Ĭ��ֵ
 */
typedef struct {
	uint16_t   pat; ///< pat��ĳ�ʱʱ��
	uint16_t   sdt; ///< sdt��ĳ�ʱʱ��
	uint16_t   nit; ///< nit��ĳ�ʱʱ��
	uint16_t   pmt; ///< pmt��ĳ�ʱʱ��
} GxSearchTimeOut;

/**
 * ˵����appΪ����ʵ����̨���ܣ�����Ҫ��д���ϵ�һ���ṹ�壬
 * Ȼ����PMServiceMsgID_StarScan��Ϣ�����Ҵ�����д�õĽṹ��
 */
typedef void (*GxSearchDiseqc)(uint32_t sat_id,fe_sec_voltage_t polar,int32_t sat22k);
typedef status_t (*GxSearchModifyProg)(GxBusPmDataProg* prog );//�����ݿ����ӽ�Ŀǰ��ص��ú��������û��޸Ľ�Ŀ���ݣ�����GX_SEARCH_OK,��ѽ�Ŀ���뵽���ݿ�

typedef struct {
	GxSearchType scan_type;               ///< ѡ�����������ʽ
	GxSearchTVRadio tv_radio;             ///< ѡ������tv��Ŀ����radio��Ŀ����ȫ��
	GxSearchFtaCas fta_cas;               ///< ѡ��������ѽ�Ŀ���Ǽ��ܽ�Ŀ����ȫ��
	GxSearchNitSwitch nit_switch;         ///< �Ƿ�����nit����
	GxSatSearch params_s;
	GxSearchExtend*  ext;                 ///< ��̨��չ����
	uint32_t    ext_num;                  ///< ��չ���˵�����
	uint32_t*  ext_tp_id;                 ///< ��Щtp��Ҫ���б�����չ����
	uint32_t   ext_tp_num;                ///< tp������
	GxSearchTimeOut time_out;             ///< ���ű�ĳ�ʱʱ��
	GxSearchDiseqc search_diseqc;
	GxSearchCheckCa check_ca_fun;         ///< ���caϵͳ�Ƿ���ȷ
	uint32_t demux_id;//ʹ���ĸ�demux
	GxSearchModifyProg  modify_prog;
	GxSearchCheckPmtPid check_pmtpid_fun;
	private_table_parser sdt_parse_fun;
	private_table_parser pmt_parse_fun;   ///< pmt��˽�н�������������pmt��Ҫ��pat��ȡpid��û�취ʹ��GxSearchExtend
} GxMsgProperty_ScanSatStart;

/**˵����appΪ����ʵ����̨���ܣ�
 * ����Ҫ��д���ϵ�һ���ṹ�壬
 * Ȼ����PMServiceMsgID_ CableScanStart��Ϣ�����Ҵ�����д�õĽṹ��
 */
typedef struct {
	GxSearchType scan_type;               ///< ѡ�����������ʽ
	GxSearchTVRadio tv_radio;             ///< ѡ������tv��Ŀ����radio��Ŀ����ȫ��
	GxSearchFtaCas fta_cas;               ///< ѡ��������ѽ�Ŀ���Ǽ��ܽ�Ŀ����ȫ��
	GxSearchNitSwitch nit_switch;         ///< �Ƿ�����nit����
	GxCableSearch params_c;
	private_table_parser pmt_parse_fun;   ///< pmt��˽�н�������������pmt��Ҫ��pat��ȡpid��û�취ʹ��GxSearchExtend
	GxSearchCheckCa check_ca_fun;         ///< ���caϵͳ�Ƿ���ȷ
	GxSearchExtend*  ext;                 ///< ��̨��չ����
	uint32_t   ext_num;                   ///< ��չ���˵�����
	uint32_t*  ext_tp_id;                 ///< ��Щtp��Ҫ���б�����չ����
	uint32_t   ext_tp_num;                ///< tp������
	GxSearchTimeOut time_out;             ///< ���ű�ĳ�ʱʱ��
	uint32_t demux_id;//ʹ���ĸ�demux
	GxSearchModifyProg  modify_prog;
	GxSearchCheckPmtPid check_pmtpid_fun;
	private_table_parser sdt_parse_fun;
} GxMsgProperty_ScanCableStart;

/**
 * ˵����appΪ����ʵ����̨���ܣ�
 * ����Ҫ��д���ϵ�һ���ṹ�壬
 * Ȼ����PMServiceMsgID_ CableScanStart��Ϣ�����Ҵ�����д�õĽṹ��
 */
typedef struct {
	GxSearchType scan_type;               ///< ѡ�����������ʽ
	GxSearchTVRadio tv_radio;             ///< ѡ������tv��Ŀ����radio��Ŀ����ȫ��
	GxSearchFtaCas fta_cas;               ///< ѡ��������ѽ�Ŀ���Ǽ��ܽ�Ŀ����ȫ��
	GxSearchNitSwitch nit_switch;         ///< �Ƿ�����nit����
	GxTSearch params_t;
	GxSearchExtend*  ext;                 ///< ��̨��չ����
	private_table_parser pmt_parse_fun;   ///< pmt��˽�н�������������pmt��Ҫ��pat��ȡpid��û�취ʹ��GxSearchExtend
	GxSearchCheckCa check_ca_fun;         ///< ���caϵͳ�Ƿ���ȷ
	uint32_t   ext_num;                   ///< ��չ���˵�����
	uint32_t*  ext_tp_id;                 ///< ��Щtp��Ҫ���б�����չ����
	uint32_t   ext_tp_num;                ///< tp������
	GxSearchTimeOut time_out;             ///< ���ű�ĳ�ʱʱ��
	uint32_t demux_id;//ʹ���ĸ�demux
	GxSearchModifyProg  modify_prog;
	GxSearchCheckPmtPid check_pmtpid_fun;
	private_table_parser sdt_parse_fun;
} GxMsgProperty_ScanTStart;

/**
 * ˵����appΪ����ʵ����̨���ܣ�
 * ����Ҫ��д���ϵ�һ���ṹ�壬
 * Ȼ����PMServiceMsgID_ CableScanDtmbtart��Ϣ�����Ҵ�����д�õĽṹ��
 */
typedef struct {
	GxSearchType scan_type;               ///< ѡ�����������ʽ
	GxSearchTVRadio tv_radio;             ///< ѡ������tv��Ŀ����radio��Ŀ����ȫ��
	GxSearchFtaCas fta_cas;               ///< ѡ��������ѽ�Ŀ���Ǽ��ܽ�Ŀ����ȫ��
	GxSearchNitSwitch nit_switch;         ///< �Ƿ�����nit����
	GxDtmbSearch params_dtmb;
	GxSearchExtend*  ext;                 ///< ��̨��չ����
	private_table_parser pmt_parse_fun;   ///< pmt��˽�н�������������pmt��Ҫ��pat��ȡpid��û�취ʹ��GxSearchExtend
	GxSearchCheckCa check_ca_fun;         ///< ���caϵͳ�Ƿ���ȷ
	uint32_t   ext_num;                   ///< ��չ���˵�����
	uint32_t*  ext_tp_id;                 ///< ��Щtp��Ҫ���б�����չ����
	uint32_t   ext_tp_num;                ///< tp������
	GxSearchTimeOut time_out;             ///< ���ű�ĳ�ʱʱ��
	uint32_t demux_id;//ʹ���ĸ�demux
	GxSearchModifyProg  modify_prog;
	GxSearchCheckPmtPid check_pmtpid_fun;
	private_table_parser sdt_parse_fun;
} GxMsgProperty_ScanDtmbStart;

/**
 * ˵����appΪ����ʵ����̨���ܣ�
 * ����Ҫ��д���ϵ�һ���ṹ�壬
 * Ȼ����PMServiceMsgID_ CableScanDtmbtart��Ϣ�����Ҵ�����д�õĽṹ��
 */
typedef struct {
	GxSearchType scan_type;               ///< ѡ�����������ʽ
	GxSearchTVRadio tv_radio;             ///< ѡ������tv��Ŀ����radio��Ŀ����ȫ��
	GxSearchFtaCas fta_cas;               ///< ѡ��������ѽ�Ŀ���Ǽ��ܽ�Ŀ����ȫ��
	GxSearchNitSwitch nit_switch;         ///< �Ƿ�����nit����
	GxTSearch params_t;
	GxSearchExtend*  ext;                 ///< ��̨��չ����
	private_table_parser pmt_parse_fun;   ///< pmt��˽�н�������������pmt��Ҫ��pat��ȡpid��û�취ʹ��GxSearchExtend
	GxSearchCheckCa check_ca_fun;         ///< ���caϵͳ�Ƿ���ȷ
	uint32_t   ext_num;                   ///< ��չ���˵�����
	uint32_t*  ext_tp_id;                 ///< ��Щtp��Ҫ���б�����չ����
	uint32_t   ext_tp_num;                ///< tp������
	GxSearchTimeOut time_out;             ///< ���ű�ĳ�ʱʱ��
	uint32_t demux_id;                    ///< ʹ���ĸ�demux
	GxSearchModifyProg  modify_prog;
	GxSearchCheckPmtPid check_pmtpid_fun;
	private_table_parser sdt_parse_fun;
} GxMsgProperty_ScanDvbt2Start;

/**�쳣״̬*/

typedef enum {
	SEARCH_ERROR = 0,
	SEARCH_DBASE_OVERFLOW,
} GxMsgStatusReplyCode;

typedef struct {
	GxMsgStatusReplyCode type;      ///< �쳣��������, 0-����ǰ�˻����ǽ�������쳣��������ʧ�� 1-���ݿ�����
} GxMsgProperty_StatusReply;

/*˵����������������Ҫ��ʾ����Ϣ,�ֽ׶�ֻ�н�Ŀ����,�������Ҫ,�ڴ˽ṹ�������*/
/*
typedef struct {
	uint8_t name[MAX_PROG_NAME];
} GxSearchInfoShow;
*/

typedef struct {
	GxBusPmDataProgType type;            ///< tv����radio
	GxBusPmDataProgExistFlag flag;       ///< �жϽ�Ŀ�Ƿ��Ѿ�����
	uint32_t service_id;
	uint8_t name[MAX_PROG_NAME];         ///< ������ʾ����Ϣ����ֻ��name
	GxBusPmDataProgSwitch scramble_flag;
} GxMsgProperty_NewProgGet;


/**�ش���������Ϣ ������ǰ�����ĸ�tp�ĸ�����,����Ҳ���Ը��ݼ���num���м���,*/
typedef enum {
	NIT = 0 ,
	NOT_NIT,
} GxMsgNitReplyCode;

typedef struct {
	uint16_t sat_max_count;         ///< �������ǵ��������
	uint16_t sat_num;               ///< ��ǰ�������ǵڼ���sat
	uint16_t tp_max_count;          ///< ����tp���������
	uint16_t tp_num;                ///< ��ǰ�������ǵڼ���tp
	uint16_t tp_id;                 ///< ��ǰ������tp��id
	uint32_t frequency;             ///< Ƶ���Ƶ�ʵ�λ MHz
	GxMsgNitReplyCode nit_flag;     ///< ������ǰ������tp�Ƿ���nit������
	union {
		GxBusPmTp_s tp_s;
		GxBusPmTp_c tp_c;
		GxBusPmTp_t tp_t;
		GxBusPmTp_dtmb tp_dtmb;
		GxBusPmTp_dvbt2 tp_dvbt2;
	};                              ///< ��ǰ������Ƶ�����Ϣ
	uint8_t sat_name[MAX_SAT_NAME]; ///< ���ǵ�����
} GxMsgProperty_SatTpReply;

typedef enum {
	BLIND_TP = 0 ,
	BLIND_PROGRESS,
} GxMsgBlindReplyType;

typedef enum {
	BLIND_FAST = 0, ///< ��ɨ
	BLIND_DETAIL,   ///< ��ɨ
} GxMsgBlindSearchType;

typedef enum {
	BLIND_POLAR_ALL = 0, ///< ȫ��������
	BLIND_POLAR_H,       ///< ֻɨˮƽ����
	BLIND_POLAR_V,       ///< ֻɨ��ֱ����
} GxMsgBlindPolarType;

typedef struct {
	uint32_t  enable;
	uint32_t  step_mhz;
	uint32_t  window_size_k;
	uint32_t  low_freq_mhz;
	uint32_t  high_freq_mhz;
#define BLIND_SCAN_MODE_ENABLE  (0x12345678)
} GxBlindScanMode;

typedef struct {
	uint32_t max_num;                 ///< ��Ҫ������sat������
	uint32_t *array;                  ///< ��Ҫ������sat��id������
	GxMsgBlindSearchType search_type; ///< äɨ�ķ�ʽ
	GxMsgBlindPolarType  polar_type;  ///< ��������
	GxSearchDiseqc search_diseqc;
	GxSearchCheckCa check_ca_fun;     ///< ���caϵͳ�Ƿ���ȷ
	GxSearchTVRadio tv_radio;         ///< ѡ������tv��Ŀ����radio��Ŀ����ȫ��
	GxSearchFtaCas fta_cas;           ///< ѡ��������ѽ�Ŀ���Ǽ��ܽ�Ŀ����ȫ��
	GxSearchNitSwitch nit_switch;     ///< �Ƿ�����nit����
	uint32_t *ts;                     ///< ��Ҫ������ts��,�����auto scan����ôts�ŵ�˳���id�������id˳��һһ��Ӧ,����Ҫ��ֵ��������null
	GxPidSearch params_pid;           ///< �����������в�Ϊ0�ĳ�Ա ,��ô�����Ա��ָ������Ҫƥ���pid
	GxSearchExtend*  ext;             ///< ��̨��չ����
	uint32_t    ext_num;              ///< ��չ���˵�����
	GxSearchTimeOut time_out;         ///< ���ű�ĳ�ʱʱ��
	uint32_t demux_id;                ///< ʹ���ĸ�demux
	GxSearchModifyProg  modify_prog;
	GxBlindScanMode blind_mode;
	GxSearchCheckPmtPid check_pmtpid_fun;
} GxMsgProperty_BlindScanStart;

typedef enum {
	DVBS,
	DIRECTV,
	DVBS2,
} GxBlindSearchTpType;

typedef enum {
	BLIND_STAGE_TP = 0,
	BLIND_STAGE_PROG,
	BLIND_STAGE_NONE,
} GxBlindSearchStage;

typedef struct {
	GxMsgBlindReplyType type;       ///< ������ǰ���ص���tp��Ϣ���ǽ�����Ϣ
	uint16_t sat_max_count;         ///< �������ǵ��������
	uint16_t sat_num;               ///< ��ǰ�������ǵڼ���sat
	uint32_t frequency;             ///< Ƶ���Ƶ�ʵ�λ MHz
	GxBusPmTp_s tp_s;               ///< ��ǰ������Ƶ�����Ϣ
	uint8_t sat_name[MAX_SAT_NAME]; ///< ���ǵ�����
	uint32_t progress;              ///< ������Ϣ
	GxBlindSearchTpType mode;
	fe_modulation_t qpsk;
	GxBlindSearchStage stage;
	uint32_t sat_id;
	uint32_t tp_id;
} GxMsgProperty_BlindScanReply;

//����һ����ͣ����

__END_DECLS

#endif
/*@}*/

