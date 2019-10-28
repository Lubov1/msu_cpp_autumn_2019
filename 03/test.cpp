#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <assert.h>
#include "Matrix.h"

int main(){
	try{
		const size_t rows = 5;
		const size_t cols = 3;
		Matrix m(rows, cols);

		assert(m.getRows() == 5);
		assert(m.getColumns() == 3);

		m[1][2] = 5; // строка 1, колонка 2
		assert(m[1][2]==5);
		double x = m[4][1];
		//cout<<m[5][0];
		//cout<<m[-1][0];
		//cout<<m[0][7];

		assert(x==1);
		m *= 3; // умножение на число
		m*=5;
		Matrix m1(rows, cols);
		Matrix m2(rows, cols);
		assert(!(m1 == m));
		assert(m1 == m2);
		// cout<<m;
		// cout<<m1;
	}
	catch (exception &err){
		cout<<"error";
	}

	



}