/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __LINKAGE_DES_H__
#define __LINKAGE_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

typedef union{
	uint32_t network_id:16;
	uint32_t initial_service_id:16;
}HandOverType;

typedef struct {
	uint32_t hand_over_type:4;
	uint32_t reserved_future_use:3;
	uint32_t original_type:1;
	uint32_t reserved:24;

	HandOverType type;
	uint16_t * private_data_byte;
}MobileRoaming;

typedef union
{
	uint8_t *private_data_type;
	MobileRoaming	mobileroaming_s;
}LinkageType;


/*linkage 0x4a ÃèÊö·û*/
typedef struct
{
	uint32_t descriptor_tag:8;
	uint32_t descriptor_length:8;
	uint32_t transport_stream_id:16;

	uint32_t original_network_id:16;
	uint32_t service_id:16;

	uint32_t linkage_type:8;
	uint32_t reserved:24;

	LinkageType linkage_s;
}GxSubsystemSiParseLinkageDes;

__END_DECLS

#endif
/*@}*/

