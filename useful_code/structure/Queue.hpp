#ifndef QUEUE_H
#define QUEUE_H

using namespace std;

template<class T>
class Queue{
private:
	struct queNode{
		T theData;
		queNode* next;
		
		queNode(const T &x, queNode* N = NULL):theData(x), next(N){};
		queNode():next(NULL){};
		~queNode(){};
	};
	queNode* front;
	queNode* rear;
public:
	Queue(){front = rear = NULL;};
	~Queue();
	bool isEmpty() const {return front==NULL;};
	void enQueue(const T &x);
	T deQueue();
	T getHead() const {return front->theData;};
};

template<class T>
Queue<T>::~Queue()
{
	queNode* tmp;
	while(front!=NULL){
		tmp = front;
		front = front->next;
		delete tmp;
	}
}

template<class T>
void Queue<T>::enQueue(const T &x)
{
	if(rear==NULL){front = rear = new queNode(x);}
	else{rear = rear->next = new queNode(x);}
}

template<class T>
T Queue<T>::deQueue()
{
	queNode* tmp = front;
	T value = front->theData;
	front = front->next;
	if(front==NULL){rear = NULL;}
	delete tmp;
	return value;
}

#endif 
