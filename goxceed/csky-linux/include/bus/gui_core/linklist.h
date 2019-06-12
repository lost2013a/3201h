#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#ifdef __cplusplus
extern "C" {
#endif

#define ElemType void*
#define Q (*qe)

typedef struct quenode {
	ElemType data;
	struct quenode *next;
}quenode_t;

typedef struct quefr {
	int count;
	struct quenode *front;
	struct quenode *rear;
}quefr_t;

typedef void (*linklist_free_func)(void *p);

quefr_t *linklist_new(quefr_t *qe);
void linklist_insert(quefr_t *qe, ElemType x);
ElemType linklist_delete(quefr_t *qe);

quenode_t *linklist_get_front(quefr_t *qe);
quenode_t *linklist_get_rear(quefr_t *qe);
int linklist_get_count(quefr_t *qe);

void linklist_set_front(quefr_t *qe, quenode_t *front);
void linklist_set_rear(quefr_t *qe, quenode_t *rear);
void linklist_set_count(quefr_t *qe, int count);

void linklist_clear(quefr_t *qe);
void linklist_delete_all(quefr_t *qe, linklist_free_func fun);
void linklist_release(quefr_t **qe, linklist_free_func fun);

#ifdef __cplusplus
}
#endif

#endif


