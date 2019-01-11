#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 100000+10; 
int myData[maxn] = {0};
int number[2*maxn][2] = {0};

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	int n,x;
	cin>>n>>x;
	
	int y = 0;
	int pos = 0;
	
	int count = 0;
	
	for(int i = 1;i<n+1;i++){
		cin>>y;
		if(y>x){count++;}
		else if(y<x){count--;}
		else{pos = i;}
		
		myData[i] = count;
	}
	
	for(int i = 0;i<pos;i++){
		number[myData[i]+maxn][0]++;
	}
	
	for(int i = pos;i<n+1;i++){
		number[myData[i]+maxn][1]++;
	}
	
	int cnt = 0;
	int i = 0;
	while(number[i+maxn][0]!=0 or number[i+maxn][1]!=0){
		cnt+=number[i+maxn][0]*number[i+maxn][1];
		i++;
	}
	i = -1;
	while(number[i+maxn][0]!=0 or number[i+maxn][1]!=0){
		cnt+=number[i+maxn][0]*number[i+maxn][1];
		i--;
	}
	
	cout<<cnt<<'\n';

	cout<<flush;
	return 0;
} 
