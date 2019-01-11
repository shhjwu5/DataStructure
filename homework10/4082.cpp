#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 100000+10;

struct node{
	int number;
	int c;
	node* next;
	
	node(int num):number(num),c(0),next(NULL){}
};

bool inCoun[maxn] = {0};
node* city[maxn] = {NULL};

void update(int i, int &total, int &cnt)
{
	if(inCoun[i]){return;}
	inCoun[i] = true;
	total++;
	cnt+=city[i]->c;
	node* t = city[i]->next;
	while(t!=NULL){update(t->number,total,cnt);t = t->next;}
}

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	int n,m;
	cin>>n>>m;
	
	for(int i = 0;i<n+1;i++){city[i] = new node(i);}
	int a,b;
	for(int i = 0;i<m;i++){
		cin>>a>>b;
		node* nodeA = new node(a);
		nodeA->next = city[b]->next;
		city[b]->next = nodeA;
		city[b]->c++;
		
		node* nodeB = new node(b);
		nodeB->next = city[a]->next;
		city[a]->next = nodeB;
		city[a]->c++;
	}
	
	int result = 0;
	int total = 0;
	int cnt = 0;
	for(int i = 0;i<n+1;i++){
		total = cnt = 0;
		update(i,total,cnt);
		result+=(total*(total-1)/2-cnt/2);
	}
	
	cout<<result<<'\n';
	
	cout<<flush;
	return 0;
} 
