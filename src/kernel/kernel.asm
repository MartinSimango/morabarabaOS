[BITS 32] ; switch to 32 bit mode
[extern main]

global _start
dataseg equ 0x10

_start:
    ; jmp $
    mov    ax, dataseg   ; Byte offset for selector 2 (start of data seg)
    mov    ds, ax        ; (remember, each descriptor is 8 bytes)
    mov    es, ax
    mov    fs, ax
    mov    gs, ax
    mov    ss, ax

    mov    esp, 0x2ffff  ; Set stack to grow downwards from 0x30000 - so you have 0x30000 until 0x7e00  (max of this should be 0x9fc00)
    call   main ; go to the start of the kernel code
    jmp $



TIMES 512 - ($ - $$) db 0   