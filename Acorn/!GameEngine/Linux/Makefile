headers		= -Isrc/include
gccflags   	= -c -O2 -Wall -std=gnu99 $(headers)
linkflags  	= 
TARGET   = engine
SRCDIR = src
OBJDIR = obj
BINDIR   = bin
SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

# Libraries
libraries	= -lm -lncurses

# Final target

$(BINDIR)/$(TARGET): $(OBJECTS)
	gcc $(linkflags) -o $@ $(OBJECTS) $(libraries)

# Macro for building c files
#.c.o:;		gcc $(gccflags) $< -o $@

# Clean
#clean:#
#		@$(rm) $(OBJECTS)


#$(BINDIR)/$(TARGET): $(OBJECTS)
#    @$(LINKER) $(OBJECTS) $(LFLAGS) -o $@
#    @echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c  
	gcc $(gccflags) $< -o $@
#    @echo "Compiled "$<" successfully!"

.PHONY: clean
clean:
#    $(rm) $(OBJECTS)
#    @echo "Cleanup complete!"

.PHONY: remove
remove: clean
#    $(rm) $(BINDIR)/$(TARGET)
#    @echo "Executable removed!"		