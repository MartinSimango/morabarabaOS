#include "idt.h"
#include "io.h"
#include "irq.h"
#include "memory.h"
#include "timer.h"
#include "tty.h"

#define TOTAL_INTERRUPTS 256
#define KERNEL_CODE_SEGMENT 0x08
#define KERNEL_DATA_SEGMENT 0x10 // 0x2ffff

// ASM defined functions

extern void no_interrupt();
extern void idt_load(struct idtr_desc *ptr);
extern void int20h_timer();
extern void int25h_sound();

struct idt_desc idt_descriptors[TOTAL_INTERRUPTS];
struct idtr_desc idtr_descriptor;

// void idt_zero() { tty_print(&DefaultTTY, "Divide by zero error\n"); }

// // todo need to find out which PiC send command by looking at interrupt
// number void int20h_timer_handler() {
//   // tty_print(&DefaultTTY, "Timer\n");
//   outb(PIC1, PIC_EOI);
// }

void no_interrupt_handler() { irq_end_of_interrupt(); }

void idt_set(int interrupt_no, void *address) {
  struct idt_desc *desc = &idt_descriptors[interrupt_no];
  desc->offset_low = (uint32)(address);
  desc->selector = KERNEL_CODE_SEGMENT;
  desc->zero = 0;
  desc->type_attr = 0xEE; // todo: look up interrupt attributes
  desc->offset_high = (uint32)(address) >> 16;
}

void idt_init() {

  memset(idt_descriptors, 0, sizeof(idt_descriptors));
  idtr_descriptor.limit = sizeof(idt_descriptors) - 1;
  idtr_descriptor.base = (uint32)idt_descriptors;

  for (uint16 i = 0; i < TOTAL_INTERRUPTS; i++) {
    idt_set(i, no_interrupt);
  }
  // idt_set(0, idt_zero);

  idt_set(0x20, int20h_timer);
  irq_clear_mask(5);
  idt_set(0x25, int25h_sound);

  idt_load(&idtr_descriptor);
}
