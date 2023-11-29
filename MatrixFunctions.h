#pragma once
#include <vector>

extern std::vector<float> SquareMatrixMultiplication(std::vector<float> MatrixA, std::vector<float> MatrixB);
extern std::vector<float> SquareMatrixMultiplicationParallel(std::vector<float> MatrixA, std::vector<float> MatrixB);

extern float MatrixElementsSumParallel(std::vector<std::vector<float>> Matrix);
extern float MatrixElementsSumParallelNoReduction(std::vector<std::vector<float>> Matrix);
extern float MatrixElementsSum(std::vector<std::vector<float>> Matrix);

extern std::vector<float> GaussianElimination(std::vector<std::vector<float>> Matrix);

extern void PrintFloatVector(std::vector<float> vec);
