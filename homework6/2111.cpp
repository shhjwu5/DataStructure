#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

struct node{
	int number;
	node* left;
	node* right;
	node* father;
	
	node(int Num, node* lt, node* rt, node* ft):number(Num),left(lt),right(rt),father(ft){}
};

class Tree{
	node* root;
	int up = -1;
	int down = -1;
public:
	Tree():root(NULL){}
	Tree(node* t):root(t){}
	~Tree(){del(root);}
	void insert(int x){insert(root,x);};
	void remove(int x){remove(root,x);};
	int ask(int x){
		up=-1;
		down=-1;
		ask(root,x);
		if(up==-1){
			return abs(x-down);
		}else if(down==-1){
			return abs(up-x);
		}else{
			return (abs(up-x)>abs(x-down))?abs(x-down):abs(up-x);
		}
	};
private:
	void del(node* t){
		if(t==NULL){return;}
		del(t->left);
		del(t->right);
		delete t;
	};
	void insert(node* t, int x){
		if(t==NULL){
			t = new node(x,NULL,NULL,NULL);
			root = t;
			return;
		}
		if(t->number==x){return;}
		if(t->number>x){
			if(t->left==NULL){
				node* p = new node(x,NULL,NULL,t);
				t->left = p;
			}else{
				insert(t->left,x);
			}
		}else{
			if(t->right==NULL){
				node* p = new node(x,NULL,NULL,t);
				t->right = p;
			}else{
				insert(t->right,x);
			}
		}
	};
	void remove(node* &t, int x){
		if(t==NULL){return;}
		if(x<t->number){remove(t->left,x);}
		else if(x>t->number){remove(t->right,x);}
		else if(t->left!=NULL and t->right!=NULL){
			node* tmp = t->right;
			while(tmp->left!=NULL){
				tmp = tmp->left;
			}
			t->number = tmp->number;
			remove(t->right,t->number);
		}else{
			node* oldNode = t;
			t = (t->left!=NULL)?t->left:t->right;
			delete oldNode;
		}
	};
	void ask(node* t, int x){
		if(t==NULL){return;}
		if(t->number==x){
			up = x;
			return;
		}
		
		if(t->number>x){
			up = t->number;
			ask(t->left,x);
			return;
		}else{
			down = t->number;
			ask(t->right,x);
			return;
		}
	};
	node* find(node* t, int x){
		if(t->number==x){return t;}
		if(t->number>x){
			if(t->left==NULL){
				return NULL;
			}
			return find(t->left,x);
		}else{
			if(t->right==NULL){
				return NULL;
			}
			return find(t->right,x);
		}
	};
};

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int M = 0, ope = 0, x = 0;
    cin>>M;
    
    Tree tree; 
    
    for(int i = 0;i<M;i++){
    	cin>>ope>>x;
    	switch (ope){
    		case 0:
    			cout<<tree.ask(x)<<'\n';
    			break;
    		case 1:
    			tree.insert(x);
    			break;
    		case 2:
    			tree.remove(x);
    			break;
    	}
	}

    return 0;
}
