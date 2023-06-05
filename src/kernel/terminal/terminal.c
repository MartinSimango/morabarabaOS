#include "terminal.h"
#include "screen.h"
#include "string.h"
#include "timer.h"
#include "vbe.h"

void terminal_initialize(terminal *t) { terminal_clear(t); }

void terminal_clear(terminal *t) {
  for (uint16 i = 0; i < SCREEN_HEIGHT; i++) {
    for (uint16 j = 0; j < SCREEN_WIDTH; j++) {
      screen_draw_pixel(t->background_color, j, i);
    }
  }

  t->terminal_row = 0;
  t->terminal_col = 2;
}

void terminal_put_char(terminal *t, char c) {
  if (c == '\n') {
    t->terminal_row += t->fnt.font_height;
    t->terminal_col = 2;
    return;
  }

  uint8 char_width = font_get_char_width(&t->fnt, c) + 2;
  if (t->terminal_col + char_width >= SCREEN_WIDTH) {
    t->terminal_row += t->fnt.font_height;
    t->terminal_col = 2;
  }
  screen_print(&c, t->terminal_col, t->terminal_row, &t->fnt);

  t->terminal_col += char_width;
}

void terminal_print(terminal *t, const char *s) {
  for (size_t i = 0; i < strlen(s); i++) {
    terminal_put_char(t, s[i]);
  }
}

void terminal_set_text_color(terminal *t, RGB text_color) {
  t->fnt.font_color = text_color;
}
void terminal_init() { terminal_initialize(&Defaultterminal); }

void terminal_print_default(const char *s) {
  terminal_print(&Defaultterminal, s);
}

void terminal_print_int_default(uint32 num) {
  char buf[256];
  terminal_print_default(itoa(num, buf, 10000));
}

// todo add error number
void terminal_kernel_panic(uint8 error_num) {
  Defaultterminal.fnt.font_color = BLACK;
  Defaultterminal.background_color = BLUE_SCREEN;
  terminal_clear(&Defaultterminal);
  // change how to print error number
  terminal_print_default("Kernel Panick!!! - ");
  terminal_print_int_default(error_num);
  while (1)
    ;
}
