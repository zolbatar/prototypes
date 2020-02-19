# Compiler flags etc.
INCLUDE = -I Core/Include -I x86/Include -I Library/Include -I ../
CCFLAGS = -O3 -mcpu=i686 -march=i586 -fno-builtin -nostdinc -Wall
AS 	= i386-elf-gcc $(INCLUDE) $(CCFLAGS) -c
CC 	= i386-elf-gcc $(INCLUDE) $(CCFLAGS) -c
LD	= i386-elf-ld -nostdlib -N -T Kernel.ld
OBJDUMP = i386-elf-objdump -D -S -x
STRIP   = i386-elf-strip

# Kernel
OBJS	= Core/Boot.o \
	  Core/Kernel.o \
	  Core/DeviceManager.o \
	  Core/DMMFileIO.o \
	  Core/Elf.o \
	  Core/FileSystem.o \
	  Core/InterruptManager.o \
	  Core/IOManager.o \
	  Core/Locking.o \
	  Core/MemoryManager.o \
	  Core/MessageManager.o \
	  Core/ModuleManager.o \
	  Core/ObjectManager.o \
	  Core/TimerManager.o \
	  Core/ProcessManager.o \
	  x86/8259a.o \
	  x86/8254.o \
	  x86/Console.o \
	  x86/Descriptor.o \
	  x86/Exception.o \
          Library/CType.o \
          Library/Printf.o \
          Library/Scanf.o \
          Library/Strtol.o \
          Library/String.o
KERNEL	= x86-Kernel

# Make rules
.S.o:
	$(AS) -o $@ $<

.c.o:
	$(CC) $< -o $@

all:	$(KERNEL)

$(KERNEL): $(OBJS)
	$(LD) $(OBJS) -o $(KERNEL)
	$(OBJDUMP) $(KERNEL) > Kernel.dis
	$(STRIP) $(KERNEL)

install: $(KERNEL)
	 gzip -f $(KERNEL)
	 cp $(KERNEL).gz A:/System

clean:
	-rm $(KERNEL)
	-rm $(KERNEL).gz
	-rm $(OBJS)

