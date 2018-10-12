#include <iostream>
#include <iomanip>

using namespace std;

class MyComplex
{
	friend ostream &operator<<(ostream &, const MyComplex &);
	friend ostream &operator<<(ostream &, const MyComplex &);
	
	friend MyComplex operator+(const MyComplex &, const MyComplex &);
	friend MyComplex operator-(const MyComplex &, const MyComplex &);
	friend MyComplex operator*(const MyComplex &, const MyComplex &);
	friend MyComplex operator/(const MyComplex &, const MyComplex &);

private:
  	double x,y;
public:
	MyComplex(double,double);
	
	double getX() const;
	double getY() const;
	void write(double, double);
	
	MyComplex operator+=(const MyComplex &);
	MyComplex operator-=(const MyComplex &);
	MyComplex operator*=(const MyComplex &);
	MyComplex operator/=(const MyComplex &);
};

MyComplex::MyComplex(double a=0.0, double b=0.0)
{
	x=a,y=b;
}

void MyComplex::write(double a, double b)
{
	x = a;
	y = b;
}

ostream &operator<<(ostream &os, const MyComplex &r)
{
	
	os.setf(ios::showpoint);
	os.precision(2);
	os.setf(ios::fixed);  	
	os<<r.x<<' '<<r.y;
	
	return os;
}

double MyComplex::getX() const
{
	return x;
}

double MyComplex::getY() const
{
	return y;
}

istream &operator>>(istream &is, MyComplex &r)
{
	double a = 0.0, b = 0.0;
	is>>a>>b;
	r.write(a,b);
		
	return is;
}

MyComplex operator+(const MyComplex &r1, const MyComplex &r2)
{
	return MyComplex(r1.getX()+r2.getX(),r1.getY()+r2.getY());
}

MyComplex operator-(const MyComplex &r1, const MyComplex &r2)
{
	return MyComplex(r1.getX()-r2.getX(),r1.getY()-r2.getY());
}

MyComplex operator*(const MyComplex &r1, const MyComplex &r2)
{
	return MyComplex(r1.getX()*r2.getX()-r1.getY()*r2.getY(),r1.getX()*r2.getY()+r1.getY()*r2.getX());
}

MyComplex operator/(const MyComplex &r1, const MyComplex &r2)
{
	double base = r2.getX()*r2.getX()+r2.getY()*r2.getY();
	return MyComplex((r1.getX()*r2.getX()+r1.getY()*r2.getY())/base,(-r1.getX()*r2.getY()+r1.getY()*r2.getX())/base);
}

MyComplex MyComplex::operator+=(const MyComplex &r)
{
	x += r.getX();
	y += r.getY();
	
	return *this;
}

MyComplex MyComplex::operator-=(const MyComplex &r)
{
	x -= r.getX();
	y -= r.getY();
	
	return *this;
}

MyComplex MyComplex::operator*=(const MyComplex &r)
{
	double oriX = x, oriY = y;	
	x = oriX*r.getX()-oriY*r.getY();
	y = oriX*r.getY()+oriY*r.getX();
	
	return *this;
}

MyComplex MyComplex::operator/=(const MyComplex &r)
{
	double oriX = x, oriY = y;
	double base = r.getX()*r.getX()+r.getY()*r.getY();
	x = (oriX*r.getX()+oriY*r.getY())/base;
	y = (-oriX*r.getY()+oriY*r.getX())/base;
	
	return *this;
}

int main()
{
  MyComplex z1;
  MyComplex z2;

  cin >> z1 >> z2;

  cout << z1 + z2 <<endl;
  cout << z1 - z2 <<endl;
  cout << z1 * z2 <<endl;
  cout << z1 / z2 <<endl;
  cout << (z1 += z2) <<endl;
  cout << (z1 -= z2) <<endl;
  cout << (z1 *= z2) <<endl;
  cout << (z1 /= z2) <<endl;

  return 0;
}
