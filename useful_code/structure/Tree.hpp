#ifndef TREE_H
#define TREE_H

#include "Queue.hpp" 

using namespace std;

template<class T>
class Tree{
private:
	struct treeNode{
		treeNode* left;
		treeNode* right;
		T theData;
		
		treeNode():left(NULL), right(NULL){};
		treeNode(const T item, treeNode* L = NULL, treeNode* R = NULL):theData(item), left(L), right(R){};
		~treeNode(){};
	};
	treeNode* root;
public:
	Tree():root(NULL){};
	Tree(T x){root = new treeNode(x);};
	~Tree();
	void clear();
	bool isEmpty() const;
	T findRoot(T flag) const;
	T leftChild(T x, T flag) const;
	T rightChild(T x, T flag) const;
	void delLeft(T x);
	void delRight(T x);
	void preOrder() const;
	void midOrder() const;
	void postOrder() const;
	void levelOrder() const;
	void createTree(T flag);
	T parent(T x, T flag) const {return flag;};
private:
	treeNode* find(T x, treeNode* t) const;
	void clear(treeNode* &t);
	void preOrder(treeNode* t) const;
	void midOrder(treeNode* t) const;
	void postOrder(treeNode* t) const;
};

template<class T>
bool Tree<T>::isEmpty() const
{
	return root==NULL;
}

template<class T>
T Tree<T>::findRoot(T flag) const
{
	if(root==NULL){
		return flag;
	}else{
		return root->theData;
	}
}

template<class T>
void Tree<T>::clear(Tree<T>::treeNode* &t)
{
	if(t==NULL){
		return;
	}
	clear(t->left);
	clear(t->right);
	delete t;
	t = NULL;
}

template<class T>
void Tree<T>::clear()
{
	clear(root);
}

template<class T>
Tree<T>::~Tree()
{
	clear(root);
}

template<class T>
void Tree<T>::preOrder(Tree<T>::treeNode* t) const
{
	if(t==NULL){
		return;
	}
	cout<<t->theData<<' ';
	preOrder(t->left);
	preOrder(t->right);
}

template<class T>
void Tree<T>::preOrder() const
{
	cout<<"preOrder: ";
	preOrder(root);
	cout<<'\n';
}

template<class T>
void Tree<T>::midOrder(Tree<T>::treeNode* t) const
{
	if(t==NULL){
		return;
	}
	midOrder(t->left);
	cout<<t->theData<<' ';
	midOrder(t->right);
}

template<class T>
void Tree<T>::midOrder() const
{
	cout<<"midOrder: ";
	midOrder(root);
	cout<<'\n';
}

template<class T>
void Tree<T>::postOrder(Tree<T>::treeNode* t) const
{
	if(t==NULL){
		return;
	}
	postOrder(t->left);
	postOrder(t->right);
	cout<<t->theData<<' ';
}

template<class T>
void Tree<T>::postOrder() const
{
	cout<<"postOrder: ";
	postOrder(root); 
	cout<<'\n';
}

template<class T>
void Tree<T>::levelOrder() const
{
	Queue<treeNode*> que;
	treeNode* tmp;
	
	cout<<"levelOrder: ";
	que.enQueue(root);
	
	while(!que.isEmpty()){
		tmp = que.deQueue();
		cout<<tmp->theData<<' ';
		if(tmp->left){
			que.enQueue(tmp->left);
		}
		if(tmp->right){
			que.enQueue(tmp->right);
		}
	}
}

template<class T>
typename Tree<T>::treeNode* Tree<T>::find(T x, Tree<T>::treeNode* t) const
{
	treeNode* tmp;
	if(t==NULL){
		return NULL;
	}
	if(t->theData==x){
		return t;
	}
	if(tmp=find(x,t->left)){
		return tmp;
	}else{
		return find(x,t->right);
	}
}

template<class T>
void Tree<T>::delLeft(T x)
{
	treeNode* tmp = find(x,root);
	if(tmp==NULL){
		return;
	}
	clear(tmp->left);
}

template<class T>
void Tree<T>::delRight(T x){
	treeNode* tmp = find(x,root);
	if(tmp==NULL){
		return;
	}
	clear(tmp->right);
}

template<class T>
T Tree<T>::leftChild(T x, T flag) const
{
	treeNode* tmp = find(x, root);
	if(tmp==NULL or tmp->left==NULL){
		return flag;
	}
	return tmp->left->data;
}

template<class T>
T Tree<T>::rightChild(T x, T flag) const
{
	treeNode* tmp = find(x, root);
	if(tmp==NULL or tmp->right==NULL){
		return flag;
	}
	return tmp->right->data;
}

template<class T>
void Tree<T>::createTree(T flag)
{
	Queue<treeNode*> que;
	treeNode* tmp;
	T x, leftData, rightData;
	
	cout<<"input root: ";
	cin>>x;
	root = new treeNode(x);
	que.enQueue(root);
	
	while(!que.isEmpty()){
		tmp = que.deQueue();
		cout<<"input "<<tmp->theData<<"'s sons ("<<flag<<"indicate empty treeNode): ";
		cin>>leftData>>rightData;
		if(leftData!=flag){
			que.enQueue(tmp->left = new treeNode(leftData));
		}
		if(rightData!=flag){
			que.enQueue(tmp->right = new treeNode(rightData)); 
		}
	}
	
	cout<<"create complete.\n";
}

#endif
