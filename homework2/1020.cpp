#include <iostream>
#include <cmath>

using namespace std;

void calResult(int);

int main()
{
	int n = 0;
	cin>>n; 
	
	if(n==2){
		cout<<n<<"=2(1)"<<endl;
	}else{
		calResult(n);
	}
	
	return 0;
}

void calResult(int n)
{	
	int* odd;
	odd = new int [(int)sqrt(n)];
	
	odd[0] = 2;
	
	int total = 0;
	int cnt = 3;
	int time = 0;
	int flag = 0;
	
	cout<<n<<"=";
	
	while(n!=1){
		time = 0;
		while(!(n%odd[total])){
			time++;
			n = n/odd[total];
		}
		if(time){
			cout<<odd[total]<<"("<<time<<")";
		}
		
		flag = 0;
		
		while(flag != 1 and n!=1){
			flag = 1;
			int i = 0;
			while(i<=total and odd[i]<=int(sqrt(cnt))){
				if(!(cnt%odd[i])){
					flag = 0;
					break;
				}
				i++;
			}
			if(flag){
				total++;
				odd[total] = cnt;
			}
			if(cnt++>=sqrt(n)){
				cnt = n;
			};
		}
	}
	
	cout<<endl;
	
	delete odd;
}
