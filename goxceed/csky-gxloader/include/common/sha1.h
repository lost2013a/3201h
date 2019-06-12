/*	$OpenBSD: sha1.h,v 1.23 2004/06/22 01:57:30 jfb Exp $	*/
/*
 * SHA-1 in C
 * By Steve Reid <steve@edmweb.com>
 * 100% Public Domain
 */

#include <common/config.h>

#ifndef HAVE_SHA1
#undef SHA1_BLOCK_LENGTH
#undef SHA1_DIGEST_LENGTH
#undef SHA1_DIGEST_STRING_LENGTH

#define	SHA1_BLOCK_LENGTH		64
#define	SHA1_DIGEST_LENGTH		20
#define	SHA1_DIGEST_STRING_LENGTH	(SHA1_DIGEST_LENGTH * 2 + 1)

typedef struct {
    uint32_t state[5];
    uint64_t count;
    uint8_t  buffer[SHA1_BLOCK_LENGTH];
} SHA1_CTX;

__BEGIN_DECLS
void SHA1Init(SHA1_CTX *);
void SHA1Pad(SHA1_CTX *);
void SHA1Transform(uint32_t [5], const uint8_t [SHA1_BLOCK_LENGTH]);
void SHA1Update(SHA1_CTX *, const uint8_t *, size_t);
void SHA1Final(uint8_t [SHA1_DIGEST_LENGTH], SHA1_CTX *);
char *SHA1End(SHA1_CTX *, char *);
char *SHA1Data(const uint8_t *, size_t, char *);
__END_DECLS

#endif /* !HAVE_SHA1 */
