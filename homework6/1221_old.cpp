#include <iostream>
#include <cstdio>

using namespace std;

template <class T>
class AvlTree{
private:
	struct avlNode{
		T theData;
		avlNode* l 
		avlNode* right;
		int height;
		
		avlNode(const T &element, avlNode* lt, avlNode* rt, int h=1):theData(element),left(lt),right(rt),height(h){};
	};
	avlNode* ithEle;
	int cnt;
	avlNode* root;
public:
	AvlTree(){root=NULL;}
	~AvlTree(){makeEmpty(root);};
	void insert(const T &x);
	void remove(const T &x);
	void removeLessThan(const T &lt);
	void removeGreaterThan(const T &rt);
	void removeInterval(const T &lt, const T &rt);
	bool find(const T &x) const;
	T findith(int i);
private:
	void findith(int i, avlNode* &t);
	void insert(const T &x, avlNode* &t);
	bool remove(const T &x, avlNode* &t);
	void removeLessThan(const T &lt, avlNode* &t);
	void removeGreaterThan(const T &rt, avlNode* &t);
	void removeInterval(const T &lt, const T &rt, avlNode* &t); 
	void makeEmpty(avlNode* &t);
	int height(avlNode* t) const {return t==NULL?0:t->height;};
	void LL(avlNode* &t);
	void LR(avlNode* &t);
	void RL(avlNode* &t);
	void RR(avlNode* &t);
	int max(int a, int b){return a>b?a:b;};
	bool adjust(avlNode* &t, int subTree);
};

template <class T>
bool AvlTree<T>::find(const T &x) const{
	avlNode* t = root;
	while(t!=NULL and t->theData!=x){
		if(t->theData>x){
			t = t->left;
		}else{
			t = t->right;
		}
	}
	
	if(t==NULL){
		return false;
	}else{
		return true;
	}
}

template <class T>
T AvlTree<T>::findith(int i){
	cnt = 0;
	findith(i,root);
	if(cnt==i){
		return ithEle->theData;
	}else{
		return NULL;
	}
}

template <class T>
void AvlTree<T>::findith(int i, avlNode* &t){
	if(cnt==i or t==NULL){
		return;
	}
	findith(i,t->left);
	cnt++;
	if(cnt==i){
		ithEle = t;
		return;
	}
	findith(i,t->right);
	return;
}

template <class T>
void AvlTree<T>::LL(avlNode* &t){
	avlNode* tl = t->left;
	t->left = tl->right;
	tl->right = t;
	t->height = max(height(t->left),height(t->right))+1;
	tl->height = max(height(tl->left),height(t))+1;
	t = tl;
}

template <class T>
void AvlTree<T>::RR(avlNode* &t){
	avlNode* tl = t->right;
	t->right = tl->left;
	tl->left = t;
	t->height = max(height(t->left),height(t->right))+1;
	tl->height = max(height(tl->right),height(t))+1;
	t = tl;
}

template <class T>
void AvlTree<T>::LR(avlNode* &t){
	RR(t->left);
	LL(t);
}

template <class T>
void AvlTree<T>::RL(avlNode* &t){
	LL(t->right);
	RR(t);
}

template <class T>
void AvlTree<T>::insert(const T &x){
	insert(x,root);
}

template <class T>
void AvlTree<T>::insert(const T &x, avlNode* &t){
	if(t==NULL){
		t = new avlNode(x,NULL,NULL);
	}else if(x<t->theData){
		insert(x,t->left);
		if(height(t->left)-height(t->right)==2){
			if(x<=t->left->theData){
				LL(t);
			}else{
				LR(t);
			}
		}
	}else if(t->theData<x){
		insert(x,t->right);
		if(height(t->right)-height(t->left)==2){
			if(t->right->theData<=x){
				RR(t);
			}else{
				RL(t);
			}
		}
	}else if(t->theData==x){
		avlNode* p = new avlNode(x,NULL,NULL);
		p->left = t->left;
		t->left = p;
		if(height(t->right)-height(t->left)==2){
			if(t->right->theData<=x){
				RR(t);
			}else{
				RL(t);
			}
		}
	}
	
	t->height = max(height(t->left),height(t->right))+1;
}

template <class T>
void AvlTree<T>::remove(const T &x){
	remove(x,root);
}

template <class T>
void AvlTree<T>::removeLessThan(const T &lt){
	removeLessThan(lt,root);
}

template <class T>
void AvlTree<T>::removeGreaterThan(const T &rt){
	removeGreaterThan(rt,root);
}

template <class T>
void AvlTree<T>::removeInterval(const T &lt, const T &rt){
	removeInterval(lt,rt,root);
}

template <class T>
bool AvlTree<T>::remove(const T &x,avlNode* &t){
	if(t==NULL){
		return true;
	}
	if(x==t->theData){
		if(t->left==NULL or t->right==NULL){
			avlNode* oldNode = t;
			t = (t->left!=NULL)?t->left:t->right;
			delete oldNode;
			return false;
		}else{
			avlNode* tmp = t->right;
			while(tmp->left!=NULL){
				tmp = tmp->left;
			}
			t->theData = tmp->theData;
			if(remove(tmp->theData,t->right)){
				return true;
			}
			return adjust(t,1);
		}
	}
	
	if(x<t->theData){
		if(remove(x,t->left)){
			return true;
		}
		return adjust(t,0);
	}else{
		if(remove(x,t->right)){
			return true;	
		}
		return adjust(t,1);
	}
}

template <class T>
bool AvlTree<T>::adjust(avlNode* &t, int subTree){
	if(subTree){
		if(height(t->left)-height(t->right)==1){
			return true;
		}
		if(height(t->right)==height(t->left)){
			--t->height;
			return false;
		}
		if(height(t->left->right)>height(t->left->left)){
			LR(t);
			return false;
		}
		LL(t);
		if(height(t->right)==height(t->left)){
			return false;
		}else{
			return true;
		}
	}else{
		if(height(t->right)-height(t->left)==1){
			return true;
		}
		if(height(t->right)==height(t->left)){
			--t->height;
			return false;
		}
		if(height(t->right->left)>height(t->right->right)){
			RL(t);
			return false;
		}
		RR(t);
		if(height(t->right)==height(t->left)){
			return false;
		}else{
			return true;
		}
	}
}

template <class T>
void AvlTree<T>::removeLessThan(const T &lt, avlNode* &t){
	if(t==NULL){
		return;
	}
	if(t->theData<lt){
		removeLessThan(lt,t->left);
		removeLessThan(lt,t->right);
		remove(t->theData,t);
	}else{
		removeLessThan(lt,t->left);
	}
}

template <class T>
void AvlTree<T>::removeGreaterThan(const T &rt, avlNode* &t){
	if(t==NULL){
		return;
	}
	if(t->theData>rt){
		removeGreaterThan(rt,t->right);
		removeGreaterThan(rt,t->left);
		remove(t->theData,t);
	}else{
		removeGreaterThan(rt,t->right);
	}
}

template <class T>
void AvlTree<T>::removeInterval(const T &lt, const T &rt, avlNode* &t){
	if(t==NULL){
		return;
	}
	if(t->theData>=rt){
		removeInterval(lt,rt,t->left);
	}else if(t->theData<=lt){
		removeInterval(lt,rt,t->right);
	}else{
		removeInterval(lt,rt,t->left);
		removeInterval(lt,rt,t->right);
		remove(t->theData,t);
	}
}

template <class T>
void AvlTree<T>::makeEmpty(avlNode* &t){
	if(t==NULL){
		return;	
	} 
	makeEmpty(t->left);
	makeEmpty(t->right);
	delete t;
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

	int n = 0;
	cin>>n;
	
	AvlTree<int> tree;
	
    char operation[30] = {0};
    int p = 0,q = 0;
    bool flag = false;
    int ith = 0;
	for(int i = 0;i<n;i++){
		operation[0] = 0;
		operation[5] = 0;
		operation[7] = 0;
		cin>>operation;
		if(operation[0]=='i'){
			cin>>p;
			tree.insert(p);
		}else if(operation[0]=='d'){
			if(operation[7]=='l'){
				cin>>p;
				tree.removeLessThan(p);
			}else if(operation[7]=='g'){
				cin>>p;
				tree.removeGreaterThan(p);
			}else if(operation[7]=='i'){
				cin>>p>>q;
				tree.removeInterval(p,q);
			}else{
				cin>>p;
				tree.remove(p);
			}
		}else if(operation[0]=='f'){
			if(operation[5]=='i'){
				cin>>p;
				ith = tree.findith(p);
				if(ith){
					cout<<ith<<'\n';
				}else{
					cout<<"N"<<'\n';
				}
			}else{
				cin>>p;
				flag = tree.find(p);
				if(flag){
					cout<<"Y"<<'\n';
				}else{
					cout<<"N"<<'\n';
				}
			}
		}
	}

    return 0;
}
