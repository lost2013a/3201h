#ifndef __GXUPDATE_DEF_H__
#define __GXUPDATE_DEF_H__

#include "gxcore.h"

__BEGIN_DECLS

/** 升级参数限定*/
#define MAX_UPDATE_STREAM_NAME            (256)  /**< 升级流名字符串最大长度*/
#define MAX_UPDATE_PARTITION_NAME         (256)  /**< 升级分区名字符串最大长度*/
#define MAX_UPDATE_PROTOCOL_NAME          (256)  /**< 升级协议名字符串最大长度*/

/**错误值列表*/
typedef enum {
	GXUPDATE_UPDATE_FAILURE               = -10,  /**< 升级失败           */
	GXUPDATE_TERMINAL_NOT_SUPPORT         = -9,   /**< 终端类型错误       */
	GXUPDATE_PARTITION_ERROR              = -8,   /**< 分区错误           */
	GXUPDATE_PROTOCOL_ERROR               = -6,   /**< 协议错误           */
	GXUPDATE_SYSTEM_INFO_GET_FAILURE      = -5,   /**< 系统信息错误       */
	GXUPDATE_PROTOCOL_PARAM_ERROR         = -4,   /**< 升级协议参数错误   */
	GXUPDATE_MEM_ERROR                    = -2,   /**< 内存错误           */
	GXUPDATE_OK                           = 0,    /**< 升级成功           */
	GXUPDATE_START                        = 1,    /**< 升级启动           */
	GXUPDATE_INITIALIZING                 = 2,    /**< 正在初始化升级参数 */
	GXUPDATE_STOP                         = 3,    /**< 升级被终止         */
} GxUpdate_Error;

/** 升级流IOCTL Key值列表*/
typedef enum {
	GXUPDATE_STREAM_PROTOCOL_SELECT       = 1,    /**< 选择升级流的升级协议 */
	GXUPDATE_STREAM_PROTOCOL_CTRL         = 2,    /**< 升级协议IOCTL        */
	GXUPDATE_STREAM_PARTITION_SELECT      = 3,    /**< 选择升级的分区类型   */
	GXUPDATE_STREAM_PARTITION_CTRL        = 4,    /**< 分区IOCTL            */
	GXUPDATE_STREAM_UPDATE_START          = 5,    /**< 开始升级             */
	GXUPDATE_STREAM_UPDATE_STOP           = 6,    /**< 停止升级             */
	GXUPDATE_STREAM_UPDATE_GET_STATUS     = 7     /**< 获取升级状态         */
} GxUpdate_StremIoctlKey;

/** 升级协议终端类型*/
typedef enum {
	GXUPDATE_CLIENT,                              /**< 客户端   */
	GXUPDATE_SERVER                               /**< 服务器端 */
} GxUpdate_Terminal;

/**升级流名称类型*/
typedef char    GxUpdate_StreamName[MAX_UPDATE_STREAM_NAME];
/**升级分区名称类型*/
typedef char    GxUpdate_PartitionName[MAX_UPDATE_PARTITION_NAME];
/**升级协议名称类型*/
typedef char    GxUpdate_ProtocolName[MAX_UPDATE_PROTOCOL_NAME];

typedef struct {
	int32_t           type;           /**< 升级状态类型*/
	union {
		int32_t   percent;        /**< 升级进度百分比*/
		int32_t   error;          /**< 升级错误号*/
	};
} GxUpdate_Status;

/** 升级协议IOCTL类型*/
typedef struct {
	int32_t key;        /**< 升级协议IOCTL KEY值，其值参考选择的升级协议实现 */
	void*   buf;        /**< 升级协议IOCTL KEY所带参数                       */
	size_t  size;       /**< 升级协议IOCTL KEY所带参数buf大小                */
} GxUpdate_IoCtrl;

/** 升级协议类型*/
typedef struct {
	char*               name;                                             /**< 升级协议名 */
	handle_t            (*open)     (const char*);                        /**< 打开升级协议 */
	GxUpdate_Terminal   (*get_type) (handle_t);                           /**< 获取升级协议类型 */
	int32_t             (*set_size) (handle_t, size_t);
	int32_t             (*ioctl)    (handle_t, int32_t, void*, size_t);   /**< 设置获取升级协议 */
	uint32_t            (*read)     (handle_t, uint8_t*, ssize_t*);       /**< 读升级数据 */
	ssize_t             (*write)    (handle_t, const uint8_t*, size_t);   /**< 写升级数据 */
	int32_t             (*close)    (handle_t);                           /**< 关闭打开的升级协议 */
} GxUpdate_ProtocolOps;


/** 升级分区类型*/
typedef struct {
	char*    name;                                             /**< 分区名*/
	handle_t (*open)    (const char*);                         /**< 打开分区*/
	int32_t  (*ioctl)   (handle_t, int32_t, void*, size_t);    /**< 设置获取升级协议*/
	ssize_t  (*get_size)(handle_t);                            /**< 获取读写分区大小*/
	ssize_t  (*read)    (handle_t, uint8_t*, size_t);          /**< 读分区数据*/
	ssize_t  (*write)   (handle_t, const uint8_t*, size_t);    /**< 写分区数据*/
	int32_t  (*close)   (handle_t);                            /**< 关闭打开的分区*/
} GxUpdate_PartitionOps;

__END_DECLS

#endif

