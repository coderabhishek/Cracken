#include<iostream>
#include<assert.h>
#include<vector>
#include<set>
#include<map>
#include<string.h>
#include<stdio.h>
#include<stack>
#include<stdlib.h>
#include<memory>

using namespace std;

void yyerror(string);

int cur_scope = 0;

string ir = "";

map<string, int> addr_table;

struct code_segment{
	string ic, type, jit, jif, start;
};

map<string, string> struct_sub_type;

string start_label = "L1";

bool coercible(string t1, string t2){
	if(t1 == t2)
		return true;
	if((t1 == "float" and t2 == "int") || (t1 == "int" and t2 == "float"))
		return true;
	return false;
}

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

string scoped_name(string s){
	return s + "_" + to_string(cur_scope);
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
int global_addr = 9000;

int get_addr(string t){

	assert(types.find(t) != types.end());

	auto temp = global_addr;
	global_addr += types[t];
	return temp;	
}

class sym_table_cl{

	private:
		map<string, stack< pair<int, string> > > sym_tab;	
		sym_table_cl(){};
	public:
		static sym_table_cl get_singleton(){
			static sym_table_cl sym_table;
			return sym_table;
		}

		bool find(string name){
			return (sym_tab.find(name) != sym_tab.end());
		}

		void set(string name, string type){
			assert(sym_tab[name].empty() or sym_tab[name].top().first >= cur_scope);
			if(!sym_tab[name].empty() and  sym_tab[name].top().first == cur_scope){
				yyerror("Variable already declared!!");	
			}

			sym_tab[name].push(make_pair(cur_scope, type));
			addr_table[scoped_name(name)] = global_addr;
			global_addr += types[type];
			cout<<"Remark: Bound "<<name<<" to "<<addr_table[scoped_name(name)]<<endl;
		}	

		string get(string name){
			if(sym_tab.find(name) != sym_tab.end())
				return sym_tab[name].top().second;
			yyerror("No variable named " + name);
		}

		void clear_scope(){
			for(auto it = sym_tab.begin();it!=sym_tab.end();++it){
				assert(it->second.top().first >= cur_scope);
				if(it->second.top().first == cur_scope){
					(it->second).pop();
				}
			}
		}

};

sym_table_cl sym_table = sym_table_cl::get_singleton(); 



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

	if(!sym_table.find(f)){
		auto parent_type = sym_table.get(f);
		auto it = struct_sub_type.find(parent_type + "." + s);
		if(it != struct_sub_type.end())
			return it->second;
	}
	return "";
}


string find_type(string s){
	if(isdigit(s[0]))
	{
		if(s.find(".") == string::npos)
			return "int";
		else return "float";
	}
	if(s[0] == '\'')
		return "char";
	if(s.find(".") != string::npos){
		string t;
		int i=0;
		for(;i<s.size();++i)
		{
			if(s[i] == '.')
				break;
			t.push_back(s[i]);
		}	
		t = find_type(t);
		i++;
		string temp;
		for(;i<s.size();++i){
			if(s[i]!='.')
				temp.push_back(s[i]);
			else{
				if(struct_sub_type.find(t + "." + temp) == struct_sub_type.end())
					yyerror("Unknown member!!");
				t = struct_sub_type[t + "." + temp];
				temp = "";	
			}
		}
		if(struct_sub_type.find(t + "." + temp) == struct_sub_type.end())
			yyerror("Unknown member!!");
		t = struct_sub_type[t + "." + temp];
		return t;
	}
	if(!sym_table.find(s)){
		cout<<"No variable named "<<s<<". Type resolution failed!"<<endl;
		exit(0);
	}
	return sym_table.get(s);
}

struct func{
	string name;
	vector<string> para_type_list;
	string r_type;
};

struct param_list{
	vector<string> v;
};
vector<func> funcs;

void types_init(){
	types["int"] = 4;
	types["char"] = 1;
	types["float"] = 4;
}

int size_of_param_frame(vector<string> &v){
	auto res = 0;
	for(auto el: v){
		res += types[el];
	}
	return res;
}

string f_name;
vector<string> p_end_iterator;
vector<func> f_end_iterator;
vector<func>::iterator func_itr = f_end_iterator.end();
vector<string>::iterator param_itr = p_end_iterator.end();	
