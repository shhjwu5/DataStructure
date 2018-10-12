#include <iostream>
#include <cmath>

struct list{
	int num;
	list* next;
};

using namespace std;

int* findNum(int);
void calResult(int, int*);

int main()
{
	int n = 0;
	cin>>n; 
	cout<<n<<endl;
	
	if(n==2){
		cout<<n<<"=2(1)"<<endl;
	}else{
		int* result = findNum(n);
		calResult(n, result);
	}
	
	return 0;
}

int* findNum(int n)
{	
	int bottom = (int)sqrt(n);
	list* head;
	head = new list;
	head->num = 2;
	head->next = nullptr;
	
	int total = 1;
	
	int flag = 1;
	
	list* p;
	p = head;
	
	for(int i = 3;i<=bottom;i++){
		flag = 1;
		for(int j = 0;j<total;j++){
			if(!(i%(p->num))){
				flag = 0;
				break;
			}
		}
		if(flag){
			list* newNode;
			newNode = new list;
			newNode->num = i;
			newNode->next = nullptr;
			p->next = newNode;
			total++;
			p = p->next; 
			cout<<i<<endl; 
		}
	}
	
	p = head;
	
	int* result;
	result = new int [total+1];
	
	for(int i = 1;i<total+1;i++){
		result[i] = p->num;
		p = p->next;
	}
	result[0] = total;
	
	p = head;
	list* q;
	q = p;
	
	if(p->next!=nullptr){
		p = p->next;
		delete q;
		q = p;
	}
	
	return result;
}

void calResult(int n, int* result)
{
	cout<<n<<"=";
	int cnt = 1;
	int time = 0;
	int flag = 1;
	
	while(cnt<=result[0] and n>1){
		time = 0;
		while(!(n%result[cnt])){
			time++;
			n = n/result[cnt];
		}
		if(time!=0){
			cout<<result[cnt]<<"("<<time<<")";
			flag = 0;
		}
		cnt++;
	}
	if(flag){
		cout<<n<<"(1)";
	}
	
	cout<<endl;
}
