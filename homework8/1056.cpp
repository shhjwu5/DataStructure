#include <iostream>
#include <cstdio>

using namespace std;

struct box;
struct candy;

struct candy{
	int number;
	candy* next;
	
	box* origin;
	
	candy():next(NULL),origin(NULL){};
};

struct box{
	int number;
	
	box* big;
	box* small;
	
	candy* head;
	candy* tail;
	
	box():number(0),big(NULL),small(NULL),head(NULL),tail(NULL){};
};

const int maxn = 500000+10;
candy* candies[maxn] = {NULL};
box* first = NULL;box* last = NULL;

void remove(box* theBox)
{
	if(theBox->big!=NULL){theBox->big->small = theBox->small;}
	else{first = theBox->small;}
	if(theBox->small!=NULL){theBox->small->big = theBox->big;}
	else{last = theBox->big;}
	
	theBox->big = NULL;
	theBox->small = NULL;
}

void merge(int x, int y)
{
	if(candies[x]==NULL or candies[y]==NULL){return;}
	box* addBox = candies[x]->origin;
	box* toBox = candies[y]->origin;
	
	if(addBox==toBox){return;}
	
	remove(addBox);
	remove(toBox);
	
	box* newBox = new box;
	newBox->number = addBox->number+toBox->number;
	newBox->head = toBox->head;
	newBox->tail = addBox->tail;
	toBox->tail->next = addBox->head;
	
	candy* q = toBox->head;
	while(q!=NULL){
		q->origin = newBox;
		q = q->next;
	}
	addBox = NULL;
	toBox = NULL;
	
	box* p = first;
	while(p!=NULL and newBox->number<p->number){p = p->small;}
	if(p!=NULL){
		newBox->big = p->big;
		newBox->small = p;
		if(p->big!=NULL){p->big->small = newBox;}
		else{first = newBox;}
		p->big = newBox;
	}else{
		newBox->big = last;
		newBox->small = p;
		if(p->big!=NULL){p->big->small = newBox;}
		else{first = newBox;}
		if(last!=NULL){last->small = newBox;}
		last = newBox;
	}
}

void eat(int x)
{
	if(candies[x]==NULL){return;}
	box* theBox = candies[x]->origin;
	candy* p = theBox->head;
	candy* pre = theBox->head;
	while(p!=NULL){
		pre = p;
		p = p->next;
		candies[pre->number] = NULL; 
		delete pre;
	}
	
	remove(theBox);
}

void find(int x)
{
	int flag = 1;
	box* p = first;
	for(int i = 0;i<x-1;i++){
		p = p->small;
		if(p==NULL){
			flag = 0;
			break;
		}
	}
	if(flag==1){cout<<p->number<<'\n';}
	else{cout<<0<<'\n';}
}

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	int n,m;
	cin>>n>>m;
	
	first = new box;
	box* p = first;
	candies[1] = new candy;
	first->head = first->tail = candies[1];
	first->number = 1;
	candies[1]->origin = first;
	candies[1]->number = 1;
	
	for(int i = 2;i<n+1;i++){
		p->small = new box;
		p->small->big = p;
		candies[i] = new candy;
		p->small->head = p->small->tail = candies[i];
		p->small->number = 1;
		candies[i]->origin = p->small;
		p = p->small;
		candies[i]->number = i;
	}
	
	last = p;
	
	for(int i = 0;i<m;i++){
		char op;
		int x,y;
		cin>>op;
		if(op=='C'){
			cin>>x>>y;
			merge(x,y);
		}else if(op=='D'){
			cin>>x;
			eat(x);
		}else if(op=='Q'){
			cin>>x;
			find(x);
		}
	}
	
	cout<<flush;
	return 0; 
} 
