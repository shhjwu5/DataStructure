#include <iostream>
#include <fstream> 

using namespace std;

int main()
{
	ifstream infile("input.in",ifstream::in);
	ofstream outfile("output.out",ofstream::out);
	
	ios::sync_with_stdio(0);
	infile.tie(0);
	outfile.tie(0);
	
	int a, b, c;
	infile>>a>>b>>c;
	
	outfile<<c<<b<<a<<endl;
	outfile<<flush;
	
	return 0;
}
