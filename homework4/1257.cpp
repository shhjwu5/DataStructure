#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 100000+5;

struct node{
	int number;
	int which;
	node* left;
	node* right;
	node* father;
};

class Tree{
private:
	int length = 0;
	node* root = NULL;
	int inTree[maxn] = {0};
	node* myData[maxn] = {NULL};
	void addNode();
	void swapNode();
	void findNode();
public:
	Tree(int n){
		int ope = 0;
		root = new node;
		root->number = 1;
		root->left = NULL;
		root->right = NULL;
		root->father = NULL;
		
		inTree[0] = 1;
		myData[0] = root;
		
		for(int i = 0;i<n;i++){
			cin>>ope;
			if(ope==1){
				addNode();
			}else if(ope==2){
				findNode();
			}else if(ope==3){
				swapNode();
			}
		}
	};
	void output(node*, int);
	node* getRoot(){
		return root;
	}
};

void Tree::addNode()
{
	int thisNumber = 0;
	int leftNumber = 0;
	int rightNumber = 0;
	cin>>thisNumber>>leftNumber>>rightNumber;
	thisNumber-=1;
	leftNumber-=1;
	rightNumber-=1;
	if(inTree[thisNumber] == 1 and myData[thisNumber]->left==NULL and myData[thisNumber]->right==NULL 
		and inTree[leftNumber]!=1 and inTree[rightNumber]!=1 and leftNumber!=rightNumber){
		myData[thisNumber]->number = thisNumber;
		
		myData[leftNumber] = new node;
		myData[leftNumber]->number = leftNumber;
		myData[leftNumber]->which = 1;
		myData[leftNumber]->left = NULL;
		myData[leftNumber]->right = NULL;
		myData[leftNumber]->father = NULL;
		inTree[leftNumber] = 1;
		
		myData[rightNumber] = new node;
		myData[rightNumber]->number = rightNumber;
		myData[rightNumber]->which = 2;
		myData[rightNumber]->left = NULL;
		myData[rightNumber]->right = NULL;
		myData[rightNumber]->father = NULL;
		inTree[rightNumber] = 1;
		
		myData[thisNumber]->left = myData[leftNumber];
		myData[leftNumber]->father = myData[thisNumber];
		myData[thisNumber]->right = myData[rightNumber];
		myData[rightNumber]->father = myData[thisNumber];
		cout<<"Ok!"<<endl;
	}else{
		cout<<"Error!"<<endl; 
	}
}

void Tree::findNode()
{
	int nodeNumber = 0;
	cin>>nodeNumber;
	nodeNumber-=1;
	
	if(inTree[nodeNumber]==1){
		if(myData[nodeNumber]->father){
			cout<<myData[nodeNumber]->father->number+1<<' ';
		}else{
			cout<<0<<' ';
		}
		if(myData[nodeNumber]->left){
			cout<<myData[nodeNumber]->left->number+1<<' ';
		}else{
			cout<<0<<' ';
		}
		if(myData[nodeNumber]->right){
			cout<<myData[nodeNumber]->right->number+1<<' ';
		}else{
			cout<<0<<' ';
		}
		cout<<endl;
	}else{
		cout<<"Error!"<<endl;
	}
}

void Tree::swapNode()
{
	int thisNode = 0;
	cin>>thisNode;
	thisNode-=1;
	
	if(inTree[thisNode]==1){
		if(myData[thisNode]->which==1){
			if(myData[thisNode]->father->right){
				cout<<myData[thisNode]->father->right->number<<endl;
			}else{
				cout<<0<<endl;
			}
			myData[thisNode]->father->left = myData[thisNode]->father->right;
			myData[thisNode]->father->right = myData[thisNode];
			myData[thisNode]->father->left->which = 1;
			myData[thisNode]->father->right->which = 2;
		}else if(myData[thisNode]->which==2){
			if(myData[thisNode]->father->left){
				cout<<myData[thisNode]->father->left->number+1<<endl;
			}else{
				cout<<0<<endl;
			}
			myData[thisNode]->father->right = myData[thisNode]->father->left;
			myData[thisNode]->father->left = myData[thisNode];
			myData[thisNode]->father->left->which = 1;
			myData[thisNode]->father->right->which = 2;
		}
	}else{
		cout<<"Error!"<<endl;
	}
}

void Tree::output(node* tmp, int flag)
{
	if(flag == 0){
		cout<<tmp->number+1<<' ';
		if(tmp->left){
			output(tmp->left, 0);
		}else{
			output(tmp->father, tmp->which);
		}
	}else if(flag == 1){
		if(tmp->right){
			output(tmp->right, 0);
		}else{
			output(tmp->father, tmp->which);
		}
	}else if(flag == 2){
		if(tmp->father){
			output(tmp->father, tmp->which);
		}else{
			return;
		}
	}else{
		return;
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n = 0;
	cin>>n;

	Tree theTree(n);
	theTree.output(theTree.getRoot(), 0);	
	
	cout<<flush;

	return 0;
}




