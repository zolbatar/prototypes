# Compiler flags etc.
INCLUDE = -I include \
	  -I include/lib \
	  -I ../api/include 
CCFLAGS   = -O3 -mcpu=i486 -march=i486 -fno-builtin -nostdinc -fno-builtin -Wall
AS 	= i386-elf-gcc $(CCFLAGS) $(INCLUDE) -c
CC 	= i386-elf-gcc $(CCFLAGS) $(INCLUDE) -c
LD      = i386-elf-ld -nostdlib -N -T Kernel.ld
OBJDUMP = i386-elf-objdump -D -S -x
STRIP   = i386-elf-strip

# kernel
KERNELOBJS =  src/boot.o \
	      src/kernel-main.o \
      	      src/syslog.o \
      	      src/interrupt.o \
      	      src/mm.o \
      	      src/object.o \
      	      src/timer.o \
      	      src/process.o \
      	      src/ipc.o \
      	      src/module.o \
      	      src/elf.o \
      	      src/syscall.o \
	      src/syscalls.o \
	      src/arch/x86/8259a.o \
	      src/arch/x86/8254.o \
	      src/arch/x86/textmodevideo.o \
	      src/arch/x86/descriptor.o \
	      src/arch/x86/exception.o \
              src/lib/ctype.o \
              src/lib/printf.o \
              src/lib/scanf.o \
              src/lib/strtol.o
KERNEL =      x86-kernel

# Make rules
.S.o:
	$(AS) -o $@ $<

.c.o:
	$(CC) $< -o $@

all:	$(KERNEL)

$(KERNEL): $(KERNELOBJS)
	$(LD) $(KERNELOBJS) -o $(KERNEL)
	$(OBJDUMP) $(KERNEL) > $(KERNEL).dis
	$(STRIP) $(KERNEL)

install: $(KERNEL)
	 gzip -f $(KERNEL)
	 cp $(KERNEL).gz A:/System

clean:
	-rm $(KERNEL)
	-rm $(KERNEL).gz
	-rm $(KERNEL).dis
	-rm $(KERNELOBJS)

