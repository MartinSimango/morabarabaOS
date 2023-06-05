#ifndef _VGA_H
#define _VGA_H

// VGA Graphics Driver

#include "console.h"
#include "tty.h"
#include "types.h"
#include "vbe.h"

// vga console driver
struct vga {
  short *video_memory;
  int x_pos;
  int y_pos;
  bool attr;
  int width;
  int height;
};

static struct vga vga_device;

int vga_console_setup(struct console *co);

void vga_console_putc(struct console *co, char c);

void vga_console_write(struct console *co, const char *s, unsigned int count);

void register_vga_console();

#endif