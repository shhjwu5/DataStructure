#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 100000+10;

struct node{
	int num;
	int pos; 
	
	node* small;
	node* big;
	
	node(int x, int w):num(x),pos(w),small(NULL),big(NULL){}
};

node* number[maxn] = {NULL};
node* point[maxn] = {NULL};
int result[maxn] = {0};

void quicksort(int start, int end)
{
	if(start>=end){return;}
	
	int a = start;
	int b = end;
	node* tmp = number[a];
	
	while(a<b){
		while(tmp->num<=number[b]->num and a<b){b--;}
		number[a] = number[b];
		while(number[a]->num<tmp->num and a<b){a++;}
		number[b] = number[a];
	}
	number[a] = tmp;
	
	quicksort(start,a-1);
	quicksort(a+1,end);
}

void delNode(node* t)
{
	if(t->big!=NULL){t->big->small = t->small;}
	if(t->small!=NULL){t->small->big = t->big;}
	t->big = NULL;
	t->small = NULL;
}

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	int n = 0;
	cin>>n;
	
	int x = 0;
	for(int i = 0;i<n;i++){
		cin>>x;
		number[i] = new node(x,i);
	}
	if(n%2==0){n--;}
	
	quicksort(0,n-1);
	
	for(int i = 0;i<n;i++){
		point[number[i]->pos] = number[i];
	}
	
	for(int i = 1;i<n;i++){
		number[i]->small = number[i-1];
		number[i-1]->big = number[i];
	}
	
	for(int i = 0;i<n;i++){
		number[i]->pos = i;
	}
	
	node* mid = number[n/2];
	int del = n-1;
	for(int save=n/2;save>=0;save--){
		result[save] = mid->num;
		if(del<1){break;}
		
		if(point[del]->pos==mid->pos){
			if(point[del-1]->pos<mid->pos){mid = mid->big;}
			else{mid = mid->small;}
		}else if(point[del-1]->pos==mid->pos){
			if(point[del]->pos<mid->pos){mid = mid->big;}
			else{mid = mid->small;}
		}else{
			int change = 0;
			if(point[del]->pos<mid->pos){change+=1;}
			else{change-=1;}
			if(point[del-1]->pos<mid->pos){change+=1;}
			else{change-=1;}
			if(change==2){mid = mid->big;}
			else if(change==-2){mid = mid->small;}
		}
		
		delNode(point[del]);
		delNode(point[del-1]);
		
		del-=2;
	}
	
	for(int i = 0;i<n/2+1;i++){
		cout<<result[i]<<' ';
	}
	cout<<endl;
	
	cout<<flush;
	return 0;
}
