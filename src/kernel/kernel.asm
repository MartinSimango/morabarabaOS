[BITS 32] ; switch to 32 bit mode
[extern start_kernel]
section .text.prologue


global _start
DATA_SEG equ 0x10

_start:
    mov    ax, DATA_SEG   ; Byte offset for selector 2 (start of data seg)
    mov    ds, ax        ; (remember, each descriptor is 8 bytes)
    mov    es, ax
    mov    fs, ax
    mov    gs, ax
    mov    ss, ax
;    mov    esp, 0x2fffff  ; Set stack to grow downwards from 0x30000 - so you have 0x30000 until 0x7e00  (max of this should be 0x9fc00)
    mov    esp, 0x00200000  ;
    mov    ebp, esp
    ; call   remap_master_pic

    call   start_kernel ; go to the start of the kernel code
    
    ; jmp $

remap_master_pic:
     ; Remap the master PIC
    mov al, 00010001b
    out 0x20, al ; Tell master PIC

    mov al, 0x20; Interrupt 0x20 is where master ISR should start
    out 0x21, al

    mov al, 00000001b
    out 0x21, al
    ret
    



TIMES 512 - ($ - $$) db 0   