#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 10000+10;

struct edge{
	int number;
	int length;
	edge* next;
	
	edge(int num):number(num),length(0),next(NULL){}
	edge(int num,int len):number(num),length(len),next(NULL){}
};

struct node{
	int number;
	int distance;
	bool known;
	int howMany;
	node* pre;
	bool inHeap;
	
	node(int num):number(num),distance(1e9),known(false),inHeap(false),howMany(1e9),pre(NULL){}
};

class PriorQueue{
private: 
	int currentSize;
	node** array;
public:
	PriorQueue(){array = new node*[maxn];currentSize = 0;};
	~PriorQueue(){delete [] array;};
	bool isEmpty() const {return currentSize == 0;}
	void enQueue(node* &x);
	node* deQueue();
	node* getHead() const {return array[1];};
	void buildHeap();
private:
	void percolateDown(int hole); 
};

void PriorQueue::enQueue(node* &x)
{
	currentSize++;
	int hole = currentSize;
	
	while(hole>1 and ((x->distance<array[hole/2]->distance) or (x->distance==array[hole/2]->distance and x->howMany<array[hole/2]->howMany))){
		array[hole] = array[hole/2];
		hole/=2;
	}
	array[hole] = x;
}

node* PriorQueue::deQueue()
{
	node* minItem = array[1];
	array[1] = array[currentSize--];
	percolateDown(1);
	return minItem;
} 

void PriorQueue::percolateDown(int hole)
{
	int child;
	node* tmp = array[hole];
	
	while(hole*2<=currentSize){
		child = hole*2;
		if(child!=currentSize and ((array[child+1]->distance<array[child]->distance) or (array[child+1]->distance==array[child]->distance and array[child+1]->howMany<array[child]->howMany))){
			child++;
		}
		if((array[child]->distance<tmp->distance) or (array[child]->distance==tmp->distance and array[child]->howMany<tmp->howMany)){
			array[hole] = array[child];
		}else{
			break;
		}
		hole = child;
	}
	
	array[hole] = tmp;
}

void PriorQueue::buildHeap()
{
	for(int i = currentSize/2;i>0;i--){
		percolateDown(i);
	}
}

edge* point[maxn] = {NULL};
node* myData[maxn] = {NULL};
PriorQueue que;
int allNum[maxn] = {0};
int total = 0;

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	int n,m,start,end;
	cin>>n>>m>>start>>end;
	
	for(int i = 1;i<n+1;i++){point[i] = new edge(i);}
	
	int a,b,p;
	edge* tmp;
	edge* current;
	for(int i = 0;i<m;i++){
		cin>>a>>b>>p;
		tmp = new edge(b,p);
		current = point[a]->next;
		while(current!=NULL and current->number!=b){current = current->next;}
		if(current!=NULL){
			if(current->length>p){current->length = p;}
		}else{
			tmp->next = point[a]->next;
			point[a]->next = tmp;
		}
	}
	
	for(int i = 1;i<n+1;i++){myData[i] = new node(i);}
	myData[start]->distance = 0;
	myData[start]->howMany = 0;
	myData[start]->pre = myData[start];
	que.enQueue(myData[start]);

	node* now;
	while(!que.isEmpty()){
		now = que.deQueue();
		now->known = true;
		for(edge* p = point[now->number]->next;p!=NULL;p = p->next){
			if(!myData[p->number]->known){
				if(myData[p->number]->distance>now->distance+p->length){
					myData[p->number]->distance = now->distance+p->length;
					myData[p->number]->howMany = now->howMany+1;
					myData[p->number]->pre = now;
					if(myData[p->number]->inHeap==false){
						que.enQueue(myData[p->number]);
						myData[p->number]->inHeap = true;
					}else{
						que.buildHeap();
					}
				}else if(myData[p->number]->distance==now->distance+p->length and myData[p->number]->howMany>now->howMany+1){
					myData[p->number]->howMany = now->howMany+1;
					myData[p->number]->pre = now;
					if(myData[p->number]->inHeap==false){
						que.enQueue(myData[p->number]);
						myData[p->number]->inHeap = true;
					}else{
						que.buildHeap();
					}
				}
			}
		}
	}
	
	cout<<myData[end]->distance<<'\n';
	node* t = myData[end];
	for(int i = 0;i<myData[end]->howMany;i++){
		allNum[total++] = t->number;
		t = t->pre; 
	}
	allNum[total++] = start;
	for(int i = total-1;i>=0;i--){
		cout<<allNum[i]<<' ';
	}
	cout<<endl;
	
	cout<<flush;
	return 0;
}
