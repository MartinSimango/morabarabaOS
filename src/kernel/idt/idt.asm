section .asm

global idt_load
global int20h_timer
global int25h_sound
global no_interrupt

extern int20h_timer_handler 
extern no_interrupt_handler
extern int25h_sound_handler

; each 
idt_load:
    push ebp
    mov ebp, esp
    
    mov ebx, [ebp+8] ; get first paramter passed to function. ebp+0  esp will point to esp ebp +4 will be ret address 
    lidt [ebx]
    
    pop ebp
    ret
    

int20h_timer:
    cli
    pushad
    call int20h_timer_handler
    popad
    sti
    iret

    

int25h_sound:
    cli
    pushad
    call int25h_sound_handler
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