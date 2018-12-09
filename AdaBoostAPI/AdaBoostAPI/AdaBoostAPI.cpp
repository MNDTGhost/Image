// AdaBoostAPI.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AdaBoost.h"
#include "general.h"
#include <iostream>
int main()
{
	AdaBoostType::DATAS data = { {0}, {1},{ 2 },{ 3 },{ 4 },{ 5 },{ 6 },{ 7 },{ 8 },{ 9 } };

	AdaBoostType::LABELS label = { 1, 1, 1, -1, -1, -1, 1, 1, 1, -1 };

	AdaBoost adaBoost(data, label);
	adaBoost.Train(5);

	AdaBoostType::LABELS labels = adaBoost.Predict(data);
	for (UINT32 index = 0; index < labels.size(); index++)
	{
		std::cout << labels[index] << " ";
	}

	system("pause");
	return 0;
}

