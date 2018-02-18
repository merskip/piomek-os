//
// gdt.h
//
// Created by Piotr Merski on 10.02.18
//

#pragma once
#include"../../../kernel/primitives.h"

#define GDT_WHOLE_32_BIT_MEMORY_SPACE 0x0, 0xFFFFFFFF

struct gdt_entry {
    u16int limit_low; // The lower 16 bits of the limit.
    u16int base_low; // The lower 16 bits of the base.
    u8int base_middle; // The next 8 bits of the base.
    u8int access; // Flags of access
    u8int limit_and_granularity; // The last 8 bits of limit and granularity
    u8int base_high; // The last 8 bits of the base.
} __attribute__((packed));

void gdt_init_default();

void gdt_fill_entry(struct gdt_entry *entry, u32int base, u32int limit, u8int access, u8int granularity);
void gdt_load_and_flush(struct gdt_entry entities[], size_t size);
