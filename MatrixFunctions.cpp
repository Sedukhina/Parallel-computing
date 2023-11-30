#include <omp.h>
#include <vector>
#include <cmath>
#include "MatrixFunctions.h"
#include <algorithm>

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

void DivideMatrixRowByNumber(std::vector<std::vector<float>>& Matrix, int RowNum, float Number)
{
	for (int i = 0; i < Matrix[RowNum].size(); i++) {
		Matrix[RowNum][i] = Matrix[RowNum][i] / Number;
	}
}

void RowsSubstraction(std::vector<std::vector<float>>& Matrix, int MinuendRowNum, int SubtrahendRowNum, float multiplyer)
{
	for (int column = 0; column < Matrix[MinuendRowNum].size(); column++) {
		Matrix[MinuendRowNum][column] = Matrix[MinuendRowNum][column] - Matrix[SubtrahendRowNum][column] * multiplyer;
	}
}

bool IsColumnEmpty(std::vector<std::vector<float>>& Matrix, int ColumnNum)
{
	for (int j = 0; j < Matrix.size(); j++) {
		if (Matrix[j][ColumnNum] != 0) {
			return false;
		}
	}
	return true;
}

bool IsMatrixConsistent(std::vector<std::vector<float>>& Matrix)
{
	for (auto row : Matrix) {
		if (std::any_of(row.begin(), row.end(), [](int num) { return num != 0; })) {
			if (row[row.size() - 1] == 0 || !std::any_of(row.begin(), row.end() - 1, [](int num) { return num != 0; })) 
			{
				return false;
			}
		}
	}
	return true;
}

void SwapToGetDiagonalElementNonzero(std::vector<std::vector<float>>& Matrix, int i, int empty_cols, int empty_rows)
{
	for (int j = Matrix.size() - 1; j > 0; j--) {
		if (Matrix[j][i + empty_cols - empty_rows] != 0) {
			std::swap(Matrix[i], Matrix[j]);
		}
	}
}

//Gives empty output if matrix is inconsistent
std::vector<std::vector<float>> GaussianElimination(std::vector<std::vector<float>> Matrix)
{
	int EmptyCols = 0;
	int EmptyRows = 0;
	int i;
	for (i = 0; i < Matrix.size(); i++)
	{
		//Skipping empty rows
		while (!std::any_of(Matrix[i].begin(), Matrix[i].end(), [](int num) { return num != 0; }))
		{
			EmptyRows++;
			i++;
			if (i == Matrix.size())
			{
				if (IsMatrixConsistent(Matrix)) 
				{
					return Matrix;
				}
				else
				{
					return std::vector<std::vector<float>>();
				}
			}
		}
		//Skipping empty cols
		while (IsColumnEmpty(Matrix, i + EmptyCols - EmptyRows))
		{
			EmptyCols++;
			if (i + EmptyCols - EmptyRows == Matrix.size())
			{
				if (IsMatrixConsistent(Matrix))
				{
					return Matrix;
				}
				else
				{
					return std::vector<std::vector<float>>();
				}
			}
		}
		//Dealing with zeros on diagonal
		if (Matrix[i][i + EmptyCols - EmptyRows] == 0)
		{
			SwapToGetDiagonalElementNonzero(Matrix, i, EmptyCols, EmptyRows);
		}
		if (Matrix[i][i + EmptyCols - EmptyRows] != 0)
		{
			//Dividing row by diagonal elem
			DivideMatrixRowByNumber(Matrix, i, Matrix[i][i + EmptyCols - EmptyRows]);
			//Substracting row from other rows
#pragma omp parallel for 
			for (int RowNum = 0; RowNum < Matrix.size(); RowNum++)
			{
				if (RowNum != i) 
				{
					RowsSubstraction(Matrix, RowNum, i, Matrix[RowNum][i + EmptyCols - EmptyRows]);
				}
			}
		}

	}
	if (IsMatrixConsistent(Matrix))
	{
		return Matrix;
	}
	else
	{
		return std::vector<std::vector<float>>();
	}
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
