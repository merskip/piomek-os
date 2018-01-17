cmake_minimum_required(VERSION 3.9)
project(PiomekOS)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_C_FLAGS "-g -m32 -nostdlib")
set(CMAKE_C_LINK_FLAGS "-g -m32 -n -T linker.ld -nostdlib")
set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf32")

enable_language(ASM_NASM)

add_executable(kernel.bin
        start.asm
        main.c
        drives/keyboard.c
        drives/video.c
        kernel/commands.c
        kernel/common.c
        kernel/intr.c
        kernel/io.c
        kernel/kernel.c
        kernel/string.c)

add_custom_command(TARGET kernel.bin
        POST_BUILD
        COMMAND cp kernel.bin isofiles/boot/ && grub-mkrescue -o PiomekOS.iso isofiles
        COMMENT "Creating PiomekOS.iso"
        )

configure_file(linker.ld linker.ld)
file(COPY isofiles DESTINATION .)