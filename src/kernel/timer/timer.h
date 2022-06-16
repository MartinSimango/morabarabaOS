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

#endif