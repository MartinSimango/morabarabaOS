#include "tty.h"
#include "screen.h"
#include "string.h"
#include "timer.h"
#include "vbe.h"

void tty_initialize(tty *t) { tty_clear(t); }

void tty_clear(tty *t) {
  for (uint16 i = 0; i < SCREEN_HEIGHT; i++) {
    for (uint16 j = 0; j < SCREEN_WIDTH; j++) {
      screen_draw_pixel(t->background_color, j, i);
    }
  }

  t->tty_row = 0;
  t->tty_col = 2;
}

void tty_put_char(tty *t, char c) {
  if (c == '\n') {
    t->tty_row += t->fnt.font_height;
    t->tty_col = 2;
    return;
  }

  uint8 char_width = font_get_char_width(&t->fnt, c) + 2;
  if (t->tty_col + char_width >= SCREEN_WIDTH) {
    t->tty_row += t->fnt.font_height;
    t->tty_col = 2;
  }
  screen_print(&c, t->tty_col, t->tty_row, &t->fnt);

  t->tty_col += char_width;
}

void tty_print(tty *t, const char *s) {
  for (size_t i = 0; i < strlen(s); i++) {
    tty_put_char(t, s[i]);
  }
}

void tty_set_text_color(tty *t, RGB text_color) {
  t->fnt.font_color = text_color;
}
void tty_init() { tty_initialize(&DefaultTTY); }

void tty_print_default(const char *s) { tty_print(&DefaultTTY, s); }

void tty_print_int_default(uint32 num) {
  char buf[256];
  tty_print_default(itoa(num, buf, 10000));
}

// todo add error number
void tty_kernel_panic(uint8 error_num) {
  DefaultTTY.fnt.font_color = BLACK;
  DefaultTTY.background_color = BLUE_SCREEN;
  tty_clear(&DefaultTTY);
  // change how to print error number
  tty_print_default("Kernel Panick!!! - ");
  tty_print_int_default(error_num);
  while (1)
    ;
}
