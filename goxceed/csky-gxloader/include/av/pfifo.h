#ifndef GXAV_PFIFO_H
#define GXAV_PFIFO_H

struct pfifo {
	unsigned char *data;
	unsigned int  size;
	unsigned int  pread;
	unsigned int  pwrite;
	unsigned int  malloced;
};

unsigned int pfifo_init    (struct pfifo *fifo, void *buffer, unsigned int size);
unsigned int pfifo_put     (struct pfifo *fifo, void *buf, unsigned int len);
unsigned int pfifo_get     (struct pfifo *fifo, void *buf, unsigned int len);
unsigned int pfifo_peek    (struct pfifo *fifo, void *buf, unsigned int len);
unsigned int pfifo_len     (struct pfifo *fifo);
unsigned int pfifo_is_full (struct pfifo *fifo);
unsigned int pfifo_is_empty(struct pfifo *fifo);
unsigned int pfifo_freelen (struct pfifo *fifo);
void pfifo_free  (struct pfifo *fifo);
void pfifo_reset (struct pfifo *fifo);
void pfifo_flush (struct pfifo *fifo);


#endif
