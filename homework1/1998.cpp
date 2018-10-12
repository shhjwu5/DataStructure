#include <iostream>
#include <cmath>

using namespace std;

int sortOnce(int* data, int first, int end)
{
	int i = first, j = end;
	while (i<j){
		while(i<j and data[i]<=data[j]){
			j--;
		}
		if(i<j){
			int tmp = data[i];
			data[i] = data[j];
			data[j] = tmp;
		}
		while(i<j and data[i]<=data[j]){
			i++;
		}
		if(i<j){
			int tmp = data[i];
			data[i] = data[j];
			data[j] = tmp;
		}
	}
	
	return i;
} 

void Sort(int* data, int first, int end)
{
	if(first<=end){
		int middle = sortOnce(data, first, end);
		Sort(data, first, middle-1);
		Sort(data, middle+1, end);
	}
}

int main()
{
   	int n = 0;
   	cin>>n;
   	
   	int* data;
   	data = new int [n];
	for(int i = 0;i<n;i++){
		cin>>data[i];
	}
	
	Sort(data, 0, n-1);
	
	int total = 0;
	for(int i = 0;i<n;i++){
		total = total + abs(data[i]-data[n/2]);	
	}
	
	cout<<total<<endl;
	
	delete data;
	
  	return 0;
}
