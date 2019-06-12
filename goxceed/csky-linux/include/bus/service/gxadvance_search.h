#ifndef __GXATSC_SEARCH_H__
#define __GXATSC_SEARCH_H__

#include "gxmsg.h"
#include "gxbus.h"
#include "gxcore.h"
#include "module/pm/gxpm_manage.h"
#include "sub_system/si_sub_engine/si_sub_engine.h"

typedef enum {
	GX_SEARCH_AUTO=0, ///< 自动搜索
	GX_SEARCH_MANUAL, ///< 手动搜索
	GX_SEARCH_PID,    ///< pid搜索
} GxSearchScanType;

#if 0
typedef enum {
	GX_SEARCH_FRONT_ATSC_T = 0,
	GX_SEARCH_FRONT_ATSC_C,
	GX_SEARCH_FRONT_S,
	GX_SEARCH_FRONT_T,
	GX_SEARCH_FRONT_C,
	GX_SEARCH_FRONT_DTMB,
	GX_SEARCH_FRONT_DVBT2,
}GxSearchFrontType;
#endif

typedef enum {
	GX_SEARCH_ANALOG_TV = 0, ///< 模拟电视
	GX_SEARCH_TV,            ///< TV节目
	GX_SEARCH_RADIO,         ///< 音频节目
	GX_SEARCH_DATAPROGRAM,   ///< 数据广播
	GX_SEARCH_ALL,           ///< 所有节目
} GxSearchType;

typedef struct {
	uint16_t pat; ///< pat表过滤超时时间, 单位ms, 如果不设值使用默认值5000ms
	uint16_t pmt; ///< pmt表过滤超时时间，单位ms，如果不设值使用默认值5000ms
	uint16_t vct; ///< vct表过滤超时时间，单位ms, 如果不设值使用默认值15000ms
	uint16_t sdt; ///< sdt表过滤超时时间，单位ms, 如果不设值使用默认值15000ms
	uint16_t nit; ///< vct表过滤超时时间，单位ms, 如果不设值使用默认值10000ms
	uint16_t reserve;
} GxSearchTimeOut;

typedef enum {
	GX_SEARCH_NIT_ENABLE = 0, ///< nit搜索使能
	GX_SEARCH_NIT_DISABLE,    ///< nit搜索不使能
} GxSearchNitSwitch;



//往数据库增加节目前会回调该函数，由用户修改节目数据，返回GX_SEARCH_OK,会把节目加入到数据库
typedef status_t (*GxSearchModifyProg)(GxBusPmDataProg* prog);

/*在pat解析时，先把原始数据传给用户，再进行标准的搜台动作*/
typedef int32_t (*GxGetOriginalSection)(uint8_t *section, uint32_t len);

/**
 * 说明：搜索的类型可以在这个结构中添加,
 * 该结构和GxSearchTVRadio结构
 * 组合起来可以任意组合条件，更具应用的不同随意组合,
 * 采用位运算可以结合各种方式,
 * 比如0x3就是GX_SEARCH_FTA 和GX_SEARCH_CAS 的组合相当于现阶段all搜索
 */
typedef enum {
	GX_SEARCH_FTA = 1,                    ///< 只搜索免费节目
	GX_SEARCH_CAS = 2,                    ///< 只搜索加密节目
	GX_SEARCH_FTA_CAS_ALL = GX_SEARCH_ALL ///< 搜索所有节目
} GxSearchFtaCas;



typedef struct {
	uint16_t service_id;
	uint8_t  service_type;
	uint32_t reserve:8;

	uint32_t sdt_version;
	uint8_t  service_name[MAX_PROG_NAME];
}GxSearchSdtInfo;


/*检测ca系统是否正确 返回0代表ca system不对 返回1代表ca system正确*/
typedef uint32_t (*GxSearchCheckCa)(uint16_t ca_system_id,uint16_t ele_pid,uint16_t ecm_pid);
/*针对内蒙项目，在获取sdt信息时回传节目名字等 */
typedef void (*GxSearchGetSdtInfo)(GxSearchSdtInfo * info);
typedef int32_t (*GxSearchNitCheck)(uint32_t sat_id,uint32_t fre,uint32_t symbol_rate,GxBusPmTpPolar polar);
typedef bool (*GxSearchCheckPmtPid)(uint16_t pid,uint16_t prog_num);



/**
 * PID搜索时指定的各个PID参数,
 * 可以和S以及C T的搜索结构体搭配使用组合出各种PID搜索方式
 * PID搜索时如果各PID的值为 0XFFFFFFFF 将不做对比
 */
typedef struct {
	uint32_t video_pid; ///< 所要搜索的节目的video pid
	uint32_t audio_pid; ///< 所要搜索的节目的audio pid
	uint32_t pcr_pid;   ///< 所要搜索的节目的pcr pid
} GxPidSearch;

typedef void (*GxSearchDiseqc)(uint32_t sat_id,fe_sec_voltage_t polar,int32_t sat22k);


/**
 * 搜索异常状态
 */
typedef enum {
	SEARCH_ERROR = 0,      // 由于前端或者解析表失败导致搜索失败
	SEARCH_DBASE_OVERFLOW, // 数据库满
} GxMsgStatusReplyCode;


typedef struct {
	GxMsgStatusReplyCode type;
} GxMsgProperty_StatusReply;


/**
 *搜索过程中搜到新节目用来显示的信息
 */
typedef struct {
	GxSearchType type;                   // 节目类型
	GxBusPmDataProgExistFlag flag;       // 是否已存在
	uint8_t name[MAX_PROG_NAME];         // 节目名称
	uint32_t service_id;                 // pmt中的program_number与vct中的program_number相同
	uint32_t source_id;
	GxBusPmDataProgSwitch scramble_flag; // 节目是否加密
} GxMsgProperty_NewProgGet;

typedef enum {
	BLIND_TP = 0 ,
	BLIND_PROGRESS,
} GxMsgBlindReplyType;

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

typedef enum {
	GX_SEARCH_LOCK_ERR = 0,
	GX_SEARCH_LOCK_OK ,
} GxSearchFrontLockFlag;

/* 回传的搜索信息 表明当前搜索哪个tp哪个卫星,进度也可以根据几个num进行计算 */
typedef struct {
	uint16_t sat_max_count;          // 最大sat数
	uint16_t sat_num;                // 当前搜到第几个sat
	uint16_t tp_max_count;           // 最大tp数
	uint16_t tp_num;                 // 当前搜到第几个tp
	uint16_t tp_id;                  // 当前搜索的tp_id
	uint16_t reserve;
	uint32_t frequency;              // 当前搜索的tp频率
	GxSearchFrontLockFlag lock_flag;
	union {
		GxBusPmTp_s tp_s;
		GxBusPmTp_c tp_c;
		GxBusPmTp_t tp_t;
		GxBusPmTp_c Atsc_tp_c;
		GxBusPmTp_t Atsc_tp_t;
		GxBusPmTp_dtmb tp_dtmb;
		GxBusPmTp_dvbt2 tp_dvbt2;
	};
	uint8_t sat_name[MAX_SAT_NAME];  // 卫星名字
} GxMsgProperty_SatTpReply;


typedef struct {
	uint32_t max_num;
	uint32_t *array;
	uint32_t *ts;
} ParamsCommonInfo;

typedef struct {
	uint32_t sat_id;
	ParamsCommonInfo info;
} GxSearchOtherParams;

typedef enum {
	BLIND_FAST = 0, ///< 块扫
	BLIND_DETAIL,   ///< 慢扫
} GxBlindSearchType;

typedef enum {
	BLIND_POLAR_ALL = 0, ///< 全极化方向
	BLIND_POLAR_H,       ///< 只扫水平方向
	BLIND_POLAR_V,       ///< 只扫垂直方向
} GxBlindPolarType;

/* 盲扫极化*/
#define BLIND_SCAN_POLAR_H          (0) // 18V
#define BLIND_SCAN_POLAR_V          (1) // 13V
#define BLIND_SCAN_POLAR_ALL        (2)
/* 盲扫本振*/
#define BLIND_SCAN_LNB_OCS          (0)
#define BLIND_SCAN_LNB_SINGLE       (1)
/* 盲扫本振类型*/
#define BLIND_SCAN_LNB_C            (0)
#define BLIND_SCAN_LNB_KU           (1)

typedef struct {
	GxBlindSearchType search_type; ///< 盲扫的方式
	GxBlindPolarType  polar_type;  ///< 极化方向

	uint32_t  enable;
	uint32_t  step_mhz;
	uint32_t  window_size_k;
	uint32_t  low_freq_mhz;
	uint32_t  high_freq_mhz;
#define BLIND_SCAN_MODE_ENABLE  (0x12345678)
} GxBlindSearchParams;

typedef struct {
	ParamsCommonInfo info;
	GxSearchDiseqc search_diseqc;
	GxBlindSearchParams blind_info;
} GxSearchSParams;

typedef union {
	GxSearchOtherParams other_info;
	GxSearchSParams     s_info;
} GxSearchFrontendParams;

typedef enum {
	GXBUS_SEARCH_UTF8_TRANS_NO,
	GXBUS_SEARCH_UTF8_TRANS_YES,
} GxSearchTranscodingFlag;

typedef struct {
	GxSearchScanType        scan_type;              ///< 选择何种搜索方式
	GxSearchType            tv_radio;               ///< 选择搜索tv节目还是radio节目还是全搜
	GxSearchFtaCas          fta_cas;                ///< 选择搜索免费节目还是加密节目还是全搜
	GxSearchNitSwitch       nit_switch;             ///< 是否启用nit搜索
	uint32_t                ext_num;                ///< 扩展过滤的数量
	uint32_t*               ext_tp_id;              ///< 哪些tp需要进行本次扩展搜索
	uint32_t                ext_tp_num;             ///< tp的数量
	GxSearchTimeOut         timeout;                ///< 各张表的超时时间
	uint32_t                demux_id;               ///< 使用哪个demux
	GxSearchTranscodingFlag transcodingflag;
	GxPidSearch             params_pid;             ///< 如果scan_type选择了pid搜索,那么这个成员就指明了所要匹配的pid
	GxSearchModifyProg      modify_prog;
	GxSearchCheckCa         check_ca_fun;           ///< 检测ca系统是否正确
	GxSearchGetSdtInfo      get_sdt_info_func;
	GxSearchNitCheck        nit_tp_private_check;
	GxGetOriginalSection    pmt_original_parse_fun; ///< pmt的私有解析函数，由于pmt需要从pat获取pid，没办法使用GxSearchExtend
	GxGetOriginalSection    sdt_original_parse_fun; ///< 获取sdt表的时候回传sdt原始数据
	GxSearchCheckPmtPid     check_pmtpid_fun;
} GxSearchServiceParams;

/**
 * 说明：app为了能实现搜台功能，
 * 就需要填写如上的一个结构体，
 * 然后发送PMServiceMsgID_ CableScanStart消息，并且带上填写好的结构体
 */
typedef struct {
	GxSearchServiceParams   ServiceParams;
	GxSearchFrontendParams  FrontendParams;
} GxMsgProperty_ScanStart;

#endif
