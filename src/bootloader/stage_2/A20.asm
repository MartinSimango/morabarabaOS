enableA20:    
    call CheckA20
    cmp  ax, 0
    jne  enable_A20__done
    ; mSetA20BIOS
    
    mov ax, 0x2401
    int 0x15

    call CheckA20
    cmp  ax, 0
    jne  enable_A20__done
    call mSetA20Keyboard

    call CheckA20

    cmp  ax, 0
    jne  enable_A20__done
    ; mSetA20FastGate

    in al, 0x92
    or al, 2
    out 0x92, al


    call CheckA20
    xchg bx, bx
    cmp  ax, 0
    jne  enable_A20__done
    enable_A20__fail:
        mov si, a20error
        call PrintString
        call Reboot
    enable_A20__done:
        ret

CheckA20:
    RET
;     pushf                          ; Save registers that
;     push ds                        ; we are going to
;     push es                        ; overwrite.
;     push di
;     push si

;     cli                            ; No interrupts, please

;     xor ax, ax                     ; Set es:di = 0000:0500
;     mov es, ax
;     mov di, 0x0500

;     mov ax, 0xffff                 ; Set ds:si = ffff:0510
;     mov ds, ax
;     mov si, 0x0510

;     mov al, di       ; Save byte at es:di on stack.
;     push ax                        ; (we want to restore it later)

;     mov al, si       ; Save byte at ds:si on stack.
;     push ax                        ; (we want to restore it later)

;     mov di, 0x00     ; [es:di] = 0x00
;     mov si, 0xFF     ; [ds:si] = 0xff

;     cmp di, 0xFF     ; Did memory wrap around?

;     pop ax
;     mov si, al       ; Restore byte at ds:si

;     pop ax
;     mov di, al       ; Restore byte at es:di

;     mov ax, 0
;     je check_a20__exit             ; If memory wrapped around, return 0.

;     mov ax, 1                      ; else return 1.

; check_a20__exit:
;     pop si                         ; Restore saved registers.
;     pop di
;     pop es
;     pop ds
;     popf
;     ret

; %macro mSetA20BIOS
;   mov ax, 0x2401
;   int 0x15
; %endmacro

Wait_8042_command:
    in      al,0x64
    test    al,2
    jnz     Wait_8042_command
    ret

Wait_8042_data:
  in      al,0x64
  test    al,1
  jz      Wait_8042_data
  ret

mSetA20Keyboard:
    cli                        ; Disable interrupts

    call    Wait_8042_command  ; When controller ready for command
    mov     al,0xAD            ; Send command 0xad (disable keyboard).
    out     0x64,al

    call    Wait_8042_command  ; When controller ready for command
    mov     al,0xD0            ; Send command 0xd0 (read from input)
    out     0x64,al

    call    Wait_8042_data     ; When controller has data ready
    in      al,0x60            ; Read input from keyboard
    push    eax                ; ... and save it

    call    Wait_8042_command  ; When controller is ready for command
    mov     al,0xD1            ; Set command 0xd1 (write to output)
    out     0x64,al            

    call    Wait_8042_command  ; When controller is ready for command
    pop     eax                ; Write input back, with bit ;2 set
    or      al,2
    out     0x60,al

    call    Wait_8042_command  ; When controller is ready for command
    mov     al,0xAE            ; Write command 0xae (enable keyboard)
    out     0x64,al

    call    Wait_8042_command  ; Wait until controller is ready for command

    sti                        ; Enable interrupts
    ret

; %macro mSetA20FastGate
;   in al, 0x92
;   or al, 2
;   out 0x92, al
; %endmacro
; Reboot:
;     mov si, rebootmsg
;     call PrintString
;     xor ax, ax ; 
;     int 0x16  ; wait for key press interupt
;     db 0XEA ; machine language to jump to FFFF:0000 (reboot)
;     dw 0x0000
;     dw 0xFFFF 

; rebootmsg db "Press any key to reboot",0x0d,0xA,0
a20error  db "Failed to set A20",0x0d,0xA,0