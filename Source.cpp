#include <omp.h>
#include <stdio.h>
#include <random>
#include <Windows.h>
#include "IntegralSolver.h"
#include "MatrixFunctions.h"
#include "IntegralFunctionsTests.h"
#include <iostream>

void GenerateFloatVector(unsigned int VectorLength, std::vector<float>& Vec);

float Integrand(float x);
void SolveIntegralAndMeasureTime(const std::function<float(float)>& Integrand, float a, float b, unsigned int PartsAmount, int NumThreads);

int main(void) 
{
	
	IntegralFunctionTest(IntegralSolver::LeftRiemannSum, TestIntegrand_1, 1, 45, 1e4, -988.37f, 0.01f);
	IntegralFunctionTest(IntegralSolver::LeftRiemannSum, TestIntegrand_2, 0, 400, 1e5, 0.36203f, 0.01f);
	IntegralFunctionTest(IntegralSolver::LeftRiemannSum, TestIntegrand_3, -30, 10, 1e4, 22026.f, 0.01f);
	IntegralFunctionTest(IntegralSolver::LeftRiemannSum, Integrand, 1, 9, 1e4, 52, 0.01f);
	
	
	printf("Enter Parts Amount\n");
	double PartsAmount;
	std::cin >> PartsAmount;

	printf("Enter Threads Amount\n");
	unsigned int ThreadsAmount;
	std::cin >> ThreadsAmount;

	SolveIntegralAndMeasureTime(Integrand, 1, 9, PartsAmount, ThreadsAmount);
	
	/*
	for (size_t ThreadsAmount = 1; ThreadsAmount < omp_get_max_threads()*2; ThreadsAmount *= 2)
	{
		for (size_t PartsAmount = 10; PartsAmount < 1e8; PartsAmount *= 1e2)
		{
			SolveIntegralAndMeasureTime(Integrand, 1, 9, PartsAmount, ThreadsAmount);
			printf("\n");
		}
	}
	*/

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

