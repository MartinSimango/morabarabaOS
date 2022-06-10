#ifndef _COLOURS_
#define _COLOURS_

#include "types.h"

typedef struct RGB {
  uint8 blue;
  uint8 green;
  uint8 red;
} __attribute__((packed)) RGB;

static const RGB WHITE = (RGB){0xff, 0xff, 0xff};
static const RGB BLACK = (RGB){0, 0, 0};
static const RGB RED = (RGB){0, 0, 0xff};
static const RGB GREEN = (RGB){0, 0xff, 0};
static const RGB BLUE = (RGB){0xff, 0, 0};
static const RGB YELLOW = (RGB){0, 0xff, 0xff};
static const RGB PURPLE = (RGB){30, 0, 30};
static const RGB SKY_BLUE = (RGB){180, 105, 63};
static const RGB LIGHT_BLUE = (RGB){0, 63, 63};

static const RGB TERMINAL_GRAY = (RGB){30, 30, 30};

void init_colours();

#endif