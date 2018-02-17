cmake_minimum_required(VERSION 3.9)
project(PiomekOS)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_C_FLAGS "-g -m32 -nostdlib")
set(CMAKE_CXX_FLAGS "-g -m32 -nostdlib")
set(CMAKE_CXX_LINK_FLAGS "-g -m32 -n -T linker.ld -nostdlib")
set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf32")
set(CMAKE_ASM_NASM_FLAGS "-g")

enable_language(ASM_NASM)

add_executable(kernel.bin
        multiboot.asm
        kernel.asm
        idt.asm
        main.c
        drives/keyboard.c
        drives/video.c
        kernel/commands.c
        kernel/common.c
        kernel/intr.c
        kernel/io.c
        kernel/kernel.c
        kernel/string.c
        kernel/Foo.cpp
        src/gdt.c
        src/gdt.asm)

add_custom_target(${PROJECT_NAME}.iso
        COMMAND cp kernel.bin isofiles/boot/
        COMMAND grub-mkrescue -o ${PROJECT_NAME}.iso isofiles
        DEPENDS kernel.bin
        COMMENT "Building disk image ${PROJECT_NAME}.iso")

configure_file(linker.ld linker.ld)
file(COPY isofiles DESTINATION .)