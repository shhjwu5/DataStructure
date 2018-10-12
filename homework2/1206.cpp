#include <iostream>

using namespace std;

const int BEGIN = 1;
const int END = 2;
const int IF = 3;
const int THEN = 4;
const int IFTHEN = 5;
const int ELSE = 6;

const char RIGHT[7] = "Match!";
const char WRONG[7] = "Error!";

struct list{
	list* next;
	int value;
};

list* create()
{
	list* head;
	list* tail;
	head = new list;
	tail = new list;
	
	head->next = tail;
	head->value = 0;
	
	tail->next = nullptr;
	tail->value = 0;
	
	return head;
}

void add(list* head, int n)
{
	list* newList;
	newList = new list;
	newList->value = n;
	newList->next = head->next;
	head->next = newList;
}

void copyChar(char* str1, const char* str2)
{
	for(int i = 0;i<7;i++){
		str1[i] = str2[i];
	}
}

int main()
{
	list* be = create();
	list* ite = create();

	list* p;        

	char result[7] = {0};
	copyChar(result,RIGHT);
	
	char input[100];
	while(!cin.eof() and cin>>input){
		if(input[0]=='b' and input[1]=='e' and input[2]=='g' and input[3]=='i' and input[4]=='n' and input[5]==0){
			add(be, BEGIN);
		}
		if(input[0]=='i' and input[1]=='f' and input[2]==0){
			add(ite, IF);
		}
		if(input[0]=='e' and input[1]=='n' and input[2]=='d' and input[3]==0){
			if(be->next->value == BEGIN){
				p = be->next;
				be->next = be->next->next;
				delete p;
			}else{
				copyChar(result, WRONG);
				break;
			}
		}
		if(input[0]=='t' and input[1]=='h' and input[2]=='e' and input[3]=='n' and input[4]==0){
			if(ite->next->value == IF){
				p = ite->next;
				ite->next->value = IFTHEN;
			}else{
				copyChar(result, WRONG);
				break;
			}
		}
		if(input[0]=='e' and input[1]=='l' and input[2]=='s' and input[3]=='e' and input[4]==0){
			if(ite->next->value == IFTHEN){
				p = ite->next;
				ite->next = ite->next->next;
				delete p;
			}else{
				copyChar(result, WRONG);
				break;
			}
		}
	}
	
	if(be->next->value != 0){
		copyChar(result, WRONG);
	}
	delete be->next;
	delete be;
	
	p = ite;
	
	list* q;
	q = new list;
	q = p;
	
	while(p->next->value == IFTHEN){
		p = p->next;
		delete q;
		q = p;
	}
	if(p->next->value != 0){
		copyChar(result, WRONG);
	}
	while(p->next->value != 0){
		p = p->next;
		delete q;
		q = p;
	}
	delete p->next;
	delete p;
	
	cout<<result<<endl;
	
	return 0;
}
