section .asm

global idt_load
global int20h
global no_interrupt

extern int20h_handler 
extern no_interrupt_handler
; each 
idt_load:
    push ebp
    mov ebp, esp
    
    mov ebx, [ebp+8] ; get first paramter passed to function. ebp+0  esp will point to esp ebp +4 will be ret address 
    lidt [ebx]
    
    pop ebp
    ret
    

int20h:

    cli
    pushad
    call int20h_handler
    popad
    sti
    iret


no_interrupt:
    cli
    pushad
    call no_interrupt_handler
    popad
    sti
    iret