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