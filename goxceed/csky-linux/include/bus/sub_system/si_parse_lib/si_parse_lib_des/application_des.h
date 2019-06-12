/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __APPLICATION_DES_H__
#define __APPLICATION_DES_H__

#include "gxcore.h"
__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*application_des 0x0 ÃèÊö·û*/
typedef struct
{
	uint16_t application_profile;
	uint16_t version_major:8;
	uint16_t version_minor:8;

	uint32_t version_micro:8;
	uint32_t reserved:24;
}GxSubsystemSiParseApplicationProfile;

typedef struct
{
    uint8_t descriptor_tag;
    uint8_t descriptor_length;
    uint16_t application_profiles_length;

	uint32_t profie_count;
	GxSubsystemSiParseApplicationProfile* profile;

	uint16_t service_bound_flag:1;
	uint16_t visibility:2;
	uint16_t reserved_future_flag:5;
	uint16_t application_priority:8;
	uint16_t transport_protocol_label_length;

	uint8_t* transport_protocol_label;

}GxSubsystemSiParseApplicationDes;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS
#endif
/*@}*/
