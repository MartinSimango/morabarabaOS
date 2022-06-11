#pragma once

#include "colours.h"
#include "types.h"

typedef struct lv_font_glyph_dsc_t {
  uint8 w_px;
  uint16 glyph_index;
} lv_font_glyph_dsc_t;

typedef struct font {
  uint8 font_height;
  uint8 font_scale_height;
  uint8 font_scale_width;
  RGB font_color;
  const uint8 *glyph_bitmap;
  const lv_font_glyph_dsc_t *glyph_description;
  uint8 unicode_first; /*First Unicode letter in this font*/
} font;

font font_set_color(font font, RGB color);

font font_scale(font font, uint8 x, uint8 y);

uint8 font_get_char_width(font *font, char c);
