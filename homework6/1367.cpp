#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 1000000+10;
const int power = 30;

int myData[maxn][2] = {0};
int pos = 0;
int maxDiff = 0;

void insert(int a)
{
	int posA = 0;
	int number = 0;
	for(int i = power;i>=0;i--){
		number = (a>>i)&1;
		if(myData[posA][number]==0){
			myData[posA][number] = ++pos;
		}
		posA = myData[posA][number];
	}
}

void initialize(int n)
{
	int p = 0;
	for(int i = 0;i<n;i++){
		cin>>p;
		insert(p);
	}
}

void findInsert(int b)
{
	int pos = 0;
	int number = 0;
	int total = 0;
	for(int i = power;i>=0;i--){
		number = (b>>i)&1;
		if(myData[pos][number==0]!=0){
			total+=(1<<i);
			pos = myData[pos][number==0];
		}else{
			pos = myData[pos][number];
		}
	}
	if(total>maxDiff){
		maxDiff = total;
	}
}

void find(int n)
{
	int p = 0;
	for(int i = 0;i<n;i++){
		cin>>p;
		findInsert(p);
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int sizeA, sizeB;
	cin>>sizeA>>sizeB;
	
	initialize(sizeA);

	find(sizeB);
	
	cout<<maxDiff<<endl;

	cout<<flush;
	return 0;
} 
