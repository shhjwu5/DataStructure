#include <cstdio>

using namespace std;

const int maxn = 1000+10;
const int maxm = 10000+10;
int theData[maxn] = {0};

int main()
{
	int n = 0;
	scanf("%d\n",&n);
	
	int sum = 0;
	
	scanf("[%d",&theData[0]);
	sum+=theData[0];
	
	for(int i = 1;i<n;i++){
		scanf(",%d",&theData[i]);
		sum+=theData[i];
	}
	
	for(int i = 0;i<n-1;i++){
		for(int j = n-1;j>i;j--){
			if(theData[j]>=theData[i]){
				for(int k = i;k<=j;k++){
					if(theData[k]<theData[i]){
						theData[k] = theData[i];
					}
				}
			}
		}
	}
	
	for(int i = n-1;i>0;i--){
		for(int j = 0;j<i;j++){
			if(theData[j]>=theData[i]){
				for(int k = j;k<=i;k++){
					if(theData[k]<theData[i]){
						theData[k] = theData[i];
					}
				}
			}
		}
	}

	int total = 0;
	for(int i = 0;i<n;i++){
		total+=theData[i];
	}

	printf("%d",total-sum);

	return 0;
}
