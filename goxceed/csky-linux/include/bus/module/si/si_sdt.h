/** @addtogroup si_module*/
/*@{*/
/* Define to prevent recursive inclusion */
#ifndef __SI_SDT_H__
#define __SI_SDT_H__

#include "si_public.h"
#include "gxcore.h"

__BEGIN_DECLS

/**
 *  SDT information storage structure
 */
typedef struct
{
	si_info_t  si_info;              /* si basic information storage structure  */
	uint16_t   service_count;        /* service count */
	uint16_t   res;                  /* reserved*/
	uint16_t   orig_network_id;      /* original network id */
	uint16_t   tsid;
	service_info_t *service_info;    /* service descriptor information storage structure */
	uint8_t    *tail;                /* record the des data, move from tail to begin*/
	uint8_t    buf[SI_SDT_BUF_SIZE]; /* data buf */
}SdtInfo;

__END_DECLS

#endif /* __SI_SDT_H__ */
/*@}*/

