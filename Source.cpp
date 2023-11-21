#include <omp.h>
#include <stdio.h>
#include <random>
#include "IntegralSolver.h"
#include "MatrixFunctions.h"
#include "IntegralFunctionsTests.h"

void GenerateFloatVector(unsigned int VectorLength, std::vector<float>& Vec);

float Integrand(float x);
void SolveIntegralAndMeasureTime(const std::function<float(float)>& Integrand, float a, float b, unsigned int PartsAmount, int NumThreads);

int main(void) 
{
	IntegralFunctionTest(IntegralSolver::LeftRiemannSum, TestIntegrand_1, 1, 45, 1e4, -988.37f, 0.01f);
	IntegralFunctionTest(IntegralSolver::LeftRiemannSum, TestIntegrand_2, 0, 400, 1e5, 0.36203f, 0.01f);
	IntegralFunctionTest(IntegralSolver::LeftRiemannSum, TestIntegrand_3, -30, 10, 1e4, 22026.f, 0.01f);
	IntegralFunctionTest(IntegralSolver::LeftRiemannSum, Integrand, 1, 9, 1e4, 52, 0.01f);
	
	SolveIntegralAndMeasureTime(Integrand, 1, 9, 1000, 10);

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
	printf("\nSolving Result %f\n", IntegralSolver::LeftRiemannSum(Integrand, a, b, PartsAmount, NumThreads));
	auto end_time = omp_get_wtime();
	printf("Time for solving %lf\n", end_time - start_time);
}

