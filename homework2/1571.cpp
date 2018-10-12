#include<iostream>
#include<cmath> 

using namespace std;

int** a;
int** b;
int* aIdx;
int* bIdx;
int** tmp; 
int* temp;

long long sum = 0;

void MergeA(int start, int mid, int end, int pos)
{
    int i = start, j=mid+1, k = start;
    while(i<=mid and j<=end){
        if(a[i][pos]>a[j][pos]){
            tmp[k] = a[j];
            k++; j++;
		}else{
            tmp[k] = a[i];
            k++; i++;
        }
    }
    while(i<=mid){
		tmp[k] = a[i];
        k++; i++;
	} 
    while(j<=end){
		tmp[k] = a[j];
        k++; j++;
	}
    for(int p = start;p<=end;p++){
    	a[p] = tmp[p];
	}
}

void MergeB(int start, int mid, int end, int pos)
{
    int i = start, j=mid+1, k = start;
    while(i<=mid and j<=end){
        if(b[i][pos]>b[j][pos]){
            tmp[k] = b[j];
            k++; j++;
		}else{
            tmp[k] = b[i];
            k++; i++;
        }
    }
    while(i<=mid){
		tmp[k] = b[i];
        k++; i++;
	} 
    while(j<=end){
		tmp[k] = b[j];
        k++; j++;
	}
    for(int p = start;p<=end;p++){
    	b[p] = tmp[p];
	}
}

void finalMerge(int start, int mid, int end)
{
    int i = start, j=mid+1, k = start;
    while(i<=mid and j<=end){
        if(bIdx[i]>bIdx[j]){
        	sum = sum + mid-i+1;
            temp[k] = bIdx[j];
            k++; j++;
		}else{
            temp[k] = bIdx[i];
            k++; i++;
        }
    }
    while(i<=mid){
		temp[k] = bIdx[i];
        k++; i++;
	} 
    while(j<=end){
		temp[k] = bIdx[j];
        k++; j++;
	}
    for(int p = start;p<=end;p++){
    	bIdx[p] = temp[p];
	}
}
 
void MergeSort(int start, int end, int pos, int which)
{
    int mid;
    if(start<end){
        mid = start+(end-start)/2;
        MergeSort(start, mid, pos, which);
        MergeSort(mid+1, end, pos, which);
        if(which == 0){
        	MergeA(start, mid, end, pos);
		}else if (which == 1){
			MergeB(start, mid, end, pos);
		}else{
			finalMerge(start, mid, end);
		}
    }
}

void distance(int n)
{
	for(int i = 0;i<n;i++){
		aIdx[a[i][2]] = i;
	}
	for(int i = 0;i<n;i++){
		bIdx[i] = aIdx[b[i][2]];
	}
	
	MergeSort(0, n-1, 0, 2);
}

int main()
{
	int n = 0;
	cin>>n;
	
	a = new int* [n];
	b = new int* [n];
	aIdx = new int [n];
	bIdx = new int [n];
	tmp = new int* [n];
	temp = new int [n];
	for(int i = 0;i<n;i++){
		a[i] = new int [3];
		tmp[i] = new int [3];
		cin>>a[i][0];
		a[i][1] = i;
	}
	for(int i = 0;i<n;i++){
		b[i] = new int [3];
		cin>>b[i][0];
		b[i][1] = i;
	}

	MergeSort(0, n-1, 0, 0);
	for(int i = 0;i<n;i++){
		a[i][2] = i;
	}
	MergeSort(0, n-1, 1, 0);
	
	MergeSort(0, n-1, 0, 1);
	for(int i = 0;i<n;i++){
		b[i][2] = i;
	}
	MergeSort(0, n-1, 1, 1);
	
	sum = 0;
	distance(n);
	
	cout<<sum%99999997<<endl;
	
	for(int i = 0;i<n;i++){
		delete a[i];
		delete b[i];
	}
	delete temp;
	delete aIdx;
	delete bIdx;
	delete a;
	delete b;
	delete tmp;
	
	return 0;
}
