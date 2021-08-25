#ifndef _SCRREN_ 
#define _SCREEN_

#include "colours.h"

#define SCREEN_HEIGHT 200
#define SCREEN_WIDTH 320

#define PALETTE_MASK_REGISTER 0x03c6 
#define PALETTE_READ_REGISTER 0x03c7
#define PALETTE_WRITE_REGISTER 0x03c8
#define PALETTE_DATA_REGISTER  0x03c9



static const uint8 SCREEN_PALETTE_SIZE = 0;

void init_screen();

void init_default_pallete();

void init_pallete(RGB * pallete, uint8 pallette_size);

void pallete_set(uint8 index, struct RGB colour);

#endif