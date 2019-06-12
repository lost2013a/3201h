/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SERVICE_MOVE_DES_H__
#define __SERVICE_MOVE_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*service_move 0x60 ÃèÊö·û*/
typedef struct
{
    uint8_t descriptor_tag;   
    uint8_t descriptor_length;
    uint16_t new_original_network_id;
    uint16_t  new_transport_stream_id;
    uint16_t  new_service_id;
}GxSubsystemSiParseServiceMoveDes;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

