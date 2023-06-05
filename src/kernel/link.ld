OUTPUT_FORMAT("binary")
ENTRY(_start)



/* INPUT(
    obj/loadkernel.o
    obj/main.o
    obj/screen.o
    obj/util.o
    obj/colours.o

)

OUTPUT(
    bin/kernel.bin
) */
SECTIONS
{

    . = 0x100000;/* 1M;  /* where kernel will be loaded to (0x100000) */

    .text BLOCK(4K) : ALIGN(0x1000)
    {
        *(.text.prologue)
        *(.text)
    }

    .rodata BLOCK(4K) : ALIGN(0x1000)
    {
        *(.rodata)
    }

    .data BLOCK(4K) : ALIGN(0x1000)
    {
        *(.data)
    }

    .bss BLOCK(4K) : ALIGN(0x1000)
    {
        *(COMMON)
        *(.bss)
        
    }

    .asm BLOCK(4K) : ALIGN(0x1000){
        *(.asm)
    }

    end = .;
}