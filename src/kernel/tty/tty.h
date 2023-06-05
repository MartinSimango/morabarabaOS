#ifndef _TTY_
#define _TTY_

#include "types.h"

#define TTY_BUFFER_SIZE 80 * 25

struct tty_driver;

struct tty {
  char output_buffer[TTY_BUFFER_SIZE];
  int buffer_pos;
  struct tty_driver *tty_driver;
  int tty_count;
};

struct tty_driver {
  int (*write)(struct tty *t, const char *buf, int count);
  int (*install)(struct tty_driver *driver, struct tty *tty);
  void (*flush)(struct tty *t);
  struct tty *ttys[2];
  int tty_number;
};


extern struct tty tty_1, tty_2;



#endif