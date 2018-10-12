#include <iostream>

using namespace std;

const char error[7] = "Error!";

void getInput(char**, int*);
void printArticle(char**, int, int, int*);
int command(char**, int*);

int main()
{
	char** input;
	input = new char* [100];
	int* length;
	length = new int [101];
	getInput(input, length); 
	int flag = 1;
	while(flag){
		flag = command(input, length);
	}
	
	return 0;
}

void getInput(char** input, int* length)
{
	int i = 0; 
	while(i<100){
		input[i] = new char [2000] {0};
		cin.getline(input[i],2000);
		int time = 0;
		while(input[i][time]!=0){
			time++;
		}
		length[i+1] = time;
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
	length[0] = i;
}

void printArticle(char** input, int begin, int end, int* length)
{
	int i = begin-1;
	int j = 0;
	if(end<=length[0]){
		for(int k = i;k<end;k++){
			j = 0;
			for(int j = 0;j<length[k+1];j++){
				putchar(input[k][j]);
			}
			putchar('\n');
		}
	}else{
		cout<<error<<endl;
	}
}

int command(char** input, int* length)
{
	char com[4] = {0};
	cin.clear();
	cin.sync();
	int a = 0;
	int b = 0;
	int c = 0;
	char data[101] = {0};
	int flag = 1;
	cin>>com;
	if(com[0]=='i' and com[1]=='n' and com[2]=='s'){
		cin>>a;
		a = a-1;
		cin>>b;
		b = b-1;
		if(a>=0 and b>=0){
			char add[100] = {0};
			cin.get();
			cin.getline(add,100);
			int check = length[a+1];
			
			int cnt = 0;
			while(add[cnt]!=0){
				cnt++;
			}
			
			if(b<=check and a<=length[0]-1){
				for(int n = cnt+check;n>cnt+b-1;n--){
					input[a][n] = input[a][n-cnt];
				}
				for(int n = b;n<b+cnt;n++){
					input[a][n] = add[n-b];
				}
				length[a+1] = length[a+1] + cnt;
			}else{
				cout<<error<<endl;
			}
		}else{
			cout<<error<<endl;
		}
	}else if(com[0]=='d' and com[1]=='e' and com[2]=='l'){
		cin>>a;
		a = a-1;
		cin>>b;
		b = b-1;
		cin>>c;
		if(a>=0 and b>=0 and c>=0){
			int check = length[a+1]; 
			
			if(a>=0 and b>=0 and b+c<=check and a<=length[0]-1){
				int q = b+c;
				while(input[a][q]!=0){
					input[a][q-c]=input[a][q];
					q++;
				}
				for(int m = q-c;m<q;m++){
					input[a][m] = 0;
				}
				length[a+1] = length[a+1] - c;
			}else{
				cout<<error<<endl;
			}
		}else{
			cout<<error<<endl;
		}
	}else if(com[0]=='l' and com[1]=='i' and com[2]=='s' and com[3]=='t'){
		cin>>a;
		cin>>b;
		if(a>0 and a<=b and b<=length[0]){
			printArticle(input,a,b,length);
		}else{
			cout<<error<<endl;
		}
	}else if(com[0]=='q' and com[1]=='u' and com[2]=='i' and com[3]=='t'){
		printArticle(input,1,length[0],length);
		flag = 0;
	}
	
	return flag;
}
