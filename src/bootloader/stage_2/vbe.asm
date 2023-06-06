[BITS 16]

; vbe_set_mode:
; Sets a VESA mode
; In\	AX = Width
; In\	BX = Height
; In\	CL = Bits per pixel
; Out\	FLAGS = Carry clear on success
; Out\	Width, height, bpp, physical buffer, all set in vbe_screen structure



hexString: db '0x0000'
newline: db 0x0d,0xA,0
space:  db ' ', 0
hex_to_ascii: db '0123456789ABCDEF'

print_hex:
        mov cx, 4	; offset in string, counter (4 hex characters)
        .hex_loop:
            mov ax, dx	              ; Hex word passed in DX
            and al, 0Fh               ; Use nibble in AL
            mov bx, hex_to_ascii
            xlatb                     ; AL = [DS:BX + AL]

            mov bx, cx                ; Need bx to index data
            mov [hexString+bx+1], al  ; Store hex char in string
            ror dx, 4                 ; Get next nibble
        loop .hex_loop 

        mov si, hexString             ; Print out hex string
        mov cx, 6                     ; Length of string
        mov ah, 0Eh     ; BIOS teletype output
        .loop:
            lodsb
            int 10h
        loop .loop
        ret
;  1280x1024 
; 1024 x 768
screen:
    .width				dw 1024
    .height				dw 768
    .bpp				db 32

vbe_set_mode:

	push es					; some VESA BIOSes destroy ES, or so I read
	mov ax, 0x4F00				; get VBE BIOS info
	mov di, vbe_info_block
	int 0x10
	pop es
 
	cmp ax, 0x4F				; BIOS doesn't support VBE?
	jne .error
 
	mov ax, word[vbe_info_block.video_mode_pointer]
	mov [.offset], ax
	mov ax, word[vbe_info_block.video_mode_pointer+2]
	mov [.segment], ax
 
	mov ax, [.segment]
	mov fs, ax
	mov si, [.offset]
 
.find_mode:
	mov dx, [fs:si]
	add si, 2
	mov [.offset], si
	mov [.mode], dx
	mov ax, 0
	mov fs, ax
   
    mov ax, 0xFFFF	
	cmp [.mode], ax			; end of list?
	je .error
 
	push es
	mov ax, 0x4F01				; get VBE mode info
	mov cx, [.mode]
	mov di, mode_info_block
	int 0x10
	pop es
    
	cmp ax, 0x4F
	jne .error
  
     ; Will take the first default mode with the below commented out
     ; TODO try for desired mode then go to default mode
    ; mov dx, [.mode] ; 

    ; call print_hex
    ; mov si, space
    ; call print_string

    ; mov dx,  [mode_info_block.x_resolution]
    ; call print_hex
    ; mov si, space
    ; call print_string

    ; mov dx,  [mode_info_block.y_resolution]
    ; call print_hex
    ; mov si, space
    ; call print_string

    mov dx, [mode_info_block.bits_per_pixel]
	and dx, 0x00FF ; bits per pixel is only 1 byte so zero out the hight bits 
    call print_hex
	    mov si, space
    call print_string

	; mov si, newline
    ; call print_string

 
	mov ax, [screen.width]
	cmp ax, [mode_info_block.x_resolution]
	jne .next_mode
	mov ax, [screen.height]
	cmp ax, [mode_info_block.y_resolution]
	jne .next_mode
 
	mov al, [screen.bpp]
	cmp al, [mode_info_block.bits_per_pixel]
	jne .next_mode
 
	; Set the mode
	push es
	mov ax, 0x4F02
	mov bx, [.mode]
	
	or bx, 0x4000			; enable LFB - linear frame buffer
	mov di, 0			; not sure if some BIOSes need this... anyway it doesn't hurt
	int 0x10
	pop es 
	cmp ax, 0x4F
	jne .error
 
	clc
	ret
 
.next_mode:
	mov ax, [.segment]
	mov fs, ax
	mov si, [.offset]
	jmp .find_mode
 
.error:
	stc
	ret
 

; 1280x1024
.segment			dw 0
.offset			    dw 0
.mode				dw 0

vbe_info_block:		; 'Sector' 2
	.vbe_signature: db 'VESA'
	.vbe_version: dw 0          ; Should be 0300h? BCD value
	.oem_string_pointer: dd 0 
	.capabilities: dd 0
	.video_mode_pointer: dd 0
	.total_memory: dw 0
	.oem_software_rev: dw 0
	.oem_vendor_name_pointer: dd 0
	.oem_product_name_pointer: dd 0
	.oem_product_revision_pointer: dd 0
	.reserved: times 222 db 0
	.oem_data: times 256 db 0

mode_info_block:	; 'Sector' 3
    ;; Mandatory info for all VBE revisions
	.mode_attributes: dw 0
	.window_a_attributes: db 0
	.window_b_attributes: db 0
	.window_granularity: dw 0
	.window_size: dw 0
	.window_a_segment: dw 0
	.window_b_segment: dw 0
	.window_function_pointer: dd 0
	.bytes_per_scanline: dw 0

    ;; Mandatory info for VBE 1.2 and above
	.x_resolution: dw 0
	.y_resolution: dw 0
	.x_charsize: db 0
	.y_charsize: db 0
	.number_of_planes: db 0
	.bits_per_pixel: db 0
	.number_of_banks: db 0
	.memory_model: db 0
	.bank_size: db 0
	.number_of_image_pages: db 0
	.reserved1: db 1

    ;; Direct color fields (required for direct/6 and YUV/7 memory models)
	.red_mask_size: db 0
	.red_field_position: db 0
	.green_mask_size: db 0
	.green_field_position: db 0
	.blue_mask_size: db 0
	.blue_field_position: db 0
	.reserved_mask_size: db 0
	.reserved_field_position: db 0
	.direct_color_mode_info: db 0

    ;; Mandatory info for VBE 2.0 and above
	.physical_base_pointer: dd 0     ; Physical address for flat memory frame buffer
	.reserved2: dd 0
	.reserved3: dw 0

    ;; Mandatory info for VBE 3.0 and above
	.linear_bytes_per_scan_line: dw 0
    .bank_number_of_image_pages: db 0
    .linear_number_of_image_pages: db 0
    .linear_red_mask_size: db 0
    .linear_red_field_position: db 0
    .linear_green_mask_size: db 0
    .linear_green_field_position: db 0
    .linear_blue_mask_size: db 0
    .linear_blue_field_position: db 0
    .linear_reserved_mask_size: db 0
    .linear_reserved_field_position: db 0
    .max_pixel_clock: dd 0

    .reserved4: times 190 db 0      ; Remainder of mode info block

