#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "keyboard.h"

void keyboard_init() {
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);
}

void keyboard_end() {
    nocbreak();
    echo();
}

int kbhit(void) {
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

BYTE check_for_key() {
    BYTE code = (BYTE)kbhit();
    if (code) {
        code = getch();
        if (code == '\033') {  // if the first value is esc
            getch();              // skip the [
            switch (getch()) {    // the real value
                case 'A':
                    return _KEY_UP;
                case 'B':
                    return _KEY_DOWN;
                case 'C':
                    return _KEY_RIGHT;
                case 'D':
                    return _KEY_LEFT;
                default:
                    return KEY_ESCAPE;
            }
        }
        return code;
    } else {
        return 0;
    }
}
