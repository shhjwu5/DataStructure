#ifndef AVLTREE_H
#define AVLTREE_H 

#include <iostream> 

using namespace std;

template<class Key, class Other>
struct Pair{
	Key key;
	Other other;
	
	Pair(Key ke, Other oth):key(ke),other(oth){}
};

template<class Key, class Other>
class AvlTree{
private:
	struct avlNode{
		Pair<Key, Other> myData;
		avlNode* left;
		avlNode* right;
		int height;
		
		avlNode(const Pair<Key, Other> &element, avlNode* lt, avlNode* rt, int h = 1):myData(element),left(lt),right(rt),height(h){}
	};
	
	avlNode* root;
public:
	AvlTree(){root = NULL;}
	~AvlTree(){makeEmpty(root);}
	Pair<Key, Other>* find(const Key &x) const;
	void insert(const Pair<Key, Other> &x){insert(x,root);};
	void remove(const Key &x){remove(x,root);};
	void printTree(){printTree(root);};
private:
	void insert(const Pair<Key, Other> &x, avlNode* &t);
	bool remove(const Key &x, avlNode* &t);
	void makeEmpty(avlNode* &t);
	void printTree(avlNode* &t);
	int height(avlNode* t) const {return t==NULL?0:t->height;}
	void LL(avlNode* &t);
	void LR(avlNode* &t);
	void RL(avlNode* &t);
	void RR(avlNode* &t);
	int max(int a, int b){return (a>b)?a:b;}
	bool adjust(avlNode* &t, int subTree);
};

template<class Key, class Other>
Pair<Key, Other>* AvlTree<Key, Other>::find(const Key &x) const
{
	avlNode* t = root;
	while(t!=NULL and t->myData.key!=x){
		if(t->myData.key>x){t = t->left;}
		else{t = t->right;}
	}
	if(t==NULL){return NULL;}
	else{return (Pair<Key, Other>*) t;}
}

template<class Key, class Other>
void AvlTree<Key, Other>::LL(avlNode* &t)
{
	avlNode* t1 = t->left;
	t->left = t1->right;
	t1->right = t;
	t->height = max(height(t->left),height(t->right))+1;
	t1->height = max(height(t1->left),height(t))+1;
	t = t1; 
}

template<class Key, class Other>
void AvlTree<Key, Other>::RR(avlNode* &t)
{
	avlNode* t1 = t->right;
	t->right = t1->left;
	t1->left = t;
	t->height = max(height(t->left),height(t->right))+1;
	t1->height = max(height(t1->right),height(t))+1;
	t = t1;
}

template<class Key, class Other>
void AvlTree<Key, Other>::LR(avlNode* &t)
{
	RR(t->left);
	LL(t);
}

template<class Key, class Other>
void AvlTree<Key, Other>::RL(avlNode* &t)
{
	LL(t->right);
	RR(t);
}

template<class Key, class Other>
void AvlTree<Key, Other>::insert(const Pair<Key, Other> &x, avlNode* &t)
{
	if(t==NULL){t = new avlNode(x,NULL,NULL);}
	else if(x.key<t->myData.key){
		insert(x,t->left);
		if(height(t->left)-height(t->right)==2){
			if(x.key<t->left->myData.key){LL(t);}
			else{LR(t);}
		}
	}else if(t->myData.key<x.key){
		insert(x,t->right);
		if(height(t->right)-height(t->left)==2){
			if(t->right->myData.key<x.key){RR(t);}
			else{RL(t);}
		}
	}
	t->height = max(height(t->left),height(t->right))+1;
}

template<class Key, class Other>
bool AvlTree<Key, Other>::remove(const Key &x, avlNode* &t)
{
	if(t==NULL){return true;}
	if(x==t->myData.key){
		if(t->left==NULL or t->right==NULL){
			avlNode* oldNode = t;
			t = (t->left!=NULL)?t->left:t->right;
			delete oldNode;
			return false;
		}else{
			avlNode* tmp = t->right;
			while(tmp->left!=NULL){tmp = tmp->left;}
			t->myData = tmp->myData;
			if(remove(tmp->myData.key,t->right)){return true;}
			return adjust(t,1);
		}
	}
	if(x<t->myData.key){
		if(remove(x,t->left)){return true;}
		return adjust(t,0);
	}else{
		if(remove(x,t->right)){return true;}
		return adjust(t,1);
	}
}

template<class Key, class Other>
bool AvlTree<Key, Other>::adjust(avlNode* &t, int subTree)
{
	if(subTree){
		if(height(t->left)-height(t->right)==1){return true;}
		if(height(t->right)==height(t->left)){--t->height;return false;}
		if(height(t->left->right)>height(t->left->left)){LR(t);return false;}
		LL(t);
		if(height(t->right)==height(t->left)){return false;}
		else{return true;}
	}else{
		if(height(t->right)-height(t->left)==1){return true;}
		if(height(t->right)==height(t->left)){--t->height;return false;}
		if(height(t->right->left)>height(t->right->right)){RL(t);return false;}
		RR(t);
		if(height(t->right)==height(t->left)){return false;}
		else{return true;}
	}
}

template<class Key, class Other>
void AvlTree<Key,Other>::makeEmpty(avlNode* &t)
{
	if(t==NULL){return;}
	makeEmpty(t->left);
	makeEmpty(t->right);
	delete t;
} 

template<class Key,class Other>
void AvlTree<Key,Other>::printTree(avlNode* &t)
{
	if(t==NULL){cout<<"*"<<endl;return;}
	cout<<t->myData.key<<' '<<t->myData.other<<endl;
	printTree(t->left);
	cout<<"#"<<endl;
	printTree(t->right);
}

#endif
