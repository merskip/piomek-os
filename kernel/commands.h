#ifndef __H_COMMANDS__
#define __H_COMMANDS__

#include "common.h"

struct cmd_t {
    u16int cid;
    const char* string;
    u32int (*callback)(u16int args, const char* argv[]);
};
struct cmd_t cmd_s[512];
u16int __cmd_last_cid__;

void cmd_init(void);
u16int cmd_add(const char* str, u32int (*callback)(u16int args, const char* argv[]));

u16int __cmd_get_len__(const char buffor[], bool full);
void* cmd_get_addr(const char buffor[]);

u16int cmd_get_args(const char buffor[]);

u32int cmd__help(u16int args, const char* argv[]);
u32int cmd__shutdown(u16int args, const char* argv[]);
u32int cmd__reboot(u16int args, const char* argv[]);
u32int cmd__keytest(u16int args, const char* argv[]);
u32int cmd__keystats(u16int args, const char* argv[]);
u32int cmd__chars(u16int args, const char* argv[]);
u32int cmd__cmds(u16int args, const char* argv[]);
#endif
