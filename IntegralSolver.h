#pragma once
#include <functional>

class IntegralSolver
{
public:
	static float LeftRiemannSum(const std::function<float(float)>& Integrand, float a, float b, unsigned int PartsAmount, int NumThreads);
};

