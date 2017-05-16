#include <stdarg.h>
#include "string.h"
#include "common.h"
#include "../drives/video.h"

int __int_char_lenght__(int number, long* mod, int system)
{
    long i = 1;
    int len = 0;

    if (number < 0)
	number *= -1;

    if (number == 0 || number == 1)
    {
	*mod = 1;
	return 1;
    }

    for (i = 1; i <= number; i *= system)
    {
	len++;
    }

    *mod = (i == 1) ? i : i/system;

    return len;
}

void print_int_dec(int number)
{
    int i = 0;
    long mod;
    int number_len = __int_char_lenght__(number, &mod, 10);
    
    if (number < 0)
    {
	video_put(0x2D); // print -
	number *= -1;
    }

    for (i = 0; i < number_len; i++)
    {
	video_put(number / mod + 0x30);
	number -= number / mod * mod;
	mod /= 10;
    }
}

void print_int_hex(int number)
{
    __print_int_hex__(number, false);
}

void print_int_HEX(int number)
{
    __print_int_hex__(number, true);
}

void __print_int_hex__(int number, bool uppercase)
{
    int i = 0;
    long mod;
    int number_len = __int_char_lenght__(number, &mod, 16);
    int dec_char = 0;
    int offset_char = (uppercase == true) ? 0x37 : 0x57;

    if (number < 0)
    {
	video_put(0x2D); // print -
	number *= -1;
    }

    video_puts("0x");

    for (i = 0; i < number_len; i++)
    {
	dec_char = number / mod;
	video_put((dec_char < 0xA) ? dec_char+0x30 : dec_char+offset_char);
	number -= number / mod * mod;
	mod /= 16;
    }
}

void __printf__(const char* format, ...)
{
    int i = 0;
    char char_buf[] = {0x00, 0x00};
    va_list args;

    va_start(args, format);

    while (format[i] != 0x00)
    {
	switch(format[i])
	{
	case '%':
	    i++;
	    
	    switch (format[i])
	    {
		/* String */
	    case 's':
		video_puts(va_arg(args, const char*));
		break;
	    
		/* Integer */
	    case 'i': 
	    case 'd':
		print_int_dec(va_arg(args, int));
		break;

		/* Hex lowercase */
	    case 'x':
		print_int_hex(va_arg(args, int));
		break;

		/* Hex uppercase */
	    case 'X':
		print_int_HEX(va_arg(args, int));
		break;
		
	    }
	    break;

	default:
	    char_buf[0] = format[i];

	    video_puts(char_buf);
	    break;
	}

	i++;
    }
    
    va_end(args);
    return;
}

void print_right(const char* s)
{
    int i = 0;
    int len = 0;

    while (s[i] != 0x00)
    {
	i++;
    }
    len = i;

    video.index = video.index + (80 - (video.index % 80) - len);

    video_puts(s);
}

void print_right_color(const char* s, unsigned int color)
{
    unsigned short int old_color = video.color;
    video.color = color;

    print_right(s);

    video.color = old_color;
    video_move_cursor_line(video.index);
}

bool __strcmp__(const char s1[], const char s2[])
{
    u16int i = 0;

    while (true)
    {
	if (s1[i] == 0x00 && s2[i] == 0x00) /* End of both strings */
	    return true;

	if (s1[i] == 0x00 || s2[i] == 0x00) /* End of one of the strings */
	    return false;

	if (s1[i] != s2[i])
	    return false;

	i++;
    }
}

u32int __strlen__(const char s[])
{
    u16int i = 0;

    while (s[i] != 0x00)
    {
	i++;
    }

    return i;
}
