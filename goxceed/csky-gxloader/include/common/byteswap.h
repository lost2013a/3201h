#ifndef _GX_CORE_BYTESWAP_H_
#define _GX_CORE_BYTESWAP_H_

#include <common/config.h>

__BEGIN_DECLS
/*
 * Swap 16-bit
 */
#if defined(__GNUC__) && defined(__i386__) && \
   !(__GNUC__ == 2 && __GNUC_MINOR__ == 95)

static __inline__ uint16_t
GxSwap16(uint16_t x)
{
	__asm__("xchgb %b0,%h0" :
	        "=q" (x) :
		"0" (x));
	return (x);
}
#elif defined(__GNUC__) && defined(__x86_64__)
static __inline__ uint16_t
GxSwap16(uint16_t x)
{
	__asm__("xchgb %b0,%h0" :
	        "=Q" (x) :
		"0" (x));
	return (x);
}
#elif defined(__GNUC__) && (defined(__powerpc__) || defined(__ppc__))
static __inline__ uint16_t
GxSwap16(uint16_t x)
{
	uint16_t rv;
	__asm__("rlwimi %0,%2,8,16,23" :
	        "=&r" (rv) :
		"0" (x >> 8), "r" (x));
	return (rv);
}
#else
static __inline__ uint16_t
GxSwap16(uint16_t x)
{
	return ((x<<8)|(x>>8));
}
#endif

/*
 * Swap 32-bit
 */
#if defined(__GNUC__) && defined(__i386__)
static __inline__ uint32_t
GxSwap32(uint32_t x)
{
	__asm__("bswap %0" :
	        "=r" (x) :
		"0" (x));
	return (x);
}
#elif defined(__GNUC__) && defined(__x86_64__)
static __inline__ uint32_t
GxSwap32(uint32_t x)
{
	__asm__("bswapl %0" :
	        "=r" (x) :
		"0" (x));
	return (x);
}
#elif defined(__GNUC__) && (defined(__powerpc__) || defined(__ppc__))
static __inline__ uint32_t
GxSwap32(uint32_t x)
{
	uint32_t rv;
	__asm__("rlwimi %0,%2,24,16,23" :
	        "=&r" (rv) :
		"0" (x>>24), "r" (x));
	__asm__("rlwimi %0,%2,8,8,15" :
	        "=&r" (rv) :
		"0" (rv), "r" (x));
	__asm__("rlwimi %0,%2,24,0,7" :
	        "=&r" (rv) :
		"0" (rv), "r" (x));
	return (rv);
}
#else
static __inline__ uint32_t
GxSwap32(uint32_t x)
{
	return ((x << 24) |
	       ((x << 8) & 0x00FF0000) | ((x >> 8) & 0x0000FF00) |
	        (x >> 24));
}
#endif

/*
 * Swap 64-bit
 */
#ifdef HAVE_64BIT
# if defined(__GNUC__) && defined(__i386__)
static __inline__ uint64_t
GxSwap64(uint64_t x)
{
	union {
		struct { uint32_t a, b; } s;
		uint64_t u;
	} v;
	v.u = x;
	__asm__("bswapl %0 ; bswapl %1 ; xchgl %0,%1" :
	        "=r" (v.s.a), "=r" (v.s.b) :
		"0" (v.s.a), "1" (v.s.b));
	return (v.u);
}
# elif defined(__GNUC__) && defined(__x86_64__)
static __inline__ uint64_t
GxSwap64(uint64_t x)
{
	__asm__("bswapq %0" :
	        "=r" (x) :
		"0" (x));
	return (x);
}
# else /* !MD */
static __inline__ uint64_t
GxSwap64(uint64_t x)
{
	uint32_t high, low;

	low = (uint32_t)(x & 0xFFFFFFFF);
	x >>= 32;
	high = (uint32_t)(x & 0xFFFFFFFF);
	x = GxSwap32(low);
	x <<= 32;
	x |= GxSwap32(high);
	return (x);
}
# endif /* MD */
#endif /* HAVE_64BIT */

/*
 * Swap floating-point types.
 */
static __inline__ float
GxSwapFLT(float v)
{
	union { uint32_t i; float v; } u;

	u.v = v;
	u.i = GxSwap32(u.i);
	return (u.v);
}

#ifdef HAVE_64BIT
static __inline__ double
GxSwapDBL(double v)
{
	union { uint64_t i; double v; } u;

	u.v = v;
	u.i = GxSwap64(u.i);
	return (u.v);
}
#else
static __inline__ double
GxSwapDBL(double v)
{
	union { uint8_t data[8]; double v; } uIn;
	union { uint8_t data[8]; double v; } uOut;
	int i;

	uIn.v = v;
	for (i = 0; i < 8; i++) {
		uOut.data[i] = uIn.data[7-i];
	}
	return (uOut.v);
}
#endif /* HAVE_64BIT */

#ifdef HAVE_LONG_DOUBLE
static __inline__ long double
GxSwapLDBL(long double v)
{
	union { uint8_t data[10]; long double v; } uIn;
	union { uint8_t data[10]; long double v; } uOut;
	int i;

	uIn.v = v;
	for (i = 0; i < 10; i++) {
		uOut.data[i] = uIn.data[9-i];
	}
	return (uOut.v);
}
#endif /* HAVE_LONG_DOUBLE */

#if GX_BYTEORDER == GX_BIG_ENDIAN
# define GxSwapLE16(X)	GxSwap16(X)
# define GxSwapLE32(X)	GxSwap32(X)
# define GxSwapLE64(X)	GxSwap64(X)
# define GxSwapLEFLT(X) GxSwapFLT(X)
# define GxSwapLEDBL(X) GxSwapDBL(X)
# define GxSwapLELDBL(X) GxSwapLDBL(X)
# define GxSwapBE16(X)	(X)
# define GxSwapBE32(X)	(X)
# define GxSwapBE64(X)	(X)
# define GxSwapBEFLT(X) (X)
# define GxSwapBEDBL(X) (X)
# define GxSwapBELDBL(X) (X)
#else
# define GxSwapLE16(X)	(X)
# define GxSwapLE32(X)	(X)
# define GxSwapLE64(X)	(X)
# define GxSwapLEFLT(X) (X)
# define GxSwapLEDBL(X) (X)
# define GxSwapLELDBL(X) (X)
# define GxSwapBE16(X)	GxSwap16(X)
# define GxSwapBE32(X)	GxSwap32(X)
# define GxSwapBE64(X)	GxSwap64(X)
# define GxSwapBEFLT(X) GxSwapFLT(X)
# define GxSwapBEDBL(X) GxSwapDBL(X)
# define GxSwapBELDBL(X) GxSwapLDBL(X)
#endif

__END_DECLS

#endif /* _GX_CORE_BYTESWAP_H_ */
