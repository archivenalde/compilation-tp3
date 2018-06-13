exe: lex.yy.c y.tab.c
	gcc -o exe lex.yy.c y.tab.c -lm -ll while-lang-mk.c -g

lex.yy.c: while-lang.l y.tab.h while-lang-types.h
	lex -l while-lang.l

y.tab.c y.tab.h: while-lang.y
	yacc -vd while-lang.y

clean:
	rm y.*
	rm lex.yy.c
	rm exe
	rm -r exe*