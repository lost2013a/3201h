#ifndef __EXTENDED_CHANNEL_NAME_DES_H__
#define __EXTENDED_CHANNEL_NAME_DES_H__
#include "multiple_string.h"
__BEGIN_DECLS
typedef struct {
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t reserved:16;
    GxSubsystemSiParseMSSstruct  long_channel_name_text;
}GxSubsystemSiParseExtendedNamedes;

__END_DECLS
#endif

