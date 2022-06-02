#include "tty.h"
#include "string.h"


uint16* VIDEO_MEMORY = 0;


void tty_initialize(terminal *t){
    VIDEO_MEMORY = (uint16*) (0xb8000);
    tty_clear(t);
    t->text_color=TTY_WHITE;

}

void tty_clear(terminal *t){
    for (uint8 i=0; i < VGA_WIDTH; i++){
        for (uint8 j=0; j< VGA_WIDTH; j++) 
        {   
            tty_put_char(t, ' ',i, j);
        }
      }
  t->terminal_row=0;
  t->terminal_col=0;
}


void tty_put_char(terminal*t ,char c, uint8 x,uint8 y) {
    if (c == '\n') {
        t->terminal_row=0;
        t->terminal_col++;
        return;
    }

    VIDEO_MEMORY[(y*VGA_WIDTH) +x] = tty_make_video_mem_char(c,t->text_color);
    t->terminal_row++;
    if (t->terminal_row >= VGA_WIDTH) {
        t->terminal_row=0;
        t->terminal_col++;
    }
}

void tty_print(terminal*t, const char* s)  {
    for (size_t i=0; i< strlen(s); i++) {
        tty_put_char(t,s[i], t->terminal_row, t->terminal_col);
    }
}

void tty_set_text_color(terminal *t, tty_color text_color) {
    t->text_color = text_color;
}

uint16 tty_make_video_mem_char(uint8 c, uint8 text_color) {
    return (text_color <<8) | c;

}



