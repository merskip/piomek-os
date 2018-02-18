;
; kernel.asm
;
; Created by Piotr Merski on 10.02.2018
;

extern start_kernel

section .text

start:
    cli ; Disabling interrupts

    mov esp, stack + stack_size ; Setup the stack

    push eax ; Magic number inside multiboot header
    call start_kernel

section .bss

stack: resb 8
stack_size equ $ - stack