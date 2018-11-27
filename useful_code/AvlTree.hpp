#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>

using namespace std;

template <class T>
class AvlTree{
private:
	struct avlNode{
		T theData;
		avlNode* left;
		avlNode* right;
		int height;
		
		avlNode(const T &element, avlNode* lt, avlNode* rt, int h=1):theData(element),left(lt),right(rt),height(h){};
	};
	
	avlNode* root;
public:
	AvlTree(){root=NULL;}
	~AvlTree(){makeEmpty(root);};
	void insert(const T &x);
	void remove(const T &x);
private:
	avlNode* find(const T &x) const;
	void insert(const T &x, avlNode* &t);
	bool remove(const T &x, avlNode* &t);
	void makeEmpty(avlNode* &t);
	int height(avlNode* t) const {return t==NULL?0:t->height;};
	void LL(avlNode* &t);
	void LR(avlNode* &t);
	void RL(avlNode* &t);
	void RR(avlNode* &t);
	int max(int a, int b){return a>b?a:b;};
	bool adjust(avlNode* &t, int subTree);
};

template <class T>
avlNode* AvlTree<T>::find(const T &x) const{
	avlNode* t = root;
	while(t!=NULL and t->theData!=x){
		if(t->theData>x){
			t = t->left;
		}else{
			t = t->right;
		}
	}
	
	if(t==NULL){
		return NULL;
	}else{
		return t;
	}
}

template <class T>
void AvlTree<T>::LL(avlNode* &t){
	avlNode* tl = t->left;
	t->left = tl->right;
	tl->right = t;
	t->height = max(height(t->left),height(t->right))+1;
	tl->height = max(height(tl->left),height(t))+1;
	t = tl;
}

template <class T>
void AvlTree<T>::RR(avlNode* &t){
	avlNode* tl = t->right;
	t->right = tl->left;
	tl->left = t;
	t->height = max(height(t->left),height(t->right))+1;
	tl->height = max(height(tl->right),height(t))+1;
	t = tl;
}

template <class T>
void AvlTree<T>::LR(avlNode* &t){
	RR(t->left);
	LL(t);
}

template <class T>
void AvlTree<T>::RL(avlNode* &t){
	LL(t->right);
	RR(t);
}

template <class T>
void AvlTree<T>::insert(const T &x){
	insert(x,root);
}

template <class T>
void AvlTree<T>::insert(const T &x, avlNode* &t){
	if(t==NULL){
		t = new avlNode(x,NULL,NULL);
	}else if(x<t->theData){
		insert(x,t->left);
		if(height(t->left)-height(t->right)==2){
			if(x<t->left->theData){
				LL(t);
			}else{
				LR(t);
			}
		}
	}else if(t->theData<x){
		insert(x,t->right);
		if(height(t->right)-height(t->left)==2){
			if(t->right->theData<x){
				RR(t);
			}else{
				RL(t);
			}
		}
	}
	
	t->height = max(height(t->left),height(t->right))+1;
}

template <class T>
void AvlTree<T>::remove(const T &x){
	remove(x,root);
}

template <class T>
void AvlTree<T>::remove(const T &x,avlNode* &t){
	if(t==NULL){
		return true;
	}
	if(x==t->theData){
		if(t->left==NULL or t->right==NULL){
			avlNode* oldNode = t;
			t = (t->left!=NULL)?t->left:t->right;
			delete oldNode;
			return false;
		}
	}else{
		avlNode* tmp = t->right;
		while(tmp->left!=NULL){
			tmp = tmp->left;
		}
		t->theData = tmp->theData;
		if(remove(tmp->theData,t->right)){
			return true;
		}
		return adjust(t,1);
	}
	
	if(x<t->theData){
		if(remove(x,t->left)){
			return true;
		}
		return adjust(t,0);
	}else{
		if(remove(x,t->right)){
			return true;	
		}
		return adjust(t,1);
	}
}

template <class T>
bool AvlTree<T>::adjust(avlNode* &t, int subTree){
	if(subTree){
		if(height(t->left)-height(t->right)==1){
			return true;
		}
		if(height(t->right)==height(t->left)){
			--t->height;
			return false;
		}
		if(height(t->left->right)>height(t->left->left)){
			LR(t);
			return false;
		}
		LL(t);
		if(height(t->right)==height(t->left)){
			return false;
		}else{
			return true;
		}
	}else{
		if(height(t->right)-height(t->left)==1){
			return true;
		}
		if(height(t->right)==height(t->left)){
			--t->height;
			return false;
		}
		if(height(t->right->left)>height(t->right->right)){
			RL(t);
			return false;
		}
		RR(t);
		if(height(t->right)==height(t->left)){
			return false;
		}else{
			return true;
		}
	}
}

template <class T>
void AvlTree<T>::makeEmpty(avlNode* &t){
	if(t==NULL){
		return;	
	} 
	makeEmpty(t->left);
	makeEmpty(t->right);
	delete t;
} 

#endif 
