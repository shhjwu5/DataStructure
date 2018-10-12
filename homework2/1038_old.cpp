#include<iostream>

using namespace std;

struct list{
	list* previous;
	list* next;
	int data;
};

int main()
{
    int n = 0;
    cin>>n; 
	
	list* p;
	
	list* head;
	head = new list;
	head->data = 1;
	head->next = head;
	head->previous = head;
	
	p = head;
	
	for(int i = 2;i<=n;i++){
		list* newNode;
		newNode = new list;
		newNode->data = i;
		newNode->next = head;
		newNode->previous = p;
		p->next = newNode;
		head->previous = newNode;
		p = p->next;
	}

	int m = 0;
	
	p = head;
	
	list* q;

	for(int i = 0;i<n-1;i++){
		cin>>m;
		for(int k = 0;k<m-1;k++){
			p = p->next;
		}
		q = p->previous;
		q->next = p->next;
		p->next->previous = q;
		p->previous = nullptr;
		p->next = nullptr;
		delete p;
		p = q->next;
	}
	
	cout<<p->data<<endl;
	
	return 0;
}
