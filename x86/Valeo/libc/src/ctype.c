#include <ctype.h>

int isalnum ( int ch ) {
    return ( unsigned int ) ( ( ch | 0x20 ) - 'a' ) < 26u ||
           ( unsigned int ) ( ch - '0' ) < 10u;
}

int isalpha ( int ch ) {
    return ( unsigned int ) ( ( ch | 0x20 ) - 'a' ) < 26u;
}

int isascii ( int ch ) {
    return ( unsigned int ) ch < 128u;
}

int isblank ( int ch ) {
    return ch == ' ' || ch == '\t';
}

int iscntrl ( int ch ) {
    return ( unsigned int ) ch < 32u || ch == 127;
}

int isdigit ( int ch ) {
    return ( unsigned int ) ( ch - '0' ) < 10u;
}

int isgraph ( int ch ) {
    return ( unsigned int ) ( ch - '!' ) < 127u - '!';
}

int islower ( int ch ) {
    return ( unsigned int ) ( ch - 'a' ) < 26u;
}

int isprint ( int ch ) {
    return ( unsigned int ) ( ch - ' ' ) < 127u - ' ';
}

int ispunct ( int ch ) {
    return isprint ( ch ) && !isalnum ( ch ) && !isspace ( ch );
}

int isspace ( int ch ) {
    return ( unsigned int ) ( ch - 9 ) < 5u || ch == ' ';
}

int isupper ( int ch ) {
    return ( unsigned int ) ( ch - 'A' ) < 26u;
}

int isxdigit ( int ch ) {
    return ( unsigned int ) ( ch - '0' ) < 10u ||
           ( unsigned int ) ( ( ch | 0x20 ) - 'a' ) < 6u;
}
