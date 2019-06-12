/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SUBTITLING_DES_H__
#define __SUBTITLING_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*subtitling 0x59 ÃèÊö·û*/
typedef struct
{
    uint8_t language[3];
    uint8_t substitling_type;
    uint16_t composition_page_id;
    uint16_t ancillary_page_id;
}GxSubsystemSiParseSubtInfo;

typedef struct
{
    uint32_t descriptor_tag:8;   
    uint32_t descriptor_length:8;
    uint32_t subt_info_count:16;

    GxSubsystemSiParseSubtInfo* subt_info;
}GxSubsystemSiParseSubtDes;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

