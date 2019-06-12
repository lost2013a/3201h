#ifndef __GX_SUBTITLE_H__
#define __GX_SUBTITLE_H__

#include "gxcore.h"
#include "sub_def.h"


__BEGIN_DECLS

#ifndef E_FAILURE
#define E_FAILURE                   -1
#endif
#ifndef E_OK
#define E_OK                        0
#endif
#ifndef E_INVALID_HANDLE
#define E_INVALID_HANDLE            0
#endif

typedef enum {
	GXSUBTITLE_SPP,
	GXSUBTITLE_OSD
} GxSubitle_RenderType;

typedef struct {
	GxSubtitle_RenderRect       render_rect;
	GxSubitle_RenderType        render_type;
} GxSubtitle_Param;

typedef struct {
	uint32_t                    pid;
	uint16_t                    comp_page_id;
	uint16_t                    anci_page_id;
} GxSubtitle_Stream;

handle_t    GxSubtitle_Open         (GxSubtitle_Param* param);
int32_t     GxSubtitle_StreamSet    (handle_t handle, GxSubtitle_Stream* stream);
int32_t     GxSubtitle_Synchronize  (handle_t handle, int32_t milliseconds);
int32_t     GxSubtitle_Close        (handle_t handle);
int32_t     GxSubtitle_Start        (handle_t handle);
int32_t     GxSubtitle_SetNtsc      (handle_t handle, bool flag);
int32_t     GxSubtitle_Stop         (handle_t handle, int freeze);
int32_t     GxSubtitle_Show         (handle_t handle);
int32_t     GxSubtitle_Clear        (handle_t handle);
int32_t     GxSubtitle_Hide         (handle_t handle);
int32_t     GxSubtitle_SendPesData  (handle_t handle, uint8_t* packet, int packet_length);

extern void subt_create_surface(void);

__END_DECLS

#endif
