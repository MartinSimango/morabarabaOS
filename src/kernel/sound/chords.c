#include "chords.h"
#include "memory.h"

void chords_init() { scale_init(); }

void chord_init(Chord *chord) { chord->num_of_notes = 0; }

void chord_add_note(Chord *chord, Note note) {
  chord->notes[chord->num_of_notes++] = note;
}

Chord chord_instance() {
  Chord chord;
  memset(&chord, 0, sizeof(Chord));
  return chord;
}

uint8 chord_degree_to_note_count(uint8 degree) {
  return (degree == 0) ? 3 : degree - 2;
}
Chord Maj(Note root, uint8 degree) {
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

Chord Min(Note root, uint8 degree) {
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
