#ifndef __GENRE_DES_H__
#define __GENRE_DES_H__
__BEGIN_DECLS
typedef struct {
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t reserved:11;
    uint32_t attribute_count:5;
    uint8_t * attribute;
}GxSubsystemSiParseGenreDes;
__END_DECLS
#endif
