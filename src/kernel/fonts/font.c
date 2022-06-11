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

uint8 font_get_char_width(font *font, char c) {
  uint16 index = (uint8)c - font->unicode_first;
  uint8 char_width = font->glyph_description[index].w_px;
  return char_width;
}