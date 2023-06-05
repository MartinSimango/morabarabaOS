#include "song_claire_de_lune.h"
#include "song_oh_sussana.h"

Song *song_get_oh_sussana() {
  beat_set_bpm(200);
  Song *song = kmalloc(sizeof(Song));
  song->melodies[0] = song_get_oh_sussana_melody_1();
  song->melodies[1] = song_get_oh_sussana_melody_2();
  song->melody_count = 2;
  return song;
}

Song *song_get_claire_de_lune() {
  beat_set_bpm(200);
  beat_set_beat_note(8);
  Song *song = (Song *)kmalloc(sizeof(Song));
  song->melodies[0] = song_claire_de_lune_melody_1();
  song->melodies[1] = song_claire_de_lune_melody_2();
  song->melody_count = 2;
  return song;
}
