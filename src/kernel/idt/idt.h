#ifndef _IDT_
#define _IDT_

#include "types.h"

//  Offset is the simply the address of the ISR (Interrupt Service Routine)
struct idt_desc {
  uint16 offset_low;  // Offset bits 0 - 15
  uint16 selector;    // Selector thats in our GDT
  uint8 zero;         // Does nothing, unused set to zero
  uint8 type_attr;    // Descriptor type and attributes
  uint16 offset_high; // Offset bits 16-31
} __attribute__((packed));

// The address of the below will be loaded into memory with the ldtr instruction
struct idtr_desc {
  uint16 limit; // Size of descriptor table -1
  uint32 base;  // Base address of the start of the interrupt descriptor table
} __attribute__((packed));

void idt_init();

#endif