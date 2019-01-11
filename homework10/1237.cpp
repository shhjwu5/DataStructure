#include <iostream>
#include <cstdio> 

using namespace std;
const int maxn = 100000+10;

template<class T>
class PriorQueue{
private:
	int currentSize;
	T *array;
public:
	PriorQueue(){array = new T[maxn];currentSize = 0;};
	~PriorQueue(){delete [] array;};
	bool isEmpty() const {return currentSize == 0;};
	void enQueue(const T &x);
	T deQueue();
	T getHead() const {return array[1];};
private:
	void percolateDown(int hole); 
};

template<class T>
void PriorQueue<T>::enQueue(const T &x)
{
	currentSize++;
	int hole = currentSize;
	
	while(hole>1 and x.semester<array[hole/2].semester){
		array[hole] = array[hole/2];
		hole/=2;
	}
	array[hole] = x;
}

template<class T>
T PriorQueue<T>::deQueue()
{
	T minItem = array[1];
	array[1] = array[currentSize--];
	percolateDown(1);
	return minItem;
} 

template<class T>
void PriorQueue<T>::percolateDown(int hole)
{
	int child;
	T tmp = array[hole];
	
	while(hole*2<=currentSize){
		child = hole*2;
		if(child!=currentSize and array[child+1].semester<array[child].semester){
			child++;
		}
		if(array[child].semester<tmp.semester){
			array[hole] = array[child];
		}else{
			break;
		}
		hole = child;
	}
	
	array[hole] = tmp;
}

struct node{
	int number;
	node* next;
	
	node(int num):number(num),next(NULL){}
	~node(){if(next!=NULL){delete next;}}
};

struct NSPair{
	int number;
	int semester;
	
	NSPair():number(0),semester(0){}
	NSPair(int i, int t):number(i),semester(t){}
};

int preLearn[maxn] = {0};
node* classes[maxn] = {NULL};

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	int n,m;
	cin>>n>>m;
	
	for(int i = 1;i<n+1;i++){classes[i] = new node(i);}
	int now,pre;
	node* tmp;
	for(int i = 1;i<m+1;i++){
		cin>>now>>pre;
		preLearn[now]++;
		tmp = new node(now);
		tmp->next = classes[pre]->next;
		classes[pre]->next = tmp;
	}
	
	int result = 1;
	PriorQueue<NSPair> que;
	for(int i = 1;i<n+1;i++){
		if(preLearn[i]==0){que.enQueue(NSPair(i,result));preLearn[i]--;}
	}
	
	while(!que.isEmpty()){
		NSPair t = que.deQueue();
		if(result<t.semester){result++;}
		node* p = classes[t.number]->next;
		while(p!=NULL){
			preLearn[p->number]--;
			if(preLearn[p->number]==0){
				que.enQueue(NSPair(p->number,result+1));
			}
			p = p->next;
		}
	}
	
	cout<<result<<'\n';
	
	cout<<flush;
	return 0;
}

