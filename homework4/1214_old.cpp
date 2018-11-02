#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 100000+5;

struct node{
	int number;
	node* left;
	node* twin;
	node* father;
};

class Tree{
private:
	int length = 0;
	node* root = NULL;
	node* myTree[maxn] = {NULL};
public:
	Tree(int);
	node* getRoot() const{
		return root;
	};
	void frontPrint(node*);
	void endPrint(node*);
	void layerPrint();
};

Tree::Tree(int n){
	length = n;
	for (int i = 0;i<length;i++){
		myTree[i] = new node;
		myTree[i]->number = 0;
		myTree[i]->left = NULL;
		myTree[i]->twin = NULL;
		myTree[i]->father = NULL;
	}
	
	int son = 0, brother = 0, value = 0;
	for(int i = 0;i<length;i++){
		cin>>son>>brother>>value;
		if(son){
			son--;
			myTree[i]->left = myTree[son];
			myTree[son]->father = myTree[i];
		}
		if(brother){
			brother--;
			myTree[i]->twin = myTree[brother];
			myTree[brother]->father = myTree[i]->father;
		}
		myTree[i]->number = value;
	}
	
	root = myTree[0];
	while(root->father){
		root = root->father;
	}
}

void Tree::frontPrint(node* p)
{
	node* tmp = p;
	cout<<p->number<<' ';
	if(p->left){
		p = p->left;
		frontPrint(p);
		while(p->twin){
			frontPrint(p->twin);
			p = p->twin;
		}
	}
	if(tmp->number==root->number){
		cout<<'\n';
	}
	return;
}

void Tree::endPrint(node* p)
{
	node* tmp = p;
	if(p->left){
		p = p->left;
		endPrint(p);
		while(p->twin){
			endPrint(p->twin);
			p = p->twin;
		}
	}
	if(tmp->number==root->number){
		cout<<tmp->number<<'\n';
	}else{
		cout<<tmp->number<<' ';
	}
	return;
}

void Tree::layerPrint()
{
	node* layer[maxn] = {NULL};
	int cnt = 0;
	int add = 1;
	layer[0] = root;
	node* tmp = NULL;
	while(layer[cnt]){
		tmp = NULL;
		if(layer[cnt]->left){
			tmp = layer[cnt]->left;
			layer[add++] = tmp;
			while(tmp->twin){
				layer[add++] = tmp->twin;
				tmp = tmp->twin;
			}
		}
		cout<<layer[cnt++]->number<<' ';
	}
	cout<<'\n';
	
	return;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int n =0;
	cin>>n;
	
	Tree thisTree(n);
	node* myRoot = thisTree.getRoot();
	
	thisTree.frontPrint(myRoot);
	thisTree.endPrint(myRoot);
	thisTree.layerPrint();
	
	cout<<flush;
	
	return 0;
}
