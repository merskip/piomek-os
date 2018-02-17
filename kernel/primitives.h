#pragma once

typedef unsigned int      u32int;
typedef signed   int      s32int;

typedef unsigned short    u16int;
typedef signed   short    s16int;

typedef unsigned char     u8int;
typedef signed   char     s8int;

#ifndef __cplusplus
/* BOOL */
typedef u8int             bool;
#endif

#define true 1
#define True true
#define TRUE True

#define false 0
#define False false
#define FALSE False

typedef __SIZE_TYPE__ size_t;
