#include <iostream>
#include <cmath>

using namespace std;

void oneStep();

int main()
{
	int t = 0;
	cin>>t;
	
	for(int i = 0;i<t;i++){
		oneStep();
	}
	 
	return 0;
}

void oneStep()
{
	int n = 0, m = 0;
	cin>>n>>m;
	int* train;
	train = new int [n];
	for(int i = 0;i<n;i++){
		cin>>train[i];
	}
	
	int* change;
	change = new int [m];
	for(int i = 0;i<m;i++){
		change[i]=-1;
	}

	int flag = 1;
	int wait = -1;
	int cnt = 0;
	int one = 0;
	while(cnt<n){
		if(wait==-1){
			if(one==train[cnt]){
				cnt++;
				one++;
				continue;
			}else{
				wait++;
				change[wait] = one;
				one++;
			}
		}else{
			if(one==train[cnt]){
				cnt++;
				one++;
				continue;
			}else{
				if(train[cnt]==change[wait]){
					change[wait] = -1;
					wait--;
					cnt++;
					continue;
				}else{
					if(wait==m-1){
						flag = 0;
						break;
					}else{
						wait++;
						change[wait] = one;
						one++;
					}
				}
			}
		}
	}
	
	if(flag){
		cout<<"YES"<<endl;
	}else{
		cout<<"NO"<<endl;
	}
	
	delete train;
	delete change;
}
