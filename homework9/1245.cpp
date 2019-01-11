#include <iostream>
#include <cstdio>
 
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
	stackNode* Top;
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
	Top = NULL;
}

template<class T>
Stack<T>::~Stack()
{
	stackNode* tmp;
	while(Top!=NULL){
		tmp = Top;
		Top = Top->next;
		delete tmp;
	}
}

template<class T>
bool Stack<T>::isEmpty() const
{
	return Top==NULL;
}

template<class T>
void Stack<T>::push(const T &x)
{
	Top = new stackNode(x, Top);
}

template<class T>
T Stack<T>::pop()
{
	stackNode* tmp = Top;
	T x = tmp->theData;
	Top = Top->next;
	delete tmp;
	return x;
}

template<class T>
T Stack<T>::top() const
{
	return Top->theData;
}



const int Add = '+';
const int Minus = '-';
const int Prod = '*';
const int Div = '/';
const int Left = '(';
const int Right = ')';
const int Space = ' ';

const int maxn = 1000+10;

Stack<int> cal;
int express[maxn] = {0};

Stack<int> symbol;
Stack<int> result;
char input[maxn] = {0};

void buildStack(int n)
{
	int i = n-1;
	while(i>=0){
		if(input[i]==Right){symbol.push(input[i]);i--;}
		else if(input[i]==Left){
			while(true){
				int t = symbol.pop();
				if(t!=Right){result.push(t);}
				else{break;}
			}
			i--;
		}else if(input[i]==Add or input[i]==Minus or input[i]==Prod or input[i]==Div){
			if(symbol.isEmpty()==1 or symbol.top()==Right){symbol.push(input[i]);}
			else if(!((input[i]==Add or input[i]==Minus) and (symbol.top()==Prod or symbol.top()==Div))){symbol.push(input[i]);}
			else{
				int t = symbol.top();
				while((t==Prod or t==Div) and (input[i]==Add or input[i]==Minus)){
					result.push(symbol.pop());
					if(symbol.isEmpty()==1){break;}
					else{t = symbol.top();}
				}
				symbol.push(input[i]);
			}
			i--;
		}else if(input[i]==Space){
			i--;
		}else{
			int power = 10;
			int sum = input[i--]-48;
			while(input[i]>='0' and input[i]<='9'){
				sum+=(input[i]-48)*power;
				power*=10;i--;
			}
			result.push(sum);
		}
	}
	
	while(symbol.isEmpty()==0){result.push(symbol.pop());}
}

int length = 0;

void printStack()
{	
	while(result.isEmpty()==0){
		int t = result.pop();
		express[length++] = t;
		if(t==Add or t==Minus or t==Prod or t==Div){cout<<(char)t<<' ';}
		else{cout<<t<<' ';}
	}
	cout<<endl;
}

int calculate()
{
	for(int i = length-1;i>=0;i--){
		if(express[i]==Add or express[i]==Minus or express[i]==Prod or express[i]==Div){
			int a = cal.pop();
			int b = cal.pop();
			if(express[i]==Add){cal.push(a+b);}
			else if(express[i]==Minus){cal.push(a-b);}
			else if(express[i]==Prod){cal.push(a*b);}
			else if(express[i]==Div){cal.push(a/b);}
		}else{
			cal.push(express[i]);
		}
	}
	return cal.pop();
}

int main()
{
	cin.getline(input,1003);
	int size = 0;
	while(input[size]==Add or input[size]==Minus or input[size]==Prod or input[size]==Div or input[size]==Left or input[size]==Right or input[size]==Space or (input[size]>='0' and input[size]<='9')){
		size++;
	}
	
	buildStack(size);
	printStack();
	cout<<calculate()<<endl;
	
	cout<<flush;
	return 0;
}
