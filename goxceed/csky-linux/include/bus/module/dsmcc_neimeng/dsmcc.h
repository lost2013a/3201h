/*@{*/
#ifndef __DSMCC_H__
#define __DSMCC_H__

#include "gxcore.h"
#include "sub_system/si_sub_engine/si_sub_engine.h"

__BEGIN_DECLS

/*����ֵ*/
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
	uint32_t object_key_length;//Ӧ��С�ڵ���0x4
	uint8_t* object_key;
}DsmccPorgServiceGate;

typedef struct {
	uint32_t module_id;
	uint32_t module_size;
	uint32_t block_size;
	uint32_t total_block_num;// module_size/block_size
	uint32_t block_num;// block_num == total_block_num �������
	uint8_t* block;
	uint32_t module_version;
	uint8_t* data;
}DsmccModule;

typedef struct {
	uint32_t prog_pid;//��������dii dsi ddb ��pmt��������
    int8_t* base_dir;//����Ŀ¼·������ʱ��֪����ʲô�� ait�������
	int8_t* name;//app���֣���ait����������
	uint8_t language[3];
	uint8_t component_tag;//������Ӧpmt��ait
	SiEngineHandle si_dsi;
	DsmccPorgServiceGate service_gate;
	SiEngineHandle si_dii;
	uint32_t total_module_count;
	uint32_t module_count;//module_count = total_module_countʱ module�������
	DsmccModule* module;
	SiEngineHandle si_ddb;
	uint32_t finish_flag;//progĿ¼��������ɱ�־������ddb������Ѷ���ң�����������Է���si engine���ɶ���
}DsmccPorg;

typedef struct {
	int8_t* root;
	uint32_t pmt_pid;
	uint32_t dmx_id;
	uint32_t ts_id;
	uint32_t sw_buffer_size;//���ڹ���ddb��fifo��С
}DsmccOpen;

/*����java����ķ����ó������ݽṹ*/
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
 * @brief      dsmcc��ʼ��
 *
 * @param     root:���dsmmc�ļ��ĸ�Ŀ¼
 * 			  pmt_pid:dsmcc��Ŀ��pmt pid//��pidӦ������̨�ѳ����ģ��������ɹ����dsmcc��Ŀû����ȷ��ʶ��
 * 			  ���ԡ�������ʱ�ٶ�֪��pmt pid��
 *
 * @return    -1:ִ��ʧ��
 */
DsmccHandle GxDsmccOpen(DsmccOpen* init);

#if 0
/**
 * @brief      ����dsmcc
 *
 * @param      obj:���뵽��dsmcc���
 *
 *
 * @return    -1:ִ��ʧ��
 * 			   0:ִ�гɹ�
 */
int32_t GxDsmccStart(DsmccHandle obj);
/**
 * @brief      ��ȡ����dsmcc���ж���prog
 *
 * @param      obj:���뵽��dsmcc���
 *
 *
 * @return    -1:ִ��ʧ��
 * 			   0��n:prog����
 */
int32_t GxDsmccProgNum(DsmccHandle dsmcc);
/**
 * @brief      ��ʼһ�����ݹ㲥prog�Ĺ��� ֮����ҪGxDsmccWait�ȴ�������ɡ�
 *
 * @param      obj:���뵽��dsmcc���
 * 				prog_pid:Ҫ���˵Ľ�Ŀpid
 *
 *
 * @return    -1:ִ��ʧ��
 * 			   0:ִ�гɹ�
 */
int32_t GxDsmccFilterProg(DsmccHandle dsmcc,uint32_t prog_pid);
#endif

/**
 * @brief      �ȴ���ɹ��˵���GxDsmccStart��GxDsmccFilterProg֮��ʹ�øú����ȴ����֪ͨ
 * 				�ȴ������л������߳�����
 *
 * @param      obj:���뵽��dsmcc���
 *
 *
 * @return    -1:ִ��ʧ��
 * 			   0:ִ�гɹ�
 */
int32_t GxDsmccWait(DsmccHandle dsmcc);

/**
 * @brief      ��ʼһ�����ɹ����ݹ㲥��Ŀdir��Ŀ¼���� ֮����ҪGxDsmccWait�ȴ�������ɡ�
 *
 * @param      obj:���뵽��dsmcc���
 * 				pid:��Ŀ��pid ����������Ѷ����7155
 *
 *
 * @return    -1:ִ��ʧ��
 * 			   0:ִ�гɹ�
 */
int32_t GxDsmccNeimengFilterRoot(DsmccHandle dsmcc,uint32_t pid);
/**
 * @brief      ��ʼһ�����ɹ����ݹ㲥��Ŀdir���� ֮����ҪGxDsmccWait�ȴ�������ɡ�
 * 				����start_index�Ǵ�GxDsmccNeimengFilterRoot��ʼ��ȡ
 *
 * @param      obj:���뵽��dsmcc���
 *
 *
 * @return    -1:ִ��ʧ��
 * 			   0:ִ�гɹ�
 */
int32_t GxDsmccNeimengFilterDir(uint32_t start_index);
/**
 * @brief      ��ȡ���ɹ����ݹ㲥��Ŀ¼�еĳ�Ա����
 *
 * @param      obj:���뵽��dsmcc���
 *
 *
 * @return    -1:ִ��ʧ��
 *             �������֣�dir�г�Ա����
 */
int32_t GxDsmccNeimengGetDirCount(void);
/**
 * @brief      ��ȡ���ɹ����ݹ㲥��Ŀ¼���б�
 *
 * @param        list:�����б�Ŀռ䣬���û�����
 *               pos:ϣ���Ӻδ���ȡ�б�,��0��ʼ
 *               count��ϣ����ȡ�ĳ�Ա������
 *
 * @return    -1:ִ��ʧ��
 *             �������֣�dir�г�Ա����
 */
int32_t GxDsmccNeimengGetDirList(DsmccNeimengDirObj* list,uint32_t pos,uint32_t count);
/**
 * @brief      ��ʼһ�����ɹ����ݹ㲥��Ŀ�ļ����� ֮����ҪGxDsmccWait�ȴ�������ɡ�
 *
 * @param      obj: ���뵽��dsmcc���
 *             pid: ��Ŀ��pid ����������Ѷ����7155
 *             file_id����Ŀ¼�б���õ���file��ʶ
 *
 *
 * @return    -1:ִ��ʧ��
 *             0:ִ�гɹ�
 */
int32_t GxDsmccNeimengFilterFil(DsmccHandle dsmcc, uint32_t pid,uint16_t file_id);
/**
 * @brief      ��ȡ�ļ�������
 *
 * @param
 *
 * @return    NULL:ִ��ʧ��
 *            ����ֵΪ�ļ�����ָ��
 */
int8_t* GxDsmccNeimengGetFil(void);

__END_DECLS

#endif
/*@}*/

