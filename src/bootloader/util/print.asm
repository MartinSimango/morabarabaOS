[BITS 16]

print_string:
    MOV AL, [SI] ; get a byte from SI register
    INC SI
    OR AL, AL ; if AL is equal to 0 
    JZ exit_function ;  jmp if zero
    CALL print_character
    JMP print_string
exit_function:
    RET

print_character:
    MOV AH, 0X0E; teletype mode (print something to the screen)
    MOV BH, 0x00 ; page no
    MOV BL, 0x07; Text attribute 0x07 lightgrey font on black background

    INT 0x10 ; CALL BIOS video interrupt
    RET


clear_screen:
    MOV AH, 0x00
    MOV AL, 0x03
    INT 0x10
    RET

