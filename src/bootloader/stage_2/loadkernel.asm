[BITS 16]
[ORG 0x7e00] ; memory free is to us if from 0x07e00 until 0x07FFFF w

jmp EnterProtectiveMode

%include "src/bootloader/stage_2/gdt.asm"
%include "src/bootloader/stage_2/vbe.asm"


EnterProtectiveMode:

    call PrintProtectiveModeMessage
    call clear_screen

    cli

    call EnableA20
    call SetVideoMode
    call vbe_get_info
 
    
    lgdt [gdt] ; load gdt
 
    call EnablePE

    jmp codeseg:LoadKernel ; far jmp  new cs must be offset of code segment in GDT .ie codeseg is the offset of the code segment in the GDT
                                     ; i.e codeseg is codeseg bytes away from the start of the GDT and codeseg bytes away from the GDT is
                                     ; the beginning of the codeseg in the GDT (offset is 0x8)
    



; switch to grahpics mode 1280x1024 with 16.8M colours and use linear buffer
SetVideoMode:
;switch from text mode to video mode 320x200 px 8 bit graphics
    ; mov ah, 0x00
    ; mov al, 0x13 
    mov AX, 4F02h
    mov BX, VBE_MODE 
    int 0x10
    RET
; todo make this better as this is the A20 fast method. Check to set if A20 is set
EnableA20:
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

; enable protective mode bit
EnablePE:
    mov eax, cr0 
    or  eax, 1
    mov cr0, eax
    ret


PrintProtectiveModeMessage:
    mov si, ProtectiveModeMessage
    call print_string
    ret

Reboot:
    mov si, rebootmsg
    call print_string
    xor ax, ax ; 
    int 0x16  ; wait for key press interupt
    db 0XEA ; machine language to jump to FFFF:0000 (reboot)
    dw 0x0000
    dw 0xFFFF 
    

%include "src/bootloader/util/print.asm"


rebootmsg db "Press any key to reboot",0x0d,0xA,0

KernelMessage db "Now Loading the Kernel...", 0x0d,0xA,0
ProtectiveModeMessage db "Entering protective mode...", 0x0d,0xA,0
LoadGDT db "Loading GDT", 0x0d, 0
GDTLoader db "GDT finished loading", 0x0d, 0





[BITS 32] ; switch to 32 bit mode

LoadKernel:
    mov eax, 2 ; sector to read
    mov ecx, 100 ; number of sectors to read
    mov edi, 0x0100000 ; where to load kernel into address
    call ata_lba_read
    jmp  codeseg:0x0100000

; disk driver to read from disk (talking to motherboard to read from disk)
ata_lba_read:
    ; send sector to read
    mov ebx, eax ; backup LBA
    shr eax, 24 ; send highest 8 bits of lba to hard disk controller
    or eax, 0xE0 ; select the master drive
    mov dx, 0x1F6 ; port to right 8 bits to
    out dx, al; (al will contain the highest 8 bits of eax)

    ; send number of sectors to read
    mov eax, ecx
    mov dx, 0x1F2
    out dx, al

    ; send more bits of LBA
    mov eax, ebx ; restore backup of LBA
    mov dx, 0x1f3
    out dx, al

    ; send more bits of LBA
    mov dx, 0x1F4
    mov eax, ebx ; restore backup of LBA
    shr eax, 8
    out dx, al

   ; send upper 16  bits of LBA
    mov dx, 0x1F5
    mov eax, ebx ; restore backup of LBA
    shr eax, 16
    out dx, al

    mov dx, 0x1F7
    mov al, 0x20
    out dx, al

; read all sectors into memory
.next_sector:
    push ecx

; check if we need to read
.try_again:
    mov dx, 0x1F7
    in al, dx
    test al, 8
    jz .try_again

; read 256 words at a time (512 bytes)
    mov ecx, 256
    mov dx, 0x1F0
    rep insw ; insw reads a word from the io port in dx and writes it into edi 
             ; rep repeats instruction x many times where x is the value in the ecx register
    pop ecx ; restore old value as we stored it on the stack 
    loop .next_sector ; jmps to next_sector and decrements ecx until ecx =0
    ret 





TIMES 512 - ($ - $$) db 0
