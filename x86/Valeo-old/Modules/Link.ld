OUTPUT_FORMAT("elf32-i386")
ENTRY("_start")
SECTIONS
{
    .text :
    {
        code = .;
        *(.text)
        . = ALIGN(4096);
    }

    .rodata :
    {   rodata = .;
         *(.rodata*);
        . = ALIGN(4);
    }

    .data :
    {
        _CTOR_LIST_ = .; LONG((_CTOR_END_ - _CTOR_LIST_) / 4 - 2) *(.ctors) LONG(0) _CTOR_END_ = .;
        _DTOR_LIST_ = .; LONG((_DTOR_END_ - _DTOR_LIST_) / 4 - 2) *(.dtors) LONG(0) _DTOR_END_ = .;

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

