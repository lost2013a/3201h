#ifndef __SI_EIT_H__
#define __SI_EIT_H__

/* Includes --------------------------------------------------------------- */
#include <time.h>
#include "module/si/si_public.h"

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */
/** extended item information storage structure */
typedef  struct  extended_item_info {
	uint8_t  *item_description;       /**< item_description */
	uint8_t  *item;                   /**< item */

	uint16_t reserved;
	uint8_t  item_description_length; /**< item description length(8) */
	uint8_t  item_length;             /**< item length(8) */
} extended_item_info_t;

/** short event descriptor information storage structure  */
typedef  struct  short_event_des_info {
	uint8_t  *event_name;            /**< event name short event descriptor */
	uint8_t  *text;                  /**< text(8) short event descriptor */

	uint8_t  language_code[3];       /**< language_code(24) short event descriptor */
	uint8_t  event_name_length;      /**< event name length (8) short event descriptor */

	uint32_t text_length : 16;       /**< text length(8) short event descriptor */
	uint32_t reserved : 16;
} short_event_des_t;

/** extended event descriptor information storage structure */
typedef struct   extended_event_des_info {
	extended_item_info_t *extended_item_info; /**< extended item information storage structure */
	uint8_t *extended_text;                   /**< extended text extended event descriptor */

	uint8_t language_code[3];                 /**< extended_language_code(24) extended short event descriptor */
	uint8_t item_count;                       /**< item_count(8) extended event descriptor */

	uint16_t extended_text_length;            /**< extend text length(8) */
	uint16_t reserved;
} extended_event_des_t;

/** parental rating  */
typedef struct parental_rating {
	uint8_t country_code[3];
	uint8_t rating;   /* 0:undefined  0x01-0x0F:age=rating+3  0x10-0xff:age defined by broadcaster */
}parental_rating_t;

typedef struct time_shifted_event_des {
	uint16_t reference_service_id;
	uint16_t reference_event_id;
}time_shifted_event_des_t;

/** event information storage structure */
typedef struct event_info {
	short_event_des_t       *short_event_des;
	extended_event_des_t    *extended_event_des;
	parental_rating_t       *parental_rating_des;
	time_shifted_event_des_t tms_event_des; // for NVOD

	time_t                   start_time;                    /**< [5]start time(high 16 bits: MJD date)(low 24 bits: BCD time)   */
	time_t                   duration;                      /**< [3] duration(24bits BCD time, exp. 0x123456 = 12:34:56) */

	uint16_t                 event_id;                      /**< event id(16) */
	uint16_t                 running_status          : 3;   /**< running status(3) */
	uint16_t                 free_CA_mode            : 1;   /**< free CA modes(1) */
	uint16_t                 descriptors_loop_length : 12;  /**< descriptors loop length(12) need ?*/

	uint8_t                  short_event_count;
	uint8_t                  extended_event_count;
	uint8_t                  parental_rating_count;
	uint8_t                  tms_event_count;
}event_info_t;

/** EIT information storage structure */
typedef struct {
	si_info_t     si_info;               /**< si basic information storage structure  */
	event_info_t *event_info;            /**< event information storage structure */
	uint8_t      *tail;
	uint8_t       buf[SI_EIT_BUF_SIZE];  /**< data buf */
	uint16_t      service_id;            /**< service_id(16) */
	uint16_t      orig_network_id;       /**< original_network_id(16) */
	uint16_t      event_count;           /**< event count */
	uint8_t       last_table_id;         /**< last_table_id(8) */
	uint8_t       reserved;
}EitInfo;


__END_DECLS

#endif

