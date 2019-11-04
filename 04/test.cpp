#include <iostream>
#include <cstdint>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <exception>
#include <assert.h>
#include "BigInt.h"
using namespace std;




int main(){
	try{
		BigInt d(111);
		BigInt g(10);
		BigInt s(230);
		BigInt q1(99);

		assert(g-d == -101);
		assert(d-g ==101);
		assert(d-s == (-119));

		d=-d;g=-g;s=-s;

		assert(g-d == 101);
		assert(d-g == -101);
		assert(d-s == 119);

		assert(g+d == -121);
		assert(d+g == -121);
		assert(d+s == -341);

		d=-d;g=-g;s=-s;

		assert(g+d == 121);
		assert(d+g == 121);
		assert(d+s == 341);

		assert(g+(-d) == -101);
		assert(d+(-g) == 101);
		assert(d+(-s) == -119);

		assert(q1+g == 109);
		assert(g+10000 == 10010);
		assert(q1-19345 == -19246);
		assert(q1-99 == 0);

		assert(q1 == q1);
		assert(q1>g);
		assert(-q1>-s);
		assert(-s<0);

		assert((s+g+d+q1+5+100000) == 100455);
	}
	catch (exception &err){
		cout<<"error";
	}
}