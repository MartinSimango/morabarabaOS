[BITS 16] ; tell assemble to use 16 bit code
[ORG 0x7c00] ; this is the address of where BIOS load the bootloader into

MOV [BOOT_DISK], dl

CALL ReadDisk
JMP PROGRAM_SPACE


%include "diskread.asm"

TIMES 510 - ($ - $$) db 0 ; fill all bytes until the 510th byte with zeros
DW 0xAA55 ; tell bios that this is a bootable device


