#include <iostream>
#include <cstdio>

using namespace std;

const int maxn = 1000000+5;
int n = 0;
char myData[maxn] = {0};

void createLevel()
{
	for(int i = 1;i<=n;i++){
		myData[i] = getchar();
	}
}

void createPre(int m)
{
	if(m>n){
		return;
	}else{
		myData[m] = getchar();
		createPre(2*m);
		createPre(2*m+1);
	}
}

void createMid(int m)
{
	if(m>n){
		return;
	}else{
		createMid(2*m);
		myData[m] = getchar();
		createMid(2*m+1);
	}
}

void createPost(int m)
{
	if(m>n){
		return;
	}else{
		createPost(2*m);
		createPost(2*m+1);
		myData[m] = getchar();
	}
}

void preOrder(int m)
{
	if(m>n){
		return;
	}else{
		putchar(myData[m]);
		preOrder(2*m);
		preOrder(2*m+1);
		if(m==1){
			putchar('\n');
		}
	}
}

void midOrder(int m)
{
	if(m>n){
		return;
	}else{
		midOrder(2*m);
		putchar(myData[m]);
		midOrder(2*m+1);
		if(m==1){
			putchar('\n');
		}
	}
}

void postOrder(int m)
{
	if(m>n){
		return;
	}else{
		postOrder(2*m);
		postOrder(2*m+1);
		putchar(myData[m]);
		if(m==1){
			putchar('\n');
		}
	}
}

void levelOrder()
{
	for(int i = 1;i<=n;i++){
		putchar(myData[i]);
	}
	putchar('\n');
}

int main()
{
	int length = 0;
	scanf("%d",&length);
	
	char first = 0;
	char input[40] = {0};
	
	for(int i = 0;i<length;i++){
		scanf("%d",&n);
		
		int j = 0;
		scanf("%c", &input[j]);
		while(input[j]!='\n'){
			j++;
			scanf("%c",&input[j]);
		}

		if(input[1]=='I'){
			if(input[9]=='E'){
				createLevel();
				midOrder(1);
			}else{
				createMid(1);
				levelOrder();
			}
		}else if(input[1]=='P' and input[2]=='R'){
			if(input[10]=='E'){
				createLevel();
				preOrder(1);
			}else{
				createPre(1);
				levelOrder();
			}
		}else{
			if(input[11]=='E'){
				createLevel();
				postOrder(1);
			}else{
				createPost(1);
				levelOrder();
			}
		}
	}
	return 0;
}
