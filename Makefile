build:
	 nasm helloworld.asm -f bin -o boot.bin # make the bootloader

iso: build
	dd if=/dev/zero of=boot.iso bs=512 count=3000 # roughly a disk of 1,5 mb
	dd if=boot.bin of=boot.iso conv=notrunc bs=512 count=1 

run: 
	qemu-system-i386 -drive format=raw,file=boot.iso

view-bin:
	xxd boot.bin
	
	 	
