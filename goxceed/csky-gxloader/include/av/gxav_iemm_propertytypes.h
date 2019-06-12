#ifndef __GXAV_IEMM_PROPERTYTYPES_H__
#define __GXAV_IEMM_PROPERTYTYPES_H__

typedef struct {
	unsigned int m_Iemm_CAData;
	unsigned int m_Iemm_CAMask;
} GxIemmProperty_CABytes_t;

typedef struct {
#define	IEMM_PID_DISABLE   (0)
#define	IEMM_PID_ENABLE    (1)
	unsigned char  m_pid_en;

#define	IEMM_TABLE_ID_FILTER_DISABLE (0)
#define	IEMM_TABLE_ID_FILTER_ENABLE  (1)
	unsigned char  m_table_id_en;
	unsigned int   m_emm_pid;

#define IEMM_TABLE_ID_FILTER_REJECT          (0)
#define IEMM_TABLE_ID_FILTER_WITHOUT_CA_ADDR (1)
#define IEMM_TABLE_ID_FILTER_WITH_CA_ADDR    (2)
#define IEMM_TABLE_ID_FILTER_RESERVE         (3)
	unsigned char            m_table_id_filter_mode[16];
	GxIemmProperty_CABytes_t m_CABytes[8];
	unsigned char            m_CACtrlID[8];
} GxIemmProperty_Request ;

typedef struct {
	unsigned int  m_reserver;
} GxIemmProperty_Stop ;

typedef struct {
	unsigned int  m_run_en;
	unsigned int  m_delay_time;
} GxIemmProperty_Run;

typedef struct {
	unsigned char   m_only_get_overflow_interrupt;
	unsigned char   m_overflow_interrupt;
	unsigned char   m_arriver_interrupt;
	unsigned char   m_hardware_software_interrupt;
	unsigned char  *m_p_data;
} GxIemmProperty_InterruptEvent;

typedef struct {
	unsigned int   m_input_buf_list ;    //<= 10 ;
	unsigned int   m_output_buf_list;   //<= m_input_buf_list
	 #define IEMM_MAX_READ_BUF_LIST (10)
	unsigned char   *m_p_data[IEMM_MAX_READ_BUF_LIST];
} GxIemmProperty_ReadDataBuff;

typedef struct {
	unsigned int   m_output_buf_list;
} GxIemmProperty_ReadDataList;

typedef struct{
	unsigned int  m_flag;
	unsigned int  m_read_index;
} GxIemmProperty_UpdateReadIndex;

#endif

