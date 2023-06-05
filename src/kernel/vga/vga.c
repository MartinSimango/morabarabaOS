#include "vga.h"
#include "tty.h"
#include "vbe.h"

void init_vga_device() {
  vga_device.video_memory =  (short*)0xB8000;//(short *)VBE_MODE_INFO->PhysBasePtr;
  vga_device.width = 80;
  vga_device.height = 20;
  vga_device.x_pos = 0;
  vga_device.y_pos = 0;
  vga_device.attr = false;
}

void vga_console_reset(struct console *co) {
    ((struct vga*)co->data)->x_pos = 0;
    ((struct vga*)co->data)->y_pos = 0;

}

int vga_console_setup(struct console *co) {
  init_vga_device();
  return 0;
}

void vga_console_putc(struct console *co, char c) {
  int pos = vga_device.x_pos + (vga_device.width * vga_device.y_pos);
  if (c == '\n'){
    vga_device.x_pos = 0;
    vga_device.y_pos++;
    return;
  }
  if (!vga_device.attr) {
    vga_device.video_memory[pos] = c;
  } else {
   
    vga_device.video_memory[pos] =
        (c << 8) | vga_device.video_memory[pos];
    vga_device.x_pos++;
    if (vga_device.x_pos >= vga_device.width ) {
        vga_device.x_pos = 0;
        vga_device.y_pos++;
    }
    
  }
  vga_device.attr = !vga_device.attr;
}

void vga_console_write(struct console *co, const char *s, unsigned int count) {
  while (count--) {
    vga_console_putc(co, *s);
    s++;
  }
}

int write_tty(struct tty *t, const char *buf, int count) {
  while (count--) {
    t->output_buffer[t->buffer_pos++] = *buf;
    buf++;
  }
  return count;
}

int install_tty(struct tty_driver *driver, struct tty *tty) {
  driver->ttys[driver->tty_number++] = tty;
  tty->tty_driver = driver;
  return 0;
}

void flush_tty(struct tty *t) {
  // 0 out
  t->buffer_pos = 0;
}


struct tty_driver vga_tty_driver = {
  .write = write_tty,
  .install = install_tty,
  .flush = flush_tty
};

struct tty_driver *vga_console_device(struct console *co) {
  return &vga_tty_driver;
}

struct console vga_console = {.write = vga_console_write,
                                     .setup = vga_console_setup,
                                     .device = vga_console_device,
                                     .data = &vga_device,
                                     .reset = vga_console_reset};

void register_vga_console() { register_console(&vga_console); }
