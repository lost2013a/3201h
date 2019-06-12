/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __VBI_TTX_DES_H__
#define __VBI_TTX_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

typedef struct
{
    uint8_t language[3];
    uint8_t teletex_type:5;
    uint8_t magazine_number:3;
    uint8_t page_number;
    uint32_t reserved:24;
}GxSubsystemSiParseTtxInfo;

/*VBI teletext 0x45 ÃèÊö·û*/
typedef struct
{
    uint32_t descriptor_tag:8;   
    uint32_t descriptor_length:8;
    uint32_t reserved:16;

    uint32_t txt_info_count;
    GxSubsystemSiParseTtxInfo* ttx_info;
}GxSubsystemSiParseVbiDes;

/*teletext  0x56 ÃèÊö·û*/
typedef struct
{
    uint32_t descriptor_tag:8;   
    uint32_t descriptor_length:8;
    uint32_t txt_info_count:16; 

    GxSubsystemSiParseTtxInfo* ttx_info;
}GxSubsystemSiParseTtxDes;

__END_DECLS

#endif
/*@}*/

