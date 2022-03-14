№ 1. Дана грамматика. Постройте вывод заданной цепочки.
a) цепочка: a - b * a + b
грамматика:

S -> T | T + S | T - S
T -> F | F * T
F -> a | b

__S__ -> __T__ - S -> __F__ - S -> a - __S__ -> a - __T__ + S -> a - __F__ * T + S ->
-> a - b * __T__ + S -> a - b * __F__ + S -> a - b * a + __S__ -> 
-> a - b * a + __T__ -> a - b * a + __F__ -> a - b * a + b

b) цепочка: aaabbbccc
грамматика:

S -> aSBC | abC
CB -> BC
bB -> bb
bC -> bc
cC -> cc

__S__ -> a __S__ BC -> aa __S__ BCBC -> aaab __CB__ CBC -> aaa __bB__ CCBC -> 
-> aaabbC __CB__ C -> aaabb __CB__ CC -> aaab __bB__ CCC -> aaabb __bC__ CC ->
-> aaabbb __cC__ C -> aaabbbc __cC__ -> aaabbbccc

№ 2. Построить грамматику порождающую язык:

a) L = {a^n b^m c^k | n,m,k > 0}

G ({a, b, c}, {S, B, C}, P, S)

P:
S -> aS | aB
B -> bB | bC
C -> cC | c

1) __S__ -> a __B__ -> ab __C__ -> abc
2) __S__ -> a __S__ -> aa __B__ -> aab __B__ -> aabb __B__ -> aabbb __C__ -> aabbbc

b) L = {0^n (10)^m | n,m >= 0}

G ({0, 1}, {S, T}, P, S)

P:
S -> 0S | T
T -> 10T | 10 | _ε_

1) __S__ -> 0 __S__ -> 00 __S__ -> 000 __S__ -> 000 __T__ -> 00010 __T__ -> 0001010 __T__ -> 000101010
2) __S__ -> __T__ -> _ε_

c) L = {a1,a2,...,an,an,...,a2,a1 | ai = {0, 1}}

G ({0, 1}, {S, A}, P, S)

P:
S -> 0A0 | 1A1
A -> 0A0 | 1A1 | _ε_

1) __S__ -> 0 __A__ 0 -> 01 __A__ 10 -> 010 __A__ 010 -> 0101 __A __1010 -> 01011010
2) __S__ -> 0 __A__ 0 -> 00