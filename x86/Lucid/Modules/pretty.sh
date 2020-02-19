#sh

astyle --style=kr --pad=all Keyboard/*.c
rm Keyboard/*.orig
astyle --style=kr --pad=all Keyboard/*.h
rm Keyboard/*.orig
astyle --style=kr --pad=all KConsole/*.c
rm KConsole/*.orig
astyle --style=kr --pad=all KConsole/*.h
rm KConsole/*.orig

