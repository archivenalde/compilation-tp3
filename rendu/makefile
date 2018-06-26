exe: lex.yy.c y.tab.c
	gcc -o exe lex.yy.c y.tab.c -lm -ll liste.c while-lang-mk.c while-lang-pr.c while-lang-table.c while-lang-mem.c while-lang-eval.c -g 2> /dev/null

lex.yy.c: while-lang.l y.tab.h while-lang-types.h
	lex -l while-lang.l 2> /dev/null

y.tab.c y.tab.h: while-lang.y
	yacc -vd while-lang.y 2> /dev/null

clean:
	rm y.*
	rm lex.yy.c
	rm -r exe*
