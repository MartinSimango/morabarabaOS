#ifndef _UTIL_
#define _UTIL_

#define asm __asm__ volatile



#define CLI() asm ("cli")
#define STI() asm ("sti")


typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;

static inline void outb(uint16 port, uint8 value) {
    asm ("outb %0, %1" : : "a" (value), "dN" (port));
}
static inline uint8 inb(uint16 port) {
    uint8 value;
    asm ("inb %1, %0" : "=a" (value) : "dN" (port));
    return value;
}




#endif


