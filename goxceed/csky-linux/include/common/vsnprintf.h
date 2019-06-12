/*	Public domain	*/

#include <common/config.h>

#include <stdarg.h>

#ifdef HAVE_VSNPRINTF
# include <stdio.h>
# define GxVsnprintf vsnprintf
#else

__BEGIN_DECLS

int GxVsnprintf(char *, size_t, const char *, va_list);

__END_DECLS

#endif
