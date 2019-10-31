#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "Matrix.h"


Matrix::Row::Row(int* s,size_t kol_cols){
	row=s;
	this->kol_cols=kol_cols;
}
int& Matrix::Row::operator[](size_t r){
	if (r>=kol_cols || r<0)
		throw out_of_range("");
	return row[r];
}

Matrix::Matrix( size_t n, size_t m){
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
size_t Matrix::getRows(){
	return rows;
}
size_t Matrix::getColumns(){
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
Matrix&  Matrix::operator*=(const int& a){
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
Matrix::Row Matrix::operator[](size_t r){
	if (r>=rows || r<0)
		throw out_of_range("");
	return Row(A[r],cols);
}



