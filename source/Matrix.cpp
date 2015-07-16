#include "Matrix.h"

Matrix::Matrix(size_t rows, size_t cols) :
	mRows(rows), mCols(cols)
{
	mData = std::vector<std::vector<float>>(rows, std::vector<float>(cols));
	isVector = false;
}

Matrix::Matrix(size_t rows)
	: mRows(rows), mCols(1)
{
	mData = std::vector<std::vector<float>>(rows, std::vector<float>(1));
	isVector = true;
}

unsigned int Matrix::size() {
	return mRows * mCols;
}

unsigned int Matrix::getRowCount() {
	return mRows;
}

unsigned int Matrix::getColCount() {
	return mCols;
}

float Matrix::getValue(int row) {
	return getValue(row, 0);
}

float  Matrix::getValue(int row, int col) {
	return mData[row][col];
}

void Matrix::setValue(int row, float value) {
	setValue(row, 0, value);
}

void Matrix::setValue(int row, int col, float value) {
	mData[row][col] = value;
}

void Matrix::matVecMult(double x[], double r[]) {
	for (unsigned int i = 0; i< mData.size(); i++) {
		r[i] = 0;
		for (unsigned int j = 0; j < mData[0].size(); j++){
			r[i] += mData[i][j] * x[j];
		}
	}
}

Matrix operator-(Matrix lhs, Matrix rhs)
{
	int minRows = lhs.mRows < rhs.mRows ? lhs.mRows : rhs.mRows;
	int minCols = lhs.mCols < rhs.mCols ? lhs.mCols : rhs.mCols;
	Matrix output = Matrix::Matrix(minRows, minCols);

	if (lhs.mRows != rhs.mRows || lhs.mCols != rhs.mCols) {
		printf("ERROR: Matrix subtract operator, matrix has no equal size");
		return output;
	}

	for (int i = 0; i < minRows; i++) 
	{
		for (int j = 0; j < minCols; j++) 
		{
			output.mData[i][j] = lhs.mData[i][j] - rhs.mData[i][j];
		}
	}

	return output;
}

Matrix operator*(Matrix lhs, const float rhs)
{
	Matrix output = Matrix::Matrix(lhs.mRows, lhs.mCols);
	for (unsigned int i = 0; i < lhs.mRows; i++) 
	{
		for (unsigned int j = 0; j < lhs.mCols; j++) 
		{
			output.mData[i][j] = lhs.mData[i][j] * rhs;
		}
	}
	return output;
}

Matrix operator*(Matrix lhs, Matrix rhs)
{
	Matrix output = Matrix::Matrix(lhs.mRows, rhs.mCols);
	for (unsigned int i = 0; i < lhs.mRows; i++) 
	{
		for (unsigned int j = 0; j < rhs.mCols; j++) 
		{
			for (unsigned int k = 0; k < lhs.mCols; k++)
			{
				output.mData[i][j] += (lhs.mData[i][k] * rhs.mData[k][j]);
			}
		}
	}
	return output;
}

Matrix::~Matrix(void)
{
}
