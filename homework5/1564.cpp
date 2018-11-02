#include <iostream>

using namespace std;

const int maxn = 8;
int myData[8][8];
int tmp[8][8] = {0};

int add[4][2] = {0,1,0,-1,-1,0,1,0};
int minResult = 1e9;

void find(int a, int b, int c, int d, int state, int result){
	tmp[a][b] = 1;
	result+=state*myData[a][b];
	if(a==c and b==d){
		if(result<minResult){
			minResult = result;
		}
		tmp[a][b] = 0;
		return;
	}
	state = (state*myData[a][b])%4+1;
	for(int i = 0;i<4;i++){
		if(myData[a+add[i][0]][b+add[i][1]]!=0){
			if(tmp[a+add[i][0]][b+add[i][1]]==0){
				find(a+add[i][0],b+add[i][1],c,d,state,result);
			}
		}
	}
	tmp[a][b] = 0;
	return;
}

int main()
{
	for(int i = 0;i<8;i++){
		myData[i][0] = myData[i][7] = 0; 
	}
	for(int i = 1;i<7;i++){
		myData[0][i] = myData[7][i] = 0;
	}
	
	int n = 0;
	cin>>n;
	for(int i = 0;i<n;i++){
		for(int j = 1;j<7;j++){
			for(int k =1;k<7;k++){
				cin>>myData[j][k];
			}
		}
		
		int a = 0, b = 0, c = 0, d = 0;
		cin>>a>>b>>c>>d;
		a++;b++;c++;d++;
		
		int result = 0;
		find(a,b,c,d,0,result);
	}
	
	cout<<minResult<<endl;
	
	cout<<flush;
	return 0;
}
