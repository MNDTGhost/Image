#pragma once
#ifndef GAUSSIANELIMINATION_H
#define GAUSSIANELIMINATION_H
#include "general.h"

class GaussianElimination
{
public:
	GaussianElimination(float** matrix, C_UINT32& row, C_UINT32& col) :_matrix(matrix), _row(row), _col(col) {};

	~GaussianElimination();

	void Compute();
private:
	void SwapRow(float** col1, float** col2);

	void AddRow(C_FLOAT* srcCol, float* purCol, C_FLOAT base);

	void LeaderOne(float* col, C_FLOAT base);

	C_UINT32 _row;
	C_UINT32 _col;
	float** _matrix;
};

#endif // !GAUSSIANELIMINATION_H