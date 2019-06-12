/*-
 * Copyright (c) 1990, 1993, 1994
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)db.h	8.7 (Berkeley) 6/16/94
 */

#ifndef _DB_H_
#define	_DB_H_

#include <limits.h>

#include "compat.h"
#include "gxcore.h"

__BEGIN_DECLS

#define	RET_ERROR	-1		/* Return values. */
#define	RET_SUCCESS	 0
#define	RET_SPECIAL	 1

typedef unsigned int db_uint32_t;
typedef unsigned int db_uint;
typedef unsigned int db_uint16_t;
typedef int          db_int32_t;
typedef int          db_int16_t;
typedef unsigned int db_uchar;

#define	MAX_PAGE_NUMBER	0xffffffff	/* >= # of pages in a file */
typedef db_uint32_t	pgno_t;
#define	MAX_PAGE_OFFSET	65535		/* >= # of bytes in a page */
typedef db_uint16_t	indx_t;
#define	MAX_REC_NUMBER	0xffffffff	/* >= # of records in a tree */
typedef db_uint32_t	recno_t;

/* Key/data structure -- a Data-Base Thang. */
typedef struct {
	void	*data;			/* data */
	size_t	 size;			/* data length */
} DBT;

/* Routine flags. */
#define	R_CURSOR	1		/* del, put, seq */
#define	__R_UNUSED	2		/* UNUSED */
#define	R_FIRST		3		/* seq */
#define	R_IAFTER	4		/* put (RECNO) */
#define	R_IBEFORE	5		/* put (RECNO) */
#define	R_LAST		6		/* seq (BTREE, RECNO) */
#define	R_NEXT		7		/* seq */
#define	R_NOOVERWRITE	8		/* put */
#define	R_PREV		9		/* seq (BTREE, RECNO) */
#define	R_SETCURSOR	10		/* put (RECNO) */
#define	R_RECNOSYNC	11		/* sync (RECNO) */

typedef enum { DB_BTREE, DB_HASH, DB_RECNO } DBTYPE;

/*
 * !!!
 * The following flags are included in the dbopen(3) call as part of the
 * open(2) flags.  In order to avoid conflicts with the open flags, start
 * at the top of the 16 or 32-bit number space and work our way down.  If
 * the open flags were significantly expanded in the future, it could be
 * a problem.  Wish I'd left another flags word in the dbopen call.
 *
 * !!!
 * None of this stuff is implemented yet.  The only reason that it's here
 * is so that the access methods can skip copying the key/data pair when
 * the DB_LOCK flag isn't set.
 */
#if UINT_MAX > 65535
#define	DB_LOCK		0x20000000	/* Do locking. */
#define	DB_SHMEM	0x40000000	/* Use shared memory. */
#define	DB_TXN		0x80000000	/* Do transactions. */
#else
#define	DB_LOCK		    0x2000	/* Do locking. */
#define	DB_SHMEM	    0x4000	/* Use shared memory. */
#define	DB_TXN		    0x8000	/* Do transactions. */
#endif

/* Access method description structure. */
typedef struct __db {
	DBTYPE type;			/* Underlying db type. */
	int (*close)	__P((struct __db *));
	int (*del)	__P((const struct __db *, const DBT *, db_uint));
	int (*get)	__P((const struct __db *, const DBT *, DBT *, db_uint));
	int (*put)	__P((const struct __db *, DBT *, const DBT *, db_uint));
	int (*seq)	__P((const struct __db *, DBT *, DBT *, db_uint));
	int (*sync)	__P((const struct __db *, db_uint));
	void *internal;			/* Access method private. */
	int (*fd)	__P((const struct __db *));
} DB;

#define	BTREEMAGIC	0x053162
#define	BTREEVERSION	3

/* Structure used to pass parameters to the btree routines. */
typedef struct {
#define	R_DUP		0x01	/* duplicate keys */
	u_long	flags;
	db_uint	cachesize;	/* bytes to cache */
	int	maxkeypage;	/* maximum keys per page */
	int	minkeypage;	/* minimum keys per page */
	db_uint	psize;		/* page size */
	int	(*compare)	/* comparison function */
	    __P((const DBT *, const DBT *));
	size_t	(*prefix)	/* prefix function */
	    __P((const DBT *, const DBT *));
	int	lorder;		/* byte order */
} BTREEINFO;

#define	HASHMAGIC	0x061561
#define	HASHVERSION	2

/* Structure used to pass parameters to the hashing routines. */
typedef struct {
	db_uint	bsize;		/* bucket size */
	db_uint	ffactor;	/* fill factor */
	db_uint	nelem;		/* number of elements */
	db_uint	cachesize;	/* bytes to cache */
	db_uint32_t		/* hash function */
		(*hash) __P((const void *, size_t));
	int	lorder;		/* byte order */
} HASHINFO;

/* Structure used to pass parameters to the record routines. */
typedef struct {
#define	R_FIXEDLEN      0x01      /* fixed-length records */
#define	R_NOKEY         0x02      /* key not required */
#define	R_SNAPSHOT      0x04      /* snapshot the input */
	u_long         flags;
	db_uint        cachesize; /* bytes to cache */
	db_uint        psize;     /* page size */
	int            lorder;    /* byte order */
	size_t         reclen;    /* record length (fixed-length records) */
	db_uchar       bval;      /* delimiting byte (variable-length records */
	char           *bfname;   /* btree file name */
} RECNOINFO;

DB *dbopen __P((const char *, int, int, DBTYPE, const void *));

#ifdef __DBINTERFACE_PRIVATE
DB	*__bt_open __P((const char *, int, int, const BTREEINFO *, int));
DB	*__hash_open __P((const char *, int, int, const HASHINFO *, int));
DB	*__rec_open __P((const char *, int, int, const RECNOINFO *, int));
void	 __dbpanic __P((DB *dbp));
#endif

__END_DECLS

#endif /* !_DB_H_ */
