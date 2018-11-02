#include <iostream>
#include <cstdio>

using namespace std;

struct node{
	int number;
	int rightNum;
	node* left;
	node* right;
};

struct tree{
	node* root;
};

tree* myData = new tree;

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	int cnt = 0;
	int n = 0;
	cin>>n;
	
	myData->root = new node;
	cin>>myData->root->number;
	myData->root->rightNum = 1; 
	myData->root->left = NULL;
	myData->root->right = NULL;
	
	int input = 0;
	
	for(int i = 0;i<n-1;i++){
		cin>>input;
		node* p = new node;
		p = myData->root;
		while(true){
			if(input>=p->number){
				p->rightNum+=1;
				if(p->right){
					p = p->right;
				}else{
					node* tmp = new node;
					tmp->number = input;
					tmp->rightNum = 1;
					tmp->left = NULL;
					tmp->right = NULL;
					p->right = tmp;
					break;
				}
			}else{
				cnt+=p->rightNum;
				if(p->left){
					p = p->left;
				}else{
					node* tmp = new node;
					tmp->number = input;
					tmp->rightNum = 1;
					tmp->left = NULL;
					tmp->right = NULL;
					p->left = tmp;
					break;
				}
			}
		}
	}
	
	cout<<cnt<<endl;
	
	return 0;
} 
