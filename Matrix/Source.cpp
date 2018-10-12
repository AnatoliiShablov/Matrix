#include <cstdio> //Library for files(read from files, write to files)
#include <chrono>
#include <fstream>
#include "Matrix.h" // Library for matrix (need to be in folder of project)

const size_t NumberOfTests = 10;
const bool DispalayResult = false;

int main()
{
	std::cout << std::fixed << Matrix<int>::indentity(3) << std::endl;

	std::ifstream input("StressIn.txt");
	std::ofstream output("StressOut.txt");

	auto t_start = std::chrono::steady_clock::now();
	for (int i = 0; i < NumberOfTests; i++)
	{
		Matrix<double> x;
		input >> x;
		output << x.transpose();
	}
	auto t_end = std::chrono::steady_clock::now();
	output << "\n\nDURATION - " << (t_end - t_start).count();
	return 0;
}