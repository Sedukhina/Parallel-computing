#include <omp.h>
#include <stdio.h>
#include <random>

#include "MatrixFunctions.h"

void GenerateFloatVector(unsigned int VectorLength, std::vector<float>& Vec);

int main(void) 
{
#ifdef _OPENMP
	printf("OpenMP is supported!\n");
#endif

	double start_time, end_time, tick;
	start_time = omp_get_wtime();
	end_time = omp_get_wtime();
	tick = omp_get_wtick();
	printf("Time for time measurement %lf\n", end_time - start_time);
	printf("Timer precision %lf\n", tick);

#pragma omp parallel 
	{
		printf("Hello World\n");
	}

	return 0;
}

void GenerateFloatVector(unsigned int VectorLength, std::vector<float>& Vec)
{
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_real_distribution<> Dist(-5000, 5000);
	for (int i = Vec.size(); i < VectorLength + (int)!VectorLength; i++)
	{
		Vec.push_back((float)Dist(gen));
	}
}