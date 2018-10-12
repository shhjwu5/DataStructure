#include<iostream>

using namespace std;

const int base = 334; 

int* create()
{
	int length = 0;
	int k = 0;
	int* myList;
	myList = new int [base];
	k=(int)getchar()-48;
	while(k>=0 and k<=9){
		myList[length+1] = k;
		length++;
		k=(int)getchar()-48;
	}
	
	for(int i = length+1;i<base;i++){
		myList[i] = 0;
	}
	
	myList[0] = length;
		
	return myList;
}

void printList(int* myList)
{
	int len = myList[0];
	
	int p = 1;
	
	while(myList[p]<0.5){
		p++;
	}
	
	for(int i = p;i<p+len;i++){
		putchar(myList[i]+48); 
	}
	if(len==0){
		putchar('0');
	}
	cout<<endl;
}

void minusList(int* myList1, int* myList2)
{
	int len = myList1[0];
	int borrow = 0;
	int mid = 0;
	
	int p = 1;
	int q = 1;
	
	while(myList1[p]<0.5){
		p++;
	}
	
	for(int i = base-1;i>0;i--){
		mid = myList1[i]-myList2[i]-borrow;
		if(mid<0){
			borrow = 1;
			mid = mid + 10;
		}else{
			borrow = 0;
		}
		myList1[i] = mid;
	}
	
	while(myList1[q]<0.5){
		q++;
	}
	
	myList1[0] = myList1[0] - q + p;
}

int* delBack(int* myList)
{
	int len = myList[0];
	
	int q = 1;
	
	while(myList[q]<0.5){
		q++;
	}
	
	for(int i = q+len-1;i>q;i--){
		myList[i] = myList[i-1];
	}
	
	for(int i = 1;i<=q;i++){
		myList[i] = 0;
	}
	
	myList[0]--;
	
	return myList;
}

int isGreater(int* myList1, int* myList2)
{
	int flag = 1;
	if(myList1[0]>myList2[0]){
		flag = 1;
	}else if(myList1[0]<myList2[0]){
		flag = 0;
	}else{
		for(int i = 1;i<301;i++){
			if(myList1[i]>myList2[i]){
				flag = 1;
				break;
			}else if(myList1[i]<myList2[i]){
				flag = 0;
				break;
			}
		}
	}
	
	return flag;
}

int main()
{
	int* myList1 = create();
	int* myList2 = create();
	
	int total = myList1[0] - myList2[0] + 1;
	
	int flag = 0;
	
	if(isGreater(myList1,myList2)){
		myList2[0] = myList1[0];
		for(int i = total;i>0;i--){
			int t = 0;
			while(isGreater(myList1,myList2)){
				minusList(myList1,myList2);
				t++;
			}
			if(flag != 0 or t != 0){
				putchar(t+48);
				flag = 1;
			}
			
			delBack(myList2);
		}
	}else{
		putchar('0');
	}
    return 0;
}
