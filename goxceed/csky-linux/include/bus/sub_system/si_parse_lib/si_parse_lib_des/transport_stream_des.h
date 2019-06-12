/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __TRANSPORT_STREAM_DES_H__
#define __TRANSPORT_STREAM_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*transport_stream 0x67 ÃèÊö·û*/
typedef struct
{
    uint32_t descriptor_tag:8;   
    uint32_t descriptor_length:24;

    uint8_t* byte;
}GxSubsystemSiParseTransportStreamDes;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

