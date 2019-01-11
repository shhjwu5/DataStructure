#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 100000+10;

struct node;
struct link;

struct link{
	node* poi;
	link* next;
	link* pre;
	
	link(node* po):poi(po),pre(NULL),next(NULL){}
};

struct node{
	int number;
	link* begin;
	node* father;
	int h;
	
	node(int x):number(x),begin(NULL),h(0),father(NULL){}
};

int n = 0;
node* root = NULL;
node* town[maxn] = {NULL};
bool inTree[maxn] = {0};
int result[maxn] = {0};
int cnt = 0;

void buildTree(node* p)
{
	link* t = p->begin;
	while(t!=NULL){
		if(inTree[t->poi->number]==1){
			p->father = town[t->poi->number];
			if(t->pre!=NULL){t->pre->next = t->next;}
			else{p->begin = t->next;}
			if(t->next!=NULL){t->next->pre = t->pre;}
			link* tmp = t;
			t = t->next;
		}else{
			inTree[t->poi->number] = 1;
			buildTree(town[t->poi->number]);
			t = t->next;
		}
	}
}

void updateH(node* p)
{
	p->h = 1;
	link* t = p->begin;
	while(t!=NULL){
		updateH(t->poi);
		p->h+=t->poi->h;
		t = t->next;
	}
}

void quicksort(int start, int end)
{
	if(start>=end){return;}
	
	int a = start;
	int b = end;
	int tmp = result[a];
	while(a<b){
		while(tmp<=result[b] and a<b){b--;}
		result[a] = result[b];
		while(result[a]<tmp and a<b){a++;}
		result[b] = result[a];
	}
	result[a] = tmp;
	
	quicksort(start,a-1);
	quicksort(a+1,end);
}

void check(node* p)
{
	if(n-p->h<=n/2){
		link* t = p->begin;
		while(t!=NULL){
			if(t->poi->h>n/2){
				check(t->poi);
				return;
			}
			t = t->next; 
		}
		result[cnt++] = p->number;
		t = p->begin;
		while(t!=NULL){
			check(t->poi);
			t = t->next;
		}
	}else{
		return;
	}
}

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	cin>>n;
	
	for(int i = 1;i<n+1;i++){
		town[i] = new node(i);
	}
	
	int x,y;
	for(int i = 0;i<n-1;i++){
		cin>>x>>y;
		link* tmpx = new link(town[x]);
		link* tmpy = new link(town[y]);
		
		if(town[x]->begin!=NULL){town[x]->begin->pre = tmpy;}
		tmpy->next = town[x]->begin;
		town[x]->begin = tmpy;
		
		if(town[y]->begin!=NULL){town[y]->begin->pre = tmpx;} 
		tmpx->next = town[y]->begin;
		town[y]->begin = tmpx;
	}
	
	root = town[1];
	node* p = root;
	inTree[1] = 1;

	buildTree(p);
	updateH(root);

	check(root);
	
	quicksort(0,cnt-1);
	
	for(int i = 0;i<cnt;i++){
		cout<<result[i]<<'\n';
	}
	
	cout<<flush;
	return 0;
} 
