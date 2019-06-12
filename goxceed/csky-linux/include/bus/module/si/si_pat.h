/** @addtogroup si_module*/
/*@{*/
/* Define to prevent recursive inclusion */
#ifndef __SI_PAT_H__
#define __SI_PAT_H__

#include "si_public.h"
#include "gxcore.h"

__BEGIN_DECLS

/**
 *  program information storage structure
 */
typedef struct program_info
{
	uint16_t   prog_num;  ///< program_number(16)
	uint16_t   pmt_pid;   ///< program_map_PID(13)
}prog_info_t;

/**
 *   pat information storage structure
 */
typedef struct
{
	si_info_t    si_info;                 ///< si  basic information storage structure
	prog_info_t  *prog_info;              ///< program_number(16)
	uint16_t     nit_pid;                 ///< nit_pid(13)
	uint16_t     prog_count;              ///< total program count
	uint8_t      buf[SI_PAT_BUF_SIZE];    ///< data buf used to store prog info
}PatInfo;

__END_DECLS

#endif /* __SI_PAT_H__ */
/*@}*/

