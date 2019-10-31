#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <assert.h>

using namespace std;
class Matrix{
	int **A;
	size_t rows;
	size_t cols;
public:
	class Row{
	public:
		int *row;
		size_t kol_cols;
		Row(int* s,size_t kol_cols);
		int& operator[](size_t r);
	};
	Matrix(size_t n,size_t m);
	~Matrix();
	size_t getRows();
	size_t getColumns();
	Matrix& operator*=(const int& a);
	bool operator==(const Matrix& other) const;
	friend ostream & operator<<(ostream & out, const Matrix & matr);
	Row  operator[](size_t r);
};