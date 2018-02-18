;
; idt.asm
;
; Created by Piotr Merski on 18.02.18
;

global idt_flush

idt_flush:
    mov eax, [esp + 4] ; Load address of IDT descriptor struct to eax
    lidt [eax] ; Load new IDT
    ret
