#include <cmath>
#include "IntegralFunctionsTests.h"

float TestIntegrand_1(float x)
{
	return x * x * sin(x);
}

float TestIntegrand_2(float x)
{
	return sin(x) * cos(x);
}

float TestIntegrand_3(float x)
{
	return exp(x);
}

bool IntegralFunctionTest(const std::function<float(const std::function<float(float)>, float, float, int, int)>& IntegralFunctionToTest, const std::function<float(float)>& Integrand, float a, float b, int PartsAmount, float RealResult, float AcceptableBiasRate)
{
	float FuncResult = IntegralFunctionToTest(Integrand, a, b, PartsAmount, -1);
	bool Result = (((RealResult - abs(RealResult) * AcceptableBiasRate) < FuncResult) && ((RealResult + abs(RealResult) * AcceptableBiasRate) > FuncResult));
	if (Result)
	{
		printf("Test Succesful\n");
	}
	else
	{
		printf("Test Failed\nReal Output: %f\nProgram Output: %f\n", RealResult, FuncResult);
	}
	return Result;
}