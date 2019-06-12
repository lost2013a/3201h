#ifndef __GUI_CORE_H__
#define __GUI_CORE_H__

#include "gxtype.h"
#include "gxcore.h"

#include "types.h"
#include "widget.h"
#include "stack.h"
#include "linklist.h"
#include "gui_event.h"
#include "gui_key.h"
#include "gui_timer.h"
#include "gui_hash.h"
#include "framebuffer.h"
#include "gui_pool.h"

__BEGIN_DECLS

#if 1
extern GuiPool gui_pool;
#define GUI_STRDUP(str) GuiPool_Strdup(&gui_pool, str)
#define GUI_MALLOC(size)  GuiPool_Alloc(&gui_pool, size)
#define GUI_MALLOCZ(size) GuiPool_Allocz(&gui_pool, size)
#define GUI_REALLOC(ptr, size) GuiPool_Realloc(&gui_pool, ptr, size)
#define GUI_FREE(p) if(p) {GuiPool_Free(&gui_pool, p); p = NULL;}
#else
#define GUI_STRDUP(str)   GxCore_Strdup(str)
#define GUI_MALLOC(size)  GxCore_Malloc(size)
#define GUI_MALLOCZ(size) GxCore_Mallocz(size)
#define GUI_REALLOC(ptr, size) GxCore_Realloc(ptr, size)
#define GUI_FREE(p) if(p) {GxCore_Free(p); p = NULL;}
#endif

#define WIDGET_IS_FOCUS(name)   ((name)&&(0 == strcasecmp(name, GUI_GetFocusWidget())))
#define WIDGET_ISNOT_FOCUS(name)   ((name)&&(strcasecmp(name, GUI_GetFocusWidget())))

#define SIGNAL_HANDLER
#define SIGNAL_CONNECT(SIGNAL) GUI_SignalConnect(#SIGNAL, SIGNAL);

typedef struct {
	char*       file_xml_config;
	char*       file_xml_keymap;
	char*       file_xml_widget;
	char*       file_xml_style;
	char*       file_xml_color;
	char*       file_xml_i18n;
	char*       file_xml_image;
	char*       file_xml_font;
	char*       file_pal;
}GuiExtFiles;

typedef struct _GuiClut {
	unsigned     int num;
	Color*       palette;
	void*        create_pal;
	struct _GuiClut *next;
}GuiClut;

typedef struct _GuiI18n {
    char*        language;
    hash_t*      hash_text;
    struct _GuiI18n*    next;
}GuiI18n;

typedef struct _GuiColors {
	hash_t*      hash_colors;
}GuiColors;

typedef struct {
	char*        theme_path;
	char*        cur_language;

	int          chip_id;
	int          width;
	int          height;
	int          resolution_width;
	int          resolution_height;
	int	     key_mask;
	int          bpp;
	int          bpp8_multclut;
	int          enable_ga;
	int          enable_i18n;
	int          ga_count;
	int          image_limit;
	int          enable_antiflicker;
	int          enable_double_buffer;
        int          enable_key_shield;
        int          key_shield;

	GuiClut*     clut;
	GuiClut*     firstclut;
	quefr_t*     job_link;
	hash_t*      color_hash;
	Color        osd_trans;
	Color        gui_trans;
	int          osd_alpha;
	int          logical_clut;

	GuiI18n*     i18n;
	GuiI18n*     cur_i18n;

	GuiColors    colors;

	GuiExtFiles  files;
	int          block_join;
	int	          image_buffer_size;
} GuiConfig;

typedef struct _GuiCore {
	GuiConfig    config;

	GuiWidget*   root_widget;
	GuiSignalFunc root_event;
	GuiSignalFunc top_event;

	GuiSignal*   key_process;

	GuiWidget*   freedom_widget;
	GuiWidget*   style_widget;
	GuiWidget*   focus_widget;

	gx_stack_t*  win_stack;
	gx_stack_t*  ontop_stack;

	GUI_Event event_cache;

	int	     image_size;
	//hash_t*      signal_hash;
	void *image_cache;
	struct framebuffer fb;
} GuiCore;

typedef hash_t GuiSignalTable;


status_t GUI_Init(const char* theme_config);
status_t GUI_Quit(void);
status_t GUI_Exec(void);
status_t GUI_Loop(void);
status_t GUI_LoopEvent(void);
void GUI_StartSchedule(void);
status_t GUI_CreateDialog(const char* window_name);
status_t GUI_LinkDialog(const char *window_name, const char *path);
status_t GUI_CheckDialog(const char *window_name);

const char *GUI_CreatePrompt(int x,
                             int y,
                             const char *name,
                             const char *style,
                             const char *string,
                             const char *mode);
status_t GUI_CheckPrompt(const char *name);
status_t GUI_PromptString(const char *name, const char *string);
status_t GUI_EndPrompt(const char *name);

status_t GUI_EndDialog(const char* window_name);
status_t GUI_SetProperty(const char* widget_name, const char* property, void* value);
status_t GUI_GetProperty(const char* widget_name, const char* property, void* value);
status_t GUI_SetFocusWidget(const char* widget_name);
const char* GUI_GetFocusWidget(void);
const char *GUI_GetFocusWindow(void);
const char *GUI_GetPreviousWindow(const char *widget_name);
const char *GUI_GetNextWindow(const char *widget_name);
status_t GUI_SetInterface(const char *property, void *value);
status_t GUI_SignalConnect(const char *handlername, GuiSignalFunc func);
status_t GUI_SetEvent(GUI_Event *event);
status_t GUI_ExecEvent(GUI_Event *event);
status_t GUI_SendEvent(const char *widget_name, GUI_Event* event);
status_t GUI_LoadWidget(const char *file_path);
status_t GUI_RegisterWidget(const char *widget_style);
const char *GUI_GetSignal(const char *widget_name, const char *signal_name);
void GUI_StartSchedule(void);
void GUI_StopSchedule(void);
int gdi_register_gbk(void);
int gdi_register_gb2312(void);
int gdi_register_big5(void);
int gdi_register_ksx(void);
int gdi_set_default_local(char *name);


__END_DECLS

#endif

