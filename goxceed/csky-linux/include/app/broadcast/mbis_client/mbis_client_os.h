#ifndef _MBIS_CLIENT_OS_H_
#define _MBIS_CLIENT_OS_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//-----------------------   memory  ---------------------------

int d_mbis_mem_open(void);

void* os_malloc(unsigned int size);

void os_free(void* ptr);

int d_mbis_mem_close(void);

//----------------------  task/thread  ------------------------

//int os_task_create(void (*pTaskFun)(void*), void* pParam);
int os_task_create(void (*pTaskFun)(void*), void* pParam, unsigned char priority);

int os_task_destroy(int taskID);

void os_task_delay(unsigned int millisecond);


//------------------------   mutex  ---------------------------

int os_mutex_create(void);

int os_mutex_lock(int mutex);

int os_mutex_unlock(int mutex);

int os_mutex_destroy(int mutex);

//-----------------------  semaphore  -------------------------

int os_sem_create(void);

int os_sem_destroy(int sem);

int os_sem_post(int sem);

int os_sem_wait(int sem);

//------------------------  debug msg ---------------------------


void os_debug_msg(char* fmt, ...);


//-----------------------   stbid  ---------------------------

int os_get_stbid(char* stbid);


//-----------------------   cas  ---------------------------

// 获得机顶盒的CAS号.
// -->(1)同方凌讯版本: 通过调用该接口, 获得机顶盒的CAS号, 进而进行授权检测.
// -->(2)山东版本: 无授权检测业务流程, 不会调用该接口.
int os_get_cas(unsigned char* cas);


//------------------------  System Time  ------------------------

long os_get_clock_count(void);

int os_get_system_time(char* pOut);

int os_get_system_date(char* pOut);

long os_difftime(const char* pTime1, const char* pTime2);


//--------------------  volume space  ---------------------------

typedef long long int X_I64;
typedef unsigned long long int X_U64;

X_I64 os_get_volume_total_size(const char* path);

X_I64 os_get_volume_free_size(const char* path);


//-----------------------  File I/O  ----------------------------

typedef void* FS_Handle;

int os_check_exist(const char* path);

int os_check_read(const char* path);

int os_check_write(const char* path);

X_I64 os_get_file_size(const char* pFile);

int os_rename(const char* pOldName, const char* pNewName);

int os_create_file(const char *pFile, X_U64 size);

int os_reset_file_size(FS_Handle handle, X_U64 size);

int os_delete_file(const char *pFile);

int os_copy_file(const char* pSrcFile, const char* pDesFile);

int os_create_dir(const char* pDir);

int os_delete_dir(const char* pDir);

int os_clear_dir(const char* pDir);

FS_Handle os_open_file(const char *pFile);

void os_close_file(FS_Handle handle);

int os_read_file(FS_Handle handle, X_I64 offset, void *buf, unsigned int count);

int os_write_file(FS_Handle handle, X_I64 offset, const void *buf, unsigned int count);

int os_file_append(FS_Handle handle, void *buf, unsigned int count);

int os_same_node(const char* path1, const char* path2);

int os_file_move(const char* pSrcFile, const char* pDesDir);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _MBIS_CLIENT_OS_H_
