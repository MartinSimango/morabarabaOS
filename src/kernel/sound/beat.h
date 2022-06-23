#ifndef _BEAT_H
#define _BEAT_H

#define BPM 120
#define MSM 60 * 1000.0 // milliseconds in a minute

#define BEAT_NOTE 8

#define SIXTEENTH_NOTE MSM / (BPM * (16.0 / BEAT_NOTE))
#define EIGTH_NOTE MSM / (BPM * (8.0 / BEAT_NOTE))
#define QUARTER_NOTE MSM / (BPM * (4.0 / BEAT_NOTE))
#define HALF_NOTE MSM / (BPM * (2.0 / BEAT_NOTE))
#define WHOLE_NOTE MSM / (BPM * (1.0 / BEAT_NOTE))

#define DOTTED_NOTE(note) (note + note / 2)

#include "chords.h"
#include "types.h"

#define MAX_NOTES_IN_BEAT 20

typedef uint16 beat_duration;

typedef struct Beat {
  Note notes[MAX_NOTES_IN_BEAT];
  uint8 num_notes;
  beat_duration duration[MAX_NOTES_IN_BEAT]; // in ms
  beat_duration
      duration_left_to_play[MAX_NOTES_IN_BEAT]; // in ms (how much time is left
                                                // to play for the beat)
} Beat;

Beat beat_create();

Beat beat_from_note(Note note, beat_duration beat_duration);

Beat beat_from_chord(Chord chord, beat_duration beat_duration);

void beats_from_notes(Beat *beats, Note *notes, uint8 notes_length,
                      beat_duration beat_duration);

void beats_from_chords(Beat *beats, Chord *chords, uint8 chords_length,
                       beat_duration beat_duration);

void beat_add_note(Beat *beat, Note note, beat_duration duration, beat_duration duration_left_to_play);

uint16 beat_max_duration_in_beat(Beat beat);

uint16 beat_min_duration_in_beat(Beat beat);


void free_note_in_beat(Beat beat);

#endif