#include "font.h"

font font_set_color(font font, RGB color) {
  font.font_color = color;
  return font;
}

font font_scale(font font, uint8 x, uint8 y) {
  font.font_scale_width = x;
  font.font_scale_height = y;
  return font;
}
