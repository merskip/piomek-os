#include "commands.h"
#include "../drives/video.h"
#include "../drives/keyboard.h"
#include "string.h"

void cmd_init(void)
{
    __cmd_last_cid__ = 0;

    cmd_add("help", cmd__help);
    cmd_add("shutdown", cmd__shutdown);
    cmd_add("reboot", cmd__reboot);
    cmd_add("keytest", cmd__keytest);
    cmd_add("keystats", cmd__keystats);
    cmd_add("chars", cmd__chars);
    cmd_add("cmds", cmd__cmds);
}

u16int cmd_add(const char* str, u32int (*callback)(u16int args, const char* argv[]))
{
    /* 512 - limit */
    if (__cmd_last_cid__ >= 512)
	return -1;

    cmd_s[__cmd_last_cid__].cid = __cmd_last_cid__;
    cmd_s[__cmd_last_cid__].string = str;
    cmd_s[__cmd_last_cid__].callback = callback;

    __cmd_last_cid__++;

    return __cmd_last_cid__ - 1;
}

u16int __cmd_get_len__(const char buffor[], bool full)
{
    u16int i = 0;
    u8int ascii = 0x00;

    while ((ascii = buffor[i]) != 0x00)
    {
	if (full == false && ascii == 0x20)
	    break;

	i++;
    }

    return i;
}

void* cmd_get_addr(const char buffor[])
{
    u16int i = 0;
    
    for (i = 0; i < __cmd_last_cid__; i++)
    {
	if (strcmp(cmd_s[i].string, buffor))
	{
	    return cmd_s[i].callback;
	}
    }

    return 0x0;
}

u16int cmd_get_args(const char buffor[])
{
    u16int i = 0;
    u16int args = 0;
    char ascii = 0x00;

    while ((ascii = buffor[i]) != 0x00)
    {
	if (ascii == 0x20)
	{
	    args++;
	}

	i++;
    }
    
    return args+1;
}

u32int cmd__help(u16int args, const char* argv[])
{
    printf("\n");
    printf("The list of available commands: \n");
    printf("\n");
    printf(" * help      Wyswietla pomoc, czyli to \n");
    printf(" * colors    Wyswietla kolory \n"); 
    printf(" * shutdown  Wylacza komputer, nie dziala \n");
    printf(" * reboot    Uruchamia ponownie komputer \n");
    printf(" * keystats  Wyswietla status klawiszy specjalnych \n");
    printf(" * keytest   Przechwytuje nacisniete klawiszy i je wyswietla. \n");
    printf("             Ich numer w DEC, HEX, status czy zwolniony czy nacisnmiety, \n");
    printf("             oraz znak w ASCII. Aby wyjsc nalezy nacisnac ^C (Ctrl + C) \n");
    printf(" * chars     Generaruje liste dostepnych znakow \n");
    printf(" * cmds      Wyswietla liste polecen wraz z adresami funkcjow \n");
    

    return 0;
}

u32int cmd__shutdown(u16int args, const char* argv[])
{
    video_cls();

    video_set_color(COLOR_MAGNETA | BG_COLOR_BLACK);

    video.index = (VIDEO_SCREEN_HEIGHT / 2 - 2) * 80 + 27;
    printf("It's now safe to turn off");

    video.index = (VIDEO_SCREEN_HEIGHT / 2 - 1) * 80 + 27;
    printf("your computer.");

    video_set_color(COLOR_BLACK | BG_COLOR_BLACK);
    video_move_cursor_line(video.index);

    __full_sleep_cpu__();

    while (true);

    return 1;
}

u32int cmd__reboot(u16int args, const char* argv[])
{
    printf("Reset now! \n");

    keyboard_reset_system();
    
    return 1;
}

u32int cmd__keytest(u16int args, const char* argv[])
{
    u16int key;
    u8int ascii[] = {0x00, 0x00};
    u8int status[] = {0x00, 0x00};
    bool exit = false;

    printf("| Dec    | Hex   |   | ASCII |\n");
    printf("|--------|-------|---|-------|\n");

    for (;;)
    {
	key = getch_keycode();

	if (key == 0x1D)
	    exit = true;

	if (key == 0x2E && exit == true)
	{
	    printf("^C\n");
	    break;
	}

	if (key != 0x1D)
	    exit = false;

	if (key & 0x80)	/* Release the key */
	    status[0] = 0x31;
	else		/* Push the key */
	    status[0] = 0x30;

	/* if (key != 0x1C) */
	ascii[0] = keycode_to_ascii(key & 0x80);
	/* else */
	/* 	ascii[0] = 0x20; */

	printf("| %i\t | %X\t | %s | %s     |\n", key, key, status, ascii);
    }

    return 0;
}

u32int cmd__keystats(u16int args, const char* argv[])
{
    printf("Shift: \t %i \n", key_special.is_shift);
    printf("Ctrl: \t %i \n", key_special.is_ctrl);
    printf("Alt: \t %i \n", key_special.is_alt);

    printf("NumLock: \t %i \n", key_special.is_num);
    printf("Capslock: \t %i \n", key_special.is_capslock);
    printf("ScrollLock: \t %i \n", key_special.is_super);

    return 0;
}

u32int cmd__chars(u16int args, const char* argv[])
{
    u32int i = 0;
    u32int j = (video.index - video.index % VIDEO_SCREEN_WIDTH) / VIDEO_SCREEN_WIDTH;
    char ascii[] = {0x00, 0x00};

    while (true)
    {
	for (; j < VIDEO_SCREEN_HEIGHT-1; j++)
	{
	    ascii[0] = i;
	    printf("%i = %s \n", i, ascii);
	    i++;
	}
	    
	while (true)
	{
	    u32int key = getch_keycode();

	    if (key == 0x1C)
		break;
		
	    if (key == 0x01)
		return;
	}
	j = 0;
    }

    return 0;
}


u32int cmd__cmds(u16int args, const char* argv[])
{
    u16int i = 0;
    u16int j = 0;
    long mod = 0;

    printf("+--------+-----------------------+----------------+\n");
    printf("| CID    | Command               | Address        |\n");
    printf("+--------+-----------------------+----------------+\n");

    for (i = 0; i < __cmd_last_cid__; i++)
    {
	    printf("| %i\t ", cmd_s[i].cid);

	    printf("| %s", cmd_s[i].string);
	    for (j = strlen(cmd_s[i].string); j <= 21; j++)
	        printf(" ");

	    printf("| %X", cmd_s[i].callback);
	    for (j = __int_char_lenght__((int) cmd_s[i].callback, &mod, 16)-2; j <= 9; j++)
	        printf(" ");

	    printf(" |\n");
    }
	printf("+--------+-----------------------+----------------+\n");

    return 0;
}
