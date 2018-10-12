#include <iostream>

using namespace std;

int step(int, int, int);

int main()
{
	int n = 0, x = 0, y = 0;
	cin>>n>>x>>y;

	cout<<step(n, x, y)-1<<endl;;
	
	return 0;
}

int step(int n, int x, int y)
{
	if(x==1){
		return y;
	}else if(y==1){
		return (n-1)*3+(n-x+1); 
	}else if(x==n){
		return (n-1)*2+(n-y+1);
	}else if(y==n){
		return (n-1)+x;
	}else{
		return (n-1)*4+step(n-2, x-1, y-1);
	}
}
