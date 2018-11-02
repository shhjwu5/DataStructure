#include <iostream>

using namespace std;

struct node{
	int value;
	node* pre;
	node* next;
};

struct list{
	node* head;
	node* tail;
};

int main()
{
	int n = 0;
	cin>>n;
	
	list* myList;
	myList = new list;
	myList->head = new node;
	myList->head->next = NULL;
	myList->head->pre = NULL;
	int find = 0;
	cin>>find;
	myList->head->value = find;
	
	myList->tail = myList->head;
	
	node* tmp;
	for(int i = 1;i<n;i++){
		tmp = new node;
		cin>>find;
		tmp->value = find;
		tmp->pre = myList->tail;
		tmp->next = NULL;
		
		myList->tail->next = tmp;
		myList->tail = tmp;
	}
	
	int m = 0;
	cin>>m;
	int total = 0;
	for(int i = 0;i<m;i++){
		cin>>find;
		tmp = myList->head;
		
		while(tmp->value!=find){
			total++;
			tmp = tmp->next;
			if(tmp==NULL){
				break;
			}
		}
		if(tmp==NULL){
			continue;
		}else{
			total++;
		}
		
		if(tmp==myList->tail){
			myList->tail = tmp->pre;
			tmp->next = myList->head;
			tmp->pre->next = NULL;
			tmp->pre = NULL; 
			myList->head->pre = tmp;
			myList->head = tmp;
		}else if(tmp==myList->head){
		}else{
			tmp->pre->next = tmp->next;
			tmp->next->pre = tmp->pre;
			tmp->next = myList->head;
			tmp->pre = NULL;
			myList->head->pre = tmp;
			myList->head = tmp;
		}
	}
	
	cout<<total<<endl; 
	
	cout<<flush;
	return 0;
} 
