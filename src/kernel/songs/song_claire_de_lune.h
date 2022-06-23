#pragma once

#include "song.h"

static Chord f4_af4;
static Chord f5_af5;
static Chord f5_af5;
static Chord df5_f5;
static Chord gf4_a4;
static Chord c5_ef5;
static Chord bf4_df5;
static Chord ef4_gf4;
static Chord af4_c5;



static inline Melody *song_claire_de_lune_melody_1(uint8 wave, uint8 volume) {
  Melody *melody = new_melody();
  Beat beat;
  //Bar 1
  melody_add_beat(melody, beat_from_note(RST, EIGTH_NOTE + EIGTH_NOTE));

  melody_add_beat(
      melody, beat_from_chord(f5_af5, EIGTH_NOTE + DOTTED_NOTE(QUARTER_NOTE)));

  melody_add_beat(
      melody, beat_from_chord(df5_f5, DOTTED_NOTE(QUARTER_NOTE) + EIGTH_NOTE));

  melody_add_beat(melody, beat_from_chord(c5_ef5, EIGTH_NOTE));
  melody_add_beat(melody, beat_from_chord(df5_f5, EIGTH_NOTE));
  melody_add_beat(melody, beat_from_chord(c5_ef5, DOTTED_NOTE(HALF_NOTE) +EIGTH_NOTE));
  melody_add_beat(melody, beat_from_chord(bf4_df5, EIGTH_NOTE));
  melody_add_beat(melody, beat_from_chord(c5_ef5, EIGTH_NOTE));
  beat = beat_from_note(Df5(wave,volume),EIGTH_NOTE+SIXTEENTH_NOTE);
  beat_add_note(&beat,Bf4(wave,volume),DOTTED_NOTE(HALF_NOTE) +EIGTH_NOTE, DOTTED_NOTE(HALF_NOTE) + EIGTH_NOTE); 
  melody_add_beat(melody, beat);
  melody_add_beat(melody, beat_from_note(F5(wave,volume),2*(EIGTH_NOTE+SIXTEENTH_NOTE))); 
  melody_add_beat(melody, beat_from_note(Df5(wave,volume),EIGTH_NOTE+SIXTEENTH_NOTE +EIGTH_NOTE)); 

  melody_add_beat(melody, beat_from_chord(af4_c5, EIGTH_NOTE));
  melody_add_beat(melody, beat_from_chord(bf4_df5, EIGTH_NOTE));
  melody_add_beat(melody, beat_from_chord(af4_c5, DOTTED_NOTE(HALF_NOTE)));





  return melody;
}

static inline Melody *song_claire_de_lune_melody_2(uint8 wave, uint8 volume) {
  Melody *melody = new_melody();

  melody_add_beat(melody, beat_from_note(RST, EIGTH_NOTE));
  melody_add_beat(
      melody, beat_from_chord(f4_af4, QUARTER_NOTE + DOTTED_NOTE(HALF_NOTE)));

  melody_add_beat(melody,
                  beat_from_chord(gf4_a4, DOTTED_NOTE(HALF_NOTE) +
                                              DOTTED_NOTE(QUARTER_NOTE)));

  melody_add_beat(
      melody, beat_from_chord(f4_af4, DOTTED_NOTE(HALF_NOTE) + DOTTED_NOTE(QUARTER_NOTE)));
  
  melody_add_beat(
      melody, beat_from_chord(ef4_gf4,DOTTED_NOTE(HALF_NOTE) + DOTTED_NOTE(QUARTER_NOTE)));

  


  return melody;
}

static inline void song_claire_de_lune_init_chords(uint8 wave, uint8 volume) {
  f4_af4.num_of_notes = 0;
  chord_add_note(&f4_af4, F4(wave, volume));
  chord_add_note(&f4_af4, Af4(wave, volume));

  f5_af5.num_of_notes = 0;
  chord_add_note(&f5_af5, F5(wave, volume));
  chord_add_note(&f5_af5, Af5(wave, volume));

  df5_f5.num_of_notes = 0;
  chord_add_note(&df5_f5, F5(wave, volume));
  chord_add_note(&df5_f5, Df5(wave, volume));

  gf4_a4.num_of_notes = 0;
  chord_add_note(&gf4_a4, Gf4(wave, volume));
  chord_add_note(&gf4_a4, A4(wave, volume));

  c5_ef5.num_of_notes = 0;
  chord_add_note(&c5_ef5, C5(wave, volume));
  chord_add_note(&c5_ef5, Ef5(wave, volume));

  bf4_df5.num_of_notes = 0;
  chord_add_note(&bf4_df5, Bf4(wave, volume));
  chord_add_note(&bf4_df5, Df5(wave, volume));

  ef4_gf4.num_of_notes = 0;
  chord_add_note(&ef4_gf4, Ef4(wave, volume));
  chord_add_note(&ef4_gf4, Gf4(wave, volume));

  af4_c5.num_of_notes = 0;
  chord_add_note(&af4_c5, Af4(wave, volume));
  chord_add_note(&af4_c5, C5(wave, volume));

}

Song *song_get_claire_de_lune(uint8 wave, uint8 volume);
