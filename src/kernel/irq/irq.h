#ifndef _IRQ_H
#define _IRQ_H

#include "types.h"

void remap_pic();

void irq_init();

void irq_clear_mask(uint8 IRQline);

void irq_end_of_interrupt();

#endif