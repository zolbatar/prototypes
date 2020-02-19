# Compiler flags etc.
INCLUDE = -I ..
CCFLAGS = -O3 -mcpu=i686 -march=i586 -Wall \
           -nostdlib -nostdinc -fno-exceptions -fno-rtti -fno-builtin
CC 	= i386-elf-gcc $(INCLUDE) $(CCFLAGS) -c
CPP 	= i386-elf-g++ $(INCLUDE) $(CCFLAGS) -c
AR 	= i386-elf-ar r
LD	= i386-elf-ld --relocateable

#User-Library
API = RT-Support.o Console.o ProcessManager.o InterruptManager.o DeviceManager.o \
      MessageManager.o ModuleManager.o
APILIB = API.o

# Make rules
.cpp.o:
	$(CPP) $< -o $@
	strip -g -x $@

all:	$(APILIB)

$(APILIB): $(API)
	$(LD) $(API) -o $(APILIB)
#	$(AR) $(APILIB) $(API)

clean:
	-rm $(API)
	-rm $(APILIB)

