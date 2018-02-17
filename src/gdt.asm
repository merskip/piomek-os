;
; gdt.asm
;
; Created by Piotr Merski on 17.02.18
;

global gdt_flush

gdt_flush:
    mov eax, [esp + 4] ; Load address of GDT descriptor struct to eax
    lgdt [eax] ; Load new GDT

    ; Reload CS register
    jmp 0x08:.reload_cs
.reload_cs:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ret ; Done, new GDT is loaded
