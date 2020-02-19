# Compiler flags etc.
INCLUDE = -I .. -I ../API/LIBC-INCLUDE -I ../Kernel/Library/Include
CCFLAGS = -O3 -mcpu=i686 -march=i586 -Wall \
           -nostdlib -nostdinc -fno-exceptions -fno-rtti -fno-builtin
CC	= i386-elf-g++ $(INCLUDE) $(CCFLAGS) -c
LD	= i386-elf-ld -T Link.ld --relocateable
OBJDUMP = i386-elf-objdump -D -S -x

# Library
APILIB = ../API-Library/API.o

# Modules
KEYBOARDOBJ = Keyboard/Keyboard.o
KEYBOARD = Keyboard/Keyboard
KEYBOARDDIS = Keyboard/Keyboard.dis
KCONSOLEOBJ = KConsole/KConsole.o
KCONSOLE = KConsole/KConsole
KCONSOLEDIS = KConsole/KConsole.dis

LIBRARY = ../Kernel/Library/CType.o \
	  ../Kernel/Library/Printf.o \
	  ../Kernel/Library/Scanf.o \
	  ../Kernel/Library/Strtol.o

# Make rules
.cpp.o:
	$(CC) $< -o $@
	strip -g -x $@

all:	$(KEYBOARD) $(KCONSOLE)

$(KEYBOARD): $(KEYBOARDOBJ)
	$(LD) $(KEYBOARDOBJ) $(APILIB) -o $(KEYBOARD)
	$(OBJDUMP) $(KEYBOARD) > $(KEYBOARDDIS)

$(KCONSOLE): $(KCONSOLEOBJ)
	$(LD) $(KCONSOLEOBJ) $(APILIB) $(LIBRARY) -o $(KCONSOLE)
	$(OBJDUMP) $(KCONSOLE) > $(KCONSOLEDIS)

install: $(KEYBOARD) $(KCONSOLE)
	 cp $(KEYBOARD) A:/System/Modules/Keyboard
	 cp $(KCONSOLE) A:/System/Modules/KConsole

clean:
	-rm $(KEYBOARDOBJ)
	-rm $(KEYBOARDDIS)
	-rm $(KEYBOARD)
	-rm $(KCONSOLEOBJ)
	-rm $(KCONSOLEDIS)
	-rm $(KCONSOLE)

