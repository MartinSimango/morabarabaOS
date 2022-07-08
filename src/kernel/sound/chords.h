#ifndef _CHORDS_H_
#define _CHORDS_H_

#include "scale.h"

//  TODO IT'S PROBABLY BETTER TO HARDCODE THE CHORDS AS IT IS CHEAPER
//  COMPUTATIONALLY
// (ALTHOUGH HAVING CHORDS HARDCODED MEANS MORE MEMORY SO CPU OR MEMORY?) CHORD
// IS 12*24+8= 296 BYTES SO MEANING STORE 100 CORDS IS ONLY 29600 BYTES OF
// MEMORY OR 29 KB

#define MAX_NOTES_IN_CHORD 12

typedef struct Chord {
  uint8 num_of_notes;
  Note notes[MAX_NOTES_IN_CHORD];
} Chord;

void chords_init();

uint8 chord_degree_to_note_count(uint8 degree);

void chord_init(Chord *chord);

Chord chord_instance();

void chord_add_note(Chord *chord, Note note);

Chord chord_add_notes(Chord *chord, uint8 num_notes, Note note, ...);

Chord Maj(Note root, uint8 degree);

Chord Min(Note root, uint8 degree);

#endif