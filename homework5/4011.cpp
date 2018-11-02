#include <iostream>

using namespace std;

const int maxn = 1005;
const int maxPos = 1000/4+5;

class BigInt{ 
private:
	char myData[maxn] = {0};
	int number[maxPos] = {0};
	int length;
	BigInt timeTen();
public:
	BigInt():length(1){};
	BigInt(int n):length(1){number[maxPos-1]=n;};
	~BigInt(){};
	void printInt() const;
	BigInt operator+(BigInt addInt);
	BigInt operator-(BigInt minusInt);
	int &operator[](int i) {return number[i];};
	int getLength(){return length;};
	void setLength(int n){length = n;};
};

BigInt BigInt::operator-(BigInt minusInt)
{
	int minus = 0;
	int tmp = 0;
	BigInt theMinus;
	for(int i = maxPos-1;i>=0;i--){
		tmp = number[i] - minusInt[i] - minus;
		if(tmp<0){
			tmp += 10000;
			minus = 1;
		}else{
			minus = 0;
		}
		theMinus[i] = tmp%10000;
	}
	
	int cnt = 0;
	while(theMinus[cnt]==0){
		cnt++;
	}
	theMinus.setLength(maxPos-cnt);
	
	return theMinus;
}

BigInt BigInt::operator+(BigInt addInt)
{
	int add = 0;
	int tmp = 0;
	BigInt theSum;
	for(int i = maxPos-1;i>=0;i--){
		tmp = number[i] + addInt[i] + add;
		theSum[i] = tmp%10000;
		add = tmp/10000;
	}
	
	int cnt = 0;
	while(theSum[cnt]==0){
		cnt++;
	}
	theSum.setLength(maxPos-cnt);
	
	return theSum;
}

void BigInt::printInt() const
{
	for(int i = 0;i<length;i++){
		int theNumber = number[maxPos-length+i];
		if(i>0){
			if(theNumber<1000){
				cout<<0;
			}
			if(theNumber<100){
				cout<<0;
			}
			if(theNumber<10){
				cout<<0;
			}
		}
		cout<<theNumber;
	}
}

const int maxT = 50+5;
BigInt total[maxT][maxT];
BigInt maxInt[maxT];

int main()
{
	int k = 0;
	int h = 0;
	cin>>k>>h;
	
	BigInt first(1);
	total[1][0] = first;
	maxInt[1] = first;
	
	for(int i = 2;i<h+1;i++){
		for(int j = 0;j<k;j++){
			total[i][j] = maxInt[i-1];
			for(int m = k-1;m>k-1-j;m--){
				total[i][j] = total[i][j]-total[i-1][m];
			}
			maxInt[i] = maxInt[i]+total[i][j];
		}
	}

	maxInt[h].printInt();
	cout<<flush;
	return 0;
} 
