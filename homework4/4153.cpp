#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

const int maxn = 100000+5;
int stonePos[maxn] = {0};
int head[maxn] = {0};
int tail[maxn] = {0};

int sortOnce(int first, int end)
{
	int i = first, j = end;
	while (i<j){
		while(i<j and stonePos[i]<=stonePos[j]){
			j--;
		}
		if(i<j){
			int tmp = stonePos[i];
			stonePos[i] = stonePos[j];
			stonePos[j] = tmp;
		}
		while(i<j and stonePos[i]<=stonePos[j]){
			i++;
		}
		if(i<j){
			int tmp = stonePos[i];
			stonePos[i] = stonePos[j];
			stonePos[j] = tmp;
		}
	}
	
	return i;
} 

void Sort(int first, int end)
{
	if(first<=end){
		int middle = sortOnce(first, end);
		Sort(first, middle-1);
		Sort(middle+1, end);
	}
}

int findMin(int n, int m)
{
	int S = (stonePos[n-1]-stonePos[0])/(m-1)+1;
	int start = 0;
	int startPos = 0;
	int cnt = 1;
	int flag = 1;
	while(S>0){
		flag = 1;
		start = 0;
		startPos = stonePos[start];
		cnt = 1;
		while(cnt<m){
			start++;
			if(start==n){
				flag = 0;
				break;
			}
			while(stonePos[start]-startPos<S){
				start++;
				if(start==n){
					flag = 0;
					break;
				}
			}
			
			if(!flag){
				break;
			}
			startPos = stonePos[start];
			cnt++;
		}
		if(flag){
			break;
		}else{
			S--;
		}
	}
	
	cout<<S<<'\n';
}

int findSecondMin(int n, int m)
{
	int S = stonePos[n-1]-stonePos[0];
	int Ss = 1;
	int start = 0;
	int startPos = 0;
	int cnt = 1;
	int check = 0;
	while(Ss<=S){
		int begin = Ss;
		int end = S;
		S = (Ss+S)/2;
		start = 0;
		startPos = stonePos[start];
		cnt = 1;
		head[0] = 1;
		while(cnt<m){
			start++;
			if(start==n){
				head[start-1] = cnt;
				break;
			}
			while(stonePos[start]-startPos<S){
				start++;
				head[start-1] = cnt;
				if(start==n){
					break;
				}
			}
			
			if(start==n){
				break;
			}
			cnt++;
			head[start] = cnt;
	
			startPos = stonePos[start];
		}
		
		start = n-1;
		startPos = stonePos[start];
		cnt = 1;
		tail[n-1] = 1;
		while(cnt<m){
			start--;
			if(start==-1){
				tail[start+1] = cnt;
				break;
			}
			while(startPos-stonePos[start]<S){
				start--;
				tail[start+1] = cnt;
				if(start==-1){
					break;
				}
			}
			cnt++;
			tail[start] = cnt;
			
			if(start==-1){
				break;
			}
			
			startPos = stonePos[start];
		}
		
		int flag = 0;
		for(int i = 0;i<n;i++){
			if(head[i]+tail[i+1]>=m){
				flag = 1;
				break;
			}
		}
		
		if(!flag){
			Ss = begin;
			S = S - 1;
			if(Ss>S){
				break;
			}
		}else{
			Ss = S+1;
			S = end;

			if(Ss>S){
				break;
			}
		}
	}
	
	cout<<S<<'\n';
} 

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int n,m,k;
	cin>>n>>m>>k;
	for(int i = 0;i<n;i++){
		cin>>stonePos[i];
	}
	
	Sort(0, n-1);
	
	if(k==1){
		findMin(n, m);
	}else{
		findSecondMin(n, m);
	}
	
	cout<<flush;
	
	return 0;
} 
