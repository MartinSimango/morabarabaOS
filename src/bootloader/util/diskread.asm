LOAD_KERNEL_SEGMENT equ 0x1000 ; where the second stage bootloader will be loaded
PROGRAM_SPACE equ 0x7e00

read_disk:
    MOV SI, ReadingFromDisk
    CALL print_string
    MOV AH, 0x02; tell BIOS to read from disk
    MOV bx,  PROGRAM_SPACE ; where to put new data it reads from disk
    MOV al, 1; how many sectors to read
    MOV dl, [iBootDrive] ; load disk number into dl
    MOV ch, 0x00 ; read from first cylinder
    MOV dh, 0x00 ; read from first head
    MOV cl, 0x02 ; read from 2nd sector

    INT 0x13 ; bios interrupt to read values in registers

    JC disk_read_failed
    RET

DiskReadErrorString db 'Disk Read Failed ',0x0d,0xA,0 
ReadingFromDisk db 'Reading From Disk..',0x0d,0xA,0

disk_read_failed:
    MOV SI, DiskReadErrorString
    CALL print_string
    CALL reboot
    