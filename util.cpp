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

struct code_segment{
	string ic, type, jit, jif, start;
};

string start_label = "L1";

string get_label(){
	auto t = start_label;
	for(int i=start_label.size()-1;i>0;--i){
		if(start_label[i] != '9'){
			start_label[i]++;
			break;
		}
	}
	if(t == start_label){
		start_label.push_back('1');
	}
	return t;
}

int ic_var_num = 2; // _to and _t1 are reserved for temp expr evaluation

string get_ic_var_name(){
	return "_t" + to_string(ic_var_num);
}

struct symbol{
	string type;
	int size;
	symbol(string type, int size): type(type), size(size) {};
};

code_segment *create(){
	auto res = new code_segment();
	if(res != NULL)
	return res;
	
	assert(false);
}

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
map<string, string> struct_sub_type;

int global_addr = 0;

int get_addr(string t){

	assert(types.find(t) != types.end());

	auto temp = global_addr;
	global_addr += types[t];
	return temp;	
}

map<string, string > sym_table;

string get_complex_type(string basic_type){
	string f, s;
	bool fl = 0;
	for(auto el: basic_type){
		if(el == '.')
		{
			f = 1;
			continue;
		}
		if(fl)
			s.push_back(el);
		else f.push_back(el);
	}

	if(sym_table.find(f) != sym_table.end()){
		auto parent_type = sym_table[f];
		auto it = struct_sub_type.find(parent_type + "." + s);
		if(it != struct_sub_type.end())
			return it->second;
	}
	return "";
}


string find_type(string s){
	cout<<"Finding type for "<<s<<endl;
	if(isdigit(s[0]))
	{
		if(s.find(".") == string::npos)
			return "int";
		else return "float";
	}
	if(s[0] == '\'')
		return "char";
	if(sym_table.find(s) == sym_table.end()){
		cout<<"No variable named "<<s<<". Type resolution failed!"<<endl;
		exit(0);
	}
	return sym_table[s];
}




void types_init(){
	types["int"] = 4;
	types["char"] = 1;
	types["float"] = 4;
}
