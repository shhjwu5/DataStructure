#include <iostream>
#include <cstdio>
 
using namespace std;
 
const int songNum = 100000+5;
const int peoNum = 1000000+5;		
	
long double songs[songNum] = {0};
long double boys[peoNum] = {0};
long double girls[peoNum] = {0};
long double tmp[peoNum] = {0};
	
int totalNum = 0;
int boyNum = 0;
int girlNum = 0;
int nSongs = 0;
 
void MergeBoy(int start, int mid, int end)
{
    int i = start, j=mid+1, k = start;
    while(i<=mid and j<=end){
        if(boys[i]>boys[j]){
            tmp[k] = boys[j];
            k++; j++;
		}else{
            tmp[k] = boys[i];
            k++; i++;
        }
    }
    while(i<=mid){
		tmp[k] = boys[i];
        k++; i++;
	} 
    while(j<=end){
		tmp[k] = boys[j];
        k++; j++;
	}
    for(int p = start;p<=end;p++){
    	boys[p] = tmp[p];
	}
}
 
void MergeGirl(int start, int mid, int end)
{
    int i = start, j=mid+1, k = start;
    while(i<=mid and j<=end){
        if(girls[i]>girls[j]){
            tmp[k] = girls[j];
            k++; j++;
		}else{
            tmp[k] = girls[i];
            k++; i++;
        }
    }
    while(i<=mid){
		tmp[k] = girls[i];
        k++; i++;
	} 
    while(j<=end){
		tmp[k] = girls[j];
        k++; j++;
	}
    for(int p = start;p<=end;p++){
    	girls[p] = tmp[p];
	}
}
 
void MergeSortBoy(int start, int end)
{
    int mid;
    if(start<end){
        mid = start+(end-start)/2;
        MergeSortBoy(start, mid);
        MergeSortBoy(mid+1, end);
        MergeBoy(start, mid, end);
    }
}
 
void MergeSortGirl(int start, int end)
{
    int mid;
    if(start<end){
        mid = start+(end-start)/2;
        MergeSortGirl(start, mid);
        MergeSortGirl(mid+1, end);
        MergeGirl(start, mid, end);
    }
}
 
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout.setf(ios::showpoint);
	cout.precision(2);
	cout.setf(ios::fixed);  
	
	cin>>nSongs;
	for(int i = 1;i<nSongs+1;i++){
		cin>>songs[i];
	}
	
	int sex = 0;
	long long time = 0;
	cin>>totalNum;
	for(int i = 0;i<totalNum;i++){
		cin>>sex>>time;
		if(sex==1){
			boys[boyNum++] = time;
		}else{
			girls[girlNum++] = time;
		}
	}
	
	MergeSortBoy(0,boyNum-1);
	MergeSortGirl(0,girlNum-1);
	
	long long mainTime = 0;
	int theSong = 0;
	int theStart = 0;
	int theEnd = 0;
	long double timeBoy = 0;
	long double timeGirl = 0;
	
	for(int round = 0;round<nSongs-1;round++){
		theStart = theEnd;
		mainTime += songs[round];
		while(theEnd<boyNum and theEnd<girlNum and boys[theEnd]<=mainTime and girls[theEnd]<=mainTime){
			theEnd++;
		}
		for(int i = theStart;i<theEnd;i++){
			timeBoy+=(mainTime-boys[i])/(double)boyNum;
			timeGirl+=(mainTime-girls[i])/(double)girlNum;
		}
	}
	mainTime += songs[nSongs-1];
	for(int i = theEnd;i<boyNum;i++){
		timeBoy+=(mainTime-boys[i])/(double)boyNum;
	}
	for(int i = theEnd;i<girlNum;i++){
		timeGirl+=(mainTime-girls[i])/(double)girlNum;
	}
	
	if(timeBoy==0){
		cout<<0.00<<' ';
	}else{
		cout<<timeBoy<<' ';
	}
	if(timeGirl==0){
		cout<<0.00<<endl;
	}else{
		cout<<timeGirl<<endl;
	}
	
	return 0;
}
