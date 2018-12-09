#include "stdafx.h"
#include "WeakClassifier.h"

WeakClassifier::WeakClassifier()
{

}

WeakClassifier::~WeakClassifier()
{

}

WeakClassifier& WeakClassifier::operator=(const WeakClassifier& weakClassifier)
{
	_dimension = weakClassifier.Dimension();
	_threshold = weakClassifier.Threshold();
	_alpha = weakClassifier.Alpha();
	_sign = weakClassifier.Sign();

	return *this;
}

AdaBoostType::LABELS WeakClassifier::Predict(AdaBoostType::C_DATAS& data, C_UINT32& dimension) const
{
	C_UINT32 size = data.size();

	std::vector<__int32> predict(size);
	WeakClassifier::CMP_FM compare = GetCompareFormula();

	for (UINT32 index = 0; index < size; index++)
	{
		if (compare(data[index][dimension], _threshold))
		{
			predict[index] = 1;
		}
		else
		{
			predict[index] = -1;
		}
	}
	return predict;
}

std::vector<double> WeakClassifier::WeightsPredict(AdaBoostType::C_DATAS& data) const
{
	C_UINT32 size = data.size();

	std::vector<double> predict(size);
	WeakClassifier::CMP_FM compare = GetCompareFormula();

	for (UINT32 index = 0; index < size; index++)
	{
		if (compare(data[index][_dimension], _threshold))
		{
			predict[index] =  _alpha;
		}
		else
		{
			predict[index]= -_alpha;
		}
	}
	return predict;
}

double WeakClassifier::WeightsPredict(AdaBoostType::C_DATA& data) const
{
	WeakClassifier::CMP_FM compare = GetCompareFormula();

	if (compare(data[_dimension], _threshold))
	{
		return _alpha;
	}
	else
	{
		return -_alpha;
	}
}

WeakClassifier::CMP_FM WeakClassifier::GetCompareFormula() const
{
	switch (_sign)
	{
	case SignType::SMALL:
		return [](C_DOUBLE value, C_DOUBLE threshold) {return value <= threshold; };
	case SignType::BIG:
		return [](C_DOUBLE value, C_DOUBLE threshold) {return value > threshold; };
	default:
		return [](C_DOUBLE value, C_DOUBLE threshold) {return value <= threshold; };
	}
}

void WeakClassifier::Dimension(C_UINT32 dimension)
{
	_dimension = dimension;
}

UINT32 WeakClassifier::Dimension() const
{
	return _dimension;
}

void  WeakClassifier::Threshold(C_DOUBLE threshold)
{
	_threshold = threshold;
}

double  WeakClassifier::Threshold() const
{
	return _threshold;
}

void WeakClassifier::Error(C_DOUBLE error)
{
	_error = error;
	_alpha = 0.5 * log((1.0 - error) / std::max(error, 0.0000000000001)) / log(exp(1));
}

double WeakClassifier::Error() const
{
	return _error;
}

double WeakClassifier::Alpha() const
{
	return _alpha;
}

void WeakClassifier::Sign(const SignType sign)
{
	_sign = sign;
}

WeakClassifier::SignType WeakClassifier::Sign() const
{
	return _sign;
}

void WeakClassifier::SetWeakParams(C_UINT32 dimension, C_DOUBLE threshold, C_DOUBLE error, const SignType sign)
{
	Dimension(dimension);
	Threshold(threshold);
	Error(error);
	Sign(sign);
}

void WeakClassifier::SetWeakParams(C_UINT32 dimension, C_DOUBLE threshold, C_DOUBLE error)
{
	Dimension(dimension);
	Threshold(threshold);
	Error(error);
}