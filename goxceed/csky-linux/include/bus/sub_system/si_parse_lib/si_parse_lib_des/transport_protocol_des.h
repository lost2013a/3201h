/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __TRANSPORT_PROTOCOL_DES_H__
#define __TRANSPORT_PROTOCOL_DES_H__

#include "gxcore.h"
__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*transport_protocol_des 0x02 ÃèÊö·û*/
typedef struct
{
	uint8_t  remote_connection:1;
	uint8_t  reserved_future_use:7;

	uint16_t original_network_id;
	uint16_t transport_stream_id;
	
	uint16_t service_id;
	uint16_t component_tag:8;
	uint16_t reserved:8;
}GxSubsystemSiParseSelectorOc;

typedef struct
{
    uint8_t descriptor_tag;
    uint8_t descriptor_length;
    uint16_t protocol_id;
	
	uint32_t protocol_label:8;
	uint32_t reserved:24;

	union {
		GxSubsystemSiParseSelectorOc oc;
	//	GxSubsystemSiParseSelectorIp ip;
	};

}GxSubsystemSiParseTransportProtocolDes;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS
#endif
/*@}*/
