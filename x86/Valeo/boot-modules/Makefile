# Compiler flags etc.
INCLUDE = -I ../api/include -I ../libc/include -I io/include
CCFLAGS = -O3 -mcpu=i486 -march=i486 -fno-builtin -nostdinc -fno-builtin -Wall
AS 	= i386-elf-gcc $(CCFLAGS) $(INCLUDE) -c
CC 	= i386-elf-gcc $(CCFLAGS) $(INCLUDE) -c
LD      = i386-elf-ld -nostdlib -N -T Boot-Module.ld --relocateable
OBJDUMP = i386-elf-objdump -D -S -x
STRIP   = i386-elf-strip

IOOBJ =  io/src/io.o
IO    =  io/src/io

# Make rules
.S.o:
	$(AS) -o $@ $<

.c.o:
	$(CC) $< -o $@

all:	$(IO)

$(IO): $(IOOBJ)
	$(LD) $(IOOBJ) ../libc/libc.a -o $(IO)
	$(OBJDUMP) $(IO) > $(IO).dis

install: $(IO)
	 cp $(IO) A:/System/Modules

clean:
	-rm $(IO)
	-rm $(IOOBJ)
	-rm $(IO).dis
	


