#include <iostream>
#include <cstdio>
#include <cmath>

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
	BigInt();
	~BigInt(){};
	void initialize();
	void printInt() const;
	BigInt operator+(BigInt addInt);
	BigInt operator*(BigInt prodInt); 
	BigInt operator-(BigInt minusInt);
	BigInt Sqrt(); 
	int &operator[](int i) {return number[i];};
	int getLength(){return length;};
	void setLength(int n){length = n;};
	bool operator>(BigInt compInt);
	bool operator<(BigInt compInt);
	BigInt divide2();
};

BigInt first;
BigInt second;

BigInt::BigInt()
{
	length = 0;
}

void BigInt::initialize()
{
	char tmp = 0;
	tmp = getchar();
	while(tmp>='0' && tmp<='9'){
		myData[length] = tmp;
		length++;
		tmp = getchar();
	}
	
	int n = length/4;
	int more = length%4;
	
	for(int i = 0;i<more;i++){
		number[maxPos-1-n] += (myData[i]-48)*pow(10, more-1-i);
	}
	
	for(int i = 0;i<n;i++){
		for(int j = 0;j<4;j++){
			number[maxPos-n+i] += (myData[more+4*i+j]-48)*pow(10, 4-1-j);
		}
	}
	
	if(more){
		length = n+1;
	}else{
		length = n;	
	}
}

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

BigInt BigInt::timeTen()
{
	BigInt theTime;
	for(int i = 0;i<maxPos-1;i++){
		theTime[i] = number[i+1];
	}
	theTime[maxPos-1] = 0;
	
	theTime.setLength(length+1);
	
	return theTime; 
}

BigInt BigInt::operator*(BigInt prodInt)
{	
	int prod = 0;
	int tmp = 0;
	BigInt theProd;
	
	BigInt stepProd = prodInt;
	
	for(int i = maxPos-1;i>=maxPos-1-length;i--){
		prod = 0;
		for(int j = maxPos-1;j>=maxPos-1-stepProd.getLength();j--){
			tmp = theProd[j] + number[i] * stepProd[j] + prod;
			theProd[j] = tmp%10000;
			prod = tmp/10000;
		}
		stepProd = stepProd.timeTen();
	}
	
	int cnt = 0;
	while(theProd[cnt]==0){
		cnt++;
	}
	theProd.setLength(maxPos-cnt);
	
	return theProd;
}

bool BigInt::operator>(BigInt compInt)
{
	bool flag = 0;
	for(int i = 0;i<maxPos;i++){
		if(number[i]>compInt[i]){
			flag = 1;
			break;
		}else if(number[i]<compInt[i]){
			flag = 0;
			break;
		}
	}
	
	return flag;
}

bool BigInt::operator<(BigInt compInt)
{
	bool flag = 0;
	for(int i = 0;i<maxPos;i++){
		if(number[i]<compInt[i]){
			flag = 1;
			break;
		}else if(number[i]>compInt[i]){
			flag = 0;
			break;
		}
	}
	
	return flag;
}

BigInt BigInt::Sqrt()
{
	BigInt theSqrt;
	int n = length;
	
	n = n/2+1;
	theSqrt.setLength(n); 
	for(int i = maxPos-1;i>maxPos-n;i--){
		theSqrt[i] = 0000;
	}
	
	theSqrt[maxPos-n] = 5000;
	
	BigInt tmp = *this;
	int pos = maxPos-n;
	int count = 3;
	while(pos<maxPos){
		if((theSqrt*(theSqrt+first)).divide2()>tmp){
			theSqrt[pos]-=(int)pow(10,count);
			if(!((theSqrt*(theSqrt+first)).divide2()>tmp)){
				if(count==0){
					if(theSqrt[pos++]==0){
						theSqrt.setLength(n--); 
					}
					count = 3;
				}else{
					count--;
				}
			}else{
				if(count==0 and theSqrt[pos]%10==0){
					if(theSqrt[pos++]==0){
						theSqrt.setLength(n--); 
					}
					count = 3;
				}
				if(theSqrt[pos]/(int)pow(10,count)==0){
					count--;
				}
			}
		}else if((theSqrt*(theSqrt+first)).divide2()<tmp){
			theSqrt[pos]+=pow(10,count);
			if(!((theSqrt*(theSqrt+first)).divide2()<tmp)){
				theSqrt[pos]-=(int)pow(10,count);
				if(count==0){
					if(theSqrt[pos++]==0){
						theSqrt.setLength(n--); 
					}
					count = 3;
				}else{
					count--;
				}
			}else{
				if(count==0 and theSqrt[pos]%10==9){
					if(theSqrt[pos++]==0){
						theSqrt.setLength(n--); 
					}
					count = 3;
				}
				if(theSqrt[pos]/(int)pow(10,count)==9){
					count--;
				}
			}
		}else{
			theSqrt = theSqrt - first;
			break;
		}
	}
	
	int cnt = 0;
	while(theSqrt[cnt]==0){
		cnt++;
	}
	theSqrt.setLength(maxPos-cnt);
	
	return theSqrt;
}

BigInt BigInt::divide2()
{
	BigInt div2;
	
	int div = 0;
	for(int i = 0;i<maxPos;i++){
		div2[i] = (number[i]+div)/2;
		if(number[i]%2==1){
			div = 10000;
		}else{
			div = 0;
		}
	}
	
	return div2;
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

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	BigInt myData;
	myData.initialize();
	
	for(int i = 0;i<maxPos-1;i++){
		second[i] = 0;
	}
	second[maxPos-1] = 2;
	
	for(int i = 0;i<maxPos-1;i++){
		first[i] = 0;
	}
	first[maxPos-1] = 1;

	BigInt theSqrt = myData.Sqrt();
	BigInt theMod = myData - (theSqrt*(theSqrt+first)).divide2();
	theSqrt = theSqrt + first; 
	
	BigInt theFirst;
	BigInt theSecond;
	
	if(theSqrt[maxPos-1]%2==1){
		theFirst = theSqrt+first-theMod;
		theSecond = theMod;
	}else{
		theFirst = theMod;
		theSecond = theSqrt+first-theMod;
	}
	

	theFirst.printInt();
	cout<<'/';
	theSecond.printInt();
	
	cout<<flush;
	
	return 0;
}
