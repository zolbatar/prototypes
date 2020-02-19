# Compiler flags etc.
INCLUDE = -I include
CCFLAGS = -O3 -mcpu=i486 -march=i486 -fno-builtin -nostdinc -fno-builtin -Wall
CC 	= i386-elf-gcc $(CCFLAGS) $(INCLUDE) -c
AR 	= i386-elf-ar rvs

# Kernel
OBJS	= src/stdlib.o \
	  src/ctype.o \
	  src/printf.o
LIBC	= libc.a

# Make rules
.c.o:
	$(CC) $< -o $@

all:	$(LIBC)

$(LIBC): $(OBJS)
	$(AR) $(LIBC) $(OBJS)

clean:
	-rm $(LIBC)
	-rm $(OBJS)

