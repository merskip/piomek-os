;
; kernel.asm
;
; Created by Piotr Merski on 10.02.2018
;

extern start_kernel

extern gdt_descr
extern idt_descr

section .text

start:
    cli ; Disabling interrupts

    mov esp, stack + stack_size ; Setup the stack

    lgdt [gdt_descr]
    lidt [idt_descr]

    push eax ; Magic number inside multiboot header
    call start_kernel

section .bss

stack: resb 8
stack_size equ $ - stack