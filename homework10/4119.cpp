#include <iostream>
#include <cstdio>

using namespace std;

struct node{
	int number;
	int length;
	node* next;
	
	node(int num):number(num),length(0),next(NULL){}
	node(int num, int len):number(num),length(len),next(NULL){}
};

const int maxn = 20000+10;
node* rooms[maxn] = {NULL};
int path[maxn][3] = {0};

void dfs(int point, int i)
{
	node* t = rooms[point]->next;
	while(t!=NULL){
		if(path[t->number][i]==-1){
			path[t->number][i] = path[point][i]+t->length;
			dfs(t->number,i);
		}
		t = t->next;
	}
}

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	int n;
	int pos[3] = {0};
	cin>>n>>pos[0]>>pos[1]>>pos[2];
	
	for(int i = 1;i<n+1;i++){
		rooms[i] = new node(i);
		path[i][0] = path[i][1] = path[i][2] = -1;
	}
	
	int u,v,w;
	node* tmp = NULL;
	for(int i = 0;i<n-1;i++){
		cin>>u>>v>>w;
		tmp = new node(v,w);
		tmp->next = rooms[u]->next;
		rooms[u]->next = tmp;
		
		tmp = new node(u,w);
		tmp->next = rooms[v]->next;
		rooms[v]->next = tmp;
	}
	
	path[pos[0]][0] = path[pos[1]][1] = path[pos[2]][2] = 0;
	
	for(int i = 0;i<3;i++){
		dfs(pos[i],i);
	}
	
	int mintotal = 1e9;
	int minpoint = 0;
	int total = 0;
	for(int i = 1;i<n+1;i++){
		total = 0;
		for(int j = 0;j<3;j++){
			total+=path[i][j];
		}
		if(total<mintotal){
			mintotal = total;
			minpoint = i;
		}
	}
	
	cout<<minpoint<<'\n';
	cout<<mintotal<<'\n';
	
	cout<<flush;
	return 0;
} 
