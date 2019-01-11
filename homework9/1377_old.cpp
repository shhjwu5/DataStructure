#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 100000+10;
int myData[maxn] = {0};

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
	
	int cnt = 0;
	int tmp = 0;
	int maxTmp = 0;
	
	for(int i = 0;i<pos;i++){
		tmp = (pos-i)%2==1?pos:(pos+1);
		maxTmp = (n-i)%2==1?n+1:n;
		for(int j = tmp;j<maxTmp;j+=2){
			if(myData[j]-myData[i]==0){cnt++;}
		}
	}
	cout<<cnt<<'\n';

	cout<<flush;
	return 0;
} 
