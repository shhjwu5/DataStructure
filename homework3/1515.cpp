#include <iostream>
 
using namespace std;
 
int main()
{
	int cnt2 = 0;
	int cnt3 = 0;	
	
	int n = 0, m = 0;
	cin>>n>>m;
	
	int** building;
	int** dis2;
	int** dis3;

	building = new int* [m+2];
	dis2 = new int* [m+2];
	dis3 = new int* [m+2];
	
	for(int i = 0;i<m+2;i++){
		building[i] = new int [n+2];
		dis2[i] = new int [n+2];
		dis3[i] = new int [n+2];
	}
	
	for(int i = 0;i<m+2;i++){
		building[i][0] = -3;
		dis2[i][0] = -3;
		dis3[i][0] = -3;
		
		building[i][n+1] = -3;
		dis2[i][n+1] = -3;
		dis3[i][n+1] = -3;
	}
	
	for(int j = 0;j<n+2;j++){
		building[0][j] = -3;
		dis2[0][j] = -3;
		dis3[0][j] = -3;
		
		building[m+1][j] = -3;
		dis2[m+1][j] = -3;
		dis3[m+1][j] = -3;
	}
	
	for(int i = 1;i<m+1;i++){
		for(int j = 1;j<n+1;j++){
			cin>>building[i][j];
			if(building[i][j]==2){
				dis2[i][j] = 0;
				dis3[i][j] = -1;
			}else if(building[i][j]==3){
				dis3[i][j] = 0;
				dis2[i][j] = -1;
			}else if(building[i][j]==4){
				dis2[i][j] = -1;
				dis3[i][j] = -1;
				cnt2++;
				cnt3++;
			}else if(building[i][j]==1){
				dis2[i][j] = -2;
				dis3[i][j] = -2;
			}else{
				dis2[i][j] = -1;
				dis3[i][j] = -1;
			}
		}
	}
	
	int flag = 1;
	int cnt = 0;
	while((cnt2>0 or cnt3>0) and flag){
		flag = 0;
		for(int i = 1;i<m+1;i++){
			for(int j = 1;j<n+1;j++){
				if(dis2[i][j]==cnt){
					if(dis2[i-1][j]==-1){
						dis2[i-1][j] = cnt+1;
						flag = 1;
						if(building[i-1][j]==4){
							cnt2--;
						}
					}
					if(dis2[i+1][j]==-1){
						dis2[i+1][j] = cnt+1;
						flag = 1;
						if(building[i+1][j]==4){
							cnt2--;
						}
					}
					if(dis2[i][j-1]==-1){
						dis2[i][j-1] = cnt+1;
						flag = 1;
						if(building[i][j-1]==4){
							cnt2--;
						}
					}
					if(dis2[i][j+1]==-1){
						dis2[i][j+1] = cnt+1;
						flag = 1;
						if(building[i][j+1]==4){
							cnt2--;
						}
					}
				}
				if(dis3[i][j]==cnt){
					if(dis3[i-1][j]==-1){
						dis3[i-1][j] = cnt+1;
						flag = 1;
						if(building[i-1][j]==4){
							cnt3--;
						}
					}
					if(dis3[i+1][j]==-1){
						dis3[i+1][j] = cnt+1;
						flag = 1;
						if(building[i+1][j]==4){
							cnt3--;
						}
					}
					if(dis3[i][j-1]==-1){
						dis3[i][j-1] = cnt+1;
						flag = 1;
						if(building[i][j-1]==4){
							cnt3--;
						}
					}
					if(dis3[i][j+1]==-1){
						dis3[i][j+1] = cnt+1;
						flag = 1;
						if(building[i][j+1]==4){
							cnt3--;
						}
					}
				}
			}
		}
		cnt++;
	}
	
	int minStep = n*m;
	int tmp = 0;
	for(int i = 1;i<m+1;i++){
		for(int j = 1;j<n+1;j++){
			if(building[i][j] == 4 and dis2[i][j]!=-1 and dis3[i][j]!=-1){
				tmp = dis2[i][j]+dis3[i][j];
				minStep=tmp<minStep?tmp:minStep;
			}
		}
	}
	
	cout<<minStep;
	
	return 0;
}
