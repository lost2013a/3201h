/*	Public domain	*/

#ifndef STRING_COMPAT_H
#define STRING_COMPAT_H

#include <common/config.h>
#include "common/error.h"

__BEGIN_DECLS

size_t  strlcpy(char *dst, const char *src, size_t siz) BOUNDED_ATTRIBUTE(__string__, 1, 3);
size_t  strlcat(char *dst, const char *src, size_t siz) BOUNDED_ATTRIBUTE(__string__, 1, 3);

__END_DECLS

#endif
