#ifndef __SUB_DEF_H__
#define __SUB_DEF_H__

#include "gxcore.h"

__BEGIN_DECLS

typedef enum {
	SUBT_TIMER_ONCE,
	SUBT_TIMER_REPEAT
} SUBT_TIMER_FLAG;

typedef int (*subt_timer_event) (void *userdata);

typedef struct subteventlist {
	subt_timer_event  event;
	void*        data;
	int trigger_time;
	int delta_time;
	int flag;
	int active;
	struct subteventlist* next;
} subt_event_list;


typedef struct {
	subt_event_list* (*create)  (subt_timer_event event, int time, void *data,  SUBT_TIMER_FLAG flag);
	int32_t     (*reset)        (subt_event_list *pTimer);
	int32_t     (*stop)         (subt_event_list *pTimer);
	int32_t     (*remove)       (subt_event_list *pTimer);
	int32_t     (*removall)     (void);
	void        (*delayms)      (uint32_t ms);
	int32_t     (*exec)         (void);
} GxSubtitle_TimerOps;

typedef struct {
	handle_t                handle;
	GxSubtitle_TimerOps*  ops;
} GxSubtitle_Timer;


typedef struct {
	handle_t    (*open)     (uint32_t demux_id);
	int32_t     (*close)    (handle_t handle);
	int32_t     (*start)    (handle_t handle);
	int32_t     (*stop)     (handle_t handle);
	int64_t     (*get_stc)  (handle_t handle);
	int32_t     (*set_pid)  (handle_t handle, uint16_t pid);

	size_t      (*get_pes)  (handle_t handle, uint8_t** ptr, size_t size);
	uint8_t     (*nextbyte) (handle_t handle);
	void        (*skipbytes)(handle_t handle, uint16_t size);
	void        (*copybytes)(handle_t handle, uint8_t* ptr, uint16_t size);
	uint8_t     (*get2bits) (handle_t handle, uint8_t* ptr, uint32_t* index);
	uint32_t    (*alignbyte)(handle_t handle, uint32_t index);
} GxSubtitle_DemuxOps;

typedef struct  {
	handle_t                handle;
	GxSubtitle_DemuxOps*    ops;
} GxSubtitle_demux;

typedef struct {
	uint16_t                x;
	uint16_t                y;
	uint16_t                width;
	uint16_t                heigth;
} GxSubtitle_RenderRect;

typedef struct {
	uint16_t                x;
	uint16_t                y;
} GxSubtitle_RenderPoint;

typedef struct {
	GxSubtitle_RenderPoint  start_point;
	uint16_t                len;
	uint16_t                thickness;
} GxSubtitle_RenderLine;

typedef struct {
	uint8_t            y;
	uint8_t            cb;
	uint8_t            cr;
	uint8_t            t;
} GxSubtitle_YCC;

typedef struct {
	uint8_t            r;
	uint8_t            g;
	uint8_t            b;
	uint8_t            t;
} GxSubtitle_RGB;

typedef struct {
	union color_format {
		uint32_t       value;
		GxSubtitle_YCC ycc;
		GxSubtitle_RGB rgb;
	}color;
} GxSubtitle_RenderColor;

typedef struct {
	uint8_t                 clut_id;
	GxSubtitle_RenderColor  entries_list[256];
} GxSubtitle_RenderClut;

typedef struct {
	handle_t    (*open)         (GxSubtitle_RenderRect* rect);
	int32_t     (*close)        (handle_t handle);
	int32_t     (*set_color)    (handle_t handle, uint8_t color_index, GxSubtitle_RenderColor* color);
	int32_t     (*clear)        (handle_t handle);
	int32_t     (*show)         (handle_t handle);
	int32_t     (*hide)         (handle_t handle);
	int32_t     (*fill_region)  (handle_t handle, GxSubtitle_RenderRect* rect, uint8_t color_index);
	int32_t     (*draw_line)    (handle_t handle, GxSubtitle_RenderLine* l, uint8_t color_index);
	void        (*set_ntsc)     (handle_t handle, bool flag);
	bool        (*get_ntsc)     (handle_t handle);
	void*       (*get_buf)      (handle_t handle);
	int32_t     (*change_buf)   (handle_t handle, GxSubtitle_RenderRect* rect);
	GxSubtitle_RenderRect*    (*get_rect)(handle_t handle);
} GxSubtitle_RenderOps;

typedef struct  {
	handle_t                handle;
	GxSubtitle_RenderOps*   ops;
} GxSubtitle_Render;

typedef struct {
	handle_t    (*open)         (GxSubtitle_Render* render, GxSubtitle_Timer* timer);
	int32_t     (*close)        (handle_t handle);
	int32_t     (*start)        (handle_t handle);
	int32_t     (*stop)         (handle_t handle);
	int32_t     (*synchronize)  (handle_t handle, int32_t milliseconds);
	int32_t     (*set_stream)   (handle_t handle, uint16_t comp_page_id, uint16_t anci_page_id);
	int32_t     (*decode)       (handle_t handle, uint8_t* packet, int total_size);
	int32_t     (*render)       (handle_t handle);
} GxSubtitle_DecoderOps;

typedef struct {
	handle_t                handle;
	GxSubtitle_DecoderOps*  ops;
} GxSubtitle_Decoder;


typedef struct {
	volatile bool           decoding;
	volatile bool           rendering;
	volatile bool           timing;
	handle_t                render_thread;
	handle_t                timer_thread;
	GxSubtitle_Render       render;
	GxSubtitle_Decoder      decoder;
	GxSubtitle_Timer        timer;
} GxSubtitle_Info;

__END_DECLS

#endif

