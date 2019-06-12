/*	$OpenBSD: md5.h,v 1.16 2004/06/22 01:57:30 jfb Exp $	*/
/*
 * This code implements the MD5 message-digest algorithm.
 * The algorithm is due to Ron Rivest.  This code was
 * written by Colin Plumb in 1993, no copyright is claimed.
 * This code is in the public domain; do with it what you wish.
 *
 * Equivalent code is available from RSA Data Security, Inc.
 * This code has been tested against that, and is equivalent,
 * except that you don't need to include two pages of legalese
 * with every copy.
 */

#ifndef MD5_H
#define MD5_H

#include <common/config.h>
#ifdef HAVE_MD5

#include <md5.h>

#else /* !HAVE_MD5 */

#undef MD5_BLOCK_LENGTH
#undef MD5_DIGEST_LENGTH
#undef MD5_DIGEST_STRING_LENGTH

#define	MD5_BLOCK_LENGTH		64
#define	MD5_DIGEST_LENGTH		16
#define	MD5_DIGEST_STRING_LENGTH	(MD5_DIGEST_LENGTH * 2 + 1)

typedef struct MD5Context {
	uint32_t state[4];			/* state */
	uint64_t count;				/* number of bits, mod 2^64 */
	uint8_t  buffer[MD5_BLOCK_LENGTH];		/* input buffer */
} MD5_CTX;

__BEGIN_DECLS
void	 MD5Init(MD5_CTX *);
void	 MD5Update(MD5_CTX *, const uint8_t *, size_t);
void	 MD5Pad(MD5_CTX *);
void	 MD5Final(uint8_t [MD5_DIGEST_LENGTH], MD5_CTX *);
void	 MD5Transform(uint32_t [4], const uint8_t [MD5_BLOCK_LENGTH]);
char	*MD5End(MD5_CTX *, char *);
char	*MD5Data(const uint8_t *, size_t, char *);
__END_DECLS

#endif /* !HAVE_MD5 */


#endif
