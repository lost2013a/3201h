/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SI_PARSE_LIB_H__
#define __SI_PARSE_LIB_H__

#include "gxcore.h"
#include "sub_system/si_parse_lib/si_parse_lib_table/si_parse_lib_pat.h"
#include "sub_system/si_parse_lib/si_parse_lib_table/si_parse_lib_pmt.h"
#include "sub_system/si_parse_lib/si_parse_lib_table/si_parse_lib_sdt.h"
#include "sub_system/si_parse_lib/si_parse_lib_table/si_parse_lib_tdt.h"
#include "sub_system/si_parse_lib/si_parse_lib_table/si_parse_lib_nit.h"
#include "sub_system/si_parse_lib/si_parse_lib_table/si_parse_lib_tot.h"
#include "sub_system/si_parse_lib/si_parse_lib_table/si_parse_lib_ait.h"
#include "sub_system/si_parse_lib/si_parse_lib_table/si_parse_lib_dsi.h"
#include "sub_system/si_parse_lib/si_parse_lib_table/si_parse_lib_dii.h"
#include "sub_system/si_parse_lib/si_parse_lib_table/si_parse_lib_ddb.h"
#include "sub_system/si_parse_lib/si_parse_lib_table/si_parse_lib_mgt.h"
#include "sub_system/si_parse_lib/si_parse_lib_table/si_parse_lib_atsc_eit.h"
#include "sub_system/si_parse_lib/si_parse_lib_table/si_parse_lib_dvb_eit.h"
#include "sub_system/si_parse_lib/si_parse_lib_table/si_parse_lib_vct.h"
#include "sub_system/si_parse_lib/si_parse_lib_table/si_parse_lib_ett.h"
#include "sub_system/si_parse_lib/si_parse_lib_table/si_parse_lib_stt.h"
#include "sub_system/si_parse_lib/si_parse_lib_table/si_parse_lib_rrt.h"
#include "sub_system/si_parse_lib/si_parse_lib_table/si_parse_lib_biop_dir.h"
#include "sub_system/si_parse_lib/si_parse_lib_table/si_parse_lib_biop_file.h"

__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

/* ISO 13818.1 defined TS descriptor tags */
enum {													
    SI_PARSE_LIB_APPLICATION_DES		    	= 0x00,	/* application */
    SI_PARSE_LIB_APPLICATION_NAME_DES		    = 0x01,	/* application name */
    SI_PARSE_LIB_TRANSPORT_PROTOCOL_DES	    	= 0x02,	/* transport_protocol */
    SI_PARSE_LIB_DVB_J_APPLICATION_DES		    = 0x03,	/* dvb j application */
    SI_PARSE_LIB_DVB_J_APPLICATION_LOCATION_DES	= 0x04,	/* dvb j application location */
    SI_PARSE_LIB_REGISTRATION_DES			    = 0x05,	/* registration descriptor */
    SI_PARSE_LIB_DATA_STREAM_ALIGNMENT_DES		= 0x06,	/* data stream alignment */
    SI_PARSE_LIB_TARGET_BACKGROUND_GRID_DES 	= 0x07,	/* target background grid */
    SI_PARSE_LIB_VIDEO_WINDOW_DES			    = 0x08,	/* video window descriptor */
    SI_PARSE_LIB_CA_DES					    	= 0x09,	/* CA */
    SI_PARSE_LIB_ISO639_LANGUAGE_DES		    = 0x0a,	/* ISO-639 language descriptor */
    SI_PARSE_LIB_APPLICATION_ICONS_DES			= 0x0b,	/* application icons */
    SI_PARSE_LIB_MUX_BUFFER_UTILIZATION_DES 	= 0x0c,	/* mux buffer utlization */
    SI_PARSE_LIB_COPYRIGHT_DES					= 0x0d,	/* copyright */
    SI_PARSE_LIB_MAXIMUM_BITRATE_DES			= 0x0e,	/* maximum bitrate */
    SI_PARSE_LIB_PRIVATE_DATA_INDICATOR_DES 	= 0x0f,	/* private data indicator */
    SI_PARSE_LIB_SMOOTHING_BUFFER_DES			= 0x10,	/* smoothing buffer */
    SI_PARSE_LIB_STD_DES						= 0x11,	/* STD */
    SI_PARSE_LIB_IBP_DES						= 0x12,	/* I, B, P */
};



/* DVB 100 468 defined descriptor tags */
enum 
{												   	  	/* NIT, BAT, SDT, EIT, TOT, PMT, SIT */
    SI_PARSE_LIB_NETWORK_NAME_DES					= 0x40,	/*  *								 */
    SI_PARSE_LIB_SERVICE_LIST_DES					= 0x41,	/*  *    *							 */
    SI_PARSE_LIB_STUFFING_DES						= 0x42,	/*  *    *    *    *			  *	 */
    SI_PARSE_LIB_SAT_DELIVERY_SYSTEM_DES			= 0x43,	/*  *								 */
    SI_PARSE_LIB_CAB_DELIVERY_SYSTEM_DES			= 0x44,	/*  *								 */
    SI_PARSE_LIB_VBI_TTX_DES						= 0x45,	/*                           *       */
    SI_PARSE_LIB_VBI_TTX_DATA_DES					= 0x46,	/*                           *       */
    SI_PARSE_LIB_BOUQUET_NAME_DES					= 0x47,	/*       *    *                   *  */
    SI_PARSE_LIB_SERVICE_DES						= 0x48,	/*            *                   *  */
    SI_PARSE_LIB_COUNTRY_AVAILABILITY_DES			= 0x49,	/*       *    *					  *  */
    SI_PARSE_LIB_LINKAGE_DES						= 0x4a,	/*  *    *    *    *              *  */
    SI_PARSE_LIB_NVOD_REFERENCE_DES 				= 0x4b,	/*            *                   *  */
    SI_PARSE_LIB_TIME_SHIFTED_SERVICE_DES			= 0x4c,	/*            *                   *  */
    SI_PARSE_LIB_SHORT_EVENT_DES					= 0x4d,	/*                 *              *  */
    SI_PARSE_LIB_EXTENDED_EVENT_DES	    			= 0x4e,	/*                 *              *  */
    SI_PARSE_LIB_TIME_SHIFTED_EVENT_DES	    		= 0x4f,	/*                 *              *  */
    SI_PARSE_LIB_COMPONENT_DES						= 0x50,	/*            *    *              *  */
    SI_PARSE_LIB_MOSAIC_DES					    	= 0x51,	/*            *              *       */
    SI_PARSE_LIB_STREAM_IDENTIFIER_DES				= 0x52,	/*                           *       */
    SI_PARSE_LIB_CA_IDENTIFIER_DES					= 0x53,	/*       *    *    *              *  */
    SI_PARSE_LIB_CONTENT_DES						= 0x54,	/*                 *              *  */
    SI_PARSE_LIB_PARENTAL_RATING_DES				= 0x55,	/*	               *              *  */
    SI_PARSE_LIB_TELETEXT_DES						= 0x56,	/*                           *       */
    SI_PARSE_LIB_TELEPHONE_DES						= 0x57,	/*            *    *              *  */
    SI_PARSE_LIB_LOCAL_TIME_OFFSET_DES				= 0x58,	/*                      *            */
    SI_PARSE_LIB_SUBTITLING_DES				    	= 0x59,	/*                           *    *  */
    SI_PARSE_LIB_TER_DELIVERY_SYSTEM_DES			= 0x5a,	/*  *                                */
    SI_PARSE_LIB_MULTILINGUAL_NETWORK_NAME_DES		= 0x5b,	/*  *                                */
    SI_PARSE_LIB_MULTILINGUAL_BOUQUET_NAME_DES		= 0x5c,	/*       *                           */
    SI_PARSE_LIB_MULTILINGUAL_SERVICE_NAME_DES   	= 0x5d,	/*            *                   *  */
    SI_PARSE_LIB_MULTILINGUAL_COMPONENT_DES	    	= 0x5e,	/*                 *              *  */
    SI_PARSE_LIB_PRIVATE_DATA_SPECIFIER_DES	    	= 0x5f,	/*  *    *    *    *         *    *  */
    SI_PARSE_LIB_SERVICE_MOVE_DES					= 0x60,	/*							 *		 */
    SI_PARSE_LIB_SHORT_SMOOTHING_BUFFER_DES	    	= 0x61,	/*				   *			  *  */
    SI_PARSE_LIB_FREQUENCY_LIST_DES			    	= 0x62,	/*  *							  *  */
    SI_PARSE_LIB_PARTIAL_TRANSPORT_STREAM_DES		= 0x63,	/*								  *  */
    SI_PARSE_LIB_DATA_BROADCAST_DES			    	= 0x64,	/*            *    *			  *  */
    SI_PARSE_LIB_SYSTEM_DES					        = 0x65,	/*						     *		 */
    SI_PARSE_LIB_DATA_BROADCAST_ID_DES				= 0x66,	/*                           *       */
	SI_PARSE_LIB_PDC_DES							= 0x69,
    SI_PARSE_LIB_AC3_DES                            = 0x6A,        /*                                            */
    SI_PARSE_LIB_ANCILLARY_DATA_DES                 = 0x6B,        /*                                            */
    SI_PARSE_LIB_APPLICATION_SIGNALLING_DES         = 0x6F,
    SI_PARSE_LIB_EAC3_DES                           = 0x7A,        /*                                            */
    SI_PARSE_LIB_RESERVE_END                        = 0x7F,
    SI_PARSE_LIB_USER_DEFINED_BEGIN                 = 0x80,
    
    SI_PARSE_LIB_CAPTION_SERVICE_DES                = 0x86,
    SI_PARSE_LIB_CONTENT_ADVISORY_DES               = 0x87,
    SI_PARSE_LIB_ATSC_EXTENDED_EVENT_DES            = 0xA0,
    SI_PARSE_LIB_SERVICE_LOCATION_DES               = 0xA1,
    SI_PARSE_LIB_ATSC_TIME_SHIFTED_SERVICE_DES      = 0xA2,
    SI_PARSE_LIB_REDISTRIBUTION_CONTRL_DES          = 0xAA,
    SI_PARSE_LIB_GENRE_DES                          = 0xAB,
    SI_PARSE_LIB_USER_DEFINED_END                   = 0xFE,
};
/*����ֵ*/
#define GX_SI_PARSE_LIB_PARAMETER_ERR (0xffffffff)
#define GX_SI_PARSE_LIB_ERR           (0xfffffffe)
#define GX_SI_PARSE_LIB_NO_MEM        (0xfffffffd)
#define GX_SI_PARSE_LIB_SUCCESS       (0xfffffffc)

/* Exported Functions ----------------------------------------------------- */

/**
 *  @brief      ��һ��section���ݽ�����pat��ĸ�ʽ
 *   
 *  @param       uint8_t* section:section����
 *                uint32_t size:section�Ĵ�С
 *  
 *  @return      pat����
 *               NULL����������
 */
GxSubsystemSiParsePAT* GxSubsystm_SiParseLibPatParse(uint8_t* section,uint32_t size);

/**
 *  @brief      �ͷ�pat�Ŀռ䣬Ӧ��Ӧ����ͨ��GxSubsystm_SiParseLibPatParse��ȡ
 *  �����õ�pat����֮��ĳ��ʱ���ͷ�pat�Ŀռ䡣
 *   
 *  @param       void* pat:pat�Ĵ洢�ռ䣬��ͨ��GxSubsystm_SiParseLibPatParse��ȡ��
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR������Ĳ����Ǵ����
 *               GX_SI_PARSE_LIB_ERR��ִ�д���          
 *               GX_SI_PARSE_LIB_SUCCESS��ִ�гɹ�
 */
int32_t  GxSubsystm_SiParseLibPatRelease(void* pat);

/**
 *  @brief      ��һ��section���ݽ�����pmt��ĸ�ʽ
 *   
 *  @param       uint8_t* section:section����
 *                uint32_t size:section�Ĵ�С
 *  
 *  @return      pmt����
 *               NULL����������
 */
GxSubsystemSiParsePMT* GxSubsystm_SiParseLibPmtParse(uint8_t* section,uint32_t size);

/**
 *  @brief      �ͷ�pmt�Ŀռ䣬Ӧ��Ӧ����ͨ��GxSubsystm_SiParseLibPmtParse��ȡ
 *  �����õ�pmt����֮��ĳ��ʱ���ͷ�pmt�Ŀռ䡣
 *   
 *  @param       void* pmt:pmt�Ĵ洢�ռ䣬��ͨ��GxSubsystm_SiParseLibPmtParse��ȡ��
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR������Ĳ����Ǵ����
 *               GX_SI_PARSE_LIB_ERR��ִ�д���          
 *               GX_SI_PARSE_LIB_SUCCESS��ִ�гɹ�
 */
int32_t  GxSubsystm_SiParseLibPmtRelease(void* pmt);
/**
 *  @brief      ��һ��section���ݽ�����sdt��ĸ�ʽ
 *   
 *  @param       uint8_t* section:section����
 *                uint32_t size:section�Ĵ�С
 *  
 *  @return      sdt����
 *               NULL����������
 */
GxSubsystemSiParseSDT* GxSubsystm_SiParseLibSdtParse(uint8_t* section,uint32_t size);

/**
 *  @brief      �ͷ�sdt�Ŀռ䣬Ӧ��Ӧ����ͨ��GxSubsystm_SiParseLibSdtParse��ȡ
 *  �����õ�sdt����֮��ĳ��ʱ���ͷ�sdt�Ŀռ䡣
 *   
 *  @param       void* sdt:sdt�Ĵ洢�ռ䣬��ͨ��GxSubsystm_SiParseLibSdtParse��ȡ��
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR������Ĳ����Ǵ����
 *               GX_SI_PARSE_LIB_ERR��ִ�д���          
 *               GX_SI_PARSE_LIB_SUCCESS��ִ�гɹ�
 */
int32_t  GxSubsystm_SiParseLibSdtRelease(void* sdt);
/**
 *  @brief      ��һ��section���ݽ�����tdt��ĸ�ʽ
 *   
 *  @param       uint8_t* section:section����
 *                uint32_t size:section�Ĵ�С
 *  
 *  @return      tdt����
 *               NULL����������
 */
GxSubsystemSiParseTDT* GxSubsystm_SiParseLibTdtParse(uint8_t* section,uint32_t size);

/**
 *  @brief      �ͷ�tdt�Ŀռ䣬Ӧ��Ӧ����ͨ��GxSubsystm_SiParseLibTdtParse��ȡ
 *  �����õ�tdt����֮��ĳ��ʱ���ͷ�tdt�Ŀռ䡣
 *   
 *  @param       void* tdt:tdt�Ĵ洢�ռ䣬��ͨ��GxSubsystm_SiParseLibTdtParse��ȡ��
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR������Ĳ����Ǵ����
 *               GX_SI_PARSE_LIB_ERR��ִ�д���          
 *               GX_SI_PARSE_LIB_SUCCESS��ִ�гɹ�
 */
int32_t  GxSubsystm_SiParseLibTdtRelease(void* tdt);

/**
 *  @brief      ��һ��section���ݽ�����nit��ĸ�ʽ
 *   
 *  @param       uint8_t* section:section����
 *                uint32_t size:section�Ĵ�С
 *  
 *  @return      nit����
 *               NULL����������
 */
GxSubsystemSiParseNIT* GxSubsystm_SiParseLibTnitParse(uint8_t* section,uint32_t size);

/**
 *  @brief      �ͷ�nit�Ŀռ䣬Ӧ��Ӧ����ͨ��GxSubsystm_SiParseLibNitParse��ȡ
 *  �����õ�nit����֮��ĳ��ʱ���ͷ�nit�Ŀռ䡣
 *   
 *  @param       void* nit:nit�Ĵ洢�ռ䣬��ͨ��GxSubsystm_SiParseLibNitParse��ȡ��
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR������Ĳ����Ǵ����
 *               GX_SI_PARSE_LIB_ERR��ִ�д���          
 *               GX_SI_PARSE_LIB_SUCCESS��ִ�гɹ�
 */
int32_t  GxSubsystm_SiParseLibTnitRelease(void* nit);

/**
 *  @brief      ��һ��section���ݽ�����nit��ĸ�ʽ
 *   
 *  @param       uint8_t* section:section����
 *                uint32_t size:section�Ĵ�С
 *  
 *  @return      nit����
 *               NULL����������
 */
GxSubsystemSiParseNIT* GxSubsystm_SiParseLibDtmbnitParse(uint8_t* section,uint32_t size);

/**
 *  @brief      �ͷ�nit�Ŀռ䣬Ӧ��Ӧ����ͨ��GxSubsystm_SiParseLibNitParse��ȡ
 *  �����õ�nit����֮��ĳ��ʱ���ͷ�nit�Ŀռ䡣
 *   
 *  @param       void* nit:nit�Ĵ洢�ռ䣬��ͨ��GxSubsystm_SiParseLibNitParse��ȡ��
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR������Ĳ����Ǵ����
 *               GX_SI_PARSE_LIB_ERR��ִ�д���          
 *               GX_SI_PARSE_LIB_SUCCESS��ִ�гɹ�
 */
int32_t  GxSubsystm_SiParseLibDtmbnitRelease(void* nit);


/**
 *  @brief      ��һ��section���ݽ�����tot��ĸ�ʽ
 *   
 *  @param       uint8_t* section:section����
 *                uint32_t size:section�Ĵ�С
 *  
 *  @return      tot����
 *               NULL����������
 */
GxSubsystemSiParseTOT* GxSubsystm_SiParseLibTotParse(uint8_t* section,uint32_t size);

/**
 *  @brief      �ͷ�tot�Ŀռ䣬Ӧ��Ӧ����ͨ��GxSubsystm_SiParseLibTotParse��ȡ
 *  �����õ�tot����֮��ĳ��ʱ���ͷ�tot�Ŀռ䡣
 *   
 *  @param       void* tot:tot�Ĵ洢�ռ䣬��ͨ��GxSubsystm_SiParseLibTotParse��ȡ��
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR������Ĳ����Ǵ����
 *               GX_SI_PARSE_LIB_ERR��ִ�д���          
 *               GX_SI_PARSE_LIB_SUCCESS��ִ�гɹ�
 */
int32_t  GxSubsystm_SiParseLibTotRelease(void* tot);

/**
 *  @brief      ��һ��section���ݽ�����ait��ĸ�ʽ
 *   
 *  @param       uint8_t* section:section����
 *                uint32_t size:section�Ĵ�С
 *  
 *  @return      ait����
 *               NULL����������
 */
GxSubsystemSiParseAIT* GxSubsystm_SiParseLibAitParse(uint8_t* section,uint32_t size);

/**
 *  @brief      �ͷ�ait�Ŀռ䣬Ӧ��Ӧ����ͨ��GxSubsystm_SiParseLibAitParse��ȡ
 *  �����õ�ait����֮��ĳ��ʱ���ͷ�ait�Ŀռ䡣
 *   
 *  @param       void* ait:ait�Ĵ洢�ռ䣬��ͨ��GxSubsystm_SiParseLibAitParse��ȡ��
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR������Ĳ����Ǵ����
 *               GX_SI_PARSE_LIB_ERR��ִ�д���          
 *               GX_SI_PARSE_LIB_SUCCESS��ִ�гɹ�
 */
int32_t  GxSubsystm_SiParseLibAitRelease(void* ait);




/**
 *  @brief      ��һ��section���ݽ�����mgt��ĸ�ʽ
 *   
 *  @param       uint8_t* section:section����
 *                uint32_t size:section�Ĵ�С
 *  
 *  @return      mgt����
 *               NULL����������
 */
GxSubsystemSiParseMGT* GxSubsystm_SiParseLibMgtParse(uint8_t* section,uint32_t size);


/**
 *  @brief      �ͷ�mgt�Ŀռ䣬Ӧ��Ӧ����ͨ��GxSubsystm_SiParseLibMgtParse��ȡ
 *  �����õ�mgt����֮��ĳ��ʱ���ͷ�mgt�Ŀռ䡣
 *   
 *  @param       void* mgt:mgt�Ĵ洢�ռ䣬��ͨ��GxSubsystm_SiParseLibMgtParse��ȡ��
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR������Ĳ����Ǵ����
 *               GX_SI_PARSE_LIB_ERR��ִ�д���          
 *               GX_SI_PARSE_LIB_SUCCESS��ִ�гɹ�
 */
int32_t  GxSubsystm_SiParseLibMgtRelease(void* mgt);



/**
 *  @brief      ��һ��section���ݽ����� atsc eit��ĸ�ʽ
 *   
 *  @param       uint8_t* section:section����
 *                uint32_t size:section�Ĵ�С
 *  
 *  @return      atsc eit����
 *               NULL����������
 */
GxSubsystemSiParseAtscEIT* GxSubsystm_AtscSiParseLibEitParse(uint8_t* section,uint32_t size);


/**
 *  @brief      �ͷ�eit�Ŀռ䣬Ӧ��Ӧ����ͨ��GxSubsystm_AtscSiParseLibEitParse��ȡ
 *  �����õ�eit����֮��ĳ��ʱ���ͷ�eit�Ŀռ䡣
 *   
 *  @param       void* eit:eit�Ĵ洢�ռ䣬��ͨ��GxSubsystm_AtscSiParseLibEitParse��ȡ��
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR������Ĳ����Ǵ����
 *               GX_SI_PARSE_LIB_ERR��ִ�д���          
 *               GX_SI_PARSE_LIB_SUCCESS��ִ�гɹ�
 */
int32_t  GxSubsystm_AtscSiParseLibEitRelease(void* eit);


/**
 *  @brief      ��һ��section���ݽ�����dvb eit��ĸ�ʽ
 *   
 *  @param       uint8_t* section:section����
 *                uint32_t size:section�Ĵ�С
 *  
 *  @return      dvb eit����
 *               NULL����������
 */
GxSubsystemSiParseDvbEIT* GxSubsystm_DvbSiParseLibEitParse(uint8_t* section,uint32_t size);


/**
 *  @brief      �ͷ�eit�Ŀռ䣬Ӧ��Ӧ����ͨ��GxSubsystm_DvbSiParseLibEitParse��ȡ
 *  �����õ�eit����֮��ĳ��ʱ���ͷ�eit�Ŀռ䡣
 *   
 *  @param       void* eit:eit�Ĵ洢�ռ䣬��ͨ��GxSubsystm_DvbSiParseLibEitParse��ȡ��
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR������Ĳ����Ǵ����
 *               GX_SI_PARSE_LIB_ERR��ִ�д���          
 *               GX_SI_PARSE_LIB_SUCCESS��ִ�гɹ�
 */
int32_t  GxSubsystm_DvbSiParseLibEitRelease(void* eit);






/**
 *  @brief      ��һ��section���ݽ�����tvct��ĸ�ʽ
 *   
 *  @param       uint8_t* section:section����
 *                uint32_t size:section�Ĵ�С
 *  
 *  @return      tvct����
 *               NULL����������
 */
GxSubsystemSiParseVCT* GxSubsystm_SiParseLibTvctParse(uint8_t* section,uint32_t size);


/**
 *  @brief      �ͷ�tvct�Ŀռ䣬Ӧ��Ӧ����ͨ��GxSubsystm_SiParseLibTvctParse��ȡ
 *  �����õ�tvct����֮��ĳ��ʱ���ͷ�tvct�Ŀռ䡣
 *   
 *  @param       void* vct:vct�Ĵ洢�ռ䣬��ͨ��GxSubsystm_SiParseLibTvctParse��ȡ��
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR������Ĳ����Ǵ����
 *               GX_SI_PARSE_LIB_ERR��ִ�д���          
 *               GX_SI_PARSE_LIB_SUCCESS��ִ�гɹ�
 */
int32_t  GxSubsystm_SiParseLibTvctRelease(void* vct);





/**
 *  @brief      ��һ��section���ݽ�����cvct��ĸ�ʽ
 *   
 *  @param       uint8_t* section:section����
 *                uint32_t size:section�Ĵ�С
 *  
 *  @return      cvct����
 *               NULL����������
 */
GxSubsystemSiParseVCT* GxSubsystm_SiParseLibCvctParse(uint8_t* section,uint32_t size);


/**
 *  @brief      �ͷ�cvct�Ŀռ䣬Ӧ��Ӧ����ͨ��GxSubsystm_SiParseLibCvctParse��ȡ
 *  �����õ�cvct����֮��ĳ��ʱ���ͷ�cvct�Ŀռ䡣
 *   
 *  @param       void* vct:vct�Ĵ洢�ռ䣬��ͨ��GxSubsystm_SiParseLibCvctParse��ȡ��
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR������Ĳ����Ǵ����
 *               GX_SI_PARSE_LIB_ERR��ִ�д���          
 *               GX_SI_PARSE_LIB_SUCCESS��ִ�гɹ�
 */
int32_t  GxSubsystm_SiParseLibCvctRelease(void* vct);




/**
 *  @brief      ��һ��section���ݽ�����ett��ĸ�ʽ
 *   
 *  @param       uint8_t* section:section����
 *                uint32_t size:section�Ĵ�С
 *  
 *  @return      ett����
 *               NULL����������
 */
GxSubsystemSiParseETT* GxSubsystm_SiParseLibEttParse(uint8_t* section,uint32_t size);


/**
 *  @brief      �ͷ�ett�Ŀռ䣬Ӧ��Ӧ����ͨ��GxSubsystm_SiParseLibEttParse��ȡ
 *  �����õ�ett����֮��ĳ��ʱ���ͷ�ett�Ŀռ䡣
 *   
 *  @param       void* ett:ett�Ĵ洢�ռ䣬��ͨ��GxSubsystm_SiParseLibEttParse��ȡ��
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR������Ĳ����Ǵ����
 *               GX_SI_PARSE_LIB_ERR��ִ�д���          
 *               GX_SI_PARSE_LIB_SUCCESS��ִ�гɹ�
 */
int32_t  GxSubsystm_SiParseLibEttRelease(void* ett);


/**
 *  @brief      ��һ��section���ݽ�����stt��ĸ�ʽ
 *   
 *  @param       uint8_t* section:section����
 *                uint32_t size:section�Ĵ�С
 *  
 *  @return      stt����
 *               NULL����������
 */
GxSubsystemSiParseSTT* GxSubsystm_SiParseLibSttParse(uint8_t* section,uint32_t size);


/**
 *  @brief      �ͷ�stt�Ŀռ䣬Ӧ��Ӧ����ͨ��GxSubsystm_SiParseLibSttParse��ȡ
 *  �����õ�stt����֮��ĳ��ʱ���ͷ�stt�Ŀռ䡣
 *   
 *  @param       void* stt:stt�Ĵ洢�ռ䣬��ͨ��GxSubsystm_SiParseLibSttParse��ȡ��
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR������Ĳ����Ǵ����
 *               GX_SI_PARSE_LIB_ERR��ִ�д���          
 *               GX_SI_PARSE_LIB_SUCCESS��ִ�гɹ�
 */
int32_t  GxSubsystm_SiParseLibSttRelease(void* stt);


/**
 *  @brief      ��һ��section���ݽ�����rrt��ĸ�ʽ
 *   
 *  @param       uint8_t* section:section����
 *                uint32_t size:section�Ĵ�С
 *  
 *  @return      rrt����
 *               NULL����������
 */
GxSubsystemSiParseRRT* GxSubsystm_SiParseLibRrtParse(uint8_t* section,uint32_t size);


/**
 *  @brief      �ͷ�rrt�Ŀռ䣬Ӧ��Ӧ����ͨ��GxSubsystm_SiParseLibRrtParse��ȡ
 *  �����õ�rrt����֮��ĳ��ʱ���ͷ�rrt�Ŀռ䡣
 *   
 *  @param       void* rrt:rrt�Ĵ洢�ռ䣬��ͨ��GxSubsystm_SiParseLibRrtParse��ȡ��
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR������Ĳ����Ǵ����
 *               GX_SI_PARSE_LIB_ERR��ִ�д���          
 *               GX_SI_PARSE_LIB_SUCCESS��ִ�гɹ�
 */
int32_t  GxSubsystm_SiParseLibRrtRelease(void* rrt);




__END_DECLS

#endif
/*@}*/

