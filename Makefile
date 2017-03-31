all: 
	lex com.l
	yacc com.y -d
	gcc y.tab.c lex.yy.c -o cc

clean:
	rm y.tab.c y.tab.h lex.yy.c cc
