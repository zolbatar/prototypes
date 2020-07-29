#!/bin/sh
clear
bison -dv bbcbasic.y
flex -l bbcbasic.l
gcc \
    -g \
    -Wall \
    *.c \
    -lfl \
    -o test
./test < ../BBCBASIC/MANBASIC