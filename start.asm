;
; start.asm
;
; Created by Piotr Merski on 10.02.2018
;

global __start__
global idt
global gdt
global irq1 

	
extern start_kernel
extern do_irq1

section .text

__start__:
	cli					; Disabling interrupts
	mov 	esp, stack + 0x4000

	lgdt 	[gdt_descr]
	lidt 	[idt_descr]

	push 	ebx
	push	eax
	call 	start_kernel
	
SECTION .bss
align 4

stack:
	resb 0x4000

SECTION .data
align 4

gdt_descr:
	dw 	256 * 8 - 1			; 2047
	dd 	gdt

gdt:
	dd 	0x0, 0x0
	dd 	0x0000FFFF, 0x00CF9A00
	dd 	0x0000FFFF, 0x00CF9200

idt_descr:
	dw 	256 * 8 - 1			; 2047
	dd 	idt

idt:
	times 	256 dd 0x0, 0x0
