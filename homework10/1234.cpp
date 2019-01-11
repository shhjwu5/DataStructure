#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 10000+5;
const int maxm = 100000+10;
int lines[maxm][3] = {0};
int point[maxn] = {0};

void quicksort(int start, int end)
{
	if(start>=end){return;}
	
	int a = start;
	int b = end;
	int tmp[3] = {lines[start][0],lines[start][1],lines[start][2]};
	while(a<b){
		while(tmp[2]<=lines[b][2] and a<b){b--;}
		lines[a][0] = lines[b][0];
		lines[a][1] = lines[b][1];
		lines[a][2] = lines[b][2];
		while(lines[a][2]<=tmp[2] and a<b){a++;}
		lines[b][0] = lines[a][0];
		lines[b][1] = lines[a][1];
		lines[b][2] = lines[a][2];
	}
	lines[a][0] = tmp[0];
	lines[a][1] = tmp[1];
	lines[a][2] = tmp[2];
	
	quicksort(start,a-1);
	quicksort(a+1,end);
}

int find(int x)
{
	if(point[x]<=0){return x;}
	else{return find(point[x]);}
}

void merge(int a, int b)
{
	int posA = find(a);
	int posB = find(b);
	if(point[posA]<point[posB]){
		point[posA] = posB;
		point[posB] = min(point[posB],point[posA]-1);
	}else{
		point[posB] = posA;
		point[posA] = min(point[posB]-1,point[posA]);
	}
}

int main()
{
	ios::sync_with_stdio(9);cin.tie(0);cout.tie(0);
	
	int n,m;
	cin>>n>>m;
	
	for(int i = 0;i<m;i++){cin>>lines[i][0]>>lines[i][1]>>lines[i][2];}
	quicksort(0,m-1);
	
	int a,b,p;
	int total = 0;
	
	for(int i = 0;i<m;i++){
		a = lines[i][0];
		b = lines[i][1];
		p = lines[i][2];
		
		if(find(a)==find(b)){continue;}
		else{
			merge(a,b);
			total+=p;
		}
	}
	
	cout<<total<<endl;
	
	cout<<flush;
	return 0;
}
