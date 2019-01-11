#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	int m,n;
	cin>>m>>n;
	
	int* A = new int[m];
	int* B = new int[n];
	
	for(int i = 0;i<m;i++){cin>>A[i];}
	for(int i = 0;i<n;i++){cin>>B[i];}

	if(m==0){for(int i = 0;i<n;i++){cout<<B[i]<<' ';}}
	else if(n==0){for(int i = 0;i<m;i++){cout<<A[i]<<' ';}}
	else{
		int a = 0;
		int b = 0;
		while(a<m and b<n){
			if(A[a]<=B[b]){cout<<A[a++]<<' ';}
			else{cout<<B[b++]<<' ';}
		}
		if(a<m){for(int i = a;i<m;i++){cout<<A[i]<<' ';}}
		if(b<n){for(int i = b;i<n;i++){cout<<B[i]<<' ';}}
	}
	cout<<flush;
	return 0;
} 
