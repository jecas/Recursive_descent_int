The grammar:
E -> E+T
	| E-T
	| T
T -> T*F
	| T/F
	| F
F -> num
	| (E)

The grammar without left recursion:	
E -> TE'
E' -> (+T | -T)E'
	| eps
T -> FT'
T' -> (*F | /F)T'
	| eps
F -> num
	| (E)

First and follow sets:	
	| FIRST     | FOLLOW
E	| num, (    | -|, ) 
E'  | +, -, eps | -|, )
T	| num, ( 	| +, -, -|, )
T' 	| *, /, eps | +, -, -|, )
F 	| num, (    | *, /, +, -, -|, )

The scheme of translation:
E -> T {E'.i = T.v} E' {E.v=E'.v}
E' -> (+T {E'.i=E.i+T.v} | -T {E'.i=E'.i-T.v}) E' {E'.v=E'.v}
	| eps {E'.v=E'.i}
T -> F {T'.i=F.v} T' {T.v=T'.v}
T' -> (*F {T'.i=T'.i*F.v} | /F {T'.i=T'.i/F.v}) T' {T'.v=T'.v}
	| eps {T'.v=T'.i}
F -> num {F.v=num.v}
	| (E) {F.v=E.v}