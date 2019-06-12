/** @defgroup pm_module PM Module*/
/*@{*/
#ifndef __PARENTAL_RATING_DES_H__
#define __PARENTAL_RATING_DES_H__

#include "gxcore.h"

__BEGIN_DECLS

/* Exported Types --------------------------------------------------------- */

/*parental rating 0x55 ÃèÊö·û*/
typedef struct
{
    uint8_t country[3];
    uint8_t rating;
}GxSubsystemSiParseParentalRating;

typedef struct
{
    uint32_t descriptor_tag:8;
    uint32_t descriptor_length:8;
    uint32_t parental_rating_count:16;

    GxSubsystemSiParseParentalRating* parental_rating;
}GxSubsystemSiParseParentalRatingDes;

__END_DECLS

#endif
/*@}*/

