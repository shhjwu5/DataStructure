#include <iostream>
#include <cstdio>

const int maxn = 30+5;
int path[maxn][maxn] = {0};
int p = 0;
int dp[maxn][maxn] = {0};
int a[maxn] = {0};

int dfs(int l, int r)
{
    if(dp[l][r]>0){
    	return dp[l][r];
	}
    if(l>r){
    	return 1;
	}
    if(l==r){
        dp[l][r] = a[l];
        path[l][r] = l;
    }else{
        for(int i = l;i<=r;i++){
            int x = dfs(l, i-1)*dfs(i+1, r)+a[i];
            if(x>dp[l][r]){
                dp[l][r] = x;
                path[l][r] = i;
            }
        }
    }
    return dp[l][r];
}

void print(int l, int r)
{
    if(l>r){
    	return;
	}
    printf(p++==0?"%d":" %d", path[l][r]);
    print(l, path[l][r]-1);
    print(path[l][r]+1, r);
}

int main ( )
{
    int n = 0;
    scanf ("%d", &n);
    for(int i = 1;i<=n;i++)
        scanf("%d", &a[i]);
    printf("%d\n", dfs(1, n));
    p = 0;
    print(1, n);
    return 0;
}
