#ifndef _SCRREN_
#define _SCREEN_

#include "colours.h"
#include "font.h"
#include "vbe.h"

// 1024x768
#define SCREEN_HEIGHT VBE_MODE_INFO->YResolution
#define SCREEN_WIDTH VBE_MODE_INFO->XResolution

#define PALETTE_MASK_REGISTER 0x03c6
#define PALETTE_READ_REGISTER 0x03c7
#define PALETTE_WRITE_REGISTER 0x03c8
#define PALETTE_DATA_REGISTER 0x03c9

// static const uint8 SCREEN_PALETTE_SIZE = 0;

void init_screen(RGB color);

void init_default_pallete();

void init_pallete(RGB *pallete, uint8 pallette_size);

void pallete_set(uint32 index, struct RGB colour);

void screen_draw_pixel(RGB color, uint16 x, const uint16 y);

void screen_print(const char *s, size_t x, size_t y, const font *font);



#endif