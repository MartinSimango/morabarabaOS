#include "screen.h"


void init_pallete(RGB * pallete, uint8 pallette_size) {
    // CLI();
    // outb(PALETTE_DATA_REGISTER, 0xFF);
    // // // STI();
    // struct RGB colour;
    // // pallete_set(0, colour = WHITE);
    // for (uint8 i = 0; i < pallette_size; i++) {
    //     // pallete_set(i, pallete[i]); 
    // }
    // pallete_set(0, colour = BLACK);
}



void init_default_pallete() {
    // CLI();
    outb(PALETTE_DATA_REGISTER, 0xFF);
    // STI();
    struct RGB colour;
    pallete_set(0, colour = WHITE);
    for(uint8 i = 1; i< 255; i++) {
        colour.red = (((i >> 5) & 0x7) * (256 / 8)) / 4;
        colour.green = (((i >> 2) & 0x7) * (256 / 8)) / 4;
        colour.blue = (((i >> 0) & 0x3) * (256 / 4)) / 4;
        pallete_set(i, colour);
    }
    pallete_set(255, colour = BLACK);

}

void pallete_set(uint8 index, struct RGB colour) {
  //  CLI();
    outb(PALETTE_WRITE_REGISTER, index);
    outb(PALETTE_DATA_REGISTER, colour.red);
    outb(PALETTE_DATA_REGISTER, colour.green);
    outb(PALETTE_DATA_REGISTER, colour.blue);
 //   STI();
}


void init_screen() {
  
    init_default_pallete();
    
    uint8 *VGA_MEMORY = (uint8*) 0x0A0000;

    for (int width = 0; width < SCREEN_WIDTH; width++)
    {
        for (int height = 0; height < SCREEN_HEIGHT; height++)
        {
            // uint16 offset = (height<<8) + (height<<6) + width;
            uint16 offset = width + height*SCREEN_WIDTH;
            VGA_MEMORY[offset] = height+1;

        }
        
    }
    
}