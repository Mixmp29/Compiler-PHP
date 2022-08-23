grammar Php;

document: SBL QM PHP elements QM SBR EOF;

elements: statement*;

statement: assigned SEMI;

assigned: DOLL ID ASSIGN expression;

expression: VALUE;

PHP: 'php';
BREAK: 'break';
FOR: 'for';
ARRAY: 'array';
FOREACH: 'foreach';
AS: 'as';
IF: 'if';
ELSE: 'else';
ENDIF: 'endif';
ECHO: 'echo';
AND: '&&';
OR: '||';
INC: '++';
SBL: '<';
SBR: '>';
QM: '?';
DOLL: '$';
MOD: '%';
LINK: '&';
ID: [a-zA-Z] [a-zA-Z0-9]*;
VALUE: '0' | [1-9][0-9]*;
STRING: '"' ~ ["\n\r]* '"';
ASSIGN: '=';
EQ: '==';
SEMI: ';';
COLON: ':';
COMMA: ',';
POINT: '.';
PLUS: '+';
MINUS: '-';
MUL: '*';
DEF: '/';
LP: '(';
RP: ')';
LB: '{';
RB: '}';
WS: [ \t\r\n]+ -> skip;
ERRC: .;