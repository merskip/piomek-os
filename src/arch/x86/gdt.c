//
// gdt.c
//
// Created by Piotr Merski on 10.02.18
//

#include "gdt.h"

struct gdt_descriptor {
     u16int limit;
    u32int base;
} __attribute__((packed));

struct gdt_descriptor gdt_shared_descriptor;
struct gdt_entry gdt_default_entries[5];

void gdt_init_default() {

    // Special zero entry, must be
    gdt_fill_entry(&gdt_default_entries[0], 0, 0, 0, 0);

    // Kernel code segment
    gdt_fill_entry(&gdt_default_entries[1],
                   GDT_WHOLE_32_BIT_MEMORY_SPACE, 0x9A, 0x0C);
    // Kernel data segment
    gdt_fill_entry(&gdt_default_entries[2],
                   GDT_WHOLE_32_BIT_MEMORY_SPACE, 0x92, 0x0C);

    // User code segment
    gdt_fill_entry(&gdt_default_entries[3],
                   GDT_WHOLE_32_BIT_MEMORY_SPACE, 0xFA, 0x0C);
    // User data segment
    gdt_fill_entry(&gdt_default_entries[4],
                   GDT_WHOLE_32_BIT_MEMORY_SPACE, 0xF2, 0x0C);

    gdt_load_and_flush(gdt_default_entries, sizeof(gdt_default_entries));
}

void gdt_fill_entry(struct gdt_entry *entry, u32int base, u32int limit, u8int access, u8int granularity) {
    *entry = (struct gdt_entry) {
            .base_low = (u16int) (base & 0xFFFF),
            .base_middle = (u8int) ((u8int) (base >> 16) & 0xFF),
            .base_high = (u8int) ((base >> 24) & 0xFF),

            .limit_low = (u16int) (limit & 0xFFFF),
            .limit_and_granularity = (u8int) (((granularity & 0x0F) << 4) | ((limit >> 16) & 0x0F)),

            .access = access,
    };
}

void gdt_flush(void *gdt_desc);

void gdt_load_and_flush(struct gdt_entry *entities, size_t size) {
    gdt_shared_descriptor.base = (u32int)entities;
    gdt_shared_descriptor.limit = (u16int) (size - 1);
    gdt_flush(&gdt_shared_descriptor);
}
