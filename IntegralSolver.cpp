#include "IntegralSolver.h"
#include <omp.h>
#include <algorithm>

float IntegralSolver::LeftRiemannSum(const std::function<float(float)>& Integrand, float a, float b, unsigned int PartsAmount, int ThreadsAmount)
{
	if (PartsAmount < 1)
	{
		PartsAmount = 1;
	}

	float PartitionStep = (b - a) / PartsAmount;
	float Sum = 0;

	int CachedMaxThreads = omp_get_max_threads();

	ThreadsAmount = std::clamp(ThreadsAmount, 1, CachedMaxThreads);
	omp_set_num_threads(ThreadsAmount);

	printf("Parts Amount: %i\n", PartsAmount);
	printf("Threads Amount: %i\n", ThreadsAmount);

#pragma omp parallel for reduction (+:Sum)
	for (int i = 0; i < PartsAmount; i++)
	{
		Sum += Integrand(a + i * PartitionStep) * PartitionStep;
	}

	omp_set_num_threads(CachedMaxThreads);

	return Sum;
}