#include <iostream>

using namespace std;

int main()
{
	int L = 0;
	cin>>L;
	
	int** data;
	data = new int* [L];
	
	for (int i = 0;i<L;i++){
		data[i] = new int [L];
		for(int j = 0;j<L;j++){
			cin>>data[i][j];
		}
	}
	
	int m = 0;
	int cnt = L*L;

	for(int i = 0;i<L;i++){
		for(int j = 0;j<L;j++){
			if(data[i][j]!=0){
				cnt--;
			}
		}
	}
	
	int cost = 0;
	
	while(cnt>0){
		for(int i = 0;i<L;i++){
			for(int j = 0;j<L;j++){
				if(data[i][j]==1){
					if(i>0){
						if(data[i-1][j]==0){
							data[i-1][j] = 3;
						}
					}
					if(i<L-1){
						if(data[i+1][j]==0){
							data[i+1][j] = 3;
						}
					}
					if(j>0){
						if(data[i][j-1]==0){
							data[i][j-1] = 3;
						}
					}
					if(j<L-1){
						if(data[i][j+1]==0){
							data[i][j+1] = 3;
						}
					}
				}
			}
		}
		
		for(int i = 0;i<L;i++){
			for(int j = 0;j<L;j++){
				if(data[i][j]==3){
					cnt--;
					data[i][j] = 1;
				}
			}
		}
		
		cost++;
	}
	
	cout<<cost<<endl;
	
	for (int i = 0;i<L;i++){
		delete data[i];
	}
	delete data;
	
	return 0;
}
