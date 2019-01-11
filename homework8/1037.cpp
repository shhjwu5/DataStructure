#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 10000+10;
int A[maxn] = {0};
int B[maxn] = {0};

void swap(int array[], int a, int b){
    int tmp = array[a];
    array[a] = array[b];
    array[b] = tmp;
}

void quicksort(int array[], int start, int end)
{
	if(start>=end){return;}
	
	int left = start;int right = end;
	while(left<right){
		while(array[left]<=array[right] and left<right){right--;}
		swap(array,left,right); 
		while(array[left]<array[right] and left<right){left++;}
		swap(array,left,right);
	}
	
	quicksort(array, start, left-1);
	quicksort(array, left+1, end);
}

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	int a,b;cin>>a>>b;
	
	for(int i = 0;i<a;i++){cin>>A[i];}
	for(int i = 0;i<b;i++){cin>>B[i];}
	
	quicksort(A,0,a-1);
	quicksort(B,0,b-1);
	
	int cnt = 0;
	int cntB = 0;
	for(int i = 0;i<a;i++){
		cnt++;
		if(B[cntB]<A[i] and cntB<b){cnt++;cntB++;}
	}
	
	cout<<cnt<<'\n';
	
	cout<<flush;
	return 0;
}
 
