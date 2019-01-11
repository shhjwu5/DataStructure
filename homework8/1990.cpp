#include <iostream>
#include <cstdio>

using namespace std;

struct like;
struct cd;

struct like{
	like* small;
	like* big;
	
	int number;
	
	cd* begin;
	
	like(int t):small(NULL),big(NULL),number(t),begin(NULL){}
};

struct cd{
	int number;
	
	cd* pre;
	cd* next;
	
	like* origin;
	
	cd(int i):number(i),pre(NULL),next(NULL),origin(NULL){}
};

const int maxn = 2000000+10;
cd* cds[maxn] = {NULL};

like* head = NULL;

void removeLike(like* node)
{
	if(node->small!=NULL){node->small->big = node->big;}
	else{head = node->big;}
	if(node->big!=NULL){node->big->small = node->small;}
	
	node = NULL;
}

void removeCd(cd* node)
{
	if(node->pre!=NULL){node->pre->next = node->next;}
	else{node->origin->begin = node->next;}
	if(node->next!=NULL){node->next->pre = node->pre;}
	
	node->next = NULL;
	node->pre = NULL;
	node->origin = NULL; 
}

void insertLike(like* leftLike, like* rightLike, like* newLike)
{
	newLike->big = rightLike;
	newLike->small = leftLike;
	
	if(leftLike!=NULL){leftLike->big = newLike;}
	else{head = newLike;}
	if(rightLike!=NULL){rightLike->small = newLike;}
}

void insertCd(like* theLike, cd* theCd)
{
	theCd->origin = theLike;
	theCd->next = theLike->begin;
	if(theLike->begin!=NULL){theLike->begin->pre = theCd;}
	theLike->begin = theCd;
}

void print()
{
	like* p = head;
	while(p!=NULL){
		cout<<p->number<<'\t';
		cd* q = p->begin;
		while(q!=NULL){
			cout<<q->number<<' ';
			q = q->next;
		}
		cout<<endl;
		p = p->big;
	}
}

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	int n,m;
	cin>>n>>m;
	
	int input;
	cds[1] = new cd(1);
	cin>>input;
	head = new like(input);
	head->begin = cds[1];
	cds[1]->origin = head;

	like* p = head;
	for(int i = 2;i<n+1;i++){
		cds[i] = new cd(i);
		cin>>input;
		if(input==p->number){
			cds[i]->next = p->begin;
			cds[i]->origin = p;
			
			p->begin->pre = cds[i];
			p->begin = cds[i];
		}else{
			p->big = new like(input);
			p->big->small = p;
			
			p = p->big;
			p->begin = cds[i];
			cds[i]->origin = p;
		}
	}
	
	int pos,diff;
	for(int i = 1;i<m+1;i++){
		cin>>pos>>diff;
		
		like* theLike = cds[pos]->origin;
		cd* theCd = cds[pos];
		like* newLike;
		if(diff==1){
			removeCd(theCd);
			if(theLike->big==NULL or theLike->big->number>theLike->number+1){
				newLike = new like(theLike->number+1);
				insertLike(theLike,theLike->big,newLike);
				insertCd(newLike,theCd);
			}else{
				insertCd(theLike->big,theCd);
			}
			if(theLike->begin==NULL){removeLike(theLike);}
		}else{
			removeCd(theCd);
			if(theLike->small==NULL or theLike->small->number<theLike->number-1){
				newLike = new like(theLike->number-1);
				insertLike(theLike->small,theLike,newLike);
				insertCd(newLike,theCd);
			}else{
				insertCd(theLike->small,theCd);
			}
			if(theLike->begin==NULL){removeLike(theLike);}
		}
		
		cout<<head->begin->number<<'\n';
	}
	
	cout<<flush;
	return 0;
}
