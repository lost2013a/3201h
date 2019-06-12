#ifndef GX_EMAIL_H
#define GX_EMAIL_H

#include <time.h>

#include "gxcore.h"
#include "gxcas.h"

__BEGIN_DECLS
#define	EMAIL_WRITE_THROUGH     (1)			/*是否在每次操作后同步数据库 */

typedef enum sort_type {
	SORT_TIME_NEW_FIRST,
	SORT_TIME_OLD_FIRST,
	SORT_UNREADED_FIRST,
	SORT_LEVEL_FIRST,
}EmailSort_t;


typedef struct mail_box_info {
	int total_size;
	int used_size;

	int total_num;
	int readed_num;
	int unreaded_num;

	int have_received;                          /*也用于产生mail id */

	EmailSort_t sort;/* 邮件排序 因为sort需要保存，所以放在邮箱头部中*/
} EmailBox_t;


#define	MAX_AUTHOR_NAME     (32)			/*邮件作者  */
#define	MAX_TITLE_LEN       (64)			/*邮件台头 */

typedef struct mail_head {
	int mail_level;               /* 邮件等级，值越大，级别越低*/
	char author[MAX_AUTHOR_NAME];
	char title[MAX_TITLE_LEN];

	time_t creat_time;            /* 创建时间，调用ADD时调用者无需关心以下几项 */
	int mail_state;               /* 邮件状态 1未读，0已读*/
	int mail_id;                  /* 邮件到ID */
} EmailHead_t;

#define	MAX_CONTEXT_LEN     (1024)			/*邮件正文长度  */
#define	MAX_CC_LEN          (128)			/*邮件抄送人  */
#define	MAX_ADDRESSEE_LEN   (128)			/*邮件收件人列表 */
#define	MAX_SING_LEN        (128)			/*邮件签名档  */
typedef struct mail_body {
	char context[MAX_CONTEXT_LEN];
	char cc[MAX_CC_LEN];
	char addressee[MAX_ADDRESSEE_LEN];
	char singnature[MAX_SING_LEN];
}EmailBody_t;

typedef struct mail_all {
	EmailHead_t mail_head;
	EmailBody_t mail_body;
} Email_t;

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  GxEmail_Init
 *  Description:  初始化邮件，参数box_size用于规定邮箱到内存大小
 *  每次打开到邮箱 path都应该不同，否则将操作同一数据区，导致错误。
 * =====================================================================================
 */
handle_t GxEmail_Open(const char* path,int32_t box_size);

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  GxEmail_Add
 *  Description:  添加一封邮件，参数为邮件头head和邮件主体body.
 * =====================================================================================
 */
int32_t GxEmail_Add(handle_t handle,Email_t *mail);

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  GxEmail_Del
 *  Description:  根据mail_id删除一封邮件
 * =====================================================================================
 */
int32_t GxEmail_Del(handle_t handle,int32_t mail_id);

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  GxEmail_ReadHeads
 *  Description:  获取邮件头列表，用于显示。参数from count规定从第几封邮件开始读取
 *  多少封邮件。返回读取到的邮件头个数
 * =====================================================================================
 */
int32_t GxEmail_ReadHeads(handle_t handle,uint32_t from,uint32_t count,EmailHead_t *heads);

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  GxEmail_ReadBody
 *  Description:  根据mail_id获取邮件主体
 * =====================================================================================
 */
int32_t GxEmail_ReadBody(handle_t handle,int32_t mail_id,EmailBody_t *body);

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  GxEmail_Sort
 *  Description:  对邮件进行排序，模块只在读取时改变顺序，而并不改变存在flash中
 *  到内容。
 * =====================================================================================
 */
int32_t GxEmail_Sort(handle_t handle,EmailSort_t sort);

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  GxEmail_SetReaded
 *  Description:  根据mail_id设置已读状态。
 * =====================================================================================
 */
int32_t GxEmail_SetReaded(handle_t handle,int32_t mail_id);

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  GxEmail_SetUnreaded
 *  Description:  根据mail_id设置邮件为未读状态
 * =====================================================================================
 */
int32_t GxEmail_SetUnreaded(handle_t handle,int32_t mail_id);

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  GxEmail_ReadBoxInfo
 *  Description:  获取邮箱信息
 * =====================================================================================
 */
int32_t GxEmail_ReadBoxInfo(handle_t handle,OUT EmailBox_t *box);

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  GxEmail_Sync
 *  Description:  用于同步数据库，写进非易失性存储器。在写通模式下，每次有效操作
 *  都会对非易失性存储器进行操作，此函数无效
 * =====================================================================================
 */
#if EMAIL_WRITE_THROUGH == 0
int32_t GxEmail_Sync(handle_t handle);
#endif
/*
 * ===  FUNCTION  ======================================================================
 *         Name:  GxEmail_Close
 *  Description:  关闭邮件文件
 * =====================================================================================
 */
int32_t GxEmail_Close(handle_t handle);

__END_DECLS
#endif

