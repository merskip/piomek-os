#ifndef __H_KERNEL__
#define __H_KERNEL__

#include "common.h"

void __cli_cpu__(void);
void __halt_cpu__(void);
void __full_sleep_cpu__(void);

void run_terminal(void);

void run_command(u16int len, char* buffor);
u16int command_lenght(u16int index_on_end);
#endif
