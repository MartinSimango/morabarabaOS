#include "irq.h"
#include "io.h"

#define PIC1 0x20 /* IO base address for master PIC */
#define PIC1_OFFSET 0x20
#define PIC2 0xA0 /* IO base address for slave PIC */
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_OFFSET 0x28
#define PIC2_DATA (PIC2 + 1)
#define PIC_EOI 0x20

#define ICW1_ICW4 0x01      /* ICW4 (not) needed */
#define ICW1_SINGLE 0x02    /* Single (cascade) mode */
#define ICW1_INTERVAL4 0x04 /* Call address interval 4 (8) */
#define ICW1_LEVEL 0x08     /* Level triggered (edge) mode */
#define ICW1_INIT 0x10      /* Initialization - required! */

#define ICW4_8086 0x01       /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO 0x02       /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE 0x08  /* Buffered mode/slave */
#define ICW4_BUF_MASTER 0x0C /* Buffered mode/master */
#define ICW4_SFNM 0x10       /* Special fully nested (not) */

void remap_pic() {

  uint8 mask_1 = insb(PIC1_DATA); // save masks
  uint8 mask_2 = insb(PIC2_DATA);

  outb(PIC1_COMMAND,
       ICW1_INIT |
           ICW1_ICW4); // starts the initialization sequence (in cascade mode)
  outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
  outb(PIC1_DATA, PIC1_OFFSET); // ICW2: Master PIC vector offset
  outb(PIC2_DATA, PIC2_OFFSET); // ICW2: Slave PIC vector offset
  // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
  outb(PIC1_DATA, 4);
  outb(PIC2_DATA, 2); // ICW3: tell Slave PIC its cascade identity (0000 0010)

  outb(PIC1_DATA, ICW4_8086);
  outb(PIC2_DATA, ICW4_8086);

  outb(PIC1_DATA, mask_1); // restore saved masks.
  outb(PIC2_DATA, mask_2);
}

void irq_init() { remap_pic(); }

void irq_clear_mask(uint8 IRQline) {
  uint16 port;
  uint8 value;

  if (IRQline < 8) {
    port = PIC1_DATA;
  } else {
    port = PIC2_DATA;
    IRQline -= 8;
  }
  value = insb(port) & ~(1 << IRQline);
  outb(port, value);
}

void irq_end_of_interrupt() { outb(PIC1, PIC_EOI); }
