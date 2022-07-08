#include "chords.h"
#include "memory.h"
#include <stdarg.h>

void chords_init() { scale_init(); }

void chord_init(Chord *chord) { chord->num_of_notes = 0; }

void chord_add_note(Chord *chord, Note note) {
  chord->notes[chord->num_of_notes++] = note;
}

uint8 align_to_4_bytes(uint8 bytes) {
  if ((bytes % 4) == 0) {
    return bytes;
  }
  return bytes - (bytes % 4) + 4;
}

Chord chord_add_notes(Chord *chord, uint8 num_notes, Note note, ...) {
  chord->notes[0] = note;

  va_list argp;
  va_start(argp, note);
  uint8 note_count = 1;

  while (note_count < num_notes) {
    // please note Size of Note is 24 bytes and int is 4 (on 32 bit systems)
    // c will mostly likely align arguments to 4 bytes  so 24 bytes is find is
    // 24%4=0 but if Note increases c will align struct with the size of the
    // largeset privitve members in struct (largenst member is 4 bytes - 32 bit
    // system)
    chord->notes[note_count] = va_arg(argp, Note);
    note_count++;
  }
  chord->num_of_notes = note_count;
  va_end(argp);

  return *chord;
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
