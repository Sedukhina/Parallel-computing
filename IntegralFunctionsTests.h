#pragma once
#include <functional>

extern float TestIntegrand_1(float x);
extern float TestIntegrand_2(float x);
extern float TestIntegrand_3(float x);
extern bool IntegralFunctionTest(const std::function<float(const std::function<float(float)>, float, float, int, int)>& IntegralFunctionToTest, const std::function<float(float)>& Integrand, float a, float b, int PartsAmount, float RealResult, float AcceptableBias);
