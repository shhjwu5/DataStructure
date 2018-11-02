#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 100000+5;

struct node{
	int number;
	node* left;
	node* right;
	node* father;
};

class Tree{
private:
	int length = 0;
	node* root = NULL;
	node* myData[maxn] = {NULL};
	node* myTree[maxn] = {NULL};
	void createRoot();
	void createMyTree();
public:
	Tree(int n){
		length = n;
		createRoot();
		createMyTree();
	};
	void output();
};

void Tree::createRoot()
{
	for(int i = 0;i<length;i++){
		myData[i] = new node;
		myData[i]->father = NULL;
		myData[i]->left = NULL;
		myData[i]->right = NULL;
	}
	
	int thisLeft = 0;
	int thisRight = 0;
	int value = 0;
	
	for(int i = 0;i<length;i++){
		cin>>thisLeft>>thisRight>>value;
		myData[i]->number = value;
		if(thisLeft){
			thisLeft-=1;
			myData[i]->left = myData[thisLeft];
			myData[thisLeft]->father = myData[i];
		}
		if(thisRight){
			thisRight-=1;
			myData[i]->right = myData[thisRight];
			myData[thisRight]->father = myData[i];
		}
	}
	
	root = myData[0];
	while(root->father){
		root = root->father;
	}
}

void Tree::createMyTree()
{
	myTree[0] = root;
	node* p;
	
	int cnt = 0;
	int add = 1;
	int total = 1;
	while(total<length){
		if(myTree[cnt]){
			p = myTree[cnt];
			if(p->left){
				myTree[add] = p->left;
				total++;
			}else{
				myTree[add] = NULL;
			}
			add++;
			if(p->right){
				myTree[add] = p->right;
				total++;
			}else{
				myTree[add] = NULL;
			}
			add++;
			cnt++;
		}else{
			myTree[add] = NULL;
			add++;
			myTree[add] = NULL;
			add++;
			cnt++;
		}
	}
}

void Tree::output()
{
	int i = 0;
	int cnt = 0;
	while(cnt<length){
		if(myTree[i]!=NULL){
			cout<<myTree[i]->number<<' ';
			cnt++;
		}
		i++;
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
	theTree.output();	
	
	cout<<flush;

	return 0;
}
