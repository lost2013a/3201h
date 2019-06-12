/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __SI_PARSE_LIB_PMT_H__
#define __SI_PARSE_LIB_PMT_H__

#include "gxcore.h"
#include "../si_parse_lib_des/ca_des.h"
#include "../si_parse_lib_des/vbi_ttx_des.h"
#include "../si_parse_lib_des/vbi_data_des.h"
#include "../si_parse_lib_des/stream_identifier_des.h"
#include "../si_parse_lib_des/subtitling_des.h"
#include "../si_parse_lib_des/AC_3_des.h"
#include "../si_parse_lib_des/EAC_3_des.h"
#include "../si_parse_lib_des/ancillary_data_des.h"
#include "../si_parse_lib_des/iso_639_language_des.h"
#include "../si_parse_lib_des/data_broadcast_id_des.h"
#include "../si_parse_lib_des/application_signalling_des.h"

__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */
typedef struct
{
    //uint32_t ca_system_count;
    //GxSubsystemSiParseCaSystemDes* ca_system;

    // uin32t_t service_move_count;
    // GxSubsystemSiParseServiceMoveDes* service_move;

    //uin32t_t private_data_specifier_count;
    //GxSubsystemSiParsePrivateDes* private_data;
    
    //uin32t_t data_braodcast_id_count;
    //GxSubsystemSiParseDataBroadcaseIdDes* data_braodcast_id;

    uint32_t ca_count;
    GxSubsystemSiParseCaDes* ca;
}GxSubsystemSiParsePmtLoop1;

typedef struct
{
    uint32_t stream_type:8;
    uint32_t elementary_pid:13;
    uint32_t reserved:2;
    
    uint32_t es_info_length;

    uint32_t vbi_ttx_count;
    GxSubsystemSiParseVbiDes* vbi_ttx;

    uint32_t vbi_ttx_data_count;
    GxSubsystemSiParseVbiDataDes* vbi_ttx_data;
    
    uint32_t stream_identifier_count;
    GxSubsystemSiParseStreamIdentifierDes* stream_identifier;

    uint32_t ttx_count;
    GxSubsystemSiParseTtxDes* ttx;

    uint32_t subtitling_count;
    GxSubsystemSiParseSubtDes* subtitling;

    uint32_t ac3_count;
    GxSubsystemSiParseAC3Des* ac3;
    
	uint32_t eac3_count;
    GxSubsystemSiParseEAC3Des* eac3;
    
    uint32_t ancillary_data_count;
    GxSubsystemSiParseAncillaryDataDes* ancillary_data;

    uint32_t ca_count;
    GxSubsystemSiParseCaDes* ca;

    uint32_t iso_639_count;
    GxSubsystemSiParseIso639LanguageDes* iso_639;
    
	uint32_t data_broadcast_id_count;
    GxSubsystemSiParseDataBroadcaseIdDes* data_broadcast_id;
   
	uint32_t application_signalling_count;
	GxSubsystemSiParseApplicationSignallingDes* application_signalling;
	
	//uint32_t ca_system_count;
    //GxSubsystemSiParseCaSystemDes* ca_system;
    
    // uint32t_t service_move_count;
    // GxSubsystemSiParseServiceMoveDes* service_move;
    
    //uin32t_t private_data_specifier_count;
    //GxSubsystemSiParsePrivateDes* private_data;

}GxSubsystemSiParsePmtLoop2;

typedef struct
{
    uint32_t table_id:8;
    uint32_t section_syntax_indicator:1;
    uint32_t section_length:12;
    uint32_t reserved1:11;

    uint32_t program_number:16;
    uint32_t version_number:5;
    uint32_t current_next_indicator:1;
    uint32_t section_number:8;
    uint32_t reserved2:2;

    uint32_t last_section_number:8;
    uint32_t PCR_PID:13;
    uint32_t reserved3:11;

    uint32_t program_info_length;

    GxSubsystemSiParsePmtLoop1 loop1;
    uint32_t loop2_count; 
    GxSubsystemSiParsePmtLoop2* loop2;
} GxSubsystemSiParsePMT;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

