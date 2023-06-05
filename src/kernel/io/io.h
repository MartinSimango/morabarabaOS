#ifndef _UTIL_
#define _UTIL_

#include "types.h"

#define CLI() asm("cli")
#define STI() asm("sti")

//  ASM defined functions
extern uint8 insb(uint16 port);
extern uint16 insw(uint16 port);

extern void outb(uint16 port, uint8 value);

extern void outw(uint16 port, uint16 value);

static inline uint8 low_byte(uint16 value) { return (uint8)(value & 0xFF); }

static inline uint8 high_byte(uint16 value) {
  return (uint8)((value >> 8) & 0xFF);
}

static void inline enable_interrupts() { STI(); }

static void inline disable_interrupts() { CLI(); }

// Wait a very small amount of time (1 to 4 microseconds, generally)
static inline void io_wait(void) 
{
    outb(0x80, 0);
}

// #define asm __asm__ volatile

// static inline void outb(uint16 port, uint8 value) {
//   asm("outb %0, %1" : : "a"(value), "dN"(port));
// }

// static inline uint8 inb(uint16 port) {
//   uint8 value;
//   asm("inb %1, %0" : "=a"(value) : "dN"(port));
//   return value;
// }

#endif
