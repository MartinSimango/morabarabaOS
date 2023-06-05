#include "vc.h"



void vc_con_write(struct vc *vc) {
  short attr = (vc->background_color & 0xF0) | (vc->text_color & 0x0F);
  for (int i = 0; i < vc->tty->buffer_pos; i++) {
    vc->vc_screenbuf[vc->vc_pos++] = (attr << 8) | vc->tty->output_buffer[i];
  }
  vc->tty->tty_driver->flush(vc->tty);
}

void vc_con_set(struct vc *vc, struct console *co) {
  co->reset(co);
  for (int i = 0; i < vc->vc_pos; i++) {
    char char_to_write[2] = { vc->vc_screenbuf[i], vc->vc_screenbuf[i]>>8 };
    if (char_to_write[0] == '\n') {
         co->write(co, char_to_write, 1);
    } else {
        co->write(co, char_to_write, 2);
    }
  }
}
