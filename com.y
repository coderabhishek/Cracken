%{
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#define YYDEBUG 1
extern char *yytext;
void yyerror(char *s);
typedef struct {
	char name[50], type[50];
	int addr;
} symbol;

symbol *create(char *s, char *t, int addr){
	symbol *nd = (symbol *)malloc(sizeof(symbol));
	strcpy(nd->name, s);
	strcpy(nd->type, t);
	nd->addr = addr;
	return nd;
}

%}

%union {struct symbol *sym; char str[50];}
%start program;
%token COL;
%token <str> TYPE;
%token OP_PARENS;
%token CL_PARENS;
%token OP_BR;
%token CL_BR;
%token OP_SQBR;
%token CL_SQBR;
%token IF;
%token ELSE;
%token ELSEIF;
%token WHILE;
%token EQ;
%token COMMA;
%token MULTIPLY;
%token DIVIDE;
%token PLUS;
%token MINUS;
%token <str> COMPARATOR;
%token <str> IDENTIFIER;
%token <str> INT_VAL;
%token <str> CONST_STR;
%token <str> REAL_VAL; 

%%

program : line program | function program | line | function 	


function : TYPE IDENTIFIER OP_PARENS CL_PARENS COL



line : decl COL | expr COL | if_block COL | loop_block COL

if_block : IF OP_BR expr CL_BR OP_PARENS lines CL_PARENS 

loop_block : WHILE OP_BR expr CL_BR OP_PARENS lines CL_PARENS 

lines : line lines | line

decl : TYPE IDENTIFIER_LIST

IDENTIFIER_LIST : IDENTIFIER EQ expr COMMA IDENTIFIER_LIST | IDENTIFIER COMMA IDENTIFIER_LIST  | IDENTIFIER EQ expr | IDENTIFIER { printf("||%s||", $1); } 

place_holder : IDENTIFIER | constant 

expr : place_holder | OP_PARENS expr CL_PARENS | expr PLUS sub_expr | expr MINUS sub_expr | IDENTIFIER EQ expr | expr COMMA expr  

sub_expr : place_holder MULTIPLY place_holder | place_holder DIVIDE place_holder | expr 

constant : REAL_VAL | INT_VAL | CONST_STR 

%%

void yyerror (char *s) {
  printf("SYNTAX ERROR NEAR : '%s'\n", yytext);

}

int main(){
	return yyparse();
}
void yywrap(void) {
	return;
}
