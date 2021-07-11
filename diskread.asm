PROGRAM_SPACE equ 0x7e00 ; this address is 512 bytes 07c00

ReadDisk:
    MOV AH, 0x02; tell BIOS to read from disk
    MOV bx, PROGRAM_SPACE ; where to put new data it reads from disk
    MOV al, 1; how many sectors to read
    MOV dl, [BOOT_DISK] ; load disk number into dl
    MOV ch, 0x00 ; read from first cylinder
    MOV dh, 0x00 ; read from first head
    MOV cl, 0x02 ; read from 2nd sector

    INT 0x13 ; bios interrupt to read values in registers

    JC DiskReadFailed
    RET
BOOT_DISK:
    db 0

DiskReadErrorString db 'Disk Read Failed ', 0 

DiskReadFailed:
    MOV SI, DiskReadErrorString
    CALL PrintString
    JMP $

%include "print.asm"
