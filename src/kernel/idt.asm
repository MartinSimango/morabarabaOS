section .asm

global idt_load

; each 
idt_load:
    push ebp
    mov ebp, esp
    
    mov ebx, [ebp+8] ; get first paramter passed to function. ebp+0  esp will point to esp ebp +4 will be ret address 
    lidt [ebx]
    
    pop ebp
    ret
    
