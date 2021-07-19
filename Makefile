BOOTLOADER=src/bootloader
KERNEL=src/kernel
OBJ=obj
BIN=bin
IMAGE=morabarabaOS.iso


build-bootloader:
	nasm $(BOOTLOADER)/stage_1/main.asm -f bin -o $(BIN)/boot.bin #1st stage bootloader
	nasm $(BOOTLOADER)/stage_2/loadkernel.asm -f elf32 -o $(OBJ)/loadkernel.o #2nd stage bootloader that loads/calls kernel

	

build-kernel:
	i686-unknown-linux-gnu-gcc -o $(OBJ)/kernel.o -c $(KERNEL)/kernel.c
	i686-unknown-linux-gnu-ld -o $(BIN)/kernel.bin -Ttext=0x7e00 -e main $(OBJ)/loadkernel.o $(OBJ)/kernel.o
	i686-unknown-linux-gnu-objcopy -O binary $(BIN)/kernel.bin $(BIN)/kernel.bin 

build: build-bootloader build-kernel

iso:
	dd if=/dev/zero of=$(IMAGE) bs=512 count=20 #make disk 1 mb in size
	dd if=$(BIN)/boot.bin of=$(IMAGE) conv=notrunc bs=512 seek=0 count=1 
	dd if=$(BIN)/kernel.bin of=$(IMAGE) conv=notrunc bs=512 seek=1 count=2 

run:
	qemu-system-i386 -drive format=raw,file=$(IMAGE)

all: build iso run

view:
	xxd $(IMAGE)
	