#ifndef _COLOURS_
#define _COLOURS_

#include "types.h"

typedef struct RGB {
  uint8 blue;
  uint8 green;
  uint8 red;
} __attribute__((packed)) RGB;

static const RGB WHITE = {0xff, 0xff, 0xff};
static const RGB BLACK = {0, 0, 0};
static const RGB RED = {0, 0, 0xff};
static const RGB GREEN = {0, 0xff, 0};
static const RGB BLUE = {0xff, 0, 0};
static const RGB YELLOW = {0, 0xff, 0xff};
static const RGB PURPLE = {30, 0, 30};
static const RGB SKY_BLUE = {180, 105, 63};
static const RGB LIGHT_BLUE = {0, 63, 63};
static const RGB NAVY_BLUE = {68, 42, 32};
static const RGB BLUE_SCREEN = {0XBF, 0, 0};

static const RGB TERMINAL_GRAY = {30, 30, 30};

void init_colours();

#endif