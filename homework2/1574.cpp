#include<iostream>

using namespace std;

int mod(int k, int n)
{  
    int ans=1, base=10;
    while(k!=0){
    	if(k%2){
    		ans = (ans*base)%n;
		}
    	base = (base*base)%n; 
    	k = k/2;
	}
	
    return ans;  
} 

int main()
{
	int n = 0, m = 0, x = 0;
	int k = 0;
	cin>>n>>m>>k>>x;
	
	int result = 1;
	result = mod(k,n);
	
	result = (result*m+x)%n;
	
	cout<<result<<endl;
	
	return 0;
}
