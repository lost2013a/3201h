/** @addtogroup si_module*/
/*@{*/
/* Define to prevent recursive inclusion */
#ifndef __SI_PUBLIC_H__
#define __SI_PUBLIC_H__

/* Includes --------------------------------------------------------------- */
#include <stdio.h>
#include <stdint.h>
#include <ctype.h>
#include "gxcore.h"

__BEGIN_DECLS

/* Exported Constants ----------------------------------------------------- */

/* Error Constants -----------------------------------------------------------*/
#define GxSiDes_Trace(...) //printf("%s",__FUNCTION__)
/* Exported Types --------------------------------------------------------- */
/**
 *   si common info
 */
typedef struct si_sinfo {
	uint16_t  ts_id;                        ///< transport stream id(16)
	uint16_t  reserved1;

	uint8_t   current_next_indicator : 1;   ///< current next indicator(1)
	uint8_t   ver_number  : 5;              ///< version number(5)
	uint8_t   reserved    : 2;              ///< reserved
	uint8_t   sec_number;                   ///< section number(8)
	uint8_t   last_sec_number;              ///< last section number(8)
	uint8_t   segment_last_sec_number;      ///< only for eit
}si_info_t;
// si common info end -----------------------------------------------

// TODO: MOSAIC_____________________________
/**
 *   mosaic descriptor
 */
/* cell info type when cell_linkage_info is 0x02 or 0x03 */
typedef struct cell_linkage23_info {
	uint16_t ori_net_id; /* original network id(16) */
	uint16_t ts_id;      /* transport stream id(16) */
	uint16_t service_id; /* service id(16) */
	uint16_t reserved1;
}cell_linkage23_info_t;

/* cell info type when cell_linkage_info is 0x04 */
typedef struct cell_linkage4_info {
	uint16_t ori_net_id; /* original network id(16) */
	uint16_t ts_id;      /* transport stream id(16) */
	uint16_t service_id; /* service id(16) */
	uint16_t event_id;   /* event id(16) */
}cell_linkage4_info_t;


/* cell info type when cell_linkage_info is 0x01 */
typedef struct cell_linkage1_info {
	uint16_t bouquet_id;		/* bouquet id(16) */
	uint16_t  reserved1;
}cell_linkage1_info_t;

/* mosaic cell information storage structure  */
typedef struct mosa_cell_info {
	uint8_t logi_cell_id;                      /* logical cell id(6) */
	uint8_t logi_cell_pres_info:4;             /* logical cell presentation info(3) */
	uint8_t mosa_cell_linkage_info:4;          /* cell linkage info(4) */
	uint8_t max_elem_cell_id;                  /* max elementary cell id(8) */
	uint8_t min_elem_cell_id;                  /* max elementary cell id(8) */
	union {
		cell_linkage1_info_t  cell_linkage1_info;
		cell_linkage23_info_t cell_linkage23_info;
		cell_linkage4_info_t  cell_linkage4_info;
	};                                         /* cell info type */
}mosa_cell_info_t;

/* mosaic information storage structure  */
typedef struct mosaic_info {
	uint8_t  nr_ver_elm_cells   : 3;  /* number vertical elementary cells(3) */
	uint8_t  reserved           : 1;  /* reserved for future use(1) */
	uint8_t  nr_hor_elm_cells   : 3;  /* number horizontal elementary cells(3) */
	uint8_t  mosaci_entry_point : 1;  /* mosaci entry point (1)*/
	uint8_t  cell_count;              /* cell count(8)*/
	uint16_t res;                     /* reserved  */
	mosa_cell_info_t *mosa_cell_info; /* mosaic cell info  */
}mosaic_info_t;
// mosaic descriptor end ----------------------------------------------------


// TODO: SERVICE_INFO________________________
/* service list descriptor information */
typedef struct service_list_info {
	uint16_t service_id;     /* sever_id(16) service list descriptor */
	uint8_t  service_type;   /* sever_type (8) service list descriptor */
	uint8_t  reserved;
}service_list_info_t;

/* service descriptor information storage structure */
typedef struct service_des_info {
	uint8_t *service_provider_name;      /* service_provider_name service descriptor */
	uint8_t *service_name;               /* service_name service descriptor */
	uint8_t service_type;                /* service_type (8) service descriptor */
	uint8_t service_provider_name_length;/* service_provider_name_length (8) service descriptor */
	uint8_t service_name_length;         /* service_name_length (8) service descriptor */
	uint8_t reserved;
} service_des_info_t;

/* nvod reference information storage structure */
typedef struct nvod_ref_info {
	uint16_t  transport_stream_id;   /* transport_stream_id Nvod reference descriptor */
	uint16_t  original_network_id;	 /* original_network_id Nvod reference descriptor */
	uint16_t  timeshift_service_id;  /* timeshift_service_id Nvod reference descriptor */
	uint16_t  res;                   /* timeshift_service_id Nvod reference descriptor */
}nvod_ref_info_t;

/* nvod reference descriptor information storage structure */
typedef struct NVOD_reference_des_info {
	nvod_ref_info_t	*nvod_des_info;     /* nvod reference information storage structure */
	uint8_t         service_number;	    /* service_number (8) Nvod reference descriptor */
} NVOD_ref_des_info_t;

/* bouquet name descriptor information storage structure */
typedef struct bouquet_info {
	uint32_t  bouquet_name_length;  /* bouquet_name length */
	uint8_t   *bouquet_name;        /* bouquet_name */
}bouquet_info_t;

/* service information storage structure */
typedef struct service_info {
	service_des_info_t *service_des_info;    /* service descriptor information storage structureonly once exist */
	//	NVOD_ref_des_info_t *nvod_ref_info;   /* nvod reference descriptor information storage structure */
	bouquet_info_t *bouquet_info;            /* bouquet name descriptor information storage structure */
	mosaic_info_t *mosaic_info;              /* mosaic information only once exist */

	uint16_t orig_network_id;                /* original_network_id(16) put in loop2 */
	uint16_t ts_id;

	uint16_t service_id;                     /* service_id(16) */

	uint8_t EIT_sch_flag:1;                  /* eit schedule flag(1)  */
	uint8_t EIT_pf_flag:1;                   /* eit present following flag(1) */
	uint8_t running_status:3;                /* running status (3) */
	uint8_t free_ca_mode:1;                  /* free_CA_mode(1) */
	uint8_t reserved:1;
	uint8_t mosaic_des_count : 1;            /* mosaic descriptor count */
	//	uint8_t time_shifted_service_count:1; /* time shifted service descriptor count(1) */
	//	uint8_t nvod_ref_nr;                  /* nvod reference number */

	//	uint8_t nvod_ref_des_count;           /* nvod reference descriptor number */
	uint8_t bouquet_des_count;               /* bouquet descriptor count */

	uint32_t service_des_count;              /* service descriptor count(1) 实际发现有非标准流>1 */

	//	int8_t	   channel_vol;

}service_info_t;
// service descriptor end ----------------------------------------------------

typedef struct {
	uint16_t    ca_system_id;
	uint16_t    ca_pid;
	uint16_t    elem_pid;
	uint16_t    private_data_len;
	uint8_t    *private_data;
}CaDescriptor;


/* ISO 13818.1 defined TS descriptor tags */
enum {
	SI_VIDEO_STREAM_DESCRIPTOR           = 0x02,	/* Video stream */
	SI_AUDIO_STREAM_DESCRIPTOR           = 0x03,	/* Audio stream */
	SI_HIERARCHY_DESCRIPTOR              = 0x04,	/* Hierarchy information */
	SI_REGISTRATION_DESCRIPTOR           = 0x05,	/* registration descriptor */
	SI_DATA_STREAM_ALIGNMENT_DESCRIPTOR  = 0x06,	/* data stream alignment */
	SI_TARGET_BACKGROUND_GRID_DESCRIPTOR = 0x07,	/* target background grid */
	SI_VIDEO_WINDOW_DESCRIPTOR           = 0x08,	/* video window descriptor */
	SI_CA_DESCRIPTOR                     = 0x09,	/* CA */
	SI_ISO639_LANGUAGE_DESCRIPTOR        = 0x0a,	/* ISO-639 language descriptor */
	SI_SYSTEM_CLOCK_DESCRIPTOR           = 0x0b,	/* system clock */
	SI_MUX_BUFFER_UTILIZATION_DESCRIPTOR = 0x0c,	/* mux buffer utlization */
	SI_COPYRIGHT_DESCRIPTOR              = 0x0d,	/* copyright */
	SI_MAXIMUM_BITRATE_DESCRIPTOR        = 0x0e,	/* maximum bitrate */
	SI_PRIVATE_DATA_INDICATOR_DESCRIPTOR = 0x0f,	/* private data indicator */
	SI_SMOOTHING_BUFFER_DESCRIPTOR       = 0x10,	/* smoothing buffer */
	SI_STD_DESCRIPTOR                    = 0x11,	/* STD */
	SI_IBP_DESCRIPTOR                    = 0x12,	/* I, B, P */
};



/* DVB 100 468 defined descriptor tags */
enum {                                                   /* NIT, BAT, SDT, EIT, TOT, PMT, SIT */
	SI_NETWORK_NAME_DESCRIPTOR              = 0x40,	/*  *                                 */
	SI_SERVICE_LIST_DESCRIPTOR              = 0x41,	/*  *    *                            */
	SI_STUFFING_DESCRIPTOR                  = 0x42,	/*  *    *    *    *			  *	 */
	SI_SAT_DELIVERY_SYSTEM_DESCRIPTOR       = 0x43,	/*  *								 */
	SI_CAB_DELIVERY_SYSTEM_DESCRIPTOR       = 0x44,	/*  *								 */
	SI_RESERVED1_DESCRIPTOR                 = 0x45,	/*                           *       */
	SI_RESERVED2_DESCRIPTOR                 = 0x46,	/*                           *       */
	SI_BOUQUET_NAME_DESCRIPTOR              = 0x47,	/*       *    *                   *  */
	SI_SERVICE_DESCRIPTOR                   = 0x48,	/*            *                   *  */
	SI_COUNTRY_AVAILABILITY_DESCRIPTOR      = 0x49,	/*       *    *					  *  */
	SI_LINKAGE_DESCRIPTOR                   = 0x4a,	/*  *    *    *    *              *  */
	SI_NVOD_REFERENCE_DESCRIPTOR            = 0x4b,	/*            *                   *  */
	SI_TIME_SHIFTED_SERVICE_DESCRIPTOR      = 0x4c,	/*            *                   *  */
	SI_SHORT_EVENT_DESCRIPTOR               = 0x4d,	/*                 *              *  */
	SI_EXTENDED_EVENT_DESCRIPTOR            = 0x4e,	/*                 *              *  */
	SI_TIME_SHIFTED_EVENT_DESCRIPTOR        = 0x4f,	/*                 *              *  */
	SI_COMPONENT_DESCRIPTOR                 = 0x50,	/*            *    *              *  */
	SI_MOSAIC_DESCRIPTOR                    = 0x51,	/*            *              *       */
	SI_STREAM_IDENTIFIER_DESCRIPTOR         = 0x52,	/*                           *       */
	SI_CA_IDENTIFIER_DESCRIPTOR             = 0x53,	/*       *    *    *              *  */
	SI_CONTENT_DESCRIPTOR                   = 0x54,	/*                 *              *  */
	SI_PARENTAL_RATING_DESCRIPTOR           = 0x55,	/*		       *              *  */
	SI_TELETEXT_DESCRIPTOR                  = 0x56,	/*                           *       */
	SI_TELEPHONE_DESCRIPTOR                 = 0x57,	/*            *    *              *  */
	SI_LOCAL_TIME_OFFSET_DESCRIPTOR         = 0x58,	/*                      *            */
	SI_SUBTITLING_DESCRIPTOR                = 0x59,	/*                           *    *  */
	SI_TER_DELIVERY_SYSTEM_DESCRIPTOR       = 0x5a,	/*  *                                */
	SI_MULTILINGUAL_NETWORK_NAME_DESCRIPTOR = 0x5b,	/*  *                                */
	SI_MULTILINGUAL_BOUQUET_NAME_DESCRIPTOR = 0x5c,	/*       *                           */
	SI_MULTILINGUAL_SERVICE_NAME_DESCRIPTOR = 0x5d,	/*            *                   *  */
	SI_MULTILINGUAL_COMPONENT_DESCRIPTOR    = 0x5e,	/*                 *              *  */
	SI_PRIVATE_DATA_SPECIFIER_DESCRIPTOR    = 0x5f,	/*  *    *    *    *         *    *  */
	SI_SERVICE_MOVE_DESCRIPTOR              = 0x60,	/*							 *		 */
	SI_SHORT_SMOOTHING_BUFFER_DESCRIPTOR    = 0x61,	/*				   *			  *  */
	SI_FREQUENCY_LIST_DESCRIPTOR            = 0x62,	/*  *							  *  */
	SI_PARTIAL_TRANSPORT_STREAM_DESCRIPTOR  = 0x63,	/*								  *  */
	SI_DATA_BROADCAST_DESCRIPTOR            = 0x64,	/*            *    *			  *  */
	SI_SYSTEM_DESCRIPTOR                    = 0x65,	/*						     *		 */
	SI_DATA_BROADCAST_ID_DESCRIPTOR         = 0x66,	/*                           *       */
	SI_AC3_DESCRIPTOR                       = 0x6A, /*                                   */
	SI_EAC3_DESCRIPTOR                      = 0x7A, /*                                   */
	SI_RESERVE_BEGIN                        = 0x6F,
	SI_RESERVE_END                          = 0x7F,
	SI_USER_DEFINED_BEGIN                   = 0x80,
	SI_USER_DEFINED_END                     = 0xFE,
};
/* Exported Variables ----------------------------------------------------- */

/* Exported Macros -------------------------------------------------------- */
#define ADDITIONAL_SIZE			(2048)
#define	SI_PMT_BUF_SIZE			(1024+ADDITIONAL_SIZE)
#define	SI_PAT_BUF_SIZE			(1024+ADDITIONAL_SIZE)
#define	SI_SDT_BUF_SIZE			(1024+ADDITIONAL_SIZE)
#define	SI_EIT_BUF_SIZE			(4*1024+ADDITIONAL_SIZE*6)
#define	SI_NIT_BUF_SIZE			(1024+ADDITIONAL_SIZE)
#define	SI_CAT_BUF_SIZE			(1024+ADDITIONAL_SIZE)
#define	SI_BAT_BUF_SIZE			(1024+ADDITIONAL_SIZE)
#define	SI_TOT_BUF_SIZE			(512)
#define	SI_DES_BUF_SIZE			(256)

/*==================== Fixed PID Definition ======================*/
#define NIT_PID                         (0x0010)   /* Network Information Table */
#define PAT_PID                         (0x00)
#define SDT_PID                         (0x11)
#define BAT_PID                         (0x11)
#define EIT_PID                         (0x12)
#define TDT_PID                         (0x14)
#define TOT_PID                         (0x14)
#define CAT_PID                         (0x01)

/*================== Fixed Table ID Definition =====================*/

#define	PAT_TID                    0x00 /* Program Association Table */
#define	CAT_TID                    0x01 /* Conditional Access Table */
#define	PMT_TID                    0x02 /* Program Map Table */
                                        /* 0x04 to 0x3F are reserved*/
#define	NIT_ACTUAL_NETWORK_TID     0x40 /* Network Information Table - Actual Network*/
#define	NIT_OTHER_NETWORK_TID      0x41 /* Network Information Table - Other Network*/
#define	SDT_ACTUAL_TS_TID          0x42 /* Service Description Table - Actual Transport Stream*/
                                        /* 0x43 to 0x45 are reserved for future use*/
#define	SDT_OTHER_TS_TID           0x46 /* Service Description Table - Other Transport Stream*/
                                        /* 0x47 to 0x49 are reserved for future use*/
#define	BAT_TID                    0x4A /* Bouquet Association Table */
#define	EIT_ACTUAL_PF_TID          0x4E
#define	EIT_OTHER_PF_TID           0x4F
                                        /* 0x50 to 0x6F are used for Various EIT Table*/
#define	TDT_TID                    0x70 /* Time & Date Table */
#define	RST_TID                    0x71 /* Running Status Table */
#define	TOT_TID                    0x73 /* Time Offset Table */

// get data from section
#define TODATALO3(data)                     (data & 0x07)
#define TODATAHI3(data)                     ((data >> 5 ) & 0x07)
#define TODATAHI4(data)                     ((data >> 4) & 0x0f)
#define TODATALO4(data)                     (data & 0x0f)
#define TODATA5(data)                       ((data >> 1) & 0x1F)
#define TODATA12(data1,data2)               (((data1 & 0x0f) << 8 ) | data2)
#define TODATA13(data1,data2)               (((data1 & 0x1f) << 8 ) | data2)
#define TODATA16(data1,data2)               ((data1 << 8 )  | data2)
#define TODATA24(data1,data2,data3)         ((data1 << 16 ) | (data2 << 8 )  | data3)
#define TODATA28(data1,data2,data3,data4)   ((data1 << 20 ) | (data2 << 12 ) | (data3 << 4 ) | (data4 >> 4))
#define TODATA32(data1,data2,data3,data4)   (((data1 << 24 )| (data2 << 16 ) | (data3 << 8 ) | (data4)))

__END_DECLS

#endif /*__SI_PUBLIC_H__*/
/*@}*/

