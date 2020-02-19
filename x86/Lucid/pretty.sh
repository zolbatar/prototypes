#sh

astyle --style=kr --pad=all Kernel/Core/*.c
astyle --style=kr --pad=all Kernel/Core/Include/*.h
astyle --style=kr --pad=all Kernel/Call-Interface/*.h
astyle --style=kr --pad=all Kernel/x86/*.c
astyle --style=kr --pad=all Kernel/x86/Include/*.h
astyle --style=kr --pad=all Library/*.c
astyle --style=kr --pad=all Library/Include/*.h
astyle --style=kr --pad=all API/Include/*.h
astyle --style=kr --pad=all API/*.c
astyle --style=kr --pad=all DDK/*.h

rm Kernel/Core/*.orig
rm Kernel/Core/Include/*.orig
rm Kernel/Call-Interface/*.orig
rm Kernel/x86/*.orig
rm Kernel/x86/Include/*.orig
rm Library/*.orig
rm Library/Include/*.orig
rm API/Include/*.orig
rm API/*.orig
rm DDK/*.orig

