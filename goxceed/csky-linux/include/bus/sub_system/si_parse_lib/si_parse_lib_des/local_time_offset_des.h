/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __LOCAL_TIME_OFFSET_DES_H__
#define __LOCAL_TIME_OFFSET_DES_H__

#include "gxcore.h"

__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

/*local time offset 0x58 ÃèÊö·û*/
typedef struct
{
    uint8_t country[3];
    uint8_t country_region_id:6;
    uint8_t reserved:1;
    uint8_t local_time_offset_polarity:1;

    uint16_t local_time_offset;
    uint16_t next_time_offset;
    
    uint8_t  time_of_change[5];
    uint32_t reserved2:24;
}GxSubsystemSiParseLocalTimeOfffset;

typedef struct
{
    uint32_t descriptor_tag:8;   
    uint32_t descriptor_length:8;
    uint32_t time_offset_count:16;

    GxSubsystemSiParseLocalTimeOfffset* time_offset;
}GxSubsystemSiParseLocalTimeOfffsetDes;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

