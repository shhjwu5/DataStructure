#include <iostream>
#include <cstdio> 

using namespace std;

int main()
{
	freopen("input.in", "r", stdin);
	freopen("output.out", "w", stdout);
	
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int x;
	for (int i = 0;i<3;i++){
		cin>>x;
		cout<<x<<'\n';
	}
	cout<<flush;
	
	fclose(stdin);
	fclose(stdout);
	
	return 0;
}
