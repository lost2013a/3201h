/*@{*/
#ifndef __DSMCC_H__
#define __DSMCC_H__

#include "gxcore.h"
#include "sub_system/si_sub_engine/si_sub_engine.h"

__BEGIN_DECLS

/*返回值*/
#define DSMCC_PARAMETER_ERR (-1)
#define DSMCC_ERR           (-2)
#define DSMCC_SUCCESS       (0)

typedef int32_t DsmccHandle;

/* Exported Types --------------------------------------------------------- */


typedef struct {
	uint32_t type_id_len;
	uint8_t* type_id;//service gate way = "srg"; file = "fil"; director="dir"
	uint32_t carousel_id;
	uint16_t module_id;
	uint32_t object_key_length;//应该小于等于0x4
	uint8_t* object_key;
}DsmccPorgServiceGate;

typedef struct {
	uint32_t module_id;
	uint32_t module_size;
	uint32_t block_size;
	uint32_t total_block_num;// module_size/block_size
	uint32_t block_num;// block_num == total_block_num 接收完成
	uint8_t* block;
	uint32_t module_version;
	uint8_t* data;
}DsmccModule;

typedef struct {
	uint32_t prog_pid;//用来过滤dii dsi ddb 从pmt解析出来
    int8_t* base_dir;//基本目录路径，暂时不知道干什么用 ait解出来的
	int8_t* name;//app名字，从ait解析出来的
	uint8_t language[3];
	uint8_t component_tag;//用来对应pmt和ait
	SiEngineHandle si_dsi;
	DsmccPorgServiceGate service_gate;
	SiEngineHandle si_dii;
	uint32_t total_module_count;
	uint32_t module_count;//module_count = total_module_count时 module接收完毕
	DsmccModule* module;
	SiEngineHandle si_ddb;
	uint32_t finish_flag;//prog目录树解析完成标志，用于ddb解析轮讯查找，如果嫌慢可以仿照si engine做成队列
}DsmccPorg;

typedef struct {
	int8_t* root;
	uint32_t pmt_pid;
	uint32_t dmx_id;
	uint32_t ts_id;
	uint32_t sw_buffer_size;//用于过滤ddb的fifo大小
}DsmccOpen;

/*根据java里面的分析得出的数据结构*/
typedef enum {
	NEIMENG_DIR=0,
	NEIMENG_FILE,
}DsmccNeimengType;

typedef struct {
	uint32_t start_index;
	int8_t* name;
}DsmccNeimengDirInfo;

typedef struct {
	uint16_t file_id;
	uint16_t reserved;
	int8_t* name;
}DsmccNeimengFileInfo;

typedef struct {
	DsmccNeimengType type;
	union
	{
		DsmccNeimengDirInfo dir;
		DsmccNeimengFileInfo file;
	};
}DsmccNeimengDirObj;

/**
 * @brief      dsmcc初始化
 *
 * @param     root:存放dsmmc文件的根目录
 * 			  pmt_pid:dsmcc节目的pmt pid//该pid应该是搜台搜出来的，但是内蒙古这个dsmcc节目没有正确标识，
 * 			  所以。。。暂时假定知道pmt pid先
 *
 * @return    -1:执行失败
 */
DsmccHandle GxDsmccOpen(DsmccOpen* init);

#if 0
/**
 * @brief      启动dsmcc
 *
 * @param      obj:申请到的dsmcc句柄
 *
 *
 * @return    -1:执行失败
 * 			   0:执行成功
 */
int32_t GxDsmccStart(DsmccHandle obj);
/**
 * @brief      获取本次dsmcc中有多少prog
 *
 * @param      obj:申请到的dsmcc句柄
 *
 *
 * @return    -1:执行失败
 * 			   0～n:prog数量
 */
int32_t GxDsmccProgNum(DsmccHandle dsmcc);
/**
 * @brief      开始一个数据广播prog的过滤 之后需要GxDsmccWait等待过滤完成。
 *
 * @param      obj:申请到的dsmcc句柄
 * 				prog_pid:要过滤的节目pid
 *
 *
 * @return    -1:执行失败
 * 			   0:执行成功
 */
int32_t GxDsmccFilterProg(DsmccHandle dsmcc,uint32_t prog_pid);
#endif

/**
 * @brief      等待完成过滤调用GxDsmccStart和GxDsmccFilterProg之后都使用该函数等待完成通知
 * 				等待过程中会引起线程休眠
 *
 * @param      obj:申请到的dsmcc句柄
 *
 *
 * @return    -1:执行失败
 * 			   0:执行成功
 */
int32_t GxDsmccWait(DsmccHandle dsmcc);

/**
 * @brief      开始一个内蒙古数据广播节目dir根目录解析 之后需要GxDsmccWait等待过滤完成。
 *
 * @param      obj:申请到的dsmcc句柄
 * 				pid:节目的pid 例如阳光视讯就是7155
 *
 *
 * @return    -1:执行失败
 * 			   0:执行成功
 */
int32_t GxDsmccNeimengFilterRoot(DsmccHandle dsmcc,uint32_t pid);
/**
 * @brief      开始一个内蒙古数据广播节目dir解析 之后需要GxDsmccWait等待过滤完成。
 * 				其中start_index是从GxDsmccNeimengFilterRoot开始获取
 *
 * @param      obj:申请到的dsmcc句柄
 *
 *
 * @return    -1:执行失败
 * 			   0:执行成功
 */
int32_t GxDsmccNeimengFilterDir(uint32_t start_index);
/**
 * @brief      获取内蒙古数据广播。目录中的成员数量
 *
 * @param      obj:申请到的dsmcc句柄
 *
 *
 * @return    -1:执行失败
 *             其他数字：dir中成员数量
 */
int32_t GxDsmccNeimengGetDirCount(void);
/**
 * @brief      获取内蒙古数据广播。目录中列表
 *
 * @param        list:保存列表的空间，由用户申请
 *               pos:希望从何处获取列表,从0开始
 *               count：希望获取的成员数量，
 *
 * @return    -1:执行失败
 *             其他数字：dir中成员数量
 */
int32_t GxDsmccNeimengGetDirList(DsmccNeimengDirObj* list,uint32_t pos,uint32_t count);
/**
 * @brief      开始一个内蒙古数据广播节目文件解析 之后需要GxDsmccWait等待过滤完成。
 *
 * @param      obj: 申请到的dsmcc句柄
 *             pid: 节目的pid 例如阳光视讯就是7155
 *             file_id：从目录列表里得到的file标识
 *
 *
 * @return    -1:执行失败
 *             0:执行成功
 */
int32_t GxDsmccNeimengFilterFil(DsmccHandle dsmcc, uint32_t pid,uint16_t file_id);
/**
 * @brief      获取文件的内容
 *
 * @param
 *
 * @return    NULL:执行失败
 *            其他值为文件内容指针
 */
int8_t* GxDsmccNeimengGetFil(void);

__END_DECLS

#endif
/*@}*/

