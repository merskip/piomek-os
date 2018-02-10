;
; idt.asm
;
; Created by Piotr Merski on 10.02.18
;

global idt
global idt_descr

section .data

idt_descr:
    dw 256 * 8 - 1 ; 2047
    dd idt

idt:
    times 256 dd 0x0, 0x0
