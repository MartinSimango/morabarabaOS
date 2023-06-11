OUTPUT_FORMAT("binary")
ENTRY(rust_main)


SECTIONS
{

    . = 0x7e00;

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