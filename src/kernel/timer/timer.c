#include "timer.h"
#include "io.h"

struct timer timer;

void int20h_timer_handler() {
  timer.tick++;
  irq_end_of_interrupt();
}

uint64 get_timer_count() { return timer.tick; }

void set_pit_count(uint16 reload_value) {
  outb(PIT_CHANNEL_MODE, PIT_MODE);

  // set reload value
  outb(PIT_CHANNEL_0, low_byte(reload_value));  // Low byte
  outb(PIT_CHANNEL_0, high_byte(reload_value)); // High byte
}

void timer_init() {
  timer.tick = 0;
  timer.reloadValue = PIT_TIMER_RELOAD_VALUE;
  timer.frequency = PIT_HZ / PIT_TIMER_RELOAD_VALUE;

  set_pit_count(timer.reloadValue);
}

// time in ms
void timer_sleep(uint32 time) {
  // uint32 time_to_cut = time/1000.0 *160;
  // time = time - time_to_cut; // cut out some milliseconds due to inaccuaries
  // with clock in qemu uint64 start = get_timer_count();

  // while ((get_timer_count() - start) < time) {
  // }
  uint64 clock_speed = 150000;
  uint32 count = 0;
  while (count < time) {
    for (uint64 i = 0; i < clock_speed; i++) {
      asm("nop");
    }
    count++;
  }
}
