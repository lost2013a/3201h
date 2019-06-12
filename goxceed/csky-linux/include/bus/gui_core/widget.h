#ifndef __WIDGET_H__
#define __WIDGET_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "gui_hash.h"
#include "gxcore.h"
#include "IMG.h"

__BEGIN_DECLS

#define WIDGET_STATE_FOCUSED    (1<<0)
#define WIDGET_STATE_FOCUSSABLE (1<<1)
#define WIDGET_STATE_HIDE       (1<<2)
#define WIDGET_STATE_DISABLE    (1<<3)


#define WIDGET_SET_PROPERTY(pwidget, property, value) do {   \
	if (pwidget && pwidget->ops && pwidget->ops->set)    \
		pwidget->ops->set(pwidget, property, value); \
} while(0)


#define WIDGET_IS_BOXITEM(pwidget)   ((pwidget) && (strcasecmp(pwidget->classname, "boxitem") == 0))
#define WIDGET_IS_WINDOW(pwidget)    ((pwidget) && (strcasecmp(pwidget->classname, "window") == 0))
#define WIDGET_ISNOT_WINDOW(pwidget) ((pwidget) && (strcasecmp(pwidget->classname, "window")))
#define WIDGET_IS_ROOT(pwidget)      ((pwidget) && (pwidget == gui.root_widget))
#define WIDGET_ISNOT_ROOT(pwidget)   ((pwidget) && (pwidget != gui.root_widget))
#define WIDGET_IS_HIDE(pwidget)      ((pwidget) && (pwidget->state & WIDGET_STATE_HIDE))
#define WIDGET_ISNOT_HIDE(pwidget)   ((pwidget) && ((pwidget->state & WIDGET_STATE_HIDE) == 0))

#define WIDGET_CHECK_OBJECT(self, data, obj, obj_type) do { \
	if((NULL == self) || (NULL == data))    \
		return (EVENT_TRANSFER_STOP);   \
	obj = (obj_type*)(self->object);        \
	if(NULL == obj)                         \
		return (EVENT_TRANSFER_STOP);   \
}while (0)

#define WIDGET_CHECK_RECT(dst_rect, src_rect) \
    if((dst_rect.x < src_rect.x) || (dst_rect.y < src_rect.y) \
       || (dst_rect.w > src_rect.w) || (dst_rect.h > src_rect.h)) return (1)

#define WIDGET_ADJUST_ACCORDING_PARENT(parent, self) \
	if(parent) { \
		self->rect.x += parent->rect.x; \
		self->rect.y += parent->rect.y; \
	}

enum {
    EVENT_TRANSFER_STOP = 0,
    EVENT_TRANSFER_KEEPON = 1
};

typedef struct _GuiWidget GuiWidget;



typedef struct GUI_Rect {
    int x, y;
    int w, h;
} GUI_Rect;

typedef struct _GuiWidgetOps {
    const char *owner;
    void* (*create)(GuiWidget *self);
    int (*release)(GuiWidget *self);
    int (*prepare_image)(GuiWidget *self); // 准备图片资源
    int (*draw)(GuiWidget *self);          // 将图片资源清空( 指针赋空 )
    int (*update)(GuiWidget *self, GUI_Rect *rect);
    int (*clear_image)(GuiWidget *self);
    int (*event)(GuiWidget *self, void *data);
    int (*set)(GuiWidget *self, char *name, void *data);
    int (*get)(GuiWidget *self, char *name, void *data);

    struct _GuiWidgetOps *next;
}GuiWidgetOps;

struct _GuiWidget {
    char *name;
    char *classname;
    char *stylename;
    char *xml_filename;
    int fore_color[3];
    int back_color[3];

    unsigned int state;
    char need_update;
    GUI_Rect rect;
    GUI_Rect string_rect;
    hash_t* property;
    hash_t* signal;
    struct _GuiWidget *parent;
    struct _GuiWidget *first_child;
    struct _GuiWidget *last_child;
    struct _GuiWidget *prior_sibling;
    struct _GuiWidget *next_sibling;
    GuiWidgetOps *ops;
    void *object;
	void *usr_data;
    int init;
    handle_t widget_mutex;
};


typedef int (*GuiSignalFunc)(const char* widgetname, void *userdata);

typedef struct _GuiSignal {
    GuiSignalFunc handler;
    void *userdata;
}GuiSignal;

typedef struct _GuiWidgetSignal {
    char* handler_name;
    GuiSignal* signal;
}GuiWidgetSignal;

typedef struct _ListItemPara {
    int x_offset;
    int sel;
    char *string;
    char *image;
    char *fore_color;
    char *back_color;
    char *font;
    struct _ListItemPara *next;
}ListItemPara;

typedef struct _TimeItemPara {
    int sel;
    int from_start;
    char *string;
}TimeItemPara;


typedef struct _SpectrumInfo {
	int channal_num;
	int value;
	int need_update;
	struct _SpectrumInfo *next;
}SpectrumInfo;

typedef struct _GuiUpdatePixel {
	int x;
	int y;
	char* color;
	int real_color;
}GuiUpdatePixel;

typedef struct _GuiUpdateRect {
	int x;
	int y;
	int w;
	int h;
	char* color;
	int real_color;
}GuiUpdateRect;

typedef struct _GuiUpdateImage {
	int x;
	int y;
	int width;
	int height;
	char *name;
}GuiUpdateImage;

typedef struct _GuiUpdateImageFile {
    int x;
    int y;
    int width;
    int height;
    char *path;
}GuiUpdateImageFile;

typedef struct _GuiUpdateString {
    int x;
    int y;
    int xsize;
    int ysize;
    int length;
    int color;
    int inter_char;
    int inter_line;
    char *alignment;
    char *string;
}GuiUpdateString;

typedef struct _GuiGetString {
    char *string;
    int height;
    int width;
}GuiGetString;


int check_rect_not_zero(GUI_Rect *rect);
int stringlist_index(const char **list, const char *name);

void *widget_create(GuiWidget *widget);
int widget_draw(GuiWidget *widget);
int widget_update(GuiWidget *widget, GUI_Rect *rect);
int widget_release(GuiWidget *widget);


GuiWidget *widget_new(const char *name, const char *type, const char *style);
status_t widget_destroy(GuiWidget *widget);
int widget_del(GuiWidget *widget);
int widget_del_tree(GuiWidget *widget);


GuiWidget *widget_new_child(GuiWidget *parent, const char *name, const char *type, const char *style);
int widget_add_child(GuiWidget *widget, GuiWidget *child);
int widget_del_child(GuiWidget *widget, const char *name);
GuiWidget *widget_rename(const char *name, const char* new_name);

int widget_get_int(GuiWidget *widget, const char *name, int defult);
int widget_get_alignment(GuiWidget *widget);
GuiWidget *widget_get_parent(GuiWidget *widget);
GuiWidget *widget_get_firstchild(GuiWidget *widget);
GuiWidget *widget_get_lastchild(GuiWidget *widget);
GuiWidget *widget_get_priorsibling(GuiWidget *widget);
GuiWidget *widget_get_nextsibling(GuiWidget *widget);
const char *widget_get_name(GuiWidget *widget);
int widget_get_rect(GuiWidget *widget, GUI_Rect *rect);
int widget_get_state_index(GuiWidget* widget);
int widget_get_focussable(GuiWidget* widget);
GuiWidget* widget_get_window(GuiWidget* widget);


void widget_children_set_update(GuiWidget *widget, int update);
void widget_set_update(GuiWidget *widget, int update);
void widget_set_virtual_focus(GuiWidget *widget);
int widget_get_update(GuiWidget *widget);
int widget_set_property(GuiWidget *widget, const char *name, const char *value);
const char *widget_get_property(GuiWidget *widget, const char *name);
const GuiWidget *widget_get_style(const char *name);
const char *widget_get_signal(GuiWidget *widget, const char *signal_name);

int widget_exec_event(GuiWidget *widget, void *usrdata);


int widget_register_widget(const char *widget_type);
int widget_register(const char *widget_name, GuiWidgetOps *ops);
void widget_ops_init(void);
void widget_ops_clean(void);
GuiWidgetOps* widget_get_ops(const char* type);


int widget_notify_parent(GuiWidget *widget, void *data);
int widget_notify_root(GuiWidget* widget, void* data);
int widget_notify_top(GuiWidget* widget, void* data);

int widget_string_alignment(int alignment,
                          int text_len,
                          int font_height,
                          GUI_Rect *src_rect,
                          GUI_Rect *dst_rect);


void* widget_signal_new(GuiWidget *widget, const char *name, const char *handler);
void* gui_signal_new(const char *handlername, GuiSignalFunc func, void *userdata);


int exec_widget_signal_data(GuiWidget *widget, const char *signal_name, void *userdata);
int exec_widget_event_data(GuiWidget *widget, GuiWidgetSignal *signal, void *userdata);


GuiWidget *gui_get_window(const char *name);
GuiWidget *gui_get_widget(GuiWidget *widget, const char *name);
image_desc *widget_img_load(const char* img_id);
int widget_img_clear(image_desc **desc);
GuiWidget *widget_load_from_xml(const unsigned char* string);

__END_DECLS

#endif

