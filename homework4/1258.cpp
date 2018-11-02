#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 100000+5;
int myData[maxn] = {0};
int tmp[maxn] = {0}; 
long long cnt = 0;

void Merge(int start, int mid, int end)
{
    int i = start, j=mid+1, k = start;
    while(i<=mid and j<=end){
        if(myData[i]>myData[j]){
            cnt += mid-i+1;
			tmp[k++] = myData[j++];
		}else{
            tmp[k++] = myData[i++];
        }
    }
    while(i<=mid){
		tmp[k++] = myData[i++];
	} 
    while(j<=end){
		tmp[k++] = myData[j++];
	}
    for(int p = start;p<=end;p++){
    	myData[p] = tmp[p];
	}
}
 
void MergeSort(int start, int end)
{
    int mid;
    if(start<end){
        mid = start+(end-start)/2;
        MergeSort(start, mid);
        MergeSort(mid+1, end);
        Merge(start, mid, end);
    }
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n = 0;
	cin>>n;
	
	for(int i = 0;i<n;i++){
		cin>>myData[i];
	}
	
	MergeSort(0,n-1);
	
	cout<<cnt<<endl;
	
	return 0;
} 
