#!/bin/sh
antlr4 -Dlanguage=Cpp BBCBasicV.g
g++ -I /usr/include/antlr4-runtime/ *.cpp