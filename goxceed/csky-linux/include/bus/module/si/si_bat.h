#ifndef __SI_BAT_H__
#define __SI_BAT_H__

/* Includes --------------------------------------------------------------- */
#include "si_public.h"
#include "gxcore.h"

__BEGIN_DECLS

typedef struct trans_stream {
	uint16_t tp_stream_id;              /**< transport_stream_id(16) */
	uint16_t orig_network_id;           /**< original_network_id(16) */
	uint8_t  service_number;            /**< service_number (8) service list descriptor */
	service_list_info_t *service_list;  /**< service list information */
}trans_stream_t;

/* linkage information in nit  storage structure */
typedef struct linkage_info {
	uint16_t   ts_id;           /**< transport stream id */
	uint16_t   orig_network_id; /**< original network id */
	uint16_t   service_id;      /**< service id */
	uint8_t    linkage_type;    /**< linkage type */
	uint8_t   *private_data;    /**< transport stream information array */
}linkage_info_t;


/* BAT information storage structure */
typedef struct bat_info {
	si_info_t        si_info;              /**< si basic information storage structure  */

	bouquet_info_t  *bouquet_info;         /**< bouquet information */
	linkage_info_t  *linkage_info;         /**< bouquet information */
	trans_stream_t  *ts_info;              /**< transport stream  information */
	uint8_t         *tail;                 /**< tail position */

	uint8_t         buf[SI_BAT_BUF_SIZE];  /**< data buf */

	uint16_t        bouquet_id;            /**< bouquet_id(16) */
	uint8_t         ts_count;              /**< transport stream count */
	uint8_t         bouquet_count;         /**< transport stream count */

	uint8_t         linkage_count;         /**< linkage des count */
}BatInfo;

__END_DECLS

#endif /* __SI_BAT_H__ */
/*@}*/

