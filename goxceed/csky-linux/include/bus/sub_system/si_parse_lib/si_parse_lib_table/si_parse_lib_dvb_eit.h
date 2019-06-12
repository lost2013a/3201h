#ifndef __SI_PARSE_LIB_DVB_EIT_H__
#define __SI_PARSE_LIB_DVB_EIT_H__
#include "gxcore.h"
#include "../si_parse_lib_des/stuffing_des.h"
#include "../si_parse_lib_des/linkage_des.h"
#include "../si_parse_lib_des/short_event_des.h"
#include "../si_parse_lib_des/extended_event_des.h"
#include "../si_parse_lib_des/time_shift_event_des.h"
#include "../si_parse_lib_des/component_des.h"
#include "../si_parse_lib_des/ca_identifier_des.h"
#include "../si_parse_lib_des/content_des.h"
#include "../si_parse_lib_des/parental_rating_des.h"
#include "../si_parse_lib_des/telephone_des.h"
#include "../si_parse_lib_des/multilingual_component_des.h"
#include "../si_parse_lib_des/private_data_specifier_des.h"
#include "../si_parse_lib_des/short_smoothing_buffer_des.h"
#include "../si_parse_lib_des/data_broadcast_des.h"
#include "../si_parse_lib_des/PDC_des.h"

__BEGIN_DECLS
typedef struct {
	uint32_t event_id:16;
	uint32_t reserved:16;

	uint8_t start_time[5];
	uint8_t duration[3];

	uint32_t running_status:3;
	uint32_t free_CA_mode:1;
	uint32_t descriptors_loop_length:12;
	uint32_t reserved2:8;

	uint32_t sd_count;
	GxSubsystemSiParseStuffingDes*  sd;

	uint32_t ld_count;
	GxSubsystemSiParseLinkageDes* ld;

	uint32_t sed_count;
	GxSubsystemSiParseShortEventDes* sed;

	uint32_t eed_count;
	GxSubsystemSiParseExtendedEventDes * eed;

	uint32_t tsed_count;
	GxSubsystemSiParseTimeShiftEventDes* tsed;

	uint32_t componentdes_count;
	GxSubsystemSiParseComponentDes* componentdes;

	uint32_t cid_count;
	GxSubsystemSiParseCaIdentifierDes* cid;

	uint32_t contentdes_count;
	GxSubsystemSiParseContentDes* contentdes;

	uint32_t prd_count;
	GxSubsystemSiParseParentalRatingDes* prd;

	uint32_t td_count;
	GxSubsystemSiParseTelephoneDes* td;

	uint32_t mcd_count;
	GxSubsystemSiParseMulitiComponentDes* mcd;

	uint32_t pd_count;
	GxSubsystemSiParsePrivateDes* pd;

	uint32_t ssd_count;
	GxSubsystemSiParseShortSmoothingDes* ssd;

	uint32_t dbd_count;
	GxSubsystemSiParseDataBroadcastDes*  dbd;

	uint32_t pdcd_count;
	GxSubsystemSiParsePdcDes* pdcd;
}GxSubsystemSiParseDvbEITLoop;

typedef struct {
    uint32_t table_id:8;
    uint32_t section_syntax_indicator:1;
    uint32_t reserved_future_use:1;
    uint32_t reserved:10;
    uint32_t section_length:12;

    uint32_t service_id:16;
    uint32_t reserved2:2;
    uint32_t version_number:5;
    uint32_t current_next_indicator:1;
    uint32_t section_number:8;

    uint32_t last_section_number:8;
    uint32_t transport_stream_id:16;
    uint32_t reserved3:8;

    uint32_t original_network_id:16;
    uint32_t segment_last_section_number:8;
    uint32_t last_table_id:8;

    uint32_t loop_count;
    GxSubsystemSiParseDvbEITLoop * loop;

	uint32_t CRC_32;
}GxSubsystemSiParseDvbEIT;
__END_DECLS
#endif
