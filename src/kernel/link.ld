OUTPUT_FORMAT("binary")
ENTRY(_main)



INPUT(
    obj/loadkernel.o
    obj/main.o
    obj/screen.o
    obj/util.o
    obj/colours.o

)

OUTPUT(
    bin/kernel.bin
)
SECTIONS
{

    . = 0x8000;

    .text : ALIGN(0x1000)
    {
        /* *(.text.prologue) */
        *(.text)
    }

    .rodata : ALIGN(0x1000)
    {
        *(.rodata)
    }

    .data : ALIGN(0x1000)
    {
        *(.data)
    }

    .bss : ALIGN(0x1000)
    {
        *(COMMON)
        *(.bss)
        
    }

    end = .;
}