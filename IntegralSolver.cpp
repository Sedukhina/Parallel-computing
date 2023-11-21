#include "IntegralSolver.h"
#include <omp.h>
#include <algorithm>

float IntegralSolver::LeftRiemannSum(const std::function<float(float)>& Integrand, float a, float b, unsigned int PartsAmount, int NumThreads)
{
	float PartitionStep = (b - a) / PartsAmount;
	float Sum = 0;

	NumThreads = std::clamp(NumThreads, 1, omp_get_max_threads());
	omp_set_num_threads(NumThreads);

#pragma omp parallel for reduction (+:Sum)
	for (int i = 0; i < PartsAmount; i++)
	{
		Sum += Integrand(a + i * PartitionStep) * PartitionStep;
	}

	return Sum;
}