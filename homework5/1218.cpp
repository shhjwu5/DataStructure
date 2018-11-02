#include <iostream>

using namespace std;

template<class T>
void Merge(T myData[], T tmp[], int start, int mid, int end)
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

template<class T>
void MergeSort(T myData[], T tmp[], int start, int end)
{
    int mid;
    if(start<end){
        mid = start+(end-start)/2;
        MergeSort(myData, tmp, start, mid);
        MergeSort(myData, tmp, mid+1, end);
		Merge(myData, tmp, start, mid, end);
    }
}

const int maxn = 10000+5;

template<class T>
class Set{
private:
	int size = 0;
	T myData[maxn] = {0};
public:
	Set(){};
	~Set(){};
	void printSet();
	void AND(T andData[], int andSize);
	void OR(T orData[], int orSize);
	void MINUS(T minusData[], int minusSize);
};

template<class T>
void Set<T>::printSet()
{
	for(int i = 0;i<size;i++){
		cout<<myData[i]<<' ';
	}
	cout<<'\n';
}

template<class T>
void Set<T>::AND(T andData[], int andSize){
	int size1 = 0;
	int size2 = 0;
	int totalSize = 0;
	T tmp[maxn] = {0};
	MergeSort(andData, tmp, 0, andSize-1);
	
	while(size1<size and size2<andSize){
		if(myData[size1]>andData[size2]){
			size2++;
		}else if(myData[size1]<andData[size2]){
			size1++;
		}else{
			tmp[totalSize++] = andData[size2++];
			size1++;
		}
	}
	
	size = totalSize;
	for(int i = 0;i<totalSize;i++){
		myData[i] = tmp[i];
	}
}

template<class T>
void Set<T>::OR(T orData[], int orSize){
	int size1 = 0;
	int size2 = 0;
	int totalSize = 0;
	T tmp[maxn] = {0};
	MergeSort(orData, tmp, 0, orSize-1);
	
	while(size1<size and size2<orSize){
		if(myData[size1]>orData[size2]){
			tmp[totalSize++] = orData[size2++];
		}else if(myData[size1]<orData[size2]){
			tmp[totalSize++] = myData[size1++];
		}else{
			tmp[totalSize++] = orData[size2++];
			size1++;
		}
	}
	while(size1<size){
		tmp[totalSize++] = myData[size1++];
	}
	while(size2<orSize){
		tmp[totalSize++] = orData[size2++];
	}
	
	size = totalSize;
	for(int i = 0;i<totalSize;i++){
		myData[i] = tmp[i];
	}
}

template<class T>
void Set<T>::MINUS(T minusData[], int minusSize){
	int size1 = 0;
	int size2 = 0;
	int totalSize = 0;
	T tmp[maxn] = {0};
	MergeSort(minusData, tmp, 0, minusSize-1);
	
	while(size1<size and size2<minusSize){
		if(myData[size1]>minusData[size2]){
			size2++;
		}else if(myData[size1]<minusData[size2]){
			tmp[totalSize++] = myData[size1++];
		}else{
			size2++;
			size1++;
		}
	}
	while(size1<size){
		tmp[totalSize++] = myData[size1++];
	}
	
	size = totalSize;
	for(int i = 0;i<totalSize;i++){
		myData[i] = tmp[i];
	}
}

int main()
{
	int n = 0;
	cin>>n;
	char operation = 0;
	Set<int> mySet;
	
	int number = 0;
	int tmp[maxn] = {0};

	for(int i = 0;i<n;i++){
		cin>>operation;
		if(operation=='+'){
			cin>>number;
			for(int j = 0;j<number;j++){
				cin>>tmp[j];
			}
			mySet.OR(tmp, number);
			mySet.printSet();
		}else if(operation=='*'){
			cin>>number;
			for(int j = 0;j<number;j++){
				cin>>tmp[j];
			}
			mySet.AND(tmp, number);
			mySet.printSet();
		}else if(operation=='-'){
			cin>>number;
			for(int j = 0;j<number;j++){
				cin>>tmp[j];
			}
			mySet.MINUS(tmp, number);
			mySet.printSet();
		}
	}
	
	return 0;
}
