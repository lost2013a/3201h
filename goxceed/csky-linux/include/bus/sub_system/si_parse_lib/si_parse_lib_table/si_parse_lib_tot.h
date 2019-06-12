/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SI_PARSE_LIB_TOT_H__
#define __SI_PARSE_LIB_TOT_H__

#include "gxcore.h"
#include "../si_parse_lib_des/local_time_offset_des.h"

__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

/*-----------------------------¸÷ÖÖ±í-----------------------------------*/

/*tot*/
typedef struct
{
    uint32_t table_id:8;
    uint32_t section_syntax_indicator:1;
    uint32_t reserved_future_use:1;
    uint32_t section_length:12;
    uint32_t reserved1:10;

    uint8_t UTC_time[5];
    uint32_t  descriptors_loop_length:24;
    
    uint32_t local_time_des_count;

    GxSubsystemSiParseLocalTimeOfffsetDes* local_time_des;

}GxSubsystemSiParseTOT;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

