#include "screen.h"
#include "io.h"
#include "types.h"

void screen_init(RGBA color) {

  RGBA *VGA_MEMORY = (RGBA *)VBE_MODE_INFO->PhysBasePtr;

  for (uint16 width = 0; width < SCREEN_WIDTH; width++) {
    for (uint16 height = 0; height < SCREEN_HEIGHT; height++) {
      uint32 offset = width + height * SCREEN_WIDTH;
      VGA_MEMORY[offset] = color;
    }
  }
}

void screen_draw_pixel(RGBA color, uint16 x, uint16 y) {
  RGBA *VGA_MEMORY = (RGBA *)VBE_MODE_INFO->PhysBasePtr;
  VGA_MEMORY[(y * SCREEN_WIDTH) + x] = color;
}

void screen_draw_char(char c, uint8 char_width, uint16 glyph_index, size_t x,
                      size_t y, const font *font) {
  const uint8 *glyph = &(font->glyph_bitmap[glyph_index]);

  uint8 font_color_RED = font->font_color.red;
  uint8 font_color_GREEN = font->font_color.green;
  uint8 font_color_BLUE = font->font_color.blue;

  size_t height = (font->font_height * font->font_scale_height);
  size_t width = (char_width * font->font_scale_width);

  for (size_t yy = 0; yy < height; yy += 1) {
    for (size_t xx = 0; xx < width; xx += 1) { // * 8 because 8 bits per pixel
      RGBA color = font->font_color;
      uint8 pixel = glyph[(yy * char_width + xx)];

      if (pixel > 0) {
        color.red &= pixel;
        color.blue &= pixel;
        color.green &= pixel;
        screen_draw_pixel(color, x + xx, y + yy);
      }
    }
  }
}

void screen_print(const char *s, size_t x, size_t y, const font *font) {
  char c;

  while ((c = *s++) != 0) {
    uint16 index = (uint8)c - font->unicode_first;
    uint8 char_width = font->glyph_description[index].w_px;
    uint16 glyph_index = font->glyph_description[index].glyph_index;

    screen_draw_char(c, char_width, glyph_index, x, y, font);

    x += char_width + 2;
  }
}