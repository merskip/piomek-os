//
// idt.c
//
// Created by Piotr Merski on 18.02.18
//

#include "idt.h"
#include "idt_handlers.h"

struct idt_descriptor {
    u16int limit;
    u32int base;
} __attribute__((packed));

struct idt_descriptor idt_shared_descriptor;
struct idt_entry idt_default_entries[256];


void idt_init_default() {
    idt_fill_entry(&idt_default_entries[0], isr_division_by_zero, 0x08, 0x8E);
    idt_fill_entry(&idt_default_entries[1], isr_debug_exception, 0x08, 0x8E);
    idt_fill_entry(&idt_default_entries[2], isr_non_maskable_interrput, 0x08, 0x8E);
    idt_fill_entry(&idt_default_entries[3], isr_breakpoint_exception, 0x08, 0x8E);
    idt_fill_entry(&idt_default_entries[4], isr_detected_overflow, 0x08, 0x8E);
    idt_fill_entry(&idt_default_entries[5], isr_out_of_bounds_exception, 0x08, 0x8E);
    idt_fill_entry(&idt_default_entries[6], isr_invalid_opcode_exception, 0x08, 0x8E);
    idt_fill_entry(&idt_default_entries[7], isr_no_coprocessor_exception, 0x08, 0x8E);
    idt_fill_entry(&idt_default_entries[8], isr_double_fault, 0x08, 0x8E);
    idt_fill_entry(&idt_default_entries[9], isr_coprocessor_segment_overrun, 0x08, 0x8E);
    idt_fill_entry(&idt_default_entries[10], isr_bad_tss, 0x08, 0x8E);
    idt_fill_entry(&idt_default_entries[11], isr_segment_not_present, 0x08, 0x8E);
    idt_fill_entry(&idt_default_entries[12], isr_stack_fault, 0x08, 0x8E);
    idt_fill_entry(&idt_default_entries[13], isr_general_protection_fault, 0x08, 0x8E);
    idt_fill_entry(&idt_default_entries[14], isr_page_fault, 0x08, 0x8E);
    idt_fill_entry(&idt_default_entries[15], isr_reserved_15, 0x08, 0x8E);
    idt_fill_entry(&idt_default_entries[16], isr_coprocessor_fault, 0x08, 0x8E);
    idt_fill_entry(&idt_default_entries[17], isr_alignment_check_exception, 0x08, 0x8E);
    idt_fill_entry(&idt_default_entries[18], isr_machine_check_exception, 0x08, 0x8E);
    for (int i = 19; i <= 31; i++) {
        idt_fill_entry(&idt_default_entries[0], isr_reserved_from_19_to_31, 0x08, 0x8E);
    }
    for (int i = 32; i < 256; i++) {
        idt_fill_entry(&idt_default_entries[i], 0, 0, 0);
    }

    idt_load_and_flush(idt_default_entries, 256);
}

void idt_fill_entry(struct idt_entry *entry, void *address, u16int segment, u8int flags) {
    *entry = (struct idt_entry) {
            .address_low = (u16int) ((u32int) address & 0xFFFF),
            .address_high = (u16int) (((u32int) address >> 16) & 0xFFFF),
            .segment = segment,
            .flags = flags,
            .zero = 0
    };
}

void idt_flush(struct idt_descriptor *idt_desc);

void idt_load_and_flush(struct idt_entry *entities, size_t size) {
    idt_shared_descriptor.base = (u32int) entities;
    idt_shared_descriptor.limit = (u16int) (sizeof(struct idt_entry) * size - 1);
    idt_flush(&idt_shared_descriptor);
}

void idt_enable_interrupts() {
    __asm__("sti");
}
