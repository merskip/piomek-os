#include "io.h"

void outportb(unsigned short port, unsigned char val)
{
    __asm__("outb %%al,%%dx"::"a"(val),"d"(port)); 
} 
 
unsigned char inportb(unsigned short port)
{ 
    unsigned char __ret; 
    __asm__("inb %%dx,%%al":"=a"(__ret):"d"(port));
    return __ret; 
} 
