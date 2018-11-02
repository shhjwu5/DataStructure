#include <iostream>
#include <cstdio>

using namespace std;

struct node{
	int number;
	node* next;
};

struct stack{
	node* head;
};

const int maxn = 1000000+5;

stack* myData;
int allNumber[maxn] = {0};

void create()
{
	myData = new stack;
	myData->head = new node;
	myData->head->number = -1;
	myData->head->next = NULL;
}

void addNode(int number)
{
	node* newNode;
	newNode = new node;
	newNode->number = number;
	newNode->next = myData->head->next;
	myData->head->next = newNode;
}

void delNode()
{
	node* p;
	p = myData->head->next;
	myData->head->next = p->next;
	delete p;
}

void del()
{
	node* p;
	while(myData->head->next){
		p = myData->head->next;
		myData->head->next = p->next;
		delete p;
	}
}

void printStack()
{
	node* p = myData->head->next;
	while(p){
		cout<<p->number<<'\t';
		p = p->next;
	}
	cout<<endl;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n = 0;
	cin>>n;

	int input = 0;
	int flag = 1;
	int total = 0;
	int cnt = 1;
	int allCnt = 0;

	create();

	for(int i = 0;i<n;i++){
		cin>>total; 

		input = 0;
		flag = 1;
		cnt = 1;
		allCnt = 0;

		for (int j = 0;j<total;j++){
			cin>>allNumber[j];
		}
		
		addNode(cnt);
		cnt++;

		while(flag && cnt<total+1){
			if(myData->head->next->number<allNumber[allCnt]){
				addNode(cnt);
				cnt++;
			}else if(myData->head->next->number>allNumber[allCnt]){
				flag = 0;
				break;
			}else{
				allCnt++;
				cnt++;
				delNode();
			}
		}

		while(myData->head->next){
			if(myData->head->next->number==allNumber[allCnt]){
				allCnt++;
				delNode();
			}else{
				flag = 0;
				break;
			}
		}

		if(flag){
			cout<<"Yes"<<'\n';
		}else{
			cout<<"No"<<'\n';
		}

		del();
	}
	
	cout<<flush;

	return 0;
}
