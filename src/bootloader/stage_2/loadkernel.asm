[BITS 16]

section .text
    global main

main:
    JMP EnterProtectiveMode

%include "src/bootloader/stage_2/idt.asm"
%include "src/bootloader/stage_2/gdt.asm"


EnterProtectiveMode:
    CALL PrintProtectiveModeMessage
    
    CALL EnableA20
    CALL ClearScreen

    cli
    lgdt [gdt] ; load gdt
    lidt [idt] ; load idt

    CALL EnablePE
    
    JMP codeseg:StartProctectiveMode
    

; todo make this better as this is the A20 fast method. Check to set if A20 is set
EnableA20:
    IN al, 0x92
    OR al, 2
    OUT 0x92, al
    RET

; enable protective mode bit
EnablePE:
    MOV eax, cr0 
    OR  eax, 1
    MOV cr0, eax
    RET


PrintProtectiveModeMessage:
    MOV SI, ProtectiveModeMessage
    CALL PrintString
    RET

Reboot:
    mov si, rebootmsg
    call PrintString
    xor ax, ax ; 
    int 0x16  ; wait for key press interupt
    db 0XEA ; machine language to jump to FFFF:0000 (reboot)
    dw 0x0000
    dw 0xFFFF 
    

%include "src/bootloader/util/print.asm"


[BITS 32] ; switch to 32 bit mode
[extern _start]
StartProctectiveMode:

    mov    ax, dataseg     ; Byte offset for selector 2 (start of data seg)
    mov    ds, ax        ; (remember, each descriptor is 8 bytes)
    mov    es, ax
    mov    fs, ax
    mov    gs, ax
    mov    ss, ax

    mov    esp, 0x2ffff  ; Set stack to grow downwards from 0x30000

    call _start ; go to the start of the kernel code



rebootmsg db "Press any key to reboot",0x0d,0xA,0

KernelMessage db "Now Loading the Kernel...", 0x0d,0xA,0
ProtectiveModeMessage db "Entering protective mode...", 0x0d,0xA,0
LoadGDT db "Loading GDT", 0x0d, 0
GDTLoader db "GDT finished loading", 0x0d, 0




TIMES 512 - ($ - $$) db 0


