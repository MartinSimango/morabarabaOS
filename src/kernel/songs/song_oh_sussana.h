#pragma once

#include "song.h"

static inline Melody *song_get_oh_sussana_melody_1(uint8 wave, uint8 volume) {
  Melody *melody_1 = new_melody();
  melody_add_beat(melody_1, beat_from_note(RST, DOTTED_NOTE(HALF_NOTE)));

  melody_add_beat(melody_1, beat_from_note(C4(wave, volume), EIGTH_NOTE));
  melody_add_beat(melody_1, beat_from_note(D4(wave, volume), EIGTH_NOTE));

  melody_add_beat(melody_1, beat_from_note(E4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1, beat_from_note(G4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1,
                  beat_from_note(G4(wave, volume), DOTTED_NOTE(QUARTER_NOTE)));
  melody_add_beat(melody_1, beat_from_note(A4(wave, volume), EIGTH_NOTE));

  melody_add_beat(melody_1, beat_from_note(G4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1, beat_from_note(E4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1,
                  beat_from_note(C4(wave, volume), DOTTED_NOTE(QUARTER_NOTE)));
  melody_add_beat(melody_1, beat_from_note(D4(wave, volume), EIGTH_NOTE));

  melody_add_beat(melody_1, beat_from_note(E4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1, beat_from_note(E4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1, beat_from_note(D4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1, beat_from_note(C4(wave, volume), QUARTER_NOTE));

  melody_add_beat(melody_1,
                  beat_from_note(D4(wave, volume), DOTTED_NOTE(HALF_NOTE)));
  melody_add_beat(melody_1, beat_from_note(C4(wave, volume), EIGTH_NOTE));
  melody_add_beat(melody_1, beat_from_note(D4(wave, volume), EIGTH_NOTE));

  melody_add_beat(melody_1, beat_from_note(E4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1, beat_from_note(G4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1,
                  beat_from_note(G4(wave, volume), DOTTED_NOTE(QUARTER_NOTE)));
  melody_add_beat(melody_1, beat_from_note(A4(wave, volume), EIGTH_NOTE));

  melody_add_beat(melody_1, beat_from_note(G4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1, beat_from_note(E4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1,
                  beat_from_note(C4(wave, volume), DOTTED_NOTE(QUARTER_NOTE)));
  melody_add_beat(melody_1, beat_from_note(D4(wave, volume), EIGTH_NOTE));

  melody_add_beat(melody_1, beat_from_note(E4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1, beat_from_note(E4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1, beat_from_note(D4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1, beat_from_note(D4(wave, volume), QUARTER_NOTE));

  melody_add_beat(melody_1,
                  beat_from_note(C4(wave, volume), DOTTED_NOTE(HALF_NOTE)));
  melody_add_beat(melody_1, beat_from_note(RST, QUARTER_NOTE));

  melody_add_beat(melody_1, beat_from_note(F4(wave, volume), HALF_NOTE));
  melody_add_beat(melody_1, beat_from_note(F4(wave, volume), HALF_NOTE));

  melody_add_beat(melody_1, beat_from_note(A4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1, beat_from_note(A4(wave, volume), HALF_NOTE));
  melody_add_beat(melody_1, beat_from_note(A4(wave, volume), QUARTER_NOTE));

  melody_add_beat(melody_1, beat_from_note(G4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1, beat_from_note(G4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1, beat_from_note(E4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1, beat_from_note(C4(wave, volume), QUARTER_NOTE));

  melody_add_beat(melody_1,
                  beat_from_note(D4(wave, volume), DOTTED_NOTE(HALF_NOTE)));
  melody_add_beat(melody_1, beat_from_note(C4(wave, volume), EIGTH_NOTE));
  melody_add_beat(melody_1, beat_from_note(D4(wave, volume), EIGTH_NOTE));

  melody_add_beat(melody_1, beat_from_note(E4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1, beat_from_note(G4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1,
                  beat_from_note(G4(wave, volume), DOTTED_NOTE(QUARTER_NOTE)));
  melody_add_beat(melody_1, beat_from_note(A4(wave, volume), EIGTH_NOTE));

  melody_add_beat(melody_1, beat_from_note(G4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1, beat_from_note(E4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1,
                  beat_from_note(C4(wave, volume), DOTTED_NOTE(QUARTER_NOTE)));
  melody_add_beat(melody_1, beat_from_note(D4(wave, volume), EIGTH_NOTE));

  melody_add_beat(melody_1, beat_from_note(E4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1, beat_from_note(E4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1, beat_from_note(D4(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_1, beat_from_note(D4(wave, volume), QUARTER_NOTE));

  melody_add_beat(melody_1,
                  beat_from_note(C4(wave, volume), DOTTED_NOTE(HALF_NOTE)));
  melody_add_beat(melody_1, beat_from_note(RST, QUARTER_NOTE));
  return melody_1;
}

static inline Melody *song_get_oh_sussana_melody_2(uint8 wave, uint8 volume) {
  Melody *melody_2 = new_melody();

  Chord Cbroken;
  Cbroken.num_of_notes = 0;
  // chord_init(&Cbroken);
  chord_add_note(&Cbroken, E3(wave, volume));
  chord_add_note(&Cbroken, G3(wave, volume));

  Chord G7broken;
  G7broken.num_of_notes = 0;
  // chord_init(&G7broken);
  chord_add_note(&G7broken, F3(wave, volume));
  chord_add_note(&G7broken, G3(wave, volume));

  Chord Fbroken;
  Fbroken.num_of_notes = 0;
  // chord_init(&G7broken);
  chord_add_note(&Fbroken, F3(wave, volume));
  chord_add_note(&Fbroken, A3(wave, volume));

  melody_add_beat(melody_2, beat_from_note(RST, WHOLE_NOTE));

  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Cbroken, QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Cbroken, QUARTER_NOTE));

  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Cbroken, QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Cbroken, QUARTER_NOTE));

  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Cbroken, QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Cbroken, QUARTER_NOTE));

  melody_add_beat(melody_2, beat_from_note(D3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(G7broken, QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_note(D3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(G7broken, QUARTER_NOTE));

  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Cbroken, QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Cbroken, QUARTER_NOTE));

  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Cbroken, QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Cbroken, QUARTER_NOTE));

  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Cbroken, QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_note(D3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(G7broken, QUARTER_NOTE));

  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Cbroken, QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Cbroken, QUARTER_NOTE));

  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Fbroken, QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Fbroken, QUARTER_NOTE));

  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Fbroken, QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Fbroken, QUARTER_NOTE));

  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Cbroken, QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Cbroken, QUARTER_NOTE));

  melody_add_beat(melody_2, beat_from_note(D3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(G7broken, QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_note(D3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(G7broken, QUARTER_NOTE));

  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Cbroken, QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Cbroken, QUARTER_NOTE));

  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Cbroken, QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Cbroken, QUARTER_NOTE));

  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Cbroken, QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_note(D3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(G7broken, QUARTER_NOTE));

  melody_add_beat(melody_2, beat_from_note(C3(wave, volume), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_chord(Cbroken, QUARTER_NOTE));
  melody_add_beat(melody_2,
                  beat_from_chord(Maj(C3(wave, volume), 5), QUARTER_NOTE));
  melody_add_beat(melody_2, beat_from_note(RST, QUARTER_NOTE));

  return melody_2;
}

Song *song_get_oh_sussana(uint8 wave, uint8 volume);
