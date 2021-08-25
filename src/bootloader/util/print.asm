[BITS 16]

PrintString:
next_character:
    MOV AL, [SI] ; get a byte from SI register
    INC SI
    OR AL, AL ; if AL is equal to 0 
    JZ exit_function ;  jmp if zero
    CALL PrintCharacter
    JMP next_character
exit_function:
    RET

PrintCharacter:
    MOV AH, 0X0E; teletype mode (print something to the screen)
    MOV BH, 0x00 ; page no
    MOV BL, 0x07; Text attribute 0x07 lightgrey font on black background

    INT 0x10 ; CALL BIOS video interrupt
    RET


ClearScreen:
    MOV AH, 0x00
    MOV AL, 0x03
    INT 0x10
    RET

