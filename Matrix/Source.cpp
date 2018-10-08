#include <cstdio> //Library for files(read from files, write to files)
#include "Matrix.h" // Library for matrix (need to be in folder of project)

int main()
{
	FILE* fileInput = std::fopen("testin.txt", "r"); //FILE* nameOfVariable = std::fopen("nameOfFile", "mode");
	FILE* fileOutput = std::fopen("testout.txt", "w"); // r - readmode, w - writemode;

	Matrix x;
	Matrix b;
	x.scanMatrix(fileInput,3,3);
	b.scanMatrix(fileInput, 3, 1);
	b = x.inverse() * b;
	b.printMatrix(fileOutput);
	std::fprintf(fileOutput, "%f", x.determinant());
	// have some funcitons like .minor(line, column), .algebraicComplement(line, column)
	/*char c;
	std::printf("Any button to exit...");
	std::scanf("%c", &c);*/
	return 0;
}