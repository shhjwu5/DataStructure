#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 1000000+10;
int parent[maxn] = {0};
int parent1[maxn] = {0};
int parent2[maxn] = {0};

void initialize(int n){
	int lt = 0, rt = 0;
	for(int i = 1;i<=n;i++){
		cin>>lt>>rt;
		parent[lt] = i;
		parent[rt] = i;
	}
}

int sameFather(int x, int y)
{
	int cnt1 = 0;
	while(x!=0){
		parent1[cnt1++] = x;
		x = parent[x];
	}
	int cnt2 = 0;
	while(y!=0){
		parent2[cnt2++] = y;
		y = parent[y];
	}
	for(int i = 0;i<cnt1 and i<cnt2;i++){
		if(parent1[cnt1-1-i]!=parent2[cnt2-1-i]){
			return parent1[cnt1-i];
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int n = 0,x = 0,y = 0;
	cin>>n>>x>>y;
	
	initialize(n);
	cout<<sameFather(x,y)<<endl;
	
	cout<<flush;
	return 0;
} 
