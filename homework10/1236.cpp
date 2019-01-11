#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100+5;

struct node{
	int number;
	int weight;
	node* next;
	
	node(int num,int w):number(num),weight(w),next(NULL){}
};

node* myData[maxn] = {NULL};
int theEnd;
int minStep = 1e9;
bool atMap[maxn] = {0};

void dfs(int from, int step)
{
	if(from==theEnd){if(step<minStep){minStep = step;};return;}
	if(atMap[from]){return;}
	atMap[from] = true;
	node* t = myData[from]->next;
	while(t!=NULL){
		dfs(t->number,step+t->weight);
		t = t->next;
	}
	atMap[from] = false;
}

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	int n,m,start;
	cin>>n>>m>>start>>theEnd;
	
	for(int i = 1;i<n+1;i++){myData[i] = new node(i,0);}
	int a,b,w;
	for(int i = 1;i<m+1;i++){
		cin>>a>>b>>w;
		node* nodeB = new node(b,w);
		nodeB->next = myData[a]->next;
		myData[a]->next = nodeB;
	}
	
	dfs(start,0);
	
	cout<<minStep<<'\n';
	
	cout<<flush;
	return 0;
}
