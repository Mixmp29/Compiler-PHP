parser grammar PhpParser;

options {
	tokenVocab = PhpLexer;
}

document: SBL QM PHP elements QM SBR EOF;

elements: statement*;

statement: colonizedElement;

colonizedElement: elementWithColon SEMI;

elementWithColon: assigned;

assigned: DOLL ID ASSIGN expression;

expression: VALUE;