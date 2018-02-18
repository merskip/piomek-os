cmake_minimum_required(VERSION 3.9)
project(PiomekOS)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_C_FLAGS "-g -m32 -nostdlib")
set(CMAKE_CXX_FLAGS ${CMAKE_C_FLAGS})

set(CMAKE_C_LINK_FLAGS "-g -m32 -n -T linker.ld -nostdlib")
set(CMAKE_CXX_LINK_FLAGS ${CMAKE_C_LINK_FLAGS})

set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf32")
set(CMAKE_ASM_NASM_FLAGS "-g")

enable_language(ASM_NASM)

add_executable(kernel.bin
        src/multiboot.asm
        src/kernel.asm
        src/kernel.c
        src/arch/x86/gdt.c
        src/arch/x86/gdt.asm
        src/arch/x86/idt.c
        src/arch/x86/idt.asm
        src/arch/x86/idt_handlers.c)

set(INCLUDE_DIRECTORIES "src")

add_custom_target(${PROJECT_NAME}.iso
        COMMAND cp kernel.bin isofiles/boot/
        COMMAND grub-mkrescue -o ${PROJECT_NAME}.iso isofiles
        DEPENDS kernel.bin
        COMMENT "Building disk image ${PROJECT_NAME}.iso")

configure_file(linker.ld linker.ld)
file(COPY isofiles DESTINATION .)