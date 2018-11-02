#ifndef MERGESORT_H
#define MERGESORT_H

using namespace std;

void Merge(int myData[], int tmp[], int start, int mid, int end)
{
    int i = start, j=mid+1, k = start;
    while(i<=mid and j<=end){
        if(myData[i]>myData[j]){
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
 
void MergeSort(int myData[], int tmp[], int start, int end)
{
    int mid;
    if(start<end){
        mid = start+(end-start)/2;
        MergeSort(myData, tmp, start, mid);
        MergeSort(myData, tmp, mid+1, end);
		Merge(myData, tmp, start, mid, end);
    }
}

#endif
