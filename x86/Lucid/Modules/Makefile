# Compiler flags etc.
INCLUDE = -I ../Library/Include -I ../API/Include -I ../DDK
CCFLAGS = -O3 -mcpu=i686 -march=i586 -fno-builtin -nostdinc -finline-functions -Wall
AS 	= i686-elf-gcc $(INCLUDE) $(CCFLAGS) -c
CC	= i686-elf-gcc $(INCLUDE) $(CCFLAGS) -fpic -c
LD	= i686-elf-ld -nostdlib -N -T Elf.ld --relocateable
OBJDUMP = i686-elf-objdump -D -S -x

# Library
LIBRARYLIB = ../Library/Library.lib
USERLIBRARYLIB = ../API/Library.lib

# Modules
KEYBOARDOBJ = Keyboard/Keyboard.o
KEYBOARD = Keyboard/Keyboard
KEYBOARDDIS = Keyboard/Keyboard.dis
KCONSOLEOBJ = KConsole/KConsole.o
KCONSOLE = KConsole/KConsole
KCONSOLEDIS = KConsole/KConsole.dis

# Make rules
.S.o:
	$(AS) -o $@ $<

.c.o:
	$(CC) $< -o $@

all:	$(KEYBOARD) $(KCONSOLE)

$(KEYBOARD): $(KEYBOARDOBJ)
	$(LD) $(KEYBOARDOBJ) $(LIBRARYLIB) $(USERLIBRARYLIB) -o $(KEYBOARD)
	$(OBJDUMP) $(KEYBOARD) > $(KEYBOARDDIS)
	strip $(KEYBOARD)

$(KCONSOLE): $(KCONSOLEOBJ)
	$(LD) $(KCONSOLEOBJ) $(LIBRARYLIB) $(USERLIBRARYLIB) -o $(KCONSOLE)
	$(OBJDUMP) $(KCONSOLE) > $(KCONSOLEDIS)
	strip $(KCONSOLE)

install: $(KEYBOARD) $(KCONSOLE)
	 cp Keyboard/Keyboard A:/System/Modules/Keyboard
	 cp KConsole/KConsole A:/System/Modules/KConsole

clean:
	-rm $(KEYBOARDOBJ)
	-rm $(KEYBOARDDIS)
	-rm $(KEYBOARD)
	-rm $(KCONSOLEOBJ)
	-rm $(KCONSOLEDIS)
	-rm $(KCONSOLE)

