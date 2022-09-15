parser grammar PhpParser;

options {
	tokenVocab = PhpLexer;
}

document: SBL QM PHP elements QM SBR EOF;

elements: statement*;

statement: colonizedElement;

colonizedElement: elementWithColon SEMI;

elementWithColon: assigned | expr;

assigned: var ASSIGN expr;

expr:
	left = expr op = (MUL | DEF | MOD) right = expr	# opExpr
	| left = expr op = (PLUS | MINUS) right = expr	# opExpr
	| left = expr op = (POINT | REP) right = expr	# strExpr
	| var op = (INC | DEC)							# uPostExpr
	| op = (INC | DEC) var							# uPrefExpr
	| LP expr RP									# parenExpr
	| var											# atomExpr;

var: DOLL ID | VALUE;

//Критерии на тройку ввод, вывод, цикл, арифметика, переменная

//На четвеёрку функция, массив