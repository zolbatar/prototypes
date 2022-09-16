grammar Dork;

prog
    : (statement DOT)* EOF
    ;

statement
    : statementAssign
    | statementMethodCallUnary
    ;

statementAssign
    : expr ASSIGN IDENTIFIER
    ;

statementMethodCallUnary
    : expr IDENTIFIER
    ;

expr
    : literal
    ;

// Literals
literal
    : integerLiteral
    | floatLiteral
    | stringLiteral
    ;

integerLiteral
    : HEXNUMBER
    | BINARYNUMBER
    | (PLUS | MINUS)? INTEGERLITERAL
    ;

floatLiteral
    : (PLUS | MINUS)? FLOATLITERAL
    ;

stringLiteral
    : STRINGLITERAL
    ;

COMMENT         : TICK ~ [\r\n]* ;

TICK            : '\'' ;
PLING           : '!' ;
HASH            : '#' ;
DOLLAR          : '$' ;
COLON           : ':' ;
COMMA           : ',' ;
PERCENT         : '%' ;
LPAREN          : '(' ;
RPAREN          : ')' ;
SOPEN           : '[' ;
SCLOSE          : ']' ;
SEMICOLON       : ';' ;
UNDERSCORE      : '_' ;
DOT             : '.' ;
COPEN           : '{' ;
CCLOSE          : '}' ;

PLUS            : '+' ;
MINUS           : '-' ;

ASSIGN          : '->' ;

// Literals
STRINGLITERAL   : '"' ~ ["\r\n]* '"' ;
HEXNUMBER       : '&' [0-9A-Fa-f]+ ;
BINARYNUMBER    : PERCENT [0|1]+ ;
INTEGERLITERAL  : DIGIT+ ;
FLOATLITERAL    : DIGIT* '.' DIGIT* ([e|E] [0-9]+ )* ;

IDENTIFIER      : NAME ;

fragment NAME   : ALPHA (ALPHA|DIGIT|UNDERSCORE)* ;
fragment ALPHA  : [a-zA-Z] ;
fragment DIGIT  : [0-9] ;

WS              : [ \r\t] + -> channel (HIDDEN) ;
