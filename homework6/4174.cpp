#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 100000+10;
long long myData[maxn][2] = {0};
int condition[maxn] = {0};

void swap(int a, int b){
    long long tmp1 = myData[a][0];
    long long tmp2 = myData[a][1];
    myData[a][0] = myData[b][0];
    myData[a][1] = myData[b][1];
    myData[b][0] = tmp1;
    myData[b][1] = tmp2;
}

void quicksort(int start, int end){
    if(start>=end){
        return;
    }
    int a = start;
    int b = end;
    while(a<b){
        while(myData[a][0]<myData[b][0] and a<b){
            b--;
        }
        swap(a,b);

        while(myData[a][0]<myData[b][0] and a<b){
            a++;
        }
        swap(a,b);
    }
    quicksort(start,a-1);
    quicksort(a+1,end);
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n = 0;
    cin>>n;

    for(int i = 0;i<n;i++){
        cin>>myData[i][0];
    }
    for(int i = 0;i<n;i++){
        cin>>myData[i][1];
    }

    quicksort(0,n-1);

    int cnt = 1;
    if(n>1){
		cnt = 2; 
	    condition[0] = -1;
	    condition[n-1] = 1;
	
	    for(int i = 1;i<n-2;i++){
	        if(condition[i]==0){
	            if(myData[i][0]-myData[i][1]>myData[i-1][0]){
	                cnt++;
	                condition[i] = -1;
	            }else if(myData[i+1][0]-myData[i+1][1]>myData[i][0]+myData[i][1]){
	                condition[i] = 1;
	                condition[i+1] = -1;
	            }else{
	                if(myData[i+1][0]-myData[i+1][1]>myData[i][0]){
	                    cnt++;
	                    condition[i+1] = -1;
	                }else{
	                    if(myData[i+1][0]-myData[i][1]>myData[i][0]){
	                        cnt++;
	                        condition[i] = 1;
	                    }else{
	                        condition[i] = 0;
	                    }
	                }
	            }
	        }
	    }
	    
	    if(condition[n-2]==0){
	    	if(myData[n-2][0]-myData[n-2][1]>myData[n-3][0]){
	            cnt++;
	            condition[n-2] = -1;
	    	}else{
	            if(myData[n-2][0]+myData[n-2][1]<myData[n-1][0]){
	                cnt++;
	                condition[n-2] = 1;
	            }
			}
		}
	}else{
		cnt = 1;
	}

    cout<<cnt<<'\n';

    cout<<flush;

    return 0;
}
