#include <iostream>

using namespace std;

int sortOnce(int** favor, int first, int end, int pos)
{
	int i = first, j = end;
	while (i<j){
		while(i<j and favor[i][pos]<=favor[j][pos]){
			j--;
		}
		if(i<j){
			int* tmp = favor[i];
			favor[i] = favor[j];
			favor[j] = tmp;
		}
		while(i<j and favor[i][pos]<=favor[j][pos]){
			i++;
		}
		if(i<j){
			int* tmp = favor[i];
			favor[i] = favor[j];
			favor[j] = tmp;
		}
	}
	
	return i;
} 

int Sort(int** data, int first, int end, int pos)
{
	if(first<=end){
		int middle = sortOnce(data, first, end, pos);
		Sort(data, first, middle-1, pos);
		Sort(data, middle+1, end, pos);
	}
}

int main()
{
   	int n = 0, m = 0;
   	cin>>n>>m;
   	
   	int* data;
   	data = new int [n];
   	for(int i = 0;i<n;i++){
   		cin>>data[i];	
	}
   	
	int** favor;
   	favor = new int* [m];
	for(int i = 0;i<m;i++){
		favor[i] = new int [3];
		cin>>favor[i][0];
		favor[i][1] = i;
	}
	
	Sort(favor, 0, m-1, 0);
	
	int j = 0;
	for(int i = 0;i<m;i++){
		while(favor[i][0]>=data[j] and j<n){
			j++;
		}
		
		if(j>=n){
			favor[i][2] = 0;
		}else{
			favor[i][2] = n-j;
		}
	}
	
	int* result;
	result = new int [m];
	for(int i = 0;i<m;i++){
		result[favor[i][1]] = favor[i][2];
	} 
	
	for(int i = 0;i<m;i++){
		cout<<result[i]<<endl;
	}
	
	delete result;
	delete data;
	for(int i = 0;i<m;i++){
		delete favor[i];
	}
	delete favor;
	
  	return 0;
}
