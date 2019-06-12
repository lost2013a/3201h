/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __TELEPHONE_DES_H__
#define __TELEPHONE_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*telephone 0x57 ÃèÊö·û*/
typedef struct
{
	uint32_t descriptor_tag:8;
	uint32_t descriptor_length:8;
	uint32_t reserved_future_use:2;
	uint32_t foreign_availability:1;
	uint32_t connection_type:5;
	uint32_t reserved_future_use2:1;
	uint32_t country_prefix_length:2;
	uint32_t international_area_code_length:3;
	uint32_t operator_code_length:2;

	uint32_t reserved_future_use3:1;
	uint32_t national_area_code_length:3;
	uint32_t core_number_length:4;
	uint32_t reserved:24;

	uint8_t* country_prefix_char;
	uint8_t* international_area_code_char;
	uint8_t* operator_code_char;
	uint8_t* national_area_code_char;
	uint8_t* core_number_char;
}GxSubsystemSiParseTelephoneDes;

__END_DECLS

#endif
/*@}*/

