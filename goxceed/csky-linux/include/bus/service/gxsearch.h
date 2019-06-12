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

#define GX_SEARCH_ALL (3)                                    ///< 搜索所有节目
//#define MAX_PROG_NAME (16)                                 ///< 这个宏再pm里面已经由定义,联调得时候不需要在这里重新定义了

#define SI_MAX_MULTI_NAME_COUNT  (2)

#define GXBUS_SEARCH_LANG_PRIORITY "gxsearch_lang_priority"  ///< 搜索时优先存储的语言，如“eng_chn”则第一优先语言为英语第二优先语言为中文，
                                                             ///< 不同语言间用_隔开，并且国家代码要符合iso9660规范
#define  GXBUS_SEARCH_LANG_DEFAULT "eng_chn"                 ///< 默认英语优先

#define GXBUS_SEARCH_UTF8 "gxsearch_utf8"                    ///< 搜索时是否把节目名字转为utf-8

#define GXBUS_SEARCH_UTF8_YES 1                              ///< 搜索时是否把节目名字转为utf-8
#define GXBUS_SEARCH_UTF8_NO  0                              ///< 搜索时是否把节目名字转为utf-8

#define GXBUS_SEARCH_NIT_LOOP "gxsearch_nit_loop"            ///< nit搜索时是否进行nit循环搜索
#define GXBUS_SEARCH_NIT_LOOP_YES 1                          ///< nit搜索时进行tp的循环搜索
#define GXBUS_SEARCH_NIT_LOOP_NO  0                          ///< nit搜索时不进行tp的循环搜索

#define GXBUS_SEARCH_DTS_SUPPORT "gxsearch_dts_support"      ///< 是否支持DTS
#define GXBUS_SEARCH_DTS_YES      1                         
#define GXBUS_SEARCH_DTS_NO  0                          


#ifndef TRUE
#  define TRUE    1
#  define FALSE   0
#endif

#if 0
/*盲扫步进量*/
#define     BLIND_SCAN_STEP_MHZ         (4)

/*盲扫每个window的范围*/
#define     BLIND_SCAN_WINDOW_SIZE_K    (16000)

/*盲扫的频率范围*/
#define     BLIND_SCAN_LOW_FREQ_MHZ     (1467)
#define     BLIND_SCAN_HIGH_FREQ_MHZ    (1492)
#endif


/* 盲扫极化 */
#define     BLIND_SCAN_POLAR_H          (0)//18V
#define     BLIND_SCAN_POLAR_V          (1)//13V
#define     BLIND_SCAN_POLAR_ALL        (2)
/* 盲扫本振 */
#define     BLIND_SCAN_LNB_OCS          (0)
#define     BLIND_SCAN_LNB_SINGLE       (1)
/* 盲扫本振类型 */
#define     BLIND_SCAN_LNB_C            (0)
#define     BLIND_SCAN_LNB_KU           (1)
/* 一次盲扫所能搜索到的tp数量 */
#define     BLIND_SCAN_TP_COUNT         (200)

/*检测ca系统是否正确 返回0代表ca system不对 返回1代表ca system正确*/
typedef uint32_t (*GxSearchCheckCa)(uint16_t ca_system_id,uint16_t ele_pid,uint16_t ecm_pid);

/*在搜台时确认是否需要过滤该pid的pmt*/
typedef bool (*GxSearchCheckPmtPid)(uint16_t pid,uint16_t prog_num);

/**该结构初步定义了各种搜索方式，有其他搜索方式需要在此结构中增加。*/
typedef enum {
	GX_SEARCH_AUTO = 0, ///< auto搜索
	GX_SEARCH_MANUAL,   ///< manual搜索
	GX_SEARCH_PID,      ///< pid搜索
} GxSearchType;

typedef enum {
	GX_SEARCH_NIT_ENABLE = 0, ///< nit搜索使能
	GX_SEARCH_NIT_DISABLE,    ///< nit搜索不使能
} GxSearchNitSwitch;

/**
 * 说明：搜索的类型可以在这个结构中添加,
 * 该结构和GxSearchFtaCas 结构
 * 组合起来可以任意组合条件，更具应用的不同随意组合,
 * 采用位预算可以结合各种方式,
 * 比如0x3就是GX_SEARCH_TV 和GX_SEARCH_RADIO 的组合相当于现阶段的all搜索
 */
typedef enum {
	GX_SEARCH_TV           = 1,            ///< 只搜索TV节目
	GX_SEARCH_RADIO        = 2,            ///< 只搜索radio节目
	GX_SEARCH_TV_RADIO_ALL = GX_SEARCH_ALL ///< 搜索所有节目
} GxSearchTVRadio;

/**
 * 说明：搜索的类型可以在这个结构中添加,
 * 该结构和GxSearchTVRadio结构
 * 组合起来可以任意组合条件，更具应用的不同随意组合,
 * 采用位运算可以结合各种方式,
 * 比如0x3就是GX_SEARCH_FTA 和GX_SEARCH_CAS 的组合相当于现阶段all搜索
 */
typedef enum {
	GX_SEARCH_FTA         = 1,            ///< 只搜索免费节目
	GX_SEARCH_CAS         = 2,            ///< 只搜索加密节目
	GX_SEARCH_FTA_CAS_ALL = GX_SEARCH_ALL ///< 搜索所有节目
} GxSearchFtaCas;

/**
 * pid搜索时指定的各个pid参数,
 * 可以和s以及c t的搜索结构体搭配使用组合出各种pid搜索方式
 * pid搜索时如果各pid的值为0xffffffff将不做对比
 */
typedef struct {
	uint32_t video_pid; ///< 所要搜索的节目的video pid
	uint32_t audio_pid; ///< 所要搜索的节目的audio pid
	uint32_t pcr_pid;   ///< 所要搜索的节目的pcr pid
} GxPidSearch;

/**
 * 卫星搜索的参数结构体,
 * 如果使auto搜索的话 max_num就是指要搜索的卫星的数量,
 * id_ array 就是卫星的id号数组
 * tp搜索的时候参数就是指tp的数量和id
 */
typedef struct {
	uint32_t max_num;       ///< 所要搜索的transport stream或者是sat的数量
	uint32_t *array;        ///< 所要搜索的tp或者sat集合的id号数组
	uint32_t *ts;           ///< 所要搜索的ts号,如果是auto scan，那么ts号的顺序和id数组里的id顺序一一对应,必须要给值，不能是null
	GxPidSearch params_pid; ///< 如果scan_type选择了pid搜索,那么这个成员就指明了所要匹配的pid
} GxSatSearch;

/**有线搜索的参数结构体*/
typedef struct {
	uint32_t sat_id;  ///< 所属的卫星id
	uint32_t max_num; ///< 所要搜索的transport stream的数量
	uint32_t *array;  ///< 所要搜索的tpid号数组
	uint32_t *ts;     ///< 所要搜索的ts号,必须要给值，不能是null
} GxCableSearch;


/**T搜索的参数结构体*/
typedef struct {
	uint32_t sat_id;  ///< 所属的卫星id
	uint32_t max_num; ///< 所要搜索的transport stream的数量
	uint32_t *array;  ///< 所要搜索的tpid号数组
	uint32_t *ts;     ///< 所要搜索的ts号,必须要给值，不能是null
} GxTSearch;

/**DTMB搜索的参数结构体*/
typedef struct {
	uint32_t sat_id;  ///< 所属的卫星id
	uint32_t max_num; ///< 所要搜索的transport stream的数量
	uint32_t *array;  ///< 所要搜索的tpid号数组
	uint32_t *ts;     ///< 所要搜索的ts号,必须要给值，不能是null
} GxDtmbSearch;

/**
 * 搜台过滤扩展，需要用户配置所要过滤的表，以及匹配条件，并且注册一个解析的私有函数
 * 比如lcn空间可用该扩展实现解析
 */
typedef struct {
	uint16_t pid;                         ///< 表的pid 的值
	uint16_t time_out;

	uint8_t  match_depth;                 ///< 匹配深度
	uint32_t reserve:24;

	uint8_t  match[18];                   ///< 匹配值
	uint8_t  mask[18];                    ///< 匹配值的掩码，对应位为1并且匹配深度足够，才会按匹配值来过滤
	private_table_parser table_parse_fun; ///< 私有解析函数指针;
} GxSearchExtend;

/**
 * 搜索时候各张表的超时时间配置,单位为ms，如果为0，那么将使用默认值
 */
typedef struct {
	uint16_t   pat; ///< pat表的超时时间
	uint16_t   sdt; ///< sdt表的超时时间
	uint16_t   nit; ///< nit表的超时时间
	uint16_t   pmt; ///< pmt表的超时时间
} GxSearchTimeOut;

/**
 * 说明：app为了能实现搜台功能，就需要填写如上的一个结构体，
 * 然后发送PMServiceMsgID_StarScan消息，并且带上填写好的结构体
 */
typedef void (*GxSearchDiseqc)(uint32_t sat_id,fe_sec_voltage_t polar,int32_t sat22k);
typedef status_t (*GxSearchModifyProg)(GxBusPmDataProg* prog );//往数据库增加节目前会回调该函数，由用户修改节目数据，返回GX_SEARCH_OK,会把节目加入到数据库

typedef struct {
	GxSearchType scan_type;               ///< 选择何种搜索方式
	GxSearchTVRadio tv_radio;             ///< 选择搜索tv节目还是radio节目还是全搜
	GxSearchFtaCas fta_cas;               ///< 选择搜索免费节目还是加密节目还是全搜
	GxSearchNitSwitch nit_switch;         ///< 是否启用nit搜索
	GxSatSearch params_s;
	GxSearchExtend*  ext;                 ///< 搜台扩展过滤
	uint32_t    ext_num;                  ///< 扩展过滤的数量
	uint32_t*  ext_tp_id;                 ///< 哪些tp需要进行本次扩展搜索
	uint32_t   ext_tp_num;                ///< tp的数量
	GxSearchTimeOut time_out;             ///< 各张表的超时时间
	GxSearchDiseqc search_diseqc;
	GxSearchCheckCa check_ca_fun;         ///< 检测ca系统是否正确
	uint32_t demux_id;//使用哪个demux
	GxSearchModifyProg  modify_prog;
	GxSearchCheckPmtPid check_pmtpid_fun;
	private_table_parser sdt_parse_fun;
	private_table_parser pmt_parse_fun;   ///< pmt的私有解析函数，由于pmt需要从pat获取pid，没办法使用GxSearchExtend
} GxMsgProperty_ScanSatStart;

/**说明：app为了能实现搜台功能，
 * 就需要填写如上的一个结构体，
 * 然后发送PMServiceMsgID_ CableScanStart消息，并且带上填写好的结构体
 */
typedef struct {
	GxSearchType scan_type;               ///< 选择何种搜索方式
	GxSearchTVRadio tv_radio;             ///< 选择搜索tv节目还是radio节目还是全搜
	GxSearchFtaCas fta_cas;               ///< 选择搜索免费节目还是加密节目还是全搜
	GxSearchNitSwitch nit_switch;         ///< 是否启用nit搜索
	GxCableSearch params_c;
	private_table_parser pmt_parse_fun;   ///< pmt的私有解析函数，由于pmt需要从pat获取pid，没办法使用GxSearchExtend
	GxSearchCheckCa check_ca_fun;         ///< 检测ca系统是否正确
	GxSearchExtend*  ext;                 ///< 搜台扩展过滤
	uint32_t   ext_num;                   ///< 扩展过滤的数量
	uint32_t*  ext_tp_id;                 ///< 哪些tp需要进行本次扩展搜索
	uint32_t   ext_tp_num;                ///< tp的数量
	GxSearchTimeOut time_out;             ///< 各张表的超时时间
	uint32_t demux_id;//使用哪个demux
	GxSearchModifyProg  modify_prog;
	GxSearchCheckPmtPid check_pmtpid_fun;
	private_table_parser sdt_parse_fun;
} GxMsgProperty_ScanCableStart;

/**
 * 说明：app为了能实现搜台功能，
 * 就需要填写如上的一个结构体，
 * 然后发送PMServiceMsgID_ CableScanStart消息，并且带上填写好的结构体
 */
typedef struct {
	GxSearchType scan_type;               ///< 选择何种搜索方式
	GxSearchTVRadio tv_radio;             ///< 选择搜索tv节目还是radio节目还是全搜
	GxSearchFtaCas fta_cas;               ///< 选择搜索免费节目还是加密节目还是全搜
	GxSearchNitSwitch nit_switch;         ///< 是否启用nit搜索
	GxTSearch params_t;
	GxSearchExtend*  ext;                 ///< 搜台扩展过滤
	private_table_parser pmt_parse_fun;   ///< pmt的私有解析函数，由于pmt需要从pat获取pid，没办法使用GxSearchExtend
	GxSearchCheckCa check_ca_fun;         ///< 检测ca系统是否正确
	uint32_t   ext_num;                   ///< 扩展过滤的数量
	uint32_t*  ext_tp_id;                 ///< 哪些tp需要进行本次扩展搜索
	uint32_t   ext_tp_num;                ///< tp的数量
	GxSearchTimeOut time_out;             ///< 各张表的超时时间
	uint32_t demux_id;//使用哪个demux
	GxSearchModifyProg  modify_prog;
	GxSearchCheckPmtPid check_pmtpid_fun;
	private_table_parser sdt_parse_fun;
} GxMsgProperty_ScanTStart;

/**
 * 说明：app为了能实现搜台功能，
 * 就需要填写如上的一个结构体，
 * 然后发送PMServiceMsgID_ CableScanDtmbtart消息，并且带上填写好的结构体
 */
typedef struct {
	GxSearchType scan_type;               ///< 选择何种搜索方式
	GxSearchTVRadio tv_radio;             ///< 选择搜索tv节目还是radio节目还是全搜
	GxSearchFtaCas fta_cas;               ///< 选择搜索免费节目还是加密节目还是全搜
	GxSearchNitSwitch nit_switch;         ///< 是否启用nit搜索
	GxDtmbSearch params_dtmb;
	GxSearchExtend*  ext;                 ///< 搜台扩展过滤
	private_table_parser pmt_parse_fun;   ///< pmt的私有解析函数，由于pmt需要从pat获取pid，没办法使用GxSearchExtend
	GxSearchCheckCa check_ca_fun;         ///< 检测ca系统是否正确
	uint32_t   ext_num;                   ///< 扩展过滤的数量
	uint32_t*  ext_tp_id;                 ///< 哪些tp需要进行本次扩展搜索
	uint32_t   ext_tp_num;                ///< tp的数量
	GxSearchTimeOut time_out;             ///< 各张表的超时时间
	uint32_t demux_id;//使用哪个demux
	GxSearchModifyProg  modify_prog;
	GxSearchCheckPmtPid check_pmtpid_fun;
	private_table_parser sdt_parse_fun;
} GxMsgProperty_ScanDtmbStart;

/**
 * 说明：app为了能实现搜台功能，
 * 就需要填写如上的一个结构体，
 * 然后发送PMServiceMsgID_ CableScanDtmbtart消息，并且带上填写好的结构体
 */
typedef struct {
	GxSearchType scan_type;               ///< 选择何种搜索方式
	GxSearchTVRadio tv_radio;             ///< 选择搜索tv节目还是radio节目还是全搜
	GxSearchFtaCas fta_cas;               ///< 选择搜索免费节目还是加密节目还是全搜
	GxSearchNitSwitch nit_switch;         ///< 是否启用nit搜索
	GxTSearch params_t;
	GxSearchExtend*  ext;                 ///< 搜台扩展过滤
	private_table_parser pmt_parse_fun;   ///< pmt的私有解析函数，由于pmt需要从pat获取pid，没办法使用GxSearchExtend
	GxSearchCheckCa check_ca_fun;         ///< 检测ca系统是否正确
	uint32_t   ext_num;                   ///< 扩展过滤的数量
	uint32_t*  ext_tp_id;                 ///< 哪些tp需要进行本次扩展搜索
	uint32_t   ext_tp_num;                ///< tp的数量
	GxSearchTimeOut time_out;             ///< 各张表的超时时间
	uint32_t demux_id;                    ///< 使用哪个demux
	GxSearchModifyProg  modify_prog;
	GxSearchCheckPmtPid check_pmtpid_fun;
	private_table_parser sdt_parse_fun;
} GxMsgProperty_ScanDvbt2Start;

/**异常状态*/

typedef enum {
	SEARCH_ERROR = 0,
	SEARCH_DBASE_OVERFLOW,
} GxMsgStatusReplyCode;

typedef struct {
	GxMsgStatusReplyCode type;      ///< 异常的类型码, 0-由于前端或者是解析表的异常导致搜索失败 1-数据库已满
} GxMsgProperty_StatusReply;

/*说明：搜索过程中需要显示的信息,现阶段只有节目名字,如果有需要,在此结构体中添加*/
/*
typedef struct {
	uint8_t name[MAX_PROG_NAME];
} GxSearchInfoShow;
*/

typedef struct {
	GxBusPmDataProgType type;            ///< tv还是radio
	GxBusPmDataProgExistFlag flag;       ///< 判断节目是否已经存在
	uint32_t service_id;
	uint8_t name[MAX_PROG_NAME];         ///< 用于显示的信息现在只有name
	GxBusPmDataProgSwitch scramble_flag;
} GxMsgProperty_NewProgGet;


/**回传的搜索信息 表明当前搜索哪个tp哪个卫星,进度也可以根据几个num进行计算,*/
typedef enum {
	NIT = 0 ,
	NOT_NIT,
} GxMsgNitReplyCode;

typedef struct {
	uint16_t sat_max_count;         ///< 表明卫星的最多数量
	uint16_t sat_num;               ///< 当前搜索的是第几个sat
	uint16_t tp_max_count;          ///< 表明tp的最多数量
	uint16_t tp_num;                ///< 当前搜索的是第几个tp
	uint16_t tp_id;                 ///< 当前搜索的tp的id
	uint32_t frequency;             ///< 频点的频率单位 MHz
	GxMsgNitReplyCode nit_flag;     ///< 表明当前搜索的tp是否是nit出来的
	union {
		GxBusPmTp_s tp_s;
		GxBusPmTp_c tp_c;
		GxBusPmTp_t tp_t;
		GxBusPmTp_dtmb tp_dtmb;
		GxBusPmTp_dvbt2 tp_dvbt2;
	};                              ///< 当前搜索的频点的信息
	uint8_t sat_name[MAX_SAT_NAME]; ///< 卫星的名称
} GxMsgProperty_SatTpReply;

typedef enum {
	BLIND_TP = 0 ,
	BLIND_PROGRESS,
} GxMsgBlindReplyType;

typedef enum {
	BLIND_FAST = 0, ///< 块扫
	BLIND_DETAIL,   ///< 慢扫
} GxMsgBlindSearchType;

typedef enum {
	BLIND_POLAR_ALL = 0, ///< 全极化方向
	BLIND_POLAR_H,       ///< 只扫水平方向
	BLIND_POLAR_V,       ///< 只扫垂直方向
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
	uint32_t max_num;                 ///< 所要搜索的sat的数量
	uint32_t *array;                  ///< 所要搜索的sat的id号数组
	GxMsgBlindSearchType search_type; ///< 盲扫的方式
	GxMsgBlindPolarType  polar_type;  ///< 极化方向
	GxSearchDiseqc search_diseqc;
	GxSearchCheckCa check_ca_fun;     ///< 检测ca系统是否正确
	GxSearchTVRadio tv_radio;         ///< 选择搜索tv节目还是radio节目还是全搜
	GxSearchFtaCas fta_cas;           ///< 选择搜索免费节目还是加密节目还是全搜
	GxSearchNitSwitch nit_switch;     ///< 是否启用nit搜索
	uint32_t *ts;                     ///< 所要搜索的ts号,如果是auto scan，那么ts号的顺序和id数组里的id顺序一一对应,必须要给值，不能是null
	GxPidSearch params_pid;           ///< 如果如果其中有不为0的成员 ,那么这个成员就指明了所要匹配的pid
	GxSearchExtend*  ext;             ///< 搜台扩展过滤
	uint32_t    ext_num;              ///< 扩展过滤的数量
	GxSearchTimeOut time_out;         ///< 各张表的超时时间
	uint32_t demux_id;                ///< 使用哪个demux
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
	GxMsgBlindReplyType type;       ///< 表明当前返回的是tp信息还是进度信息
	uint16_t sat_max_count;         ///< 表明卫星的最多数量
	uint16_t sat_num;               ///< 当前搜索的是第几个sat
	uint32_t frequency;             ///< 频点的频率单位 MHz
	GxBusPmTp_s tp_s;               ///< 当前搜索的频点的信息
	uint8_t sat_name[MAX_SAT_NAME]; ///< 卫星的名称
	uint32_t progress;              ///< 进度信息
	GxBlindSearchTpType mode;
	fe_modulation_t qpsk;
	GxBlindSearchStage stage;
	uint32_t sat_id;
	uint32_t tp_id;
} GxMsgProperty_BlindScanReply;

//增加一个暂停搜索

__END_DECLS

#endif
/*@}*/

