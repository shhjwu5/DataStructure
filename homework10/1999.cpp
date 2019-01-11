#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 100+5;
int myData[maxn][maxn] = {0};
int tmp[maxn][maxn] = {0};
int path[6][6] = {0};
int boxes[6][2] = {0};
int step = 0;
int n,m;
int total = 1;
int result = 1e9;
bool inSet[6] = {0};

void clear()
{
	for(int i = 0;i<n+2;i++){
		for(int j = 0;j<m+2;j++){
			tmp[i][j] = myData[i][j];
		}
	}
}

bool bfs(int k)
{
	int step = 2;
	bool flag = true;
	int x = boxes[k][0];
	int y = boxes[k][1];
	while(flag){
		flag = false;
		for(int i = 1;i<n+1;i++){
			for(int j = 1;j<m+1;j++){
				if(tmp[i][j]==step){
					if(tmp[i-1][j]==0 or tmp[i-1][j]==1){tmp[i-1][j] = step+1;flag=true;}
					if(tmp[i+1][j]==0 or tmp[i+1][j]==1){tmp[i+1][j] = step+1;flag=true;}
					if(tmp[i][j-1]==0 or tmp[i][j-1]==1){tmp[i][j-1] = step+1;flag=true;}
					if(tmp[i][j+1]==0 or tmp[i][j+1]==1){tmp[i][j+1] = step+1;flag=true;}
				}
			}
		}
		step++;
	}

	for(int i = k;i<total;i++){
		if(tmp[boxes[i][0]][boxes[i][1]]<2){return false;};
		path[k][i] = path[i][k] = tmp[boxes[i][0]][boxes[i][1]]-2;
	}
	return true;
}

void getSize(int pre,int theSize, int step)
{
	if(theSize==total){if(step<result){result = step;};return;}
	for(int i = 1;i<total;i++){
		if(inSet[i]==false){
			inSet[i]=true;
			getSize(i,theSize+1,step+path[pre][i]);
			inSet[i]=false;
		}
	}
}

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	cin>>n>>m;
	
	for(int i = 0;i<n+2;i++){myData[i][0] = myData[i][m+1] = -1;}
	for(int i = 0;i<m+2;i++){myData[0][i] = myData[n+1][i] = -1;}
	
	for(int i = 1;i<n+1;i++){
		for(int j = 1;j<m+1;j++){
			cin>>myData[i][j];
			if(myData[i][j]==1){;boxes[total][0] = i;boxes[total][1] = j;total++;}
			else if(myData[i][j]==2){boxes[0][0] = i;boxes[0][1] = j;myData[i][j] = 1;}
		}
	}
	
	bool t;
	
	for(int i = 0;i<total;i++){
		clear();
		tmp[boxes[i][0]][boxes[i][1]] = 2;
		t = bfs(i);
		if(t==0){break;}
	}
	
	int pre = 0;
	int theSize = 1;
	int step = 0;
	
	if(t==0){cout<<-1<<endl;}
	else{
		pre = 0;
		theSize = 1;
		step = 0;
		getSize(pre,theSize,step);
		cout<<result<<endl;
	}
	
	cout<<flush;
	return 0;
}
