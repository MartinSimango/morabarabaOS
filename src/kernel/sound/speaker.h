#ifndef _SPEAKER_H_
#define _SPEAKER_H_

#include "io.h"
#include "types.h"

// /Play sound using built in speaker
static inline void speaker_play_sound(uint32 nFrequence) {
  uint32 Div;
  uint8 tmp;

  // Set the PIT to the desired frequency
  Div = 1193180 / nFrequence;
  outb(0x43, 0xb6);
  outb(0x42, (uint8)(Div));
  outb(0x42, (uint8)(Div >> 8));

  // And play the sound using the PC speaker
  tmp = insb(0x61);
  if (tmp != (tmp | 3)) {
    outb(0x61, tmp | 3);
  }
}

// make it shutup
static inline void speaker_nosound() {
  uint8 tmp = insb(0x61) & 0xFC;
  outb(0x61, tmp);
}

#endif