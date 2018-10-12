#include <iostream>

using namespace std;

const char error[7] = "Error!";

int getInput(char**);
void printArticle(char**, int, int, int);
int command(char**, int);

int main()
{
	char** input;
	input = new char* [101];
	int length = 0;
	length = getInput(input); 
	int flag = 1;
	while(flag){
		flag = command(input, length);
	}
	
	return 0;
} 

int getInput(char** input)
{
	int i = 0;
	while(i<100){
		input[i] = new char [2000] {0};
		cin.getline(input[i],2000);
		int cnt = 0;
		for(int j = 0;j<6;j++){
			if(input[i][j]=='*'){
				cnt++;
			}
		}
		if(cnt==6){
			break;
		}
		i++;
	}
	
	input[i][0] = 0;
	
	return i;
}

void printArticle(char** input, int begin, int end, int length)
{
	int i = begin-1;
	int j = 0;
	if(end<=length){
		for(int k = i;k<end;k++){
			j = 0;
			while(input[k][j]!=0){
				putchar(input[k][j]);
				j++;
			}
			putchar('\n');
		}
	}else{
		cout<<error<<endl;
	}
}

int command(char** input, int length)
{
	char com[5] = {0};
	cin.clear();
	cin.sync();
	int a = 0;
	int b = 0;
	int c = 0;
	char data[101] = {0};
	for (int i = 0;i<4;i++){
		com[i] = getchar();
	}
	int flag = 1;
	if(com[0] == 'i' and com[1] == 'n' and com[2] == 's' and com[3] == ' '){
		cin>>a;
		a = a-1;
		cin>>b;
		b = b-1;
		if(a>=0 and b>=0){
			char add[100] = {0};
			cin.get();
			cin.getline(add,100);
			int check = 0;
			while(input[a][check]!=0){
				check++;
			}
			
			int cnt = 0;
			while(add[cnt]!=0){
				cnt++;
			}
			
			if(b<=check-1 and a<=length-1){
				for(int n = cnt+check;n>cnt+b-1;n--){
					input[a][n] = input[a][n-cnt];
				}
				for(int n = b;n<b+cnt;n++){
					input[a][n] = add[n-b];
				}
			}else{
				cout<<error<<endl;
			}
		}else{
			cout<<error<<endl;
		}
	}else if(com[0] == 'd' and com[1] == 'e' and com[2] == 'l' and com[3] == ' '){
		cin>>a;
		a = a-1;
		cin>>b;
		b = b-1;
		cin>>c;
		if(a>=0 and b>=0 and c>=0){
			int check = 0;
			while(input[a][check]!=0){
				check++;
			}
			
			if(a>=0 and b>=0 and b<=check-1 and a<=length-1){
				int q = b+c;
				while(input[a][q]!=0){
					input[a][q-c]=input[a][q];
					q++;
				}
				for(int m = q-c;m<q;m++){
					input[a][m] = 0;
				}
			}else{
				cout<<error<<endl;
			}
		}else{
			cout<<error<<endl;
		}
	}else if(com[0] == 'l' and com[1] == 'i' and com[2] == 's' and com[3] == 't'){
		cin>>a;
		cin>>b;
		if(a>0 and a<=b and b<=length){
			printArticle(input,a,b,length);
		}else{
			cout<<error<<endl;
		}
	}else if(com[0] == 'q' and com[1] == 'u' and com[2] == 'i' and com[3] == 't'){
		printArticle(input,1,length,length);
		flag = 0;
	}else{
		cout<<"end"<<endl;
	}
	
	return flag;
}
