#ifndef _MELODY_H
#define _MELODY_H

#include "beat.h"

#define MAX_BEATS_IN_MELODY 1000

// Melody is simply a collection of Beats (which are contain details of how long
// a note is played)
typedef struct Melody {
  Beat *beats;
  uint16 beats_length;
  uint32 melody_durtaion; // in ms
} Melody;

Melody *new_melody();

void melody_add_beat(Melody *melody, Beat beat);

void melody_add_beats(Melody *melody, Beat *beats, uint8 number_of_beats);

void melody_free(Melody *melody);

#endif