#include <iostream>
#include <cstdint>
#include <fstream>
#include <stdlib.h>
#include <exception>
#include "BigInt.h"
using namespace std;



BigInt::BigInt(const int a=0){
	if (a >= 0)
		s = false;
	else 
		s = true;
	string b = to_string(a);
	if (s){
		data = new char[b.length() - 1];
		size = b.length() - 1;
		for (int i = 0;i < b.length() - 1;i++)
		data[i] = b[i + 1];
	}
	else{
		data = new char[b.length()];
		size = b.length();
		for (int i = 0;i < b.length();i++)
		data[i]=b[i];
	}
}

BigInt::~BigInt(){
	delete[] data;
}
BigInt::BigInt(const BigInt& a){
	size = a.size;
	s = a.s;
	data=new char[a.size];
	for (int i = 0;i < a.size;i++)
		data[i] = a.data[i];
}
BigInt& BigInt::operator=(const BigInt& a){
	if (this == &a)
		return *this;
	char* ptr = new char[a.size];
	delete[] data;
	data = ptr;
	size = a.size;
	s=a.s;
	copy(a.data, a.data + size, data);
	return *this;
}
BigInt operator+(const BigInt& a,const BigInt& b){
	int c;
	bool f = false;
	BigInt res;
	char* ptr,*s1,*s2;
	int s1l,s2l;
	if (a.size > b.size){
		s1 = a.data;
		s2 = b.data;
		s1l = a.size;
		s2l = b.size;
	}
	else{
		s1 = b.data;
		s2 = a.data;
		s1l = b.size;
		s2l = a.size;
	}
	if (b.s == a.s){
		if (a.size == b.size){
			ptr=new char[a.size];
			for(int i = a.size - 1;i >= 0;i--){
				c = int(a.data[i] - '0') + int(b.data[i + b.size - a.size] - '0');
				if (f) c++;
				if (c > 9) {f = true; ptr[i] = char(c - 10 + '0');}
				else {f = false; ptr[i] = char(c + int('0'));}
			}
		}
		else{
			ptr = new char[s1l];
			for(int i = s1l - 1;i >= s1l - s2l;i--){
				c = int(s1[i] - '0') + int(s2[i + s2l - s1l] - '0');
				if (f) c++;
				if (c > 9) {f = true; ptr[i] = char(c - 10 + '0');}
				else {f = false; ptr[i] = char(c + int('0'));}
			}
			for(int i = s1l - s2l - 1;i >= 0;i--){
				if (f){
					c = int(s1[i] - '0');
					if (f) c++;
					if (c > 9) {f = true; ptr[i] = char(c - 10 + '0');}
					else {f = false; ptr[i] = char(c + int('0'));}
				}
				else
					ptr[i] = s1[i];
			}
		}
		if (f) {
			delete[] res.data;
			res.data = new char[s1l + 1];
			res.size = s1l + 1;
			for (int i = 1;i <= s1l;i++) res.data[i] = ptr[i - 1];
			res.data[0] = '1';
			delete[] ptr;
		}
		else{
			delete[] res.data;
			res.data = ptr;
			res.size = s1l;
		}
		res.s = a.s;
		return res;
	}
	if(a == (-b))
		return 0;
	if(!a.s)
		return a - (-b);
	else
		return b - (-a);
}
BigInt operator-(const BigInt& a,const BigInt& b){
	int c;
	bool f = false;
	BigInt res;
	char* ptr,*s1,*s2;
	int s1l,s2l,s1_sig,s2_sig;
	if (((a >= b) && (!a.s)) || ((a <= b) && a.s))
		{s1 = a.data; s2 = b.data; s1l = a.size; s2l = b.size; s1_sig = b.s; s2_sig = a.s;}
	else  
		{s1 = b.data; s2 = a.data; s1l = b.size; s2l = a.size; s1_sig = b.s; s2_sig = a.s;}
	if (b.s == a.s){
		if (s1l == s2l){
			ptr = new char[s1l];
			for(int i = s1l-1;i >= 0;i--){
				c = int(s1[i] - '0') - int(s2[i] - '0');
				if (f) c--;
				if (c < 0) {f = true; ptr[i] = char(c + 10 + '0');}
				else {f = false; ptr[i] = char(c + int('0'));}
			}
		}
		else{
			ptr = new char[s1l];
			for(int i = s1l - 1;i >= s1l - s2l;i--){
				c=int(s1[i] - '0') - int(s2[i + s2l - s1l] - '0');
				if (f) c--;
				if (c < 0) {f = true; ptr[i] = char(c + 10 + '0');}
				else {f = false; ptr[i] = char(c + int('0'));}
			}
			for(int i=s1l-s2l-1;i>=0;i--){
				if (f){
					c=int(s1[i]-'0');
					if (f) c--;
					if (c < 0) {f=true; ptr[i] = char(c + 10 + '0');}
					else {f = false; ptr[i] = char(c + int('0'));}
				}
				else
					ptr[i] = s1[i];
			}
		}
		int k = 0;
		for (k;(k < s1l) && (ptr[k] == '0');k++);
		if (k > 0){
			res.size = s1l - k;
			if (res.size == 0){
				res.size = 1;
				delete[] res.data;
				res.data = new char[1];
				res.data[0] = '0';
				delete[] ptr;
			}
			else{
				delete[] res.data;
				res.data = new char[res.size];
				for (int i = k;i < s1l;i++) res.data[i - k] = ptr[i];
				delete[] ptr;
			// res.data=ptr;
			}
		} 
		else{
			delete[] res.data;
			res.data = ptr;
			res.size = s1l;
		}
		if(!a.s)
			res.s = (a<=b);
		else
			res.s = (a<=b);

		return res;
	}
	if (a == b)
		return 0;
	if (!a.s)
		return a + (-b);
	else
		return b + (-a);

}
bool operator==(const BigInt& a,const BigInt& b){
	if (&b == &a)
		return true;
	if((a.size != b.size) && (a.s != b.s))
		return false;
	for (int i = 0;i < a.size;i++)
		if (a.data[i] != b.data[i])
			return false;
	return true;
}
bool operator!=(const BigInt& a,const BigInt& b){
	if(a == b)
		return false;
	return true;
}
bool operator>(const BigInt& a,const BigInt& b){
	if (a.s != b.s)
		return !a.s;
	if(a.size > b.size){
		return !a.s;
	}
	if((a.size < b.size))
		return a.s;
	if (!a.s){
		for (int i = 0;i < a.size;i++)
			if(a.data[i] != b.data[i])
				return (a.data[i] > b.data[i]);
	}
	else{
		for (int i = 0;i < a.size;i++)
			if(a.data[i] != b.data[i])
				return (a.data[i] < b.data[i]);
	}
	return false;
}
bool operator<(const BigInt& a,const BigInt& b){
	return b > a;
}
bool operator>=(const BigInt& a,const BigInt& b){
	return (a > b) || (a == b);
}
bool operator<=(const BigInt& a,const BigInt& b){
	return b >= a;
}

BigInt BigInt::operator-()const{
	BigInt a = *this;
	if (s)
		a.s = false;
	else
		a.s = true;
	return a;
}




ostream & operator<<(ostream & out, const BigInt & a){
	if (a.s)
		out<<'-';
	for (int i = 0; i < a.size; i++)
		out << a.data[i] ;
	out << endl;
	return out;
}




BigInt::BigInt(BigInt&& moved): data(moved.data), size(moved.size), s(moved.s){
	moved.data = nullptr;
	moved.size = 0;
}

BigInt& BigInt::operator=(BigInt&& moved){
	if (this == &moved)
		return *this;
	delete[] data;
	data= moved.data;
	size = moved.size;
	s = moved.s;
	moved.data = nullptr;
	moved.size = 0;
	return *this;
}
