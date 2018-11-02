#include <iostream>

using namespace std;

const int maxn = 1000+5;
char a[maxn] = {0};
char b[maxn] = {0};
int check[maxn][maxn] = {0};

int main()
{
	int sizeA = 0;
	int sizeB = 0;
	cin>>sizeA>>sizeB;
	
	cin>>a;
	cin>>b;
	
	for(int row = 0;row<sizeA;row++){
		check[row][0] = 0;
	}
	for(int col = 0;col<sizeB;col++){
		check[0][col] = 0;
	}
	
	for(int i = 1;i<sizeA+1;i++){
		for(int j = 1;j<sizeB+1;j++){
			if(a[i-1]==b[j-1]){
				check[i][j] = check[i-1][j-1]+1;
			}else if(check[i][j-1]>check[i-1][j]){
				check[i][j] = check[i][j-1];
			}else{
				check[i][j] = check[i-1][j];
			}
		}
	}
	
	cout<<check[sizeA][sizeB]<<endl;
	cout<<flush;
	return 0;
}
