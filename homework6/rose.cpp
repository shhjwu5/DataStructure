#include<iostream>
#include <cstdio>

using namespace std;
 
const int maxn=1000000+10;
struct node
{
    int left;
	int right;
    int flag;
    int sum;
    int leftLong;
    int rightLong;
    int longest;
};

node tree[4*maxn];

int max(int a, int b, int c)
{
	if(a>b){
		return a>c?a:c;
	}else{
		return b>c?b:c;
	}
}

void pushup(int root)
{
	tree[root].sum=tree[root*2].sum+tree[root*2+1].sum;
	tree[root].leftLong = tree[root*2].leftLong;
	if(tree[root*2].leftLong==tree[root*2].right-tree[root*2].left+1){
		tree[root].leftLong+=tree[root*2+1].leftLong;
	}
	tree[root].rightLong = tree[root*2+1].rightLong;
	if(tree[root*2+1].rightLong==tree[root*2+1].right-tree[root*2+1].left+1){
		tree[root].rightLong+=tree[root*2].rightLong;
	}
	tree[root].longest = max(tree[root*2].longest,tree[root*2+1].longest,tree[root*2].rightLong+tree[root*2+1].leftLong);
}

void pushdown(int root)
{
    if(tree[root].flag!=-1){
        tree[root*2].leftLong = tree[root*2].rightLong = tree[root*2].longest = tree[root*2].sum=tree[root].flag*(tree[root*2].right-tree[root*2].left+1);
        tree[root*2+1].leftLong = tree[root*2+1].rightLong = tree[root*2+1].longest = tree[root*2+1].sum=tree[root].flag*(tree[root*2+1].right-tree[root*2+1].left+1);
        tree[root*2].flag=tree[root].flag;
        tree[root*2+1].flag=tree[root].flag;
        tree[root].flag = -1;
    }
}

void build(int root, int left, int right)
{
    tree[root].left = left;
    tree[root].right = right;
    tree[root].sum = tree[root].leftLong = tree[root].rightLong = tree[root].longest = 0;
    tree[root].flag = -1;
    
    if(left==right){
        cin>>tree[root].sum;
        tree[root].leftLong = tree[root].rightLong = tree[root].longest = tree[root].sum;
        return;
    }
    
    int mid = (left+right)/2;
    build(root*2, left, mid);
    build(root*2+1, mid+1, right);
    
   	pushup(root); 
}

int question1(int root, int left, int right)
{
    int theLeft=tree[root].left;
    int theRight=tree[root].right;
    
    if (theLeft>=left and theRight<=right) {
        return tree[root].sum;
    }
    
    pushdown(root);
    
    int mid = (theLeft+theRight)/2;
    int sum = 0;
    if(mid>=right){
    	sum+=question1(root*2, left, right);	
	}else if(left>mid){
		sum+=question1(root*2+1, left, right);
	}else{
        sum+=question1(root*2, left, mid);
        sum+=question1(root*2+1, mid+1, right);
    }
    return sum;
}

int question2(int root, int left, int right)
{
	int theLeft=tree[root].left;
    int theRight=tree[root].right;
    
    if (theLeft>=left and theRight<=right) {
        return tree[root].longest;
    }
    
    pushdown(root);
    
    int mid = (theLeft+theRight)/2;
    int sum = 0;
    if(mid>=right){
    	sum=max(sum,question2(root*2, left, right));	
	}else if(left>mid){
		sum=max(sum,question2(root*2+1, left, right));
	}else{
        int dx = min(tree[root*2].rightLong,tree[root*2].right-left+1);
        int dy = min(tree[root*2+1].leftLong,right-tree[root*2+1].left+1);
		sum = max(sum,question2(root*2, left, right));
		sum = max(sum,question2(root*2+1, left, right));
		sum = max(sum,dx+dy);
    }
    return sum;
}
 
void update(int root, int left, int right, int val)
{
    int theLeft=tree[root].left;
    int theRight=tree[root].right;
    
    if(theLeft>right or theRight<left){
    	return;
	}
    
    if (theLeft>=left and theRight<=right) {
        tree[root].leftLong = tree[root].rightLong = tree[root].longest = tree[root].sum=val*(right-left+1);
        tree[root].flag=val;
        return;
    }
    
    pushdown(root);
    
    int mid=(theLeft+theRight)/2;
    if(right<=mid){
    	update(root*2,left, right, val);
	}else if(left>=mid+1){
		update(root*2+1, left, right, val);
	}else{
        update(root*2, left, mid, val);
        update(root*2+1, mid+1, right, val);
    }
   	pushup(root);
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
    int n = 0;
    int m = 0;
    cin>>n>>m;
    build(1,1,n);
    for(int i = 0;i<m;i++){
        int ope;
        cin>>ope;
        if (ope==1){
            int left, right, x;
            cin>>left>>right>>x;
            update(1,left,right,x);
        }else if(ope==2) {
            int left, right;
            cin>>left>>right;
            cout<<question1(1, left,right)<<'\n';
        }else if(ope==3){
        	int left, right;
        	cin>>left>>right;
        	cout<<question2(1, left, right)<<'\n';
		}
    }
    return 0;
} 
