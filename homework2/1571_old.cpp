#include<iostream>
#include<cmath> 

using namespace std;

int** myData;
int** tmp; 

int pos(int n, int begin, int end)
{
	int left = begin;
	int right = end;
	int mid = 0;
	while(left<=right){
		mid = left+(right-left)/2;
		if(n == myData[mid][4]){
			return mid;
		}else if(n<myData[mid][4]){
			right = mid-1;
		}else if(n>myData[mid][4]){
			left = mid+1;
		}
	}
}

void Merge(int start, int mid, int end,int pos)
{
    int i = start, j=mid+1, k = start;
    while(i<=mid and j<=end){
        if(myData[i][pos]>myData[j][pos]){
            tmp[k] = myData[j];
            k++; j++;
		}else{
            tmp[k] = myData[i];
            k++; i++;
        }
    }
    while(i<=mid){
		tmp[k] = myData[i];
        k++; i++;
	} 
    while(j<=end){
		tmp[k] = myData[j];
        k++; j++;
	}
    for(int p = start;p<=end;p++){
    	myData[p] = tmp[p];
	}
}
 
void MergeSort(int start, int end, int pos)
{
    int mid;
    if(start<end){
        mid = start+(end-start)/2;
        MergeSort(start, mid, pos);
        MergeSort(mid+1, end, pos);
        Merge(start, mid, end, pos);
    }
}

int main()
{
	int n = 0;
	cin>>n;
	
	myData = new int* [n];
	tmp = new int* [n];
	for(int i = 0;i<n;i++){
		myData[i] = new int [5];
		tmp[i] = new int [5];
		cin>>myData[i][0];
	}
	for(int i = 0;i<n;i++){
		cin>>myData[i][1];
		myData[i][2] = i;
	}

	MergeSort(0, n-1, 0);
	for(int i = 0;i<n;i++){
		myData[i][3] = i;
	}
	MergeSort(0, n-1, 1);
	for(int i = 0;i<n;i++){
		myData[i][4] = i;
	}
	MergeSort(0, n-1, 2);
	
	int cnt = 0;
	int j = 0;

	for(int i = n-1;i>0;i--){
		j = pos(myData[i][3], 0, i);
		cnt = cnt+i-j;
		for(int k = j;k<i;k++){
			myData[k][4] = myData[k+1][4];
		}
		for(int p = 0;p<i;p++){
			cout<<myData[p][4]<<' ';
		}
		cout<<endl;
	}
	
	cout<<cnt<<endl;
	
	/*
	for(int i = 0;i<n;i++){
		delete myData[i];
		delete tmp[i];
	}
	
	delete myData;
	delete tmp;
	*/
	
	return 0;
}
