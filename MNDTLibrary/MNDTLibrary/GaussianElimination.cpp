#include "GaussianElimination.h"

GaussianElimination::~GaussianElimination()
{
}

void GaussianElimination::SwapRow(float** col1, float** col2)
{
	float* ptr = *col1;
	*col1 = *col2;
	*col2 = ptr;
}

void GaussianElimination::AddRow(C_FLOAT* srcCol, float* purCol, C_FLOAT base)
{
	for (UINT32 index = 0; index < _col; index++)
	{
		*(purCol + index) += *(srcCol + index) * base;
	}
}

void GaussianElimination::LeaderOne(float* col, C_FLOAT base)
{
	for (UINT32 index = 0; index < _col; index++) // 走訪每一個列
	{
		if (*(col + index) != 0)
		{
			*(col + index) *= 1 / base; // 乘上 1 / iMulBase 使領導係數變為1
		}
	}
}

void GaussianElimination::Compute()
{
	UINT32 row = 0;
	UINT32 col = 0;

	while (row < _row && col < _col)
	{
		bool isCompute = false;
		UINT32 nextRow = row;

		while (nextRow < _row && !isCompute)
		{
			if (_matrix[nextRow][col] != 0)
			{
				SwapRow(&_matrix[row], &_matrix[nextRow]);
				isCompute = true;
			}
			else
			{
				nextRow++;
			}
		}


		if (isCompute)
		{
			LeaderOne(*(_matrix + row), *(*(_matrix + row) + col));

			for (UINT32 index = 0; index < row; index++)
			{
				AddRow(_matrix[row], _matrix[index], -_matrix[index][col]);
			}

			for (UINT32 index = row + 1; index < _row; index++)
			{
				AddRow(_matrix[row], _matrix[index], -_matrix[index][col]);
			}
		}
		row++;
		col++;
	}
}