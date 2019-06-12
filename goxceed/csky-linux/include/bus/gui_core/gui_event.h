#ifndef __GUI_EVENT_H__
#define __GUI_EVENT_H__

/* Event enumerations */
enum {
	GUI_NOEVENT = 0,     /* Unused (do not remove) */
	GUI_ACTIVEEVENT,     /* Application loses/gains visibility */
	GUI_KEYDOWN,         /* Keys pressed */
	GUI_KEYUP,           /* Keys released */
	GUI_MOUSEMOTION,     /* Mouse moved */
	GUI_MOUSEBUTTONDOWN, /* Mouse button pressed */
	GUI_MOUSEBUTTONUP,   /* Mouse button released */
	GUI_JOYAXISMOTION,   /* Joystick axis motion */
	GUI_JOYBALLMOTION,   /* Joystick trackball motion */
	GUI_JOYHATMOTION,    /* Joystick hat position change */
	GUI_JOYBUTTONDOWN,   /* Joystick button pressed */
	GUI_JOYBUTTONUP,     /* Joystick button released */
	GUI_QUIT,            /* User-requested quit */
	GUI_SYSWMEVENT,      /* System specific event */
	GUI_EVENT_RESERVEDA, /* Reserved for future use.. */
	GUI_EVENT_RESERVEDB, /* Reserved for future use.. */
	GUI_VIDEORESIZE,     /* User resized video mode */
	GUI_VIDEOEXPOSE,     /* Screen needs to be redrawn */
	GUI_EVENT_RESERVED2, /* Reserved for future use.. */
	GUI_EVENT_RESERVED3, /* Reserved for future use.. */
	GUI_EVENT_RESERVED4, /* Reserved for future use.. */
	GUI_EVENT_RESERVED5, /* Reserved for future use.. */
	GUI_EVENT_RESERVED6, /* Reserved for future use.. */
	GUI_EVENT_RESERVED7, /* Reserved for future use.. */
	                     /* Events SDL_USEREVENT through SDL_MAXEVENTS-1 are for your use */
	GUI_USEREVENT = 24,
	GUI_SERVICE_MSG,//zfz20090928
	/* This last event is only for bounding internal arrays
	 * It is the number of bits in the event mask datatype -- Uint32
	 */
	GUI_NUMEVENTS = 32
};

typedef struct _GUI_Key {
	unsigned char type;
	unsigned int scancode;
	unsigned short sym;
} GUI_Key;

typedef struct _GUI_MouseMotion {
	unsigned char type;  /* SDL_MOUSEMOTION */
	unsigned char which; /* The mouse device index */
	unsigned char state; /* The current button state */
	unsigned short x, y; /* The X/Y coordinates of the mouse */
	short xrel;          /* The relative motion in the X direction */
	short yrel;          /* The relative motion in the Y direction */
} GUI_MouseMotion;

typedef struct _GUI_MouseButton {
	unsigned char type;   /* SDL_MOUSEBUTTONDOWN or SDL_MOUSEBUTTONUP */
	unsigned char which;  /* The mouse device index */
	unsigned char button; /* The mouse button index */
	unsigned char state;  /* SDL_PRESSED or SDL_RELEASED */
	unsigned short x, y;  /* The X/Y coordinates of the mouse at press time */
} GUI_MouseButton;

typedef struct {
	unsigned char type;
	void* service_msg;
} GUI_ServiceMsg;

typedef union {
	unsigned char type;
	GUI_Key key;
	GUI_MouseMotion motion;
	GUI_MouseButton button;
	GUI_ServiceMsg msg;
} GUI_Event;

#endif

