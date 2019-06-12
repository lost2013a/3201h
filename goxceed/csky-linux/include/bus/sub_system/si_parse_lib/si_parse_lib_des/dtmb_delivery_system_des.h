
/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __DTMB_DELIVERY_SYSTEM_DES_H__
#define __DTMB_DELIVERY_SYSTEM_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*-----------------------------光嶽宙峰憲-----------------------------------*/

/*dtmb delivery system 0x5A 宙峰憲*/
typedef struct
{
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t reserved:16;

    uint32_t frequency;


    uint8_t FEC :4;
    uint16_t modulation :4;
    uint16_t number_of_subcarrier :4;
    uint16_t frame_header_mode :4;
    uint16_t interleaving_mode :4;
    uint16_t other_frequency_flag :1;
    uint16_t sfn_mfn_flag :1;
    uint16_t reserved2 :10;
}GxSubsystemSiParseDtmbDeliveryDes;

__END_DECLS

#endif
/*@}*/
