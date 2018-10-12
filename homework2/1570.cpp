#include<iostream>
#include<cmath>

using namespace std;

int pos(int n, const int* data, int begin, int end);

int main()
{
   	int n = 0, m = 0;
   	cin>>n>>m;
   	
   	int* data = new int [n];
   	int* favor = new int [m];
   	
   	for(int i = 0;i<n;i++){
   		cin>>data[i];
	}
	for(int i = 0;i<m;i++){
		cin>>favor[i];
	}
	
	int p = 0;
	
	for(int i = 0;i<m;i++){
		p = pos(favor[i],data,0,n-1);
		cout<<n-p<<'\n';
	}
	
  	return 0;
}

int pos(int n, const int* data, int begin, int end)
{
	if(n<data[begin]){
		return begin;
	}else if(n>=data[end]){
		return end+1;
	}
	int left = begin;
	int right = end;
	int mid = 0;
	while(left<=right){
		mid = (left+right)/2;
		if(n == data[mid]){
			return mid+1;
		}else if(n<data[mid]){
			right = mid-1;
		}else if(n>data[mid]){
			left = mid+1;
		}
	}
	
	if(n<data[right]){
		return right;
	}else{
		return left;
	}
}
