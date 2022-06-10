[BITS 16]

VBE_INFO_BLOCK_ADDRESS equ 0x8000
VBE_MODE_INFO_ADDRESS equ 0x8200 ;(0x8000 + 512)

;411B = linear mode 111B= bank switching

VBE_800x600 equ 0x8113
VBE_1280x1024 equ 0x411B
VBE_1024x768 equ 118h

VBE_MODE equ VBE_1280x1024

vbe_get_info:
    call vbe_get_info_block
    call vbe_get_mode_info
    ret

vbe_get_info_block:
    mov ax, 0x4F00
    mov cx, VBE_MODE
    mov di, VBE_INFO_BLOCK_ADDRESS ; es is already set to 0 so this is pretty the stack address
    int 0x10
    ret ;  return val is always in eax (al is lower 8 bits of eax)

vbe_get_mode_info:
    mov ax, 0x4F01
    mov cx, VBE_MODE
    mov di, VBE_MODE_INFO_ADDRESS ; es is already set to 0 so this is pretty the stack address
    int 0x10
    ret ;  return val is always in eax (al is lower 8 bits of eax)


    