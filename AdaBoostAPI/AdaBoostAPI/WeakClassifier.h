#pragma once
#ifndef WEAKCLASSIFIER_H
#define WEAKCLASSIFIER_H
#include "general.h"

/**********************************************************
 * pridect formula: alpha * compare(DATAS[dimension], threshold)
***********************************************************/
class WeakClassifier
{
public:
	enum SignType
	{
		BIG, SMALL
	};

	WeakClassifier();
	~WeakClassifier();

	WeakClassifier& operator=(const WeakClassifier& weakClassifier);

	AdaBoostType::LABELS Predict(AdaBoostType::C_DATAS& data, C_UINT32& dimension) const;

	std::vector<double> WeightsPredict(AdaBoostType::C_DATAS& data) const;

	double WeightsPredict(AdaBoostType::C_DATA& data) const;

	void Dimension(C_UINT32 dimension);
	UINT32 Dimension() const;

	void Threshold(C_DOUBLE threshold);
	double Threshold() const;

	double Alpha() const;

	void Error(C_DOUBLE sign);
	double Error() const;

	void Sign(const SignType sign);
	SignType Sign() const;

	void SetWeakParams(C_UINT32 dimension, C_DOUBLE threshold, C_DOUBLE alpha, const SignType sign);

	void SetWeakParams(C_UINT32 dimension, C_DOUBLE threshold, C_DOUBLE alpha);

private:
	typedef bool (*CMP_FM)(C_DOUBLE, C_DOUBLE);

	CMP_FM GetCompareFormula() const;

	UINT32 _dimension;
	double _threshold;
	double _alpha;
	double _error;
	SignType _sign;
};

#endif // !WEAKCLASSIFIER_H
