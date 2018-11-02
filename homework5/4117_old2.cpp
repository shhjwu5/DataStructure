#include<iostream>
#include<cmath>

using namespace std;
 
const int maxn=100000+10;
struct node
{
    int left;
	int right;
    long long flag;
    long long sum;
};

node tree[4*maxn];

void build(int left, int right, int root)
{
    tree[root].left = left;
    tree[root].right = right;
    tree[root].sum = 0;
    tree[root].flag = 0;
    
    if(left==right){
        cin>>tree[root].sum;
        return;
    }
    
    int mid = (left+right)/2;
    build(left, mid, root*2);
    build(mid+1, right, root*2|1);
    
    tree[root].sum=tree[root*2].sum+tree[root*2+1].sum;
}

void pushdown(int root)
{
    if(tree[root].flag!=0){
        tree[root*2].sum+=tree[root].flag*(tree[root*2].right-tree[root*2].left+1);
        tree[root*2+1].sum+=tree[root].flag*(tree[root*2+1].right-tree[root*2+1].left+1);
        tree[root*2].flag+=tree[root].flag;
        tree[root*2+1].flag+=tree[root].flag;
        tree[root].flag = 0;
    }
}

long long question(int left, int right, int root)
{
    int theLeft=tree[root].left;
    int theRight=tree[root].right;
    
    if (theLeft>=left and theRight<=right) {
        return tree[root].sum;
    }
    
    pushdown(root);
    
    int mid = (theLeft+theRight)/2;
    long long sum = 0;
    if(mid>=right){
    	sum+=question(left, right, root*2);	
	}else if(left>mid){
		sum+=question(left, right, root*2+1);
	}else{
        sum+=question(left, mid, root*2);
        sum+=question(mid+1, right, root*2+1);
    }
    return sum;
}
 
void update(int left, int right, int root, int val)
{
    int theLeft=tree[root].left;
    int theRight=tree[root].right;
    
    if(theLeft>right or theRight<left){
    	return;
	}
    
    if (theLeft>=left and theRight<=right) {
        tree[root].sum+=val*(right-left+1);
        tree[root].flag+=val;
        return;
    }
    
    pushdown(root);
    
    int mid=(theLeft+theRight)/2;
    if(right<=mid){
    	update(left, right, root*2, val);
	}else if(left>=mid+1){
		update(left, right, root*2+1, val);
	}else{
        update(left, mid, root*2, val);
        update(mid+1, right, root*2+1, val);
    }
    tree[root].sum=tree[root*2].sum+tree[root*2+1].sum;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
    int n = 0;
    int m = 0;
    cin>>n>>m;
    build(1,n,1);
    for(int i = 0;i<m;i++){
        char str;
        cin>>str;
        if (str=='Q') {
            int left, right;
            cin>>left>>right;
            cout<<question(left, right, 1)<<'\n';
        }else if(str=='C') {
            int left, right, x;
            cin>>left>>right>>x;
            update(left, right, 1, x);
        }
    }
    return 0;
} 
