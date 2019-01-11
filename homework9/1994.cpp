#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 500+5;
int myData[maxn][maxn] = {0};

void bfs(int i, int j)
{
	if(myData[i][j]==-1){return;}
	myData[i][j] = -1;
	bfs(i-1,j);
	bfs(i+1,j);
	bfs(i,j-1);
	bfs(i,j+1);
}

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	int n,m;
	cin>>n>>m;
	
	for(int i = 0;i<n+2;i++){myData[i][0] = myData[i][m+1] = -1;}
	for(int i = 0;i<m+2;i++){myData[0][i] = myData[n+1][i] = -1;}
	
	for(int i = 1;i<n+1;i++){
		for(int j = 1;j<m+1;j++){
			cin>>myData[i][j];
		}
	}
	
	int cnt = 0;
	for(int i = 1;i<n+1;i++){
		for(int j = 1;j<m+1;j++){
			if(myData[i][j]==-1){continue;}
			cnt++;
			bfs(i,j);
		}
	}
	
	cout<<cnt<<endl;
	
	cout<<flush;
	return 0;
} 
