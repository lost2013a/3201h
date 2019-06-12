#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "common/config.h"
#include "common/byteswap.h"
#include "common/cpuinfo.h"
#include "common/error.h"
#include "common/limits.h"
#include "common/md5.h"
#include "common/rmd160.h"
#include "common/setenv.h"
#include "common/snprintf.h"
#include "common/string_compat.h"
#include "common/vsnprintf.h"
#include "common/vasprintf.h"
#include "common/hash.h"
#include "common/list.h"
#include "common/mempool.h"
#include "common/debug.h"
#include "common/gxmalloc.h"

#include "variant.h"
#include "gxset.h"

__BEGIN_DECLS

#define GX_OBJECT_NAME_MAX        32
#define GX_OBJECT_CLASS_NAME_MAX  32
#define GX_OBJECT_LIBS_MAX       128

#define GXCLASS(obj)        ((struct gx_class *)(obj))
#define GXOBJECT(obj)             ((struct gx_object *)(obj))
#define GetGxClassFromObject(obj) ((struct gx_class *)(GXOBJECT(obj)->cls))

typedef struct gx_class  GxClass;
typedef struct gx_object GxObject;

#define GX_EVENT_NAME_MAX 32
#define GX_EVENT_ARGS_MAX 16

typedef struct gx_event {
	char      name[GX_EVENT_NAME_MAX];
	uint32_t  flags;
#define GX_EVENT_ASYNC      0x01
#define GX_EVENT_PROPAGATE  0x02
#define GX_EVENT_SCHEDULED  0x03

	void*    sender;
	void*    self;

	void     (*handler)(struct gx_event *);

	int      argc;
	GxProp   argv[GX_EVENT_ARGS_MAX];
}GxEvent;

typedef void (*GxEventFn)(GxEvent*);

struct gx_object{
	char              name[GX_OBJECT_NAME_MAX];  /* class name                */
	GxClass*          cls;                       /* class theme style handler */

	GxObject*         parent;                    /* class parent widget       */

	GxObject*         first_child;               /* class first child widget  */
	GxObject*         last_child;                /* class last child widget   */
	GxObject*         prior;
	GxObject*         next;
#ifdef THREADS
//	GxMutex           lock;                      /* General object lock       */
#endif
	int               flags;

	KSET_DEF(GxProp)  props;
	KSET_DEF(GxEvent) events;
};

struct gx_class {
	char                 name[GX_OBJECT_CLASS_NAME_MAX];
	void*                parent;                   /* parent class              */
	size_t               size;                     /* Structure size            */
	KSET_DEF(GxClass*)   subclasses;

//	char                 libs[GX_OBJECT_LIBS_MAX]; /* .so */

	void* (*create)      (GxObject *self);
	void  (*release)     (GxObject *self);
//	int   (*load)        (GxObject *self, GxStream*, const GxVersion *);
//	int   (*save)        (GxObject *self, GxStream*);

	int  (*event)        (GxObject *self, void *userdata);
};


extern GxClass gxRootClass;

void  GxClassInitTable       (void **table);
int   GxClassRegister        (void *obj_class);
int   GxClassUnregister      (void *obj_class);
void* GxClassFindChild       (void *obj_class, const char *subname);
void* GxFindClassByName      (const char *class_name);
void  GxClassPrintTree       (void *obj_class, int depth);
void  GxClassDestroy(void);
#define GxClassGetParentClass(obj) (GXCLASS(obj)->parent)

void* GxObjectNewByClassName (void *parent, const char *name, const char *class_name);
void* GxObjectNew            (const char *name, void *obj_class);
char* GxObjectGenName        (void *p);
void  GxObjectInit           (void *p, void *cl);
void  GxObjectAttach         (void *parentp, void *pChld);
void  GxObjectDetach         (void *childp);
void  GxObjectSetName        (void *p, const char *fmt, ...);
void* GxObjectFindChild      (void *parent, const char *name);
void  GxObjectDestroy        (void *p);

#define GxObjectGetName(p) (((GxObject*)(p))->name)

GxVariant* GxObjectSetProp   (void *p, const char *key, enum gx_variant_type type, ...);
GxVariant* GxObjectGetProp   (void *p, const char *key);

GxEvent*   GxObjectSetEvent  (void *p, const char *event_name, GxEventFn event_fun, const char *fmt, ...);
GxEvent*   GxObjectGetEvent  (void *p, const char *event_name);
void       GxObjectUnsetEvent(void *p, const char *event_name);
void       GxObjectPostEvent (void *sp, void *rp, const char *evname, const char *fmt, ...);

void GxObjectPrintTree(void *p, int depth);

GxVariant* GxObjectSetString (void *, const char *, const char *, ...);
#define GxObjectSetUint(p, k, i)        GxObjectSetProp((p), (k), GX_UINT        , (i))
#define GxObjectSetInt(p, k, i)         GxObjectSetProp((p), (k), GX_INT         , (i))
#define GxObjectSetUint8(p, k, i)       GxObjectSetProp((p), (k), GX_UINT8       , (i))
#define GxObjectSetSint8(p, k, i)       GxObjectSetProp((p), (k), GX_SINT8       , (i))
#define GxObjectSetUint16(p, k, i)      GxObjectSetProp((p), (k), GX_UINT16      , (i))
#define GxObjectSetSint16(p, k, i)      GxObjectSetProp((p), (k), GX_SINT16      , (i))
#define GxObjectSetUint32(p, k, i)      GxObjectSetProp((p), (k), GX_UINT32      , (i))
#define GxObjectSetSint32(p, k, i)      GxObjectSetProp((p), (k), GX_SINT32      , (i))
#define GxObjectSetUint64(p, k, i)      GxObjectSetProp((p), (k), GX_UINT64      , (i))
#define GxObjectSetSint64(p, k, i)      GxObjectSetProp((p), (k), GX_SINT64      , (i))
#define GxObjectSetFloat(p, k, i)       GxObjectSetProp((p), (k), GX_FLOAT       , (i))
#define GxObjectSetDouble(p, k, i)      GxObjectSetProp((p), (k), GX_DOUBLE      , (i))
#define GxObjectSetLongDouble(p, k, i)  GxObjectSetProp((p), (k), GX_LONG_DOUBLE , (i))
#define GxObjectSetPointer(p, k, i)     GxObjectSetProp((p), (k), GX_POINTER     , (i))
#define GxObjectSetBool(p, k, i)        GxObjectSetProp((p), (k), GX_BOOL        , (i))

#define GxObjectGetUint(p, k)           GxGetUint(GxObjectGetProp((p), (k)))
#define GxObjectGetInt(p, k)            GxGetInt(GxObjectGetProp((p), (k)))
#define GxObjectGetUint8(p, k)          GxGetUint8(GxObjectGetProp((p), (k)))
#define GxObjectGetSint8(p, k)          GxGetSint8(GxObjectGetProp((p), (k)))
#define GxObjectGetUint16(p, k)         GxGetUint16(GxObjectGetProp((p), (k))
#define GxObjectGetSint16(p, k)         GxGetSint16(GxObjectGetProp((p), (k)))
#define GxObjectGetUint32(p, k)         GxGetUint32(GxObjectGetProp((p), (k)))
#define GxObjectGetSint32(p, k)         GxGetSint32(GxObjectGetProp((p), (k)))
#define GxObjectGetUint64(p, k)         GxGetUint64(GxObjectGetProp((p), (k)))
#define GxObjectGetSint64(p, k)         GxGetSint64(GxObjectGetProp((p), (k)))
#define GxObjectGetFloat(p, k)          GxGetFloat(GxObjectGetProp((p), (k)))
#define GxObjectGetDouble(p, k)         GxGetDouble(GxObjectGetProp((p), (k)))
#define GxObjectGetLongDouble(p, k)     GxGetLongDouble(GxObjectGetProp((p), ()k))
#define GxObjectGetString(p, k)         GxGetString(GxObjectGetProp((p), (k)))
#define GxObjectGetPointer(p, k)        GxGetPointer(GxObjectGetProp((p), (k)))
#define GxObjectGetBool(p, k)           GxGetBool(GxObjectGetProp((p), (k)))

__END_DECLS

#endif

