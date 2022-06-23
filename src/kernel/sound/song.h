#ifndef _SONG_H
#define _SONG_H

#include "melody.h"
#include "types.h"

#define MAX_MELODIES_IN_SONG 5

typedef struct Song {
  Melody *melodies[MAX_MELODIES_IN_SONG];
  uint8 melody_count;
} Song;

static inline void song_free(Song *song) {
  for (uint8 i = 0; i < song->melody_count; i++) {
    melody_free(song->melodies[i]);
  }
  kfree(song);
}

#endif