#ifndef _LIST_H_
#define _LIST_H_

#include <common/config.h>

__BEGIN_DECLS

struct gxlist_head
{
    struct gxlist_head *next, *prev;
};

#define GX_LIST_HEAD_INIT(name) { &(name), &(name) }

#define GX_LIST_HEAD(name) \
	struct gxlist_head name = GX_LIST_HEAD_INIT(name)

#define GX_INIT_LIST_HEAD(ptr) do { \
	(ptr)->next = (ptr); (ptr)->prev = (ptr); \
} while (0)

void gxlist_add     (struct gxlist_head *newnode, struct gxlist_head *head);
void gxlist_add_tail(struct gxlist_head *newnode, struct gxlist_head *head);
void gxlist_del     (struct gxlist_head *entry);
void gxlist_del_init(struct gxlist_head *entry);
int  gxlist_empty   (struct gxlist_head *head );
void gxlist_splice  (struct gxlist_head *list, struct gxlist_head *head);

struct gxlist_head *gxlist_get(struct gxlist_head *head);

#define gxlist_entry(ptr, type, member) \
	((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))

#define gxlist_for_each(pos, head) \
	for (pos = (head)->next; pos != (head); \
			pos = pos->next)

#define gxlist_for_each_entry(pos, head, member)                            \
	for (pos = gxlist_entry((head)->next, typeof(*pos), member);        \
			&pos->member != (head);                                     \
			pos = gxlist_entry(pos->member.next, typeof(*pos), member))

#define gxlist_for_each_safe(pos, n, head) \
	for (pos = (head)->next, n = pos->next; pos != (head); \
			pos = n, n = pos->next)

#define gxlist_for_each_entry_safe(pos, n, head, member)                           \
	for (pos = gxlist_entry((head)->next, typeof(*pos), member),               \
			n = gxlist_entry(pos->member.next, typeof(*pos), member);  \
			&pos->member != (head);                                    \
			pos = n, n = gxlist_entry(n->member.next, typeof(*n), member))

__END_DECLS

#endif
