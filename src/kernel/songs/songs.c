#include "song_claire_de_lune.h"
#include "song_oh_sussana.h"

Song *song_get_oh_sussana(uint8 wave, uint8 volume) {
  Song *song = kmalloc(sizeof(Song));
  song->melodies[0] = song_get_oh_sussana_melody_1(wave, volume);
  song->melodies[1] = song_get_oh_sussana_melody_2(wave, volume);
  song->melody_count = 2;
  return song;
}

Song *song_get_claire_de_lune(uint8 wave, uint8 volume) {
  song_claire_de_lune_init_chords(wave, volume);
  Song *song = (Song *)kmalloc(sizeof(Song));
  song->melodies[0] = song_claire_de_lune_melody_1(wave, volume);
  song->melodies[1] = song_claire_de_lune_melody_2(wave, volume);
  song->melody_count = 2;
  return song;
}
