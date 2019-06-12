#include <common/config.h>

#ifndef HAVE_SETENV
__BEGIN_DECLS
int	setenv(const char *, const char *, int);
void	unsetenv(const char *);
__END_DECLS

#endif
