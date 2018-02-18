#include "kernel/kernel.h"
#include "kernel/common.h"
#include "kernel/io.h"
#include "drives/video.h"
#include "drives/keyboard.h"
#include "kernel/string.h"
#include "kernel/commands.h"
#include "src/arch/x86/gdt.h"
#include "src/arch/x86/idt.h"

char name_os[] = "PiomekOS";

u32int function_test(u16int args, const char *argv[]) {
    int i = 0;
    printf("TEST with %i args\n", args);

    for (i = 0; i < args; i++) {
        printf("argv[%i] = %s \n", i, argv[i]);
    }

    return 0;
}

u32int function_colors(u16int args, const char *argv[]) {
    color_test();
    return 0;
}

int start_kernel(unsigned int magic) {

    gdt_init_default();
    idt_init_default();
    idt_enable_interrupts();

    video_init();
    video_cls();

    video_set_color(COLOR_BLACK | BG_COLOR_WHITE);
    printf(name_os);

    video_set_color(COLOR_LIGHT_GRAY | BG_COLOR_BLACK);
    printf(", %s %s\n", __DATE__, __TIME__);

    video_set_color(COLOR_BLACK | BG_COLOR_LIGHT_GRAY);
    printf("\tPiotr Merski");
    color_reset();

    printf("\n\n\n");

    printf("Multiboot checksum: ");
    if (magic == 0x36d76289) {
        print_right_color("[ OK ]", COLOR_LIGHT_GREEN | BG_COLOR_BLACK);
    } else {
        print_right_color("[FAIL]", COLOR_RED | BG_COLOR_BLACK);
        goto END_KERNEL;
    }

    printf("Primitives size: ");
    if (__primitives_test__() == 0) {
        print_right_color("[ OK ]", COLOR_LIGHT_GREEN | BG_COLOR_BLACK);
    } else {
        print_right_color("[FAIL]", COLOR_RED | BG_COLOR_BLACK);
        goto END_KERNEL;
    }

    printf("Keyboard test: ");
    if (keyboard_self_test()) {
        print_right_color("[ OK ]", COLOR_LIGHT_GREEN | BG_COLOR_BLACK);
    } else {
        print_right_color("[FAIL]", COLOR_RED | BG_COLOR_BLACK);
        goto END_KERNEL;
    }

    printf("Keyboard set LEDs on (1, 0, 0)\n");
    keyboard_leds.num = true;
    keyboard_leds.caps = false;
    keyboard_leds.scroll = false;
    keyboard_set_leds();

    printf("\nType 'help' to get a list of commands.\n");

    cmd_init();
    cmd_add("test", function_test);
    cmd_add("colors", function_colors);

    run_terminal();

    END_KERNEL:
    __full_sleep_cpu__();

    return 0;
}
