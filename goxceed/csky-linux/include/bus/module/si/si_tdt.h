/** @addtogroup si_module*/
/*@{*/
/* Define to prevent recursive inclusion */
#ifndef __SI_TDT_H__
#define __SI_TDT_H__

#include "si_public.h"
#include "gxcore.h"

__BEGIN_DECLS

typedef struct {
	si_info_t   si_info;  /**< si  basic information storage structure  */
	uint32_t   utc_mjd;
	uint32_t   utc_time;  /**< bcd time   0x123456 means  12:34:56*/
}TdtInfo;

__END_DECLS

#endif /* __SI_TDT_H__ */
/*@}*/

