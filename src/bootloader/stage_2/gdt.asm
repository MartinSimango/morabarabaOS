; https://wiki.osdev.org/GDT_Tutorial
; we only fill the first 3 entries of the gdt table so gdt is 24 bytes. the maximum entries it can have is 8912
[BITS 16]


gdt_nulldesc: ; 8 bytes
    dd 0 ; 4 bytes
    dd 0;  4 bytes

gdt_code: ; 8 bytes
    dw 0xFFFF ; Lower 2 bytes of the descriptor’s limit
    dw 0x0000 ; Lower 2 bytes of the descriptor’s base address
    db 0x00 ; Middle byte of the descriptor’s base address          
    db 10011010b ; Access bytes
    db 11001111b ; Four flags bits influencing segment size and upper 4 bits of the limit 
    db 0x00 ; Upper byte of the descriptor’s base address
    ; base: 0x00000000 - 32 bits
    ; limit: 0xFFFFF - 20 bits

 gdt_data:  ; 8 bytes
    dw 0xFFFF ; Lower 2 bytes of the descriptor’s limit
    dw 0x0000 ; Lower 2 bytes of the descriptor’s base address
    db 0x00 ; Middle byte of the descriptor’s base address          
    db 10010010b ; Access bytes
    db 11001111b ; Four flags bits influencing segment size and upper 4 bits of the limit 
    db 0x00 ; Upper byte of the descriptor’s base address

gdt_end: 

; 65,536 is max size of table but 2^16 holds between  0 and 65,535 so 
    ; setting the size as 1 means that table size will be seens as 2 and setting it 2 means it will be seen as 3 etc... so  
    ; setting if we want size x we need to set the size to x -1
gdt: ; this is the gdtr
    dw  gdt_end - gdt_nulldesc - 1 ; size
    dd  gdt_nulldesc ; offset

CODE_SEG equ gdt_code - gdt_nulldesc
DATA_SEG equ gdt_data - gdt_nulldesc

