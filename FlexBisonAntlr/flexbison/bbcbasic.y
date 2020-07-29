%{
#include <stdio.h>

int yylex();
int yyerror(char *s);
extern int num_lines, num_chars;

%}

%token STRING NUM OTHER SEMICOLON

%type <name> STRING
%type <number> NUM

%union{
	char name[20];
    int number;
}

%%

prog: stmts ;
stmts:	| stmt SEMICOLON stmts

stmt:
		STRING {
				printf("Your entered a string - %s", $1);
		}
		| NUM {
				printf("The number you entered is - %d", $1);
		}
		| OTHER
;

%%

int yyerror(char *s)
{
	printf("Syntax Error on line %s\n", s);
	return 0;
}

int main()
{
    printf("PiTubeDirect BASIC 0.01 - Daryl Dudey\n");
    yyparse();
    printf("# of lines = %d, # of chars = %d\n", num_lines, num_chars);
    return 0;
}