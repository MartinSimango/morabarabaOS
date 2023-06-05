PROGRAM_SPACE equ 0x7e00

read_disk:
    MOV SI, ReadingFromDisk
    CALL print_string
    MOV AH, 0x02; tell BIOS to read from disk
    MOV bx, PROGRAM_SPACE ; where to put new data it reads from disk
    MOV al, 3; how many sectors to read
    ; MOV dl, [iBootDrive] ; load disk number into dl
    MOV ch, 0x00 ; read from first cylinder
    MOV dh, 0x00 ; read from first head
    MOV cl, 0x02 ; read from 2nd sector

    INT 0x13 ; bios interrupt to read values in registers

    JC disk_read_failed ; jump if carry is set (carry is set if interrupt 0x13 is set)
    RET


read_kernel:
    push es
    mov ax, 0x1000
    mov es, ax
    MOV SI, ReadingFromDiskKernel
    CALL print_string
    MOV AH, 0x02; tell BIOS to read from disk
    MOV bx, 0 ; where to put new data it reads from disk
    MOV al, 127; how many sectors to read
    ; MOV dl, [iBootDrive] ; load disk number into dl
    MOV ch, 0x00 ; read from first cylinder
    MOV dh, 0x00 ; read from first head
    MOV cl, 0x05 ; read from 5th sector

    INT 0x13 ; bios interrupt to read values in registers

    JC disk_read_failed ; jump if carry is set (carry is set if interrupt 0x13 is set)
    pop es
    RET

DiskReadErrorString db 'Disk Read Failed ',0x0d,0xA,0 
ReadingFromDisk db 'Reading From Disk..',0x0d,0xA,0
ReadingFromDiskKernel db 'Reading From Disk Loading Kernel..',0x0d,0xA,0


disk_read_failed:
    MOV SI, DiskReadErrorString
    CALL print_string
    CALL reboot
    