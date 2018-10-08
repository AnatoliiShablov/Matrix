#include "Matrix.h"

void Matrix::resize()
{
	this->matrix.assign((this->height)*(this->width), 0);
}

bool Matrix::empty() const
{
	return ((this->height)&&(this->width));
}

Matrix::Matrix()
{
	this->width = 0;
	this->height = 0;
}

Matrix::Matrix(Matrix const & getted)
{
	this->matrix = getted.matrix;
	this->height = getted.height;
	this->width = getted.width;
}

Matrix::Matrix(std::vector<std::vector<double>> const &getted)
{
	this->height = getted.size();
	if (this->height)
	{
		this->width = getted[0].size();
	}
	else
	{
		this->width = 0;
	}
	this->resize();
	size_t it = 0;

	for (std::vector<double> const &line : getted)
	{
		for (double const &element : line)
		{
			this->matrix[it++] = element;
		}
	}
}

void Matrix::scanMatrix(FILE* &input, size_t height, size_t width)
{
	this->width = width;
	this->height = height;
	this->resize();
	for (size_t it = 0; it < height*width; it++)
	{
		std::fscanf(input, "%lf", &this->matrix[it]);
	}
}

void Matrix::scanMatrix(FILE* &input)
{
	size_t height(0);
	size_t width(0);
	std::fscanf(input, "%d%d", &height, &width);
	this->scanMatrix(input, height, width);
}

void Matrix::printMatrix(FILE* &output) const
{
	for (size_t it = 0; it < (this->height)*(this->width); it++)
	{
		std::fprintf(output, "%lf ", this->matrix[it]);
		if ((it) && !(it%width))std::fprintf(output, "\n");
	}
}

double Matrix::determinant() const
{
	if (this->height != this->width)
	{
		std::perror("Nonsquare matrix");
		return NULL;
	}
	if (!this->empty())
	{
		std::perror("Empty matrix");
		return NULL;
	}
	std::vector<double> subMatrix = this->matrix;
	int sign = 1;
	size_t n = this->height;
	for (size_t mainColumn = 0; mainColumn < n; mainColumn++)
	{
		if (subMatrix[mainColumn*mainColumn] == 0)
		{
			size_t change = 0;
			for (change = mainColumn; ((change < n) && (subMatrix[change][mainColumn] == 0)); change++) {}
			if (change == n)
			{
				return 0;
			}

			if (change != mainColumn)
			{
				std::swap(subMatrix[change], subMatrix[mainColumn]);
				-sign;
			}
		}
		for (size_t subColumn = mainColumn + 1; subColumn < n; subColumn++)
		{

			double factor = subMatrix[mainColumn][subColumn] / subMatrix[mainColumn][mainColumn];
			for (size_t i = mainColumn; i < n; i++)
			{
				subMatrix[i][subColumn] -= factor * subMatrix[i][mainColumn];
			}
		}
	}
	double result = 1;
	for (size_t i = 0; i < this->height; i++)
	{
		result *= subMatrix[i][i];
	}
	result *= sign;
	return result;
}

double Matrix::minor(size_t _line, size_t _column) const
{
	_line--;
	_column--;
	if ((this->height < 2) || (this->width < 2))
	{
		std::perror("Too small for minor");
		return NULL;
	}
	Matrix newMatrix;
	newMatrix.height = this->height - 1;
	newMatrix.width = this->width - 1;
	newMatrix.resize();
	for (size_t line(0), i(0); line < newMatrix.height; line++, i++)
	{
		if (i == _line) i++;
		for (size_t column(0), j(0); column < newMatrix.width; column++, j++)
		{
			if (j == _column) j++;
			newMatrix.matrix[line][column] = this->matrix[i][j];
		}
	}
	return newMatrix.determinant();
}

double Matrix::algebraicComplement(size_t const _line, size_t const _column) const
{
	return ((((_line + _column) % 2) ? -1 : 1) * (this->minor(_line, _column)));
}

Matrix Matrix::operator+(Matrix const & add) const
{
	if ((this->height != add.height) || (this->width != add.width))
	{
		return Matrix();
		std::perror("Sum of level-different matrixes");
	}
	Matrix result(add);
	for (size_t i = 0; i < result.height; i++)
	{
		for (size_t j = 0; j < result.width; j++)
		{
			result.matrix[i][j] += this->matrix[i][j];
		}
	}
	return result;
}

Matrix Matrix::operator-(Matrix const & rem) const
{
	if ((this->height != rem.height) || (this->width != rem.width))
	{
		return Matrix();
		std::perror("Sum of level-different matrixes");
	}
	Matrix result;
	result.height = this->height;
	result.width = this->width;
	result.resize();
	for (size_t i = 0; i < result.height; i++)
	{
		for (size_t j = 0; j < result.width; j++)
		{
			result.matrix[i][j] = this->matrix[i][j] - rem.matrix[i][j];
		}
	}
	return result;
}

Matrix Matrix::operator*(double const & alpha) const
{
	Matrix result;
	result.height = this->height;
	result.width = this->width;
	result.resize();
	for (size_t i = 0; i < result.height; i++)
	{
		for (size_t j = 0; j < result.width; j++)
		{
			result.matrix[i][j] = this->matrix[i][j] * alpha;
		}
	}
	return result;
}

Matrix Matrix::operator/(double const & alpha) const
{
	return *this*(1/alpha);
}

Matrix Matrix::operator*(Matrix const & getted) const
{
	if (this->width != getted.height)
	{
		std::perror("Width != Height in multiply");
		return Matrix();
	}
	size_t length = this->width;
	Matrix result;
	result.height = this->height;
	result.width = getted.width;
	result.resize();
	for (size_t line = 0; line < result.height; line++)
	{
		for (size_t column = 0; column < result.width; column++)
		{
			for (size_t i = 0; i < length; i++)
			{
				result.matrix[line][column] += this->matrix[line][i] * getted.matrix[i][column];
			}
		}
	}
	return result;
}

bool Matrix::operator==(Matrix const & getted) const
{
	if ((this->height != getted.height) || (this->width != getted.width))
	{
		return false;
	}
	for (size_t line = 0; line < this->height; line++)
	{
		for (size_t column = 0; column < this->width; column++)
		{
			if (this->matrix[line][column] != getted.matrix[line][column])
				return false;
		}
	}
	return true;
}

bool Matrix::operator!=(Matrix const & getted) const
{
	return !(*this==getted);
}

void Matrix::operator+=(Matrix const & add)
{
	*this = *this + add;
}

void Matrix::operator-=(Matrix const & rem)
{
	*this = *this - rem;
}

void Matrix::operator*=(double const & alpha)
{
	*this = *this * alpha;
}

void Matrix::operator/=(double const & alpha)
{
	*this = *this / alpha;
}

void Matrix::operator*=(Matrix const & getted)
{
	*this = *this * getted;
}

Matrix Matrix::transpose() const
{
	Matrix result;
	result.height = this->width;
	result.width = this->height;
	result.resize();
	for (size_t line = 0; line < result.height; line++)
	{
		for (size_t column = 0; column < result.width; column++)
		{
			result.matrix[line][column] = this->matrix[column][line];
		}
	}
	return result;
}

Matrix Matrix::inverse() const
{
	double determinant = this->determinant();
	if (!(determinant))
	{
		std::perror("Determinant = NULL");
		return Matrix();
	}
	Matrix result;
	result.height = this-> height;
	result.width = this-> width;
	result.resize();
	for (int i = 0; i < result.height; i++)
	{
		result.matrix[i][i] = 1;
	}
	std::vector<std::vector<double>> getted = this->matrix;
	size_t n = this->width;
	for (size_t mainColumn = 0; mainColumn < n - 1; mainColumn++)
	{
		if (getted[mainColumn][mainColumn] == 0)
		{
			size_t change = 0;
			for (change = mainColumn; ((change < n) && (getted[change][mainColumn] == 0)); change++) {}
			if (change != mainColumn)
			{
				std::swap(getted[change], getted[mainColumn]);
				std::swap(result.matrix[change], result.matrix[mainColumn]);
			}
		}
		for (size_t subLine = mainColumn + 1; subLine < n; subLine++)
		{

			double factor = getted[subLine][mainColumn] / getted[mainColumn][mainColumn];
			for (size_t i = 0; i < n; i++)
			{
				getted[subLine][i] -= factor * getted[mainColumn][i];
				result.matrix[subLine][i] -= factor * result.matrix[mainColumn][i];
			}
		}

	}

	for (size_t mainColumn = n-1; mainColumn  > 0; mainColumn--)
	{
		for (size_t subLine = mainColumn - 1; subLine--;)
		{

			double factor = getted[subLine][mainColumn] / getted[mainColumn][mainColumn];
			for (size_t i = 0; i < n; i++)
			{
				getted[subLine][i] -= factor * getted[mainColumn][i];
				result.matrix[subLine][i] -= factor * result.matrix[mainColumn][i];
			}
		}
	}
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			result.matrix[i][j] /= getted[i][i];
		}
	}
	return result;
}

Matrix operator*(double const alpha, Matrix const & getted)
{
	return (getted*alpha);
}

void transpose(Matrix & getted)
{
	getted = getted.transpose();
}

void inverse(Matrix & getted)
{
	getted = getted.inverse();
}
