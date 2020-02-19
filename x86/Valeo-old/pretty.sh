#sh

astyle --style=kr --pad=all API/*.h
rm API/*.orig

astyle --style=kr --pad=all API-Library/*.cpp
rm API-Library/*.orig

astyle --style=kr --pad=all Kernel/Core/*.c
rm Kernel/Core/*.orig
astyle --style=kr --pad=all Kernel/Core/Include/*.h
rm Kernel/Core/Include/*.orig
astyle --style=kr --pad=all Kernel/x86/*.c
rm Kernel/x86/*.orig
astyle --style=kr --pad=all Kernel/x86/Include/*.h
rm Kernel/x86/Include/*.orig
astyle --style=kr --pad=all Kernel/Library/*.c
rm Kernel/Library/*.orig
astyle --style=kr --pad=all Kernel/Library/Include/*.h
rm Kernel/Library/Include/*.orig

astyle --style=kr --pad=all Modules/Keyboard/*.cpp
rm Modules/Keyboard/*.orig
astyle --style=kr --pad=all Modules/Keyboard/*.h
rm Modules/Keyboard/*.orig

