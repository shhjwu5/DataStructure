#include <iostream>

using namespace std;

template<class T>
class Queue{
private:
	struct node{
		T theData;
		node* next;
		
		node(const T &item, node* N = NULL):theData(item), next(N){};
		node():next(NULL){};
		~node(){};
	};
	node* front;
	node* rear;
public:
	Queue();
	~Queue();
	bool isEmpty() const;
	void enQueue(const T &x);
	T deQueue();
};

template<class T>
Queue<T>::Queue()
{
	front = NULL;
	rear = NULL;
}

template<class T>
Queue<T>::~Queue()
{
	node* tmp;
	while(front!=NULL){
		tmp = front;
		front = front->next;
		delete tmp;
	}
}

template<class T>
bool Queue<T>::isEmpty() const
{
	return front==NULL;
}

template<class T>
void Queue<T>::enQueue(const T &x)
{
	if(rear==NULL){
		rear = new node(x);
		front = rear;
	}else{
		rear->next = new node(x);
		rear = rear->next;
	}
}

template<class T>
T Queue<T>::deQueue()
{
	node* tmp = front;
	T value = front->theData;
	front = front->next;
	if(front==NULL){
		rear = NULL;
	}
	delete tmp;
	return value;
}

template<class T>
class Tree{
private:
	struct treeNode{
		treeNode* left;
		treeNode* brother;
		treeNode* father;
		treeNode* leftBro;
		T theData;
		
		treeNode():left(NULL), brother(NULL), father(NULL), leftBro(NULL){};
		treeNode(const T item, treeNode* L = NULL, treeNode* B = NULL, treeNode* F = NULL, treeNode* LB = NULL):theData(item), left(L), brother(B), father(F), leftBro(LB){};
		~treeNode(){};
	};
	treeNode* root;
	int size;
public:
	Tree():root(NULL){};
	Tree(T x){root = new treeNode(x);};
	~Tree();
	void clear();
	bool isEmpty() const;
	void preOrder() const;
	void postOrder() const;
	void levelOrder() const;
	void createTree();
	T parent(T x, T flag) const {return flag;};
private:
	treeNode* find(T x, treeNode* t) const;
	void clear(treeNode* &t);
	void preOrder(treeNode* t) const;
	void postOrder(treeNode* t) const;
};

template<class T>
bool Tree<T>::isEmpty() const
{
	return root==NULL;
}

template<class T>
void Tree<T>::clear(Tree<T>::treeNode* &t)
{
	if(t==NULL){
		return;
	}
	clear(t->left);
	clear(t->brother);
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
	preOrder(t->brother);
}

template<class T>
void Tree<T>::preOrder() const
{
	preOrder(root);
	cout<<'\n';
}

template<class T>
void Tree<T>::postOrder(Tree<T>::treeNode* t) const
{
	if(t==NULL){
		return;
	}
	postOrder(t->left);
	cout<<t->theData<<' ';
	postOrder(t->brother);
}

template<class T>
void Tree<T>::postOrder() const
{
	postOrder(root); 
	cout<<'\n';
}

template<class T>
void Tree<T>::levelOrder() const
{
	Queue<treeNode*> que;
	treeNode* tmp;
	
	que.enQueue(root);
	
	while(!que.isEmpty()){
		tmp = que.deQueue();
		cout<<tmp->theData<<' ';
		if(tmp->left){
			que.enQueue(tmp->left);
			tmp = tmp->left;
			while(tmp->brother){
				que.enQueue(tmp->brother);
				tmp = tmp->brother;
			}
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
		return find(x,t->brother);
	}
}

template<class T>
void Tree<T>::createTree()
{
	const int maxn = 100000+5;
	treeNode* listTree[maxn] = {NULL};
	
	T leftData, brotherData, value;

	cin>>size;
	
	for(int i = 0;i<size;i++){
		listTree[i] = new treeNode;
	}
	
	for(int i = 0;i<size;i++){
		cin>>leftData>>brotherData>>value;
		listTree[i]->theData = value;
		if(leftData>0){
			leftData--;
			listTree[i]->left = listTree[leftData];
			listTree[leftData]->father = listTree[i];
		}
		if(brotherData>0){
			brotherData--;
			listTree[i]->brother = listTree[brotherData];
			listTree[brotherData]->leftBro = listTree[i];
		}
	}
	
	root = listTree[0];
	while(root->father!=NULL or root->leftBro!=NULL){
		if(root->father!=NULL){
			root = root->father;
		}
		if(root->leftBro!=NULL){
			root = root->leftBro;
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Tree<int> tree;
	tree.createTree();
	
	tree.preOrder();
	tree.postOrder();
	tree.levelOrder();
	
	cout<<flush;

	return 0;
}
