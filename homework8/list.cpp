#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 50000+5;

string name[maxn];

struct node{
	node* next[26];
	bool here;
	int deps;
	
	node():here(false),deps(0){for(int i = 0;i<26;i++){next[i] = NULL;}}
};

struct poi{
	node* po;
	node* po2;
	poi():po(NULL),po2(NULL){}
};

poi* point[maxn] = {NULL};

node* root = NULL;
node* broot = NULL;

bool check[maxn] = {0};

int num(char x)
{
	return x-97;
}

int sameBegin(int x, int y)
{
	int total = min(name[x].size(),name[y].size());
	int a = 0;
	int b = total-1;
	
	int mid;
	while(a<b){
		mid = (a+b)/2;
		if(point[x][mid].po==point[y][mid].po){
			a = mid+1;
		}else{
			b = mid-1;
		}
	}
	
	if(point[x][a].po==point[y][a].po){
		return point[x][a].po->deps;
	}else{
		return point[x][a].po->deps-1;
	}
}

int sameEnd(int x, int y)
{
	int xsize = name[x].size();
	int ysize = name[y].size();
	int total = min(xsize,ysize);
	int a = 0;
	int b = total-1;
	
	int mid;
	while(a<b){
		mid = (a+b)/2;
		if(point[x][xsize-1-mid].po2==point[y][ysize-1-mid].po2){
			a = mid+1;
		}else{
			b = mid-1;
		}
	}
	
	if(point[x][xsize-1-a].po2==point[y][ysize-1-a].po2){
		return point[x][xsize-1-a].po2->deps;
	}else{
		return point[x][xsize-1-a].po2->deps-1;
	}
}

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	int n = 0;
	cin>>n;
	
	string t;
	node* p;
	node* bp;
	root = new node;
	broot = new node;
	for(int i = 1;i<n+1;i++){
		cin>>name[i];
		t = name[i];
		p = root;
		bp = broot;
		point[i] = new poi[t.size()];
		for(int j = 0;j<t.size();j++){
			if(p->next[num(t[j])]==NULL){
				p->next[num(t[j])] = new node;
				p = p->next[num(t[j])];
				p->deps = j+1;
			}else{
				p = p->next[num(t[j])];
			}
			point[i][j].po = p;
		}
		
		for(int j = t.size()-1;j>=0;j--){
			if(bp->next[num(t[j])]==NULL){
				bp->next[num(t[j])] = new node;
				bp = bp->next[num(t[j])];
				bp->deps = t.size()-j;
			}else{
				bp = bp->next[num(t[j])];
			}
			point[i][j].po2 = bp;
		}
		
		if(p->here==1){check[i] = 1;}
		else{check[i] = 0;p->here = 1;}
	}
	
	int m = 0;
	cin>>m;
	int ope,x,y;
	for(int i = 0;i<m;i++){
		cin>>ope;
		if(ope==1){
			cin>>x;
			if(check[x]==1){cout<<"yes"<<'\n';}
			else{cout<<"no"<<'\n';}
		}else if(ope==2){
			cin>>x>>y;
			cout<<sameBegin(x,y)<<'\n';
		}else if(ope==3){
			cin>>x>>y;
			cout<<sameEnd(x,y)<<'\n';
		}
	}
	
	cout<<flush;
	return 0;
}
