parser grammar PhpParser;

options {
	tokenVocab = PhpLexer;
}

document: SBL QM PHP elements QM SBR EOF;

elements: statement*;

statement:
	colonizedElement
	| ifElse
	| ifState
	| whileState
	| codeBlock;

colonizedElement: elementWithColon SEMI;

elementWithColon: echo | print | assigned | expr;

echo: ECHO expr POINT expr | ECHO POINT expr;

print: PRINT expr;

input: FGETS LP STDIN RP;

ifElse: ifState elseState;

ifState: IF LP comparison RP codeBlock;

elseState: ELSE codeBlock;

whileState: WHILE LP comparison RP codeBlock;

assigned: var ASSIGN expr;

codeBlock: LB elements RB;

expr:
	left = expr op = (MUL | DEF | MOD) right = expr	# opExpr
	| left = expr op = (PLUS | MINUS) right = expr	# opExpr
	| left = expr op = (POINT | REP) right = expr	# strExpr
	| var op = (INC | DEC)							# uPostExpr
	| op = (INC | DEC) var							# uPrefExpr
	| LP expr RP									# parenExpr
	| var											# atomExpr;

comparison: left = expr condition right = expr;

var: id | value | string | input;

condition: SBL | SBR | SBLE | SBRE | EQ | NE;

id: DOLL ID;

value: VALUE;

string: STRING;