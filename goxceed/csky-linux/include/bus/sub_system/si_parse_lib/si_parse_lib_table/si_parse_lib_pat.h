/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SI_PARSE_LIB_PAT_H__
#define __SI_PARSE_LIB_PAT_H__

#include "gxcore.h"

__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

/*-----------------------------¸÷ÖÖ±í-----------------------------------*/

/*pat*/
typedef struct
{
    uint16_t   prog_num;  ///< program_number(16)
    uint16_t   network_pid;
    uint16_t   pmt_pid;   ///< program_map_PID(13)
    uint16_t   reserved1;
}GxSubsystemSiParseProgInfo;

typedef struct
{
    uint32_t table_id:8;
    uint32_t section_syntax_indicator:1;
    uint32_t section_length:12;
    uint32_t reserved1:11;

    uint32_t transport_stream_id:16;
    uint32_t section_number:8;
    uint32_t last_section_number:8;

    uint32_t version_number:5;
    uint32_t current_next_indicator:1;
    uint32_t reserved2:26;

    uint32_t prog_count;
    GxSubsystemSiParseProgInfo* prog_info;
}GxSubsystemSiParsePAT;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

