#include "intr.h"
#include "io.h"

#define _set_gate(gate_addr, type, dpl, addr)		\
    __asm__("movw %%dx,%%ax\n\t"			\
	    "movw %0,%%dx\n\t"				\
	    "movl %%eax,%1\n\t"				\
	    "movl %%edx,%2\n\t"				\
	    ::"i"((short)(0x8000+((dpl)<<13)+((type)<<8))),	\
	     "o"(*((char *)(gate_addr))),		\
	     "o"(*(4+(char *)(gate_addr))),		\
	     "d"((char *)(addr)),"a"(0x00080000)) 
 
void set_intr_gate(int n, void* addr) 
{ 
    _set_gate(&idt[n], 14, 0, addr); 
} 
 
void set_trap_gate(int n, void* addr) 
{ 
    _set_gate(&idt[n], 15, 0, addr); 
} 
 
void set_system_gate(int n, void* addr) 
{ 
    _set_gate(&idt[n], 15, 3, addr); 
}

static unsigned int cached_irq_mask = 0xffff; 
 
#define __byte(x,y)       (((unsigned char *)&(y))[x]) 
#define cached_21      (__byte(0,cached_irq_mask)) 
#define cached_A1      (__byte(1,cached_irq_mask)) 
 
void disable_irq(unsigned int irq) 
{ 
    unsigned int mask = 1 << irq; 
    cached_irq_mask |= mask; 
    if (irq & 8) 
    { 
	outportb(cached_A1,0xA1); 
    } else { 
	outportb(cached_21,0x21); 
    } 
} 
 
void enable_irq(unsigned int irq) 
{ 
    unsigned int mask = ~(1 << irq);
    cached_irq_mask &= mask; 
    if (irq & 8) { 
	outportb(cached_A1,0xA1); 
    } else { 
	outportb(cached_21,0x21); 
    } 
}
