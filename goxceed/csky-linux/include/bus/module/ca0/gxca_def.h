#ifndef __GXCA_DEF_H__
#define __GXCA_DEF_H__

#include "gxcore.h"

__BEGIN_DECLS

/**CASÃû³Æ*/
#define GXCA_NAME_SIZE          (32)

#ifndef E_OK
#define E_OK                    (0)
#endif
#ifndef E_FAILURE
#define E_FAILURE               (-1)
#endif
#ifndef E_INVALID_HANDLE
#define E_INVALID_HANDLE        (0)
#endif

typedef struct {
	char        name[GXCA_NAME_SIZE];
	handle_t    (*open)(const char* name);
	int         (*close)(void);
	int         (*ioctl)(handle_t handle, int key, void* buf, size_t size);
} GxCA_System;

__END_DECLS

#endif
