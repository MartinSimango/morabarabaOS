#ifndef _COLOURS_
#define _COLOURS_

#include "types.h"

// 
typedef struct RGBA {
  uint8 blue;
  uint8 green;
  uint8 red;
  uint8 alpha;
} __attribute__((packed)) RGBA;

static const RGBA WHITE = {0xff, 0xff, 0xff,200};
static const RGBA BLACK = {0,0, 0, 0};
static const RGBA RED = {0, 0, 0xff,0};
static const RGBA GREEN = {0, 0xff, 0,0};
static const RGBA BLUE = {0xff, 0, 0,0};
static const RGBA YELLOW = {0, 0xff, 0xff,0};
static const RGBA PURPLE = {30, 0, 30,0};
static const RGBA SKY_BLUE = {180, 105, 63,0};
static const RGBA LIGHT_BLUE = {0, 63, 63,0};
static const RGBA NAVY_BLUE = {68, 42, 32,0};
static const RGBA BLUE_SCREEN = {0XBF, 0, 0,0};


static const RGBA TERMINAL_GRAY = {20,20, 20, 100};

void init_colours();

#endif