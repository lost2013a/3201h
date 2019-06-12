/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __ISO_639_LANGUAGE_DES_H__
#define __ISO_639_LANGUAGE_DES_H__

#include "gxcore.h"

__BEGIN_DECLS


/* Exported Types --------------------------------------------------------- */

/*iso_639_language 0x0a ÃèÊö·û*/
typedef struct
{
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t language_count:16;

    uint8_t* language;
    uint8_t audio_type;
}GxSubsystemSiParseIso639LanguageDes;

__END_DECLS

#endif
/*@}*/

