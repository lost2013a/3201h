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
/*返回值*/
#define GX_SI_PARSE_LIB_PARAMETER_ERR (0xffffffff)
#define GX_SI_PARSE_LIB_ERR           (0xfffffffe)
#define GX_SI_PARSE_LIB_NO_MEM        (0xfffffffd)
#define GX_SI_PARSE_LIB_SUCCESS       (0xfffffffc)

/* Exported Functions ----------------------------------------------------- */

/**
 *  @brief      把一段section数据解析成pat表的格式
 *   
 *  @param       uint8_t* section:section数据
 *                uint32_t size:section的大小
 *  
 *  @return      pat数据
 *               NULL：发生错误
 */
GxSubsystemSiParsePAT* GxSubsystm_SiParseLibPatParse(uint8_t* section,uint32_t size);

/**
 *  @brief      释放pat的空间，应用应该在通过GxSubsystm_SiParseLibPatParse获取
 *  解析好的pat数据之后某个时刻释放pat的空间。
 *   
 *  @param       void* pat:pat的存储空间，是通过GxSubsystm_SiParseLibPatParse获取的
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR：传入的参数是错误的
 *               GX_SI_PARSE_LIB_ERR：执行错误          
 *               GX_SI_PARSE_LIB_SUCCESS：执行成功
 */
int32_t  GxSubsystm_SiParseLibPatRelease(void* pat);

/**
 *  @brief      把一段section数据解析成pmt表的格式
 *   
 *  @param       uint8_t* section:section数据
 *                uint32_t size:section的大小
 *  
 *  @return      pmt数据
 *               NULL：发生错误
 */
GxSubsystemSiParsePMT* GxSubsystm_SiParseLibPmtParse(uint8_t* section,uint32_t size);

/**
 *  @brief      释放pmt的空间，应用应该在通过GxSubsystm_SiParseLibPmtParse获取
 *  解析好的pmt数据之后某个时刻释放pmt的空间。
 *   
 *  @param       void* pmt:pmt的存储空间，是通过GxSubsystm_SiParseLibPmtParse获取的
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR：传入的参数是错误的
 *               GX_SI_PARSE_LIB_ERR：执行错误          
 *               GX_SI_PARSE_LIB_SUCCESS：执行成功
 */
int32_t  GxSubsystm_SiParseLibPmtRelease(void* pmt);
/**
 *  @brief      把一段section数据解析成sdt表的格式
 *   
 *  @param       uint8_t* section:section数据
 *                uint32_t size:section的大小
 *  
 *  @return      sdt数据
 *               NULL：发生错误
 */
GxSubsystemSiParseSDT* GxSubsystm_SiParseLibSdtParse(uint8_t* section,uint32_t size);

/**
 *  @brief      释放sdt的空间，应用应该在通过GxSubsystm_SiParseLibSdtParse获取
 *  解析好的sdt数据之后某个时刻释放sdt的空间。
 *   
 *  @param       void* sdt:sdt的存储空间，是通过GxSubsystm_SiParseLibSdtParse获取的
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR：传入的参数是错误的
 *               GX_SI_PARSE_LIB_ERR：执行错误          
 *               GX_SI_PARSE_LIB_SUCCESS：执行成功
 */
int32_t  GxSubsystm_SiParseLibSdtRelease(void* sdt);
/**
 *  @brief      把一段section数据解析成tdt表的格式
 *   
 *  @param       uint8_t* section:section数据
 *                uint32_t size:section的大小
 *  
 *  @return      tdt数据
 *               NULL：发生错误
 */
GxSubsystemSiParseTDT* GxSubsystm_SiParseLibTdtParse(uint8_t* section,uint32_t size);

/**
 *  @brief      释放tdt的空间，应用应该在通过GxSubsystm_SiParseLibTdtParse获取
 *  解析好的tdt数据之后某个时刻释放tdt的空间。
 *   
 *  @param       void* tdt:tdt的存储空间，是通过GxSubsystm_SiParseLibTdtParse获取的
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR：传入的参数是错误的
 *               GX_SI_PARSE_LIB_ERR：执行错误          
 *               GX_SI_PARSE_LIB_SUCCESS：执行成功
 */
int32_t  GxSubsystm_SiParseLibTdtRelease(void* tdt);

/**
 *  @brief      把一段section数据解析成nit表的格式
 *   
 *  @param       uint8_t* section:section数据
 *                uint32_t size:section的大小
 *  
 *  @return      nit数据
 *               NULL：发生错误
 */
GxSubsystemSiParseNIT* GxSubsystm_SiParseLibTnitParse(uint8_t* section,uint32_t size);

/**
 *  @brief      释放nit的空间，应用应该在通过GxSubsystm_SiParseLibNitParse获取
 *  解析好的nit数据之后某个时刻释放nit的空间。
 *   
 *  @param       void* nit:nit的存储空间，是通过GxSubsystm_SiParseLibNitParse获取的
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR：传入的参数是错误的
 *               GX_SI_PARSE_LIB_ERR：执行错误          
 *               GX_SI_PARSE_LIB_SUCCESS：执行成功
 */
int32_t  GxSubsystm_SiParseLibTnitRelease(void* nit);

/**
 *  @brief      把一段section数据解析成nit表的格式
 *   
 *  @param       uint8_t* section:section数据
 *                uint32_t size:section的大小
 *  
 *  @return      nit数据
 *               NULL：发生错误
 */
GxSubsystemSiParseNIT* GxSubsystm_SiParseLibDtmbnitParse(uint8_t* section,uint32_t size);

/**
 *  @brief      释放nit的空间，应用应该在通过GxSubsystm_SiParseLibNitParse获取
 *  解析好的nit数据之后某个时刻释放nit的空间。
 *   
 *  @param       void* nit:nit的存储空间，是通过GxSubsystm_SiParseLibNitParse获取的
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR：传入的参数是错误的
 *               GX_SI_PARSE_LIB_ERR：执行错误          
 *               GX_SI_PARSE_LIB_SUCCESS：执行成功
 */
int32_t  GxSubsystm_SiParseLibDtmbnitRelease(void* nit);


/**
 *  @brief      把一段section数据解析成tot表的格式
 *   
 *  @param       uint8_t* section:section数据
 *                uint32_t size:section的大小
 *  
 *  @return      tot数据
 *               NULL：发生错误
 */
GxSubsystemSiParseTOT* GxSubsystm_SiParseLibTotParse(uint8_t* section,uint32_t size);

/**
 *  @brief      释放tot的空间，应用应该在通过GxSubsystm_SiParseLibTotParse获取
 *  解析好的tot数据之后某个时刻释放tot的空间。
 *   
 *  @param       void* tot:tot的存储空间，是通过GxSubsystm_SiParseLibTotParse获取的
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR：传入的参数是错误的
 *               GX_SI_PARSE_LIB_ERR：执行错误          
 *               GX_SI_PARSE_LIB_SUCCESS：执行成功
 */
int32_t  GxSubsystm_SiParseLibTotRelease(void* tot);

/**
 *  @brief      把一段section数据解析成ait表的格式
 *   
 *  @param       uint8_t* section:section数据
 *                uint32_t size:section的大小
 *  
 *  @return      ait数据
 *               NULL：发生错误
 */
GxSubsystemSiParseAIT* GxSubsystm_SiParseLibAitParse(uint8_t* section,uint32_t size);

/**
 *  @brief      释放ait的空间，应用应该在通过GxSubsystm_SiParseLibAitParse获取
 *  解析好的ait数据之后某个时刻释放ait的空间。
 *   
 *  @param       void* ait:ait的存储空间，是通过GxSubsystm_SiParseLibAitParse获取的
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR：传入的参数是错误的
 *               GX_SI_PARSE_LIB_ERR：执行错误          
 *               GX_SI_PARSE_LIB_SUCCESS：执行成功
 */
int32_t  GxSubsystm_SiParseLibAitRelease(void* ait);




/**
 *  @brief      把一段section数据解析成mgt表的格式
 *   
 *  @param       uint8_t* section:section数据
 *                uint32_t size:section的大小
 *  
 *  @return      mgt数据
 *               NULL：发生错误
 */
GxSubsystemSiParseMGT* GxSubsystm_SiParseLibMgtParse(uint8_t* section,uint32_t size);


/**
 *  @brief      释放mgt的空间，应用应该在通过GxSubsystm_SiParseLibMgtParse获取
 *  解析好的mgt数据之后某个时刻释放mgt的空间。
 *   
 *  @param       void* mgt:mgt的存储空间，是通过GxSubsystm_SiParseLibMgtParse获取的
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR：传入的参数是错误的
 *               GX_SI_PARSE_LIB_ERR：执行错误          
 *               GX_SI_PARSE_LIB_SUCCESS：执行成功
 */
int32_t  GxSubsystm_SiParseLibMgtRelease(void* mgt);



/**
 *  @brief      把一段section数据解析成 atsc eit表的格式
 *   
 *  @param       uint8_t* section:section数据
 *                uint32_t size:section的大小
 *  
 *  @return      atsc eit数据
 *               NULL：发生错误
 */
GxSubsystemSiParseAtscEIT* GxSubsystm_AtscSiParseLibEitParse(uint8_t* section,uint32_t size);


/**
 *  @brief      释放eit的空间，应用应该在通过GxSubsystm_AtscSiParseLibEitParse获取
 *  解析好的eit数据之后某个时刻释放eit的空间。
 *   
 *  @param       void* eit:eit的存储空间，是通过GxSubsystm_AtscSiParseLibEitParse获取的
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR：传入的参数是错误的
 *               GX_SI_PARSE_LIB_ERR：执行错误          
 *               GX_SI_PARSE_LIB_SUCCESS：执行成功
 */
int32_t  GxSubsystm_AtscSiParseLibEitRelease(void* eit);


/**
 *  @brief      把一段section数据解析成dvb eit表的格式
 *   
 *  @param       uint8_t* section:section数据
 *                uint32_t size:section的大小
 *  
 *  @return      dvb eit数据
 *               NULL：发生错误
 */
GxSubsystemSiParseDvbEIT* GxSubsystm_DvbSiParseLibEitParse(uint8_t* section,uint32_t size);


/**
 *  @brief      释放eit的空间，应用应该在通过GxSubsystm_DvbSiParseLibEitParse获取
 *  解析好的eit数据之后某个时刻释放eit的空间。
 *   
 *  @param       void* eit:eit的存储空间，是通过GxSubsystm_DvbSiParseLibEitParse获取的
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR：传入的参数是错误的
 *               GX_SI_PARSE_LIB_ERR：执行错误          
 *               GX_SI_PARSE_LIB_SUCCESS：执行成功
 */
int32_t  GxSubsystm_DvbSiParseLibEitRelease(void* eit);






/**
 *  @brief      把一段section数据解析成tvct表的格式
 *   
 *  @param       uint8_t* section:section数据
 *                uint32_t size:section的大小
 *  
 *  @return      tvct数据
 *               NULL：发生错误
 */
GxSubsystemSiParseVCT* GxSubsystm_SiParseLibTvctParse(uint8_t* section,uint32_t size);


/**
 *  @brief      释放tvct的空间，应用应该在通过GxSubsystm_SiParseLibTvctParse获取
 *  解析好的tvct数据之后某个时刻释放tvct的空间。
 *   
 *  @param       void* vct:vct的存储空间，是通过GxSubsystm_SiParseLibTvctParse获取的
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR：传入的参数是错误的
 *               GX_SI_PARSE_LIB_ERR：执行错误          
 *               GX_SI_PARSE_LIB_SUCCESS：执行成功
 */
int32_t  GxSubsystm_SiParseLibTvctRelease(void* vct);





/**
 *  @brief      把一段section数据解析成cvct表的格式
 *   
 *  @param       uint8_t* section:section数据
 *                uint32_t size:section的大小
 *  
 *  @return      cvct数据
 *               NULL：发生错误
 */
GxSubsystemSiParseVCT* GxSubsystm_SiParseLibCvctParse(uint8_t* section,uint32_t size);


/**
 *  @brief      释放cvct的空间，应用应该在通过GxSubsystm_SiParseLibCvctParse获取
 *  解析好的cvct数据之后某个时刻释放cvct的空间。
 *   
 *  @param       void* vct:vct的存储空间，是通过GxSubsystm_SiParseLibCvctParse获取的
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR：传入的参数是错误的
 *               GX_SI_PARSE_LIB_ERR：执行错误          
 *               GX_SI_PARSE_LIB_SUCCESS：执行成功
 */
int32_t  GxSubsystm_SiParseLibCvctRelease(void* vct);




/**
 *  @brief      把一段section数据解析成ett表的格式
 *   
 *  @param       uint8_t* section:section数据
 *                uint32_t size:section的大小
 *  
 *  @return      ett数据
 *               NULL：发生错误
 */
GxSubsystemSiParseETT* GxSubsystm_SiParseLibEttParse(uint8_t* section,uint32_t size);


/**
 *  @brief      释放ett的空间，应用应该在通过GxSubsystm_SiParseLibEttParse获取
 *  解析好的ett数据之后某个时刻释放ett的空间。
 *   
 *  @param       void* ett:ett的存储空间，是通过GxSubsystm_SiParseLibEttParse获取的
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR：传入的参数是错误的
 *               GX_SI_PARSE_LIB_ERR：执行错误          
 *               GX_SI_PARSE_LIB_SUCCESS：执行成功
 */
int32_t  GxSubsystm_SiParseLibEttRelease(void* ett);


/**
 *  @brief      把一段section数据解析成stt表的格式
 *   
 *  @param       uint8_t* section:section数据
 *                uint32_t size:section的大小
 *  
 *  @return      stt数据
 *               NULL：发生错误
 */
GxSubsystemSiParseSTT* GxSubsystm_SiParseLibSttParse(uint8_t* section,uint32_t size);


/**
 *  @brief      释放stt的空间，应用应该在通过GxSubsystm_SiParseLibSttParse获取
 *  解析好的stt数据之后某个时刻释放stt的空间。
 *   
 *  @param       void* stt:stt的存储空间，是通过GxSubsystm_SiParseLibSttParse获取的
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR：传入的参数是错误的
 *               GX_SI_PARSE_LIB_ERR：执行错误          
 *               GX_SI_PARSE_LIB_SUCCESS：执行成功
 */
int32_t  GxSubsystm_SiParseLibSttRelease(void* stt);


/**
 *  @brief      把一段section数据解析成rrt表的格式
 *   
 *  @param       uint8_t* section:section数据
 *                uint32_t size:section的大小
 *  
 *  @return      rrt数据
 *               NULL：发生错误
 */
GxSubsystemSiParseRRT* GxSubsystm_SiParseLibRrtParse(uint8_t* section,uint32_t size);


/**
 *  @brief      释放rrt的空间，应用应该在通过GxSubsystm_SiParseLibRrtParse获取
 *  解析好的rrt数据之后某个时刻释放rrt的空间。
 *   
 *  @param       void* rrt:rrt的存储空间，是通过GxSubsystm_SiParseLibRrtParse获取的
 *  
 *  @return      GX_SI_PARSE_LIB_PARAMETER_ERR：传入的参数是错误的
 *               GX_SI_PARSE_LIB_ERR：执行错误          
 *               GX_SI_PARSE_LIB_SUCCESS：执行成功
 */
int32_t  GxSubsystm_SiParseLibRrtRelease(void* rrt);




__END_DECLS

#endif
/*@}*/

