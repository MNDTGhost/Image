#pragma once
#ifndef STRONGCLASSFIER_H
#define STRONGCLASSFIER_H
#include "general.h"
#include "WeakClassifier.h"

/**********************************************************
* pridect formula: sign(sum(weakClassfier.weightsPredict()))
***********************************************************/
class StrongClassfier
{
public:
	StrongClassfier();
	~StrongClassfier();

	void Add(const WeakClassifier& weakClassifier);

	AdaBoostType::LABELS Predict(AdaBoostType::C_DATAS& data) const;

	AdaBoostType::LABEL Predict(AdaBoostType::C_DATA& data) const;

	AdaBoostType::LABELS Sign(const std::vector<double>& predict) const;

	AdaBoostType::LABEL Sign(const double predict) const;

private:
	std::vector<WeakClassifier>* _weakClassifiers;

};

#endif