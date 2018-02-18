;
; multiboot.asm
;
; Created by Piotr Merski on 10.02.2018
;


; For more details see https://www.gnu.org/software/grub/manual/multiboot2/multiboot.html#OS-image-format
section .multiboot_header

mb_header_start:
    dd 0xe85250d6 ; Magic number (multiboot 2)
    dd 0 ; Architecture 0 (protected mode i386)
    dd mb_header_end - mb_header_start ; Header length
    dd -(0xe85250d6 + 0 + (mb_header_end - mb_header_start)) ; Checksum

    ; Tags
    dw 0 ; Type
    dw 0 ; Flags
    dd 8 ; Size
mb_header_end: