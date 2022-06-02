[BITS 16]
gdt_nulldesc:
    dd 0 ; 4 bytes
    dd 0;  4 bytes

gdt_code:
    dw 0xFFFF ; Lower 2 bytes of the descriptor’s limit
    dw 0x0000 ; Lower 2 bytes of the descriptor’s base address
    db 0x00 ; Middle byte of the descriptor’s base address          
    db 10011010b ; Access bytes
    db 11001111b ; Four flags bits influencing segment size and upper 4 bits of the limit 
    db 0x00 ; Upper byte of the descriptor’s base address

 gdt_data: 
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

codeseg equ gdt_code - gdt_nulldesc
dataseg equ gdt_data - gdt_nulldesc

