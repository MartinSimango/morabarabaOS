section .asm
global insb
global insw
global outb
global outw

;uint8 insb(uint16 port);

insb:
    push ebp
    mov ebp, esp

    xor eax, eax ; make eax 0
    mov edx, [ebp+8] 

    in al, dx 

    pop ebp
    ret ;  return val is always in eax (al is lower 8 bits of eax)

;uint16 insw(uint16 port);

insw:
    push ebp
    mov ebp, esp

    xor eax, eax ; make eax 0
    mov edx, [ebp+8] 

    in ax, dx

    pop ebp
    ret ;  return val is always in eax (al is lower 8 bits of eax)

; void outb(uint16 port, uint8 value);

outb:
    push ebp
    mov ebp, esp

    mov eax, [ebp+12] ; get value at address of value
    mov edx, [ebp+8] ; get value at address of port

    out dx, al

    pop ebp
    ret

; void outw(uint16 port, uint16 value);
outw:
    push ebp
    mov ebp, esp

    mov eax, [ebp+12] ; get value at address of value
    mov edx, [ebp+8] ; get value at address of port

    out dx, ax

    pop ebp
    ret