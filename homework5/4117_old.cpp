#include <iostream>
#include <cmath>

using namespace std;

const in maxn 100000+5;
int A[maxn] = {0};
int n = 0;
int N = 0;
int Sum[maxn<<2] = {0};
int Add[maxn<<2] = {0};

void build()
{
	N = 1;
	while(N<n+2){
		N<<=1;
	}
	
	for(int i = 0;i<n;i++){
		Sum[N+i] = A[i];
	}
	
	for(int i = N-1;i>0;i--){
		Sum[i] = Sum[i<<1]+Sum[i<<1|1];
		Add[i] = 0;
	}
} 

void updatePoint(int pos, int val)
{
	for(int s = N+pos;s;s>>=1){
		Sum[s]+=val;
	}
}

int query(int left, int right)
{
	int ans = 0;
	for(int s=N+left-1,t=N+right+1;s^t^1;s>>=1,t>>=1){
		if(~s&1){
			ans+=Sum[S^1];
		}
		if(t&1){
			ans+=Sum[t^1];
		}
	}
	
	return ans;
}

void updateInter(int left, int right, int val)
{
	int s = 0, t = 0, leftNumber = 0, rightNumber = 0, x = 1; 
	for(s=N+left-1,t=N+right+1;s^t^1;s>>=1,t>>=1,x<<=1){
		Sum[s]+=val*leftNumber;
		Sum[t]+=val*rightNumber;
		if(~s&1){
			Add[s^1]+=val;
			Sum[s^1]+=val*x;
			leftNumber+=x; 
		}
		if(t&1){
			Add[t^1]+=val;
			Sum[t^1]+=val*x;
			rightNumber+=x; 
		}
	}
	
	for(;s;s>>=1;t>>=1){
		Sum[s]+=val*leftNumber;
		Sum[t]+=val*rightNumber;
	}
} 

int main()
{
	cin>>n;
	for(int i = 0;i<n;i++){
		cin>>A[i];
	}
	
	 
	
	cout<<flush;
	return 0;
} 
