#include "music.h"
#include "kheap.h"
#include "math.h"
#include "memory.h"
#include "sb16.h"
#include "timer.h"
#include "tty.h"

void music_init() {
  chords_init();
  Chord bdim;
  bdim.notes[0] = B_Note(4, 0, 20), bdim.notes[1] = F_Note(5, 0, 20),
  bdim.notes[2] = D_Note(5, 0, 20), bdim.num_of_notes = 3;

  Chord chords[8] = {
      Maj(C_Note(4, 0, 20), 0),
      Min(D_Note(6, 0, 20), 0),
      Min(E_Note(4, 0, 20), 0),
      Maj(F_Note(4, 0, 50), 0),
      Maj(G_Note(4, 0, 50), 0),
      Min(A_Note(4, 0, 50), 0),
      bdim,
      Maj(C_Note(7, 0, 50), 0),
  };

  Beat melody_1_beats[8];
  melody_1_beats[0] = music_create_beat_from_note(D4(0, 50), QUARTER_NOTE);
  melody_1_beats[1] = music_create_beat_from_note(C4(0, 50), QUARTER_NOTE);
  melody_1_beats[2] = music_create_beat_from_note(F4(0, 50), QUARTER_NOTE);
  melody_1_beats[3] = music_create_beat_from_note(E4(0, 50), QUARTER_NOTE);
  melody_1_beats[4] = music_create_beat_from_note(D4(0, 50), QUARTER_NOTE);
  melody_1_beats[5] = music_create_beat_from_note(A4(0, 50), QUARTER_NOTE);
  melody_1_beats[6] = music_create_beat_from_note(G4(0, 50), QUARTER_NOTE);
  melody_1_beats[7] = music_create_beat_from_note(E4(0, 50), QUARTER_NOTE);

  Beat melody_3_beats[8];

  melody_3_beats[0] = music_create_beat_from_note(D2(0, 20), QUARTER_NOTE);
  melody_3_beats[1] = music_create_beat_from_note(C2(0, 20), QUARTER_NOTE);
  melody_3_beats[2] = music_create_beat_from_note(F2(0, 20), QUARTER_NOTE);
  melody_3_beats[3] = music_create_beat_from_note(E2(0, 20), QUARTER_NOTE);
  melody_3_beats[4] = music_create_beat_from_note(D2(0, 20), QUARTER_NOTE);
  melody_3_beats[5] = music_create_beat_from_note(A2(0, 20), QUARTER_NOTE);
  melody_3_beats[6] = music_create_beat_from_note(G2(0, 20), QUARTER_NOTE);
  melody_3_beats[7] = music_create_beat_from_note(E2(0, 20), QUARTER_NOTE);

  Beat melody_2_beats[5];

  melody_2_beats[0] = music_create_beat_from_note(F4(0, 50), QUARTER_NOTE);
  // melody_2_beats[1] = music_create_beat_from_note(&a, QUARTER_NOTE);
  melody_2_beats[1] = music_create_beat_from_note(RST, QUARTER_NOTE);
  melody_2_beats[2] = music_create_beat_from_note(RST, QUARTER_NOTE);
  melody_2_beats[3] = music_create_beat_from_note(A4(0, 50), QUARTER_NOTE);
  // melody_2_beats[4] = music_create_beat_from_note(&r, WHOLE_NOTE);
  melody_2_beats[4] = music_create_beat_from_chord(bdim, WHOLE_NOTE);
  // Beat b[16];
  // tranform_beat_to_sixteenth(&melody_1_beats[0], b);
  Melody melody_1;
  Melody melody_2;
  Melody melody_3;

  melody_1.beats = melody_1_beats;
  melody_1.beats_length = 8;

  melody_2.beats = melody_2_beats;
  melody_2.beats_length = 5;

  melody_3.beats = melody_3_beats;
  melody_3.beats_length = 8;

  Melody melodies[3];
  melodies[0] = melody_2;
  melodies[1] = melody_1;
  melodies[2] = melody_3;

  Song song;
  song.melodies = melodies;
  music_play_song(song, 3);

  // sb16_pause_sound();

  // music_play_melody(melody_1);
  // music_play_melody(melody_2);
  // music_play_chord(chords[0]);
  //   music_play_chord(chords[1]);
  // music_play_chord(chords[2]);
  // music_play_chord(chords[3]);
  // music_play_chord(chords[4]);
  // music_play_chord(chords[5]);
  // music_play_chord(chords[6]);
  //   music_play_chord(chords[7]);
}

void music_play_chord(Chord c) { sb16_set_notes(c.notes, c.num_of_notes); }

void music_play_note(Note note) { sb16_set_notes(&note, 1); }

void music_play_melody(Melody melody) {
  // sb16_play_sound();
  for (uint16 i = 0; i < melody.beats_length; i++) {
    sb16_set_notes(melody.beats[i].notes, melody.beats[i].num_notes);
    timer_sleep(melody.beats[i].duration);
  }
  // sb16_pause_sound();
}

void tranform_beat_to_sixteenth(const Beat *src, Beat *dest) {

  uint16 num_of_beats = src->duration / (SIXTEENTH_NOTE);

  for (uint16 i = 0; i < num_of_beats; i++) {
    dest[i].duration = SIXTEENTH_NOTE;
    dest[i].num_notes = src->num_notes;
    for (uint16 j = 0; j < dest[i].num_notes; j++) {
      dest[i].notes = src[0].notes;
    }
  }
}

void music_play_song(Song song, uint8 melody_count) {
  uint16 num_of_melodies = melody_count;
  uint16 max_melody = 0;
  for (uint16 i = 0; i < num_of_melodies; i++) {
    uint16 beat_num = song.melodies[i].beats_length;
    uint16 melody_duration = 0;
    for (uint16 j = 0; j < beat_num; j++) {
      melody_duration += song.melodies[i].beats[j].duration;
    }

    if (melody_duration > max_melody) {
      max_melody = melody_duration;
    }
  }

  uint16 num_of_beats = max_melody / (SIXTEENTH_NOTE);
  Note notes[num_of_beats][12];

  Beat bees[num_of_beats][12];
  Beat durations[num_of_beats][12];

  memset(notes, 0, sizeof(notes));
  memset(notes, 0, sizeof(durations));
  memset(bees, 0, sizeof(notes));

  uint16 note_beat_count[num_of_beats];
  memset(note_beat_count, 0, sizeof(note_beat_count));

  for (uint16 j = 0; j < num_of_melodies; j++) {
    uint8 beat_count = 0;
    for (uint16 k = 0; k < song.melodies[j].beats_length; k++) {
      uint16 beat_ticks = song.melodies[j].beats[k].duration / (SIXTEENTH_NOTE);
      for (uint16 l = 0; l < beat_ticks; l++) {
        for (uint16 n = 0; n < song.melodies[j].beats[k].num_notes; n++) {
          Beat b =
              music_create_beat_from_note(song.melodies[j].beats[k].notes[n],
                                          song.melodies[j].beats[k].duration);
          b.duration_left_to_play =
              song.melodies[j].beats[k].duration - ((l)*SIXTEENTH_NOTE);
          bees[beat_count][note_beat_count[beat_count]++] = b;
        }

        beat_count++; // new beat added
      }
    }
  }

  while (1) {
    for (uint16 i = 0; i < num_of_beats; i++) {
      Note notes_to_play[note_beat_count[i]];
      for (uint16 j = 0; j < note_beat_count[i]; j++) {
        if (bees[i][j].duration_left_to_play < bees[i][j].duration) {
          bees[i][j].notes[0].sample_count =
              get_sb16_card().notes[j].sample_count;
        }
        notes_to_play[j] = bees[i][j].notes[0];
      }

      sb16_set_notes(notes_to_play,
                     note_beat_count[i]); // should take ** for notes
      timer_sleep(SIXTEENTH_NOTE);
    }
  }

  sb16_pause_sound();
}

float64 music_get_sample(Note note, uint64 sample_rate, uint8 volume,
                         uint16 sample_scale) {

  float64 val = sin(2.0 * PI * (note.freq / sample_rate) *
                    (note.sample_count * sample_scale));
  switch (note.wave_type) {
  case WAVE_SIN:
    return val * volume;
  case WAVE_SQUARE:
    return (val < 0) ? -volume : volume;
  case WAVE_TRIANGLE: {
    float64 p = 1 / (note.freq / sample_rate);
    uint8 a = volume;
    float64 i = note.sample_count * sample_scale;
    float64 mod = fmod((i - (p / 4)), p);
    return ((4 * a) / p) * fabs((mod)-p / 2) - a;
  }
  }
  return 0;
}

Beat music_create_beat_from_note(Note note, NOTE_TYPE note_type) {
  Beat beat;
  beat.notes = new_note_from_note(note);
  beat.num_notes = 1;
  beat.duration = note_type;
  beat.duration_left_to_play = note_type;
  return beat;
}

Beat music_create_beat_from_chord(Chord chord, NOTE_TYPE note_type) {
  Beat beat;
  Note *notes = new_notes_from_notes(chord.notes, chord.num_of_notes);
  beat.notes = chord.notes;
  beat.num_notes = chord.num_of_notes;
  beat.duration = note_type;
  beat.duration_left_to_play = note_type;
  return beat;
}
