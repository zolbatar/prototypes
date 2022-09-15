#!/bin/sh
clear
export CLASSPATH=".:/Users/daryl/Dev/antlr4/antlr-4.10.1-complete.jar:$CLASSPATH"
alias antlr4='java -jar /Users/daryl/Dev/antlr4/antlr-4.10.1-complete.jar'
alias grun='java org.antlr.v4.gui.TestRig'

antlr4 -Werror -Dlanguage=Cpp -no-listener -visitor -o . Dork.g4
rm *.tokens
rm *.interp