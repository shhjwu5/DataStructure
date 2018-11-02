#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 1000+5;
const int maxin = 26+2;

char front[maxin] = {0};
char middle[maxin] = {0};

struct node{
	char number;
	node* left;
	node* right;
};

struct tree{
	node* root;
};

int n = 0;

node* myTree[maxn];

void update(node* theNode, int startFront, int endFront, int startMid, int endMid)
{
	if (startFront<endFront){
		theNode->number = front[startFront];
		int pos = startMid;
		while(middle[pos]!=front[startFront]){
			pos++;
		}
		
		if(pos > startMid){
			theNode->left = new node;
			update(theNode->left, startFront+1, startFront+pos-startMid, startMid, pos-1);
		}else{
			theNode->left = NULL;
		}
		
		if(endMid > pos){
			theNode->right = new node;
			update(theNode->right, startFront+pos-startMid+1, endFront, pos+1, endMid);
		}else{
			theNode->right = NULL;
		}		
	}else{
		theNode->number = front[startFront];
		theNode->left = NULL;
		theNode->right = NULL;
		return;
	}
}

void output(tree* nodeTree)
{
	myTree[0] = nodeTree->root;
	node* p;
	
	int cnt = 0;
	int add = 1;
	int total = 1;
	while(total<n){
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
	
	total = 0;
	cnt = 0;
	while(total<n){
		if(myTree[cnt]){
			cout<<myTree[cnt]->number<<' ';
			cnt++;
			total++;
		}else{
			cout<<"NULL ";
			cnt++;
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin.getline(front, maxin);
	cin.getline(middle, maxin);
	
	while(front[n]!=0){
		n++;
	}
	
	tree* nodeTree = new tree;
	nodeTree->root = new node;
	
	update(nodeTree->root, 0, n-1, 0, n-1);
	
	output(nodeTree);
	
	return 0;
}
