#ifndef _UTIL_
#define _UTIL_

#include "types.h"

#define CLI() asm("cli")
#define STI() asm("sti")

uint8 insb(uint16 port);
uint16 insw(uint16 port);

void outb(uint16 port, uint8 value);

void outw(uint16 port, uint16 value);

static inline uint8 low_byte(uint16 value) { return (uint8)(value & 0xFF); }

static inline uint8 high_byte(uint16 value) {
  return (uint8)((value >> 8) & 0xFF);
}

static void inline enable_interrupts() { STI(); }

static void inline disable_interrupts() { CLI(); }

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
