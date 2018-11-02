#include <iostream>
#include <cstdio>

using namespace std;

template<class T>
class priorQueue{
private:
	int currentSize;
	T *array;
	int maxSize;
public:
	priorQueue(int capacity=20000);
	~priorQueue();
	void enQueue(const T &x);
	T deQueue();
	T getHead() const;
	void printQueue() const;
	int findQueue(const T x) const;
	void decreaseQueue(const int idx, const T x);
private:
	void buildHeap();
	void percolateDown(int hole); 
};

template<class T>
priorQueue<T>::priorQueue(int capacity)
{
	array = new T [capacity];
	maxSize = capacity;
	currentSize = 0;
}

template<class T>
priorQueue<T>::~priorQueue()
{
	delete [] array;
}

template<class T>
T priorQueue<T>::getHead() const
{
	return array[1];
}

template<class T>
void priorQueue<T>::enQueue(const T &x)
{
	int hole = ++currentSize;
	
	for(;hole>1 and x<array[hole/2];hole/=2){
		array[hole] = array[hole/2];
	}
	array[hole] = x;
}

template<class T>
T priorQueue<T>::deQueue()
{
	T minItem;
	minItem = array[1];
	array[1] = array[currentSize--];
	percolateDown(1);
	return minItem;
} 

template<class T>
void priorQueue<T>::percolateDown(int hole)
{
	int child;
	T tmp = array[hole];
	
	while(hole*2<=currentSize){
		child = hole*2;
		if(child!=currentSize and array[child+1]<array[child]){
			child++;
		}
		if(array[child]<tmp){
			array[hole] = array[child];
		}else{
			break;
		}
		hole = child;
	}
	
	array[hole] = tmp;
}

template<class T>
void priorQueue<T>::printQueue() const
{
	for(int i = 1;i<=currentSize;i++){
		cout<<array[i]<<' ';
	}
	cout<<endl;
}

template<class T>
int priorQueue<T>::findQueue(const T x) const
{
	int i = 1;
	int MinIdx = 0;
	int Min = 0;
	for(;i<=currentSize;i++){
		if(array[i]>x){
			Min = array[i];
			MinIdx = i;
			break;
		}
	}
	for(;i<=currentSize;i++){
		if(array[i]>x and array[i]<Min){
			Min = array[i];
			MinIdx = i;
		}
	}
	
	return MinIdx;
}

template<class T>
void priorQueue<T>::buildHeap()
{
	for(int i = currentSize/2;i>0;i--){
		percolateDown(i);
	}
}

template<class T>
void priorQueue<T>::decreaseQueue(const int idx, const T x)
{
	array[idx]-=x;
	buildHeap();	
}

int main()
{
	int n = 0;
	cin>>n;
	
	priorQueue<int> prique;
	char operation[20] = {0};
	int output = 0;
	int value = 0;
	int tmp = 0;
	
	for(int i = 0;i<n;i++){
		cin>>operation;
		
		if(operation[0]=='i'){
			cin>>output;
			prique.enQueue(output);
		}else if(operation[0]=='f'){
			cin>>output;
			cout<<prique.findQueue(output)<<endl;
		}else if(operation[0]=='d'){
			cin>>output>>value;
			prique.decreaseQueue(output, value);
		}
	}
	
	cout<<flush;
	return 0;
}

