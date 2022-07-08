#ifndef _MUSIC_H_
#define _MUSIC_H_

#include "beat.h"
#include "io.h"
#include "song.h"
#include "song_claire_de_lune.h"
#include "song_oh_sussana.h"
#include "tty.h"
#include "types.h"

typedef Song *(*Song_Func)();

extern bool is_music_playing;

extern uint32 music_current_song_beat;

extern uint32 music_current_song_num_beats;

extern Beat *music_playing_beat;

extern uint32 music_timer;

extern uint8 music_song_index;

extern Song_Func music_song_list[2];

extern uint8 MUSIC_LOOP_STATE;

#define MUSIC_LOOP_NONE 0
#define MUSIC_LOOP_SINGLE 1
#define MUSIC_LOOP_ALL 2

void music_init();

void music_play_beat(Beat beat);

void music_play_melody(Melody melody);

void music_play_song(Song_Func get_song, uint8 wave);

void music_play_song_melody(Song song, uint8 melody_count);

float64 music_get_sample(Note note, uint64 sample_rate, uint8 volume,
                         uint16 sample_scale);

static inline bool music_is_music_playing() { return is_music_playing; }

static inline uint32 music_get_current_song_beat() {
  return music_current_song_beat;
}

static inline void music_tick() { music_timer++; }

static inline void music_timer_reset() { music_timer = 0; }

static inline uint32 music_get_timer() { return music_timer; }

void music_load_next_beat();

void music_pause();

void music_play();

void music_set_volume(uint8 volume);

void music_stop();

void music_restart_song();

void music_next();

void music_previous();

static inline void music_loop_single() { MUSIC_LOOP_STATE = MUSIC_LOOP_SINGLE; }

static inline void music_loop_all() { MUSIC_LOOP_STATE = MUSIC_LOOP_ALL; }

static inline void music_loop_none() { MUSIC_LOOP_STATE = MUSIC_LOOP_NONE; }

void music_free_playing_beat();

#endif
