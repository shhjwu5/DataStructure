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
	int mid = (begin+end)/2;
	if(n<data[begin]){
		pos = begin;
	}else if(n>data[end]){
		pos = end+1;
	}else if(n<=data[end] and n>data[end-1]){
		pos = end;
	}else if(n<data[mid]){
		pos = find(data, begin, mid, n);
	}else if(n>data[mid]){
		pos = find(data, mid, end, n);
	}else{
		pos = mid;
	}
	
	return pos;
}
