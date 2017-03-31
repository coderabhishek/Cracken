%{
#include<string.h>
#include "y.tab.h"
%}

%%
"=" { return EQ; }
";"	{ return COL;}
"int"|"float"|"char" { return TYPE; }
"{" { return OP_PARENS; }
"}" { return CL_PARENS; }
")" { return OP_BR; }
"(" { return CL_BR; }
"[" { return OP_SQBR; }
"]" { return CL_SQBR; }
"+" { return PLUS; }
"-" { return MINUS; }
"*" { return MULTIPLY; }
"/" { return DIVIDE; }
"," { return COMMA; }
"if" { return IF; }
"else" { return ELSE; }
"elseif" { return ELSEIF; }
"while" { return WHILE; }
">"|"<"|"!="|"=="|">="|"<=" { strcpy(yylval.str, yytext); return COMPARATOR; }


\"[a-zA-Z0-9]*\"  { strcpy(yylval.str, yytext); return CONST_STR; }

[a-zA-Z]+[a-zA-Z0-9_]* { strcpy(yylval.str, yytext); return IDENTIFIER; }
[0-9]+	{ strcpy(yylval.str, yytext); return INT_VAL; }
[0-9]+.[0-9]+ {strcpy(yylval.str, yytext); return REAL_VAL; }

[ \t\n] {;}
