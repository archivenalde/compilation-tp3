#!/bin/sh

yacc -vd while-lang.y
flex -l while-lang.l
gcc lex.yy.c y.tab.c -lm -ll while-lang-mk.c -g
