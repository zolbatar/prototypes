#ifndef H_KEYBOARD
#define H_KEYBOARD
#include <stdbool.h>
#include "types.h"

void keyboard_init();
BYTE check_for_key();

#define KEY_ESCAPE  27
#define KEY_Q       113
#define KEY_W       119
#define KEY_E       101
#define KEY_R       114
#define _KEY_LEFT    0
#define _KEY_RIGHT   1
#define _KEY_UP      2
#define _KEY_DOWN    3
#define PAGE_UP     63
#define PAGE_DOWN   78

#endif

