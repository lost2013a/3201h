#ifndef __GUI_HASH_H__
#define __GUI_HASH_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gxcore.h"

__BEGIN_DECLS

typedef void (*hash_free_func)(void *p);

typedef struct _hashentry_t{
	char *key;
	void *value;
	struct _hashentry_t *next;
}hashentry_t;

typedef struct _hash_t{
	unsigned int ref;
	hash_free_func freefunc;
	int length;
	int num_keys;
	hashentry_t **entries;
}hash_t;

typedef struct _hash_iterator_t{
	unsigned int ref;
	hash_t *table;
	hashentry_t *entry;
	int index;
}hash_iterator_t;

hash_t *hash_new(int size, hash_free_func freefunc);
hash_t *hash_clone(hash_t *table);
int hash_release(hash_t *table);
int hash_add(hash_t *table, const char *key, void *data);
void* hash_get(hash_t *table, const char *key);
int hash_drop(hash_t *table, const char *key);
int hash_num_keys(hash_t *table);
hash_iterator_t *hash_iter_new(hash_t *table);
int hash_iter_release(hash_iterator_t *iter);
const char *hash_iter_next(hash_iterator_t *iter);
int hash_iter_set_data(hash_iterator_t *iter, void *data);
void *hash_iter_get_data(hash_iterator_t *iter);

__END_DECLS

#endif
