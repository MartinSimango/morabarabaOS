#include "beat.h"
#include "kheap.h"

uint16 BEAT_BPM = 120;
uint8 BEAT_NOTE = 4;

Beat beat_from_note(Note note, beat_duration beat_duration) {
  Beat beat;
  beat.notes[0] = note;
  beat.num_notes = 1;
  beat.duration[0] = beat_duration;
  beat.duration_left_to_play[0] = beat_duration;
  return beat;
}

Beat beat_from_chord(Chord chord, beat_duration beat_duration) {
  Beat beat;
  for (uint8 i = 0; i < chord.num_of_notes; i++) {
    beat.notes[i] = chord.notes[i];
    beat.duration[i] = beat_duration;
    beat.duration_left_to_play[i] = beat_duration;
  }
  beat.num_notes = chord.num_of_notes;

  return beat;
}

void beats_from_notes(Beat *beats, Note *notes, uint8 notes_length,
                      beat_duration beat_duration) {
  for (uint8 i = 0; i < notes_length; i++) {
    beats[i] = beat_from_note(notes[i], beat_duration);
  }
}

void beats_from_chords(Beat *beats, Chord *chords, uint8 chords_length,
                       beat_duration beat_duration) {
  for (uint8 i = 0; i < chords_length; i++) {
    beats[i] = beat_from_chord(chords[i], beat_duration);
  }
}

void beat_add_note(Beat *beat, Note note, beat_duration duration,
                   beat_duration duration_left_to_play) {
  if (1 + beat->num_notes > MAX_NOTES_IN_BEAT) {
    return;
  }
  beat->notes[beat->num_notes] = note;
  beat->duration[beat->num_notes] = duration;
  beat->duration_left_to_play[beat->num_notes++] = duration_left_to_play;
}

void beat_add_extended_note(Beat *beat, Note note, beat_duration duration) {
  beat_add_note(beat, note, duration, duration);
}
uint16 beat_max_duration_in_beat(Beat beat) {
  uint16 max_duration = 0;
  for (uint8 i = 0; i < beat.num_notes; i++) {
    if (beat.duration[i] > max_duration) {
      max_duration = beat.duration[i];
    }
  }
  return max_duration;
}

uint16 beat_min_duration_in_beat(Beat beat) {
  // todo error check
  uint16 min_duration = beat.duration[0];
  for (uint8 i = 1; i < beat.num_notes; i++) {
    if (beat.duration[i] < min_duration) {
      min_duration = beat.duration[i];
    }
  }
  return min_duration;
}

void free_note_in_beat(Beat beat) { kfree(beat.notes); }
