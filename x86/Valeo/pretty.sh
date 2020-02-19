#sh

#Src
astyle --style=kr --pad=all kernel/src/*.c
rm kernel/src/*.orig
astyle --style=kr --pad=all kernel/src/arch/x86/*.c
rm kernel/src/arch/x86/*.orig
#astyle --style=kr --pad=all kernel/src/lib/*.c
#rm kernel/src/lib/*.orig

#Includes
astyle --style=kr --pad=all kernel/include/*.h
rm kernel/include/*.orig
astyle --style=kr --pad=all kernel/include/arch/x86/*.h
rm kernel/include/arch/x86/*.orig
#astyle --style=kr --pad=all kernel/include/lib/*.h
#rm kernel/include/lib/*.orig

#Boot-Modules Src
astyle --style=kr --pad=all boot-modules/io/src/*.c
rm boot-modules/io/src/*.orig

#Boot-Modules Includes
astyle --style=kr --pad=all boot-modules/io/include/*.h
rm boot-modules/io/include/*.orig

#API Includes
astyle --style=kr --pad=all api/include/*.h
rm api/include/*.orig
astyle --style=kr --pad=all api/include/arch/x86/*.h
rm api/include/arch/x86/*.orig

#Libc Src
astyle --style=kr --pad=all libc/src/*.c
rm libc/src/*.orig

#Libc Includes
astyle --style=kr --pad=all libc/include/*.h
rm libc/include/*.orig
astyle --style=kr --pad=all libc/include/sys/*.h
rm libc/include/sys/*.orig



