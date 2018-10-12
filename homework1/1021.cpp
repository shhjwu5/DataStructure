#include <iostream>
#include <iomanip>

using namespace std;

void drawHeight(int** height, int start, int end, int firstNum)
{
	int cnt;
	cnt = firstNum;
	for(int i = start;i<=end;i++){
		height[start][i] = cnt;
		cnt++;
	}
	for(int i = start+1;i<=end;i++){
		height[i][end] = cnt;
		cnt++;
	}
	for(int i = end-1;i>=start;i--){
		height[end][i] = cnt;
		cnt++;
	}
	for(int i = end-1;i>=start+1;i--){
		height[i][start] = cnt;
		cnt++;
	}
	
	if((start+1)<=(end-1)){
		drawHeight(height, start+1,end-1,cnt);
	}
}

int main()
{
    int n = 0;
	cin>>n;
	
	int** height;
	height = new int* [n];
	for(int i = 0;i<n;i++){
		height[i] = new int[n];
	}
	
	drawHeight(height,0,n-1,1);
	
	for(int i = 0;i<n;i++){
		for(int j = 0;j<n;j++){
			cout<<setw(6)<<height[i][j];
		}
		cout<<endl;
	}
	
	for(int i = 0;i<n;i++){
		delete height[i];
	}
	delete [] height;

    return 0;
}
