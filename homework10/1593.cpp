#include <iostream>
#include <cstdio>

using namespace std;

struct mice{
	int number;
	int power;
	int score;
	
	mice(int num,int sco):number(num),score(sco),power(0){}
};

const int maxn = 1000000+10;
mice* mouse[maxn] = {NULL};

void quicksort(int start, int end)
{
	if(start>=end){return;}
	
	int a = start;
	int b = end;
	mice* tmp = mouse[start];
	while(a<b){
		while(tmp->score>mouse[b]->score and a<b){b--;}
		while(tmp->score==mouse[b]->score and tmp->number<mouse[b]->number and a<b){b--;}
		mouse[a] = mouse[b];
		while(mouse[a]->score>tmp->score and a<b){a++;}
		while(mouse[a]->score==tmp->score and mouse[a]->number<tmp->number and a<b){a++;}
		mouse[b] = mouse[a];
	}
	mouse[a] = tmp;
	
	quicksort(start,a-1);
	quicksort(a+1,end);
}

int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	
	int n,r;
	cin>>n>>r;
	int x;
	for(int i = 1;i<2*n+1;i++){
		cin>>x;
		mouse[i] = new mice(i,x);
	}
	for(int i = 1;i<2*n+1;i++){
		cin>>x;
		mouse[i]->power = x;
	}
	
	quicksort(1,2*n);
	
	mice* a;
	mice* b;
	mice* tmp;
	int t;

	for(int i = 0;i<r;i++){
		for(int j = 0;j<n;j++){
			a = mouse[2*j+1];
			b = mouse[2*j+2];
			if(a->power>b->power){
				a->score+=2;
				t = 2*j+1;
				while(t>1 and (mouse[t]->score>mouse[t-1]->score or (mouse[t]->score==mouse[t-1]->score and mouse[t]->number<mouse[t-1]->number))){
					tmp = mouse[t];
					mouse[t] = mouse[t-1];
					mouse[t-1] = tmp;
					t--;
				}
			}
			else if(a->power<b->power){
				b->score+=2;
				t = 2*j+2;
				while(t>1 and (mouse[t]->score>mouse[t-1]->score or (mouse[t]->score==mouse[t-1]->score and mouse[t]->number<mouse[t-1]->number))){
					tmp = mouse[t];
					mouse[t] = mouse[t-1];
					mouse[t-1] = tmp;
					t--;
				}
			}
			else{
				a->score++;b->score++;
				t = 2*j+1;
				while(t>1 and (mouse[t]->score>mouse[t-1]->score or (mouse[t]->score==mouse[t-1]->score and mouse[t]->number<mouse[t-1]->number))){
					tmp = mouse[t];
					mouse[t] = mouse[t-1];
					mouse[t-1] = tmp;
					t--;
				}
				t = 2*j+2;
				while(t>1 and (mouse[t]->score>mouse[t-1]->score or (mouse[t]->score==mouse[t-1]->score and mouse[t]->number<mouse[t-1]->number))){
					tmp = mouse[t];
					mouse[t] = mouse[t-1];
					mouse[t-1] = tmp;
					t--;
				}			
			}
		}
	}
	
	for(int i = 1;i<2*n+1;i++){
		cout<<mouse[i]->number<<' ';
	}
	cout<<'\n';
	
	cout<<flush;
	return 0;
} 
