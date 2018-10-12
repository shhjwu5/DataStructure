#include<iostream>
#include<cmath>

using namespace std;

struct list{
    char number;
    list* previous;
    list* next;
};

struct linearList{
	int length = 0;
    list* head;
    list* tail;
};

linearList* create()
{
    linearList* myList;
    myList = new linearList;
    myList->head = new list;
    myList->head->number = -1;
    myList->head->previous = nullptr;
    myList->tail = new list;
    myList->tail->number = -2;
    myList->tail->next = nullptr;

    myList->tail->previous = myList->head;
    myList->head->next = myList->tail;
    
    list* newNode = myList->head;
    list* previousNode;
    char k = getchar();
    while(k>47 and k<58){
        previousNode = newNode;
        newNode = new list;
        newNode->number = k;
        newNode->next = myList->tail;
        newNode->previous = previousNode;
        previousNode->next = newNode;
        myList->tail->previous = newNode;
        k = getchar();
        myList->length++;
    }

    return myList;
}

linearList* createEmpty()
{
    linearList* myList;
    myList = new linearList;
    myList->head = new list;
    myList->head->number = -1;
    myList->head->previous = nullptr;
    myList->tail = new list;
    myList->tail->number = -2;
    myList->tail->next = nullptr;
    
    list* newNode;
    newNode = new list;

    newNode->number = '0';
    newNode->next = myList->tail;
    newNode->previous = myList->head;

	myList->head->next = newNode;
	myList->tail->previous = newNode;
    myList->length = 1;

    return myList;
}


void addZero(linearList* myList)
{
	list* p;
	p = new list;
	p->number = '0';
	p->next = myList->tail;
	p->previous = myList->tail->previous;
	myList->tail->previous->next = p;
	myList->tail->previous = p;
	
	myList->length = myList->length + 1;
}

void delOne(linearList* myList)
{
	list* p;
	p = myList->tail->previous;
	myList->tail->previous = myList->tail->previous->previous;
	myList->tail->previous->next = myList->tail;
	
	delete p;
	
	myList->length = myList->length - 1;
}

void del(linearList* myList)
{
    list* p;
    list* q;
    p = myList->head;
    while (p==myList->tail){
        q = p;
        p = p->next;
        delete q;
        cout<<p->number<<endl;
    }
}

void printList(linearList* totalList)
{
    list* p = totalList->head->next;
    while(p->next!=nullptr){
        putchar(p->number);
        p = p->next;
    }
    cout<<endl;
}

linearList* sum(linearList* myList1, linearList* myList2)
{
    linearList* totalList;
    totalList = new linearList;
    totalList->head = new list;
    totalList->head->number = -1;
    totalList->head->previous = nullptr;
    totalList->tail = new list;
    totalList->tail->number = -2;
    totalList->tail->next = nullptr;

    totalList->tail->previous = totalList->head;
    totalList->head->next = totalList->tail;
    
    list* newNode = totalList->tail;
    list* previousNode;

    list* p1 = myList1->tail->previous;
    list* p2 = myList2->tail->previous;

    int add = 0;
    
    int cnt = 0;
    
    while(p1->number!=-1 or p2->number!=-1){
    	cnt++;
        if(p2->number==-1){
            previousNode = newNode;
            newNode = new list;
            int a = int(p1->number-48);
            char newNum = (a+add)%10+48;
            add = (a+add)/10;

            newNode->number = newNum;
            newNode->next = previousNode;
            newNode->previous = totalList->head;
            totalList->head->next = newNode;
            previousNode->previous = newNode;
            p1 = p1->previous;
        }
        else if(p1->number==-1){
            previousNode = newNode;
            newNode = new list;
            int b = int(p2->number-48);
            char newNum = (b+add)%10+48;
            add = (b+add)/10;

            newNode->number = newNum;
            newNode->next = previousNode;
            newNode->previous = totalList->head;
            totalList->head->next = newNode;
            previousNode->previous = newNode;
            p2 = p2->previous;
        }
        else{
            previousNode = newNode;
            newNode = new list;
            int a = int(p1->number-48);
            int b = int(p2->number-48);
            char newNum = (a+b+add)%10+48;
            add = (a+b+add)/10;

            newNode->number = newNum;
            newNode->next = previousNode;
            newNode->previous = totalList->head;
            totalList->head->next = newNode;
            previousNode->previous = newNode;
            p1 = p1->previous;
            p2 = p2->previous;
        }
    }

    if(add==1){
    	cnt++;
        previousNode = newNode;
        newNode = new list;

        newNode->number = '1';
        newNode->next = previousNode;
        newNode->previous = totalList->head;
        previousNode->previous = newNode;
        totalList->head->next = newNode;
    }

	totalList->length = cnt;

    return totalList;
}

int isGreater(linearList* list1, linearList* list2)
{
	int flag = 0;
	if (list1->length>list2->length){
		flag = 1;
	}else if(list1->length<list2->length){
		flag = 0;
	}else{
		list* p1 = list1->head->next;
		list* p2 = list2->head->next;
		while(p1->next!=nullptr){
			if(p1->number>p2->number){
				flag = 1;
				break;
			}
			if(p1->number<p2->number){
				flag = 0;
				break;
			}
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	
	return flag;
} 

int main()
{
    linearList* myList1 = create();
    linearList* myList2 = create();
    
	int cnt = 0;
	while(!isGreater(myList2, myList1)){
		addZero(myList2);
		cnt++;
	}
	delOne(myList2);
	cnt--;
	
	linearList* totalList = createEmpty();
	linearList* previousList = createEmpty();
	
	int time = 0;
	
	int tmp = 1;
	
	for (int i = cnt;i>=0;i--){
		tmp = 0;
		
		while(!isGreater(totalList, myList1)){
			previousList = totalList;
			totalList = sum(totalList, myList2);
			tmp++;
		}
		tmp--;
		
		time += tmp*pow(10, i);
		totalList = previousList;
		delOne(myList2);
	}
	
	cout<<time<<endl; 
	
    del(myList1);
    del(myList2);
    del(totalList);
    del(previousList);

    return 0;
}
