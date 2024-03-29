#ifndef _GX_LIMITS_H_
#define _GX_LIMITS_H_

#include <common/config.h>

/*
 * String limits
 */
#if defined(MAXPATHLEN)
# define GX_PATHNAME_MAX MAXPATHLEN
#else
# define GX_PATHNAME_MAX 1024
#endif
#if defined(FILENAME_MAX)
# define GX_FILENAME_MAX FILENAME_MAX
#else
# define GX_FILENAME_MAX 256
#endif

#if defined(BUFSIZ)
# define GX_BUFFER_MIN BUFSIZ
# define GX_BUFFER_MAX BUFSIZ
#else
# define GX_BUFFER_MIN 1024
# define GX_BUFFER_MAX 8192
#endif

/*
 * Integer limits
 */
#ifdef _MK_HAVE_LIMITS_H
# include <limits.h>
# define GX_INT_MIN	INT_MIN
# define GX_INT_MAX	INT_MAX
# define GX_UINT_MAX	UINT_MAX
# define GX_LONG_MIN	LONG_MIN
# define GX_LONG_MAX	LONG_MAX
# define GX_ULONG_MAX	ULONG_MAX
#else
# define GX_INT_MIN	(-0x7fffffff-1)
# define GX_INT_MAX	0x7fffffff
# define GX_UINT_MAX	0xffffffffU
# ifdef __LP64__
#  define GxULONG_MAX	0xffffffffffffffffUL
#  define GxLONG_MAX	0x7fffffffffffffffL
#  define GxLONG_MIN	(-0x7fffffffffffffffL-1)
# else
#  define GxULONG_MAX	0xffffffffUL
#  define GxLONG_MAX	0x7fffffffL
#  define GxLONG_MIN	(-0x7fffffffL-1)
# endif
#endif
#ifdef HAVE_LONG_LONG
# define GX_ULLONG_MAX	0xffffffffffffffffULL
# define GX_LLONG_MIN	(-0x7fffffffffffffffLL-1)
# define GX_LLONG_MAX	0x7fffffffffffffffLL
#endif

/*
 * Floating-point number limits
 */
#ifdef __FLT_MIN__
# define GX_FLT_MIN __FLT_MIN__
#else
# define GX_FLT_MIN 1.175494351e-38f
#endif
#ifdef __FLT_MAX__
# define GX_FLT_MAX __FLT_MAX__
#else
# define GX_FLT_MAX 3.402823466e+38f
#endif
#ifdef __DBL_MIN__
# define GX_DBL_MIN __DBL_MIN__
#else
# define GX_DBL_MIN 2.2250738585072014e-308
#endif
#ifdef __DBL_MAX__
# define GX_DBL_MAX __DBL_MAX__
#else
# define GX_DBL_MAX 1.7976931348623158e+308
#endif
#ifdef HAVE_LONG_DOUBLE
# ifdef __LDBL_MIN__
#  define GxLDBL_MIN __LDBL_MIN__
# else
#  define GxLDBL_MIN 3.36210314311209350626e-4932l
# endif
# ifdef __LDBL_MAX__
#  define GxLDBL_MAX __LDBL_MAX__
# else
#  define GxLDBL_MAX 1.18973149535723176502e+4932l
# endif
#endif /* HAVE_LONG_DOUBLE */

#ifdef _MK_HAVE_FLOAT_H
# include <float.h>
# define GX_FLT_EPSILON FLT_EPSILON
# define GX_DBL_EPSILON DBL_EPSILON
# ifdef HAVE_LONG_DOUBLE
#  define GxLDBL_EPSILON LDBL_EPSILON
# endif
#else /* !_MK_HAVE_FLOAT_H */
# define GX_FLT_EPSILON 1.192092896e-7f
# define GX_DBL_EPSILON 2.2204460492503131e-16
# ifdef HAVE_LONG_DOUBLE
#  define GxLDBL_EPSILON 1.08420217248550443e-19l
# endif
#endif /* _MK_HAVE_FLOAT_H */

#endif

