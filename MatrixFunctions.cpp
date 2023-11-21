#include <omp.h>
#include <vector>
#include <cmath>
#include "MatrixFunctions.h"

void PrintFloatVector(std::vector<float> vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		printf("%f; ", vec[i]);
	}
}

void PrintMatrix(std::vector<float> Matrix, int ColumnsCount)
{
	for (size_t i = 0; i < Matrix.size(); i++)
	{
		if (i % ColumnsCount == 0)
		{
			printf("\n");
		}
		printf("%f; ", Matrix[i]);
	}
}

std::vector<float> SquareMatrixMultiplication(std::vector<float> MatrixA, std::vector<float> MatrixB)
{
	float n = std::sqrt(MatrixA.size());
	if (n != std::floor(n))
	{
		printf("SquareMatrixMultiplication error: Matrices are not square");
		return {};
	}
	else if (MatrixA.size() != MatrixB.size())
	{
		printf("SquareMatrixMultiplication error: Matrices size is not equal");
		return {};
	}
	else
	{
		std::vector<float> ResultMatrix(MatrixA.size(), 0.f);
		for (int FirstMatrixRow = 0; FirstMatrixRow < n; FirstMatrixRow++)
		{
			for (int SecondMatrixColumn = 0; SecondMatrixColumn < n; SecondMatrixColumn++)
			{
				float NextResultElement = 0.f;
				for (int CurrentElement = 0; CurrentElement < n; CurrentElement++)
				{
					NextResultElement += MatrixA[FirstMatrixRow * (int)n + CurrentElement] * MatrixB[CurrentElement* (int)n + SecondMatrixColumn];
				}
				ResultMatrix[FirstMatrixRow * (int)n + SecondMatrixColumn] = NextResultElement;
			}
		}
		//PrintMatrix(ResultMatrix, (int)n);
		return ResultMatrix;
	}
}

std::vector<float> SquareMatrixMultiplicationParallel(std::vector<float> MatrixA, std::vector<float> MatrixB)
{
	float n = std::sqrt(MatrixA.size());
	if (n != std::floor(n))
	{
		printf("SquareMatrixMultiplication error: Matrices are not square");
		return {};
	}
	else if (MatrixA.size() != MatrixB.size())
	{
		printf("SquareMatrixMultiplication error: Matrices size is not equal");
		return {};
	}
	else
	{
		std::vector<float> ResultMatrix(MatrixA.size(), 0.f);
		int FirstMatrixRow, SecondMatrixColumn, CurrentElement = 0;
		float NextResultElement = 0.f;
		for (FirstMatrixRow = 0; FirstMatrixRow < (int)n; FirstMatrixRow++)
			{   
			for (SecondMatrixColumn = 0; SecondMatrixColumn < (int)n; SecondMatrixColumn++)
			{
				NextResultElement = 0.f;
#pragma omp parallel for reduction (+:NextResultElement)
				for (CurrentElement = 0; CurrentElement < (int)n; CurrentElement++)
				{
					NextResultElement += MatrixA[FirstMatrixRow * (int)n + CurrentElement] * MatrixB[CurrentElement * (int)n + SecondMatrixColumn];
				}
				ResultMatrix[FirstMatrixRow * (int)n + SecondMatrixColumn] = NextResultElement;
			}
		}
		//PrintMatrix(ResultMatrix, (int)n);
		return ResultMatrix;
	}
}

float MatrixElementsSum(std::vector<std::vector<float>> Matrix)
{
	float Sum = 0;
	for (std::vector<float> Row : Matrix)
	{
		for (float Elem : Row)
		{
			Sum += Elem;
		}
	}
	return Sum;
}

float MatrixElementsSumParallelNoReduction(std::vector<std::vector<float>> Matrix)
{
	float Sum = 0;
#pragma omp parallel for collapse(2)
	for (int i = 0; i < Matrix.size(); i++)
	{
		for (int j = 0; j < Matrix[i].size(); j++)
		{
			Sum += Matrix[i][j];
		}
	}
	return Sum;
}

float MatrixElementsSumParallel(std::vector<std::vector<float>> Matrix)
{
	float Sum = 0;
#pragma omp parallel for collapse(2) reduction (+:Sum)
	for (int i = 0; i < Matrix.size(); i++)
	{
		for (int j = 0; j < Matrix[i].size(); j++)
		{
			Sum += Matrix[i][j];
		}
	}
	return Sum;
}
