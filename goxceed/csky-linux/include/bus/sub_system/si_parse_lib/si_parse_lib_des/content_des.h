/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __CONTENT_DES_H__
#define __CONTENT_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*content 0x54 ÃèÊö·û*/
typedef struct
{
    uint32_t content_nibble_level_1:8;
    uint32_t content_nibble_level_2:8;
    uint32_t user_nibble1:8;
    uint32_t user_nibble2:8;
}GxSubsystemSiParseContent;

typedef struct
{
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t content_count:16;

    GxSubsystemSiParseContent* content;
}GxSubsystemSiParseContentDes;

__END_DECLS

#endif
/*@}*/

