#ifndef __GXCAS_HHH__
#define __GXCAS_HHH__
//
///< �����Ƿ�򿪲�����⹦��
#define CHECK_STRING_PARAM			(0)

#include "gxcore.h"
#include "gxcas_dbg.h"
#include "gx_jansson.h"
#include "gxcas_template.h"
#include "gxcas_func_lib.h"
#include "gx_demux.h"
#include "gx_smartcard.h"
#include "gx_descrambler.h"
#include "gxcas_template.h"

__BEGIN_DECLS

///< ����ע�ᵽCA���Ƴ���
#define GXCA_NAME_SIZE		(32)


///< ����״̬����ֵ
#ifndef E_OK
#define E_SUCESS                (0)
#endif
#ifndef E_FAILURE
#define E_FAILURE               (-1)
#endif

#ifndef E_INVALID_PARAM
#define E_INVALID_PARAM         (-2)
#endif

#ifndef E_INVALID_HANDLE
#define E_INVALID_HANDLE        (0)
#endif


///< GXCAS state
typedef enum {
	GXCAS_SUCCESS           = 0,    ///< �ɹ�
	GXCAS_ERR               = -1,   ///< ����
	GXCAS_PARAM_ERR         = -2,   ///< ��������
	GXCAS_CANT_FIND_OPS     = -3,   ///< ��Ӧ��ops������

	GXCAS_PIN_ERR           = -100, ///< �������
	GXCAS_PIN_LOCKED        = -101, ///< �������

	GXCAS_SMC_ERR           = -200, ///< ���ܿ�����
	GXCAS_SMC_INVALID_CARD  = -201, ///< ��Ч���ܿ�
	GXCAS_SMC_CARD_OUT      = -202, ///< ���ܿ�δ����
	GXCAS_SMC_VER_ERR       = -203, ///< ���ܿ��汾����

	GXCAS_ENTITLE_ERR       = -300, ///< ��Ȩ����
	GXCAS_ENTITLE_NOENTITLE = -301, ///< ��Ŀδ��Ȩ
	GXCAS_ENTITLE_OVERDUE   = -302, ///< ��Ŀ��Ȩ����
} GxCasErr_t;

///< GXCAS ���ƿ�
typedef struct CasOps_s {
	const char* name;/*ops ����,���ĵ�*/
	GxCasErr_t (*ops)(int32_t ,const char*,const char**);/*ops ����ʵ��*/
#if CHECK_STRING_PARAM
	int32_t (*input_check)(const char*); /*�����ַ�����麯��*/
	int32_t (*output_check)(const char*);/*����ַ�����麯��*/
#endif
} GxCasOps_t;

typedef struct CasEvent_s {
	const char* name;/*�¼� ����,���ĵ�*/
#if CHECK_STRING_PARAM
	int32_t (*context_check)(const char*);/*�¼����ݼ�⺯��*/
#endif
} GxCasEvents_t;

typedef struct GXCASystem_s {
	uint32_t magic;       ///< ħ������ȷ���Ƿ�Ϊ��ȷ�ľ��
	uint32_t count;       ///< ��δ����CA�ļ����������ж��Ƿ����ͷ�ȫ����Դ
	handle_t handle;      ///< ��¼��δ򿪵�ͬһ��CA�ķ��ؾ��
	handle_t lock;        ///< ���������

	/*���³�Աע��ʱ��Ҫ��ֵ */
	char *name;           ///< ע���CA����,��ʱ��˶�Ӧ
	int32_t ops_num;      ///< ע���CA Ops ����
	GxCasOps_t *ops;      ///< ע���CA ops �б�

	int32_t event_num;    ///< ע���CA �¼�����
	GxCasEvents_t *event; ///< ע���CA �¼��б�
} GxCasSystem_t;


/**
* @brief	open a ca with name.
* @param	const char * name:name of cas;
* @param        const char* pOpenParam:JSON string type param to open the CA.
*               see <������ƣ�GxCas_IOCTL���弰��������ģ��˵��.doc>
* @return	handle_t: E_INVALID_HANDLE,open failure. else the handle of ca
*/
handle_t GxCas_OpenCa(const char * name,IN const char* pOpenString);

/**
* @brief	close a ca with the handle.
* @param	handle_t handle: handle of ca.
* @return	int32_t:  >=0,success;or failure.
*/
int32_t GxCas_CloseCa(handle_t handle);

/**
* @brief	ioctl, call function of cas via ops name.
* @param	handle_t handle: handle of ca.
* @param	IN const char* input: input param string.
* @param	OUT char** output:  output param string.
*               see <������ƣ�GxCas_IOCTL���弰��������ģ��˵��.doc>
* @return	GxCasErr_t: enum of state.
*/
GxCasErr_t GxCas_Ioctl(int32_t  handle,const char* ops_name, IN const char* input,OUT const char** output);

/**
* @brief	wait event.function must be called circular
* @param	handle_t handle: handle of ca.
* @param	OUT char** event_string: out put json string that descript event.
*               see <������ƣ�GxCas_�¼����弰��������ģ��˵��.doc>
* @param	uint32_t time_out:time out.if cant get event within the time, task will be suspended.
* @return	int32_t:  >=0,success;or failure.
*/
int32_t GxCas_WaitEvent(int32_t handle,OUT const char** event_string,uint32_t time_out);

/**
* @brief	register a ca with name, ops list.
* @param	GxCasystem_t cas: name  ops list of the ca.
* @return	int32_t:  >=0,success;or failure.
*/
int32_t GxCas_RegisterCa(GxCasSystem_t* cas);

/**
* @brief	unregister a ca via ca's name.
* @param	const char * name: name of the ca.
* @return	int32_t:  >=0,success;or failure.
*/
int32_t GxCas_UnRegisterCa(const char * name);

__END_DECLS

#endif


