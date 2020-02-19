OUTPUT_FORMAT("elf32-i386")
ENTRY("Entry")
SECTIONS
{
    .text :
    {
        code = .;
        *(.text)
        . = ALIGN(4096);
    }

    .rodata :
    {   
        rodata = .;
        *(.rodata*);
        . = ALIGN(4);
    }

    .data :
    {
        data = .;
        *(.data)
        . = ALIGN(4);
    }

    .bss :
    {
        bss = .;
        *(.bss)
        . = ALIGN(4);
    }

    end = .;
}

