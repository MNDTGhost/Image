#include "stdafx.h"
#include "AdaBoost.h"

AdaBoost::~AdaBoost()
{
	delete _dataWeights;
	_dataWeights = nullptr;

	delete _strongClassfier;
	_strongClassfier = nullptr;
}

void AdaBoost::Init()
{
	assert(_data.size() > 0 && _data[0].size() > 0);

	_dataSize = _data.size();
	_dimensionSize = _data[0].size();
	_dataWeights = new std::vector<double>(_dataSize, 1.0 / _dataSize);
	_strongClassfier = new StrongClassfier();
}


void AdaBoost::Train(C_UINT32 weakSize)
{
	for (UINT32 index = 0; index < weakSize; index++)
	{
		WeakClassifier weakClassifier;
		AdaBoostType::LABELS pridect;

		ProcessError(weakClassifier, pridect);

		UpdateWeights(weakClassifier, pridect);

		_strongClassfier->Add(weakClassifier);
	}
}

void AdaBoost::ProcessError(WeakClassifier& minWeakClassifier, AdaBoostType::LABELS& minPridect)
{
	WeakClassifier weakClassifier;

	double minError = 100000;

	for (UINT32 dimension = 0; dimension < _dimensionSize; dimension++)
	{
		weakClassifier.Dimension(dimension);

		for (UINT32 index = 0; index < _dataSize; index++)
		{
			weakClassifier.Threshold(_data[index][dimension]);

			const WeakClassifier::SignType signs[] = { WeakClassifier::SignType::BIG
				, WeakClassifier::SignType::SMALL };

			for (UINT32 signIndex = 0; signIndex < sizeof(signs) / sizeof(WeakClassifier::SignType); signIndex++)
			{
				weakClassifier.Sign(signs[signIndex]);

				const std::vector<__int32> pridect = weakClassifier.Predict(_data, dimension);
				C_DOUBLE error = CalcError(pridect);

				if (error < minError)
				{
					minWeakClassifier = weakClassifier;
					minPridect = pridect;
					minError = error;
				}
			}

		}
	}
	minWeakClassifier.Error(minError);
}

double AdaBoost::CalcError(AdaBoostType::C_LABELS& pridect)
{
	assert(pridect.size() == _label.size());

	double error = 0.0;

	for (UINT32 index = 0; index < _dataSize; index++)
	{
		if (pridect[index] != _label[index])
		{
			error += _dataWeights->at(index);
		}
	}

	return error;
}

void AdaBoost::UpdateWeights(const WeakClassifier& weakClassifier, AdaBoostType::C_LABELS& pridect)
{
	double sum = 0;

	for (UINT32 index = 0; index < _dataSize; index++)
	{
		_dataWeights->at(index) *= exp(-weakClassifier.Alpha() * pridect[index] * _label[index]);
		sum += _dataWeights->at(index);
	}

	for (UINT32 index = 0; index < _dataSize; index++)
	{
		_dataWeights->at(index) /= sum;
	}

}

AdaBoostType::LABELS AdaBoost::Predict(AdaBoostType::C_DATAS& data) const
{
	return _strongClassfier->Predict(data);
}

AdaBoostType::LABEL AdaBoost::Predict(AdaBoostType::C_DATA& data) const
{
	return _strongClassfier->Predict(data);
}