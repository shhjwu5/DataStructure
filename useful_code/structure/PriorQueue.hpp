#ifndef PRIORQUEUE_H
#define PRIORQUEUE_H

#include <iostream>

using namespace std;

template<class T>
class PriorQueue{
private:
	int currentSize;
	T *array;
	int maxSize;
public:
	PriorQueue(int capacity=100);
	PriorQueue(const T myData[], int size);
	~PriorQueue();
	bool isEmpty() const;
	void enQueue(const T &x);
	T deQueue();
	T getHead() const;
private:
	void doubleSpace();
	void buildHeap();
	void percolateDown(int hole); 
};

template<class T>
PriorQueue<T>::PriorQueue(int capacity)
{
	array = new T[capacity];
	maxSize = capacity;
	currentSize = 0;
}

template<class T>
PriorQueue<T>::~PriorQueue()
{
	delete [] array;
}

template<class T>
bool PriorQueue<T>::isEmpty() const
{
	return currentSize == 0;
}

template<class T>
T PriorQueue<T>::getHead() const
{
	return array[1];
}

template<class T>
void PriorQueue<T>::enQueue(const T &x)
{
	if(currentSize == maxSize - 1){
		doubleSpace();
	}
	
	currentSize++;
	int hole = currentSize;
	
	while(hole>1 and x<array[hole/2]){
		array[hole] = array[hole/2];
		hole/=2;
	}
	array[hole] = x;
}

template<class T>
T PriorQueue<T>::deQueue()
{
	T minItem = array[1];
	array[1] = array[currentSize--];
	percolateDown(1);
	return minItem;
} 

template<class T>
void PriorQueue<T>::percolateDown(int hole)
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
void PriorQueue<T>::buildHeap()
{
	for(int i = currentSize/2;i>0;i--){
		percolateDown(i);
	}
}

template<class T>
PriorQueue<T>::PriorQueue(const T* items, int size):maxSize(size+10), currentSize(size)
{
	array = new T [maxSize];
	for(int i = 0;i<size;i++){
		array[i+1] = items[i];
	}
	buildHeap();
}

template<class T>
void PriorQueue<T>::doubleSpace()
{
	T* tmp = array;
	maxSize*=2;
	array = new T [maxSize];
	for(int i = 0;i<=currentSize;i++){
		array[i] = tmp[i];
	}
	delete [] tmp;
}

#endif 
