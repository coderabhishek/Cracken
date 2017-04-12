#include<iostream>
#include<assert.h>
#include<set>
#include<map>
#include<string>
#include<string.h>
#include<stdio.h>
#include<stack>
#include<stdlib.h>
#include<memory>

using namespace std;


struct symbol{
	string type;
	int addr;
	symbol(string type, int addr): type(type), addr(addr) {};
};

/* Remenescent of bad days :( 

symbol *create(char *s, char *t, int addr){
	symbol *nd = (symbol *)malloc(sizeof(symbol));
	strcpy(nd->name, s);
	strcpy(nd->type, t);
	nd->addr = addr;
	return nd;
}
*/

stack<string> scope;

map<string, int> types;
int global_addr = 0;

int get_addr(string t){

	assert(types.find(t) != types.end());
	
	auto temp = global_addr;
	global_addr += types[t];
	return temp;	
}

map<string, unique_ptr<symbol> > sym_table;

void types_init(){
	types["int"] = 4;
	types["char"] = 1;
	types["float"] = 4;
}
