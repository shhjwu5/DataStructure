#include<iostream>

using namespace std;

int main()
{
    int n = 0;
    cin>>n; 
	
	int p = 0;
	int* m;
	m = new int [n-1];
	
	for(int i = 0;i<n-1;i++){
		cin>>m[i];
	}
	
    for(int i = 2;i<=n;i++)
    {
        p = (p+m[n-i])%i;
    }
    cout<<p+1<<endl;;
	
	return 0;
}
