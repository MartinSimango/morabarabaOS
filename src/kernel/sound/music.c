#include "music.h"
#include "heap.h"
#include "kheap.h"
#include "math.h"
#include "melody.h"
#include "memory.h"
#include "sb16.h"
#include "speaker.h"
#include "timer.h"
#include "tty.h"

bool is_music_playing = false;
uint32 music_current_song_beat = 0;
uint32 music_current_song_num_beats = 0;
Beat *music_playing_beat = NULL;
uint32 music_timer = 0;

Song_Func music_song_list[2];
uint8 music_song_index = 0;
uint8 MUSIC_LOOP_STATE = MUSIC_LOOP_NONE;

void music_init() {
  seed(get_timer_count());
  chords_init();

  music_song_list[0] = song_get_oh_sussana;
  music_song_list[1] = song_get_claire_de_lune;
}

void music_pause() {
  sb16_is_sb16_supported() ? sb16_pause_sound() : speaker_nosound();
  is_music_playing = false;
}

Song_Func music_load_song() { return music_song_list[music_song_index]; }

void music_play() {
  if (sb16_is_sb16_supported()) {
    sb16_play_sound();
  }
  if (music_playing_beat == NULL) {
    music_play_song(music_load_song(), note_get_note_wave()); // load a song
  }
  is_music_playing = true;
}

void music_stop() {
  music_current_song_beat = 0;
  music_pause();
  music_free_playing_beat();
}

void music_play_beat(Beat beat) {
  sb16_set_notes(beat.notes, beat.num_notes);
  timer_sleep(beat_max_duration_in_beat(beat));
}

void music_play_melody(Melody melody) {
  for (uint16 i = 0; i < melody.beats_length; i++) {
    music_play_beat(melody.beats[i]);
  }
}

void music_play_song_melody(Song song, uint8 melody_count) {
  if (melody_count > song.melody_count) {
    music_play_melody(*song.melodies[0]);
    return;
  }
  music_play_melody(*song.melodies[melody_count]);
}

uint32 music_find_max_melody_duration_in_song(Song song, uint8 melody_count) {
  uint32 max_melody_duration = 0;
  for (uint16 i = 0; i < melody_count; i++) {
    if (song.melodies[i]->melody_durtaion > max_melody_duration) {
      max_melody_duration = song.melodies[i]->melody_durtaion;
    }
  }
  return max_melody_duration;
}

Beat *music_combine_melodies_from_song(Song song, uint16 num_of_beats) {

  Beat *combined_beats = kmalloc(sizeof(Beat) * num_of_beats);
  memset(combined_beats, 0, sizeof(Beat) * num_of_beats);
  for (uint16 j = 0; j < song.melody_count; j++) {
    uint16 beat_count = 0;
    for (uint16 k = 0; k < song.melodies[j]->beats_length; k++) {
      uint16 beat_ticks =
          beat_min_duration_in_beat(song.melodies[j]->beats[k]) /
          (SIXTEENTH_NOTE);
      for (uint16 l = 0; l < beat_ticks; l++) {
        for (uint16 n = 0; n < song.melodies[j]->beats[k].num_notes; n++) {
          Beat *current_beat = &combined_beats[beat_count];
          uint8 note_num = current_beat->num_notes;
          uint16 duration = song.melodies[j]->beats[k].duration[n];
          uint16 duration_left_to_play = 0;
          if (duration - ((l)*SIXTEENTH_NOTE) > 0) {
            duration_left_to_play = duration - ((l)*SIXTEENTH_NOTE);
          }
          beat_add_note(current_beat, song.melodies[j]->beats[k].notes[n],
                        duration, duration_left_to_play);

          if (l == beat_ticks - 1) { // on last tick
            // find how many beats to extend for
            uint16 ticks =
                (duration_left_to_play - SIXTEENTH_NOTE) / (SIXTEENTH_NOTE);

            if(ticks == 0 ) {
              continue;
            }
            // tty_print_default(" Ticks: ");
            // tty_print_int_default(ticks);
            // tty_print_default(" END \n");

            Note no = song.melodies[j]->beats[k].notes[n];

             no.extended_note = true;
              // uint16 d =
              //     duration_left_to_play - SIXTEENTH_NOTE - ((k)*SIXTEENTH_NOTE);
              no.extended_note_index = note_num;
              beat_add_note(&combined_beats[beat_count + 1], no, 0, 0);

            for (uint16 h = 1; h < ticks; h++) {
              no.extended_note = true;
              no.extended_note_index =
                  combined_beats[beat_count + h].num_notes-1;
              beat_add_note(&combined_beats[beat_count+h+1], no, 0, 0);
            }

          }
        }
        beat_count++; // new beat added
      }
    }
  }

  return combined_beats;
}

uint8 get_song_index(Song_Func get_song) {

  for (uint8 i = 0; i < 2; i++) {

    if (music_song_list[i] == get_song) {
      return i;
    }
  }
  return 0; // should crash as song would not be in our song list
}

void music_play_song(Song_Func get_song, uint8 wave) {
  note_set_note_wave(wave);
  Song *song = get_song();
  uint32 max_melody_duration =
      music_find_max_melody_duration_in_song(*song, song->melody_count);

  music_current_song_num_beats = max_melody_duration / (SIXTEENTH_NOTE);

  music_free_playing_beat();
  music_playing_beat =
      music_combine_melodies_from_song(*song, music_current_song_num_beats);

  song_free(song); // beats are loaded song data can now be freed

  music_song_index = get_song_index(get_song);
  music_play(wave);
  music_current_song_beat = 0;
  music_load_next_beat();
}

float64 music_get_sample(Note note, uint64 sample_rate, uint8 volume,
                         uint16 sample_scale) {
  float64 freq = (note.freq / sample_rate);
  uint32 sample = note.sample_count * sample_scale;
  switch (note.wave_type) {
  case WAVE_SIN:
    return sin(2.0 * PI * freq * sample) * volume;
  case WAVE_SQUARE:
    return (sin(2.0 * PI * freq * sample) < 0) ? -volume : volume;
  case WAVE_TRIANGLE: {
    float64 p = 1 / freq;
    float64 mod = fmod((sample - (p / 4)), p);
    return ((4 * volume) / p) * fabs((mod)-p / 2) - volume;
  }
  case WAVE_PIANO_1: {
    float64 val =
           (sin(PI * sample * freq) * sin(PI * sample * freq) *
                sin(PI * sample * freq) +
            sin(PI * (sample * freq +
                      2 / 3))); 
    val += sin(2  * PI * freq * sample) +
           sin(PI * (sample * freq +
                      2 / 3)) / 2;
    // val += sin(3  * PI * freq * sample) +
    //        sin(PI * (sample * freq +
    //                   2 / 3)) / 4;
    // val += sin(4  * PI * freq * sample) +
    //        sin(PI * (sample * freq +
    //                   2 / 3)) / 8;
    // val += sin(5  * PI * freq * sample) +
    //         sin(PI * (sample * freq +
    //                   2 / 3))/ 16;
    // val += sin(6  * PI * freq * sample) +
    //        sin(PI * (sample * freq +
    //                   2 / 3))/ 32;
      return val * volume ;
  }

                  
  case WAVE_PIANO_2: {
    float64 val = 0.6 * sin(2 * PI * freq * sample) *
                  exp(-0.0004 * 2 * PI * freq * sample);
    val += 0.4 * sin(2 * PI * freq * sample) *
           exp(-0.0004 * 2 * PI * freq * sample);
    // val += sin(2 * 2 * PI * freq * sample) *
    //        exp(-0.0004 * 2 * PI * freq * sample) / 2;
    // val += sin(3 * 2 * PI * freq * sample) *
    //        exp(-0.0004 * 2 * PI * freq * sample) / 4;
    // val += sin(4 * 2 * PI * freq * sample) *
    //        exp(-0.0004 * 2 * PI * freq * sample) / 8;
    // val += sin(5 * 2 * PI * freq * sample) *
    //        exp(-0.0004 * 2 * PI * freq * sample) / 16;
    val += sin(6 * 2 * PI * freq * sample) *
           exp(-0.0004 * 2 * PI * freq * sample) / 32;
    val += val * val * val;
    return val * volume;
  }
  }
  return 0;
}

void music_play_single_beat(Beat *beat_playing) {
  if (sb16_is_sb16_supported()) {
    sb16_set_notes(beat_playing->notes, beat_playing->num_notes);
    return;
  }

  if (beat_playing->notes[0].freq != 0) {
    speaker_play_sound(beat_playing->notes[0].freq);
  }
}

void music_update_sample_count_of_notes(Beat *beat_playing) {
  for (uint8 i = 0; i < beat_playing->num_notes; i++) {
    if (beat_playing->notes[i].extended_note) {
      beat_playing->notes[i].sample_count =
          sb16_get_sb16_card()
              .notes[beat_playing->notes[i].extended_note_index]
              .sample_count;
      // tty_print_int_default(sb16_get_sb16_card()
      //         .notes[beat_playing->notes[i].extended_note_index]
      //         .freq);
      // tty_print_default(" B: ");
      // tty_print_int_default(music_current_song_beat);
      //       tty_print_default("\n");

    }
    else if ((beat_playing->duration_left_to_play[i] < beat_playing->duration[i]) &&
        beat_playing->duration_left_to_play > 0) {
      beat_playing->notes[i].sample_count =
          sb16_get_sb16_card().notes[i].sample_count;
    }
  }
}

void music_check_if_song_done() {
  if (music_current_song_beat >= music_current_song_num_beats) {
    switch (MUSIC_LOOP_STATE) {
    case MUSIC_LOOP_NONE:
      if (music_song_index + 1 >= 2) {
        music_stop();
      } else {
        music_next();
      }
      return;
    case MUSIC_LOOP_SINGLE:
      music_current_song_beat = 0;
      return;
    case MUSIC_LOOP_ALL:
      music_next();
      return;
    }
    music_stop();
  }
}

void music_load_next_beat() {
  if (is_music_playing) {
    music_update_sample_count_of_notes(
        &music_playing_beat[music_current_song_beat]);
    music_play_single_beat(&music_playing_beat[music_current_song_beat]);
    music_current_song_beat++;
    music_check_if_song_done();
  }
}

void music_restart_song() { music_current_song_beat = 0; }

void music_free_playing_beat() {
  if (music_playing_beat != NULL) {
    kfree(music_playing_beat);
  }
  music_playing_beat = NULL;
}

void music_next() {
  music_song_index = (music_song_index + 1) % 2;
  music_free_playing_beat();
  music_play(0, 50);
}

void music_previous() {
  music_song_index = (music_song_index - 1) % 2;
  music_free_playing_beat();
  music_play(0, 50);
}

void music_set_volume(uint8 volume) { sb16_set_master_volume(volume); }