#include "music.h"
#include "math.h"
#include "sb16.h"
#include "timer.h"
#include "tty.h"

void music_init() {

Note notes[] = { C_NOTE(4, WAVE_SIN, 220),  E_NOTE(4, WAVE_SIN, 220),  G_NOTE(4, WAVE_SIN, 220)};
sb16_set_notes(notes, 3);


}

float64 music_get_sample(Note note, uint64 sample_rate, uint8 volume,
                            uint16 sample_scale) {

  float64 val = sin(2.0 * PI * (note.freq/sample_rate) * (note.sample_count * sample_scale));
  switch (note.wave_type) {
  case WAVE_SIN:
    return val *volume;
  case WAVE_SQUARE:
    return (val < 0) ? -volume : volume;
    
  }
  return 0;
}
