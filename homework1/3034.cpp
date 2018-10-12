#include <iostream>
#include <cmath>

using namespace std;

int isPrime(int n)
{
	int limit = sqrt(n);
	int flag = 1;
	for(int i = 2;i<limit+1;i++){
		if(n%i==0){
			flag = 0;
			break;
		}
	}
	
	return flag;
} 

int main()
{
    int n = 0;
    cin>>n;
    
    int gap = 0;
    int i = n;
    int j = n;
    while(!isPrime(i)){
    	i--;
    	gap++;
	}
	while(!isPrime(j)){
		j++;
		gap++;
	}
	
	cout<<gap<<endl;
	
  	return 0;
}
