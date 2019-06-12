/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SI_PARSE_LIB_TDT_H__
#define __SI_PARSE_LIB_TDT_H__

#include "gxcore.h"

__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

/*-----------------------------���ֱ�-----------------------------------*/

/*tdt*/
typedef struct
{
    uint32_t table_id:8;
    uint32_t section_syntax_indicator:1;
    uint32_t section_length:12;
    uint32_t reserved1:11;

    uint8_t UTC_time[5];//ǰ40λ����Ч����
}GxSubsystemSiParseTDT;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

