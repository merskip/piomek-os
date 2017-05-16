#include "keyboard.h"
#include "../kernel/io.h"
#include "../kernel/string.h"
#include "video.h"

enum KEYBOARD_ENCODER_IO
{
    KEYBOARD_ENC_INPUT_BUF	=	0x60,
    KEYBOARD_ENC_CMD_REG	=	0x60
};
 
enum KEYBOARD_CTRL_IO
{
    KEYBOARD_CTRL_STATS_REG	=	0x64,
    KEYBOARD_CTRL_CMD_REG	=	0x64
};

enum KEYBOARD_CTRL_STATS_MASK 
{
    KEYBOARD_CTRL_STATS_MASK_OUT_BUF	=	1,		//00000001
    KEYBOARD_CTRL_STATS_MASK_IN_BUF     =	2,		//00000010
    KEYBOARD_CTRL_STATS_MASK_SYSTEM     =	4,		//00000100
    KEYBOARD_CTRL_STATS_MASK_CMD_DATA	=	8,		//00001000
    KEYBOARD_CTRL_STATS_MASK_LOCKED	=	0x10,		//00010000
    KEYBOARD_CTRL_STATS_MASK_AUX_BUF	=	0x20,		//00100000
    KEYBOARD_CTRL_STATS_MASK_TIMEOUT	=	0x40,		//01000000
    KEYBOARD_CTRL_STATS_MASK_PARITY	=	0x80		//10000000
};

enum KEYBOARD_ENC_CMDS
{
    KEYBOARD_ENC_CMD_SET_LED			=	0xED,
    KEYBOARD_ENC_CMD_ECHO		      	=	0xEE,
    KEYBOARD_ENC_CMD_SCAN_CODE_SET		=	0xF0,
    KEYBOARD_ENC_CMD_ID				=	0xF2,
    KEYBOARD_ENC_CMD_AUTODELAY			=	0xF3,
    KEYBOARD_ENC_CMD_ENABLE			=	0xF4,
    KEYBOARD_ENC_CMD_RESETWAIT			=	0xF5,
    KEYBOARD_ENC_CMD_RESETSCAN			=	0xF6,
    KEYBOARD_ENC_CMD_ALL_AUTO		        =	0xF7,
    KEYBOARD_ENC_CMD_ALL_MAKEBREAK		=	0xF8,
    KEYBOARD_ENC_CMD_ALL_MAKEONLY		=	0xF9,
    KEYBOARD_ENC_CMD_ALL_MAKEBREAK_AUTO	        =	0xFA,
    KEYBOARD_ENC_CMD_SINGLE_AUTOREPEAT		=	0xFB,
    KEYBOARD_ENC_CMD_SINGLE_MAKEBREAK		=	0xFC,
    KEYBOARD_ENC_CMD_SINGLE_BREAKONLY		=	0xFD,
    KEYBOARD_ENC_CMD_RESEND			=	0xFE,
    KEYBOARD_ENC_CMD_RESET			=	0xFF
};

enum KEYBOARD_CTRL_CMDS
{
    KEYBOARD_CTRL_CMD_READ			=	0x20,
    KEYBOARD_CTRL_CMD_WRITE			=	0x60,
    KEYBOARD_CTRL_CMD_SELF_TEST		        =	0xAA,
    KEYBOARD_CTRL_CMD_INTERFACE_TEST	        =	0xAB,
    KEYBOARD_CTRL_CMD_DISABLE			=	0xAD,
    KEYBOARD_CTRL_CMD_ENABLE			=	0xAE,
    KEYBOARD_CTRL_CMD_READ_IN_PORT		=	0xC0,
    KEYBOARD_CTRL_CMD_READ_OUT_PORT	        =	0xD0,
    KEYBOARD_CTRL_CMD_WRITE_OUT_PORT	        =	0xD1,
    KEYBOARD_CTRL_CMD_READ_TEST_INPUTS	        =	0xE0,
    KEYBOARD_CTRL_CMD_SYSTEM_RESET		=	0xFE,
    KEYBOARD_CTRL_CMD_MOUSE_DISABLE	        =	0xA7,
    KEYBOARD_CTRL_CMD_MOUSE_ENABLE		=	0xA8,
    KEYBOARD_CTRL_CMD_MOUSE_PORT_TEST	        =	0xA9,
    KEYBOARD_CTRL_CMD_MOUSE_WRITE		=	0xD4
};

int keyboard_scancode[] = 
{
    KEY_UNKNOWN,	        //0
    KEY_ESCAPE,		        //1
    KEY_1,			//2
    KEY_2,			//3
    KEY_3,			//4
    KEY_4,			//5
    KEY_5,			//6
    KEY_6,			//7
    KEY_7,			//8
    KEY_8,			//9
    KEY_9,			//0xA
    KEY_0,			//0xB
    KEY_MINUS,		        //0xC
    KEY_EQUAL,		        //0xD
    KEY_BACKSPACE,	        //0xE
    KEY_TAB,		        //0xG
    KEY_Q,			//0x10
    KEY_W,			//0x11
    KEY_E,			//0x12
    KEY_R,			//0x13
    KEY_T,			//0x14
    KEY_Y,			//0x15
    KEY_U,			//0x16
    KEY_I,			//0x17
    KEY_O,			//0x18
    KEY_P,			//0x19
    KEY_LEFTBRACKET,            //0x1A
    KEY_RIGHTBRACKET,           //0x1B
    KEY_RETURN,		        //0x1C
    KEY_LCTRL,		        //0x1D
    KEY_A,			//0x1E
    KEY_S,			//0x1F
    KEY_D,			//0x20
    KEY_F,			//0x21
    KEY_G,			//0x22
    KEY_H,			//0x23
    KEY_J,			//0x24
    KEY_K,			//0x25
    KEY_L,			//0x26
    KEY_SEMICOLON,	        //0x27
    KEY_QUOTE,		        //0x28
    KEY_GRAVE,		        //0x29
    KEY_LSHIFT,		        //0x2A
    KEY_BACKSLASH,	        //0x2b
    KEY_Z,			//0x2c
    KEY_X,			//0x2d
    KEY_C,			//0x2e
    KEY_V,			//0x2f
    KEY_B,			//0x30
    KEY_N,			//0x31
    KEY_M,			//0x32
    KEY_COMMA,	         	//0x33
    KEY_DOT,    		//0x34
    KEY_SLASH,	         	//0x35
    KEY_RSHIFT,		        //0x36
    KEY_KP_ASTERISK,            //0x37
    KEY_RALT,		        //0x38
    KEY_SPACE,		        //0x39
    KEY_CAPSLOCK,	        //0x3A
    KEY_F1,			//0x3B
    KEY_F2,			//0x3C
    KEY_F3,			//0x3D
    KEY_F4,			//0x3E
    KEY_F5,			//0x3F
    KEY_F6,			//0x40
    KEY_F7,			//0x41
    KEY_F8,			//0x42
    KEY_F9,			//0x43
    KEY_F10,		        //0x44
    KEY_KP_NUMLOCK,	        //0x45
    KEY_SCROLLLOCK,           	//0x46
    KEY_HOME,        		//0x47
    KEY_KP_8,	        	//0x48	//keypad up arrow
    KEY_PAGEUP,	        	//0x49
    KEY_KP_2,	        	//0x50	//keypad down arrow
    KEY_KP_3,	        	//0x51	//keypad page down
    KEY_KP_0,	        	//0x52	//keypad insert key
    KEY_KP_DECIMAL,      	//0x53	//keypad delete key
    KEY_UNKNOWN,	        //0x54
    KEY_UNKNOWN,        	//0x55
    KEY_UNKNOWN,         	//0x56
    KEY_F11,	        	//0x57
    KEY_F12			//0x58
};

unsigned long int keyboard_ctrl_read_status()
{
    return inportb(KEYBOARD_CTRL_STATS_REG);
}

void keyboard_ctrl_send_cmd (unsigned long int cmd)
{
    //! wait for kkybrd controller input buffer to be clear
    while (1)
    {
	if ( (keyboard_ctrl_read_status () & KEYBOARD_CTRL_STATS_MASK_IN_BUF) == 0)
	{
	    break;
	}
    }
 
    outportb (KEYBOARD_CTRL_CMD_REG, cmd);
}

//! read keyboard encoder buffer
unsigned long int keyboard_enc_read_buf ()
{
    return inportb (KEYBOARD_ENC_INPUT_BUF);
}
 
//! send command byte to keyboard encoder
void keyboard_enc_send_cmd (unsigned long int cmd)
{
 
    //! wait for kkybrd controller input buffer to be clear
    while (1)
    {
	if ( (keyboard_ctrl_read_status () & KEYBOARD_CTRL_STATS_MASK_IN_BUF) == 0)
	{
	    break;
	}
    }

    //! send command byte to kybrd encoder
    outportb (KEYBOARD_ENC_CMD_REG, cmd);
}

//! sets leds
void keyboard_set_leds()
{
    u32int data = 0;
 
    //! set or clear the bit
    data = (keyboard_leds.scroll) ? (data | 1) : (data & 1);
    data = (keyboard_leds.num) ? (keyboard_leds.num | 2) : (keyboard_leds.num & 2);
    data = (keyboard_leds.caps) ? (keyboard_leds.num | 4) : (keyboard_leds.num & 4);
 
    //! send the command -- update keyboard Light Emetting Diods (LEDs)
    keyboard_enc_send_cmd (KEYBOARD_ENC_CMD_SET_LED);
    keyboard_enc_send_cmd (data);
}

bool keyboard_self_test ()
{
    //! send command
    keyboard_ctrl_send_cmd (KEYBOARD_CTRL_CMD_SELF_TEST);
 
    //! wait for output buffer to be full
    while (1)
	if (keyboard_ctrl_read_status () & KEYBOARD_CTRL_STATS_MASK_OUT_BUF)
	    break;
 
    //! if output buffer == 0x55, test passed
    return (keyboard_enc_read_buf () == 0x55) ? true : false;
}

//! disables the keyboard
void keyboard_disable ()
{
 
    keyboard_ctrl_send_cmd (KEYBOARD_CTRL_CMD_DISABLE);
    //_keyboard_disable = true;
}

//! enables the keyboard
void keyboard_enable ()
{
 
    keyboard_ctrl_send_cmd (KEYBOARD_CTRL_CMD_ENABLE);
    //_keyboard_disable = false;
}

//! reset the system
void keyboard_reset_system ()
{
 
    //! writes 11111110 to the output port (sets reset system line low)
    keyboard_ctrl_send_cmd (KEYBOARD_CTRL_CMD_WRITE_OUT_PORT);
    keyboard_enc_send_cmd (0xfe);
}

u16int getch_keycode(void)
{
    static u16int key_last = KEY_UNKNOWN;
    u16int key_buf;

    while (true)
    {
	key_buf = keyboard_enc_read_buf();

	if (key_last != key_buf)
	{
	    key_last = key_buf;
	    
	    if (key_buf == 0x2A || key_buf == 0x36) /* Shift on */
	    {
		key_special.is_shift = true;
	    }
	    else if (key_buf == 0xAA || key_buf == 0xB6) /* Shift off */
	    {
	     	key_special.is_shift = false;
	    }

	    if (key_buf == 0x3A) /* CapsLock on */
	    {
		key_special.is_capslock = (key_special.is_capslock == true) ? false : true;
	    }

	    break; // Goto return and return key_buf
	}
	else
	    continue; // Good programming style :)
    }

    return key_buf;
}

u16int getch(void)
{
    u16int keycode;

    while (true)
    {
	keycode = getch_keycode();

	if (keycode & 0x80)	/* Break */
	    continue;

	if (keycode == 0x45)	/* NumLock */
	    continue;

	break;
    }

    return (key_special.is_shift == true || key_special.is_capslock == true) ? keycode_to_ascii(keycode) - 0x20 : keycode_to_ascii(keycode);
}

u8int keycode_to_ascii(u16int key_code)
{
    u8int key_ascii = keyboard_scancode[key_code];

    return keyboard_scancode[key_code];
} 
