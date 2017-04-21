%{
#include<string.h>
#include "com.tab.hpp"
%}

%option yylineno
%%
"=" { return EQ; }
";"	{ return COL;}
"{" { return OP_PARENS; }
"}" { return CL_PARENS; }
"(" { return OP_BR; }
")" { return CL_BR; }
"[" { return OP_SQBR; }
"]" { return CL_SQBR; }
"^" { return DEREF; }
"+" { return PLUS; }
"-" { return MINUS; }
"*" { return STAR; }
"/" { return DIVIDE; }
":" { return T_COL; }
"," { return COMMA; }
"&" { return AMP; }
"if" { return IF; }
"else" { return ELSE; }
"while" { return WHILE; }
"struct" { return STRUCT; }
"return" { return RETURN; }
">"|"<"|"!="|"=="|">="|"<=" { strcpy(yylval.str, yytext); return COMPARATOR; }


'.' {strcpy(yylval.str, yytext); return CONST_STR; } 

[a-zA-Z]+[a-zA-Z0-9_.]* { strcpy(yylval.str, yytext); return IDENTIFIER; }
[0-9]+	{ strcpy(yylval.str, yytext); return INT_VAL; }
[0-9]+\.[0-9]+ {strcpy(yylval.str, yytext); return REAL_VAL; }

[ \t\n] {;}
