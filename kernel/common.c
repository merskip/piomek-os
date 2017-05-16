#include "kernel.h"
#include "../drives/video.h"
#include "common.h"

int __primitives_test__()
{
    if (sizeof(u32int) != 32/8)
	return 1;

    if (sizeof(u16int) != 16/8)
	return 2;

    if (sizeof(u8int) != 8/8)
	return 3;

    return 0;
}
