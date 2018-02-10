;
; gdt.asm
;
; Created by Piotr Merski on 10.02.2018
;

global gdt
global gdt_descr

section .data

gdt_descr:
    dw 256 * 8 - 1 ; 2047
    dd gdt

gdt:
    dd 0x0, 0x0
    dd 0x0000FFFF, 0x00CF9A00
    dd 0x0000FFFF, 0x00CF9200