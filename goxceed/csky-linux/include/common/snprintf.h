/*	Public domain	*/

#include <common/config.h>

#ifdef HAVE_SNPRINTF
# include <stdio.h>
# if defined(_WIN32)
#  define GxSnprintf _snprintf
# else
#  define GxSnprintf snprintf
# endif
#else

__BEGIN_DECLS
int GxSnprintf(char *, size_t, const char *, ...);
__END_DECLS

#endif /* !HAVE_SNPRINTF */
