#ifndef _VC_H_
#define _VC_H_

#include "console.h"
#include "tty.h"

struct vc {
  struct tty *tty;
  unsigned int vc_cols; /* [#] Console size */
  unsigned int vc_rows;
  unsigned int vc_size_row;        /* Bytes per row */
  unsigned long vc_origin;         /* [!] Start of real screen */
  unsigned long vc_scr_end;        /* [!] End of real screen */
  unsigned long vc_visible_origin; /* [!] Top of visible window */
  unsigned int vc_top, vc_bottom;  /* Scrolling region */
  unsigned short *vc_screenbuf;    /* In-memory */
  unsigned long vc_pos;            /* Cursor address */
  void (*set)(struct vc *vc, struct console *co);
  char background_color;
  char text_color;
  // 0b00001111
};

void vc_con_write(struct vc *vc);

void vc_con_set(struct vc *vc, struct console *co);

extern struct vc vc_consoles[2];

#endif
