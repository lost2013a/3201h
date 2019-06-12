#ifndef __SI_SI_TOT_H__
#define __SI_SI_TOT_H__

#include "si_public.h"

typedef struct {
	si_info_t  si_info;      /**< si  basic information storage structure  */
	uint32_t   utc_mjd;
	uint32_t   utc_time;     /**< bcd time   0x123456 means  12:34:56 */
	uint32_t   time_zone;
} TotInfo;

#endif

