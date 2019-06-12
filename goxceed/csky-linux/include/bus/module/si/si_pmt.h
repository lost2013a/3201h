/** @addtogroup si_module*/
/*@{*/
/* Define to prevent recursive inclusion */
#ifndef __SI_PMT_H__
#define __SI_PMT_H__

#include <module/si/si_public.h>
#include "gxcore.h"

__BEGIN_DECLS

typedef struct {
	uint8_t  iso639[3];
	uint8_t	 audio_type;
}Iso639Descriptor;

/**
 *  stream information storage structure
 */
typedef struct stream_info {
	Iso639Descriptor *iso639_info;

	uint16_t elem_pid;       /**< elementary_PID(13) */
	uint8_t  stream_type;    /**< stream_type(8) */
//	uint8_t  ca_counter;     /**< reserved */
//	uint8_t  ca_idx[4];
	uint8_t  iso639_count;
//	uint8_t  desc_mark;
}stream_info_t;

// if the flag set to "1", the  value is useful
typedef struct {
	uint16_t   elem_pid;
	uint16_t   component_type_flag : 1;
	uint16_t   bsid_flag           : 1;
	uint16_t   mainid_flag         : 1;
	uint16_t   asvc_flag           : 1;
	uint16_t   reserved_flags      : 12;

	uint8_t   component_type;
	uint8_t   bsid;
	uint8_t   mainid;
	uint8_t   asvc;
}Ac3Descriptor;

typedef struct {
	uint16_t   elem_pid;
	uint32_t EAC3_type_flag  : 1;
	uint32_t bsid_flag       : 1;
	uint32_t mainid_flag     : 1;
	uint32_t asvc_flag       : 1;
	uint32_t mixinfoexists   : 1;
	uint32_t substream1_flag : 1;
	uint32_t substream2_flag : 1;
	uint32_t substream3_flag : 1;
	uint32_t reserved        : 8;

	uint8_t EAC3_type;
	uint8_t bsid;
	uint8_t mainid;
	uint8_t asvc;
	uint8_t substream1;
	uint8_t substream2;
	uint8_t substream3;
}Eac3Descriptor;

typedef struct {
	uint8_t iso639[3];
	uint8_t type;
	uint16_t composite_page_id;
	uint16_t ancillary_page_id;
}Subtiling;

typedef struct {
	uint16_t elem_pid;
	uint16_t subt_num;
	Subtiling *subt;
}SubtDescriptor;

typedef struct {
	uint8_t iso639[3];
	uint8_t type       : 5;
	uint8_t magazine   : 3;

	uint32_t page      : 8;
	uint32_t  reserved : 24;
}Teletext;

typedef struct {
	uint16_t elem_pid;
	uint16_t ttx_num;
	Teletext *ttx;
}TeletextDescriptor;

/**
 *   PMT information storage structure
 */
typedef struct {
//	add table id here
	si_info_t si_info;            /**< si  basic information storage structure  */
	uint16_t  prog_num;           /**< program_number(16) */
	uint16_t  pcr_pid;            /**< PCR_PID(13) */

	uint16_t  reserved;
	uint8_t   ca_count;           /**< ca loop count */
	uint8_t   ca_count2;          /**< ca loop count */

	uint8_t   stream_count;       /**< stream count */
	uint8_t   ac3_count;          /**< ac-3 count */
	uint8_t   eac3_count;         /**< eac-3 count */
	uint8_t   ttx_count;
	uint8_t   subt_count;

	uint32_t  *ca_info;           /**< ca descriptor information in loop1, use "ca_system_t" to get "ca_info"*/
	uint32_t  *ca_info2;          /**< ca descriptor information in loop2 */
	uint32_t  *ac3_info;
	uint32_t  *eac3_info;
	uint32_t  *ttx_info;
	uint32_t  *subt_info;
	stream_info_t *stream_info;   /**< stream information */
//	uint32_t pmt_crc32;

	uint8_t   *tail;

	uint8_t   buf[SI_PMT_BUF_SIZE];	/**< data buf */
}PmtInfo;

__END_DECLS

#endif /* __SI_PMT_H__ */
/*@}*/

