#ifndef _SCALE_H
#define _SCALE_H

#include "notes.h"

typedef uint8 scale_type;

#define MAJOR_SCALE 0
#define MINOR_SCALE 1

#define SCALE_LENGTH 16

static Note ALL_NOTES[OCTAVE_SIZE * NUM_OCTAVES];

typedef struct Scale {
  Note notes[SCALE_LENGTH];
  scale_type type;
} Scale;

void scale_init();

uint8 major_degree_add(uint8 degree);

uint8 minor_degree_add(uint8 degree);

Note get_note_in_scale(Note note, uint8 degree, scale_type scale);

Scale get_scale(Note root, scale_type scale);

void scale_init();

#endif