[BITS 16]
[ORG 0x7c00]


; TODO find out why this doesn't effect size of program
PROGRAM_SPACE equ 0x7e00; 512 bytes after first sector



main:
    JMP short start
    NOP

  
; this sector needs to start at an offset of 0x3 bytes from the start of the program
boot_sector:
    BPB:                                   ; boot paramter block
        iOEM            db "DevOS   "      ; OEM [8 bytes]
        iSectSize       dw 0x200           ; bytes per sector [2 bytes]
        iClustSize      db 1               ; sectors per cluster [1 bytes]
        iResSect        dw 1               ; numbeof reserved sectors [2 bytes]
        iFatCnt         db 2               ; number FAT tables [1 byte]
        iRootSize       dw 224             ; number of root directory entries [2 bytes]
        iTotalSect      dw 2880            ; total number of sectors if over 32 MB [2 bytes]
        iMedia          db 0xF0            ; media Descriptor [1 byte]
        iFatSize        dw 9               ; size of each FAT. Number of sectors per FAT [2 bytes]
        iTrackSect      dw 9               ; sectors per track [2 bytes]
        iHeadCnt        dw 2               ; number of read-write heads [2 bytes]
    EBPB:                                  ; extended BPB
        iHiddenSect     dw  0              ; number of hidden sectors [2 bytes]
        iSect32         dd  0                ; number of sectors for number in filesystem [4 bytes]
        iBootDrive      db  0               ; holds drive that the boot sector came from [1 byte]
        iReserved       db  0               ; reserved, empty [1 byte]
        iBootSign       db  0x29            ; extended boot sector signature [1 byte]
        iVolID          db  "seri"          ; disk serial [4 bytes]
        acVolumeLabel   db  "Martin     "   ; volume label [11 bytes]
        acFSType        db  "FAT16   "      ; file system type [8 bytes]


; define real mode data segments
start:
    cli                  ; Turn off interrupts
    mov  [iBootDrive], dl  ; save what drive we booted from (should be 0x0)
    mov  ax, 0x00  
    mov  ds, ax          ; DS = CS = 0x0
    mov  es, ax          ; ES = CS = 0x0
    mov  ss, ax          ; SS = CS = 0x0 
    mov bp, 0x7c00      ;  Stack grows down from offset 0x7C00 toward 0x0000. decimal=  31744
    mov sp, bp
    sti                  ; Enable interrupts

    mov si, LoadingMessage
    call print_string

; prepare drive for use by resetting it
reset_drive:              
  mov  dl, [iBootDrive]   ; drive to reset 
  xor  ax, ax             ; subfunction 0 (mov ax, 0) use xor instead of mov to use less bytes as xor instruction uses less bytes
  int  0x13               ; call interrupt 13h
  jc   boot_failure        ; display error message if carry set (error)
  call read_disk
  jmp PROGRAM_SPACE     ; jmp to 2nd stage bootloader that will load the kernel



boot_failure:
    mov si, DiskError
    call print_string
    call reboot


reboot:
    mov si, RebootMsg
    call print_string
    xor ax, ax ; 
    int 0x16  ; wait for key press interupt
    db 0XEA ; machine language to jump to FFFF:0000 (reboot)
    dw 0x0000
    dw 0xFFFF 

%include "src/bootloader/util/print.asm"
%include "src/bootloader/util/diskread.asm"

RebootMsg db "Press any key to reboot",0x0d,0xA,0
DiskError db "Disk error ", 0
LoadingMessage db "Loading...",0x0d,0xA,0



TIMES 510 - ($ - $$) db 0 ; fill all bytes until the 510th byte with zeros
DW 0xAA55 ; tell bios that this is a bootable device
