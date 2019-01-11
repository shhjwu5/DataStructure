#ifndef CHARLIST_H
#define CHARLIST_H

using namespace std;

class Charlist{
	friend Charlist operator+(const Charlist &s1, const Charlist &s2);
	friend bool operator==(const Charlist &s1, const Charlist &s2);
	friend bool operator!=(const Charlist &s1, const Charlist &s2);
	friend bool operator>(const Charlist &s1, const Charlist &s2);
	friend bool operator>=(const Charlist &s1, const Charlist &s2);
	friend bool operator<(const Charlist &s1, const Charlist &s2);
	friend bool operator<=(const Charlist &s1, const Charlist &s2);
	friend ostream &operator<<(ostream &os, const Charlist &s);
	
	struct charNode{
		int size;
		char* myData;
		
	};
}; 

#endif 
