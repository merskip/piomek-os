//
// idt.h
//
// Created by Piotr Merski on 18.02.18
//

#pragma once

#include "../../../kernel/primitives.h"

struct idt_entry {
    u16int address_low; // First 16 bits of address
    u16int segment; // Code segment in GDT or LDT
    u8int zero; // Unused, always zero
    u8int flags;
    u16int address_high;
} __attribute__((packed));

void idt_init_default();
void idt_fill_entry(struct idt_entry *entry, void *address, u16int segment, u8int flags);
void idt_load_and_flush(struct idt_entry entities[], size_t size);
void idt_enable_interrupts();
