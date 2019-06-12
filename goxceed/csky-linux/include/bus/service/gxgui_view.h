#ifndef __GX_GUI_VIEW__
#define __GX_GUI_VIEW__

#include "gxbus.h"
#include "gxtype.h"
#include "gxcore.h"
#include "gui_core/gdi_core.h"
#include "gui_core/gui_core.h"

__BEGIN_DECLS

#define GUI_DEFAULT_MESSAGE_SINGLE  "default_prompt_message_single_style"
#define GUI_DEFAULT_MESSAGE_DOUBLE  "default_prompt_message_double_style"
#define GUI_DEFAULT_MESSAGE_NOTICE  "default_prompt_message_notice_style"

typedef struct {
	status_t (*app_msg_init)(handle_t self);
	status_t (*app_msg_destroy)(handle_t self);
	status_t (*app_init)(void);
} GuiViewAppCallback;

typedef enum {
	GXGUI_STATUS_NOTICE,
	GXGUI_STATUS_SINGLE_BUTTON,
	GXGUI_STATUS_DOUBLE_BUTTON,
	GXGUI_STATUS_RETURN_NOTICE
} GxGUI_StatusType;

typedef struct {
	GxGUI_StatusType  type;
	uint8_t          *warning_string;
	uint8_t          *return_string0;
	uint8_t          *return_string1;
} GxMsgProperty_GUI_Warning;

typedef struct {
	GxGUI_StatusType  type;
	uint8_t          *src_string;
	uint8_t          *return_string;
} GxMsgProperty_GUI_Return_Message;

status_t GxGuiViewRegisterApp(GuiViewAppCallback* cb);

__END_DECLS

#endif

