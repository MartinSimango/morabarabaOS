#ifndef _COLOURS_
#define _COLOURS_

#include "util.h"

typedef struct RGB
{
    uint8 red;
    uint8 green;
    uint8 blue;
} RGB;


static const RGB WHITE  =  (RGB) {63,63,63};
static const RGB BLACK  =  (RGB) {0,0,0};
static const RGB RED    =  (RGB) {63,0,0};
static const RGB GREEN  =  (RGB) {0,63,0};
static const RGB BLUE   =  (RGB) {0,0,63};
static const RGB YELLOW =  (RGB) {63,63,0};
static const RGB PURPLE =  (RGB) {30,0,30};
static const RGB PINK   =  (RGB) {63,105,180};
static const RGB LIGHT_BLUE = (RGB) {0,63,63};


// static RGB SCREEN_PALETTE[1] = {
//     GREEN
// };
void init_colours();


#endif