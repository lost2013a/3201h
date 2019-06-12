#ifndef __CONTENT_ADVISORY_DES_H__
#define __CONTENT_ADVISORY_DES_H__
__BEGIN_DECLS
typedef struct{
    uint32_t rating_dimension_j:8;
    uint32_t reserved1:20;
    uint32_t rating_value:4;
}GxSubsystemSiParseRatedDimensions;
typedef struct {
    uint32_t rating_region:8;
    uint32_t rated_dimensions:8;
    uint32_t reserved:16;
    GxSubsystemSiParseRatedDimensions * dimensions;
    uint32_t rating_description_length:8;
    uint32_t reserved2:24;
    GxSubsystemSiParseMSSstruct  rating_description_text;
}GxSubsystemSiParseRatingRegion;

typedef struct {
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t reserved1:10;
    uint32_t rating_region_count:6;
    GxSubsystemSiParseRatingRegion * rating_region_info;
}GxSubsystemSiParseContentAdvisoryDes;

__END_DECLS
#endif
