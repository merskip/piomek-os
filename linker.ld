ENTRY("start")

SECTIONS {

    /* Start layout of output file from 1 MiB /*
    . = 1M; /* */

    .multiboot_header : {
    }

    .text : {
        *(.text)
    }

    /* The GNU notes information must be after multiboot header, because Grub may not found header */
    .note.gnu.build-id : {
        *(.note.gnu.build-id)
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
