.SUFFIXES: .asm .c .cpp

SUBDIR := drives kernel

CC=gcc
CXX=g++
ASM=nasm

CFLAGS=-m32
CXXLAGS=-m32
LFLAGS=-m elf_i386 -T linker.ld 
ASMFLAGS=-f elf32

OBJS=\
	start.o \
	main.o \
	drives/video.o \
	kernel/io.o \
	kernel/intr.o \
	drives/keyboard.o \
	kernel/common.o \
	kernel/string.o \
	kernel/kernel.o \
	kernel/commands.o

OBJS_LOC=\
	start.o \
	main.o \
	drives/video.o \
	kernel/io.o \
	kernel/intr.o \
	drives/keyboard.o \
	kernel/common.o \
	kernel/string.o \
	kernel/kernel.o \
	kernel/commands.o	

PiomekOS.iso: kernel.bin
	cp kernel.bin iso/boot/kernel.bin
	grub-mkrescue -o $@ iso

kernel.bin: $(OBJS)
	@echo " ----- "
	ld $(LFLAGS) -o $@ $(OBJS_LOC)

.asm.o:
	$(ASM) $(ASMFLAGS) -o $@ $<

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

.cpp.o:
	$(CXX) $(CXXLAGS) -o $@ -c $<


clean:
	rm -f *.o
