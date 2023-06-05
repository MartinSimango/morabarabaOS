#include "screen.h"
#include "console.h"
#include "idt.h"
#include "font.h"
#include "io.h"
#include "irq.h"
#include "kheap.h"
#include "vbe.h"
#include "timer.h"
#include "sb16.h"
#include "fpu.h"
#include "music.h"
#include "tty.h"
#include "vc.h"
#include "print.h"
#include "terminal.h"


struct vc vc_consoles[2];

// // fixed width integer types
// typedef unsigned char u8;
// typedef unsigned short u16;

// #ifndef asm
// #define asm __asm__ volatile
// #endif

// #define CLI() asm ("cli")
// #define STI() asm ("sti")
// // VGA control port addresses
// #define PALETTE_MASK 0x3C6
// #define PALETTE_READ 0x3C7
// #define PALETTE_WRITE 0x3C8
// #define PALETTE_DATA 0x3C9

// static inline void outportb(u16 port, u8 data) {
//     asm("outb %1, %0" : : "dN" (port), "a" (data));
// }

// void palleteSet(int index) {
//     // CLI();
//     outportb(PALETTE_MASK, index);
//     outportb(PALETTE_DATA, 0);
//     outportb(PALETTE_DATA, 50);
//     outportb(PALETTE_DATA, 0);
//     // STI();
// }
// void _start() {
//     unsigned short *VGA_MEMORY = (unsigned short*) (0x0A0000);
//     // unsigned char *VGA_MEMORY = (unsigned char*) (0xb8000);

//     VGA_MEMORY[0] = 15;
//     // VGA_MEMORY[1] = 0x4444;
//     // VGA_MEMORY[293]= 0x4444;
//     VGA_MEMORY[2] = 15;
//     VGA_MEMORY[4] = 'L';
//     VGA_MEMORY[6] = 'L';
//     VGA_MEMORY[8] = 'O';
//     VGA_MEMORY[10] = 'W';
//     VGA_MEMORY[12] = 'O';
//     VGA_MEMORY[14] = 'R';
//     VGA_MEMORY[16] = 'L';
//     VGA_MEMORY[18] = 'D';
//     VGA_MEMORY[20] = '!';
//     // for(;;){}
//     // configure palette with 8-bit RRRGGGBB color
//     // outportb(PALETTE_MASK, 0xFF);
//     // outportb(PALETTE_WRITE, 0);
//     // for (u8 i = 0; i < 255; i++) {
//     //     outportb(PALETTE_DATA, (((i >> 5) & 0x7) * (256 / 8)) / 4);
//     //     outportb(PALETTE_DATA, (((i >> 2) & 0x7) * (256 / 8)) / 4);
//     //     outportb(PALETTE_DATA, (((i >> 0) & 0x3) * (256 / 4)) / 4);
//     // }

//     // // set color 255 = white
//     // outportb(PALETTE_DATA, 0x3F);
//     // outportb(PALETTE_DATA, 0x3F);
//     // outportb(PALETTE_DATA, 0x3F);

//     // for (u8 i = 1; i < 255; i++) {
//     //     palleteSet(i);
//     // }
//     for(;;){}


// }

// int main() {
//     return 0;
// }
// unsigned short *VGA_MEMORY = (unsigned short*) 0x0A0000;

// void enable_cursor(uint8 cursor_start, uint8 cursor_end)
// {
// 	outb(0x3D4, 0x0A);
// 	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
 
// 	outb(0x3D4, 0x0B);
// 	outb(0x3D5, (inb(0x3D5) & 0xE0) | cursor_end);
// }


void start_kernel() {
    kheap_init();
    console_init();

    idt_init();
    irq_init();
    timer_init();
    fpu_init();
    enable_interrupts();
    terminal_init();
    printk("Hello World!");



    terminal_print_default("martinsimango@customkernel ~ % Hello World!\n");
    sb16_init(); 
    music_init();   


    music_play_song(song_get_oh_sussana, WAVE_TRIANGLE); 

    music_set_volume(10);
    music_loop_single();
    while(1);
    // sb16_pause_sound();


    
}