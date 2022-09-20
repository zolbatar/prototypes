grammar Dork;

prog
    : (statement DOT)* EOF
    ;

statement
    : statementAssign
    | statementUnary
    | expr
    ;

statementAssign
    : expr ASSIGN IDENTIFIER
    ;

statementUnary
    : expr IDENTIFIER
    ;

expr
    : expr IDENTIFIER
    | expr BINARY expr
    | literal
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
SEMICOLON       : ';' ;
UNDERSCORE      : '_' ;
DOT             : '.' ;
PLUS            : '+' ;
PERCENT         : '%' ;
MINUS           : '-' ;
ASSIGN          : '->' ;
BINARYPART      : ('+' | '-' | '|' | '/' | '\\' | '*' | '~' | '<' | '>' | '=' | '@' | '%' | '&' | '?' | '!' | ',') ;
BINARY          : BINARYPART BINARYPART? ;

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
