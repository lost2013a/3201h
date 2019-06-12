#ifndef GXCORE_OS_CORE
#define GXCORE_OS_CORE

#include "gxtype.h"
#include "stdarg.h"   /* for va_list */
#include "gxcore_version.h"
#include "common/md5.h"

#ifdef __cplusplus
extern "C"{
#endif

#define GXOS_DEFAULT_PRIORITY 15

#define GX_PROT_READ		0x1		/* page can be read */
#define GX_PROT_WRITE		0x2		/* page can be written */
#define GX_PROT_EXEC		0x4		/* page can be executed */
#define GX_PROT_SEM			0x8		/* page may be used for atomic ops */
#define GX_PROT_NONE		0x0		/* page can not be accessed */

#define GX_MAP_SHARED		0x01	/* Share changes */
#define GX_MAP_PRIVATE		0x02	/* Changes are private */
#define GX_MAP_TYPE			0x03	/* Mask for type of mapping */
#define GX_MAP_FIXED		0x04	/* Interpret addr exactly */
#define GX_MAP_ANONYMOUS	0x10	/* don't use a file */

/* struct for GxCore_GetLocalTime() */
typedef struct {
    uint32_t seconds;
    uint32_t microsecs;
}GxTime;

typedef enum gx_nable {
	GX_ENABLE = 1,
	GX_UNABLE = 0
}GxNable;

/* This typedef is for the GxCore_GetErrorName function, to ensure
 * everyone is making an array of the same length */

typedef char os_err_name_t[35];

/* Initialization of API */
void GxCore_Init(void);
void GxCore_Cleanup(void);

/* Thread API */
int32_t GxCore_ThreadCreate        (const char *thread_name, handle_t *thread_id,
                                      void(*entry_func)(void *), void *arg,
                                      uint32_t stack_size,
                                      uint32_t priority);

int32_t GxCore_ThreadCreateExtend  (const char *thread_name, handle_t *thread_id,
                                      void(*entry_func)(void *), void *arg,
                                      uint32_t stack_size,
                                      uint32_t priority,
                                      uint32_t sched_policy,
                                      uint32_t detach_state);

int32_t GxCore_ThreadDelete       (handle_t thread_id);
//void     GxCore_ThreadExit         (void);

void     GxCore_ThreadStackCheck   (GxNable on_off);
int32_t  GxCore_ThreadEqual        (handle_t thread_id1, handle_t thread_id2);
int32_t  GxCore_ThreadDelay        (uint32_t millisecond);
int32_t  GxCore_ThreadSetPriority  (handle_t thread_id, uint32_t new_priority);
int32_t  GxCore_ThreadGetPriority  (handle_t thread_id, uint32_t *priority);
int32_t  GxCore_ThreadGetId        (void);
int32_t  GxCore_ThreadYield        (void);
int32_t  GxCore_ThreadJoin         (handle_t thread_id);
int32_t  GxCore_ThreadDetach       (void);
int32_t GxCore_ThreadCheckStack    (char mode);//0 - 检查越界  1 - 检查越界并且打印堆栈使用情况
int32_t GxCore_ThreadGetStack      (handle_t thread_id, uint8_t **stackbase, int32_t *stacksize);

typedef pthread_key_t gxthread_key_t;

int32_t GxCore_ThreadKeyCreate     (gxthread_key_t *key, void (*func)(void*));
int32_t GxCore_ThreadKeyDelete     (gxthread_key_t key);
int32_t GxCore_ThreadSetSpec       (gxthread_key_t key, void *p);
void *  GxCore_ThreadGetSpec       (gxthread_key_t key);

#ifndef MD5_DIGEST_LENGTH
#define	MD5_DIGEST_LENGTH		16
#endif
void GxCore_CodeMd5(unsigned char md5[MD5_DIGEST_LENGTH]);

/* Message Queue API */
int32_t  GxCore_QueueCreate        (handle_t *queue_id, uint32_t queue_depth, uint32_t data_size);
int32_t  GxCore_QueueDelete        (handle_t queue_id);
int32_t  GxCore_QueueGet           (handle_t queue_id, void *data, uint32_t size, uint32_t *size_copied, int32_t timeout);
int32_t  GxCore_QueuePut           (handle_t queue_id, void *data, uint32_t size,int32_t timeout);

/* Semaphore API */
int32_t  GxCore_SemCreate          (handle_t *sem_id, uint32_t sem_initial_value);
int32_t  GxCore_SemPost            (handle_t sem_id);
int32_t  GxCore_SemWait            (handle_t sem_id);
int32_t  GxCore_SemTryWait         (handle_t sem_id);
int32_t  GxCore_SemGetValue        (handle_t sem_id, int32_t *sval);
int32_t  GxCore_SemTimedWait       (handle_t sem_id, uint32_t msecs);
int32_t  GxCore_SemDelete          (handle_t sem_id);

/* Condition Variables */
int32_t  GxCore_CondInit           (handle_t *cond_id);
int32_t  GxCore_CondDelete         (handle_t cond_id);
int32_t  GxCore_CondWait           (handle_t cond_id, handle_t mutex_id, int32_t timeout);
int32_t  GxCore_CondSignal         (handle_t cond_id);
int32_t  GxCore_CondBroadcast      (handle_t cond_id);

/* Mutex API */
int32_t  GxCore_MutexCreate        (handle_t *mutex_id);
int32_t  GxCore_MutexCreateExt     (handle_t *mutex_id);
int32_t  GxCore_MutexLock          (handle_t mutex_id);
int32_t  GxCore_MutexUnlock        (handle_t mutex_id);
int32_t  GxCore_MutexTrylock       (handle_t mutex_id);
int32_t  GxCore_MutexDelete        (handle_t mutex_id);

/* OS Time/Tick related API */
int32_t  GxCore_GetTickTime        (GxTime *time_struct);
int32_t  GxCore_GetLocalTime       (GxTime *time);
int32_t  GxCore_SetLocalTime       (GxTime *time);
uint64_t GxCore_TickStart(int timeout_ms);
int32_t GxCore_TickEnd(uint64_t ms);

void    *GxCore_Map                (int dev, uint32_t kernel_addr, uint32_t size);
int32_t  GxCore_UnMap              (int dev, void *user_addr, uint32_t size);

/* API for a useful debugging function */
int32_t  GxCore_GetErrorName       (int32_t error_num, os_err_name_t* err_name);

/* Abstraction for printf statements */
void GxCore_printf( const char *string, ...);

void GxCore_Loop(void);

/* Assert */
void _GxCore_Assert(int a,char* a_name, char* file_name, int line_num);
#define GxCore_Assert(a) do{_GxCore_Assert((int)a, (char *)__func__, __FILE__, __LINE__);}while(0)

bool GxCore_UpUserPermissions(void);
void GxCore_DownUserPermissions(void);
bool GxCore_UpGroupPermissions(void);
void GxCore_DownGroupPermissions(void);

#ifdef __cplusplus
}
#endif

#endif
