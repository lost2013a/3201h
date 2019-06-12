#ifndef _API_COMMON_H_
#define _API_COMMON_H_

#ifndef _USE_GXCORE_STD
#define _USE_GXCORE_STD "yes"
#endif

#ifndef _USE_GXCORE_CPUINFO
#define _USE_GXCORE_CPUINFO "yes"
#endif

#ifndef GX_BYTEORDER
#define GX_BYTEORDER GX_LITTLE_ENDIAN
#endif

#ifndef _MK_HAVE_SETJMP
#define _MK_HAVE_SETJMP "yes"
#endif

#ifndef _MK_HAVE_SIGNAL
#define _MK_HAVE_SIGNAL "yes"
#endif

#ifndef HAVE_SNPRINTF
#define HAVE_SNPRINTF "yes"
#endif

#ifndef HAVE_VSNPRINTF
#define HAVE_VSNPRINTF "yes"
#endif

#ifndef HAVE_LONG_LONG
#define HAVE_LONG_LONG "yes"
#endif

#ifndef HAVE_SETENV
#define HAVE_SETENV "yes"
#endif

#undef HAVE_SHA1
#undef HAVE_MD5
#undef HAVE_RMD160

#ifndef HAVE_DLOPEN
#define HAVE_DLOPEN "yes"
#endif
#undef HAVE_DYLD
#undef HAVE_DYLD_RETURN_ON_ERROR
#undef HAVE_SHL_LOAD
#ifndef HAVE_DLFCN_H
#define HAVE_DLFCN_H "yes"
#endif
#undef HAVE_DL_H
#undef HAVE_MACH_O_DYLD_H

#ifndef _MK_HAVE_SYS_TYPES_H
#define _MK_HAVE_SYS_TYPES_H "yes"
#endif

// Limits
#ifndef _MK_HAVE_LIMITS_H
#define _MK_HAVE_LIMITS_H "yes"
#endif

#ifndef _MK_HAVE_FLOAT_H
#define _MK_HAVE_FLOAT_H "yes"
#endif

#ifndef HAVE_LONG_LONG
#define HAVE_LONG_LONG "yes"
#endif

#ifndef HAVE_LONG_DOUBLE
#define HAVE_LONG_DOUBLE "yes"
#endif

#ifndef HAVE_64BIT
#define HAVE_64BIT "yes"
#endif

#ifndef FREE_NULL_IS_A_NOOP
#define FREE_NULL_IS_A_NOOP "yes"
#endif

#ifndef _MK_HAVE_STDLIB_H
#define _MK_HAVE_STDLIB_H "yes"
#endif

#undef _MK_BIG_ENDIAN

#ifndef _MK_LITTLE_ENDIAN
#define _MK_LITTLE_ENDIAN "yes"
#endif

#define GX_BIG_ENDIAN 4321
#define GX_LITTLE_ENDIAN 1234

#ifndef AG_INLINE_OKAY
# ifdef __GNUC__
#  define AG_INLINE_OKAY
# else
#  if defined(_MSC_VER) || defined(__BORLANDC__) || \
      defined(__DMC__) || defined(__SC__) || \
      defined(__WATCOMC__) || defined(__LCC__) || \
      defined(__DECC) || defined(__EABI__)
#   ifndef __inline__
#    define __inline__	__inline
#   endif
#   define AG_INLINE_OKAY
#  else
#   if !defined(__MRC__) && !defined(_SGI_SOURCE)
#    ifndef __inline__
#     define __inline__ inline
#    endif
#    define AG_INLINE_OKAY
#   endif
#  endif
# endif
#endif

#ifndef AG_INLINE_OKAY
# define __inline__
#endif
#undef AG_INLINE_OKAY

#if !defined(__BEGIN_DECLS) || !defined(__END_DECLS)
# define _M_DEFINED_CDECLS
# if defined(__cplusplus)
#  define __BEGIN_DECLS extern "C" {
#  define __END_DECLS   }
# else
#  define __BEGIN_DECLS
#  define __END_DECLS
# endif
#endif


#ifdef HAVE_BOUNDED_ATTRIBUTE
#define BOUNDED_ATTRIBUTE(t, a, b) __attribute__((__bounded__ (t,a,b)))
#else
#define BOUNDED_ATTRIBUTE(t, a, b)
#endif
#ifdef HAVE_FORMAT_ATTRIBUTE
#define FORMAT_ATTRIBUTE(t, a, b) __attribute__((__format__ (t,a,b)))
#else
#define FORMAT_ATTRIBUTE(t, a, b)
#endif
#ifdef HAVE_NONNULL_ATTRIBUTE
#define NONNULL_ATTRIBUTE(a) __attribute__((__nonnull__ (a)))
#else
#define NONNULL_ATTRIBUTE(a)
#endif

#ifdef WIN32
#define GX_PATHSEPC '\\'
#define GX_PATHSEP "\\"
#else
#define GX_PATHSEPC '/'
#define GX_PATHSEP "/"
#endif

#ifdef ENABLE_NLS
# include <libintl.h>
# define _(String) dgettext("gxcore",String)
# ifdef dgettext_noop
#  define N_(String) dgettext_noop("gxcore",String)
# else
#  define N_(String) (String)
# endif
#else
# undef _
# undef N_
# undef ngettext
# define _(String) (String)
# define N_(String) (String)
# define ngettext(Singular,Plural,Number) ((Number==1)?(Singular):(Plural))
#endif /* !ENABLE_NLS */

#include <stdio.h>

#ifdef _MK_HAVE_STDLIB_H
#include <stdlib.h>
#endif

#include <stdint.h>

#ifdef _MK_HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#ifdef _MK_HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif

#ifdef HAVE_SHA1
#include <sha1.h>
#endif

#include <stdarg.h>
#include <string.h>

#endif
