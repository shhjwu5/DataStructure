#include <iostream>
 
using namespace std;

int** building;
int** dis2;
int** dis3;
 
int cnt2 = 0;
int cnt3 = 0;

void create(int, int);
void calculate2(int, int);
void calculate3(int, int);
void getResult(int, int);
void del(int, int);
 
int main()
{
	int n = 0, m = 0;
	cin>>n>>m;

	create(n, m);
	
	calculate2(n, m);
	calculate3(n, m);
	
	getResult(n, m);
	
	del(n, m);
	
	return 0;
}

void create(int n, int m)
{
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
			}else{
				dis2[i][j] = -1;
			}
			if(building[i][j]==3){
				dis3[i][j] = 0;
			}else{
				dis3[i][j] = -1;
			}
			if(building[i][j]==4){
				cnt2++;
				cnt3++;
			}
			if(building[i][j]==1){
				dis2[i][j] = -2;
				dis3[i][j] = -2;
			}
		}
	}
}

void del(int n, int m)
{
	for(int i = 0;i<m+2;i++){
		delete [] building[i];
		delete [] dis2[i];
		delete [] dis3[i];
	}
	
	delete [] building;
	delete [] dis2;
	delete [] dis3;
}

void calculate2(int n, int m)
{
	int flag = 1;
	int cnt = 0;
	while(cnt2>0 and flag){
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
			}
		}
		cnt++;
	}
}

void calculate3(int n, int m)
{
	int flag = 1;
	int cnt = 0;
	while(cnt3>0 and flag){
		flag = 0;
		for(int i = 1;i<m+1;i++){
			for(int j = 1;j<n+1;j++){
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
}

void getResult(int n, int m)
{
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
}
