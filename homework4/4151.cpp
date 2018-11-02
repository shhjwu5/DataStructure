#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 1000000+5;

int myData[maxn] = {0}; 
int allNumber[maxn] = {0};

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int n = 0;
	cin>>n;

	int total = 0;
	for(int i = 0;i<n;i++){
		cin>>total;
		for(int j = 1;j<total+1;j++){
			cin>>allNumber[j];
		}
		myData[0] = -1;
		myData[1] = 1;
		
		int idxAllNumber = 1;
		int idxMyData = 1;
		int number = 1;
		int flag = 1;
		while(number<=total){
			if(allNumber[idxAllNumber]==myData[idxMyData] and myData[idxMyData]!=-1){
				idxAllNumber++;
				idxMyData--;
			}else if(allNumber[idxAllNumber]<myData[idxMyData] and myData[idxMyData]!=-1){
				flag = 0;
				break;
			}else{
				number++;
				idxMyData++;
				myData[idxMyData] = number;
			}
		}
		
		if(flag){
			cout<<"Yes"<<endl;
		}else{
			cout<<"No"<<endl;
		}
	}
	
	cout<<flush;

	return 0;
}
