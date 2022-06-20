#ifndef _MUSIC_H_
#define _MUSIC_H_

#include "chords.h"
#include "types.h"

#define BPM 120

#define MSM 60 * 1000.0 // milliseconds in a minute

#define BEAT_NOTE 4

#define SIXTEENTH_NOTE MSM / (BPM * (16.0 / BEAT_NOTE))
#define EIGTH_NOTE MSM / (BPM * (8.0 / BEAT_NOTE))
#define QUARTER_NOTE MSM / (BPM * (4.0 / BEAT_NOTE))
#define HALF_NOTE MSM / (BPM * (2.0 / BEAT_NOTE))
#define WHOLE_NOTE MSM / (BPM * (1.0 / BEAT_NOTE))

typedef uint16 NOTE_TYPE;

typedef struct Beat {
  Note *notes;
  uint8 num_notes;
  NOTE_TYPE duration;           // in ms
  uint16 duration_left_to_play; // in ms (how much time is left to play for the
                                // beat)
} Beat;

typedef struct Melody {
  Beat *beats;
  uint16 beats_length;
} Melody;

typedef struct Song {
  Melody *melodies;
} Song;

void music_init();

void music_play_chord(Chord c);

void music_play_note(Note note);

void music_play_melody(Melody melody);

void music_play_song(Song song, uint8 melody_count);

float64 music_get_sample(Note note, uint64 sample_rate, uint8 volume,
                         uint16 sample_scale);

Beat music_create_beat_from_note(Note note, NOTE_TYPE note_type);

Beat music_create_beat_from_chord(Chord chord, NOTE_TYPE note_type);

void tranform_beat_to_sixteenth(const Beat *src, Beat *dest);

#endif
