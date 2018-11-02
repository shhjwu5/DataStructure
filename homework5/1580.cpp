#include<iostream>
#include<cmath> 

using namespace std;

const int maxn = 1000000+5;
int num[maxn], leastOfI[maxn], lastOfLeast[maxn], leastPos[maxn], res[maxn];

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
	int n;
	cin>>n;
	
	for(int j = 0;j<n;j++){
		cin>>num[j];	
	}
	int len = 1;
	int pos = 0;
		
	leastOfI[0] = num[0];
	leastPos[0] = 0;
	lastOfLeast[0] = -1;
	
	for (int i = 1;i<n;i++) {
		pos = lower(len, num[i]);
		
		leastOfI[pos] = num[i];
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
	
	return 0;
}
