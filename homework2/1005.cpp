#include <iostream>

using namespace std;

int*** input(int);
void del(int***, int);
int check(int** data);
int checkRow(int** data);
int checkCol(int** data);
int checkGroup(int** data);

int main()
{
	int n = 0;
	cin>>n;
	
	int*** data = input(n);
	
	int flag = 0;
	
	for (int i = 0;i<n;i++){
		flag = check(data[i]);
		if(flag){
			cout<<"Right"<<endl;
		}else{
			cout<<"Wrong"<<endl;
		}
	}
	
	del(data, n);
	
	return 0;
}

int*** input(int n)
{
	int*** data;
	
	data = new int** [n];
	for(int i = 0;i<n;i++){
		data[i] = new int* [9];
		for(int j = 0;j<9;j++){
			data[i][j] = new int [9];
			for (int k = 0;k<9;k++){
				cin>>data[i][j][k];
			}
		}
	}
	
	return data;
}

void del(int*** data, int n)
{
	for(int i = 0;i<n;i++){
		for(int j = 0;j<9;j++){
			delete data[i][j];
		}
		delete data[i];
	}
	delete data;
}

int check(int** data)
{	
	int flag = 1;
	if(flag){
		flag = checkRow(data);
	}
	if(flag){
		flag = checkCol(data);
	}
	if(flag){
		flag = checkGroup(data);
	}
	
	return flag;
}

int checkRow(int** data)
{
	int row[9] = {1,1,1,1,1,1,1,1,1};
	int flag = 1;
	
	for (int i = 0;i<9;i++){
		for (int p = 0;p<9;p++){
			row[p] = 1;
		}
		for (int j = 0;j<9;j++){
			if (row[data[i][j]-1]==0){
				flag = 0;
				break;
			}else{
				row[data[i][j]-1] = 0;
			}
		}
		if(!flag){
			break;
		}
	}
	
	return flag;
}

int checkCol(int** data)
{
	int col[9] = {1,1,1,1,1,1,1,1,1};
	int flag = 1;
	
	for (int i = 0;i<9;i++){
		for (int p = 0;p<9;p++){
			col[p] = 1;
		}
		for (int j = 0;j<9;j++){
			if (col[data[j][i]-1]==0){
				flag = 0;
				break;
			}else{
				col[data[j][i]-1] = 0;
			}
		}
		if(!flag){
			break;
		}
	}
	
	return flag;
}

int checkGroup(int** data){
	int group[9] = {1,1,1,1,1,1,1,1,1};
	int flag = 1;
	
	for (int i = 0;i<3;i++){
		for (int j = 0;j<3;j++){
			for (int p = 0;p<9;p++){
				group[p] = 1;
			}
			for (int m = 0;m<3;m++){
				for (int n = 0;n<3;n++){
					if (group[data[3*i+m][3*j+n]-1]==0){
						flag = 0;
						break;
					}else{
						group[data[3*i+m][3*j+n]-1] = 0;
					}
				}
				if(!flag){
					break;
				}
			}
			if(!flag){
				break;
			}
		}
		if(!flag){
			break;
		}
	}
	
	return flag;
}
