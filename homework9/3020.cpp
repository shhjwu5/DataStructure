#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 100000+10;
int myData[maxn] = {0};
int tmpData[maxn] = {0};

void quicksort(int start, int end)
{
	if(start>=end){return;}
	
	int tmp = myData[start];
	int a = start;
	int b = end;
	
	while(a<b){
		while(tmp<=myData[b] and a<b){b--;}
		myData[a] = myData[b];
		while(myData[a]<tmp and a<b){a++;}
		myData[b] = myData[a];
	}
	myData[a] = tmp;
	quicksort(start,a-1);
	quicksort(a+1,end);
}

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	int n,k;
	cin>>n>>k;
	
	for(int i = 0;i<n;i++){cin>>myData[i];}
	quicksort(0,n-1);
	
	int a = 0;
	int b = 0;
	int bsize = 0;
	long long total = 0;
	
	bool flag = 1;
	
	while(n-a+bsize-b>1){
		int num = 0;
		if(flag){
			if((n-k)%(k-1)==0){num=k;}
			else{num = (n-k)%(k-1)+1;}
			flag = 0;
		}else{num = k;}
		
		long long sum = 0;
		while(num--){
			if(a==n){sum+=tmpData[b++];}
			else if(b==bsize){sum+=myData[a++];}
			else if(myData[a]<tmpData[b]){sum+=myData[a++];}
			else{sum+=tmpData[b++];}
		}
		
		total+=sum;
		tmpData[bsize++] = sum;
	}
	
	cout<<total<<endl;
	
	cout<<flush;
	return 0;
}
