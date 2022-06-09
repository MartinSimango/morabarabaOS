#include "irq.h"
#include "io.h"
#include "types.h"

void remap_pic() {

  uint8 mask_1 = insb(PIC1_DATA); // save masks
  uint8 mask_2 = insb(PIC2_DATA);

  outb(PIC1_COMMAND,
       ICW1_INIT |
           ICW1_ICW4); // starts the initialization sequence (in cascade mode)
  outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
  outb(PIC1_DATA, PIC1_OFFSET); // ICW2: Master PIC vector offset
  outb(PIC2_DATA, PIC2_OFFSET); // ICW2: Slave PIC vector offset
  outb(
      PIC1_DATA,
      4); // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
  outb(PIC2_DATA, 2); // ICW3: tell Slave PIC its cascade identity (0000 0010)

  outb(PIC1_DATA, ICW4_8086);
  outb(PIC2_DATA, ICW4_8086);

  outb(PIC1_DATA, mask_1); // restore saved masks.
  outb(PIC2_DATA, mask_2);
}

void irq_init() { remap_pic(); }