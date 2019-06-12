
/*@{*/
#ifndef __GX_HW_MALLOC_H__
#define __GX_HW_MALLOC_H__

#include "gxcore.h"

__BEGIN_DECLS

typedef struct
{
	int32_t gx_av_handle;
	void* mmp_address;
	void* phys_address;
	uint32_t size;
}GxHwInfo;

typedef struct
{
	void* usr_p;//用户使用的真正的指针,用户态
	void* kernel_p;//用户使用的真正的指针，内核态
	uint32_t size;
	uint32_t id;//第一次申请时请赋值为0,之后不需要再改变

	/*CACHE表示空间来自于缓冲区 该参数由GxCore_HwMalloc里面填写，提供用户判断申请到的空间是否来自缓冲区。
	 *
	 * 使用范例：在ui中解析图片后释放指针，如果下次申请同一个图片的解析空间（id，size，&p都是同一个)
	 * 发现flag==cache，那么说明上次解析好的图片数据还没有被真正释放，ui可以不用再次解析*/
#define CACHE (1)
#define NO_CACHE (2)
	uint32_t flag;
}GxHwMallocObj;

typedef enum
{
	MALLOC_WITH_CACHE = 1,//带缓冲的申请，那么GxCore_HwFree 不会真正的free，而是放入free队列
	MALLOC_NO_CACHE =2,
	MALLOC_NO_FAIL =4,//如果fb分配失败，会尝试从内核分配
}GxHwMallocFlag;

/*#########私有函数，一般来说用户不应该直接调用以下两个函数#############*/
void GxCore_HwMallocDebug(GxHwMallocObj *p, const char  *file,uint32_t line, GxHwMallocFlag flag);
void GxCore_HwMallocRelease(GxHwMallocObj *p, GxHwMallocFlag flag);


/*#########开放用户使用的函数#############*/


/**
 * @brief  初始化，必须要首先调用,在app_star.cpp里面调用,hw malloc管理的空间来自cmdline里面分配的fb mem
 * @return 
 */
void GxCore_HwMallocInit(void);

/**
 * @brief  free
 * @return 
 */
void GxCore_HwFree(GxHwMallocObj* p);

/**
 * @brief  获取gx vq的信息
 * @return 
 */
void GxCore_HwGetInfo(GxHwInfo* info);

/**
 * @brief 该函数会通过打印输出调试信息，在DBG_QM_MALLOC模式下输出信息会有所不同
 * @return 
 */
void GxCore_HwCheckDebug(void);

/**
 * @brief 提供用户随时查询
 * @return: 0 表示检测成功，指针是正常的
 * 			-1 表示检测失败  有异常，通过打印看是什么异常
 */
int32_t GxCore_HwCheck(GxHwMallocObj* p);

/**
 * @brief malloc ,DBG_QM_MALLOC模式下有所区别,用户一般通过p->usr_p和p->kernel_p是否为NULL来判断malloc成功与否
 * @return: 
 */
#ifdef DBG_QM_MALLOC
#define GxCore_HwMalloc(p,flag) GxCore_HwMallocDebug(p,__FILE__,__LINE__,flag)
#else
#define GxCore_HwMalloc(p,flag) GxCore_HwMallocRelease(p,flag)
#endif


/**
 * @brief 清除所有缓冲
 * @return:
 */
void GxCore_HwCleanCache(void);

__END_DECLS

#endif

/*@}*/


