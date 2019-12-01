#include <iterator>
#include <iostream>
#include <stdlib.h>
#include <exception>
#include <stdexcept>
#include <assert.h>
#include <string>

#include "Vector.h"

using namespace std;


int main(){

	size_t size = 4;
	Vector<int> v(size, 7);
	for (int i = 0; i < v.size(); i++)
		assert(v[i] == 7);
	v.push_back(23);
	assert(size + 1 == v.size());
	assert(v[v.size() - 1] == v.pop_back());
	v[0] = 6;
	assert(v[0] == 6);
	Vector<int> v1(3);
	Iterator<int> t = v1.begin();
	for (int j = 0; j < v1.size();j++,++t)
		assert(v1[j] == *t);
	Vector<string> v3(5,"yes");
	Iterator<string> t3 = v3.begin();

	for (int j = 0; j < v3.size();j++,++t3)
		assert(v3[j] == *t3);

}