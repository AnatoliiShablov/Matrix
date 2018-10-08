#pragma once
#include <cstdio>
#include <vector>

class Matrix
{
private:

	std::vector<double> matrix;
	size_t height;
	size_t width;
	void resize();
	bool empty() const;
public:

	Matrix();
	Matrix(Matrix const &getted);
	Matrix(std::vector<std::vector<double>> const &getted);

	void scanMatrix(FILE* &input, size_t height, size_t width);
	void scanMatrix(FILE* &input);
	void printMatrix(FILE* &output) const;
	
	double determinant() const;
	double minor(size_t  _line, size_t  _column) const;
	double algebraicComplement(size_t  _line, size_t  _column) const;

	Matrix operator +(Matrix const &add) const;
	Matrix operator -(Matrix const &rem) const;
	Matrix operator *(double const &alpha) const;
	Matrix operator /(double const &alpha) const;
	Matrix operator *(Matrix const &getted) const;

	bool operator ==(Matrix const &getted) const;
	bool operator !=(Matrix const &getted) const;

	void operator +=(Matrix const &add);
	void operator -=(Matrix const &rem);
	void operator *=(double const &alpha);
	void operator /=(double const &alpha);
	void operator *=(Matrix const &getted);

	Matrix transpose() const;
	Matrix inverse() const;
};

Matrix operator*(double const alpha, Matrix const &getted);
void transpose(Matrix &getted);
void inverse(Matrix &getted);