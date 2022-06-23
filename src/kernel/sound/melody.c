#include "melody.h"
#include "memory.h"
#include "tty.h"

Melody *new_melody() {
  Melody *melody = kmalloc(sizeof(Melody));
  melody->beats = kmalloc(sizeof(Beat) * MAX_BEATS_IN_MELODY);
  melody->beats_length = 0;
  melody->melody_durtaion = 0;
  return melody;
}

void melody_add_beat(Melody *melody, Beat beat) {
  if (melody->beats_length + 1 > MAX_BEATS_IN_MELODY) {
    return;
  }

  melody->beats[melody->beats_length++] = beat;
  melody->melody_durtaion += beat_max_duration_in_beat(beat);
}

void melody_add_beats(Melody *melody, Beat *beats, uint8 number_of_beats) {

  if (melody->beats_length + number_of_beats > MAX_BEATS_IN_MELODY) {
    return;
  }
  for (uint8 i = 0; i < number_of_beats; i++) {
    melody->beats[melody->beats_length++] = beats[i];
    melody->melody_durtaion += beat_max_duration_in_beat(beats[i]);
  }
}

void melody_free(Melody *melody) {
  kfree(melody->beats);
  kfree(melody);
}
