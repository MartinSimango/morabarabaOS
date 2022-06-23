#ifndef _TIMER_H_
#define _TIMER_H_

#include "io.h"
#include "irq.h"
#include "kheap.h"
#include "types.h"

#define PIT_CHANNEL_0 0x40
#define PIT_CHANNEL_1 0x41
#define PIT_CHANNEL_2 0x42
#define PIT_CHANNEL_MODE 0x43

#define PIT_MODE 0x36 // 0x36 /00111100

#define PIT_HZ 1193182

#define PIT_TIMER_RELOAD_VALUE 1192; // Each clock tick will be a millsecond

extern struct timer {
  uint16 reloadValue;
  uint64 tick;
  uint32 tickCount;
  uint32 frequency;
} timer;

void int20h_timer_handler();

void set_pit_count(uint16 count);
void timer_init();
void timer_sleep(uint32 time);

uint64 get_timer_count();

static uint32 rseed = 1;

static inline void seed(uint32 s) { rseed = s; }

static inline uint32 rand() {
  static uint32 x = 123456789;
  static uint32 y = 362436069;
  static uint32 z = 521288629;
  static uint32 w = 88675123;

  x *= 23786259 - rseed;

  uint32 t;

  t = x ^ (x << 11);
  x = y;
  y = z;
  z = w;
  return w = w ^ (w >> 19) ^ t ^ (t >> 8);
}

#endif