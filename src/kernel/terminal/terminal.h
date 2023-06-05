#ifndef _TERMINAL_
#define _TERMINAL_

#include "SFMonoBold.h"
// #include "SFMonoRegular_25.h"
#include "colours.h"
#include "font.h"
#include "types.h"
#include "vbe.h"

typedef struct terminal {
  RGB background_color;
  uint16 terminal_row;
  uint16 terminal_col;
  struct font fnt;
} terminal;

static struct terminal Defaultterminal = { .fnt = SF_MONO_BOLD_FONT,
                                          .terminal_row = 0,
                                          .terminal_col = 2,
                                          .background_color = TERMINAL_GRAY};

void terminal_initialize(terminal *terminal);

void terminal_clear(terminal *terminal);

void terminal_put_char(terminal *t, char c);

void terminal_print(terminal *t, const char *s);

void terminal_set_text_color(terminal *t, RGB text_color);

// uint16 terminal_make_video_mem_char(uint8 c, uint8 text_color);

void terminal_init();

void terminal_print_default(const char *s);

void terminal_print_int_default(uint32 num);

void terminal_kernel_panic(uint8 error_num);

#endif

// os - 40k, 100K, 180K
// kernel - 140k ,200k, 280k