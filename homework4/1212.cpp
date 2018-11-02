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
bool Queue<T>::isEmpty() const
{
	return front==NULL;
}

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
		treeNode* right;
		treeNode* father;
		T theData;
		
		treeNode():left(NULL), right(NULL), father(NULL){};
		treeNode(const T item, treeNode* L = NULL, treeNode* R = NULL, treeNode* F = NULL):theData(item), left(L), right(R), father(F){};
		~treeNode(){};
	};
	treeNode* root;
	int size;
public:
	Tree():root(NULL), size(0){};
	~Tree();
	void createTree();
	bool isCBT() const;
	void levelOrder() const;
private:
	void clear(treeNode* &t);
};


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
Tree<T>::~Tree()
{
	clear(root);
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
		}
		if(tmp->right){
			que.enQueue(tmp->right);
		}
	}
	
	cout<<'\n';
}

template<class T>
void Tree<T>::createTree()
{
	const int maxn = 100000+5;
	treeNode* listTree[maxn] = {NULL};
	
	T leftData, rightData, value;

	cin>>size;
	
	for(int i = 0;i<size;i++){
		listTree[i] = new treeNode;
	}
	
	for(int i = 0;i<size;i++){
		cin>>leftData>>rightData>>value;
		listTree[i]->theData = value;
		if(leftData>0){
			leftData--;
			listTree[i]->left = listTree[leftData];
			listTree[leftData]->father = listTree[i];
		}
		if(rightData>0){
			rightData--;
			listTree[i]->right = listTree[rightData];
			listTree[rightData]->father = listTree[i];
		}
	}
	
	root = listTree[0];
	while(root->father!=NULL){
		root = root->father;
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	Tree<int> tree;
	tree.createTree();
	tree.levelOrder();
	
	cout<<flush;

	return 0;
}
