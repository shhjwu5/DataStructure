#ifndef STACK_H
#define STACK_H

using namespace std;

template<class T>
class Stack{
private:
	struct stackNode{
		T theData;
		stackNode* next;
		
		stackNode(const T &x, stackNode* N = NULL):theData(x),next(N){};
		stackNode():next(NULL){};
		~stackNode(){};
	};
	stackNode* stackTop;
public:
	Stack(){stackTop = NULL;};
	~Stack();
	bool isEmpty() const {return stackTop==NULL;};
	void push(const T &x){stackTop = new stackNode(x, stackTop);};
	T pop();
	T top() const {return stackTop->theData;}; 
};

template<class T>
Stack<T>::~Stack()
{
	stackNode* tmp;
	while(stackTop!=NULL){
		tmp = stackTop;
		stackTop = stackTop->next;
		delete tmp;
	}
}

template<class T>
T Stack<T>::pop()
{
	stackNode* tmp = stackTop;
	T x = tmp->theData;
	stackTop = stackTop->next;
	delete tmp;
	return x;
}

#endif 
