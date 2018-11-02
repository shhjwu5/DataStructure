#ifndef STACK_H
#define STACK_H

using namespace std;

template<class T>
class Stack{
private:
	struct stackNode{
		T theData;
		stackNode* next;
		
		stackNode(const T & item, stackNode* N = NULL):theData(item),next(N){};
		stackNode():next(NULL){};
		~stackNode(){};
	};
	stackNode* top;
public:
	Stack();
	~Stack();
	bool isEmpty() const;
	void push(const T &x);
	T pop();
	T top() const; 
};

template<class T>
Stack<T>::Stack()
{
	top = NULL;
}

template<class T>
Stack<T>::~Stack()
{
	stackNode* tmp;
	while(top!=NULL){
		tmp = top;
		top = top->next;
		delete tmp;
	}
}

template<class T>
bool Stack<T>::isEmpty() const
{
	return top==NULL;
}

template<class T>
void Stack<T>::push(const T &x)
{
	top = new stackNode(x, top);
}

template<class T>
T Stack<T>::pop()
{
	stackNode* tmp = top;
	T x = tmp->theData;
	top = top->next;
	delete tmp;
	return x;
}

template<class T>
T Stack<T>::top() const
{
	return top->theData;
}

#endif 
