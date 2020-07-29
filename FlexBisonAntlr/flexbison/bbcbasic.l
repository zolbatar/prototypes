%{
#include "bbcbasic.tab.h"
void showError();
int num_lines = 0, num_chars = 0;
%}

numbers ([0-9])+
alpha ([a-zA-Z])+

%%
\n      { ++num_lines; ++num_chars; };
.       { ++num_chars; };
.       { showError(); return(OTHER); }

%%

void showError() {
    printf("Other input");
}

/*int main() {
    printf("PiTubeDirect BASIC 0.01 - Daryl Dudey\n");
    yylex();
}*/