#include <iostream>

using namespace std;

long long min(long long* counter)
{
	int next = 0;
	if(counter[0]<=counter[1] and counter[0]<=counter[2]){
		next = 0;
	}else if(counter[1]<=counter[2]){
		next = 1;
	}else{
		next = 2;
	}
	
	return next;
}

long long max(long long* counter)
{
	int next = 0;
	if(counter[0]>=counter[1] and counter[0]>=counter[2]){
		next = 0;
	}else if(counter[1]>=counter[2]){
		next = 1;
	}else{
		next = 2;
	}
	
	return next;
}

void cal1(long long n, long long* time, long long* totalTime)
{
	long long counter[3][n/3+2] = {0};
	
	for(long long i = 0;i<n;i++){
		counter[i%3][i/3] = time[i];
	}
	
	int tmp = n%3;
	if(tmp==1){
		counter[0][n/3+1] = n/3+1;
		counter[1][n/3+1] = n/3;
		counter[2][n/3+1] = n/3;
	}else if(tmp==2){
		counter[0][n/3+1] = n/3+1;
		counter[1][n/3+1] = n/3+1;
		counter[2][n/3+1] = n/3;
	}else{
		counter[0][n/3+1] = n/3;
		counter[1][n/3+1] = n/3;
		counter[2][n/3+1] = n/3;
	}
	
	long long cnt[3] = {0};
	long long totalWaste = 0;
	
	for(int i = 0;i<3;i++){
		for(long long j = 0;j<counter[i][n/3+1];j++){
			totalWaste = totalWaste + counter[i][j]*(counter[i][n/3+1]-j-1);
			cnt[i] = cnt[i] + counter[i][j];
		}
	}
	
	totalTime[0] = totalWaste;
	totalTime[1] = cnt[max(cnt)];
}

void cal2(long long n, long long* time, long long* totalTime)
{
	long long counter[3] = {0};
	long long tmp = 0;
	long long last = 0;
	long long totalWaste = 0; 
	for(long long person = 0;person<n;person++){
		tmp = min(counter);
		totalWaste = totalWaste + (counter[tmp] - last)*(n-person);
		last = counter[tmp];
		counter[tmp] = counter[tmp] + time[person];
	}
	
	totalTime[0] = totalWaste;
	totalTime[1] = counter[max(counter)];
}

int main()
{
   	long long n = 0;
   	cin>>n;
   	
	long long time[n] = {0};
   	
   	for(long long i = 0;i<n;i++){
		cin>>time[i];
	}
	
	long long totalTime1[2] = {0};
	long long totalTime2[2] = {0};
	
	cal1(n, time, totalTime1);
	cal2(n, time, totalTime2);
	cout<<totalTime1[0]<<' '<<totalTime1[1]<<endl;
	cout<<totalTime2[0]<<' '<<totalTime2[1]<<endl;
	
  	return 0;
}
