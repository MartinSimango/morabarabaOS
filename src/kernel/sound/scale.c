#include "scale.h"

void scale_init() {

  uint8 count = 0;
  for (uint8 i = 0; i < NUM_OCTAVES; i++) {
    ALL_NOTES[count++] = C_Note(i, WAVE_SIN, 0);
    ALL_NOTES[count++] = CSharp_Note(i, WAVE_SIN, 0);
    ALL_NOTES[count++] = D_Note(i, WAVE_SIN, 0);
    ALL_NOTES[count++] = DSharp_Note(i, WAVE_SIN, 0);
    ALL_NOTES[count++] = E_Note(i, WAVE_SIN, 0);
    ALL_NOTES[count++] = F_Note(i, WAVE_SIN, 0);
    ALL_NOTES[count++] = FSharp_Note(i, WAVE_SIN, 0);
    ALL_NOTES[count++] = G_Note(i, WAVE_SIN, 0);
    ALL_NOTES[count++] = GSharp_Note(i, WAVE_SIN, 0);
    ALL_NOTES[count++] = A_Note(i, WAVE_SIN, 0);
    ALL_NOTES[count++] = ASharp_Note(i, WAVE_SIN, 0);
    ALL_NOTES[count++] = B_Note(i, WAVE_SIN, 0);
  }
}

uint8 major_degree_add(uint8 degree) {
  switch (degree) {
  case 0:
  case 1:
    return 0;
  case 2:
    return 2;
  case 3:
    return 4;
  case 4:
    return 5;
  case 5:
    return 7;
  case 6:
    return 9;
  case 7:
    return 11;
  }
  return major_degree_add(degree % 7) + 12;
}

uint8 minor_degree_add(uint8 degree) {
  switch (degree) { // A A# B C C# D D# E F F# G G#
  case 0:
  case 1:
    return 0;
  case 2:
    return 2;
  case 3:
    return 3;
  case 4:
    return 5;
  case 5:
    return 7;
  case 6:
    return 8;
  case 7:
    return 10;
  }
  return minor_degree_add(degree % 7) + 12;
}

Note get_note_in_scale(Note note, uint8 degree, scale_type scale) {
  uint8 note_pos = (note.octave) * 12 + note.offset;

  uint8 add = 0;
  switch (scale) {
  case MAJOR_SCALE:
    add = major_degree_add(degree);
    break;
  case MINOR_SCALE:
    add = minor_degree_add(degree);
  }

  if (note_pos + add >= NUM_NOTES) {
    return note;
  }

  Note new_note = ALL_NOTES[note_pos + add];
  new_note.volume = note.volume;
  new_note.wave_type = note.wave_type;
  return new_note;
}

Scale get_scale(Note root, scale_type st) {
  Scale scale;
  scale.type = st;
  for (uint8 i = 0; i < SCALE_LENGTH; i++) {
    scale.notes[i] = get_note_in_scale(root, i + 1, st);
  }
  return scale;
}
