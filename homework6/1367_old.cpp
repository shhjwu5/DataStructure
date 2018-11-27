#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 30000+10;
void quicksort(int array[], int start, int end){
	if(start>=end){
        return;
    }
    int a = start;
    int b = end;
    int tmp;
    while(a<b){
        while(array[a]<=array[b] and a<b){
            b--;
        }
        tmp = array[a];
        array[a] = array[b];
        array[b] = tmp;

        while(array[a]<array[b] and a<b){
            a++;
        }
        tmp = array[a];
        array[a] = array[b];
        array[b] = tmp;
    }
    quicksort(array, start,a-1);
    quicksort(array, a+1,end);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int sizeA = 0, sizeB = 0;
    cin>>sizeA>>sizeB;
    
    int A[sizeA] = {0};
    for(int i = 0;i<sizeA;i++){
    	cin>>A[i];
	}
	
	int B[sizeB] = {0};
	for(int i = 0;i<sizeB;i++){
		cin>>B[i];
	}
	
	quicksort(A,0,sizeA-1);
	quicksort(B,0,sizeB-1);
	
	if(A[sizeA-1]!=B[sizeB-1]){
		cout<<A[sizeA-1]+B[sizeB-1]<<endl;
	}else{
		int a = sizeA-1;
		int b = sizeB-1;
		while(A[a]==A[sizeA-1] and a>0){
			a--;
		}
		while(B[b] == B[sizeB-1] and b>0){
			b--;
		}
		
		if(A[a]==A[sizeA-1]){
			cout<<B[b]+A[sizeA-1]<<endl;
		}else if(B[b]==B[sizeB-1]){
			cout<<A[a]+A[sizeA-1]<<endl;
		}else if(A[a]>B[b]){
			cout<<A[a]+A[sizeA-1]<<endl;
		}else{
			cout<<B[b]+A[sizeA-1]<<endl;
		}
	}
    

    return 0;
}
