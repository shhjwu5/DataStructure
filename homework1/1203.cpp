#include <iostream>
#include <cstring> 

using namespace std;

template <class T> class linearList;
template <class T> istream &operator>>(istream &, linearList<T> &);
template <class T> ostream &operator<<(ostream &, const linearList<T> &);
template <class T> linearList<T> operator+(const linearList<T> &, const linearList<T> &);

template <class T>
class linearList
{
    friend istream &operator>>(istream &is, linearList<T> &inputList){
    	int len = inputList.getLen();
    	T a;
    	for (int i=0;i<len;i++){
        	is>>a;
        	inputList.input(i,a);
    	}

    	return is;
	};
    friend ostream& operator<<(ostream &os, const linearList<T> &outputList){
    	int len = outputList.getLen();
   		for (int i=0;i<len;i++){
        	os<<outputList.getList(i)<<' ';
    	}
    	os<<endl;

    	return os;
	};
    friend linearList<T> operator+(const linearList<T> &list1, const linearList<T> &list2){
    	int firstLen = 0,secondLen = 0;
    	firstLen = list1.getLen();
    	secondLen = list2.getLen();
    	int newLen = 0;
    	newLen = firstLen + secondLen;
    	linearList<T> newList (newLen);
    	for (int i=0;i<firstLen;i++){
        	newList.input(i,list1.getList(i));
    	}
    	for (int i=0;i<secondLen;i++){
        	newList.input(firstLen+i, list2.getList(i));
    	}

    	return newList;
	};
private:
    int length = 0;
    T* list;
public:
    linearList<T>(int len){
        length = len;
    	list = new T [length];	
	};
	void input(int pos, T value){
		list[pos] = value;
	};
	T getList(int pos) const {
		return list[pos];
	};
    int getLen() const {
    	return length;
	};
    ~linearList<T>(){
    	delete list;
	};
};

int main()
{
	char p[6];
	cin>>p;
    int len1=0,len2=0;
    cin>>len1>>len2;
    if (p[0]=='i'){
    	linearList<int> list1(len1);
    	linearList<int> list2(len2);
    	cin>>list1;
    	cin>>list2;
    	cout<<list1+list2;
	}else if(p[0]=='d'){
		linearList<double> list1(len1);
    	linearList<double> list2(len2);
    	cin>>list1;
    	cin>>list2;
    	cout<<list1+list2;
	}else{
		linearList<char> list1(len1);
    	linearList<char> list2(len2);
    	cin>>list1;
    	cin>>list2;
    	cout<<list1+list2;
	}
	

    return 0;
}

