#ifndef _TTY_
#define _TTY_

#include "util.h"

#define VGA_HEIGHT 20
#define VGA_WIDTH 80


typedef uint8 tty_color;
typedef struct terminal
{
   tty_color text_color;
   uint8 terminal_row;
   uint8 terminal_col;
} terminal;

static const tty_color TTY_CLEAR = 0;
static const tty_color TTY_BLUE = 1;
static const tty_color TTY_GREEN = 2;
static const uint8 TTY_BLUE_GREEN = 3;
static const uint8 TTY_WHITE =15;


void tty_initialize(terminal *tty);

void tty_clear(terminal* tty);

void tty_put_char(terminal*,char, uint8,uint8);

void tty_print(terminal*, const char* );

void tty_set_text_color(terminal *t, tty_color text_color);

uint16 tty_make_video_mem_char(uint8 c, uint8 text_color);

#endif