[ORG 0x7e00] ; this is the address of where BIOS load the bootloader into

CALL PrintKernelMessage
CALL EnterProtectiveMode



EnterProtectiveMode:
; 1. disable interupts
; 2. enable A20line
; 3. create GDT



PrintKernelMessage:
    CALL ClearScreen
    MOV SI, KernelMessage
    CALL PrintString
    RET



%include "print.asm"

KernelMessage db "Now Loading the Kernel...", 0x0d, 0

TIMES 512 - ($ - $$) db 0


