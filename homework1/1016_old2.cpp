#include<iostream>
#include<cmath>

using namespace std;

int* createEmpty()
{
	int length = 1;
	int* myList;
	myList = new int [300];
	
	for(int i = 0;i<300;i++){
		myList[i] = 0;
	}
	
	return myList;
}

void copyList(int* newList, int* myList)
{
	for (int i = 0;i<300;i++){
		newList[i] = myList[i];
	}
}

int* create()
{
	int length = 0;
	int k = 0;
	int* myList;
	myList = new int [300];
	k=(int)getchar()-48;
	while(k>=0 and k<=9){
		myList[length] = k;
		length++;
		k=(int)getchar()-48;
	}
	
	for(int i = 0;i<length;i++){
		myList[300-1-i] = myList[length-1-i];
	}
	
	for(int i = length;i<300;i++){
		myList[300-1-i] = 0;
	}
	
	return myList;
}

void printList(int* myList)
{
	int flag = 0;
	for(int i = 0;i<300;i++){
		if(myList[i] != 0 or flag == 1){
			putchar(myList[i]+48); 
			flag = 1;
		}
	}
	cout<<endl;
}

int* times(int* myList, int factor)
{
	int i = 0;
	int add = 0;
	int tmp = 0;
	int* productList = createEmpty();
	while(i<300){
		tmp = myList[300-1-i]*factor+add;
		productList[300-1-i] = tmp%10;
		add = tmp/10;
		i++;
	}
	
	return productList;
}

int* sum(int* myList1, int* myList2)
{
	int i = 0;
	int add = 0;
	int tmp = 0;
	int* sumList = createEmpty();
	while(i<300){
		tmp = myList1[300-1-i] + myList2[300-1-i];
		sumList[300-1-i] = tmp%10;
		add = tmp/10;
		i++;
	}
	
	return sumList;
}

int* upper(int* myList, int n)
{
	int* newList = createEmpty();
	for(int i = 0;i<n-1;i++){
		newList[i] = 0;
	}
	for(int i = n-1;i<300-n;i++){
		newList[i] = myList[i+n];
	}
	for(int i = 300-n;i<300;i++){
		newList[i] = 0;
	}
	
	return newList;
}

int length(int* myList)
{
	int i = 0;
	while(myList[i]==0){
		i++;
	}
	
	return 300-i;
}

int* delBack(int* myList, int n)
{
	int* newList = createEmpty();

	int len = length(myList);

	for(int i = 0;i<len-n;i++){
		newList[300-1-i] = myList[300-1-i-n];
	}
	for(int i = len-n;i<300;i++){
		newList[300-1-i] = 0;
	}
	
	return newList;
}

int isGreater(int* productList, int* myList)
{
	int flag = 0;
	for(int i = 0;i<300;i++){
		if(productList[i]>myList[i]){
			flag = 1;
			break;
		}
		if(productList[i]<myList[i]){
			flag = 0;
			break;
		}
	}
	
	return flag;
}

int main()
{
	int* baseList = create();
	int* subList = create();
	int* productList = createEmpty();
	int* p = createEmpty();
	int* tmpList = createEmpty();
	int* totalList = createEmpty();
	
	if(isGreater(baseList,subList)){
	
		copyList(productList, subList);
		int power = 0;
		while(!isGreater(productList,baseList)){
			power++;
			copyList(tmpList, productList);
			copyList(productList, upper(subList,power));
		}
		if(power){
			power--;
		}
		
		copyList(productList, tmpList);
		copyList(p, productList);
		
		int i = 0;
		
		while(power>=0){
			i = 0;
			int flag = 0;
			while(!isGreater(sum(totalList,productList), baseList)){
				i++;
				copyList(productList, times(p, i));
				flag = 1;
			}
			if(flag){
				i--;
			}
			copyList(productList, times(p, i));
			putchar(i+48);
			if(flag){
				copyList(totalList, sum(totalList,productList));
			}
			power--;
			copyList(p, delBack(p, 1));
			copyList(productList, p);
		}
	}else{
		cout<<0<<endl;
	}

    return 0;
}
