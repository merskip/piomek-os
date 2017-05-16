#include "kernel.h"
#include "common.h"
#include "string.h"
#include "../drives/video.h"
#include "../drives/keyboard.h"
#include "commands.h"

void __cli_cpu__(void)
{
    asm("cli");
}

void __halt_cpu__(void)
{
    asm("hlt");
}

void __full_sleep_cpu__(void)
{   
    __cli_cpu__();
    __halt_cpu__();
}

void run_terminal(void)
{
    printf("\n");

    printf(">");
    video_put_null();

    for (;;)
    {
    	u16int key = getch_keycode();

    	if (key & 0x80)
    	    continue;

    	if (key == 0x45)	/* Numlock (?) */
    	    continue;

	if (key == 0x2A || key == 0x36) /* Shift */
	    continue;

	if (key == 0x3A)	/* CapsLock */
	    continue;

	if (key == 0xE) 	/* Backspace */
	{
	    if (video.index % 80 == 0)
		continue;

	    if (video.vchar[video.index-1].ascii == 0x00)
		continue;

	    video.index--;
	    video.vchar[video.index].ascii = 0x20; /* Space */
	    video_move_cursor_line(video.index);

	    continue;
	}
	else if (key == 0x1C) 	/* Enter */
	{
	    u16int i = 0;

	    const u16int pre_index = video.index -1;
	    const u16int com_len = command_lenght(pre_index);
	    const u16int start_index = pre_index - com_len + 1;

	    char buffor[com_len+1];

	    for (i = 0; i < com_len; i++)
	    {
		buffor[i] = video.vchar[start_index + i].ascii;
	    }
	    buffor[com_len] = 0x00;

	    printf("\n");

        if (com_len > 0)
	        run_command(com_len, buffor);

	    printf(">");
	    video_put_null();
	}
	else
	{
	    u8int ascii[] = {keycode_to_ascii(key), 0x00};

	    if (key_special.is_shift == true)
		ascii[0] ^= 0x20;

	    if (key_special.is_capslock == true)
		ascii[0] ^= 0x20;
		
	    printf("%s", ascii);
	}
    }
}

void run_command(u16int len, char buffor[])
{
    u16int i = 0;

    const u16int cmd_len = __cmd_get_len__(buffor, true);
    const u16int cmd_only_len = __cmd_get_len__(buffor, false);

    u8int cmd_str[cmd_len + 1];
    u8int cmd_only[cmd_only_len + 1];

    void* (*call)(u16int, char**);

    if (cmd_str == 0)
	return;

    for (i = 0; i < cmd_len; i++)
    {
    	cmd_str[i] = buffor[i];

    	if (i < cmd_only_len)
    	    cmd_only[i] = buffor[i];
    }
    cmd_str[cmd_len] = 0x00;
    cmd_only[cmd_only_len] = 0x00;

    call = cmd_get_addr(cmd_only);

    /* printf("cmd_len = %i cmd_only_len = %i cmd_addr = %X \n", cmd_len, cmd_only_len, call);  */

    if (call != 0x0)
    {
	u16int cmd_args = cmd_get_args(buffor);
	u8int cmd_arg_index = 0;
	char buffor_argv[cmd_len + 1];
	char* argv[cmd_args];
	
	argv[cmd_arg_index++] = buffor_argv;

	for (i = 0; i <= cmd_len; i++)
	{
	    buffor_argv[i] = cmd_str[i];

	    if (buffor_argv[i] == 0x20)
	    {
		if (cmd_arg_index <= cmd_args)
		    argv[cmd_arg_index++] = buffor_argv + i + 1;

		buffor_argv[i] = 0x00;
	    }
	}

    	call(cmd_args, argv);
    }
    else
    {
    	printf("%s: command not found \n", cmd_only);
    }
}

u16int command_lenght(u16int index_on_end)
{
    u16int i = 0;

    while (video.vchar[index_on_end-i].ascii != 0x00)
    {
	i++;
    }

    return i;
}
