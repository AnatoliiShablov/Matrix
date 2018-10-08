#include "Matrix.h"

void Matrix::resize()
{
	this->matrix.assign((this->height)*(this->width), 0);
}

bool Matrix::empty() const
{
	return ((this->height) && (this->width));
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
	for (size_t line = 0; line < n; line++)
	{
		if (!subMatrix[line*(n + 1)])
		{
			size_t lineswap(0);
			for (lineswap = line; (lineswap < n) && (!subMatrix[lineswap*n + line]); lineswap++) {}
			if (lineswap == n)
			{
				return 0;
			}
			for (size_t swapper = n; swapper--;)
			{
				double temp = subMatrix[line*n + swapper];
				subMatrix[line*n + swapper] = subMatrix[lineswap*n + swapper];
				subMatrix[lineswap*n + swapper] = temp;
			}
			sign = -sign;
		}
		for (size_t extraLine = line + 1; extraLine < n; extraLine++)
		{
			double factor = subMatrix[extraLine*n + line] / subMatrix[line*(n + 1)];
			for (size_t column = line; column < n; column++)
			{
				subMatrix[extraLine*n + column] -= factor * subMatrix[line*n + column];
			}
		}
		double result = 1;
		for (size_t lc = this->height; lc--;)
		{
			result *= subMatrix[lc*(n + 1)];
		}
		result *= sign;
		return result;

	}
}

	double Matrix::minor(size_t _line, size_t _column) const
	{
		_line--;
		_column--;
		if (this->height != this->width)
		{
			std::perror("Nonsquare matrix");
			return NULL;
		}
		size_t n = this->height;
		if (n < 2)
		{
			std::perror("Empty minor");
			return NULL;
		}
		n--;
		Matrix newMatrix;
		newMatrix.height = n;
		newMatrix.width = n;
		newMatrix.resize();
		size_t newIt(0);
		for (size_t it = 0; it < (this->height)*(this->width); it++)
		{
			if (it / n == _line) it += n;
			if (it % n == _column) it++;
			newMatrix.matrix[newIt] = this->matrix[it];
		}
		return newMatrix.determinant();
	}

	double Matrix::algebraicComplement(size_t _line, size_t _column) const
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
		Matrix result(*this);
		for (size_t it = result.height; it--;)
		{
				result.matrix[it] += add.matrix[it];
		}
		return result;
	}

	Matrix Matrix::operator-(Matrix const & rem) const
	{
		if ((this->height != rem.height) || (this->width != rem.width))
		{
			return Matrix();
			std::perror("Sub of level-different matrixes");
		}
		Matrix result(*this);
		for (size_t it = result.height; it--;)
		{
			result.matrix[it] -= rem.matrix[it];
		}
		return result;
	}

	Matrix Matrix::operator*(double const & alpha) const
	{
		Matrix result(*this);
		for (size_t it = result.height; it--;)
		{
			result.matrix[it] *= alpha;
		}
		return result;
	}

	Matrix Matrix::operator/(double const & alpha) const
	{
		return *this*(1 / alpha);
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
					result.matrix[line*result.width + column] += this->matrix[line*result.width + i] * getted.matrix[i * result.width + column];
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
		for (size_t it = this->height*this->width; it--;)
		{
			if (this->matrix[it] != getted.matrix[it])
				return false;
		}
		return true;
	}

	bool Matrix::operator!=(Matrix const & getted) const
	{
		return !(*this == getted);
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
				result.matrix[line*this->width + column] = this->matrix[column*this->height + line];
			}
		}
		return result;
	}

	Matrix Matrix::inverse() const
	{/*
		double determinant = this->determinant();
		if (!(determinant))
		{
			std::perror("Determinant = NULL");
			return Matrix();
		}
		Matrix result;
		size_t n = this->height;
		result.height = n;
		result.width = n;
		result.resize();
		for (size_t i = 0; i < result.height; i++)
		{
			result.matrix[i*(n + 1)] = 1;
		}
		std::vector<double> getted = this->matrix;
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

		for (size_t mainColumn = n - 1; mainColumn > 0; mainColumn--)
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
		return result;*/
		return Matrix();
		std::perror("This function(inverse) doesn't work");
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
