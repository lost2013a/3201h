#ifndef _GUI_TIMER_H__
#define _GUI_TIMER_H__

#include <stdio.h>
#include <stdlib.h>

//#include "SDL.h"
//#include <wchar.h>

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "gxcore.h"

__BEGIN_DECLS

typedef enum {
	TIMER_ONCE,
	TIMER_REPEAT,
	TIMER_REPEAT_NOW
}TIMER_FLAG;

typedef int (*timer_event) (void *userdata);

typedef struct eventlist{
	timer_event  event;
	void*        data;
	int trigger_time;
	int delta_time;
	int flag;
	int active;
	struct eventlist* next;
}event_list;

event_list* create_timer(timer_event event, int time, void *data,  TIMER_FLAG flag);
int reset_timer(event_list *pTimer);
int remove_timer(event_list *pTimer);
int timer_exec(void);
int timer_stop(event_list *pTimer);
int remove_timer_list(void);
void gui_delay(unsigned int ms);

__END_DECLS

#endif

