#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 100000+5;
int a[maxn] = {0};
int b[maxn] = {0};

int check[maxn] = {0};
int toFind[maxn] = {0};

int leastOfI[maxn], lastOfLeast[maxn], leastPos[maxn], res[maxn];

int lower(int size, int key)
{
    int first = 0;
	int middle = 0;
    int half = 0;
	int len = size;

    while(len>0) {
        half = len/2;
        middle = first+half;
        if(leastOfI[middle]<key){     
            first = middle+1;          
            len = len-half-1;
        }else{
            len = half;
        }
    }
    return first;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int n = 0;
	cin>>n;
	
	for(int i = 0;i<n;i++){
		cin>>a[i];
		check[a[i]] = i;
	}
	for(int i = 0;i<n;i++){
		cin>>b[i];
		toFind[i] = check[b[i]];
	}
	
	int len = 1;
	int pos = 0;
		
	leastOfI[0] = toFind[0];
	leastPos[0] = 0;
	lastOfLeast[0] = -1;
	
	for (int i = 1;i<n;i++) {
		pos = lower(len, toFind[i]);
		
		leastOfI[pos] = toFind[i];
		leastPos[pos] = i;
		if(pos>0){
			lastOfLeast[i] = leastPos[pos-1];
		}else{
			lastOfLeast[i] = -1;
		}

		if (pos==len){
			len++;
		}
	}
	
	cout<<len<<endl;
		
	cout<<flush;
	return 0;
}
