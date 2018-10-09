#include <cstdio> //Library for files(read from files, write to files)
#include <chrono>
#include <ctime>
#include "Matrix.h" // Library for matrix (need to be in folder of project)

const size_t NumberOfTests = 10;
const bool DispalayResult = false;

int main()
{
	FILE* fileInput = std::fopen("StressIn.txt", "r"); //FILE* nameOfVariable = std::fopen("nameOfFile", "mode");
	FILE* fileOutput = std::fopen("StressOut.txt", "w"); // r - readmode, w - writemode;

	Matrix x;
	auto t_start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < NumberOfTests; i++)
	{
		x.scanMatrix(fileInput);
		//std::fprintf(fileOutput,"%lf\n", x.determinant());
		if (DispalayResult)
			x.transpose().printMatrix(fileOutput);
		else
			x.transpose();
	}
	auto t_end = std::chrono::high_resolution_clock::now();
	double duration = std::chrono::duration<double, std::milli>(t_end - t_start).count();
	std::fprintf(fileOutput, "\n\nDURATION - %f", duration);
	return 0;
}