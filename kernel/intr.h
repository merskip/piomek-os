#ifndef __H_INTR__
#define __H_INTR__

typedef struct desc_struct 
{ 
    long a;
    long b;
} desc_table[256]; 
 
extern desc_table gdt;
extern desc_table idt; 
 
void set_intr_gate(int n, void* addr);
void set_trap_gate(int n, void* addr);
void set_system_gate(int n, void* addr);

void disable_irq(unsigned int irq);
void enable_irq(unsigned int irq);

#endif
