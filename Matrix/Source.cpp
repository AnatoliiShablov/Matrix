#include <cstdio> //Library for files(read from files, write to files)
#include <chrono>
#include "Matrix.h" // Library for matrix (need to be in folder of project)

const size_t NumberOfTests = 1;
int main()
{
	FILE* fileInput = std::fopen("testin.txt", "r"); //FILE* nameOfVariable = std::fopen("nameOfFile", "mode");
	FILE* fileOutput = std::fopen("testout.txt", "w"); // r - readmode, w - writemode;

	Matrix x;
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	for (int i = 0; i < NumberOfTests; i++)
	{
		x.scanMatrix(fileInput);
		std::fprintf(fileOutput,"%lf\n", x.determinant());
		x.transpose().printMatrix(fileOutput);
	}
	end = std::chrono::system_clock::now();
	std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::fprintf(fileOutput, "\n\nDURATION - %f", std::chrono::duration<float>(duration));
	return 0;
}