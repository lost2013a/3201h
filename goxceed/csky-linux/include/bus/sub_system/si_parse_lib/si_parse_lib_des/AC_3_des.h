/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __AC_3_DES_H__
#define __AC_3_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*AC-3_descriptor 0x6a ÃèÊö·û*/
typedef struct
{
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t AC3_type_flag:1;
    uint32_t bsid_flag:1;
    uint32_t mainid_flag:1;
    uint32_t asvc_flag:1;
    uint32_t reserved:12;

    uint8_t AC3_type;
    uint8_t bsid;
    uint8_t mainid;
    uint8_t asvc;
}GxSubsystemSiParseAC3Des;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

