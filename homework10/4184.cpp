#include <iostream>
#include <cstdio>

using namespace std;

struct node{
	int number;
	node* next;
	
	node(int num):number(num),next(NULL){}
};

const int maxn = 100000+10;
node* tree[maxn] = {NULL};
int sizes[maxn] = {0};
int father[maxn] = {0};
bool inTree[maxn] = {0};

void updateSize(int t)
{
	sizes[t] = 1;
	node* p = tree[t]->next;
	while(p!=NULL){
		updateSize(p->number);
		sizes[t]+=sizes[p->number];
		p = p->next;
	}
}

void updateTree(int t)
{
	inTree[t] = true;
	node* p = tree[t]->next;
	while(p!=NULL){updateTree(p->number);}
}

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	int T = 0;
	cin>>T;
	
	int n,k,div;
	int a,b;
	int root;
	int goal;
	for(int i = 0;i<T;i++){
		cin>>n>>k;
		div = n/k;
		a = b = 0;
		for(int i = 1;i<n+1;i++){tree[i] = new node(i);}
		
		for(int j = 0;j<n-1;j++){
			cin>>a>>b;
			if(inTree[a]){
				father[b] = a;
				updateTree(b);
				node* tmp = new node(b);
				tmp->next = tree[a]->next;
				tree[a]->next = tmp;
			}else if(inTree[b]){
				father[a] = b;
				updateTree(a);
				node* tmp = new node(a);
				tmp->next = tree[b]->next;
				tree[b]->next = tmp;
			}else{
				if(!father[b]){
					father[b] = a;
					node* tmp = new node(b);
					tmp->next = tree[a]->next;
					tree[a]->next = tmp;
				}else{
					father[a] = b;
					node* tmp = new node(a);
					tmp->next = tree[b]->next;
					tree[b]->next = tmp;
				}
			}
		}
		
		root = 1;
		while(father[root]!=0){root++;}

		updateSize(root);
		
		goal = 0;
		for(int j = 1;j<n+1;j++){
			if(sizes[j]%k==0){goal++;}
		}
		
		if(goal==div){cout<<"YES"<<'\n';}
		else{cout<<"NO"<<'\n';}

		for(int i = 1;i<n+1;i++){tree[i] = NULL;father[i] = 0;inTree[i] = false;}
	}
	
	cout<<flush;
	return 0;
} 
