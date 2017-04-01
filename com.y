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
%type <str> sym_type;
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
%token STAR;
%token DIVIDE;
%token PLUS;
%token MINUS;
%token STRUCT;
%token <str> TYPE;
%token <str> COMPARATOR;
%token <str> IDENTIFIER;
%token <str> INT_VAL;
%token <str> CONST_STR;
%token <str> REAL_VAL; 

%%

program : line program | function program | line | function 	


function : sym_type IDENTIFIER OP_PARENS param_list CL_PARENS OP_BR lines CL_BR

param_list : param param_list | param

param : sym_type IDENTIFIER 



line : decl COL | expr COL | if_block COL | loop_block COL

if_block : IF OP_BR expr CL_BR OP_PARENS lines CL_PARENS 

loop_block : WHILE OP_BR expr CL_BR OP_PARENS lines CL_PARENS 

lines : line lines | line

decl : sym_type IDENTIFIER_LIST

IDENTIFIER_LIST : IDENTIFIER EQ expr COMMA IDENTIFIER_LIST | IDENTIFIER COMMA IDENTIFIER_LIST  | IDENTIFIER EQ expr | IDENTIFIER { printf("||%s||", $1); } 

place_holder : IDENTIFIER | constant 

expr : place_holder | OP_PARENS expr CL_PARENS | expr PLUS sub_expr | expr MINUS sub_expr | IDENTIFIER EQ expr | expr COMMA expr  

sub_expr : place_holder STAR place_holder | place_holder DIVIDE place_holder | expr 

constant : REAL_VAL | INT_VAL | CONST_STR 

sym_type : TYPE STAR{
	strcpy($$, $1);
	strcat("p_", $$);
} | TYPE {
	strcpy($$, $1);
}| STRUCT IDENTIFIER {
	strcpy($$, $2);
	strcat("struct_", $$);  
}| STRUCT IDENTIFIER STAR {
	strcpy($$, $2);
	strcat("struct_", $$);
	strcat("p_", $$);
}




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
