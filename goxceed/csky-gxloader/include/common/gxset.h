#ifndef _GX_SET_H_
#define _GX_SET_H_

#define KSET_DEF(t)                    \
struct {                               \
	int             id;            \
	int             max_count;     \
	int             size;          \
	t*              data;          \
} 

#define gxset_get(set, i)  (set).data[i]
#define gxset_getp(set,i)  ((set).data + i)
#define gxset_inc(set)     gxset_resize(set, (set).max_count+1)
#define gxset_tail(set)    (set).data[(set).id-1]
#define gxset_count(set)   (set).id

#define gxset_for_each(pos, set)                          \
	for (pos = 0; pos < (set).id; pos++)

#define gxset_init(set, c, s) do {                        \
	(set).id        = 0;                              \
	(set).max_count = (c);                            \
	(set).size      = (s);                            \
                                                          \
	if ((c)> 0)                                       \
		(set).data = malloc((c)* (s));            \
	else                                              \
		(set).data = NULL;                        \
}while(0)

#define gxset_resize(set, c) do {                         \
	(set).max_count = (c);                            \
	(set).data = realloc((set).data, (c)* (set).size);\
	if ((c) <= (set).id)                              \
		(set).id = (c) - 1;                       \
}while(0)


#define gxset_add(set, d) do {                            \
	if ((set).id >= (set).max_count)                  \
		gxset_resize(set, (set).id + 1);          \
	(set).data[(set).id] = (d);                       \
	(set).id++;                                       \
}while(0)

#define gxset_del(set, i) do {                            \
	if ( (i) < (set).id) {                            \
		memmove(&(set).data[i],&(set).data[(i)+1],\
			((set).id-(i)-1) * (set).size);   \
		(set).id--;                               \
	}                                                 \
}while(0)

#define gxset_del_v(set, v) do {                          \
	int i;                                            \
	gxset_for_each(i, set)                            \
	{                                                 \
		if ((set).data[i] == (v))                 \
		{                                         \
			gxset_del(set, i);                \
			break;                            \
		}                                         \
	}                                                 \
}while(0)

#define gxset_free(set) do {                              \
	if ((set).data) {                                 \
		free((set).data);                         \
		(set).data = NULL;                        \
	}                                                 \
}while(0)

#endif

