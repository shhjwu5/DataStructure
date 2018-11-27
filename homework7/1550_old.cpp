#include <cstdio>

using namespace std;

const int maxn = 1000+10;
const int maxm = 10000+10;
int theData[maxn] = {0};

int theMax[maxm][2] = {0};

int min(int x, int y)
{
	return x>y?y:x;
}

int max(int x, int y)
{
	return x>y?x:y;
}

int main()
{
	int n = 0;
	scanf("%d\n",&n);
	
	for(int i = 0;i<n;i++){
		theMax[i][0] = theMax[i][1] = -1;
	}
	
	int sum = 0;
	
	scanf("[%d",&theData[0]);
	sum+=theData[0];
	theMax[theData[0]][0] = theMax[theData[0]][1] = 0;
	
	int allMax = theData[0];
	
	for(int i = 1;i<n;i++){
		scanf(",%d",&theData[i]);
		sum+=theData[i];
		if(theData[i]>allMax){
			allMax = theData[i];
		}
		if(theMax[theData[i]][0]==-1){
			theMax[theData[i]][0] = theMax[theData[i]][1]= i;
		}else{
			theMax[theData[i]][1] = i;
		}
	}
	
	for(int i = allMax-1;i>=0;i--){
		if(theMax[i][0]==-1){
			theMax[i][0] = theMax[i+1][0];
			theMax[i][1] = theMax[i+1][1]; 
		}else{
			theMax[i][0] = min(theMax[i][0],theMax[i+1][0]);
			theMax[i][1] = max(theMax[i][1],theMax[i+1][1]); 
		}
	}

	int total = 0;
	for(int i = allMax;i>0;i--){
		total+=theMax[i][1]-theMax[i][0]+1;
	}

	printf("%d",total-sum);

	return 0;
}
