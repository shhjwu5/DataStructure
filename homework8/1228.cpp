#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 400+5;

int process[maxn] = {0};
int zero[maxn] = {0};
int matrix[maxn][maxn] = {0};
long long totalOne = 0;
long long totalZero = 0;

void countOne(int n)
{
	int cnt = 0;
	int now = 1;
	for(int i = 0;i<n;i++){
		if(process[i]==1){zero[cnt++] = now;now=1;}
		else{now++;}
	}
	
	if(cnt==0){return;}
	
	zero[cnt] = now;
	
	for(int i = 0;i<cnt;i++){
		for(int j = i+1;j<=cnt;j+=2){
			totalOne+=zero[i]*zero[j];
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	long long n = 0;
	cin>>n;
	
	for(int i = 0;i<n;i++){
		for(int j = 0;j<n;j++){
			cin>>matrix[i][j];
			if(matrix[i][j]%2==1){matrix[i][j] = 1;}
			else{matrix[i][j] = 0;}
		}
	}
	
	for(int i = 0;i<n;i++){
		for(int p = 0;p<n;p++){
			process[p] = 0;
		}
		for(int j = i;j<n;j++){
			for(int p = 0;p<n;p++){
				process[p] = (process[p]+matrix[j][p]==1);
			}
			countOne(n);
		}
	}
	
	totalZero = (n*(n+1)/2*n*(n+1)/2)-totalOne;
	cout<<totalOne<<' '<<totalZero<<'\n';
	
	cout<<flush;
	return 0; 
} 
