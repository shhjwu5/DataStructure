#include <iostream>

using namespace std;

int main()
{
   	int constant = 300;
  	int a[12] = {0};
  	for(int i = 0;i<12;i++){
  		cin>>a[i];
  	}
  	
  	int save = 0;
  	int hand = 0;
	int flag = 0;
	
	for(int i = 0;i<12;i++){
		hand += constant;
		if(hand>=a[i]){
			save = save + (hand-a[i])/100*100;
			hand = hand - (hand-a[i])/100*100-a[i];
		}else{
			cout<<(-i-1)<<endl;
			flag = 1;
			break;
		}
	}
	
	if(flag==0){
		cout<<(int)(save*1.2)+hand<<endl;
	}
	
  	return 0;
}
