/* DON'T USE 'OUTPUT_FORMAT("binary")' !! */
ENTRY("__start__") 

SECTIONS {
    . = 0x00100000;

    .text : {
        *(.text)
    }

    .rodata ALIGN (0x1000) : {
        *(.rodata)
    }

    .data ALIGN (0x1000) : {
        *(.data)
    }

    .bss : {
        *(.bss)
    }
}