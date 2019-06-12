/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SERVICE_LIST_DES_H__
#define __SERVICE_LIST_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*service list 0x41 ÃèÊö·û*/
typedef struct
{
    uint32_t service_id:16;
    uint32_t service_type:8;
    uint32_t reserved:8;
}GxSubsystemSiParseServiceListInfo;

typedef struct
{
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:24;

    uint32_t descriptor_count;

    GxSubsystemSiParseServiceListInfo* service_list;
}GxSubsystemSiParseServiceListDes;

__END_DECLS

#endif
/*@}*/

