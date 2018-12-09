#include "stdafx.h"
#include "StrongClassfier.h"

StrongClassfier::StrongClassfier()
{
	_weakClassifiers = new std::vector<WeakClassifier>();
}

StrongClassfier::~StrongClassfier()
{
	delete _weakClassifiers;
	_weakClassifiers = nullptr;
}

void StrongClassfier::Add(const WeakClassifier& weakClassifier)
{
	_weakClassifiers->push_back(weakClassifier);
}

AdaBoostType::LABELS StrongClassfier::Predict(AdaBoostType::C_DATAS& data) const
{
	AdaBoostType::LABELS predict(data.size());

	for (UINT32 index = 0; index < data.size(); index++)
	{
		predict[index] = Predict(data[index]);
	}

	return predict;
}

AdaBoostType::LABEL StrongClassfier::Predict(AdaBoostType::C_DATA& data) const
{
	double predict = 0;
	for (UINT32 index = 0; index < _weakClassifiers->size(); index++)
	{
		const double weakPredict = _weakClassifiers->at(index).WeightsPredict(data);

		for (UINT32 predIndex = 0; predIndex < data.size(); predIndex++)
		{
			predict += weakPredict;
		}
	}
	return Sign(predict);
}


AdaBoostType::LABELS StrongClassfier::Sign(const std::vector<double>& predict) const
{
	AdaBoostType::LABELS labels(predict.size());

	for (UINT32 index = 0; index < predict.size(); index++)
	{
		labels[index] = Sign(predict[index]);
	}
	return labels;
}

AdaBoostType::LABEL StrongClassfier::Sign(const double predict) const
{
	return predict > 0 ? 1 : -1;
}