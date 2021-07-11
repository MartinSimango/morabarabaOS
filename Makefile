build:
	 nasm bootloader.asm -f bin -o boot.bin # make the bootloader
	 nasm loadkernel.asm -f bin -o kernel.bin 

iso: build
	dd if=/dev/zero of=boot.iso bs=512 count=2 #make disk 1 mb in size
	dd if=boot.bin of=boot.iso conv=notrunc bs=512 count=1 
	dd if=kernel.bin of=boot.iso conv=notrunc bs=512 seek=1 count=1

run: 
	qemu-system-i386 -drive format=raw,file=boot.iso

view-bin:
	xxd boot.bin
	
	 	
