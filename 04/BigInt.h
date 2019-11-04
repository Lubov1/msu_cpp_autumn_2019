#include <iostream>
#include <cstdint>
#include <fstream>
#include <stdlib.h>
#include <exception>
using namespace std;

class BigInt{
	bool s;//==true если число <0
	char* data;
	int size;
public:
	BigInt(const int&a);
	~BigInt();
	BigInt(const BigInt& a);
	friend ostream & operator<<(ostream & out, const BigInt & a);
	BigInt& operator=(const BigInt& a);
	BigInt operator-()const;

	BigInt(BigInt&& moved);

	BigInt& operator=(BigInt&& moved);

	friend BigInt operator+(const BigInt& a,const BigInt& b);
	friend BigInt operator-(const BigInt& a,const BigInt& b);

	friend bool operator==(const BigInt& a,const BigInt& b);
	friend bool operator>=(const BigInt& a,const BigInt& b);
	friend bool operator!=(const BigInt& a,const BigInt& b);
	friend bool operator<=(const BigInt& a,const BigInt& b);
	friend bool operator>(const BigInt& a,const BigInt& b);
	friend bool operator<(const BigInt& a,const BigInt& b);


};

