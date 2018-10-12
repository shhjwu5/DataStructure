#include <iostream>
#include <iomanip>
 
using namespace std;

int main()
{
	cout.setf(ios::showpoint);
	cout.precision(3);
	cout.setf(ios::fixed);  
	
	int n = 0;
	cin>>n;
	
	int car = 0;
	int van = 0;
	
	int* carList = new int [n];
	int* vanList = new int [n];
	
	int tmp = 0;
	for(int i = 0;i<n;i++){
		cin>>tmp;
		if(tmp){
			cin>>vanList[van];
			van++;
		}else{
			cin>>carList[car];
			car++;
		}
	}
	
	int totalCar = car;
	int totalVan = van;
	
	int totalCarTime = 0;
	int totalVanTime = 0;
	
	int time = 0;
	int currCar = 0;
	int currVan = 0;
	while(car+van>0){
		currCar = 0;
		currVan = 0;
		while(totalCar-car<totalCar and carList[totalCar-car]<=time and currCar<8){
			totalCarTime = totalCarTime + time - carList[totalCar-car];
			currCar++;
			car--;
		}
		while(totalVan-van<totalVan and vanList[totalVan-van]<=time and currVan<2){
			totalVanTime = totalVanTime + time - vanList[totalVan-van];
			currVan++;
			van--;
		}
		
		while(totalCar-car<totalCar and carList[totalCar-car]<=time and currCar+currVan<10){
			totalCarTime = totalCarTime + time - carList[totalCar-car];
			currCar++;
			car--;
		}
		while(totalVan-van<totalVan and vanList[totalVan-van]<=time and currCar+currVan<10){
			totalVanTime = totalVanTime + time - vanList[totalVan-van];
			currVan++;
			van--;
		}
		time = time+10;
	}
	
	cout<<totalCarTime/float(totalCar)<<' '<<totalVanTime/float(totalVan)<<endl;
	
	return 0;
}
