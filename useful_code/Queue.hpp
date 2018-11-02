#ifndef QUEUE_H
#define QUEUE_H

using namespace std;

template<class T>
class Queue{
private:
	struct node{
		T theData;
		node* next;
		
		node(const T &item, node* N = NULL):theData(item), next(N){};
		node():next(NULL){};
		~node(){};
	};
	node* front;
	node* rear;
public:
	Queue();
	~Queue();
	bool isEmpty() const;
	void enQueue(const T &x);
	T deQueue();
	T getHead() const;
};

template<class T>
Queue<T>::Queue()
{
	front = NULL;
	rear = NULL;
}

template<class T>
Queue<T>::~Queue()
{
	node* tmp;
	while(front!=NULL){
		tmp = front;
		front = front->next;
		delete tmp;
	}
}

template<class T>
bool Queue<T>::isEmpty() const
{
	return front==NULL;
}

template<class T>
T Queue<T>::getHead() const
{
	return front->theData;
}

template<class T>
void Queue<T>::enQueue(const T &x)
{
	if(rear==NULL){
		rear = new node(x);
		front = rear;
	}else{
		rear->next = new node(x);
		rear = rear->next;
	}
}

template<class T>
T Queue<T>::deQueue()
{
	node* tmp = front;
	T value = front->theData;
	front = front->next;
	if(front==NULL){
		rear = NULL;
	}
	delete tmp;
	return value;
}

#endif 
