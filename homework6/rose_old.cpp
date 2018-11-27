#include<iostream>
#include<cmath>

using namespace std;
 
const int maxn=1000000+10;

struct node
{
	int left;
	int right;
	int leftSum;
	int rightSum;
    int sum;
	int flag;
    int total;
};

node tree[4*maxn];
int t = 1;

int max(int a, int b, int c)
{
	if(a>b){
		return (a>c)?a:c;
	}else{
		return (b>c)?b:c;
	}
}

void pushup(int root)
{
	tree[root].total = tree[root*2].total+tree[root*2+1].total;
    tree[root].sum = max(tree[root*2].sum,tree[root*2+1].sum,tree[root*2].rightSum+tree[root*2+1].leftSum);
    tree[root].leftSum = tree[root*2].leftSum;
    if(tree[root*2].leftSum==tree[root*2].right-tree[root*2].left){tree[root].leftSum+=tree[root*2+1].leftSum;}
	tree[root].rightSum = tree[root*2+1].rightSum;
    if(tree[root*2+1].rightSum==tree[root*2+1].right-tree[root*2+1].left){tree[root].rightSum+=tree[root*2].rightSum;}
}

void build(int left, int right, int root)
{
    tree[root].left = left;
    tree[root].right = right;
    tree[root].leftSum = 0;
    tree[root].rightSum = 0;
    tree[root].sum = 0;
    tree[root].total = 0;
    tree[root].flag = -1;
    
    if(left==right){
        cin>>tree[root].sum;
        tree[root].leftSum = tree[root].rightSum = tree[root].total = tree[root].sum;
        return;
    }
    
    int mid = (left+right)/2;
    t++;tree[root].left = t;
    build(left, mid, t);
    t++;tree[root].right = t;
	build(mid+1, right, t);
    
    pushup(root);
}

void pushdown(int root)
{
	tree[root].sum = tree[root].leftSum = tree[root].rightSum = tree[root].total = (tree[root].right-tree[root].left)*(tree[root].flag);
	return;
}

void pushdownnew(int root){
	if(tree[root].flag==-1){return;}
	tree[root*2].flag = tree[root*2+1].flag = tree[root].flag;
	pushdown(root*2);
	pushdown(root*2+1);
	tree[root].flag = -1;
	return;
}

int question1(int left, int right, int root)
{
    int theLeft=tree[root].left;
    int theRight=tree[root].right;
    
    if (theLeft>=left and theRight-1<=right) {
        return tree[root].total;
    }
    
    pushdownnew(root);
    
    int mid = (theLeft+theRight)/2;
    int sum = 0;
    if(left<mid){sum+=question1(left,right,root*2);}
    if(right>=mid){sum+=question1(left,right,root*2+1);}
    return sum;
}

int question2(int left, int right, int root)
{
	int theLeft=tree[root].left;
    int theRight=tree[root].right;
    
    if (theLeft>=left and theRight-1<=right) {
        return tree[root].sum;
    }
    
    pushdownnew(root);
    
    int mid = (theLeft+theRight)/2;
	int sum = 0;
    if(left<mid){sum=max(sum,question2(left,right,root*2));}
    if(right>=mid){sum=max(sum,question2(left,right,root*2+1));}
    if(left<mid and right>=mid){
    	int dx = min(tree[root*2].rightSum,tree[root*2].right-left);
    	int dy = min(tree[root*2+1].leftSum,right-tree[root*2+1].left+1);
    	sum = max(sum,dx+dy);
	}
	return sum;
}
 
void update(int left, int right, int root, int val)
{
    int theLeft=tree[root].left;
    int theRight=tree[root].right;
    
    if (theLeft>=left and theRight-1<=right) {
        tree[root].flag = val;
        pushdown(root);
        return;
    }
    
    pushdownnew(root);
    
    int mid=(theLeft+theRight)/2;
    if(left<mid){update(left,right,root*2,val);}
    if(right>=mid){update(left,right,root*2+1,val);}
    pushup(root);
    return;
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
        int ope;
        cin>>ope;
        if (ope==1){
            int left, right, x;
            cin>>left>>right>>x;
            update(left,right,1,x);
        }else if(ope==2) {
            int left, right;
            cin>>left>>right;
            cout<<question1(left,right,1)<<'\n';
        }else if(ope==3){
        	int left, right;
        	cin>>left>>right;
        	cout<<question2(left, right, 1)<<'\n';
		}
    }
    return 0;
} 
