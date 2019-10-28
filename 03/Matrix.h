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
		int kol_cols;
		Row(int* s,int kol_cols);
		int& operator[](int r);
	};
	Matrix(int n,int m);
	~Matrix();
	int getRows();
	int getColumns();
	Matrix& operator*=(const int& a);
	bool operator==(const Matrix& other) const;
	friend ostream & operator<<(ostream & out, const Matrix & matr);
	Row  operator[](int r);

};

