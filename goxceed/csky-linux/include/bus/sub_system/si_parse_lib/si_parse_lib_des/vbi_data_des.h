/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __VBI_DATA_DES_H__
#define __VBI_DATA_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*VBI data  0x46 ÃèÊö·û*/
typedef struct
{   
    uint32_t reserved:26;
    uint32_t field_parity:1;
    uint32_t line_offset:5;
}GxSubsystemSiParseTtxDataInfo;

typedef struct
{
    uint32_t data_service_id:8;
    uint32_t descriptor_length:8;
    uint32_t count:16;
    
    GxSubsystemSiParseTtxDataInfo* info;
}GxSubsystemSiParseTtxData;

typedef struct
{
    uint32_t descriptor_tag:8;   
    uint32_t descriptor_length:8;
    uint32_t reserved:16;

    uint32_t ttx_data_count;
    GxSubsystemSiParseTtxData* ttx_data;
}GxSubsystemSiParseVbiDataDes;

__END_DECLS

#endif
/*@}*/

