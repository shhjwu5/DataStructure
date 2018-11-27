#include <iostream>
#include <cstdio>

using namespace std;

const int maxA = 1000000+10;
const int maxB = 100000+10;

char A[maxA] = {0};
char B[maxB] = {0};

int sizeA = 0;
int sizeB = 0;

int nextB[maxB];

void getNext()
{
	nextB[0] = -1;
	
	int j = 0;
	int k = -1;
	
	while(j<sizeB-1){
		if(k==-1 or B[j]==B[k]){
			if(B[++j]==B[++k]){
				nextB[j]=nextB[k];
			}else{
				nextB[j] = k;
			}
		}else{
			k = nextB[k];
		}
	}
}

int kmp()
{
	int i = 0;
	int j = 0;
	while(i<sizeA and j<sizeB){
		if(j==-1 or A[i]==B[j]){
			i++;j++;
		}else{
			j = nextB[j]; 
		}
	}
	if(j==sizeB){
		return i-j;
	}else{
		return -1;
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	cin>>A;
	cin>>B;
	
	while(A[sizeA]!=0){
		sizeA++;
	}
	while(B[sizeB]!=0){
		sizeB++;
	}
	
	for(int i = 0;i<sizeB;i++){
		nextB[i] = -1;
	}
	
	getNext();
	int result = kmp();
	
	cout<<result<<endl;
	
	cout<<flush;
	return 0;
} 
