grammar Php;

document: element;

element: object | array | number | string;

object: SBL QM PHP QM SBR | SBL QM member (SEMI member)* QM SBR;

member: LINK ID EQ element;

array: LP RP | LP element (COMMA element)* RP;

number: VALUE;

string: STRING;

PHP: 'php';
BREAK: 'break';
FOR: 'for';
ARRAY: 'array';
FOREACH: 'foreach';
AS: 'as';
IF: 'if';
ENDIF: 'endif';
ECHO: 'echo';
AND: '&&';
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
EQ: '=';
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