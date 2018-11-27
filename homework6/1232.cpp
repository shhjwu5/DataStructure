#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn = 1000000+10;

struct node{
    int parent;
    int near[4];
    
	node(){
		for(int i = 0;i<4;i++){
			near[i] = 0;
		}
	}
};

node myData[maxn];

int num = 0;
int theStart = 0;
int theEnd = 0;
int theSize = 0;
int totalSize = 0;
int root;

int route[maxn] = {0};
int tail = 0;
bool pass[maxn] = {0};

bool flag;

int findRoot(int a)
{
    int currA = a;
    while(myData[currA].parent>0){
    	currA = myData[currA].parent;	
	}
    return currA;
}

int returnSize(int k)
{
    double ans = 1.0/2+sqrt(1.0+8*k)/2;
    if((int)ans==ans){
    	return ans-1;
	}else{
		return (int)ans;
	}
}

void combine(int a, int b)
{
    int currA = findRoot(a);
	int currB = findRoot(b);
	
    if(currA!=currB)
    {
        if(myData[currA].parent>myData[currB].parent){
			myData[currB].parent+=myData[currA].parent;
			myData[currA].parent = currB;
		}else{
			myData[currA].parent+=myData[currB].parent;
			myData[currB].parent = currA;
		}
    }
}

bool notTogether(int a, int b)
{
    int currA = findRoot(a);
	int currB = findRoot(b);
	 
    return currA!=currB;
}

void dfs()
{
    if(!flag){
        for(int i = 0;i<4;i++){
            if(myData[route[tail]].near[i] and !pass[myData[route[tail]].near[i]]){
                route[tail+1] = myData[route[tail]].near[i];
                tail++;
                pass[route[tail]] = 1;
                if(route[tail]==theEnd){
					flag = true;
					return;
				}
				
                dfs();
                
				if(route[tail]==theEnd){
					flag = true;
					return;
				}
                pass[route[tail]] = 0;
                tail--;
            }
        }
    }
}
 
int main()
{
    int a, b;
    bool mainFlag = true;
    cin>>totalSize>>theStart>>theEnd;
    num = totalSize*(totalSize+1)/2;
    for(int i = 1;i<num+1;i++){
    	myData[i].parent = -1;
	}
	
    while(cin>>a>>b and mainFlag)
    {
        theSize = returnSize(a);
        if(b==0){
        	if(returnSize(a-theSize)==theSize-1){
                combine(a,a-theSize);
                myData[a].near[0] = a-theSize;
                myData[a-theSize].near[3] = a;
            }
		}else if(b==1){
			if(returnSize(a-theSize+1)==theSize-1){
                combine(a,a-theSize+1);
                myData[a].near[1] = a-theSize+1;
                myData[a-theSize+1].near[2] = a;
            }
		}else if(b==2){
			if(returnSize(a+theSize)<=totalSize){
                combine(a, a+theSize);
                myData[a].near[2] = a+theSize;
                myData[a+theSize].near[1] = a;
            }
		}else if(b==3){
			if(returnSize(a+theSize+1)<=totalSize){
                combine(a,a+theSize+1);
            	myData[a].near[3]  = a+theSize+1;
                myData[a+theSize+1].near[0] = a;
            }
		}
                
        mainFlag = notTogether(theStart, theEnd);
    }
    
    root = findRoot(theStart);
    route[++tail] = theStart;
    
    pass[theStart] = 1;
    flag = false;
	
	dfs();
	
    for(int i = 1; i<tail+1;i++){
    	cout<<route[i]<<' ';
	}
	cout<<'\n';
    return 0;
}
