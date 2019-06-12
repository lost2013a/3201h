/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SI_PARSE_LIB_AIT_H__
#define __SI_PARSE_LIB_AIT_H__

#include "gxcore.h"
#include "../si_parse_lib_des/application_des.h"
#include "../si_parse_lib_des/application_name_des.h"
#include "../si_parse_lib_des/application_icons_des.h"
#include "../si_parse_lib_des/transport_protocol_des.h"
#include "../si_parse_lib_des/dvb_j_application_des.h"
#include "../si_parse_lib_des/dvb_j_application_location_des.h"
__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

/*-----------------------------¸÷ÖÖ±í-----------------------------------*/

/*ait*/
typedef struct
{
	uint32_t organisation_id;
	uint32_t application_id;
}AitApplicationIdentifier;

typedef struct
{
	AitApplicationIdentifier application_identifier;
	uint32_t application_control_code:8;
	uint32_t reserved_future_use:4;
	uint32_t application_descriptors_loop_length:12;
	uint32_t reserved:8;

	uint32_t application_count;
	GxSubsystemSiParseApplicationDes* application;

	uint32_t name_count;
	GxSubsystemSiParseApplicationNameDes* name;

	uint32_t icons_count;
	GxSubsystemSiParseApplicationIconsDes* icons;
	
	uint32_t transport_protocol_count;
	GxSubsystemSiParseTransportProtocolDes* transport_protocol;
	
	uint32_t dvb_j_application_count;
	GxSubsystemSiParseDvbJApplicationDes* dvb_j_application;
	
	uint32_t dvb_j_application_location_count;
	GxSubsystemSiParseDvbJApplicationLocationDes* dvb_j_application_location;

	/*
	uint32_t dvb_html_application_count;
	GxSubsystemSiParseDvbHtmlApplicationDes dvb_html_application;

	uint32_t dvb_html_application_location_count;
	GxSubsystemSiParseDvbHtmlApplicationLocationDes* dvb_html_application_location;
	
	uint32_t dvb_html_application_boundary_count;
	GxSubsystemSiParseDvbHtmlApplicationBoundaryDes* dvb_html_application_boundary;
	 */
}GxSubsystemSiParseAitLoop2;

typedef struct
{
	/*
	uint32_t external_application_authorisation_count;
	GxSubsystemSiParseExternalAppAuthorDes* external_application_authorisation;

	uint32_t routing_count;
	GxSubsystemSiParseRoutingDes* rounting;
	*/

	uint32_t transport_protocol_count;
	GxSubsystemSiParseTransportProtocolDes* transport_protocol;
}GxSubsystemSiParseAitLoop1;

typedef struct
{
    uint32_t table_id:8;
    uint32_t section_syntax_indicator:1;
    uint32_t reserved_future_use1:1;
    uint32_t section_length:12;
    uint32_t reserved1:10;
    
	uint32_t application_type:16;
	uint32_t version_number:5;
	uint32_t current_next_indicator:1;
	uint32_t section_number:8;
    uint32_t reserved2:2;

	uint32_t last_section_number:8;
    uint32_t reserved_future_use2:4;
    uint32_t common_descriptors_length:12;
	uint32_t reserved3:8;
    
	GxSubsystemSiParseAitLoop1 loop1;

	uint16_t reserved_future_use3:4;
	uint16_t application_length:12;
	uint16_t loop2_count;

	GxSubsystemSiParseAitLoop2* loop2;

}GxSubsystemSiParseAIT;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

