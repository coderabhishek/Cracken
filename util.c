#include<string.h>
#include<stdio.h>
#include<stdlib.h>


typedef struct node{
	struct node* v[125];	//diff b/w ascii of a and A
	int size;
} node;


node *root = NULL;

void insert(char *s, int sz){
	if(root==NULL)
	{
		root = (node *)malloc(sizeof(node));
		root->size = -1;
	}
	node *cur = root;
	int i=0;
	while(s[i]!='\0'){
		if(cur->v[s[i]-'A']!=NULL)
			cur = cur->v[s[i]-'A'];
		else{
			node *nd = (node *)malloc(sizeof(node));
			nd->size = -1;
			cur->v[s[i]-'A'] = nd;
			cur = nd;	
		}
		i++;
	}
	cur->size = sz;

}

int find(char *s){
	if(root == NULL)
	{
		return -1;
	}
	int i=0;
	node *cur = root;
	while(s[i]!='\0'){
		if(cur->v[s[i]-'A'] == NULL)
			return -1;
		else cur = cur->v[s[i]-'A']; 
		i++;			
	}
	return cur->size;
}



