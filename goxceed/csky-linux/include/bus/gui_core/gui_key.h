#ifndef __GUI_KEY_H__
#define __GUI_KEY_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "SDL_keysym.h"
#include "gxcore.h"

__BEGIN_DECLS

typedef int (*GuiKeyTranslate)(void *data);

/*Unused*/
#define GUIK_ANY          (-1)
#define GUIK_NULL         (SDLK_UNKNOWN)
#define GUIK_FIRST        (SDLK_FIRST)

/*Esc*/
#define GUIK_ESCAPE       (SDLK_ESCAPE)

/*Function Keys*/
#define GUIK_F1           (SDLK_F1)
#define GUIK_F2           (SDLK_F2)
#define GUIK_F3           (SDLK_F3)
#define GUIK_F4           (SDLK_F4)
#define GUIK_F5           (SDLK_F5)
#define GUIK_F6           (SDLK_F6)
#define GUIK_F7           (SDLK_F7)
#define GUIK_F8           (SDLK_F8)
#define GUIK_F9           (SDLK_F9)
#define GUIK_F10          (SDLK_F10)
#define GUIK_F11          (SDLK_F11)
#define GUIK_F12          (SDLK_F12)

/*Main Keys*/
#define GUIK_BACKQUOTE    (SDLK_BACKQUOTE)
#define GUIK_1            (SDLK_1)
#define GUIK_2            (SDLK_2)
#define GUIK_3            (SDLK_3)
#define GUIK_4            (SDLK_4)
#define GUIK_5            (SDLK_5)
#define GUIK_6            (SDLK_6)
#define GUIK_7            (SDLK_7)
#define GUIK_8            (SDLK_8)
#define GUIK_9            (SDLK_9)
#define GUIK_0            (SDLK_0)
#define GUIK_MINUS        (SDLK_MINUS)
#define GUIK_PLUS         (SDLK_PLUS)
#define GUIK_BACKSPACE    (SDLK_BACKSPACE)

#define GUIK_TAB          (SDLK_TAB)
#define GUIK_Q            (SDLK_q)
#define GUIK_W            (SDLK_w)
#define GUIK_E            (SDLK_e)
#define GUIK_R            (SDLK_r)
#define GUIK_T            (SDLK_t)
#define GUIK_Y            (SDLK_y)
#define GUIK_U            (SDLK_u)
#define GUIK_I            (SDLK_i)
#define GUIK_O            (SDLK_o)
#define GUIK_P            (SDLK_p)
/*[*/
#define GUIK_LEFTBRACKET  (SDLK_LEFTBRACKET)
/*]*/
#define GUIK_RIGHTBRACKET (SDLK_RIGHTBRACKET)
/*Enter*/
#define GUIK_RETURN       (SDLK_RETURN)

#define GUIK_CAPSLOCK     (SDLK_CAPSLOCK)
#define GUIK_A            (SDLK_a)
#define GUIK_S            (SDLK_s)
#define GUIK_D            (SDLK_d)
#define GUIK_F            (SDLK_f)
#define GUIK_G            (SDLK_g)
#define GUIK_H            (SDLK_h)
#define GUIK_J            (SDLK_j)
#define GUIK_K            (SDLK_k)
#define GUIK_L            (SDLK_l)
/*;*/
#define GUIK_SEMICOLON    (SDLK_SEMICOLON)
/*'*/
#define GUIK_QUOTEDBL     (SDLK_QUOTEDBL)
/*\*/
#define GUIK_BACKSLASH    (SDLK_BACKSLASH)

#define GUIK_LSHIFT       (SDLK_LSHIFT)
#define GUIK_Z            (SDLK_z)
#define GUIK_X            (SDLK_x)
#define GUIK_C            (SDLK_c)
#define GUIK_V            (SDLK_v)
#define GUIK_B            (SDLK_b)
#define GUIK_N            (SDLK_n)
#define GUIK_M            (SDLK_m)
/*,*/
#define GUIK_COMMA        (SDLK_COMMA)
/*.*/
#define GUIK_PERIOD       (SDLK_PERIOD)
/* */
#define GUIK_SLASH        (SDLK_SLASH)
#define GUIK_RSHIFT       (SDLK_RSHIFT)

#define GUIK_LCTRL        (SDLK_LCTRL)
/*Left Windows*/
#define GUIK_LSUPER       (SDLK_LSUPER)
#define GUIK_LALT         (SDLK_LALT)
#define GUIK_SPACE        (SDLK_SPACE)
#define GUIK_RALT         (SDLK_RALT)
/*Right Windows*/
#define GUIK_RSUPER       (SDLK_RSUPER)
#define GUIK_RCTRL        (SDLK_RCTRL)

/*Extern Keys*/
#define GUIK_PRINT        (SDLK_PRINT)
#define GUIK_SCROLLOCK    (SDLK_SCROLLOCK)
#define GUIK_PAUSE        (SDLK_PAUSE)
#define GUIK_INSERT       (SDLK_INSERT)
#define GUIK_HOME         (SDLK_HOME)
#define GUIK_PAGE_UP      (SDLK_PAGEUP)
#define GUIK_DELETE       (SDLK_DELETE)
#define GUIK_END          (SDLK_END)
#define GUIK_PAGE_DOWN    (SDLK_PAGEDOWN)

/*Direction Keys*/
#define GUIK_UP           (SDLK_UP)
#define GUIK_LEFT         (SDLK_LEFT)
#define GUIK_DOWN         (SDLK_DOWN)
#define GUIK_RIGHT        (SDLK_RIGHT)

/*Number Keys*/
#define GUIK_NUMLOCK      (SDLK_NUMLOCK)
#define GUIK_KP_DIVIDE    (SDLK_KP_DIVIDE)
#define GUIK_KP_MULTIPLY  (SDLK_KP_MULTIPLY)
#define GUIK_KP_MINUS     (SDLK_KP_MINUS)
#define GUIK_KP7          (SDLK_KP7)
#define GUIK_KP8          (SDLK_KP8)
#define GUIK_KP9          (SDLK_KP9)
#define GUIK_KP_PLUS      (SDLK_KP_PLUS)
#define GUIK_KP4          (SDLK_KP4)
#define GUIK_KP5          (SDLK_KP5)
#define GUIK_KP6          (SDLK_KP6)
#define GUIK_KP_ENTER     (SDLK_KP_ENTER)
#define GUIK_KP1          (SDLK_KP1)
#define GUIK_KP2          (SDLK_KP2)
#define GUIK_KP3          (SDLK_KP3)
#define GUIK_KP0          (SDLK_KP0)
#define GUIK_KP_PERIOD    (SDLK_KP_PERIOD)

#define GUIK_RED          (400)
#define GUIK_YELLOW       (401)
#define GUIK_BLUE         (403)
#define GUIK_GREEN        (404)


typedef struct tagKeyStruct{
	char name[20];
	int sys_code;
}key_struct;


struct scancode_map {
	int scan_code;
	int sys_code;
};

struct keys_table {
	struct scancode_map *key_map;
	int scancode_count;
	int scancode_count_max;
	int scancode_sort;
};

int find_key(unsigned int scan_value);
int key_map(const char *key_name, int scan_value);

int find_virtualkeys(unsigned short scan_code, unsigned short key);
int find_virtualkey(unsigned int key);
int virtualkey_map(const char *key_name, int scan_code);

int find_sys_code(const char *key_name);
int key_data_free(void);
unsigned int key_read(void);

__END_DECLS

#endif


