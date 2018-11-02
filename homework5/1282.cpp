#include <iostream>
#include <cmath>

using namespace std;

const int maxn = 2000+5;
long long myData[maxn] = {0};
long long myData2[maxn] = {0};
long long tmp[maxn] = {0};
long long check[maxn][maxn] = {0};

void Merge(int start, int mid, int end)
{
    int i = start, j=mid+1, k = start;
    while(i<=mid and j<=end){
        if(myData2[i]>myData2[j]){
            tmp[k] = myData2[j];
            k++; j++;
		}else{
            tmp[k] = myData2[i];
            k++; i++;
        }
    }
    while(i<=mid){
		tmp[k] = myData2[i];
        k++; i++;
	} 
    while(j<=end){
		tmp[k] = myData2[j];
        k++; j++;
	}
    for(int p = start;p<=end;p++){
    	myData2[p] = tmp[p];
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
	int n = 0;
	cin>>n;
	for(int i = 0;i<n;i++){
		cin>>myData[i];
		myData2[i] = myData[i];
	}
	
	MergeSort(0,n-1);
	
	for(int i = 0;i<n;i++){
		check[1][i] = abs(myData[1]-myData2[i]);
	}
	
	for(int i = 1;i<n;i++){
		long long mn = 1e18;
		for(int j = 0;j<n;j++){
			mn = min(mn, check[i-1][j]);
			check[i][j] = mn+abs(myData[i]-myData2[j]);
		}
	}
	
	long long ans = 1e18;
	for(int i = 0;i<n;i++){
		ans = min(ans,check[n-1][i]);
	}
	
	cout<<ans<<endl;
	
	cout<<flush;
	return 0;
}
