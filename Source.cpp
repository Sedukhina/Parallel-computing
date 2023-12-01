#include <omp.h>
#include <random>
#include "IntegralSolver.h"
#include "MatrixFunctions.h"
#include "IntegralFunctionsTests.h"
#include "PiApproximation.h"

# define M_PIl          3.141592653589793238462643383279502884L

void GenerateFloatVector(unsigned int VectorLength, std::vector<float>& Vec);

float Integrand(float x);
void SolveIntegralAndMeasureTime(const std::function<float(float)>& Integrand, float a, float b, unsigned int PartsAmount, int NumThreads);
void TestGaussianEliminationSpeed(int RowsAmount, int ColumnsAmount, int NumThreads);

int main(void) 
{
	for (size_t n = 1e2; n < 1e9; n *= 10)
	{
		for (int NumThreads = 1; NumThreads < omp_get_max_threads() + 1; NumThreads*=4)
		{
			int CachedMaxThreads = omp_get_max_threads();
			omp_set_num_threads(NumThreads);

			auto start_time = omp_get_wtime();
			auto Result = PiApproximation(n);
			auto end_time = omp_get_wtime();

			printf("Number of Samples %li\nNumber of Threads %i\nTime for solving %lf\nResult %lf\nDelta %lf\n\n", n, NumThreads, end_time - start_time, Result, abs(Result - M_PIl));
			omp_set_num_threads(CachedMaxThreads);
		}
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

inline float Integrand(float x)
{
	return 3.f * sqrt(x);
}

void SolveIntegralAndMeasureTime(const std::function<float(float)>& Integrand, float a, float b, unsigned int PartsAmount, int NumThreads)
{
	auto start_time = omp_get_wtime();
	printf("Solving Result %f\n", IntegralSolver::LeftRiemannSum(Integrand, a, b, PartsAmount, NumThreads));
	auto end_time = omp_get_wtime();
	printf("Time for solving %lf\n", end_time - start_time);
}

void TestGaussianEliminationSpeed(int RowsAmount, int ColumnsAmount, int NumThreads)
{
	int CachedMaxThreads = omp_get_max_threads();
	NumThreads = std::clamp(NumThreads, 1, CachedMaxThreads);
	omp_set_num_threads(NumThreads);

	std::vector<std::vector<float>> Matrix;
	for (size_t i = 0; i < RowsAmount; i++)
	{
		Matrix.push_back({});
		(GenerateFloatVector(ColumnsAmount, Matrix[i]));
	}
	auto start_time = omp_get_wtime();
	GaussianElimination(Matrix);
	auto end_time = omp_get_wtime();
	printf("Matrix size: %i x %i\nNumber of Threads %i\nTime for solving %lf\n", RowsAmount, ColumnsAmount, NumThreads, end_time - start_time);

	omp_set_num_threads(CachedMaxThreads);
}

