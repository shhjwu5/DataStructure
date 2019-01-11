#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 25+5;

struct box;
struct pile;

struct box{
	int number;
	pile* origin;
	box* pre;
	box* next;
	
	box(int num):number(num),origin(NULL),pre(NULL),next(NULL){}
};

struct pile{
	box* begin;
	
	pile():begin(NULL){}
};

box* boxes[maxn] = {NULL};
pile* piles[maxn] = {NULL};

void clear(box* t)
{
	box* p = t->next;
	while(p!=NULL){
		if(p->pre!=NULL){p->pre->next = NULL;}
		p->pre= NULL;
		
		piles[p->number]->begin = p;
		p->origin = piles[p->number];
		
		p = p->next;
	}
}

void attach(box* from, box* to)
{
	to->next = from;
	
	if(from->pre!=NULL){from->pre->next = NULL;}
	else{from->origin->begin = NULL;}
	from->pre = to;
	from->origin = to->origin;
}

void moveOnto(int a, int b)
{
	box* from = boxes[a];
	box* to = boxes[b];
	
	clear(from);
	clear(to);
	
	attach(from, to);
}

void moveOver(int a, int b)
{
	box* from = boxes[a]; 
	box* to = boxes[b];
	while(to->next!=NULL){to = to->next;}
	
	clear(from);
	
	attach(from, to);
}

void pileOnto(int a, int b)
{
	box* from = boxes[a]; 
	box* to = boxes[b];
	
	clear(to);
	
	attach(from, to);
	box* t = from->next;
	while(t!=NULL){t->origin = to->origin;t = t->next;}
}

void pileOver(int a, int b)
{
	box* from = boxes[a]; 
	box* to = boxes[b];
	
	while(to->next!=NULL){to = to->next;}
	
	attach(from, to);
	box* t = from->next;
	while(t!=NULL){t->origin = to->origin;t = t->next;}
}

int main()
{
	int n = 0;
	cin>>n;
	for(int i = 0;i<n;i++){
		piles[i] = new pile;
		boxes[i] = new box(i);
		piles[i]->begin = boxes[i];
		boxes[i]->origin = piles[i];
	}
	
	char input[6] = {0};
	char ope[6] = {0};
	int a,b;

	while(true){
		cin>>input;
		if(input[0]=='q'){break;}
		
		cin>>a;
		cin>>ope;
		cin>>b;
		
		if(boxes[a]->origin==boxes[b]->origin){continue;}
		
		if(input[0]=='m'){
			if(ope[1]=='n'){
				moveOnto(a,b);
			}else if(ope[1]=='v'){
				moveOver(a,b);
			}
		}else if(input[0]=='p'){
			if(ope[1]=='n'){
				pileOnto(a,b);
			}else if(ope[1]=='v'){
				pileOver(a,b);
			}
		}
	}
	
	for(int i = 0;i<n;i++){
		cout<<i<<": ";
		box* t = piles[i]->begin;
		while(t!=NULL){
			cout<<t->number<<' ';
			t = t->next;
		}
		cout<<endl;
	}
}
