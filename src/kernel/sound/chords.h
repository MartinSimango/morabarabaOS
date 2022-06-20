#ifndef _CHORDS_H_
#define _CHORDS_H_

#include "scale.h"

//  TODO IT'S PROBABLY BETTER TO HARDCODE THE CHORDS AS IT IS CHEAPER
//  COMPUTATIONALLY
// (ALTHOUGH HAVING CHORDS HARDCODED MEANS MORE MEMORY SO CPU OR MEMORY?) CHORD
// IS 12*24+8= 296 BYTES SO MEANING STORE 100 CORDS IS ONLY 29600 BYTES OF
// MEMORY OR 29 KB

typedef struct Chord {
  uint8 num_of_notes;
  Note notes[12];
} Chord;

static inline void chords_init() { scale_init(); }

static inline uint8 chord_degree_to_note_count(uint8 degree) {
  return (degree == 0) ? 3 : degree - 2;
}

static inline Chord Maj(Note root, uint8 degree) {
  degree = degree >= 15 ? 0 : degree;
  degree = (degree % 2 != 0) ? degree - 1 : degree; // degree must be odd
  Chord c;
  c.num_of_notes = chord_degree_to_note_count(degree);
  uint8 d = 1;
  for (uint8 i = 0; i < c.num_of_notes; i++) {
    c.notes[i] = get_note_in_scale(root, d, MAJOR_SCALE);
    d += 2;
  }
  return c;
}

static inline Chord Min(Note root, uint8 degree) {
  degree = degree >= 15 ? 0 : degree;
  degree = (degree % 2 != 0) ? degree - 1 : degree; // degree must be odd
  Chord c;
  c.num_of_notes = chord_degree_to_note_count(degree);
  uint8 d = 1;
  for (uint8 i = 0; i < c.num_of_notes; i++) {
    c.notes[i] = get_note_in_scale(root, d, MINOR_SCALE);
    d += 2;
  }
  return c;
}

#endif