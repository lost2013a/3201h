#ifndef __GXUPDATE_DEF_H__
#define __GXUPDATE_DEF_H__

#include "gxcore.h"

__BEGIN_DECLS

/** ���������޶�*/
#define MAX_UPDATE_STREAM_NAME            (256)  /**< ���������ַ�����󳤶�*/
#define MAX_UPDATE_PARTITION_NAME         (256)  /**< �����������ַ�����󳤶�*/
#define MAX_UPDATE_PROTOCOL_NAME          (256)  /**< ����Э�����ַ�����󳤶�*/

/**����ֵ�б�*/
typedef enum {
	GXUPDATE_UPDATE_FAILURE               = -10,  /**< ����ʧ��           */
	GXUPDATE_TERMINAL_NOT_SUPPORT         = -9,   /**< �ն����ʹ���       */
	GXUPDATE_PARTITION_ERROR              = -8,   /**< ��������           */
	GXUPDATE_PROTOCOL_ERROR               = -6,   /**< Э�����           */
	GXUPDATE_SYSTEM_INFO_GET_FAILURE      = -5,   /**< ϵͳ��Ϣ����       */
	GXUPDATE_PROTOCOL_PARAM_ERROR         = -4,   /**< ����Э���������   */
	GXUPDATE_MEM_ERROR                    = -2,   /**< �ڴ����           */
	GXUPDATE_OK                           = 0,    /**< �����ɹ�           */
	GXUPDATE_START                        = 1,    /**< ��������           */
	GXUPDATE_INITIALIZING                 = 2,    /**< ���ڳ�ʼ���������� */
	GXUPDATE_STOP                         = 3,    /**< ��������ֹ         */
} GxUpdate_Error;

/** ������IOCTL Keyֵ�б�*/
typedef enum {
	GXUPDATE_STREAM_PROTOCOL_SELECT       = 1,    /**< ѡ��������������Э�� */
	GXUPDATE_STREAM_PROTOCOL_CTRL         = 2,    /**< ����Э��IOCTL        */
	GXUPDATE_STREAM_PARTITION_SELECT      = 3,    /**< ѡ�������ķ�������   */
	GXUPDATE_STREAM_PARTITION_CTRL        = 4,    /**< ����IOCTL            */
	GXUPDATE_STREAM_UPDATE_START          = 5,    /**< ��ʼ����             */
	GXUPDATE_STREAM_UPDATE_STOP           = 6,    /**< ֹͣ����             */
	GXUPDATE_STREAM_UPDATE_GET_STATUS     = 7     /**< ��ȡ����״̬         */
} GxUpdate_StremIoctlKey;

/** ����Э���ն�����*/
typedef enum {
	GXUPDATE_CLIENT,                              /**< �ͻ���   */
	GXUPDATE_SERVER                               /**< �������� */
} GxUpdate_Terminal;

/**��������������*/
typedef char    GxUpdate_StreamName[MAX_UPDATE_STREAM_NAME];
/**����������������*/
typedef char    GxUpdate_PartitionName[MAX_UPDATE_PARTITION_NAME];
/**����Э����������*/
typedef char    GxUpdate_ProtocolName[MAX_UPDATE_PROTOCOL_NAME];

typedef struct {
	int32_t           type;           /**< ����״̬����*/
	union {
		int32_t   percent;        /**< �������Ȱٷֱ�*/
		int32_t   error;          /**< ���������*/
	};
} GxUpdate_Status;

/** ����Э��IOCTL����*/
typedef struct {
	int32_t key;        /**< ����Э��IOCTL KEYֵ����ֵ�ο�ѡ�������Э��ʵ�� */
	void*   buf;        /**< ����Э��IOCTL KEY��������                       */
	size_t  size;       /**< ����Э��IOCTL KEY��������buf��С                */
} GxUpdate_IoCtrl;

/** ����Э������*/
typedef struct {
	char*               name;                                             /**< ����Э���� */
	handle_t            (*open)     (const char*);                        /**< ������Э�� */
	GxUpdate_Terminal   (*get_type) (handle_t);                           /**< ��ȡ����Э������ */
	int32_t             (*set_size) (handle_t, size_t);
	int32_t             (*ioctl)    (handle_t, int32_t, void*, size_t);   /**< ���û�ȡ����Э�� */
	uint32_t            (*read)     (handle_t, uint8_t*, ssize_t*);       /**< ���������� */
	ssize_t             (*write)    (handle_t, const uint8_t*, size_t);   /**< д�������� */
	int32_t             (*close)    (handle_t);                           /**< �رմ򿪵�����Э�� */
} GxUpdate_ProtocolOps;


/** ������������*/
typedef struct {
	char*    name;                                             /**< ������*/
	handle_t (*open)    (const char*);                         /**< �򿪷���*/
	int32_t  (*ioctl)   (handle_t, int32_t, void*, size_t);    /**< ���û�ȡ����Э��*/
	ssize_t  (*get_size)(handle_t);                            /**< ��ȡ��д������С*/
	ssize_t  (*read)    (handle_t, uint8_t*, size_t);          /**< ����������*/
	ssize_t  (*write)   (handle_t, const uint8_t*, size_t);    /**< д��������*/
	int32_t  (*close)   (handle_t);                            /**< �رմ򿪵ķ���*/
} GxUpdate_PartitionOps;

__END_DECLS

#endif

