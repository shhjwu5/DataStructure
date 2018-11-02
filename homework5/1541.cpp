#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 200000+5;
long int myData[maxn][2] = {0};

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int k = 0;
	int n = 0;
	
	cin>>k>>n;
	
	for(int i = 0;i<n;i++){
		cin>>myData[i][0];
	}
	myData[0][1] = 0;
	
	for(int i = 0;i<k;i++){
		if(myData[i][0]>myData[myData[0][1]][0]){
			myData[0][1] = i;
		}
	}
	
	cout<<myData[myData[0][1]][0]<<' ';

	for(int i = 1;i<n-k+1;i++){
		if(myData[i-1][1]<i){
			myData[i][1] = i;
			for(int j = i;j<i+k;j++){
				if(myData[j][0]>myData[myData[i][1]][0]){
					myData[i][1] = j;
				}
			}
		}else{
			if(myData[myData[i-1][1]][0]>myData[i+k-1][0]){
				myData[i][1] = myData[i-1][1];
			}else{
				myData[i][1] = i+k-1;
			}
		}
		cout<<myData[myData[i][1]][0]<<' ';
	}
	
	cout<<'\n';
	
	cout<<flush;
	return 0;
} 
