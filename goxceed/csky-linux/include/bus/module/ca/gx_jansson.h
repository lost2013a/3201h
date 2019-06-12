
/*******************************************************************************
@brief: 本模块用于对json进行封装,使用key对结构成员赋值以及对
	结构成员的索引.模块自行分析key中表现出来的结构体层次,
	并根据得到的层次分配数据位置.本模块提供三种基本的数据
	类型,存储结构的最小成员,分别为:long long 的整形;double的浮点型
	以及字符串类型;(指针类型,bool类型用整形存储).
	模块存储数据成员时,并不一定顺序存储,模块以哈希表的方式
	存储各成员,以加快索引的速度.
	模块提供格式化的key输入,用于循环输入数组成员.
*******************************************************************************/
#ifndef   __GX_JANSSON_H__

#define __GX_JANSSON_H__
#define MAX_JSON_KEY_LEN	(128)

#include "gxcore.h"

__BEGIN_DECLS

typedef void*   GxJson_t;

/**
* @brief New a container to contain all member
* @return pointer to container. NULL: failure
*/
GxJson_t  GxJson_New(void);

/**
* @brief append a string member to container
* @param GxJson_t  container: pointer to container.
* @param const char* key: key to bind the member
* @param const char* string: the value
* @return int <0,failure;>=o,success;
*/
int GxJson_SetString(GxJson_t container,const char* key,const char*string);


/**
* @brief get a string member from container
* @param GxJson_t  container: pointer to container.
* @param const char* key: key to find the member
* @return char* if(NULL),failure;else,the string;
*/
const char* GxJson_GetString(GxJson_t container,const char* key);

/**
* @brief append a float member to container
* @param GxJson_t  container: pointer to container.
* @param const char* key: key to bind the member
* @param double val: the value
* @return int <0,failure;>=o,success;
*/
int GxJson_SetFloat(GxJson_t container,const char* key,double val);


/**
* @brief get a flot member from container
* @param GxJson_t  container: pointer to container.
* @param const char* key: key to find the member
* @return double if(0.0) the value of float is 0.0 or failure;else,the float value;
*/
double GxJson_GetFloat(GxJson_t container,const char* key);

/**
* @brief append a integer member to container
* @param GxJson_t  container: pointer to container.
* @param const char* key: key to bind the member
* @param long long val: the value
* @return int <0,failure;>=o,success;
*/
int GxJson_SetInteger(GxJson_t container,const char* key,long long val);


/**
* @brief get a integer member from container
* @param GxJson_t  container: pointer to container.
* @param const char* key: key to find the member
* @return long long  if(0) the value of integer is 0 or failure;else,the integer value;
*/
long long  GxJson_GetInteger(GxJson_t container,const char* key);


/**
* @brief append a string member to container with format key
* @param GxJson_t  container: pointer to container.
* @param const char*string: the value
* @param const char* fmt ...: key to bind the member. i.e ("frends[%d].englishname",1)
* @return int <0,failure;>=o,success;
*/
int GxJson_SetStringWithFmtKey(GxJson_t container,const char*string,const char* fmt,...);

/**
* @brief get a string member from container
* @param GxJson_t  container: pointer to container.
* @param const char* fmt,...: format key to find the member  i.e ("frends[%d].englishname",1)
* @return char* if(NULL),failure;else,the string;
*/
const char* GxJson_GetStringWithFmtKey(GxJson_t container,const char* fmt,...);

/**
* @brief append a float member to container with format key
* @param GxJson_t  container: pointer to container.
* @param double val: the value
* @param const char* fmt ...: key to bind the member. i.e ("frends[%d].englishname",1)
* @return int <0,failure;>=o,success;
*/
int GxJson_SetFloatWithFmtKey(GxJson_t container,double val,const char* fmt,...);

/**
* @brief get a float member from container
* @param GxJson_t  container: pointer to container.
* @param const char* fmt,...: format key to find the member  i.e ("frends[%d].englishname",1)
* @return double  if(0.0) the value of float is 0.0 or failure;else,the float value;
*/
double GxJson_GetFloatWithFmtKey(GxJson_t container,const char* fmt,...);


/**
* @brief append a integer member to container with format key
* @param GxJson_t  container: pointer to container.
* @param long long val: the value
* @param const char* fmt ...: key to bind the member. i.e ("frends[%d].englishname",1)
* @return int <0,failure;>=o,success;
*/
int GxJson_SetIntegerWithFmtKey(GxJson_t container,long long val,const char* fmt,...);

/**
* @brief get a integer member from container
* @param GxJson_t  container: pointer to container.
* @param const char* fmt,...: format key to find the member  i.e ("frends[%d].englishname",1)
* @return long long  if(0) the value of integer is 0 or failure;else,the integer value;
*/
long long  GxJson_GetIntegerWithFmtKey(GxJson_t container,const char* fmt,...);


/**
* @brief free the container and all item that appended to it will be free
* @param GxJson_t  container: pointer to container.
* @return int <0,failure;>=o,success;
*/
int GxJson_Free(GxJson_t  container);

/**
* @brief  dump string,make the content of the container as a format string.
* @param GxJson_t  container: pointer to container.
* @return char* if(NULL),failure;else,the string;
*/
char* GxJson_DumpString(GxJson_t container);

/**
* @brief  load string,change string to a json container.
* @param const char* string: pointer to string;
* @return GxJson_t  if(NULL),failure;else,the string;
*/
void *GxJson_LoadString(const char* string);

/**
* @brief  free string buffer
* @param const char* string: pointer to string;
* @return void;
*/
void GxJson_FreeString(char* string);

__END_DECLS

#endif



