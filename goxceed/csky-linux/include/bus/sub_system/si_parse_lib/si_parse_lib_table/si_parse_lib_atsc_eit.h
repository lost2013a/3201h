#ifndef SI_PARSE_LIB_EIT_H
#define SI_PARSE_LIB_EIT_H
#include "gxcore.h"
#include "../si_parse_lib_des/AC_3_des.h"
#include "../si_parse_lib_des/EAC_3_des.h"
#include "../si_parse_lib_des/caption_service_des.h"
#include "../si_parse_lib_des/multiple_string.h"
#include "../si_parse_lib_des/content_advisory_des.h"
#include "../si_parse_lib_des/genre_des.h"
#include "../si_parse_lib_des/redistribution_control_des.h"
__BEGIN_DECLS 
typedef struct{
    uint32_t reserved1:18;
    uint32_t event_id:14;

    uint32_t start_time;

    uint32_t reserved2:2;
    uint32_t ETM_location:2;
    uint32_t length_in_seconds:20;
    uint32_t title_length:8;

    GxSubsystemSiParseMSSstruct  title_text;
    uint32_t reserved3:20;
    uint32_t descriptor_length:12;

    uint32_t ac3_count;
    GxSubsystemSiParseAC3Des * ac3;

    uint32_t csd_count;
    GxSubsystemSiParseCaptionServiceDes * csd;

    uint32_t cad_count;
    GxSubsystemSiParseContentAdvisoryDes * cad;

    uint32_t rcd_count;
    GxSubsystemSiParseRedistributionControlDes * rcd;

    uint32_t gd_count;
    GxSubsystemSiParseGenreDes * gd;

    uint32_t eac3_count;
    GxSubsystemSiParseEAC3Des * eac3;

}GxSubsystemSiParseAtscEITLoop;
typedef struct{
    uint32_t table_id:8;
    uint32_t section_syntax_indicator:1;
    uint32_t private_indicator:1;
    uint32_t reserved1:10;
    uint32_t section_length:12;

    uint32_t source_id:16;
    uint32_t reserved2:2;
    uint32_t version_number:5;
    uint32_t current_next_indicator:1;
    uint32_t section_number:8;

    uint32_t last_section_number:8;
    uint32_t protocol_version:8;
    uint32_t num_events_in_section:8;
    uint32_t reserved3:8;


    GxSubsystemSiParseAtscEITLoop *loop;
    uint32_t CRC_32;
}GxSubsystemSiParseAtscEIT;
__END_DECLS
#endif
