#include "arch/x86/gdt.h"
#include "arch/x86/idt.h"

#define ENDLESS_LOOP while (1) {}

void start_kernel(unsigned int magic) {

    gdt_init_default();
    idt_init_default();
    idt_enable_interrupts();

    ENDLESS_LOOP;
}
