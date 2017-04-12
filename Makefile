all: 
	flex -o lex.yy.cpp com.l
	bison com.ypp -d
	g++ -std=gnu++14 com.tab.cpp lex.yy.cpp -lfl -o cc

clean:
	rm lex.* cc com.tab.*
