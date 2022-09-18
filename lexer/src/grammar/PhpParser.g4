parser grammar PhpParser;

options {
	tokenVocab = PhpLexer;
}

document: SBL QM PHP elements QM SBR EOF;

elements: statement*;

statement: colonizedElement | ifElse | ifState | codeBlock;

colonizedElement: elementWithColon SEMI;

elementWithColon: echo | print | assigned | expr;

echo: ECHO expr POINT expr | ECHO POINT expr;

print: PRINT expr;

ifElse: ifState elseState;

ifState: IF LP comparison RP codeBlock;

elseState: ELSE codeBlock;

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

var: DOLL ID | VALUE | STRING;

condition: SBL | SBR | SBLE | SBRE | EQ | NE;

//Критерии на тройку: ввод, -вывод-, цикл, -арифметика-, -переменная-, строки

//На четвеёрку: функция, массив