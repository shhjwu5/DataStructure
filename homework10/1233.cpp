#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 100+5;

struct node{
	int number;
	node* next;
	
	node(int num):number(num),next(NULL){}
};

node* myData[maxn] = {NULL};
bool inPath[maxn] = {0};
int total = 0;

int m,start,path;

void dfs(node* t, int pos)
{
	if(inPath[t->number]){return;}
	if(pos==path){total++;return;}
	inPath[t->number] = true;
	node* tmp = t->next;
	while(tmp!=NULL){dfs(myData[tmp->number],pos+1);tmp=tmp->next;}
	inPath[t->number] = false;
}

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	int n;
	cin>>n>>m>>start>>path;
	
	for(int i = 1;i<n+1;i++){myData[i] = new node(i);}
	int from,to;
	for(int i = 1;i<m+1;i++){
		cin>>from>>to;
		node* newNode = new node(to);
		newNode->next = myData[from]->next;
		myData[from]->next = newNode;
	}
	
	dfs(myData[start],0);
	
	cout<<total<<'\n';
	
	cout<<flush;
	return 0;
}
