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
  if (time > 200) {
    time =
        time -
        200; // cut out some milliseconds due to inaccuaries with clock in qemu
  }
  uint64 start = get_timer_count();

  while ((get_timer_count() - start) < time) {
    // tty_print_int_default(timer.tick);
    // tty_print_default(" ");
    // tty_print_int_default(get_timer_count());
  }
}
