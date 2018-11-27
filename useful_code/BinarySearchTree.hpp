#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

using namespace std;

template <class T>
class BinarySearchTree{
private:
	struct binaryNode{
		T myData;
		binaryNode* left;
		binaryNode* right;
		binaryNode(const T &x, binaryNode* lt=NULL, binaryNode* rt=NULL):myData(x),left(lt),right(rt){}
		~binaryNode(){}
	};
	binaryNode* root;
public:
	BinarySearchTree():root(NULL){}
	~BinarySearchTree(){clear(root);}
	void insert(const T &x){insert(root,x);};
	void remove(const T &x){remove(root,x);};
	void remove_less_than(const T &x){remove_less_than(root,x);};
	void remove_greater_than(const T &x){remove_greater_than(root,x);};
	void remove_interval(const T &lt, const T &rt){remove_interval(root,lt,rt);};
	bool find(const T &x){return find(root,x);};
	bool find_ith(const int i, T &x){return find_ith(root,i,x);};
private:
	int size(binaryNode* t) const;
	void insert(binaryNode* &t, const T &x);
	void remove(binaryNode* &t, const T &x);
	void remove_less_than(binaryNode* &t, const T &x);
	void remove_greater_than(binaryNode* &t, const T &x);
	void remove_interval(binaryNode* &t, const T &lt, const T &rt);
	bool find(binaryNode* &t, const T &x);
	bool find_ith(binaryNode* &t, const int i, T &x);
	void clear(binaryNode* &t);
};

template <class T>
void BinarySearchTree<T>::clear(binaryNode* &t)
{
	if(t==NULL){
		return;
	}else{
		clear(t->left);
		clear(t->right);
		delete t;
		t = NULL;
	}
} 

template <class T>
void BinarySearchTree<T>::insert(binaryNode* &t, const T &x)
{
	if(t==NULL){
		t = new binaryNode(x);
	}else if(t->myData>=x){
		insert(t->left,x);
	}else if(t->myData<x){
		insert(t->right,x);
	}
}

template <class T>
void BinarySearchTree<T>::remove(binaryNode* &t, const T &x)
{
	if(t==NULL){
		return;
	}else if(t->myData>x){
		remove(t->left,x);
	}else if(t->myData<x){
		remove(t->right,x);
	}else if(t->left!=NULL and t->right!=NULL){
		binaryNode* tmp = t->right;
		while(tmp->left!=NULL){
			tmp = tmp->left;
		}
		t->myData = tmp->myData;
		remove(t->right,x);
	}else{
		binaryNode* tmp = t;
		t = (t->left==NULL)?t->right:t->left;
		delete tmp;
	}
}

template <class T>
void BinarySearchTree<T>::remove_less_than(binaryNode* &t, const T &x)
{
	if(t==NULL){
		return;
	}else if(t->myData>=x){
		remove_less_than(t->left,x);
	}else{
		binaryNode* tmp = t;
		t = t->right;
		clear(tmp->left);
		delete tmp;
		remove_less_than(t,x);
	}
}

template <class T>
void BinarySearchTree<T>::remove_greater_than(binaryNode* &t, const T &x)
{
	if(t==NULL){
		return;
	}else if(t->myData<=x){
		remove_greater_than(t->right,x);
	}else{
		binaryNode* tmp = t;
		t = t->left;
		clear(tmp->right);
		delete tmp;
		remove_greater_than(t,x);
	}
}

template <class T>
void BinarySearchTree<T>::remove_interval(binaryNode* &t, const T &lt, const T &rt)
{
	if(t==NULL){
		return;
	}else if(t->myData<=lt){
		remove_interval(t->right,lt,rt);
	}else if(t->myData>=rt){
		remove_interval(t->left,lt,rt);
	}else{
		remove(t,t->myData);
		remove_interval(t,lt,rt);
	}
}

template <class T>
bool BinarySearchTree<T>::find(binaryNode* &t, const T &x)
{
	if(t==NULL){
		return false;
	}else if(t->myData==x){
		return true;
	}else if(t->myData>x){
		return find(t->left,x);
	}else{
		return find(t->right,x);
	}
}

template <class T>
int BinarySearchTree<T>::size(binaryNode* t) const
{
	if(t==NULL){
		return 0;
	}else{
		return size(t->left)+size(t->right)+1;
	}
}

template <class T>
bool BinarySearchTree<T>::find_ith(binaryNode* &t, const int i, T &x)
{
	if(t==NULL){
		return false;
	}else if(size(t->left)==i-1){
		x = t->myData;
		return true;
	}else if(size(t->left)>=i){
		return find_ith(t->left,i,x);
	}else{
		return find_ith(t->right,i-size(t->left)-1,x);
	}
}

#endif
