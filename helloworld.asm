 [BITS 16] ; tell assemble to use 16 bit code
[ORG 0x7c00] ; this is the address of where BIOS load the bootloader into

;data



; section .code


MOV SI, HelloString
CALL PrintString
JMP $


PrintString:
next_character:
    MOV AL, [SI] ; get a byte from SI register
    INC SI
    CALL PrintCharacter
    OR AL, AL ; if AL is equal to 0 
    JZ exit_function ;  jmp if zero
    JMP next_character
exit_function:
    RET

PrintCharacter:
    MOV AH, 0X0E; teletype mode (print something to the screen)
    MOV BH, 0x00 ; page no
    MOV BL, 0x07; Text attribute 0x07 lightgrey font on black background

    INT 0x10 ; CALL BIOS video interrupt
    RET



HelloString db 'Hello World', 0 ; 12 bytes of data

TIMES 510 - ($ - $$) db 0 ; fill all bytes until the 510th byte with zeros
DW 0xAA55 ; tell bios that this is a bootable device


