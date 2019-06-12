/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SI_SUB_ENGINE_H__
#define __SI_SUB_ENGINE_H__

#include "gxcore.h"
#include "sub_system/dmx_sub_system/dmx_sub_system.h"

__BEGIN_DECLS

/*����ֵ*/
#define GX_SI_ENGINE_PARAMETER_ERR (-1)
#define GX_SI_ENGINE_ERR           (-2)
#define GX_SI_ENGINE_SUCCESS       (0)
#define SI_ENGINE_NUM              (DMX_SUB_FILTER_NUM)//���֧�ֵĹ�����������Ӳ��֧�ֵ�filter����
#define SI_READ_SIZE               (64*1024)//ÿ�ζ�ȡ��section�ֽ���

typedef int32_t SiEngineHandle;
/* Exported Types --------------------------------------------------------- */

typedef enum {
    SECTION_OK = 0,
    TABLE_OK,
	REPEAT_SECTION,//�ظ���section
    ERR_PARAMS,
}SiEngineParseStatus;


typedef enum{
    GX_SEARCH_FRONT_ATSC_T = 0,
    GX_SEARCH_FRONT_ATSC_C,
    GX_SEARCH_FRONT_DVB_S,
    GX_SEARCH_FRONT_DVB_T,
    GX_SEARCH_FRONT_DVB_C,
    GX_SEARCH_FRONT_DVB_DTMB,
    GX_SEARCH_FRONT_DVB_DVBT2,
}GxSearchFrontType;



/*�����ȡ��ԭʼsection����ʱ����Ϊ��,����1ʱ����������б�׼��section�ı����;
 * �����ֹͣ���ι��ˣ���Ҫ����GxSubSystem_SiEngineFree����GxSubSystem_SiEnginePause������0
 * �����ע�����дNULL,��ʱ��ִ��Ĭ�ϵĴ����൱�ڷ���1,�˺���ִ��ʱ�䲻�ܳ���5S��
 * status�д���˵�ǰ�ı��Ƿ������ȫ*
 * si�Ǳ��ι��˵ľ��*/
typedef int32_t (*OriginalSection)(SiEngineHandle si,uint8_t *section, uint32_t len,SiEngineParseStatus status);


/*�����ȡ�������õ�section����ʱ����Ϊ,������1ʱ����������б����;
 * �����ֹͣ���ι��ˣ���Ҫ����GxSubSystem_SiEngineFree����GxSubSystem_SiEnginePause������0
 * �����ע�����дNULL,��ʱ��ִ��Ĭ�ϵĹ��˴���,�˺���ִ��ʱ�䲻�ܳ���5S.
 * table����ǿ��ת���ɱ��ν����ı�ṹ
 * status�д���˵�ǰ�ı��Ƿ������ȫ
 * si�Ǳ��ι��˵ľ��*/
typedef int32_t (*TableSection)(SiEngineHandle si, void *table, SiEngineParseStatus status);

/*���峬ʱ����Ϊ������1ʱ����������б����;
 * �����ֹͣ���ι��ˣ���Ҫ����GxSubSystem_SiEngineFree����GxSubSystem_SiEnginePause������0
 * �����ע�����дNULL����ʱ��ִ��Ĭ�ϵĳ�ʱ�����൱�ڷ���0������ִ��ʱ�䲻�ܳ���5S
 * si�Ǳ��ι��˵ľ��*/
typedef int32_t (*TimeOut)(SiEngineHandle si);

/*�������Ƿ�������,����ִ��ʱ�䲻�ܳ���5S;
 * �����ע�����дNULL����ʱ��ִ��Ĭ�ϵļ�⡣
 * si�Ǳ��ι��˵ľ��
 * sec��ԭʼsec����*/
typedef  SiEngineParseStatus (*SecNumCheck)(SiEngineHandle si,uint8_t* sec);

typedef struct
{
	uint32_t dmx_id;
	uint32_t ts;
	GxSubsystemDmxAllocFilter filter;
	OriginalSection original;
	TableSection table;
    TimeOut time_out;
	SecNumCheck sec_num_check;
	uint32_t time_ms;
    GxSearchFrontType front_type;
    void * p;//�����洢�û����ݵ�ָ��
} GxSubsystemSiEngineAlloc;



typedef enum{
    PROTOCOL_DVB = 1,
    PROTOCOL_ATSC,
}PROTOCOL_TYPE;

typedef struct{
    uint32_t dmx_id;//Ӳ��dmx id���������ṩ��Ŀǰ�ֱ���0,1.
    PROTOCOL_TYPE protocol;//dmx�Ľ���Э�飬��Ҫ����ע���ӦЭ��Ľ�����
}GxSubsystemSiProtocol;

typedef struct
{
	uint32_t parse_thread_count;//���ڽ������߳���������0ʹ��Ĭ��������1��.������ý������������ӽ����߳�
	uint32_t parse_stack;//����ջ��С������0ʹ��Ĭ��ֵ��16*1024��
	uint32_t parse_pri;//�������ȼ�������0ʹ��Ĭ��ֵ��11��
	uint32_t read_stack;//����ջ��С������0ʹ��Ĭ��ֵ��16*1024��
	uint32_t read_pri;//���������ȼ�������0ʹ��Ĭ��ֵ��10��
    uint32_t init_dmx_num;//ע��dmx����Э����������Ҫ������dmx_protocol�����������Ӧ
    GxSubsystemSiProtocol * dmx_protocol;//ע��dmx�Ľ���Э��,ʹ��ʱ��Ҫ���Ҫʹ�ö��ٸ�dmx�����г�ʼ��
}GxSubsystemSiEngineInit;

/**
 * @brief      ��ʼ��si
 * 
 * @param      parse_thread_count 
 * 
 * @return    GX_SI_ENGINE_ERR  ʧ��
 *            GX_SI_ENGINE_SUCCESS   �ɹ�
 */
status_t GxSubSystem_SiEngineInit(GxSubsystemSiEngineInit* init);

/**
 * @brief      ����һ�ι���
 * 
 * @param      
 * 
 * @return     �ɹ����뵽��si������������-1 ������ʧ��
 */
SiEngineHandle GxSubSystem_SiEngineAlloc(GxSubsystemSiEngineAlloc* para);

/**
 * @brief      ��������
 * 
 * @param      
 * 
 * @return    GX_SI_ENGINE_PARAMETER_ERR ����Ĳ�������
 *            GX_SI_ENGINE_ERR  ʧ��
 *            GX_SI_ENGINE_SUCCESS   �ɹ�
 */
status_t  GxSubSystem_SiEngineStart(SiEngineHandle si);

/**
 * @brief      �ͷŹ���
 * 
 * @param      
 * 
 * @return    GX_SI_ENGINE_PARAMETER_ERR ����Ĳ�������
 *            GX_SI_ENGINE_ERR  ʧ��
 *            GX_SI_ENGINE_SUCCESS   �ɹ�
 */
status_t  GxSubSystem_SiEngineFree(SiEngineHandle si);

/**
 * @brief      ��ͣ���� �����ͷ�Ӳ�������ǻ�����������ݻ���
 * 
 * @param      
 * 
 * @return    GX_SI_ENGINE_PARAMETER_ERR ����Ĳ�������
 *            GX_SI_ENGINE_ERR  ʧ��
 *            GX_SI_ENGINE_SUCCESS   �ɹ�
 */
status_t  GxSubSystem_SiEnginePause(SiEngineHandle si);

/**
 * @brief      �ı���˲�����
 * 
 * @param      
 * 
 * @return    GX_SI_ENGINE_PARAMETER_ERR ����Ĳ�������
 *            GX_SI_ENGINE_ERR  ʧ��
 *            GX_SI_ENGINE_SUCCESS   �ɹ�
 */
status_t  GxSubSystem_SiEngineModify(SiEngineHandle si,GxSubsystemSiEngineAlloc* para);

/**
 * @brief      �������� �����ͷ�Ӳ��������������ݻ���
 * 
 * @param      
 * 
 * @return    GX_SI_ENGINE_PARAMETER_ERR ����Ĳ�������
 *            GX_SI_ENGINE_ERR  ʧ��
 *            GX_SI_ENGINE_SUCCESS   �ɹ�
 */
status_t  GxSubSystem_SiEngineRestart(SiEngineHandle si);
/**
 * @brief      ��ȡ�û�˽����Ϣ
 * 
 * @param      
 * 
 * @return    �û�����siʱ�����˽����Ϣָ��
 */
void* GxSubSystem_SiEngineGetUser(SiEngineHandle si);

__END_DECLS

#endif
/*@}*/

