#pragma once

#include <vector>
#include "linearSolver.h"

class Matrix : 
	public implicitMatrix
{
private:
	size_t mRows;
    size_t mCols;
	bool isVector;
   std::vector<std::vector<float>> mData;

public:

	Matrix(size_t rows, size_t cols);
	Matrix(size_t rows);
	
	unsigned int size();
	unsigned int getRowCount();
	unsigned int getColCount();

	float getValue(int row);
	float getValue(int row, int col);
	void setValue(int row, float value);
	void setValue(int row, int col, float value);

	virtual void matVecMult(double x[], double r[]);

	friend Matrix operator-(const Matrix lhs, const Matrix rhs);

	friend Matrix operator*(const Matrix lhs, const float rhs);
	friend Matrix operator*(const Matrix lhs, const Matrix rhs);

	~Matrix(void);   
};

