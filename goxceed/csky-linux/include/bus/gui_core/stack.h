#ifndef STACK_H
#define STACK_H

#include "gxcore.h"

__BEGIN_DECLS

#define G_STACK_SIZE 40

#define G_STACK_OK   0
#define G_STACK_FULL 1

typedef struct stack_tag
{
	void *stack[G_STACK_SIZE];
	int stack_pointer;
} gx_stack_t;

gx_stack_t *stack_new(gx_stack_t *s);
void stack_release(gx_stack_t *s);

void *stack_pop (gx_stack_t *s);
void *stack_peek(gx_stack_t *s);
void *stack_get (gx_stack_t *stack, int id);
int stack_push  (gx_stack_t *s, void *item);
int stack_count (gx_stack_t *s);
void *stack_del(gx_stack_t *stack, int id);//zhaofz20090925
int stack_get_id(gx_stack_t *stack, void* value);//zhaofz20090925

__END_DECLS

#endif
