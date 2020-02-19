OUTPUT_FORMAT("elf32-i386")
ENTRY(Start)
SECTIONS
{   .text :
    {   code = .;
        *(.text);
    }
    .rodata :
    {   rodata = .;
         *(.rodata*);
    }
    .data :
    {   data = .;
         *(.data);
    }
    .bss :
    {   bss = .;
        *(.bss)
        *(COMMON);
    }
    _end = .;
}

