#include<iostream>

using namespace std;

struct list{
    char number;
    list* previous;
    list* next;
};

struct linearList{
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
    }

    return myList;
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
    
    while(p1->number!=-1 or p2->number!=-1){
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
            p1 = p1->previous;
            p2 = p2->previous;
        }
    }

    if(add==1){
        previousNode = newNode;
        newNode = new list;

        newNode->number = '1';
        newNode->next = previousNode;
        newNode->previous = totalList->head;
        totalList->head->next = newNode;
    }

    return totalList;
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

int main()
{
    linearList* myList1 = create();
    linearList* myList2 = create();
    linearList* totalList = sum(myList1, myList2);
    printList(totalList);
    del(myList1);
    del(myList2);
    del(totalList);

    return 0;
}
