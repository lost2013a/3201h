/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __EAC_3_DES_H__
#define __EAC_3_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*EAC-3_descriptor 0x7a ÃèÊö·û*/
typedef struct
{
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t EAC3_type_flag:1;
    uint32_t bsid_flag:1;
    uint32_t mainid_flag:1;
    uint32_t asvc_flag:1;
    uint32_t mixinfoexists:1;
    uint32_t substream1_flag:1;
    uint32_t substream2_flag:1;
    uint32_t substream3_flag:1;
    uint32_t reserved:8;

    uint8_t EAC3_type;
    uint8_t bsid;
    uint8_t mainid;
    uint8_t asvc;
    uint8_t substream1;
    uint8_t substream2;
    uint8_t substream3;
}GxSubsystemSiParseEAC3Des;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

