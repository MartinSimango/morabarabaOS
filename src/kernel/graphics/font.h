#ifndef _FONT_
#define _FONT_

#include "types.h"
void font_char(char c, size_t x, size_t y, uint8 color);

void font_str(const char *s, size_t x, size_t y, uint8 color);

#endif