#include <iostream>
#include <cstdio>

using namespace std;

struct node{
	int theRow;
	int theCol;
	int theData;
	node* right;
	node* down;
	
	node():theRow(0),theCol(0),theData(0),right(NULL),down(NULL){};
	node(int x, int y, int z, node* theRight=NULL, node* theDown=NULL):theRow(x),theCol(y),theData(z),right(theRight),down(theDown){};
};

struct list{
	node* next;
	
	list():next(NULL){};
};

const int maxn = 100000+10;

list row[maxn];
list col[maxn];

void insert(int x, int y, int z)
{
	node* newNode = new node(x,y,z);
	
	int flagRow = 0;
	int flagCol = 0;
	
	if(row[x].next==NULL){
		row[x].next = newNode;
		flagRow++;
	}
	
	if(col[y].next==NULL){
		col[y].next = newNode;
		flagCol++;
	}
	
	if(flagRow==0){
		if(row[x].next->theCol>y){
			newNode->right = row[x].next;
			row[x].next = newNode;
		}else{
			node* tmp1 = row[x].next;

			while(tmp1->right!=NULL and tmp1->right->theCol<y){
				tmp1 = tmp1->right;
			}
			if(tmp1->right==NULL){
				tmp1->right = newNode;
			}else{
				newNode->right = tmp1->right;
				tmp1->right = newNode;
			}
		}
	}
	
	if(flagCol==0){
		if(col[y].next->theRow>x){
			newNode->down = col[y].next;
			col[y].next = newNode;
		}else{
			node* tmp2 = col[y].next;

			while(tmp2->down!=NULL and tmp2->down->theRow<x){
				tmp2 = tmp2->down;
			}
			if(tmp2->down==NULL){
				tmp2->down = newNode;
			}else{
				newNode->down = tmp2->down;
				tmp2->down = newNode;
			}
		}
	}
}

void swapRow(int x, int y){
	node* tmp = row[x].next;
	row[x].next = row[y].next;
	row[y].next = tmp;
	
	tmp = row[x].next;
	while(tmp!=NULL){
		tmp->theRow = x;
		tmp = tmp->right;
	}
	tmp = row[y].next;
	while(tmp!=NULL){
		tmp->theRow = y;
		tmp = tmp->right;
	}
}

void swapCol(int x, int y){
	node* tmp = col[x].next;
	col[x].next = col[y].next;
	col[y].next = tmp;
	
	tmp = col[x].next;
	while(tmp!=NULL){
		tmp->theCol = x;
		tmp = tmp->down;
	}
	tmp = col[y].next;
	while(tmp!=NULL){
		tmp->theCol = y;
		tmp = tmp->down;
	}
}

void find(int x, int y)
{
	node* tmp = row[x].next;
	while(tmp!=NULL){
		if(tmp->theCol==y){
			cout<<tmp->theData<<'\n';
			break;
		}
		tmp = tmp->right;
	}
	if(tmp==NULL){
		cout<<0<<'\n';
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int n = 0;
	cin>>n;
	
	int x,y,z;
	for(int i = 0;i<n;i++){
		cin>>x>>y>>z;
		insert(x,y,z);
	}

	int m = 0;
	cin>>m;
	
	int ope;
	for(int i = 0;i<m;i++){
		cin>>ope>>x>>y;
		if(ope==0){
			swapRow(x,y);
		}else if(ope==1){
			swapCol(x,y);
		}else if(ope==2){
			find(x,y);
		}
	}
	
	cout<<flush;
	return 0;
}
