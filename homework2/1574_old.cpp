#include<iostream>
 
using namespace std;
 
int mod(int k, int n)
{  
    int d = 1;
    
    for(int i = 0;i<k;i++){
		d = (d*10)%n;
	}
	
    return d;  
} 
 
int main()
{
	int n = 0, m = 0, x = 0;
	int k;
	cin>>n>>m>>k>>x;
	
	int result = 1;
	result = mod(k,n);
	
	result = (result*m+x)%n;
	
	cout<<result<<endl;
	
	return 0;
}
