#pragma once

#include "song.h"

static Chord chord;
static Beat beat;

static inline Melody *song_claire_de_lune_melody_1() {
  Melody *melody = new_melody();
  // // Bar 1
  melody_add_beat(melody, beat_from_note(RST, EIGTH_NOTE + EIGTH_NOTE));

  melody_add_beat(melody,
                  beat_from_chord(chord_add_notes(&chord, 2, F5, Af5),
                                  EIGTH_NOTE + DOTTED_NOTE(QUARTER_NOTE)));

  melody_add_beat(melody,
                  beat_from_chord(chord_add_notes(&chord, 2, Df5, F5),
                                  DOTTED_NOTE(QUARTER_NOTE) + EIGTH_NOTE));

  // c5_ef5
  melody_add_beat(
      melody, beat_from_chord(chord_add_notes(&chord, 2, C5, Ef5), EIGTH_NOTE));
  melody_add_beat(
      melody, beat_from_chord(chord_add_notes(&chord, 2, Df5, F5), EIGTH_NOTE));
  melody_add_beat(melody, beat_from_chord(chord_add_notes(&chord, 2, C5, Ef5),
                                          DOTTED_NOTE(HALF_NOTE) + EIGTH_NOTE));
  melody_add_beat(melody, beat_from_chord(chord_add_notes(&chord, 2, Bf4, Df5),
                                          EIGTH_NOTE));
  melody_add_beat(
      melody, beat_from_chord(chord_add_notes(&chord, 2, C5, Ef5), EIGTH_NOTE));

  beat = beat_from_note(Df5, EIGTH_NOTE + SIXTEENTH_NOTE);
  beat_add_extended_note(&beat, Bf4, DOTTED_NOTE(HALF_NOTE) + EIGTH_NOTE);
  melody_add_beat(melody, beat);
  melody_add_beat(melody,
                  beat_from_note(F5, 2 * (EIGTH_NOTE + SIXTEENTH_NOTE)));
  melody_add_beat(
      melody, beat_from_note(Df5, EIGTH_NOTE + SIXTEENTH_NOTE + EIGTH_NOTE));

  melody_add_beat(
      melody, beat_from_chord(chord_add_notes(&chord, 2, Af4, C5), EIGTH_NOTE));
  melody_add_beat(melody, beat_from_chord(chord_add_notes(&chord, 2, Bf4, Df5),
                                          EIGTH_NOTE));

  beat = beat_from_note(Af4, DOTTED_NOTE(HALF_NOTE));
  beat_add_extended_note(&beat, C5, DOTTED_NOTE(HALF_NOTE) + EIGTH_NOTE);
  melody_add_beat(melody, beat);

  beat = beat_from_note(RST, EIGTH_NOTE);
  beat_add_extended_note(&beat, Gf4, DOTTED_NOTE(HALF_NOTE));
  melody_add_beat(melody, beat);

  melody_add_beat(melody, beat_from_note(Bf4, EIGTH_NOTE));
  melody_add_beat(melody, beat_from_note(C5, EIGTH_NOTE));
  melody_add_beat(melody, beat_from_note(Bf4, EIGTH_NOTE));
  melody_add_beat(melody, beat_from_note(Ef5, EIGTH_NOTE));
  melody_add_beat(melody, beat_from_note(Bf4, EIGTH_NOTE));

  beat = beat_from_note(Af4, EIGTH_NOTE);
  beat_add_extended_note(&beat, Gf4, DOTTED_NOTE(QUARTER_NOTE));
  melody_add_beat(melody, beat);

  melody_add_beat(melody, beat_from_note(Bf4, EIGTH_NOTE));

  beat = beat_from_note(RST, EIGTH_NOTE);
  beat_add_extended_note(&beat, Af4, QUARTER_NOTE);
  melody_add_beat(melody, beat);

  // dasd
  beat = beat_from_note(RST, EIGTH_NOTE);
  beat_add_extended_note(&beat, Ef4, DOTTED_NOTE(HALF_NOTE));
  melody_add_beat(melody, beat);

  melody_add_beat(melody, beat_from_note(Gf4, EIGTH_NOTE));
  melody_add_beat(melody, beat_from_note(Af4, EIGTH_NOTE));
  melody_add_beat(melody, beat_from_note(Gf4, DOTTED_NOTE(QUARTER_NOTE)));

  beat = beat_from_note(Ef4, DOTTED_NOTE(QUARTER_NOTE));
  beat_add_extended_note(&beat, F4, DOTTED_NOTE(QUARTER_NOTE) + EIGTH_NOTE);
  melody_add_beat(melody, beat);

  beat = beat_from_note(RST, EIGTH_NOTE);
  beat_add_extended_note(&beat, Df4,
                         DOTTED_NOTE(HALF_NOTE) + DOTTED_NOTE(QUARTER_NOTE));
  melody_add_beat(melody, beat);

  melody_add_beat(melody, beat_from_note(F4, EIGTH_NOTE));
  melody_add_beat(melody, beat_from_note(Gf4, EIGTH_NOTE));
  melody_add_beat(melody, beat_from_note(F4, EIGTH_NOTE));
  melody_add_beat(melody, beat_from_note(Bf4, EIGTH_NOTE));

  melody_add_beat(melody, beat_from_note(F4, EIGTH_NOTE));

  melody_add_beat(melody, beat_from_note(Ef4, EIGTH_NOTE));
  melody_add_beat(melody, beat_from_note(F4, EIGTH_NOTE));

  beat = beat_from_note(RST, EIGTH_NOTE);
  beat_add_extended_note(&beat, Ef4, EIGTH_NOTE);
  melody_add_beat(melody, beat);

  beat = beat_from_note(RST, EIGTH_NOTE);
  beat_add_extended_note(&beat, Bf3, DOTTED_NOTE(HALF_NOTE));
  melody_add_beat(melody, beat);

  melody_add_beat(melody, beat_from_note(Df4, EIGTH_NOTE));
  melody_add_beat(melody, beat_from_note(Ef4, EIGTH_NOTE));

  melody_add_beat(melody, beat_from_note(Df4, DOTTED_NOTE(QUARTER_NOTE)));

  melody_add_beat(melody, beat_from_chord(chord_add_notes(&chord, 2, Af3, C4),
                                          DOTTED_NOTE(QUARTER_NOTE)));

  melody_add_beat(melody, beat_from_note(RST, 2 * EIGTH_NOTE));

  melody_add_beat(melody, beat_from_chord(chord_add_notes(&chord, 2, F5, Af5),
                                          DOTTED_NOTE(QUARTER_NOTE)));
  melody_add_beat(melody, beat_from_chord(chord_add_notes(&chord, 2, Df5, F5),
                                          DOTTED_NOTE(QUARTER_NOTE)));

  return melody;
}

static inline Melody *song_claire_de_lune_melody_2() {
  Melody *melody = new_melody();
  melody_add_beat(melody, beat_from_note(RST, EIGTH_NOTE));
  melody_add_beat(melody,
                  beat_from_chord(chord_add_notes(&chord, 2, F4, Af4),
                                  QUARTER_NOTE + DOTTED_NOTE(HALF_NOTE)));

  melody_add_beat(melody, beat_from_chord(chord_add_notes(&chord, 2, Gf4, A4),
                                          DOTTED_NOTE(HALF_NOTE) +
                                              DOTTED_NOTE(QUARTER_NOTE)));

  melody_add_beat(melody, beat_from_chord(chord_add_notes(&chord, 2, F4, Af4),
                                          DOTTED_NOTE(HALF_NOTE) +
                                              DOTTED_NOTE(QUARTER_NOTE)));

  melody_add_beat(melody, beat_from_chord(chord_add_notes(&chord, 2, Ef4, Gf4),
                                          DOTTED_NOTE(HALF_NOTE) +
                                              DOTTED_NOTE(QUARTER_NOTE)));

  melody_add_beat(melody, beat_from_chord(chord_add_notes(&chord, 2, Df4, Ef4),
                                          DOTTED_NOTE(HALF_NOTE)));

  melody_add_beat(melody, beat_from_chord(chord_add_notes(&chord, 2, C4, Ef4),
                                          DOTTED_NOTE(QUARTER_NOTE)));

  // dasd
  melody_add_beat(melody, beat_from_chord(chord_add_notes(&chord, 2, Bf3, Df4),
                                          DOTTED_NOTE(HALF_NOTE)));

  melody_add_beat(melody, beat_from_chord(chord_add_notes(&chord, 2, A3, C4),
                                          DOTTED_NOTE(QUARTER_NOTE)));

  beat = beat_from_note(Af3, DOTTED_NOTE(HALF_NOTE));
  beat_add_extended_note(&beat, Bf3,
                         DOTTED_NOTE(HALF_NOTE) + DOTTED_NOTE(QUARTER_NOTE));
  melody_add_beat(melody, beat);

  melody_add_beat(melody, beat_from_note(Gf3, DOTTED_NOTE(QUARTER_NOTE)));

  melody_add_beat(melody, beat_from_chord(chord_add_notes(&chord, 2, F3, Af3),
                                          DOTTED_NOTE(HALF_NOTE)));

  beat = beat_from_note(Ef3, EIGTH_NOTE);
  beat_add_extended_note(&beat, Gf3, DOTTED_NOTE(QUARTER_NOTE));
  melody_add_beat(melody, beat);

  beat = beat_from_note(RST, EIGTH_NOTE);
  beat_add_extended_note(&beat, Af2, EIGTH_NOTE + EIGTH_NOTE);
  melody_add_beat(melody, beat);

  beat = beat_from_note(RST, EIGTH_NOTE);
  beat_add_extended_note(&beat, Df2, 3 * EIGTH_NOTE);
  melody_add_beat(melody, beat);

  melody_add_beat(
      melody, beat_from_chord(chord_add_notes(&chord, 2, Af3, F3), EIGTH_NOTE));

  melody_add_beat(melody, beat_from_chord(chord_add_notes(&chord, 2, F4, Af4),
                                          EIGTH_NOTE + DOTTED_NOTE(HALF_NOTE)));

  return melody;
}

Song *song_get_claire_de_lune();
