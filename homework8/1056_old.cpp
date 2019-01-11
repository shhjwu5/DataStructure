#include <iostream>
#include <cstdio>

using namespace std;

struct node{
	int number;
	node* big;
	node* small;
	
	node():number(1),big(NULL),small(NULL){};
};

const int maxn = 500000+10;
node* myData[maxn] = {NULL};

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	int n,m;
	cin>>n>>m;
		
	for(int i = 0;i<n;i++){myData[i] = new node;}
	for(int i = 1;i<n;i++){myData[i]->big = myData[i-1];}
	for(int i = 0;i<n-1;i++){myData[i]->small = myData[i+1];}
	node* head = myData[0];
	node* tail = myData[n-1];
	
	for(int i = 0;i<m;i++){
		char op;
		int x,y;
		cin>>op;
		if(op=='C'){
			cin>>x>>y;
			if(myData[x]->number==0 or myData[y]->number==0 or x==y){continue;}
			if(myData[x]->big!=NULL){myData[x]->big->small = myData[x]->small;}
			if(myData[x]->small!=NULL){myData[x]->small->big = myData[x]->big;}
			if(myData[y]->big!=NULL){myData[y]->big->small = myData[y]->small;}
			if(myData[y]->small!=NULL){myData[y]->small->big = myData[y]->big;}
			
			myData[y]->number+=myData[x]->number;
			myData[x]->number = 0;
			
			myData[x]->small = NULL;
			myData[x]->big = tail;
			
			tail->small = myData[x];
			tail = myData[x];
			
			node* p = head;
			while(myData[y]->number<p->number){p = p->small;}
						
			myData[y]->big = p->big;
			myData[y]->small = p;
			
			if(p->big!=NULL){p->big->small = myData[y];}
			p->big = myData[y];
			if(myData[y]->big==NULL){head = myData[y]; }
		}else if(op=='D'){
			cin>>x;
			if(myData[x]->number==0){continue;}
			if(myData[x]->big!=NULL){myData[x]->big->small = myData[x]->small;}
			else{head = myData[x]->small;}
			if(myData[x]->small!=NULL){myData[x]->small->big = myData[x]->big;}
			
			myData[x]->number = 0;
			
			myData[x]->small = NULL;
			myData[x]->big = tail;
			
			tail->small = myData[x];
			tail = myData[x];
		}else if(op=='Q'){
			cin>>x;
			node* p = head;
			for(int i = 1;i<x;i++){
				p = p->small;
				if(p->number==0){break;}
			}
			cout<<p->number<<'\n';
		}
	}
	
	cout<<flush;
	return 0; 
} 
