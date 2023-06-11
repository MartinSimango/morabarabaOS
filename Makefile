##### x86_64 VM related #####

x86_64_VM_NAME:= gdb_x86_64
x86_64_VM_SHELL:= limactl shell $(x86_64_VM_NAME)


##### PROGRAMS #####

GCC:=i686-unknown-linux-gnu-gcc #$(x86_64_VM_SHELL) i686-elf-gcc
LD:=i686-unknown-linux-gnu-ld  # $(x86_64_VM_SHELL) i686-elf-ld
OBJCOPY:=$(x86_64_VM_SHELL) i686-elf-objcopy
GDB:=$(x86_64_VM_SHELL) gdb




##### DIRECTORTIES ####
BOOTLOADER=src/bootloader
KERNEL=src/kernel
OBJ=obj
BIN=bin
IMAGE=kernel.iso
FLAGS=-g -Wno-unused-but-set-variable -ffreestanding -falign-jumps -falign-functions -falign-labels -falign-loops -fstrength-reduce -fomit-frame-pointer -finline-functions -Wno-unsused-function -fno-builtin -Werror -Wno-unused-label -Wno-cpp -O0 -Wno-unused-parameter -nostdlib -nostartfiles -nodefaultlibs -Wall -Iinc -std=gnu99  -Wno-unused-variable -Wno-unsused-function 
START_DEBUG:=qemu-system-i386 -hda $(IMAGE)  -S -s 


ALL_HEADER_FILES:=$(wildcard src/kernel/*/*.h)
ALL_SOURCE_FILES:=$(wildcard src/kernel/*/*.c*)

SOURCE_FILES_IN_MODULES:=$(patsubst src/kernel/%.c, $(OBJ)/%.o, $(ALL_SOURCE_FILES))


MODULES:=$(sort $(dir $(wildcard src/kernel/*/)))
MODULES_OBJECT_DIR:=$(patsubst src/kernel/%, $(OBJ)/%, $(MODULES))

INCLUDE_DIRS:=$(patsubst %, -I %, $(MODULES))

C_OBJECT_FILES:=$(patsubst %.c, $(OBJ)/%.o, $(SOURCE_FILES_IN_MODULES))

ASM_OBJECT_FILES:=$(OBJ)/idt.asm.o $(OBJ)/io.asm.o $(OBJ)/kernel.asm.o 

ALL_OBJECT_FILES:=$(ASM_OBJECT_FILES) $(C_OBJECT_FILES) $(OBJ)/kernel.o 

$(MODULES_OBJECT_DIR):
	mkdir -p $@

$(C_OBJECT_FILES): $(OBJ)/%.o : src/kernel/%.c 
	$(GCC) $(FLAGS) -o $@ -c $< $(INCLUDE_DIRS)



build-bootloader-stage-1:
	nasm $(BOOTLOADER)/stage_1/main.asm -f bin -o $(BIN)/boot.bin # 1st stage bootloader
	# nasm $(BOOTLOADER)/stage_1/main.asm -g -f elf -o $(OBJ)/stage_1.o


build-bootloader: build-bootloader-stage-1 bootloader-rust
	# nasm $(BOOTLOADER)/stage_1/main.asm -f bin -o $(BIN)/boot.bin # 1st stage bootloader
	# nasm $(BOOTLOADER)/stage_2/loadkernel.asm -f bin -o $(BIN)/loadkernel.bin # 2nd stage bootloader that loads kernel into RAM



build-kernel: $(MODULES_OBJECT_DIR) $(C_OBJECT_FILES) 
	nasm $(KERNEL)/kernel.asm -g -f elf -o $(OBJ)/kernel.asm.o 
	nasm $(KERNEL)/idt/idt.asm -g -f elf -o $(OBJ)/idt.asm.o
	nasm $(KERNEL)/io/io.asm -g -f elf -o $(OBJ)/io.asm.o
	# nasm $(KERNEL)/grahpics/vbe.asm -g -f elf -o $(OBJ)/vbe.asm.o


	$(GCC) $(FLAGS) -o $(OBJ)/kernel.o -c $(KERNEL)/kernel.c $(INCLUDE_DIRS)

	$(LD) -g -relocatable -o $(OBJ)/fullkernel.o $(ALL_OBJECT_FILES) 

	$(GCC) -T $(KERNEL)/link.ld $(FLAGS) $(OBJ)/fullkernel.o -o $(BIN)/os.bin 


build: build-bootloader build-kernel iso


run-bootloader: clean build-bootloader 
	dd if=$(BIN)/boot.bin  >> $(IMAGE) 
	dd if=rust.bin  >> $(IMAGE) 
	dd if=/dev/zero bs=512 count=1000 >> $(IMAGE)
	qemu-system-i386 -hda $(IMAGE)  -device sb16 -d cpu_reset -monitor stdio -audiodev coreaudio,id=coreaudio,out.frequency=44100,out.channels=2,out.format=s32

iso:
	dd if=$(BIN)/boot.bin  >> $(IMAGE) 
	dd if=$(BIN)/loadkernel.bin  >> $(IMAGE) 
	dd if=$(BIN)/os.bin >> $(IMAGE) 
	dd if=/dev/zero bs=512 count=1000 >> $(IMAGE)

run: 
	qemu-system-i386 -hda $(IMAGE)  -device sb16 -d cpu_reset -monitor stdio -audiodev coreaudio,id=coreaudio,out.frequency=44100,out.channels=2,out.format=s32
#  -soundhw pcspk 
# -device sb16 -audiodev coreaudio,id=coreaudio,out.frequency=48000,out.channels=2,out.format=s32

write-usb: clean build
	# sudo umount /dev/disk4
	sudo dd if=$(IMAGE) bs=512 of=/dev/disk4


run-usb: 
	sudo qemu-system-x86_64 -hda /dev/disk4  -device sb16 -d cpu_reset -monitor stdio -audiodev coreaudio,id=coreaudio,out.frequency=44100,out.channels=2,out.format=s32


all: clean  build run

clean:
	rm -rf bin/*
	rm -rf obj/*
	rm -f *.iso

view:
	xxd $(IMAGE)
# 317017

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


###############  FORMATTING   ###############


NPM:=$(shell which npm)
CLANG_FORMAT:=$(shell which clang-format)


format: check-tools
	clang-format -style=file -i $(ALL_SOURCE_FILES) $(ALL_HEADER_FILES)

$(NPM):
	@echo "You need to install npm first"

$(CLANG_FORMAT): $(NPM)
	sudo npm install -g clang-format

check-tools: $(CLANG_FORMAT) 

gen-clang-config:
	clang-format -style=llvm -dump-config > .clang-format.template.yaml


disassemble-kernel-iso:
	$(x86_64_VM_SHELL) objdump -b binary -D -Mintel -mi386 kernel.iso


disassemble-boot-bin:
	$(x86_64_VM_SHELL) objdump -b binary -D -Mintel -mi386 bin/boot.bin


disassemble-rust-lib:
	$(x86_64_VM_SHELL) objdump -b binary -D -Mintel -mi386 src/bootloader/stage_2/target/msbl/release/libMSBL.a



disassemble-rust-bin:
	$(x86_64_VM_SHELL) objdump -b binary -D -Mintel -mi386 rust.bin


rust-bin:
	 rustc src/bootloader/stage_2/src/lib.rs -o src/bootloader/stage_2/rust.bin

disassemble-kernel-object:	
	objdump -D $(OBJ)/fullkernel.o


bootloader-rust:
	cd src/bootloader/stage_2 && (RUST_TARGET_PATH=$(shell pwd)/src/bootloader/stage_2 xargo build --target msbl --release)
	$(LD) src/bootloader/stage_2/target/msbl/release/libMSBL.a  -n --gc-sections -T src/bootloader/stage_2/link.ld -o rust.bin
