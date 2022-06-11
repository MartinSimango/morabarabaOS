#ifndef _TTY_
#define _TTY_

#include "SFMonoBold.h"
#include "colours.h"
#include "types.h"
#include "vbe.h"

typedef struct tty {
  RGB background_color;
  uint16 tty_row;
  uint16 tty_col;
  struct font fnt;
} tty;

static struct tty DefaultTTY = {.fnt = SF_MONO_BOLD_FONT,
                                .tty_row = 0,
                                .tty_col = 2,
                                .background_color = TERMINAL_GRAY};

void tty_initialize(tty *tty);

void tty_clear(tty *tty);

void tty_put_char(tty *t, char c);

void tty_print(tty *t, const char *s);

void tty_set_text_color(tty *t, RGB text_color);

// uint16 tty_make_video_mem_char(uint8 c, uint8 text_color);

void tty_init();

void tty_print_default(const char *s);

void tty_kernel_panic(uint8 error_num);

#endif