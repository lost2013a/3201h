#ifndef __GXCA_DEBUG_H__
#define __GXCA_DEBUG_H__

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define __DEBUG__
/*mode*/
enum {
	CAS,            /* ca系统的debug信息   */
	DEMUX,          /* demux的debug信息    */
	DESCRAMBLER,    /* 解扰模块的debug信息 */
	SMC,            /* 智能卡的debug信息   */
	NVRAM,          /* flash的debug信息    */
	EMAIL,
	/* 各家ca模块 */
	HLCA,           /* 慧龙cas             */
	CHCA,           /* 长虹cas             */
	TFCA,           /* 同方cas             */
	MGCA,           /* 三洲迅驰cas         */
	MGCA42X,        /* 三洲迅驰4.2.x       */
	SUMAVISION_S,   /* 数码高级安全CA      */
	MAX_MOD_ID = 64
};




#define DISABLE     0   /* disable debug out put            */
#define EMERG       1   /* system is unusable               */
#define ERR         2   /* error conditions                 */
#define WARNING     3   /* warning conditions               */
#define NOTICE      4   /* normal but significant condition */
#define INFO        5   /* informational                    */

extern unsigned char debug_level[];
#define DEBUG_ENABLE_MODE(module,level)	{debug_level[module] = level;}
#define DEBUG_DISABLE_MODE(module)		{debug_level[module] = DISABLE;}
#ifdef __DEBUG__
#define DEBUG(module,level,fmt, ...)												\
    do {																		\
        if ((level <= debug_level[module]))		\
        printf("[%s>%s]%s():%d: "fmt,#module,#level, __func__, __LINE__, ##__VA_ARGS__);		\
    } while (0)

#define DUMP(module,level,len,p,fmt) \
	do {	\
		if ((level <= debug_level[module])){		\
			int i__;\
			printf("[%s>%s]%s():%d: ",#module,#level, __func__, __LINE__);		\
			printf("len = %d>>>",len);\
			for(i__=0;i__<len;i__++){\
				printf(fmt",",p[i__]);\
				if (i__&&i__%20 == 0)printf("\n");\
			}\
			printf("\n");\
		}\
	}while (0)

#else
#define DEBUG(mode,level,args...)		((void)0)
#define DUMP(len,p,fmt)		do{}while(0)
#endif



#ifdef __DEBUG__
	#define D_CHECK_BOOL(ret)  do{if(!ret)printf("On file:%s line %d >>> \n%s check bool return failure!\n",__FILE__,__LINE__,#ret);}while(0)
	#define D_CHECK_ZERO(ret)  do{if(ret != 0)printf("On file:%s line %d >>> \n%s check zero return failure!\n",__FILE__,__LINE__,#ret);}while(0)
#ifndef ASSERT
    #define ASSERT(a) do{if(!(a))printf("Assert failure %s in %s:%d",#a,__func__,__LINE__);}while(0)
#endif
#else
	#define D_CHECK_BOOL(ret) do{(ret);}while(0)
	#define D_CHECK_ZERO(ret) do{(ret);}while(0)
#ifndef ASSERT
    #define ASSERT(a) do{if(!(a))printf("Assert failure %s in %s:%d",#a,__func__,__LINE__);return -1;}while(0)
#endif
#endif


#define	CHECK_RET(module,ret)     do{ if(ret<0)DEBUG(module,ERR,"ret value err :%d\n",ret);}while(0)

#endif



