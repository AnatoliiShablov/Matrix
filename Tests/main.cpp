#include <complex>

#include <matrix/matrix.h>
#include <gtest/gtest.h>

struct A {
	static constexpr A unit() {
		A a;
		a.i = 1;
		return a;
	}

	constexpr bool operator==(const A& a) const {
		return i == a.i;
	}

private:
	int i = 0;
};

struct B {
	constexpr bool operator==(const B&) const {
		return true;
	}
};


int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

TEST(Matrix, SizeTest) {
	size_t height = 18;
	size_t width = 13;
	Matrix<int> matrix(width, height);

	ASSERT_EQ(matrix.height(), height);
	ASSERT_EQ(matrix.width(), width);
}

TEST(Matrix, RandomSetAndGet) {
	Matrix<int> matrix(10, 10);

	std::vector<std::vector<int>> matrixValues;
	matrixValues.reserve(matrix.height());
	for (int i = 0; i < matrix.height(); ++i) {
		std::vector<int> row;
		row.reserve(matrix.width());
		for (int j = 0; j < matrix.width(); ++j) {
			int number = rand() % 99;
			row.push_back(number);
			matrix[i][j] = number;
		}
		matrixValues.push_back(row);
	}

	for (int i = 0; i < matrix.height(); ++i) {
		for (int j = 0; j < matrix.width(); ++j) {
			ASSERT_EQ(matrix[i][j], matrixValues[i][j]);
		}
	}
}

TEST(Matrix, IndentityInt) {
	auto matrix = Matrix<int>::indentity(5);

	for (int i = 0; i < matrix.height(); ++i) {
		for (int j = 0; j < matrix.width(); ++j) {
			ASSERT_EQ(matrix[i][j], (i == j ? 1 : 0));
		}
	}
}

TEST(Matrix, IndentityDouble) {
	auto matrix = Matrix<double>::indentity(5);

	for (int i = 0; i < matrix.height(); ++i) {
		for (int j = 0; j < matrix.width(); ++j) {
			ASSERT_DOUBLE_EQ(matrix[i][j], (i == j ? 1. : 0.));
		}
	}
}

TEST(Matrix, IndentityComplex) {
	auto matrix = Matrix<std::complex<int>>::indentity(5);

	for (int i = 0; i < matrix.height(); ++i) {
		for (int j = 0; j < matrix.width(); ++j) {
			ASSERT_EQ(matrix[i][j], (i == j ? std::complex<int>{1, 0} : std::complex<int>{0, 0}));
		}
	}
}

TEST(Matrix, IndentityClassWithUnitMethod) {
	auto matrix = Matrix<A>::indentity(5);

	for (int i = 0; i < matrix.height(); ++i) {
		for (int j = 0; j < matrix.width(); ++j) {
			ASSERT_EQ(matrix[i][j], (i == j ? A::unit() : A()));
		}
	}
}

TEST(Matrix, IndentityClassWithoutUnitMethod) {
	auto matrix = Matrix<B>::indentity(5);

	for (int i = 0; i < matrix.height(); ++i) {
		for (int j = 0; j < matrix.width(); ++j) {
			ASSERT_EQ(matrix[i][j], B());
		}
	}
}

