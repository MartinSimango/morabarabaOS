[BITS 16]
[ORG 0x7e00] ; memory free is to us if from 0x07e00 until 0x07FFFF w
KERNEL_MEMORY_ADDRESS equ 0x100000
KERNEL_SECTOR equ 4
VBE_MODE_INFO_ADDRESS equ 0x8400
jmp EnterProtectiveMode

%include "src/bootloader/stage_2/gdt.asm"
%include "src/bootloader/stage_2/vbe.asm"


EnterProtectiveMode:

    call PrintProtectiveModeMessage
    call clear_screen
   
    cli
   
    call load_vbe_mode_info
    ; call SetTextMode
    
    lgdt [gdt] ; load gdt
    
 
    call EnableA20
    ; call enable_A20

    ; call check_a20
    ; cmp ax, 1
    ; jz PrintA20
    ; jmp PrintNotA20
    call EnablePE


    jmp CODE_SEG:LoadKernel ; far jmp  new cs must be offset of code segment in GDT .ie codeseg is the offset of the code segment in the GDT
                                     ; i.e codeseg is codeseg bytes away from the start of the GDT and codeseg bytes away from the GDT is
                                     ; the beginning of the codeseg in the GDT (offset is 0x8)
    ; load vbe_mode_info information into ram


SetTextMode:
;switch from text mode to video mode 320x200 px 8 bit graphics
    ; mov ah, 0x00
    ; mov al, 0x13 
    mov AX, 4F02h
    mov BX, 10Ch 
    int 0x10
    RET
; todo make th

load_vbe_mode_info: 
    call vbe_set_mode
    jc PrintErrorSettingVideoMode
    mov esi, mode_info_block
    mov edi, VBE_MODE_INFO_ADDRESS
    mov ecx, 64                 ; Mode info block is 256 bytes / 4 = 64 of dbl words
    rep movsd
    ret

; todo make this better as this is the A20 fast method. Check to set if A20 is set
EnableA20:
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

; check_a20:
;     pushf
;     push ds
;     push es
;     push di
;     push si
 
;     cli
 
;     xor ax, ax ; ax = 0
;     mov es, ax
 
;     not ax ; ax = 0xFFFF
;     mov ds, ax
 
;     mov di, 0x0500
;     mov si, 0x0510
 
;     mov al, byte [es:di]
;     push ax
 
;     mov al, byte [ds:si]
;     push ax
 
;     mov byte [es:di], 0x00
;     mov byte [ds:si], 0xFF
 
;     cmp byte [es:di], 0xFF
 
;     pop ax
;     mov byte [ds:si], al
 
;     pop ax
;     mov byte [es:di], al
 
;     mov ax, 0
;     je check_a20__exit
 
;     mov ax, 1
 
; check_a20__exit:
;     pop si
;     pop di
;     pop es
;     pop ds
;     popf
 
;     ret

; enable protective mode bit
EnablePE:
    mov eax, cr0 
    or  eax, 1
    mov cr0, eax
    ret



; PrintA20:
;     mov si, a20on
;     call print_string
;     jmp $

; PrintNotA20:
;     mov si, a20off
;     call print_string
;     jmp $

PrintProtectiveModeMessage:
    mov si, ProtectiveModeMessage
    call print_string
    ret

PrintErrorSettingVideoMode:
    mov si, ErrorSettingVideoModeMessage
    call print_string

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
; a20on db "A20 is enabled",0x0d,0xA,0
; a20off db "A20 is NOT enabled",0x0d,0xA,0



KernelMessage db "Now Loading the Kernel...", 0x0d,0xA,0
ProtectiveModeMessage db "Entering protective mode...", 0x0d,0xA,0
ErrorSettingVideoModeMessage db "Error setting video mode...", 0x0d,0xA,0

LoadGDT db "Loading GDT", 0x0d, 0
GDTLoader db "GDT finished loading", 0x0d, 0





[BITS 32] ; switch to 32 bit mode


LoadKernel:

    ; mov eax, 4 ; sector to read
    ; mov ecx, 60 ; number of sectors to read (max sectors we can read at a time)
    ; mov edi, 0x0100000 ; where to load kernel into address
    ; call ata_lba_read
    ; mov eax, 258 ; sector to read
    ; mov ecx, 255 ; number of sectors to read
    ; mov edi, 0x11FE00 ; where to load kernel into address (0x100000 + 512*255)
    ; call ata_lba_read
    ; mov eax, 513 ; sector to read
    ; mov ecx, 255 ; number of sectors to read
    ; mov edi, 0x13FC00 ; where to load kernel into address
    ; call ata_lba_read
    
    ; jmp CODE_SEG:0x0100000
    call load_kernel


    mov eax, KERNEL_MEMORY_ADDRESS
    jmp far eax

load_kernel:
    mov eax, KERNEL_MEMORY_ADDRESS
    push eax
    mov eax, 500 ; how many sectors to load 
    push eax
    mov eax, KERNEL_SECTOR
    push eax
    
    call load_sectors_into_kernel_address
    add esp, 12
    ret
; disk driver to read from disk (talking to motherboard to read from disk)
ata_lba_read:
    ; send sector to read
    mov ebx, eax ; backup LBA

    mov dx, 0x1F6 ; LBA bit 24-47 port
    shr eax, 24 ; send highest 8 bits of lba to hard disk controller
    or eax, 0xE0 ; select the master drive
    out dx, al; send LBA to ATA drive

    ; send number of sectors to read
    mov dx, 0x1F2 ; sector port
    mov eax, ecx
    out dx, al

    ; LBA bit 0-7 port
    mov dx, 0x1F3
    mov eax, ebx ; restore backup of LBA
    out dx, al

    ; LBA bit 8-15 port
    mov dx, 0x1F4
    mov eax, ebx ; restore backup of LBA
    shr eax, 8
    out dx, al

   ; LBA bit 16-23 port
    mov dx, 0x1F5
    mov eax, ebx ; restore backup of LBA
    shr eax, 16
    out dx, al

    ;  send command to ATA
    mov dx, 0x1F7
    mov al, 0x20 ; read with a retry
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

; args
; # 1 sector where kernel starts
; # 2 number of sectors to read 
; # 3 kernel start address
load_sectors_into_kernel_address:
    push ebp        ; save base pointer (save old base pointer)
    mov ebp, esp    ; set up new base pointer (make ebp now point to top of stack) - so ebp points to old ebp
                    ; ebp +0 = old epb epb+4 = ret ebp+8 = 3rd arg, ebp+12 = 2nd

    mov eax, [ebp+12] ; divedend
    mov ebx, 255      ; divisor
    xor edx, edx     ; clear remainder register
    div ebx  ; divide eax by ebx result in eax 
    inc eax
    mov ecx, eax ; how many times to repeat

    mov eax, [ebp+8]
    mov edi, [ebp+16]
    push edx
    
    loop .load_next_255_sectors
    mov ecx, edx 
    jmp .finish_remainding_sector

.load_next_255_sectors:
    push ecx
    push eax
    mov ecx, 255
    call ata_lba_read
    pop eax
    pop ecx
    add eax, 255
    loop .load_next_255_sectors
    pop edx
    mov ecx, edx
    cmp ecx, 0
    jg .finish_remainding_sector
    jmp .finish

.finish_remainding_sector:
    call ata_lba_read
   
.finish:    
    ; epilouge
    mov esp, ebp ; set esp back to where it was at begging of function
    pop ebp
    ret 




TIMES 1536 - ($ - $$) db 0
