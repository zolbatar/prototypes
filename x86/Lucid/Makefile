# Compiler flags etc.
INCLUDE = -I Kernel/Core/Include -I Kernel/x86/Include \
          -I API/Include -I Library/Include -I Kernel/Call-Interface \
          -I DDK
CCFLAGS = -O3 -mcpu=i686 -march=i586 -fno-builtin -nostdinc -finline-functions -Wall
AS 	= i686-elf-gcc $(INCLUDE) $(CCFLAGS) -c
AR 	= i686-elf-ar r
CC 	= i686-elf-gcc $(INCLUDE) $(CCFLAGS) -c
LD	= i686-elf-ld -nostdlib -N -T Elf.ld
OBJDUMP = i686-elf-objdump -D -S -x

# Kernel
OBJS	= Kernel/Core/Boot.o \
	  Kernel/Core/DeviceManager.o \
	  Kernel/Core/DMMFileIO.o \
	  Kernel/Core/FS.o \
	  Kernel/Core/Kernel.o \
	  Kernel/Core/InterruptManager.o \
	  Kernel/Core/IOManager.o \
	  Kernel/Core/ObjectManager.o \
          Kernel/Core/ProcessManager.o \
	  Kernel/Core/MemoryManager.o \
	  Kernel/Core/MessageManager.o \
	  Kernel/Core/ModuleManager.o \
	  Kernel/Core/TimerManager.o \
	  Kernel/x86/8259a.o \
	  Kernel/x86/8254.o \
	  Kernel/x86/Console.o \
	  Kernel/x86/Descriptor.o \
	  Kernel/x86/Exception.o
KERNEL	= Kernel/x86-Kernel

#Library
LIBRARY = Library/CType.o Library/Printf.o Library/Scanf.o Library/Strtol.o
LIBRARYLIB = Library/Library.lib

#User-Library
USERLIBRARY = API/KConsole.o \
	      API/KDevice.o \
	      API/KInterrupt.o \
	      API/KIO.o \
	      API/KMessage.o \
	      API/KObject.o \
	      API/KProcess.o
USERLIBRARYLIB = API/Library.lib

# Make rules
.S.o:
	$(AS) -o $@ $<

.c.o:
	$(CC) $< -o $@

all:	$(KERNEL)

$(LIBRARYLIB): $(LIBRARY)
	$(AR) $(LIBRARYLIB) $(LIBRARY)

$(USERLIBRARYLIB): $(USERLIBRARY)
	$(AR) $(USERLIBRARYLIB) $(USERLIBRARY)

$(KERNEL): $(LIBRARYLIB) $(USERLIBRARYLIB) $(OBJS)
	$(LD) $(OBJS) $(LIBRARYLIB) $(USERLIBRARYLIB) -o $(KERNEL)
	$(OBJDUMP) $(KERNEL) > Kernel/Kernel.dis
	strip $(KERNEL)

install: $(KERNEL)
	 gzip -f $(KERNEL)
	 cp $(KERNEL).gz A:/System

clean:
	-rm $(KERNEL)
	-rm $(KERNEL).gz
	-rm $(OBJS)
	-rm $(LIBRARY)
	-rm $(LIBRARYLIB)
	-rm $(USERLIBRARY)
	-rm $(USERLIBRARYLIB)

