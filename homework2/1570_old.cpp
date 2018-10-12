#include <iostream>
#include <cmath>

using namespace std;

int find(int*, int, int, int);

int main()
{
	int n = 0, t = 0;
	cin>>n>>t;
	
	int* atHand;
	atHand = new int [n];
	for(int i = 0;i<n;i++){
		cin>>atHand[i];
	}
	int* favor;
	favor = new int [t];
	for(int i = 0;i<t;i++){
		cin>>favor[i];
	}
	
	int pos = 0;
	int result = 0;
	
	for(int j = 0;j<t;j++){
		pos = find(atHand, 0, n-1, favor[j]);
		if(favor[j]<atHand[pos]){
			result = n - pos;
		}else if(favor[j]>atHand[pos]){
			result = n - pos;
		}else{
			result = n - pos - 1;
		}
		cout<<result<<endl;
	}
	
	delete atHand;
	delete favor;
	return 0;
}

int find(int* data, int begin, int end, int n)
{
	int pos = 0;
	int sep = (int)sqrt(end-begin);
	if(n<data[begin]){
		pos = begin;
	}else if(n>data[end]){
		pos = end+1;
	}else if(n<=data[end] and n>data[end-1]){
		pos = end;
	}else{
		for(int i = 0;i<sep;i++){
			if(n>data[begin+sep*i] and n<=data[begin+sep*(i+1)]){
				pos = find(data, begin+sep*i,begin+sep*(i+1),n);
			}
		}
		if(pos == 0){
			pos = find(data, begin+sep*sep,end,n);
		}
	}
	
	return pos;
}
