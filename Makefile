BOOTLOADER=src/bootloader
KERNEL=src/kernel
OBJ=obj
BIN=bin
IMAGE=kernel.iso
OBJECT_FILES=$(OBJ)/kernel.asm.o $(OBJ)/main.o $(OBJ)/tty.o $(OBJ)/idt.o $(OBJ)/idt.asm.o $(OBJ)/memory.o #$(OBJ)/screen.o  $(OBJ)/util.o $(OBJ)/colours.o 
FLAGS= -g -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unsused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -O0 -Wno-unused-paramter -nostdlib -nostartfiles -nodefaultlibs -Wall -Iinc -std=gnu99 
x86_64_VM_NAME:= arch-:vm
x86_64_VM_SHELL:= limactl shell $(x86_64_VM_NAME)
GCC:=$(x86_64_VM_SHELL) /home/martinsimango.linux/opt/cross/bin/i686-elf-gcc
OBJCOPY:=$(x86_64_VM_SHELL) /home/martinsimango.linux/opt/cross/bin/i686-elf-objcopy
GDB:=$(x86_64_VM_SHELL) gdb
START_DEBUG:=qemu-system-i386 -hda $(IMAGE)  -S -s 

build-bootloader:
	nasm $(BOOTLOADER)/stage_1/main.asm -f bin -o $(BIN)/boot.bin # 1st stage bootloader
	nasm $(BOOTLOADER)/stage_2/loadkernel.asm -f bin -o $(BIN)/loadkernel.bin # 2nd stage bootloader that loads kernel into RAM

build-kernel:
	nasm $(KERNEL)/kernel.asm -g -f elf -o $(OBJ)/kernel.asm.o 
	nasm $(KERNEL)/idt.asm -g -f elf -o $(OBJ)/idt.asm.o

	i686-unknown-linux-gnu-gcc $(FLAGS) -o $(OBJ)/main.o -c $(KERNEL)/main.c
	i686-unknown-linux-gnu-gcc $(FLAGS) -o $(OBJ)/screen.o -c $(KERNEL)/screen.c
	i686-unknown-linux-gnu-gcc $(FLAGS) -o $(OBJ)/util.o -c $(KERNEL)/util.c
	i686-unknown-linux-gnu-gcc $(FLAGS) -o $(OBJ)/colours.o -c $(KERNEL)/colours.c
	i686-unknown-linux-gnu-gcc $(FLAGS) -o $(OBJ)/tty.o -c $(KERNEL)/tty.c
	i686-unknown-linux-gnu-gcc $(FLAGS) -o $(OBJ)/idt.o -c $(KERNEL)/idt.c
	i686-unknown-linux-gnu-gcc $(FLAGS) -o $(OBJ)/memory.o -c $(KERNEL)/memory.c

	i686-unknown-linux-gnu-ld -g -relocatable -o $(OBJ)/kernel.o $(OBJECT_FILES)

	i686-unknown-linux-gnu-gcc -T $(KERNEL)/link.ld $(FLAGS) $(OBJECT_FILES) -o $(BIN)/kernel.bin 



build: build-bootloader build-kernel iso


iso:
	dd if=$(BIN)/boot.bin  >> $(IMAGE) 
	dd if=$(BIN)/loadkernel.bin  >> $(IMAGE) 
	dd if=$(BIN)/kernel.bin >> $(IMAGE) 
	dd if=/dev/zero bs=512 count=100 >> $(IMAGE)

run:
	qemu-system-i386 -hda $(IMAGE) 

all: clean build run

clean:
	rm -rf bin/*
	rm -rf obj/*
	rm -f *.iso

view:
	xxd $(IMAGE)


########### DEBUGGING ###########

debug: clean build iso
	$(START_DEBUG) &
	$(GDB) --iex 'target remote 192.168.5.2:1234'

debug-start:
	$(START_DEBUG)

start-vm:
	limactl start $(x86_64_VM_NAME)

stop-vm:
	limactl stop $(x86_64_VM_NAME)


