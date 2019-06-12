/**@defgroup book_service BOOK Service*/
 /*@{*/
/* Define to prevent recursive inclusion */
#ifndef __GX_BOOK_H__
#define __GX_BOOK_H__

#include "gxbus.h"
#include "gxcore.h"
#include <time.h>

__BEGIN_DECLS

/**����ܴ洢��book�������*/
#define MAX_BOOK_NUM	(32)

#define MAX_BOOK_STRUCT_LEN	(56)


/**
 * @brief	����bookʱ����ִ�еĻص���������ֱ��ִ�й��ܴ�����߷���Ϣ
 * @param   struct_buf �洢��book�ṹ���е��Զ������ݽṹָ��
 * @Return  void
 */
typedef void (*GxBookExec)(uint8_t *struct_buf);

/**
 * book���ͣ���book�������ֹ���
 */
typedef enum
{
	BOOK_PROGRAM_PLAY = 1, ///< ԤԼ����
	BOOK_POWER_ON = 1<<1,  ///< ԤԼ����
	BOOK_POWER_OFF = 1<<2, ///< ԤԼ�ػ�
	BOOK_TYPE_1 = 1<<3,    ///< Ԥ������1
	BOOK_TYPE_2 = 1<<4,    ///< Ԥ������2
	BOOK_TYPE_3 = 1<<5,    ///< Ԥ������3
}GxBookType;

/**
 * book�Ĵ���ģʽ
 */
typedef enum
{
	BOOK_TRIG_OFF = 0,    ///< �رմ�book
	BOOK_TRIG_ING,        ///< �δ����м�״̬
	BOOK_TRIG_BY_POINT,   ///< ֻ��ĳһ��ʱ��㴥��book
	BOOK_TRIG_BY_SEGMENT, ///< ��ĳһʱ����ڶ��ɴ���book, �ο����ʱΪ20Сʱ
} GxBookTriggerMode;

/**
 * book�ظ�ģʽ������Ҫ�����ӻ���һ��ֵ��mode����
 */
typedef struct
{
	uint32_t mode;
#define BOOK_REPEAT_MON       (1<<1)
#define BOOK_REPEAT_TUES      (1<<2)
#define BOOK_REPEAT_WED       (1<<3)
#define BOOK_REPEAT_THURS     (1<<4)
#define BOOK_REPEAT_FRI       (1<<5)
#define BOOK_REPEAT_SAT       (1<<6)
#define BOOK_REPEAT_SUN       (1)
#define BOOK_REPEAT_EVERY_DAY (0x7f)
#define BOOK_REPEAT_ONCE      (1<<8)
}GxBookRepeatMode;

/**
 * book�Ľṹ�壬�ڽ��������١��޸ġ���ʼ��ֹͣʱ���õ�
 */
typedef struct
{
	int32_t   id;                            ///< Ψһ��ʶĳ��book��id�ţ��ڽ���ʱ���
	uint32_t  pos;                           ///< ��0��ʼһֱ�������ӣ��ɱ�ʶbook�Ľ���˳��
	GxBookType book_type;                    ///< ������bookΪ�ι��ܶ�����
	GxBookTriggerMode  trigger_mode;         ///< book�Ĵ���ģʽ
	GxBookRepeatMode  repeat_mode;           ///< book�¼����ظ�ģʽ
	time_t time_stamp;                       ///< ����bookʱ����Ҫ���ô�ֵ������:Ԥ���δ���ģʽ�µĶ�δ���
	time_t trigger_time_start;               ///< ʱ��㴥�����ø�ֵ��ʱ��δ�������ʼֵ
	time_t trigger_time_end;                 ///< ʱ��㴥���������ã�ʱ��δ����Ľ���ֵ���μ�����Ϊ20Сʱ
	uint32_t struct_size;                    ///< �洢�ṹ�Ĵ�С
	uint8_t struct_buf[MAX_BOOK_STRUCT_LEN]; ///< ���ṹ�����ݿ�������
}GxBook;

/**
 * �ڻ�ȡbookʱ���õ������ݽṹ
 */
typedef struct
{
	GxBookType book_type;  ///< ������bookΪ�ι��ܶ�����
	uint32_t  book_number; ///< �ù��ܵ�book���м���book
	GxBook  *book;         ///< �洢ĳ��book type����Ϣ
}GxBookGet;

typedef GxBook GxMsgProperty_BookTrigger;
typedef GxBook GxMsgProperty_BookFinish;  // �δ����д���Ϣ
typedef GxBook* GxMsgProperty_BookCreate;
typedef GxBook* GxMsgProperty_BookDestroy;
typedef GxBook* GxMsgProperty_BookModify;
typedef GxBookGet* GxMsgProperty_BookGet;

__END_DECLS

#endif /* __GX_BOOK_H__ */
/*@}*/


