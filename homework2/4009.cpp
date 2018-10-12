#include <iostream>
#include <cmath>

using namespace std;

void calResult(int);

int main()
{
	char appeal[100] = {0};
	char hide[100] = {0};
	cin>>appeal;
	cin>>hide;
	
	int appeal_length = 0;
	while(appeal[appeal_length]){
		appeal_length++;
	}
	
	int hide_length = 0;
	while(hide[hide_length]){
		hide_length++;
	}
	
	if(hide_length!=appeal_length){
		cout<<"No Solution"<<endl;
	}else{
		int flag = 0;
		for(int a = 1;a<appeal_length+1;a++){
			flag = 0;
			if(!(appeal_length%a)){
				int i = appeal_length/a;
				
				flag = 1;
				
				for(int j = 0;j<a;j++){
					for(int k = 0;k<i;k++){
						if(appeal[k*a+j]!=hide[j*i+k]){
							flag = 0;
							break;
						}
					}
				}
			}
			if(flag){
				cout<<a<<endl;
				break;
			}
		}
		if(!flag){
			cout<<"No Solution"<<endl;
		}
	}

	return 0;
}
