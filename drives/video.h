#ifndef __H_VIDEO__
#define __H_VIDEO__

#define VIDEO_SCREEN_WIDTH  80
#define VIDEO_SCREEN_HEIGHT 25

#define COLOR_BLACK       0x0
#define COLOR_BLUE        0x1
#define COLOR_GREEN       0x2
#define COLOR_CYAN        0x3
#define COLOR_RED         0x4
#define COLOR_MAGNETA     0x5
#define COLOR_BROWN       0x6
#define COLOR_LIGHT_GRAY  0x7
#define COLOR_GRAY        0x8
#define COLOR_LIGHT_BLUE  0x9
#define COLOR_LIGHT_GREEN 0xA
#define COLOR_LIGHT_CYAN  0xB
#define COLOR_LIGHT_RED   0xC
#define COLOR_PINK        0xD
#define COLOR_YELLOW      0xE
#define COLOR_WHITE       0xF

#define BG_COLOR_BLACK       (COLOR_BLACK       << 4)
#define BG_COLOR_BLUE        (COLOR_BLUE        << 4)
#define BG_COLOR_GREEN       (COLOR_GREEN       << 4)
#define BG_COLOR_CYAN        (COLOR_CYAN        << 4)
#define BG_COLOR_RED         (COLOR_RED         << 4)
#define BG_COLOR_MAGNETA     (COLOR_MAGNETA     << 4)
#define BG_COLOR_BROWN       (COLOR_BROWN       << 4)
#define BG_COLOR_LIGHT_GRAY  (COLOR_LIGHT_GRAY  << 4)
#define BG_COLOR_GRAY        (COLOR_GRAY        << 4)
#define BG_COLOR_LIGHT_BLUE  (COLOR_LIGHT_BLUE  << 4)
#define BG_COLOR_LIGHT_GREEN (COLOR_LIGHT_GREEN << 4)
#define BG_COLOR_LIGHT_CYAN  (COLOR_LIGHT_CYAN  << 4)
#define BG_COLOR_LIGHT_RED   (COLOR_LIGHT_RED   << 4)
#define BG_COLOR_PINK        (COLOR_PINK        << 4)
#define BG_COLOR_YELLOW      (COLOR_YELLOW      << 4)
#define BG_COLOR_WHITE       (COLOR_WHITE       << 4)

#define COLOR_DEFAULT (COLOR_WHITE | BG_COLOR_BLACK)

typedef struct
{
    unsigned char ascii;
    unsigned char color;
} Video_vchar;

struct
{
    Video_vchar* vchar;
    int index;

    unsigned char color;
} video;

void video_init();
void video_cls();
void color_test();

void video_puts(const char* s);
void video_puts_color(const char* s, unsigned short int color);
void video_put(const char s);

void video_put_null(void);

void video_set_color(unsigned short int color);
void video_set_color_char(unsigned short int color, int position);
void color_reset();

void video_scroll();

void video_move_cursor(int row, int col);
void video_move_cursor_line(int position);


#endif
