#include "video.h"

void video_init()
{
    char c = (*(unsigned short int*) 0x410 ) & 0x30;
 
    if (c==0x30)
    {
	video.vchar = (Video_vchar*) 0xB0000;
    }
    else
    {
	video.vchar = (Video_vchar*) 0xB8000;
    }
    video.index = 0;

    video.color = COLOR_DEFAULT;

    video_move_cursor_line(0);
}

void video_cls()
{
    int  i = 0;
    video.index = 0;

    for(i = 0; i < VIDEO_SCREEN_WIDTH * VIDEO_SCREEN_HEIGHT; i++)
    {
    	video.vchar[i].ascii = 0x00; /* Null char */
    	video.vchar[i].color = COLOR_BLACK | BG_COLOR_BLACK;
    }

    video.index = 0;
    video_move_cursor_line(video.index);
}

void color_test()
{
    video_move_cursor_line(video.index);

    int i = 0;
    /* Color chars */
    while (i <= 0xF)
    {
        video.vchar[video.index].ascii = (i < 0x0A) ? i+0x30 : i+0x37; /* int to ascii 0-F */
        video.vchar[video.index].color = 0xf - i;
        
        if (i == 0xF) // for black foreground...
            video.vchar[video.index].color |= 0xf << 4; // ...white background
    	
	    video.index++;
	    i++;
    }
    video_put('\n');
    
    i = 0;
    /* Background chars */
    while (i <= 0xF)
    {
        video.vchar[video.index].ascii = ' ';
        video.vchar[video.index].color = (0xF - i) << 4;
        
	    video.index++;
	    i++;
    }
    video_put('\n');
    
    i = 0;
    /* Color chars on background */
    while (i <= 0xF)
    {
        char ascii = (i < 0x0A) ? i+0x30 : i+0x37; /* int to ascii 0-F */;
        unsigned char color = 0xf - i | i << 4;
        
        video.vchar[video.index].ascii = ' ';
        video.vchar[video.index].color = color;
        
        video.vchar[video.index+1].ascii = ascii;
        video.vchar[video.index+1].color = color;
        
        video.vchar[video.index+2].ascii = ' ';
        video.vchar[video.index+2].color = color;
        
        video.index += 3;
	    i++;
    }
    video_put('\n');
}

void video_puts(const char* s)
{
    int i = 0;

    while(s[i] != 0x00)
    {
	if (video.index == VIDEO_SCREEN_WIDTH * VIDEO_SCREEN_HEIGHT)
	{
	    video_scroll();
	}

	switch(s[i])
	{
	case '\n':
	    video.index = video.index + (80 - video.index % 80);
	    break;
	case '\r':
	    video.index = video.index - video.index % 80;
	    break;
	case '\t':
	    if ((video.index % 80) % 8 == 0)
		video.index += 8;

	    do
	    {
		video.index++;
	    } while ((video.index % 80) % 8 != 0);
	    break;
	default:
	    video.vchar[video.index].ascii = s[i];
	    video.vchar[video.index].color = video.color;

	    video.index++;
	    break;
	}

	i++;
    }
	
    video_move_cursor_line(video.index);
}

void video_puts_color(const char* s, unsigned short int color)
{
    unsigned short int old_color = video.color;
    video.color = color;

    video_puts(s);

    video.color = old_color;
    video_move_cursor_line(video.index);
}

void video_put(const char s)
{
    char one_char[] = {s, 0x00};

    video_puts(one_char);
}

void video_put_null(void)
{
    if (video.index == VIDEO_SCREEN_WIDTH * VIDEO_SCREEN_HEIGHT)
    {
	video_scroll();
    }

    video.vchar[video.index].ascii = 0x00;
    video.vchar[video.index].color = video.color;

    video.index++;

    video_move_cursor_line(video.index);
}

void video_set_color(unsigned short int color)
{
    video.color = color;
}

void video_set_color_char(unsigned short int color, int position)
{
    unsigned short int color_set = video.vchar[position].color >> 4;
    color_set <<= 4;

    color <<= 4;
    color >>= 4;

    color_set |= color;

    video.vchar[position].color = color_set;
}

void color_reset()
{
    video_set_color(COLOR_DEFAULT);
}

void video_scroll()
{
    int i;
    
    /* Copy each line one above */
    for (i = 0; i < VIDEO_SCREEN_WIDTH * (VIDEO_SCREEN_HEIGHT-1); i++)
    {
	video.vchar[i].ascii = video.vchar[i + VIDEO_SCREEN_WIDTH].ascii;
	video.vchar[i].color = video.vchar[i + VIDEO_SCREEN_WIDTH].color;
    }

    /* Delete last line */
    for(i = 0; i < VIDEO_SCREEN_WIDTH; ++i)
    {
	video.vchar[VIDEO_SCREEN_WIDTH * (VIDEO_SCREEN_HEIGHT-1)+i].ascii = 0x00;
	video.vchar[VIDEO_SCREEN_WIDTH * (VIDEO_SCREEN_HEIGHT-1)+i].color = COLOR_BLACK | BG_COLOR_BLACK;
    }

    if (video.index > VIDEO_SCREEN_WIDTH)
	video.index = video.index - VIDEO_SCREEN_WIDTH;
    else
	video.index = 0x0;

    video_move_cursor_line(video.index);
}

void video_move_cursor(int row, int col)
{
    video_move_cursor_line(row * VIDEO_SCREEN_WIDTH + col);
}

void video_move_cursor_line(int position)
{
    outportb(0x3D4, 0x0F);
    outportb(0x3D5, (unsigned char) (position & 0xFF));
    outportb(0x3D4, 0x0E);
    outportb(0x3D5, (unsigned char) ((position >> 8) & 0xFF));

    video_set_color_char(video.color, position);
}
