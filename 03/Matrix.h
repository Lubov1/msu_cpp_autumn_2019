#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <assert.h>

using namespace std;
class Matrix{
	int **A;
	int rows;
	int cols;
public:
	class Row{
	public:
		int *row;
		int kol_cols;
		Row(int* s,int kol_cols){row=s;this->kol_cols=kol_cols;}
		int& operator[](int r){
			if (r>=kol_cols || r<0)
				throw out_of_range("");
			return row[r];
		}
	};
	Matrix(int n,int m);
	~Matrix();
	int getRows();
	int getColumns();
	const Matrix& operator*=(const int& a);
	bool operator==(const Matrix& other) const;
	friend ostream & operator<<(ostream & out, const Matrix & matr);
	Row  operator[](int r);

};

Matrix::Matrix( int n, int m){
	rows = n;
	cols = m;
	A = new int*[rows];
	for (int i = 0; i < rows; i++){
		A[i] = new int[m];
	}
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
				A[i][j] = 1;
}
Matrix::~Matrix(){
	if (A != NULL){
		for (int i = 0; i < rows; i++)
			if(A[i] != NULL)
				delete[] A[i];
		delete[] A;
	}
}
int Matrix::getRows(){
		return rows;
	}
int Matrix::getColumns(){
		return cols;
	}
bool Matrix::operator==(const Matrix& other)const {
        if (this == &other)
            return true;
        for (int i = 0; i < rows; ++i)
        	for (int j = 0; j < cols; ++j)
        		if (this->A[i][j] != other.A[i][j])
        			return false;    
        return true;
    }
const Matrix&  Matrix::operator*=(const int& a){
	for (int i = 0; i < rows; ++i){
    	for (int j = 0; j < cols; ++j)
    		A[i][j] *= a;

    }

    return *this;
}
ostream & operator<<(ostream & out, const Matrix & matr){
	for (int i = 0; i < matr.rows; i++){
		for (int j = 0; j < matr.cols; j++){
			out << matr.A[i][j] << ' ';
			}
	out << endl;
	}
	return out;
}
Matrix::Row Matrix::operator[](int r){
	if (r>=rows || r<0)
		throw out_of_range("");
	return Row(A[r],cols);
}




