grammar BBCBasicV;

// Main high level stuff
prog: line+ EOF;
line: (
		linenumber (
			(amprstmt (COLON amprstmt?)*)
			| (COMMENT | REM)
		)
	);
linenumber: NUMBER;
amperoper: AMPERSAND;
amprstmt: (amperoper? statement) | (COMMENT | REM);
statement: endstmt | ifstmt | returnstmt;
vardecl: var (LPAREN exprlist RPAREN)*;
relop: (GTE)
	| (GT EQ)
	| (EQ GT)
	| LTE
	| (LT EQ)
	| (EQ LT)
	| neq
	| EQ
	| GT
	| LT;
neq: LT GT;
ifstmt: IF expression THEN? (statement | linenumber);
endstmt: END;
returnstmt: RETURN;

// Expressions
number: ('+' | '-')? (NUMBER | FLOAT);
func: STRINGLITERAL | number | (LPAREN expression RPAREN);

// lists
var: varname varsuffix?;
varname: LETTERS (LETTERS | NUMBER)*;
varsuffix: (DOLLAR | PERCENT);
varlist: vardecl (COMMA vardecl)*;
exprlist: expression (COMMA expression)*;
expression:
	func
	| (relationalExpression ((AND | OR) relationalExpression)*);
signExpression: NOT? (PLUS | MINUS)? func;
exponentExpression: signExpression (EXPONENT signExpression)*;
multiplyingExpression:
	exponentExpression ((TIMES | DIV) exponentExpression)*;
addingExpression:
	multiplyingExpression ((PLUS | MINUS) multiplyingExpression)*;
relationalExpression:
	addingExpression ((relop) addingExpression)?;

// Symbols
DOLLAR: '$';
PERCENT: '%';
COLON: ':';
AMPERSAND: '&';

// Tokens  
IF: 'IF' | 'if';
REM: 'REM' | 'rem';
END: 'END' | 'end';
RETURN: 'RETURN' | 'return';
THEN: 'THEN' | 'then';
NOT: 'NOT' | 'not';
AND: 'AND' | 'and';
OR: 'OR' | 'or';
EQ: '=';
GTE: '>=';
LTE: '<=';
GT: '>';
LT: '<';
LPAREN: '(';
RPAREN: ')';
PLUS: '+';
MINUS: '-';
TIMES: '*';
DIV: '/';
COMMA: ',';
EXPONENT: '^';

// Strings, letters, etc.
COMMENT: REM ~ [\r\n]*;
STRINGLITERAL: '"' ~ ["\r\n]* '"';
LETTERS: ('a' .. 'z' | 'A' .. 'Z')+;
NUMBER: ('0' .. '9')+ (('e' | 'E') NUMBER)*;
FLOAT: ('0' .. '9')* '.' ('0' .. '9')+ (
		('e' | 'E') ('0' .. '9')+
	)*;
WS: [ \r\n\t]+ -> channel (HIDDEN);