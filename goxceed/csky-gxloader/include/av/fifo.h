#ifndef GXAV_FIFO_H
#define GXAV_FIFO_H

#include "plist.h"

struct gxfifo {
	unsigned char   *data;
	unsigned int    size;
	unsigned int    pread;
	unsigned int    pwrite;
	int malloced;
	int  (*put_callback)(void*);
	void *put_data;
	int  (*get_callback)(void*);
	void *get_data;

	struct plist plist;
};

int gxfifo_init (struct gxfifo *fifo, void *buffer, unsigned int size);
unsigned int gxfifo_put     (struct gxfifo *fifo, void *buf, unsigned int len);
unsigned int gxfifo_get     (struct gxfifo *fifo, void *buf, unsigned int len);
unsigned int gxfifo_user_get(struct gxfifo *fifo, void *buf, unsigned int len);
unsigned int gxfifo_peek    (struct gxfifo *fifo, void *buf, unsigned int len, unsigned int off);
unsigned int gxfifo_len     (struct gxfifo *fifo);
unsigned int gxfifo_is_full (struct gxfifo *fifo);
unsigned int gxfifo_is_empty(struct gxfifo *fifo);
unsigned int gxfifo_freelen (struct gxfifo *fifo);
void gxfifo_free  (struct gxfifo *fifo);
void gxfifo_reset (struct gxfifo *fifo);
void gxfifo_flush (struct gxfifo *fifo);

static inline void gxfifo_set_put_func(struct gxfifo *pfifo, int (*func)(void*), void *args) {
	if (pfifo) {
		pfifo->put_callback = func;
		pfifo->put_data = args;
	}
}

static inline void gxfifo_set_get_func(struct gxfifo *pfifo, int (*func)(void*), void *args) {
	if (pfifo) {
		pfifo->get_callback = func;
		pfifo->get_data = args;
	}
}

#endif
