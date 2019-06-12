/**
 *
 * @file        app_common_porting_debug.h
 * @brief
 * @version     1.1.0
 * @date        01/12/2015 09:47:49 AM
 * @author      
 *
 */
#ifndef __APP_COMMON_PORTING_DEBUG_H__
#define __APP_COMMON_PORTING_DEBUG_H__
#ifdef __cplusplus
extern "C" {
#endif


#define APP_PORTING_DEBUG_ENABLE



#ifdef APP_PORTING_DEBUG_ENABLE


#define ASSERT_RET(ret) do {										\
								if (ret < 0) printf("[ASSERT RET]%s,%d\n",__FILE__, __LINE__);\
							} while(0)

#define ASSERT_NULL(p)  do {										\
								if (p == NULL) printf("[ASSERT NULL]%s,%d\n",__FILE__, __LINE__);\
							} while(0)



#else
	
#define ASSERT_RET(ret)

#define ASSERT_NULL(p)

#endif


#ifdef __cplusplus
}
#endif
#endif /*__APP_COMMON_PORTING_CA_API_H__*/

