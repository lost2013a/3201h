/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __VIDEO_STREAM_DES_H__
#define __VIDEO_STREAM_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*video_stream 0x2 ÃèÊö·û*/
typedef struct
{
    uint32_t descriptor_tag:8;   
    uint32_t descriptor_length:8;
    uint32_t multiple_frame_rate_flag:1;
    uint32_t frame_rate_code:4;
    uint32_t MPEG_2_flag:1;
    uint32_t constrained_paramter_flag:1;
    uint32_t still_picture_flag:1;
    uint32_t profile_and_level_indication:8;

    uint32_t chroma_format:2;
    uint32_t frame_rate_extension_flag:1;
    uin32_t reserved:29;
}GxSubsystemSiParseVideoStreamDes;

/* Exported Functions ----------------------------------------------------- */

__END_DECLS

#endif
/*@}*/

