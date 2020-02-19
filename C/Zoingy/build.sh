#!/bin/sh
rm ./loader
gcc -o loader src/main.c src/loader/getblock.c src/loader/printclass.c src/loader/loader.c -I./include -std=c11
chmod +x loader
./loader res/HelloWorldApp.class