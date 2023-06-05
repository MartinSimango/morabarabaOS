#include "console.h"
#include "kheap.h"
#include "tty.h"
#include "vbe.h"
#include "vc.h"
#include "vga.h"

struct console *default_console;
struct tty tty_1, tty_2;

void console_init() {
  register_vga_console();
  struct tty_driver * vga_tty_driver = default_console->device(default_console);
  vga_tty_driver->install(vga_tty_driver,&tty_1);
  vga_tty_driver->install(vga_tty_driver,&tty_2);
  for (int i = 0; i < 2; i++) {
    vc_consoles[i].tty = vga_tty_driver->ttys[i];
    vc_consoles[i].text_color = 255;
    vc_consoles[i].background_color = 0;
    vc_consoles[i].vc_rows = 80;
    vc_consoles[i].vc_cols = 25;
    vc_consoles[i].vc_screenbuf =
        kmalloc(vc_consoles[i].vc_rows * vc_consoles[i].vc_cols);

  }

}

void register_console(struct console *c) {
  c->setup(c);
  default_console = c;
  // add console to console list
}
