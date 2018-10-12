#include <iostream>

using namespace std;

char myData[1000000][2] = {0};
char stack[1000000] = {0};
int pData = 0;
int pStack = 0;

char other(char input)
{
	if(input==')'){
		return '(';
	}
	if(input==']'){
		return '[';
	}
	if(input=='}'){
		return '{';
	}
	
	return 1;
}

void push(char input)
{
	myData[pData][0] = input;
	if(stack[pStack-1]==other(input)){
		myData[pData][1] = 1;
		stack[pStack-1] = 0;
		pStack--;
	}else{
		myData[pData][1] = 0;
		stack[pStack] = input;
		pStack++;
	}
	
	pData++;
}

void pop()
{
	if(pData){
		char end = myData[pData-1][0];
		myData[pData-1][0] = 0;
		
		if(myData[pData-1][1]==1){
			stack[pStack] = other(end);
			pStack++;
		}else{
			stack[pStack-1] = 0;
			pStack--;
		}
		
		pData--;
	}
}

void output()
{
	if(pData){
		cout<<myData[pData-1][0]<<endl;
	}
}

void match()
{
	if(!pStack){
		printf("YES\n");
	}else{
		printf("NO\n");
	}
}

int main()
{
	int n = 0;
	scanf("%d",&n);
	
	int op = 0;
	char tmp = 0;
	for(int i = 0;i<n;i++){
		scanf("%d",&op);
		if(op==1){
			scanf(" %c",&tmp);
			push(tmp);
		}else if(op==2){
			pop();
		}else if(op==3){
			output();
		}else if(op==4){
			match();
		}
	}	
	
	return 0;
}
