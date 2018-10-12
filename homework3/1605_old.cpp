#include <iostream>

using namespace std;

struct node{
	char number;
	int check;
	node* previous;
};

struct list{
	node* head;
	node* tail;
};

list* create()
{
	list* data;
	data = new list;
	data->head = new node;
	data->tail = new node;
	data->head->number = 0;
	data->head->check = 0;
	data->head->previous = nullptr;
	
	data->tail->number = 0;
	data->tail->check = 0;
	data->tail->previous = data->head;
	
	return data;
}

void del(list* data)
{
	node* p = data->tail;
	node* q = p;
	while(p!=nullptr){
		p = p->previous;
		delete q;
		q = p;
	}
}

char other(char input)
{
	if(input==')'){
		return '(';
	}
	if(input==']'){
		return '[';
	}
	if(input=='}'){
		return '{';
	}
	
	return 1;
}

int isEmpty(list* data)
{
	if(data->tail->previous->number==data->head->number){
		return 1;
	}else{
		return 0;
	}
}

void push(list* data, list* stack, char input)
{
	node* p;
	p = new node;
	p->number = input;
	p->check = 0;
	p->previous = data->tail->previous;
	
	data->tail->previous = p;
	
	if(stack->tail->previous->number==other(input)){
		p->check = 1;
		node* q = stack->tail->previous;
		stack->tail->previous = q->previous;
		delete q;
	}else{
		node* q;
		q = new node;
		q->number = input;
		q->check = 0;
		q->previous = stack->tail->previous;
	
		stack->tail->previous = q;
	}
}

void pop(list* data, list* stack)
{
	if(!isEmpty(data)){
		char end = data->tail->previous->number;
		node* p = data->tail->previous;
		
		data->tail->previous = p->previous;
		
		p->previous = nullptr;
		
		if(p->check){
			node* q;
			q = new node;
			q->number = other(p->number);
			q->check = 0;
			q->previous = stack->tail->previous;
		
			stack->tail->previous = q;
		}else{
			node* q = stack->tail->previous;
		
			stack->tail->previous = q->previous;
		
			q->previous = nullptr;
			
			delete q;
		}
		
		delete p;
	}
}

void output(list* data)
{
	if(!isEmpty(data)){
		cout<<data->tail->previous->number<<endl;
	}
}

void match(list* stack)
{
	if(isEmpty(stack)){
		cout<<"YES"<<endl;
	}else{
		cout<<"NO"<<endl;
	}
}

int main()
{
	cin.tie(0);
	int n = 0;
	cin>>n;
	
	list* data;
	data = create();
	list* stack;
	stack = create();
	
	int op = 0;
	char tmp = 0;
	for(int i = 0;i<n;i++){
		cin>>op;
		if(op==1){
			cin>>tmp;
			push(data, stack, tmp);
		}else if(op==2){
			pop(data, stack);
		}else if(op==3){
			output(data);
		}else if(op==4){
			match(stack);
		}
	}	
	
	del(data);
	del(stack);
	
	return 0;
}
