OUTPUT_FORMAT("elf32-i386")
ENTRY(_start)
virt = 0x80000000;
phys = 0x100000;
SECTIONS
{   .text virt : AT(phys)
    {   code = .;
        *(.text);
    }
    .rodata :  AT(phys + (rodata - code))
    {   rodata = .;
         *(.rodata*);
    }
    .data :  AT(phys + (data - code))
    {   data = .;
         *(.data);
    }
    .bss :  AT(phys + (bss - code))
    {   bss = .;
        *(.bss)
        *(COMMON);
    }
    _end = .;
}

