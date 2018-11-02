#include <iostream>

using namespace std;

const int maxn = 100000+5;
int myData[maxn] = {0};

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int m = 0, n = 0;
	cin>>n>>m;
	for(int i = 0;i<n;i++){
		cin>>myData[i];
	}
	
	int left = 0;
	int right = 0;
	int add = 0;
	long long total = 0;
	
	char operation = 0;
	for(int i = 0;i<m;i++){
		cin>>operation;
		if(operation == 'C'){
			cin>>left>>right>>add;
			left--;right--;
			for(int j = left;j<right+1;j++){
				myData[j]+=add;
			}
		}else if(operation=='Q'){
			total = 0;
			cin>>left>>right;
			left--;right--;
			for(int j = left;j<right+1;j++){
				total+=myData[j];
			}
			cout<<total<<'\n';
		}
	}
}
