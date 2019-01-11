#include <iostream>
#include <cstdio> 

using namespace std;

const int maxn = 1000+10;

struct node{
	int level;
	int number;
	
	node():level(0),number(0){}
	node(int lev, int num):level(lev),number(num){}
};

class priorQueue{
private:	
	int currentSize;
	node* array;
public:
	priorQueue();
	~priorQueue();
	bool isEmpty() const;
	void enQueue(const node &x);
	int deQueue();
private:
	void percolateDown(int hole); 
};

priorQueue::priorQueue()
{
	array = new node[maxn];
	currentSize = 0;
}

priorQueue::~priorQueue()
{
	delete [] array;
}

bool priorQueue::isEmpty() const
{
	return currentSize == 0;
}

void priorQueue::enQueue(const node &x)
{
	currentSize++;
	int hole = currentSize;
	
	while(hole>1 and x.level>array[hole/2].level){
		array[hole] = array[hole/2];
		hole/=2;
	}
	array[hole] = x;
}

int priorQueue::deQueue()
{
	node minItem = array[1];
	array[1] = array[currentSize--];
	percolateDown(1);
	return minItem.number;
} 

void priorQueue::percolateDown(int hole)
{
	int child;
	node tmp = array[hole];
	
	while(hole*2<=currentSize){
		child = hole*2;
		if(child!=currentSize and array[child+1].level>array[child].level){
			child++;
		}
		if(array[child].level>tmp.level){
			array[hole] = array[child];
		}else{
			break;
		}
		hole = child;
	}
	
	array[hole] = tmp;
}

node* people[maxn] = {NULL};

bool known[maxn][maxn] = {0};
bool ask[maxn] = {0};

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
		
	int n,k;
	cin>>n>>k;
	
	priorQueue que;
	
	int x = 0;
	for(int i = 1;i<n+1;i++){
		cin>>x;
		people[i] = new node(x,i);
	}
	
	for(int i = 0;i<k;i++){
		cin>>x;
		que.enQueue(*(people[x]));
		ask[x] = 1;
	}
	
	for(int i = 1;i<n+1;i++){
		for(int j = 1;j<n+1;j++){
			cin>>known[i][j];
		}
	}
	
	int now = 0;
	while(que.isEmpty()!=1){
		now = que.deQueue();
		cout<<now<<'\n';
		for(int i = 1;i<n+1;i++){
			if(ask[i]==0 and known[now][i]==1){
				que.enQueue(*(people[i]));
				ask[i] = 1;
			}
		}
	}
	
	cout<<flush;
	return 0;
}
