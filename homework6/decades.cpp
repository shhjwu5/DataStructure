#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 1000000+10;
int A[maxn] = {0};
int B[maxn] = {0};
int row[maxn] = {0};
int deque[2] = {0};

int currentSize = 0;
int array[maxn][2] = {0};

void enQueue(const int a,const int b)
{
	currentSize++;
	int hole = currentSize;
	
	while(hole>1 and A[a]+B[b]<A[array[hole/2][0]]+B[array[hole/2][1]]){
		array[hole][0] = array[hole/2][0];
		array[hole][1] = array[hole/2][1];
		hole/=2;
	}
	array[hole][0] = a;
	array[hole][1] = b;
}

void percolateDown(int hole)
{
	int child;
	int tmp[2];
	tmp[0] = array[hole][0];
	tmp[1] = array[hole][1];
	
	while(hole*2<=currentSize){
		child = hole*2;
		if(child!=currentSize and A[array[child+1][0]]+B[array[child+1][1]]<A[array[child][0]]+B[array[child][1]]){
			child++;
		}
		if(A[array[child][0]]+B[array[child][1]]<A[tmp[0]]+B[tmp[1]]){
			array[hole][0] = array[child][0];
			array[hole][1] = array[child][1];
		}else{
			break;
		}
		hole = child;
	}
	
	array[hole][0] = tmp[0];
	array[hole][1] = tmp[1];
}

void deQueue()
{
	deque[0] = array[1][0];
	deque[1] = array[1][1];
	array[1][0] = array[currentSize][0];
	array[1][1] = array[currentSize][1];
	currentSize--;
	percolateDown(1);
} 

void swapA(int a, int b){
    int tmp = A[a];
    A[a] = A[b];
    A[b] = tmp;
}

void swapB(int a, int b){
    int tmp = B[a];
    B[a] = B[b];
    B[b] = tmp;
}

void quicksortA(int start, int end){
    if(start>=end){
        return;
    }
    int a = start;
    int b = end;
    while(a<b){
        while(A[a]<=A[b] and a<b){
            b--;
        }
        swapA(a,b);

        while(A[a]<A[b] and a<b){
            a++;
        }
        swapA(a,b);
    }
    quicksortA(start,a-1);
    quicksortA(a+1,end);
}

void quicksortB(int start, int end){
    if(start>=end){
        return;
    }
    int a = start;
    int b = end;
    while(a<b){
        while(B[a]<=B[b] and a<b){
            b--;
        }
        swapB(a,b);

        while(B[a]<B[b] and a<b){
            a++;
        }
        swapB(a,b);
    }
    quicksortB(start,a-1);
    quicksortB(a+1,end);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n = 0;
    cin>>n;

    for(int i = 0;i<n;i++){
        cin>>A[i];
    }
    for(int i = 0;i<n;i++){
        cin>>B[i];
    }

    quicksortA(0,n-1);
    quicksortB(0,n-1);
	
	int i = 0;
	enQueue(0,0);
	while(i<n){
		deQueue();
		cout<<A[deque[0]]+B[deque[1]]<<' ';
		i++;
		enQueue(deque[0],deque[1]+1);
		row[deque[0]]++;
		if(row[deque[0]+1]==0){
			enQueue(deque[0]+1,deque[1]);
			row[deque[0]+1]++;
		}
	}

    cout<<flush;

    return 0;
}
