#include <iostream>
 
using namespace std;
 
int main()
{
	int n = 0, m = 0;
	cin>>n>>m;
	
	int** building;
	int** dis;

	building = new int* [n+2];
	dis = new int* [n+2];
	
	for(int i = 0;i<n+2;i++){
		building[i] = new int [m+2];
		dis[i] = new int [m+2];
	}
	
	for(int i = 0;i<n+2;i++){
		building[i][0] = 0;
		dis[i][0] = -3;
		
		building[i][m+1] = 0;
		dis[i][m+1] = -3;
	}
	
	for(int j = 0;j<m+2;j++){
		building[0][j] = 0;
		dis[0][j] = -3;
		
		building[n+1][j] = 0;
		dis[n+1][j] = -3;
	}
	
	int a,b,c,d;
	cin>>a>>b>>c>>d;
	
	for(int i = 1;i<n+1;i++){
		for(int j = 1;j<m+1;j++){
			char x;
			cin>>x;
			dis[i][j] = -1;
			if(x=='.'){building[i][j] = 1;}
			else if(x=='|'){building[i][j] = 2;}
			else if(x=='-'){building[i][j] = 3;}
			else if(x=='*'){building[i][j] = 4;dis[i][j] = -3;}
		}
	}
	
	dis[a][b] = 0;
	
	int flag = 1;
	int cnt = 0;
	while(flag and dis[c][d]==-1){
		flag = 0;
		for(int i = 1;i<n+1;i++){
			for(int j = 1;j<m+1;j++){
				if(dis[i][j]==cnt){
					if(dis[i-1][j]==-1 and (building[i][j]==1 or building[i][j]==2) and (building[i-1][j]!=4 and building[i-1][j]!=3)){
						dis[i-1][j] = cnt+1;
						flag = 1;
					}
					if(dis[i+1][j]==-1 and (building[i][j]==1 or building[i][j]==2) and (building[i+1][j]!=4 and building[i+1][j]!=3)){
						dis[i+1][j] = cnt+1;
						flag = 1;
					}
					if(dis[i][j-1]==-1 and (building[i][j]==1 or building[i][j]==3) and (building[i][j-1]!=4 and building[i][j-1]!=2)){
						dis[i][j-1] = cnt+1;
						flag = 1;
					}
					if(dis[i][j+1]==-1 and (building[i][j]==1 or building[i][j]==3) and (building[i][j+1]!=4 and building[i][j+1]!=2)){
						dis[i][j+1] = cnt+1;
						flag = 1;
					}
				}
			}
		}
		cnt++;
	}
	
	if(dis[c][d]>=0){cout<<cnt<<'\n';}
	else{cout<<-1<<'\n';}
	
	return 0;
}
