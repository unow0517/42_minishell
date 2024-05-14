// Recursive Descendent Parsing
//Precendence, Associativity

//Context Free Grammar
//a formal grammar whose production rules can be applied to a nonterminal symbol regardless of its context. => some kind of rules which can be applied to parse the input string.

//CFG에서 G = (T, N, P, S) 로 정의되는데, 4개의 요소들은 각각

//T: terminal symbol => symbol cannot derive another symbol
//N: nonterminal symbol => symbol can derive another symbol 
//P: production rules (생성 규칙, 단말 기호와 비단말 기호를 이용하여 문자열을 만들어내는 규칙)
//S: start symbol (시작을 의미하는 단 한 개의 비단말 기호)

//BNF -> one of the CFG (Context Free Grammar), below is the form of an BNF
//G’ = ( {+, *, (, ), 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, {E, R, T, Q, F, N}, P’, E )

//P’: E ::= T R
//R ::= + T R | λ
//T ::= F Q
//Q ::= * F Q
//F ::= N | ( E )
//N ::= 0 | 1 | ... | 9

//E is starting 
//R = in this case, E can have following multiple addition or nothing(lambda)
//T = term ( a word ),
//Q = sequence of factors
//N = non-terminal for integers terminal symbol.
//So writing BNF about our shell is the first.

//first we have to know about term, factor
//example: 2 * (3 + 4)
//term : 2 * (3 + 4)
//factor : 2, (3 + 4), 3, 4,
//https://blog.naver.com/seonghun7304/222606595399

//BNF MINISHELL
//G = ( 
//	{a...z, A..Z, 0...9, \, ", ', <, <<, >, >>, |, $, ?, *(bonus)}, 
//	{N, F, T, },
//	P,
//	E
//  )

// P = (
//	N ::= a...z | A...Z | 0...9 | 	
// )



