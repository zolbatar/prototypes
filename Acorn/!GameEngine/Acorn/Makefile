headers		=
gccflags   	= -mlibscl -c -save-temps -O2 -Wall -std=gnu99 -mfpu=vfp -mfloat-abi=softfp $(headers)
linkflags  	= -mlibscl -mfpu=vfp -mfloat-abi=softfp

# C Files
c_files		= main.o engine.o graphics.o palette.o terrain.o perlin.o test.o game.o keyboard.o

# Libraries
libraries	= -lm

# Final target

!RunImage:	$(c_files)
		gcc $(linkflags) -o $@ $(c_files) $(libraries)

# Macro for building c files
.c.o:;		gcc $(gccflags) $< -o $@

# Clean
clean:
		wipe o.* ~C~V