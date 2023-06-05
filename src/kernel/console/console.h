#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include "tty.h"

struct console {
  void (*write)(struct console *co, const char *s, unsigned int count);
  int (*setup)(struct console *co);
  void (*reset)(struct console *co);
  struct tty_driver *(*device)(struct console *co);
  void *data;
};

extern struct console *default_console;

void console_init();

void register_console(struct console *);

#endif