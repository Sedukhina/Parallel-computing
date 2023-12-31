#pragma once
#include <vector>

extern std::vector<float> SquareMatrixMultiplication(std::vector<float> MatrixA, std::vector<float> MatrixB);
extern std::vector<float> SquareMatrixMultiplicationParallel(std::vector<float> MatrixA, std::vector<float> MatrixB);

extern float MatrixElementsSumParallel(std::vector<std::vector<float>> Matrix);
extern float MatrixElementsSumParallelNoReduction(std::vector<std::vector<float>> Matrix);
extern float MatrixElementsSum(std::vector<std::vector<float>> Matrix);

extern void DivideMatrixRowByNumber(std::vector<std::vector<float>>& Matrix, int RowNum, float Number);
extern void RowsSubstraction(std::vector<std::vector<float>>& Matrix, int MinuendRowNum, int SubtrahendRowNum, float multiplyer = 1.f);

extern bool IsColumnEmpty(std::vector<std::vector<float>>& Matrix, int ColumnNum);
extern bool IsMatrixConsistent(std::vector<std::vector<float>>& Matrix);

extern void SwapToGetDiagonalElementNonzero(std::vector<std::vector<float>>& Matrix, int i, int empty_cols, int empty_rows);
extern std::vector<std::vector<float>> GaussianElimination(std::vector<std::vector<float>> Matrix);

extern void PrintFloatVector(std::vector<float> vec);
