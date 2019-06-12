#ifndef GUI_HASH_H
#define GUI_HASH_H

//#include "memtest.h"

typedef struct _GxHash GxHash;
typedef void (*GxHashFreeFunc)(void *p);

#ifdef __cplusplus
extern "C" {
#endif

/** allocate and initialize a new hash table */
GxHash *GxHashNew(int size, GxHashFreeFunc freefunc);

/** allocate a new reference to an existing hash table */
GxHash *GxHashClone(GxHash *table);

/** release a hash table when no longer needed */
void GxHashRelease(GxHash *table);

/** add a key, value pair to a hash table.
 *  each key can appear only once; the value of any
 *  identical key will be replaced
 */
int GxHashAdd(GxHash *table, const char *key, void *data);

/** look up a key in a hash table */
void *GxHashGet(GxHash *table, const char *key);

/** delete a key from a hash table */
int GxHashDrop(GxHash *table, const char *key);

/** return the number of keys in a hash */
int GxHashNumKeys(GxHash *table);

/** hash key iterator functions */
typedef struct _GxHashIterator GxHashIterator;

/** allocate and initialize a new iterator */
GxHashIterator *GxHashIterNew(GxHash *table);

/** release an iterator that is no longer needed */
void GxHashIterRelease(GxHashIterator *iter);

/** return the next hash table key from the iterator.
    the returned key should not be freed */
const char *GxHashIterNext(GxHashIterator *iter);

void *GxHashIteratorGetData(GxHashIterator *iter);

int GxHashIterSetData(GxHashIterator *iter, void *data);

#ifdef __cplusplus
}
#endif
#endif /* __LIBXMPPP_HASH_H__ */

