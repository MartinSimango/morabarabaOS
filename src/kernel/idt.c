#include "idt.h"
#include "memory.h"

#define TOTAL_INTERRUPTS 256
#define KERNEL_CODE_SEGMENT 0x08
#define KERNEL_DATA_SEGMENT 0x10

#include "tty.h"

struct idt_desc idt_descriptors[TOTAL_INTERRUPTS];
struct idtr_desc idtr_descriptor;


extern void idt_load(struct idtr_desc *ptr);


struct terminal DefaultTty = {
   .text_color = TTY_WHITE,
   .terminal_col = 2,
   .terminal_row = 0
};

void idt_zero() {

    tty_print(&DefaultTty, "Divide by zero error\n");
}

void idt_set(int interrupt_no, void* address) {
    struct idt_desc * desc = &idt_descriptors[interrupt_no];
    desc->offset_low = (uint32) (address);
    desc->selector = KERNEL_CODE_SEGMENT;
    desc->zero = 0;
    desc->type_attr= 0xEE;
    desc->offset_high = (uint32) (address) >> 16;

}

void idt_init() {

    memset(idt_descriptors, 0, sizeof(idt_descriptors));
    idtr_descriptor.limit = sizeof(idt_descriptors) - 1;
    idtr_descriptor.base = (uint32) idt_descriptors;
    idt_set(0, idt_zero);

    idt_load(&idtr_descriptor);
}